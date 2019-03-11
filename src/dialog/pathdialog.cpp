#include "pathdialog.h"
#include "ui_pathdialog.h"
#include "../repository/productcatrepository.h"
#include "../repository/productrepository.h"
#include "../repository/stationrepository.h"
#include "../repository/systemrepository.h"

PathDialog::PathDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PathDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
}

PathDialog::~PathDialog()
{
    delete ui;
}

void PathDialog::fill(QSqlDatabase *database)
{
    m_database = database;
    SystemRepository systemRepos(m_database);
    ProductCatRepository productCatRepos(m_database);

    ui->systemCBox->clear();
    ui->systemCBox->addItems(systemRepos.findNamesOnly());

    ui->catCBox->clear();
    ui->catCBox->addItems(productCatRepos.findNamesOnly());
}

QMap<QString, QVariant> PathDialog::getData()
{
    SystemRepository systemRepos(m_database);
    StationRepository stationRepos(m_database);
    ProductCatRepository productCatRepos(m_database);
    ProductRepository productRepos(m_database);

    QMap<QString, QVariant> map;

    map.insert("station", stationRepos.findOneByName(ui->stationCBox->currentText()).getId());
    map.insert("product", productRepos.findOneByName(ui->productCBox->currentText()).getId());
    map.insert("quantity", ui->quantitySBox->value());
    map.insert("profit", ui->profitSBox->value());
    map.insert("date", ui->dateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    return map;
}

void PathDialog::on_systemCBox_currentIndexChanged(const QString &arg1)
{
    StationRepository stationRepos(m_database);

    ui->stationCBox->clear();
    ui->stationCBox->addItems(stationRepos.findNamesBySystem(arg1));
}

void PathDialog::on_catCBox_currentIndexChanged(const QString &arg1)
{
    ProductRepository productRepos(m_database);

    ui->productCBox->clear();
    ui->productCBox->addItems(productRepos.findNamesByCat(arg1));
}
