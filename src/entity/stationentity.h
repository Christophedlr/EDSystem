#ifndef STATIONENTITY_H
#define STATIONENTITY_H

#include <QString>
#include "../entity/systementity.h"

class StationEntity : public Entity
{
    public:
        SystemEntity getSystem() const;
        void setSystem(const SystemEntity &system);

        QString getName() const;
        void setName(const QString &name);

private:
        SystemEntity m_system;
        QString m_name;
};

#endif // STATIONENTITY_H
