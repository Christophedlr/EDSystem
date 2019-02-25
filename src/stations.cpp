#include <QInputDialog>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "stations.h"
#include "ui_stations.h"
#include "dialog/stationdialog.h"
#include "repository/stationrepository.h"
#include "repository/systemrepository.h"

Stations::Stations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stations)
{
    ui->setupUi(this);
    this->refreshTable();
}

Stations::~Stations()
{
    delete ui;
}

void Stations::on_addButton_clicked()
{
    StationDialog *dialog = new StationDialog();
    SystemRepository systemRepos(m_database.getDb());
    StationRepository stationRepos(m_database.getDb());

    SystemEntity system;
    StationEntity station;

    dialog->setSystemList(systemRepos.findNamesOnly());
    dialog->exec();

    if (dialog->m_validate) {
        system = systemRepos.findOneByName(dialog->system());
        station.setName(dialog->station());
        station.setSystem(system);

        //m_database.station()->add(m_database.system()->findByName(dialog->system()), dialog->station())
        if (stationRepos.persist(station)) {
            QMessageBox::information(this,
                        "Ajout",
                        "La ligne a bien été ajoutée dans la table"
                        );
            this->refreshTable();
        }
    }
}

void Stations::refreshTable()
{
    QList<StationEntity> list;
    StationRepository repos(m_database.getDb());

    list = repos.find();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < list.count(); ++i) {
        StationEntity entity = list.value(i);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-3,
                    new QTableWidgetItem(QString::number(entity.getId()))
                    );

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-2,
                    new QTableWidgetItem(entity.getSystem().getName())
                    );

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-1,
                    new QTableWidgetItem(entity.getName())
                    );
    }
}

void Stations::on_removeButton_clicked()
{
    QString question = QString("Supprimer la ligne %1 ?").arg(ui->tableWidget->currentRow()+1);

    if (QMessageBox::question(
                0,
                "Confirmation de suppression",
                question,
                QMessageBox::Yes|QMessageBox::No
                ) == QMessageBox::Yes) {
        if (m_database.station()->remove(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt())) {
            QMessageBox::information(this,
                        "Suppression",
                        "La ligne a bien été supprimée de la table"
                        );
            this->refreshTable();
        }
    }
}

void Stations::on_changeButton_clicked()
{
    StationDialog *dialog = new StationDialog();

    dialog->setSystemList(m_database.system()->selectNames());
    dialog->exec();

    if (dialog->Accepted) {
        if (m_database.station()->change(
                    ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toInt(),
                    m_database.system()->findByName(dialog->system()),
                    dialog->station()
                    )) {
            QMessageBox::information(this,
                        "Modification",
                        "La ligne a bien été modifiée dans la table"
                        );
            this->refreshTable();
        }
    }
}
