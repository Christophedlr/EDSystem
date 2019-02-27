#include <QInputDialog>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "productcat.h"
#include "ui_productcat.h"
#include "repository/productcatrepository.h"

ProductCat::ProductCat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductCat)
{
    ui->setupUi(this);
    this->refreshTable();
}

ProductCat::~ProductCat()
{
    delete ui;
}

void ProductCat::refreshTable()
{
    QList<ProductCatEntity> list;
    ProductCatRepository repos(m_database.getDb());

    list = repos.find();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < list.count(); ++i) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-2, new QTableWidgetItem(QString::number(list.value(i).getId())));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-1, new QTableWidgetItem(list.value(i).getName()));
    }
}

void ProductCat::on_addButton_clicked()
{
    QString name = QInputDialog::getText(this, "Ajout", "Nom de la catégorie :");

    if (!name.isEmpty())
    {
        ProductCatEntity entity;
        ProductCatRepository repos(m_database.getDb());

        entity.setName(name);

        if (repos.persist(entity)) {
            QMessageBox::information(this,
                        "Ajout",
                        "La ligne a bien été ajoutée dans la table"
                        );
            this->refreshTable();
        }
    }
}

void ProductCat::on_changeButton_clicked()
{
    QString name = QInputDialog::getText(this, "Modification", "Nom de la catégorie :");

    if (!name.isEmpty())
    {
        ProductCatEntity entity;
        ProductCatRepository repos(m_database.getDb());

        entity.setId(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt());
        entity.setName(name);

        if (repos.persist(entity)) {
            QMessageBox::information(this,
                        "Modification",
                        "La ligne a bien été modifiée dans la table"
                        );
            this->refreshTable();
        }
    }
}

void ProductCat::on_removeButton_clicked()
{
    QString question = QString("Supprimer la ligne %1 ?").arg(ui->tableWidget->currentRow()+1);

    if (QMessageBox::question(
                0,
                "Confirmation de suppression",
                question,
                QMessageBox::Yes|QMessageBox::No
                ) == QMessageBox::Yes) {
        ProductCatEntity entity;
        ProductCatRepository repos(m_database.getDb());

        entity.setId(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt());

        if (repos.remove(entity)) {
            QMessageBox::information(this,
                        "Suppression",
                        "La ligne a bien été supprimée de la table"
                        );
            this->refreshTable();
        }
    }
}
