#include <QSqlError>
#include <QSqlRecord>
#include "stationdatabase.h"

StationDatabase::StationDatabase(QSqlDatabase *database)
{
    m_database = database;
}

QList<QMap<QString, QVariant> > StationDatabase::select()
{
    QList<QMap<QString, QVariant>> list;
    QSqlQuery query;

    if (query.exec("SELECT `station`.`id`, `system`.`name` AS `system`, `station`.`name` FROM `station` LEFT JOIN `system` ON `station`.`system` = `system`.`id`")) {
        while (query.next()) {
            QMap<QString, QVariant> result;
            QSqlRecord record = query.record();

            for (int i = 0; i < record.count(); ++i) {
                result.insert(record.fieldName(i), record.value(i));
            }

            list.append(result);
        }
    } else {
        #ifdef QT_DEBUG
            QSqlError error = query.lastError();

            qDebug() << "Query not executed";
            qDebug() << error.text();
        #endif
    }

    return list;
}

bool StationDatabase::add(int systemId, QString name)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `station` (`system`, `name`) VALUES(?, ?)");
    query.bindValue(0, systemId);
    query.bindValue(1, name);

    return this->exec(query, "addStation");
}

bool StationDatabase::remove(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `station` WHERE `id` = ?");
    query.bindValue(0, id);

    return this->exec(query, "removeStation");
}

bool StationDatabase::change(int id, int systemId, QString name)
{
    QSqlQuery query;

    query.prepare("UPDATE `station` SET `name`=?, `system`=? WHERE `id`=?");
    query.bindValue(0, name);
    query.bindValue(1, systemId);
    query.bindValue(2, id);

    return this->exec(query, "changeStation");
}

bool StationDatabase::exec(QSqlQuery query, QString debugMethod)
{
    if (!query.exec()) {
        #ifdef QT_DEBUG
            qDebug() << debugMethod << " - Not executed";
            qDebug() << query.lastError().text();
        #endif

        return false;
    }

    return true;
}
