#ifndef PRODUCTCATREPOSITORY_H
#define PRODUCTCATREPOSITORY_H

#include <QList>
#include <QStringList>
#include <QSqlDatabase>
#include "../entity/productcatentity.h"

class ProductCatRepository
{
    public:
        ProductCatRepository(QSqlDatabase *database);
        QList<ProductCatEntity> find();
        ProductCatEntity findOneByName(QString name);
        QStringList findNamesOnly();
        bool persist(const ProductCatEntity &entity);
        bool remove(const ProductCatEntity &entity);


    private:
        QSqlDatabase *m_database;
        bool exec(QSqlQuery query, QString debugMethod);
        bool save(const ProductCatEntity &entity);
        bool update(const ProductCatEntity &entity);
};

#endif // PRODUCTCATREPOSITORY_H
