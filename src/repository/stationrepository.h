#ifndef STATIONREPOSITORY_H
#define STATIONREPOSITORY_H

#include <QList>
#include <QSqlDatabase>
#include "../entity/stationentity.h"

class StationRepository
{
    public:
        StationRepository(QSqlDatabase *database);
        QList<StationEntity> find();
        bool persist(const StationEntity &entity);

    private:
        QSqlDatabase *m_database;
        bool exec(QSqlQuery query, QString debugMethod);
        bool save(const StationEntity &entity);
        bool update(const StationEntity &entity);
};

#endif // STATIONREPOSITORY_H
