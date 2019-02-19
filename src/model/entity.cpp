#include "entity.h"

Entity::Entity()
{
    m_id = 0;
}

unsigned int Entity::getId() const
{
    return m_id;
}

void Entity::setId(unsigned int id)
{
    m_id = id;
}
