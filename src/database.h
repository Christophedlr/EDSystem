#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSettings>
#include "model/systemdatabase.h"
#include "model/stationdatabase.h"
#include "model/productcatdatabase.h"
#include "model/productdatabase.h"

#ifdef QT_DEBUG
    #include <QDebug>
#endif

class Database
{
    public:
        Database();
        ~Database();
        QSqlDatabase* getDb();
        SystemDatabase* system();
        StationDatabase* station();
        ProductCatDatabase* productCat();
        ProductDatabase* product();

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
