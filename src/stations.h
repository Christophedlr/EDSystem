#ifndef STATIONS_H
#define STATIONS_H

#include <QWidget>
#include "database.h"

namespace Ui {
class Stations;
}

class Stations : public QWidget
{
    Q_OBJECT

public:
    explicit Stations(QWidget *parent = 0);
    ~Stations();

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_changeButton_clicked();

private:
    Ui::Stations *ui;
    Database m_database;
    void refreshTable();
};

#endif // STATIONS_H
