#ifndef PATHREPOSITORY_H
#define PATHREPOSITORY_H

#include <QSqlDatabase>
#include "../entity/pathentity.h"

class PathRepository
{
    public:
        PathRepository(QSqlDatabase *database);
        QList<PathEntity> find();
        PathEntity findOne(unsigned int id);
        bool persist(const PathEntity &entity);
        bool remove(const PathEntity &entity);

    private:
        QSqlDatabase *m_database;
        bool exec(QSqlQuery query, QString debugMethod);
        bool save(const PathEntity &entity);
        bool update(const PathEntity &entity);
};

#endif // PATHREPOSITORY_H
