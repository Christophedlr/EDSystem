#ifndef SYSTEMDATABASE_H
#define SYSTEMDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include <QMap>
#include <QString>
#include <QVariant>

#ifdef QT_DEBUG
    #include <QDebug>
#endif

class SystemDatabase
{
    public:
        SystemDatabase(QSqlDatabase *database);
        ~SystemDatabase();
        QList<QMap<QString, QVariant>> select();
        bool add(QString name);
        bool remove(int id);
        bool change(int id, QString newName);
        bool exec(QSqlQuery query, QString debugMethod);

    private:
        QSqlDatabase *m_database;
};

#endif // SYSTEMDATABASE_H
