#include <QSqlError>
#include <QSqlRecord>
#include "systemdatabase.h"

SystemDatabase::SystemDatabase(QSqlDatabase *database)
{
    m_database = database;
}

SystemDatabase::~SystemDatabase()
{

}

QList<QMap<QString, QVariant>> SystemDatabase::select()
{
    QList<QMap<QString, QVariant>> list;
    QSqlQuery query;

    if (query.exec("SELECT * FROM `system`")) {
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

QStringList SystemDatabase::selectNames()
{
    QStringList list;
    QSqlQuery query;

    if (query.exec("SELECT * FROM `system`")) {
        while (query.next()) {
            list.append(query.value("name").toString());
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

bool SystemDatabase::add(QString name)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `system` (`name`) VALUES(?)");
    query.bindValue(0, name);

    return this->exec(query, "addSystem");
}

bool SystemDatabase::remove(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `system` WHERE `id`=?");
    query.bindValue(0, id);

    return this->exec(query, "removeSystem");
}

bool SystemDatabase::change(int id, QString newName)
{
    QSqlQuery query;

    query.prepare("UPDATE `system` SET `name`=? WHERE `id`=?");
    query.bindValue(0, newName);
    query.bindValue(1, id);

    return this->exec(query, "changeSystem");
}

int SystemDatabase::findByName(QString name)
{
    QSqlQuery query;

    query.prepare("SELECT `system`.`id` FROM `system` WHERE `name`=?");
    query.bindValue(0, name);

    if (query.exec()) {
        query.next();
        return query.value("id").toInt();
    } else {
        #ifdef QT_DEBUG
            QSqlError error = query.lastError();

            qDebug() << "Query not executed";
            qDebug() << error.text();
        #endif
    }

    return -1;
}

bool SystemDatabase::exec(QSqlQuery query, QString debugMethod)
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
