#ifndef PRODUCTDATABASE_H
#define PRODUCTDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <QStringList>
#include <QMap>
#include <QString>
#include <QVariant>

#ifdef QT_DEBUG
    #include <QDebug>
#endif

class ProductDatabase
{
    public:
        ProductDatabase(QSqlDatabase *database);
        QList<QMap<QString, QVariant>> select();
        bool add(int catId, QString name);
        bool remove(int id);
        bool change(int id, int catId, QString name);
        bool exec(QSqlQuery query, QString debugMethod);

    private:
        QSqlDatabase *m_database;
};

#endif // PRODUCTDATABASE_H
