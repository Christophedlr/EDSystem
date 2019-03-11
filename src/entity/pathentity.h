#ifndef PATHENTITY_H
#define PATHENTITY_H

#include "../model/entity.h"
#include "stationentity.h"
#include "productentity.h"

class PathEntity : public Entity
{
    public:
        PathEntity();

        StationEntity getStation() const;
        void setStation(const StationEntity &station);

        ProductEntity getProduct() const;
        void setProduct(const ProductEntity &product);

        unsigned int getProfit() const;
        void setProfit(unsigned int profit);

        unsigned int getQuantity() const;
        void setQuantity(unsigned int quantity);

        QString getDate() const;
        void setDate(const QString &date);

private:
        StationEntity m_station;
        ProductEntity m_product;
        unsigned int m_profit;
        unsigned int m_quantity;
        QString m_date;
};

#endif // PATHENTITY_H
