#include <QSqlError>
#include <QSqlRecord>
#include "productdatabase.h"

ProductDatabase::ProductDatabase(QSqlDatabase *database)
{
    m_database = database;
}

QList<QMap<QString, QVariant> > ProductDatabase::select()
{
    QList<QMap<QString, QVariant>> list;
    QSqlQuery query;

    if (query.exec("SELECT `product`.`id`, `product_category`.`name` AS `category`, `product`.`name` FROM `product` LEFT JOIN `product_category` ON `product`.`category` = `product_category`.`id`")) {
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

bool ProductDatabase::add(int catId, QString name)
{
    QSqlQuery query;

    query.prepare("INSERT INTO `product` (`category`, `name`) VALUES(?, ?)");
    query.bindValue(0, catId);
    query.bindValue(1, name);

    return this->exec(query, "addProduct");
}

bool ProductDatabase::remove(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM `product` WHERE `id` = ?");
    query.bindValue(0, id);

    return this->exec(query, "removeProduct");
}

bool ProductDatabase::change(int id, int catId, QString name)
{
    QSqlQuery query;

    query.prepare("UPDATE `product` SET `name`=?, `category`=? WHERE `id`=?");
    query.bindValue(0, name);
    query.bindValue(1, catId);
    query.bindValue(2, id);

    return this->exec(query, "changeProduct");
}

bool ProductDatabase::exec(QSqlQuery query, QString debugMethod)
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
