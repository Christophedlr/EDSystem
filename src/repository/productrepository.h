#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H

#include <QList>
#include <QSqlDatabase>
#include "../entity/productentity.h"

class ProductRepository
{
    public:
        ProductRepository(QSqlDatabase *database);
        QList<ProductEntity> find();
        ProductEntity findOne(unsigned int id);
        ProductEntity findOneByName(QString name);
        QStringList findNamesOnly();
        QStringList findNamesByCat(const QString name);
        bool persist(const ProductEntity &entity);
        bool remove(const ProductEntity &entity);

    private:
        QSqlDatabase *m_database;
        bool exec(QSqlQuery query, QString debugMethod);
        bool save(const ProductEntity &entity);
        bool update(const ProductEntity &entity);
};

#endif // PRODUCTREPOSITORY_H
