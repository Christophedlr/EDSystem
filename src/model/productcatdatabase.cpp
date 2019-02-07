#include <QSqlError>
#include <QSqlRecord>
#include "productcatdatabase.h"

ProductCatDatabase::ProductCatDatabase(QSqlDatabase *database)
{
    m_database = database;
}

QList<QMap<QString, QVariant> > ProductCatDatabase::select()
{
    QList<QMap<QString, QVariant>> list;
    QSqlQuery query;

    if (query.exec("SELECT `id`, `name` FROM `product_category`")) {
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

bool ProductCatDatabase::add(QString name)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `product_category` (`name`) VALUES(?)");
    query.bindValue(0, name);

    return this->exec(query, "addProductCat");
}

bool ProductCatDatabase::remove(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `product_category` WHERE `id`=?");
    query.bindValue(0, id);

    return this->exec(query, "removeProductCat");
}

bool ProductCatDatabase::change(int id, QString newName)
{
    QSqlQuery query;

    query.prepare("UPDATE `product_category` SET `name`=? WHERE `id`=?");
    query.bindValue(0, newName);
    query.bindValue(1, id);

    return this->exec(query, "changeProductCat");
}

int ProductCatDatabase::findByName(QString name)
{
    QSqlQuery query;

    query.prepare("SELECT `product_category`.`id` FROM `product_category` WHERE `name`=?");
    query.bindValue(0, name);

    if (query.exec()) {
        query.next();
        return query.value("id").toInt();
    } else {
        #ifdef QT_DEBUG
            QSqlError error = query.lastError();

            qDebug() << "Query not executed";
            qDebug() << error.text();
        #endif
    }

    return -1;
}

bool ProductCatDatabase::exec(QSqlQuery query, QString debugMethod)
{
    if (!query.exec()) {
        #ifdef QT_DEBUG
            qDebug() << debugMethod << " - Not executed";
            qDebug() << query.lastError().text();
        #endif

        return false;
    }

    return true;
}
