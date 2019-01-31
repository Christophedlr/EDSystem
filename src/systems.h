#ifndef SYSTEMS_H
#define SYSTEMS_H

#include <QWidget>
#include "database.h"

namespace Ui {
class Systems;
}

class Systems : public QWidget
{
    Q_OBJECT

public:
    explicit Systems(QWidget *parent = 0);
    ~Systems();

private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_changeButton_clicked();

private:
    Ui::Systems *ui;
    Database m_database;
    void refreshTable();
};

#endif // SYSTEMS_H
