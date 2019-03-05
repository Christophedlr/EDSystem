#ifndef PRODUCTENTITY_H
#define PRODUCTENTITY_H

#include <QString>
#include "../entity/productcatentity.h"

class ProductEntity : public Entity
{
    public:
        ProductCatEntity getCat() const;
        void setCat(const ProductCatEntity &system);

        QString getName() const;
        void setName(const QString &name);

private:
        ProductCatEntity m_cat;
        QString m_name;
};

#endif // PRODUCTENTITY_H
