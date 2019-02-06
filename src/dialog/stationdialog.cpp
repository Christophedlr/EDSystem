#include "stationdialog.h"
#include "ui_stationdialog.h"

StationDialog::StationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StationDialog)
{
    ui->setupUi(this);
}

StationDialog::~StationDialog()
{
    delete ui;
}

QString StationDialog::system()
{
    return ui->systemCBox->currentText();
}

QString StationDialog::station()
{
    return ui->stationEdit->text();
}

void StationDialog::setSystemList(QStringList list)
{
    ui->systemCBox->addItems(list);
}
