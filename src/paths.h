#ifndef PATHS_H
#define PATHS_H

#include <QWidget>
#include "database.h"

namespace Ui {
class Paths;
}

class Paths : public QWidget
{
    Q_OBJECT

    public:
        explicit Paths(QWidget *parent = 0);
        ~Paths();

    private slots:
        void on_addButton_clicked();
        void on_changeButton_clicked();
        void on_deleteButton_clicked();

private:
        Ui::Paths *ui;
        Database m_database;
        void refreshTable();
};

#endif // PATHS_H
