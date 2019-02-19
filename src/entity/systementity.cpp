#include "systementity.h"

SystemEntity::SystemEntity()
{

}

QString SystemEntity::getName() const
{
    return m_name;
}

void SystemEntity::setName(const QString name)
{
    m_name = name;
}
