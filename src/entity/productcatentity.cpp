#include "productcatentity.h"

QString ProductCatEntity::getName() const
{
    return m_name;
}

void ProductCatEntity::setName(const QString &name)
{
    m_name = name;
}
