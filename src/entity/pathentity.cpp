#include <QDateTime>
#include "pathentity.h"

PathEntity::PathEntity()
{

}

StationEntity PathEntity::getStation() const
{
    return m_station;
}

void PathEntity::setStation(const StationEntity &station)
{
    m_station = station;
}

ProductEntity PathEntity::getProduct() const
{
    return m_product;
}

void PathEntity::setProduct(const ProductEntity &product)
{
    m_product = product;
}

unsigned int PathEntity::getProfit() const
{
    return m_profit;
}

void PathEntity::setProfit(unsigned int profit)
{
    m_profit = profit;
}

unsigned int PathEntity::getQuantity() const
{
    return m_quantity;
}

void PathEntity::setQuantity(unsigned int quantity)
{
    m_quantity = quantity;
}

QString PathEntity::getDate() const
{
    return m_date;
}

void PathEntity::setDate(const QString &date)
{
    QDateTime dateTime;
    QString dateString = date;
    dateString.replace(10, 1, " ");
    dateString.remove(19, 4);

    dateTime = QDateTime::fromString(dateString, "yyyy-MM-dd hh:mm:ss");
    m_date = dateTime.toString("yyyy-MM-dd hh:mm:ss");
}
