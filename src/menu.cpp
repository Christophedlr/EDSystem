#include "menu.h"
#include "ui_menu.h"
#include "configuration/firstconfig.h"
#include "systems.h"
#include "stations.h"
#include "productcat.h"
#include "products.h"
#include "paths.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "elite.ico"));
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

void Menu::on_StationsButton_clicked()
{
    Stations *stations = new Stations();
    stations->show();
}

void Menu::on_productCatButton_clicked()
{
    ProductCat *productCat = new ProductCat();
    productCat->show();
}

void Menu::on_productButton_clicked()
{
    Products *products = new Products();
    products->show();
}

void Menu::on_pathsButton_clicked()
{
    Paths *paths = new Paths();
    paths->show();
}
