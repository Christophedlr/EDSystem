#ifndef STATIONREPOSITORY_H
#define STATIONREPOSITORY_H

#include <QList>
#include <QSqlDatabase>
#include "../entity/productentity.h"

class ProductRepository
{
    public:
        ProductRepository(QSqlDatabase *database);
        QList<ProductEntity> find();
        ProductEntity findOneByName(QString name);
        bool persist(const ProductEntity &entity);
        bool remove(const ProductEntity &entity);

    private:
        QSqlDatabase *m_database;
        bool exec(QSqlQuery query, QString debugMethod);
        bool save(const ProductEntity &entity);
        bool update(const ProductEntity &entity);
};

#endif // STATIONREPOSITORY_H
