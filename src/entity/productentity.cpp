#include "productentity.h"

ProductCatEntity ProductEntity::getCat() const
{
    return m_cat;
}

void ProductEntity::setCat(const ProductCatEntity &cat)
{
    m_cat = cat;
}

QString ProductEntity::getName() const
{
    return m_name;
}

void ProductEntity::setName(const QString &name)
{
    m_name = name;
}
