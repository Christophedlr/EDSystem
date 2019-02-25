#include "stationentity.h"

SystemEntity StationEntity::getSystem() const
{
    return m_system;
}

void StationEntity::setSystem(const SystemEntity &system)
{
    m_system = system;
}

QString StationEntity::getName() const
{
    return m_name;
}

void StationEntity::setName(const QString &name)
{
    m_name = name;
}
