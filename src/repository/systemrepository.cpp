#include <QSqlError>
//#include <QSqlRecord>
#include <QSqlQuery>
#include <QDebug>
#include "systemrepository.h"

SystemRepository::SystemRepository(QSqlDatabase *database)
{
    m_database = database;
}

QList<SystemEntity> SystemRepository::find()
{
    QList<SystemEntity> list;
    QSqlQuery query;

    if (query.exec("SELECT * FROM `system`")) {
        while (query.next()) {
            SystemEntity entity;

            entity.setId(query.value("id").toUInt());
            entity.setName(query.value("name").toString());

            list.append(entity);
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

SystemEntity SystemRepository::findOneByName(QString name)
{
    SystemEntity entity;
    QSqlQuery query;

    query.prepare("SELECT * FROM `system` WHERE `name` = ?");
    query.bindValue(0, name);

    if (query.exec()) {
        query.next();
        entity.setId(query.value("id").toUInt());
        entity.setName(query.value("name").toString());
    } else {
        #ifdef QT_DEBUG
            QSqlError error = query.lastError();

            qDebug() << "Query not executed";
            qDebug() << error.text();
        #endif
    }

    return entity;
}

QStringList SystemRepository::findNamesOnly()
{
    QSqlQuery query;
    QStringList list;

    if (query.exec("SELECT `name` FROM `system`")) {
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

bool SystemRepository::persist(const SystemEntity &entity)
{
    if (entity.getId() > 0) {
        return update(entity);
    } else {
        return save(entity);
    }
}

bool SystemRepository::remove(const SystemEntity &entity)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `system` WHERE `id`=?");
    query.bindValue(0, entity.getId());

    return this->exec(query, "SystemRepository - Remove");
}

bool SystemRepository::exec(QSqlQuery query, QString debugMethod)
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

bool SystemRepository::save(const SystemEntity &entity)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `system` (`name`) VALUES(?)");
    query.bindValue(0, entity.getName());

    return this->exec(query, "SystemRepository - Save");
}

bool SystemRepository::update(const SystemEntity &entity)
{
    QSqlQuery query;

    query.prepare("UPDATE `system` SET `name`=? WHERE `id`=?");
    query.bindValue(0, entity.getName());
    query.bindValue(1, entity.getId());

    return this->exec(query, "SystemRepository - Update");
}
