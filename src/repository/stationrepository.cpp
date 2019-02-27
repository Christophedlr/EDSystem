#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "stationrepository.h"

StationRepository::StationRepository(QSqlDatabase *database)
{
    m_database = database;
}

QList<StationEntity> StationRepository::find()
{
    QList<StationEntity> list;
    QSqlQuery query;

    if (query.exec("SELECT `station`.`id` AS `id`, `system`.`id` AS `system_id`,"
                   "`system`.`name` AS `system_name`,`station`.`name` AS `name`"
                   "FROM `station` LEFT JOIN `system` ON `system`.`id` = `station`.`system`")) {
        while (query.next()) {
            SystemEntity system;
            StationEntity station;

            system.setId(query.value("system_id").toUInt());
            system.setName(query.value("system_name").toString());

            station.setId(query.value("id").toUInt());
            station.setSystem(system);
            station.setName(query.value("name").toString());

            list.append(station);
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

StationEntity StationRepository::findOneByName(QString name)
{
    QSqlQuery query;
    SystemEntity system;
    StationEntity station;

    query.prepare("SELECT `station`.`id` AS `id`, `system`.`id` AS `system_id`,"
                  "`system`.`name` AS `system_name`,`station`.`name` AS `name`"
                  "FROM `station` LEFT JOIN `system` ON `system`.`id` = `station`.`system`"
                  "WHERE `station`.`name` = ?");
    query.bindValue(0, name);

    if (query.exec()) {
        query.next();

        system.setId(query.value("system_id").toUInt());
        system.setName(query.value("system_name").toString());

        station.setId(query.value("id").toUInt());
        station.setName(query.value("name").toString());
        station.setSystem(system);
    } else {
        #ifdef QT_DEBUG
            QSqlError error = query.lastError();

            qDebug() << "Query not executed";
            qDebug() << error.text();
        #endif
    }

    return station;
}

bool StationRepository::persist(const StationEntity &entity)
{
    if (entity.getId() > 0) {
        return update(entity);
    } else {
        return save(entity);
    }
}

bool StationRepository::remove(const StationEntity &entity)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `station` WHERE `id`=?");
    query.bindValue(0, entity.getId());

    return this->exec(query, "StationRepository - Remove");
}

bool StationRepository::exec(QSqlQuery query, QString debugMethod)
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

bool StationRepository::save(const StationEntity &entity)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `station` (`system`, `name`) VALUES(?, ?)");
    query.bindValue(0, entity.getSystem().getId());
    query.bindValue(1, entity.getName());

    return this->exec(query, "StationRepository - Save");
}

bool StationRepository::update(const StationEntity &entity)
{
    QSqlQuery query;

    query.prepare("UPDATE `station` SET `system`=?, `name`=? WHERE `id`=?");
    query.bindValue(0, entity.getSystem().getId());
    query.bindValue(1, entity.getName());
    query.bindValue(2, entity.getId());

    return this->exec(query, "StationRepository - Update");
}
