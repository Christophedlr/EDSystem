#include <QInputDialog>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTableWidgetItem>
#include "systems.h"
#include "ui_systems.h"

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
        if (m_database.addSystem(name)) {
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
    QList<QMap<QString, QVariant>> list;
    list = m_database.selectSystems();

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

void Systems::on_removeButton_clicked()
{
    QString question = QString("Supprimer la ligne %1 ?").arg(ui->tableWidget->currentRow()+1);

    if (QMessageBox::question(
                0,
                "Confirmation de suppression",
                question,
                QMessageBox::Yes|QMessageBox::No
                ) == QMessageBox::Yes) {
        if (m_database.removeSystem(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt())) {
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
        if (m_database.changeSystem(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt(), name)) {
            QMessageBox::information(this,
                        "Modification",
                        "La ligne a bien été modifiée dans la table"
                        );
            this->refreshTable();
        }
    }
}
