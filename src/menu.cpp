#include "menu.h"
#include "ui_menu.h"
#include "configuration/firstconfig.h"
#include "systems.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_initialConfigButton_clicked()
{
    FirstConfig *config = new FirstConfig();
    config->show();
}

void Menu::on_systemsButton_clicked()
{
    Systems *systems = new Systems();
    systems->show();
}
