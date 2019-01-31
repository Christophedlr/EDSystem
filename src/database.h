#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSettings>
#include <QList>
#include <QMap>
#include <QString>
#include <QVariant>

#ifdef QT_DEBUG
    #include <QDebug>
#endif

class Database
{
    public:
        Database();
        ~Database();
        QList<QMap<QString, QVariant>> selectSystems();
        bool addSystem(QString name);
        bool removeSystem(int id);
        bool changeSystem(int id, QString newName);

    private:
        QSqlDatabase *m_database;
        QString m_host = "localhost";
        QString m_dbname;
        QString m_username;
        QString m_password;
        int m_port = 3306;
        bool m_initialized = false;
};

#endif // DATABASE_H
