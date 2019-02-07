#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_initialConfigButton_clicked();
    void on_systemsButton_clicked();
    void on_StationsButton_clicked();
    void on_productCatButton_clicked();
    void on_productButton_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
