#ifndef SYSTEMENTITY_H
#define SYSTEMENTITY_H

#include <QString>
#include "../model/entity.h"

class SystemEntity : public Entity
{
    public:
        SystemEntity();

        QString getName() const;
        void setName(const QString name);

private:
        QString m_name;
};

#endif // SYSTEMENTITY_H
