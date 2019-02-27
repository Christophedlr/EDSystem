#include <QInputDialog>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "products.h"
#include "ui_products.h"
#include "dialog/productdialog.h"
#include "repository/productrepository.h"
#include "repository/productcatrepository.h"

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
    QList<ProductEntity> list;
    ProductRepository repos(m_database.getDb());

    list = repos.find();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < list.count(); ++i) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-3, new QTableWidgetItem(QString::number(list.value(i).getId())));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-2, new QTableWidgetItem(list.value(i).getCat().getName()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-1, new QTableWidgetItem(list.value(i).getName()));
    }
}

void Products::on_addButton_clicked()
{
    ProductDialog *dialog = new ProductDialog();
    ProductCatRepository catRepos(m_database.getDb());
    ProductRepository productRepos(m_database.getDb());

    ProductEntity product;
    ProductCatEntity cat;

    dialog->setCategoryList(catRepos.findNamesOnly());
    dialog->exec();

    if (dialog->m_validate) {
        cat = catRepos.findOneByName(dialog->category());
        product.setCat(cat);
        product.setName(dialog->product());

        if (productRepos.persist(product)) {
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
    ProductCatRepository catRepos(m_database.getDb());
    ProductRepository productRepos(m_database.getDb());

    ProductEntity product;
    ProductCatEntity cat;

    dialog->setCategoryList(catRepos.findNamesOnly());
    dialog->exec();

    if (dialog->m_validate) {
        product = productRepos.findOneByName(ui->tableWidget->item(ui->tableWidget->currentRow(), 2)->text());
        cat = catRepos.findOneByName(dialog->category());
        product.setName(dialog->product());
        product.setCat(cat);

        if (productRepos.persist(product)) {
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
        ProductRepository repos(m_database.getDb());
        ProductEntity entity;

        entity = repos.findOneByName(ui->tableWidget->item(ui->tableWidget->currentRow(), 2)->text());

        if (repos.remove(entity)) {
            QMessageBox::information(this,
                        "Suppression",
                        "La ligne a bien été supprimée de la table"
                        );
            this->refreshTable();
        }
    }
}
