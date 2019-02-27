#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "productcatrepository.h"

ProductCatRepository::ProductCatRepository(QSqlDatabase *database)
{
    m_database = database;
}

QList<ProductCatEntity> ProductCatRepository::find()
{
    QList<ProductCatEntity> list;
    QSqlQuery query;

    if (query.exec("SELECT * FROM `product_category`")) {
        while (query.next()) {
            ProductCatEntity entity;

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

ProductCatEntity ProductCatRepository::findOneByName(QString name)
{
    ProductCatEntity entity;
    QSqlQuery query;

    query.prepare("SELECT * FROM `product_category` WHERE `name` = ?");
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

QStringList ProductCatRepository::findNamesOnly()
{
    QSqlQuery query;
    QStringList list;

    if (query.exec("SELECT `name` FROM `product_category`")) {
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

bool ProductCatRepository::persist(const ProductCatEntity &entity)
{
    if (entity.getId() > 0) {
        return update(entity);
    } else {
        return save(entity);
    }
}

bool ProductCatRepository::remove(const ProductCatEntity &entity)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `product_category` WHERE `id`=?");
    query.bindValue(0, entity.getId());

    return this->exec(query, "ProductCatRepository - Remove");
}

bool ProductCatRepository::exec(QSqlQuery query, QString debugMethod)
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

bool ProductCatRepository::save(const ProductCatEntity &entity)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `product_category` (`name`) VALUES(?)");
    query.bindValue(0, entity.getName());

    return this->exec(query, "ProductCatRepository - Save");
}

bool ProductCatRepository::update(const ProductCatEntity &entity)
{
    QSqlQuery query;

    query.prepare("UPDATE `product_category` SET `name`=? WHERE `id`=?");
    query.bindValue(0, entity.getName());
    query.bindValue(1, entity.getId());

    return this->exec(query, "ProductCatRepository - Update");
}
