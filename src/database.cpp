#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
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

QList<QMap<QString, QVariant>> Database::selectSystems()
{
    QList<QMap<QString, QVariant>> list;
    QSqlQuery query;

    if (query.exec("SELECT * FROM `system`")) {
        while (query.next()) {
            QMap<QString, QVariant> result;
            QSqlRecord record = query.record();

            for (int i = 0; i < record.count(); ++i) {
                result.insert(record.fieldName(i), record.value(i));
            }

            list.append(result);
        }
    } else {
        #ifdef QT_DEBUG
            QSqlError error = query.lastError();

            qDebug() << "Query not executed";
            qDebug() << error.text();
        #endif
    }

    return list;
}

bool Database::addSystem(QString name)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `system` (`name`) VALUES(?)");
    query.bindValue(0, name);

    if (!query.exec()) {
        #ifdef QT_DEBUG
            qDebug() << "addSystem - Not executed";
            qDebug() << query.lastError().text();
        #endif

        return false;
    }

    return true;
}

bool Database::removeSystem(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `system` WHERE `id`=?");
    query.bindValue(0, id);

    if (!query.exec()) {
        #ifdef QT_DEBUG
            qDebug() << "removeSystem - Not executed";
            qDebug() << query.lastError().text();
        #endif

        return false;
    }

    return true;
}

bool Database::changeSystem(int id, QString newName)
{
    QSqlQuery query;

    query.prepare("UPDATE `system` SET `name`=? WHERE `id`=?");
    query.bindValue(0, newName);
    query.bindValue(1, id);

    if (!query.exec()) {
        #ifdef QT_DEBUG
            qDebug() << "changeSystem - Not executed";
            qDebug() << query.lastError().text();
        #endif

        return false;
    }

    return true;
}
