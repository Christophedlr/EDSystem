#ifndef PRODUCTCATDATABASE_H
#define PRODUCTCATDATABASE_H

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

class ProductCatDatabase
{
    public:
        ProductCatDatabase(QSqlDatabase *database);
        QList<QMap<QString, QVariant>> select();
        bool add(QString name);
        bool remove(int id);
        bool change(int id, QString newName);
        int findByName(QString name);
        bool exec(QSqlQuery query, QString debugMethod);

    private:
        QSqlDatabase *m_database;
};

#endif // PRODUCTCATDATABASE_H
