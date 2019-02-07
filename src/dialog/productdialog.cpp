#include "productdialog.h"
#include "ui_productdialog.h"

ProductDialog::ProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductDialog)
{
    ui->setupUi(this);
}

ProductDialog::~ProductDialog()
{
    delete ui;
}

QString ProductDialog::category()
{
    return ui->categoryCBox->currentText();
}

QString ProductDialog::product()
{
    return ui->productEdit->text();
}

void ProductDialog::setCategoryList(QStringList list)
{
    ui->categoryCBox->addItems(list);
}
