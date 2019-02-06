#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSettings>
#include "model/systemdatabase.h"
#include "model/stationdatabase.h"

#ifdef QT_DEBUG
    #include <QDebug>
#endif

class Database
{
    public:
        Database();
        ~Database();
        SystemDatabase* system();
        StationDatabase* station();

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
