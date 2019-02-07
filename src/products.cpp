#include <QInputDialog>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "products.h"
#include "ui_products.h"
#include "dialog/productdialog.h"

Products::Products(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Products)
{
    ui->setupUi(this);
    this->refreshTable();
}

Products::~Products()
{
    delete ui;
}

void Products::refreshTable()
{
    QList<QMap<QString, QVariant>> list;
    list = m_database.product()->select();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < list.count(); ++i) {
        QMap<QString, QVariant> result;

        result = list.at(i);
        for (int x = 0; x < result.count()-2; ++x) {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-3, new QTableWidgetItem(result.value("id").toString()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-2, new QTableWidgetItem(result.value("category").toString()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-1, new QTableWidgetItem(result.value("name").toString()));
        }
    }
}

void Products::on_addButton_clicked()
{
    ProductDialog *dialog = new ProductDialog();

    dialog->setCategoryList(m_database.productCat()->selectNames());
    dialog->exec();

    if (dialog->Accepted) {
        if (m_database.product()->add(m_database.productCat()->findByName(dialog->category()), dialog->product())) {
            QMessageBox::information(this,
                        "Ajout",
                        "La ligne a bien été ajoutée dans la table"
                        );
            this->refreshTable();
        }
    }
}

void Products::on_changeButton_clicked()
{
    ProductDialog *dialog = new ProductDialog();

    dialog->setCategoryList(m_database.productCat()->selectNames());
    dialog->exec();

    if (dialog->Accepted) {
        if (m_database.product()->change(
                    ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt(),
                    m_database.productCat()->findByName(dialog->category()),
                    dialog->product()
                    )) {
            QMessageBox::information(this,
                        "Modification",
                        "La ligne a bien été modifiée dans la table"
                        );
            this->refreshTable();
        }
    }
}

void Products::on_removeButton_clicked()
{
    QString question = QString("Supprimer la ligne %1 ?").arg(ui->tableWidget->currentRow()+1);

    if (QMessageBox::question(
                0,
                "Confirmation de suppression",
                question,
                QMessageBox::Yes|QMessageBox::No
                ) == QMessageBox::Yes) {
        if (m_database.product()->remove(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt())) {
            QMessageBox::information(this,
                        "Suppression",
                        "La ligne a bien été supprimée de la table"
                        );
            this->refreshTable();
        }
    }
}
