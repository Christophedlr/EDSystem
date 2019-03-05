#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "productrepository.h"

ProductRepository::ProductRepository(QSqlDatabase *database)
{
    m_database = database;
}

QList<ProductEntity> ProductRepository::find()
{
    QList<ProductEntity> list;
    QSqlQuery query;

    if (query.exec("SELECT `product`.`id` AS `id`, `product_category`.`id` AS `cat_id`,"
                   "`product_category`.`name` AS `cat_name`,`product`.`name` AS `name`"
                   "FROM `product` LEFT JOIN `product_category` ON `product_category`.`id` = `product`.`category`")) {
        while (query.next()) {
            ProductCatEntity cat;
            ProductEntity product;

            cat.setId(query.value("cat_id").toUInt());
            cat.setName(query.value("cat_name").toString());

            product.setId(query.value("id").toUInt());
            product.setCat(cat);
            product.setName(query.value("name").toString());

            list.append(product);
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

ProductEntity ProductRepository::findOneByName(QString name)
{
    QSqlQuery query;
    ProductCatEntity cat;
    ProductEntity product;

    query.prepare("SELECT `product`.`id` AS `id`, `product_category`.`id` AS `cat_id`,"
                  "`product_category`.`name` AS `cat_name`,`product`.`name` AS `name`"
                  "FROM `product` LEFT JOIN `product_category` ON `product_category`.`id` = `product`.`category`"
                  "WHERE `product`.`name` = ?");
    query.bindValue(0, name);

    if (query.exec()) {
        query.next();

        cat.setId(query.value("cat_id").toUInt());
        cat.setName(query.value("cat_name").toString());

        product.setId(query.value("id").toUInt());
        product.setName(query.value("name").toString());
        product.setCat(cat);
    } else {
        #ifdef QT_DEBUG
            QSqlError error = query.lastError();

            qDebug() << "Query not executed";
            qDebug() << error.text();
        #endif
    }

    return product;
}

QStringList ProductRepository::findNamesOnly()
{
    QSqlQuery query;
    QStringList list;

    if (query.exec("SELECT `name` FROM `product`")) {
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

bool ProductRepository::persist(const ProductEntity &entity)
{
    if (entity.getId() > 0) {
        return update(entity);
    } else {
        return save(entity);
    }
}

bool ProductRepository::remove(const ProductEntity &entity)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `product` WHERE `id`=?");
    query.bindValue(0, entity.getId());

    return this->exec(query, "ProductRepository - Remove");
}

bool ProductRepository::exec(QSqlQuery query, QString debugMethod)
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

bool ProductRepository::save(const ProductEntity &entity)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `product` (`category`, `name`) VALUES(?, ?)");
    query.bindValue(0, entity.getCat().getId());
    query.bindValue(1, entity.getName());

    return this->exec(query, "ProductRepository - Save");
}

bool ProductRepository::update(const ProductEntity &entity)
{
    QSqlQuery query;

    query.prepare("UPDATE `product` SET `category`=?, `name`=? WHERE `id`=?");
    query.bindValue(0, entity.getCat().getId());
    query.bindValue(1, entity.getName());
    query.bindValue(2, entity.getId());

    return this->exec(query, "ProductRepository - Update");
}
