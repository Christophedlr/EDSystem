#ifndef PRODUCTCATENTITY_H
#define PRODUCTCATENTITY_H

#include <QString>
#include "../model/entity.h"

class ProductCatEntity : public Entity
{
    public:
    QString getName() const;
    void setName(const QString &name);

private:
    QString m_name;
};

#endif // PRODUCTCATENTITY_H
