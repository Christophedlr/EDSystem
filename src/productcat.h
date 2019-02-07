#ifndef PRODUCTCAT_H
#define PRODUCTCAT_H

#include <QWidget>
#include "database.h"

namespace Ui {
class ProductCat;
}

class ProductCat : public QWidget
{
    Q_OBJECT

public:
    explicit ProductCat(QWidget *parent = 0);
    ~ProductCat();

private slots:
    void on_addButton_clicked();
    void on_changeButton_clicked();
    void on_removeButton_clicked();

private:
    Ui::ProductCat *ui;
    Database m_database;
    void refreshTable();
};

#endif // PRODUCTCAT_H
