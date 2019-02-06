#ifndef STATIONDATABASE_H
#define STATIONDATABASE_H

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

class StationDatabase
{
    public:
        StationDatabase(QSqlDatabase *database);
        QList<QMap<QString, QVariant>> select();
        bool add(int systemId, QString name);
        bool remove(int id);
        bool change(int id, int systemId, QString name);
        bool exec(QSqlQuery query, QString debugMethod);

    private:
        QSqlDatabase *m_database;
};

#endif // STATIONDATABASE_H
