#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
    public:
        Entity();
        unsigned int getId() const;
        void setId(unsigned int id);

    private:
            unsigned int m_id;
};

#endif // ENTITY_H
