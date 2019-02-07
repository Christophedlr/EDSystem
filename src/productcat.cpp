#include <QInputDialog>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "productcat.h"
#include "ui_productcat.h"

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
    QList<QMap<QString, QVariant>> list;
    list = m_database.productCat()->select();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < list.count(); ++i) {
        QMap<QString, QVariant> result;

        result = list.at(i);
        for (int x = 0; x < result.count()-1; ++x) {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-2, new QTableWidgetItem(result.value("id").toString()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-1, new QTableWidgetItem(result.value("name").toString()));
        }
    }
}

void ProductCat::on_addButton_clicked()
{
    QString name = QInputDialog::getText(this, "Ajout", "Nom de la catégorie :");

    if (!name.isEmpty())
    {
        if (m_database.productCat()->add(name)) {
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
        if (m_database.productCat()->change(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt(), name)) {
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
        if (m_database.productCat()->remove(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt())) {
            QMessageBox::information(this,
                        "Suppression",
                        "La ligne a bien été supprimée de la table"
                        );
            this->refreshTable();
        }
    }
}
