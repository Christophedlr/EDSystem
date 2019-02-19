#include <QInputDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include "systems.h"
#include "ui_systems.h"
#include "repository/systemrepository.h"

Systems::Systems(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Systems)
{
    ui->setupUi(this);
    this->refreshTable();
}

Systems::~Systems()
{
    delete ui;
}

void Systems::on_addButton_clicked()
{
    QString name = QInputDialog::getText(this, "Ajout", "Nom du système :");

    if (!name.isEmpty())
    {
        SystemEntity entity;
        SystemRepository repos(m_database.getDb());

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

void Systems::refreshTable()
{
    QList<SystemEntity> list;
    SystemRepository repos(m_database.getDb());

    list = repos.find();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < list.count(); ++i) {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-2, new QTableWidgetItem(QString::number(list.value(i).getId())));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-1, new QTableWidgetItem(list.value(i).getName()));
    }
}

void Systems::on_removeButton_clicked()
{
    QString question = QString("Supprimer la ligne %1 ?").arg(ui->tableWidget->currentRow()+1);

    if (QMessageBox::question(
                0,
                "Confirmation de suppression",
                question,
                QMessageBox::Yes|QMessageBox::No
                ) == QMessageBox::Yes) {
        SystemEntity entity;
        SystemRepository repos(m_database.getDb());

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

void Systems::on_changeButton_clicked()
{
    QString name = QInputDialog::getText(this, "Modification", "Nom du système :");

    if (!name.isEmpty())
    {
        SystemEntity entity;
        SystemRepository repos(m_database.getDb());

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
