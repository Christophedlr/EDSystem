#include <QSqlError>
#include <QSqlQuery>
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

bool SystemDatabase::add(QString name)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `system` (`name`) VALUES(?)");
    query.bindValue(0, name);

    if (!query.exec()) {
        #ifdef QT_DEBUG
            qDebug() << "addSystem - Not executed";
            qDebug() << query.lastError().text();
        #endif

        return false;
    }

    return true;
}

bool SystemDatabase::remove(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `system` WHERE `id`=?");
    query.bindValue(0, id);

    if (!query.exec()) {
        #ifdef QT_DEBUG
            qDebug() << "removeSystem - Not executed";
            qDebug() << query.lastError().text();
        #endif

        return false;
    }

    return true;
}

bool SystemDatabase::change(int id, QString newName)
{
    QSqlQuery query;

    query.prepare("UPDATE `system` SET `name`=? WHERE `id`=?");
    query.bindValue(0, newName);
    query.bindValue(1, id);

    if (!query.exec()) {
        #ifdef QT_DEBUG
            qDebug() << "changeSystem - Not executed";
            qDebug() << query.lastError().text();
        #endif

        return false;
    }

    return true;
}
