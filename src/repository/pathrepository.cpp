#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "pathrepository.h"

PathRepository::PathRepository(QSqlDatabase *database)
{
    m_database = database;
}

QList<PathEntity> PathRepository::find()
{
    QList<PathEntity> list;
    QSqlQuery query;

    if (query.exec("SELECT"
                   "`path_trade`.`id` AS `id`,"
                   "`station`.`id` AS `station_id`,"
                   "`station`.`name` AS `station_name`,"
                   "`system`.`id` AS `system_id`,"
                   "`system`.`name` AS `system_name`,"
                   "`product`.`id` AS `product_id`,"
                   "`product`.`name` AS `product_name`,"
                   "`product_category`.`id` AS `cat_id`,"
                   "`product_category`.`name` AS `cat_name`,"
                   "`path_trade`.`profit` AS `profit`,"
                   "`path_trade`.`quantity` AS `quantity`,"
                   "`path_trade`.`date` AS `date`"
                   "FROM `path_trade`"
                   "LEFT JOIN `station` ON `station`.`id` = `path_trade`.`station`"
                   "LEFT JOIN `system` ON `system`.`id` = `station`.`system`"
                   "LEFT JOIN `product` ON `product`.id = `path_trade`.`product`"
                   "LEFT JOIN `product_category` ON `product_category`.`id` = `product`.`category`")) {
        while (query.next()) {
            SystemEntity system;
            StationEntity station;
            ProductCatEntity cat;
            ProductEntity product;
            PathEntity path;

            system.setId(query.value("system_id").toUInt());
            system.setName(query.value("system_name").toString());

            station.setId(query.value("id").toUInt());
            station.setSystem(system);
            station.setName(query.value("station_name").toString());

            cat.setId(query.value("cat_id").toUInt());
            cat.setName(query.value("cat_name").toString());

            product.setId(query.value("product_id").toUInt());
            product.setCat(cat);
            product.setName(query.value("product_name").toString());

            path.setId(query.value("id").toUInt());
            path.setDate(query.value("date").toString());
            path.setProduct(product);
            path.setStation(station);
            path.setQuantity(query.value("quantity").toUInt());
            path.setProfit(query.value("profit").toUInt());

            list.append(path);
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

PathEntity PathRepository::findOne(unsigned int id)
{
    QSqlQuery query;
    SystemEntity system;
    StationEntity station;
    ProductCatEntity cat;
    ProductEntity product;
    PathEntity path;

    query.prepare("SELECT"
                  "`path_trade`.`id` AS `id`,"
                  "`station`.`id` AS `station_id`,"
                  "`station`.`name` AS `station_name`,"
                  "`system`.`id` AS `system_id`,"
                  "`system`.`name` AS `system_name`,"
                  "`product`.`id` AS `product_id`,"
                  "`product`.`name` AS `product_name`,"
                  "`product_category`.`id` AS `cat_id`,"
                  "`product_category`.`name` AS `cat_name`,"
                  "`path_trade`.`profit` AS `profit`,"
                  "`path_trade`.`quantity` AS `quantity`,"
                  "`path_trade`.`date` AS `date`"
                  "FROM `path_trade`"
                  "LEFT JOIN `station` ON `station`.`id` = `path_trade`.`station`"
                  "LEFT JOIN `system` ON `system`.`id` = `station`.`system`"
                  "LEFT JOIN `product` ON `product`.id = `path_trade`.`product`"
                  "LEFT JOIN `product_category` ON `product_category`.`id` = `product`.`category`"
                  "WHERE `path_trade`.`id`=?");
    query.bindValue(0, id);

    if (query.exec()) {
        query.next();

        system.setId(query.value("system_id").toUInt());
        system.setName(query.value("system_name").toString());

        station.setId(query.value("id").toUInt());
        station.setSystem(system);
        station.setName(query.value("station_name").toString());

        cat.setId(query.value("cat_id").toUInt());
        cat.setName(query.value("cat_name").toString());

        product.setId(query.value("product_id").toUInt());
        product.setCat(cat);
        product.setName(query.value("product_name").toString());

        path.setId(query.value("id").toUInt());
        path.setDate(query.value("date").toString());
        path.setProduct(product);
        path.setStation(station);
        path.setQuantity(query.value("quantity").toUInt());
        path.setProfit(query.value("profit").toUInt());
    } else {
        #ifdef QT_DEBUG
            QSqlError error = query.lastError();

            qDebug() << "Query not executed";
            qDebug() << error.text();
        #endif
    }

    return path;
}

bool PathRepository::persist(const PathEntity &entity)
{
    if (entity.getId() > 0) {
        return update(entity);
    } else {
        return save(entity);
    }
}

bool PathRepository::remove(const PathEntity &entity)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `path_trade` WHERE `id`=?");
    query.bindValue(0, entity.getId());

    return this->exec(query, "PathRepository - Remove");
}

bool PathRepository::exec(QSqlQuery query, QString debugMethod)
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

bool PathRepository::save(const PathEntity &entity)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `path_trade` (`station`, `product`, `profit`, `quantity`, `date`) VALUES(?, ?, ?, ?, ?)");
    query.bindValue(0, entity.getStation().getId());
    query.bindValue(1, entity.getProduct().getId());
    query.bindValue(2, entity.getProfit());
    query.bindValue(3, entity.getQuantity());
    query.bindValue(4, entity.getDate());

    return this->exec(query, "PathRepository - Save");
}

bool PathRepository::update(const PathEntity &entity)
{
    QSqlQuery query;

    query.prepare("UPDATE `path_trade` SET `station`=?, `product`=?, `profit`=?, `quantity`=?, `date`=? WHERE `id`=?");
    query.bindValue(0, entity.getStation().getId());
    query.bindValue(1, entity.getProduct().getId());
    query.bindValue(2, entity.getProfit());
    query.bindValue(3, entity.getQuantity());
    query.bindValue(4, entity.getDate());
    query.bindValue(5, entity.getId());

    return this->exec(query, "PathRepository - Update");
}
