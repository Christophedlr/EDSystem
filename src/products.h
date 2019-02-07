#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <QWidget>
#include "database.h"

namespace Ui {
class Products;
}

class Products : public QWidget
{
    Q_OBJECT

public:
    explicit Products(QWidget *parent = 0);
    ~Products();

private slots:
    void on_addButton_clicked();
    void on_changeButton_clicked();
    void on_removeButton_clicked();

private:
    Ui::Products *ui;
    Database m_database;
    void refreshTable();
};

#endif // PRODUCTS_H
