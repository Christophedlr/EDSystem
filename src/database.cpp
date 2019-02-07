#include <QSqlError>
#include "database.h"

Database::Database()
{
    QSettings settings("Christophedlr", "EDSystem");

    m_host = settings.value("host").toString();
    m_port = settings.value("port").toInt();
    m_username = settings.value("username").toString();
    m_password = settings.value("password").toString();
    m_dbname = settings.value("dbname").toString();

    m_database = new QSqlDatabase(QSqlDatabase::addDatabase("QMYSQL"));
    m_database->setHostName(m_host);
    m_database->setDatabaseName(m_dbname);
    m_database->setUserName(m_username);
    m_database->setPassword(m_password);
    m_database->setPort(m_port);

    if (m_database->open()) {
        m_initialized = true;
    } else {
        #ifdef QT_DEBUG
            QSqlError error = m_database->lastError();

            qDebug() << "Impossible initialized database";
            qDebug() << error.text();
        #endif
    }
}

Database::~Database()
{
    delete m_database;
}

SystemDatabase* Database::system()
{
    return new SystemDatabase(m_database);
}

StationDatabase *Database::station()
{
    return new StationDatabase(m_database);
}

ProductCatDatabase *Database::productCat()
{
    return new ProductCatDatabase(m_database);
}

ProductDatabase *Database::product()
{
    return new ProductDatabase(m_database);
}
