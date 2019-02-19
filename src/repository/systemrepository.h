#ifndef SYSTEMREPOSITORY_H
#define SYSTEMREPOSITORY_H

#include <QList>
#include <QSqlDatabase>
#include "../entity/systementity.h"

class SystemRepository
{
    public:
        SystemRepository(QSqlDatabase *database);
        QList<SystemEntity> find();
        bool persist(const SystemEntity &entity);
        bool remove(const SystemEntity &entity);
        bool exec(QSqlQuery query, QString debugMethod);

    private:
        QSqlDatabase *m_database;
        bool save(const SystemEntity &entity);
        bool update(const SystemEntity &entity);
};

#endif // SYSTEMREPOSITORY_H
