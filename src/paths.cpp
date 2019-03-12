#include <QMessageBox>
#include "paths.h"
#include "ui_paths.h"
#include "dialog/pathdialog.h"
#include "repository/pathrepository.h"
#include "repository/productrepository.h"
#include "repository/stationrepository.h"

Paths::Paths(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paths)
{
    ui->setupUi(this);
    this->refreshTable();
}

Paths::~Paths()
{
    delete ui;
}

void Paths::on_addButton_clicked()
{
    PathDialog *pathDialog = new PathDialog();
    pathDialog->fill(m_database.getDb());
    pathDialog->exec();

    if (pathDialog->result() == pathDialog->Accepted) {
        PathEntity entity;
        PathRepository repos(m_database.getDb());
        ProductRepository productRepos(m_database.getDb());
        StationRepository stationRepos(m_database.getDb());
        QMap<QString, QVariant> map = pathDialog->getData();

        entity.setDate(map.value("date").toString());
        entity.setProduct(productRepos.findOne(map.value("product").toUInt()));
        entity.setProfit(map.value("profit").toUInt());
        entity.setQuantity(map.value("quantity").toUInt());
        entity.setStation(stationRepos.findOne(map.value("station").toUInt()));

        if (repos.persist(entity)) {
            QMessageBox::information(this,
                        "Ajout",
                        "La ligne a bien été ajoutée dans la table"
                        );
            this->refreshTable();
        }
    }
}

void Paths::on_changeButton_clicked()
{
    PathDialog *pathDialog = new PathDialog();
    pathDialog->fill(m_database.getDb());
    pathDialog->exec();

    if (pathDialog->result() == pathDialog->Accepted) {
        PathEntity entity;
        PathRepository repos(m_database.getDb());
        ProductRepository productRepos(m_database.getDb());
        StationRepository stationRepos(m_database.getDb());
        QMap<QString, QVariant> map = pathDialog->getData();

        entity.setDate(map.value("date").toString());
        entity.setProduct(productRepos.findOne(map.value("product").toUInt()));
        entity.setProfit(map.value("profit").toUInt());
        entity.setQuantity(map.value("quantity").toUInt());
        entity.setStation(stationRepos.findOne(map.value("station").toUInt()));
        entity.setId(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toUInt());

        if (repos.persist(entity)) {
            QMessageBox::information(this,
                        "Modification",
                        "La ligne a bien été modifiée dans la table"
                        );
            this->refreshTable();
        }
    }
}

void Paths::on_deleteButton_clicked()
{
    QString question = QString("Supprimer la ligne %1 ?").arg(ui->tableWidget->currentRow()+1);

    if (QMessageBox::question(
                0,
                "Confirmation de suppression",
                question,
                QMessageBox::Yes|QMessageBox::No
                ) == QMessageBox::Yes) {
        PathRepository repos(m_database.getDb());
        PathEntity entity;

        entity = repos.findOne(ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text().toUInt());

        if (repos.remove(entity)) {
            QMessageBox::information(this,
                        "Suppression",
                        "La ligne a bien été supprimée de la table"
                        );
            this->refreshTable();
        }
    }
}

void Paths::refreshTable()
{
    QList<PathEntity> list;
    PathRepository repos(m_database.getDb());

    list = repos.find();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for (int i = 0; i < list.count(); ++i) {
        PathEntity entity = list.value(i);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-8,
                    new QTableWidgetItem(QString::number(entity.getId()))
                    );

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-7,
                    new QTableWidgetItem(entity.getDate())
                    );

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-6,
                    new QTableWidgetItem(entity.getStation().getSystem().getName())
                    );

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-5,
                    new QTableWidgetItem(entity.getStation().getName())
                    );

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-4,
                    new QTableWidgetItem(entity.getProduct().getCat().getName())
                    );

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-3,
                    new QTableWidgetItem(entity.getProduct().getName())
                    );

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-2,
                    new QTableWidgetItem(QString::number(entity.getQuantity()))
                    );

        ui->tableWidget->setItem(
                    ui->tableWidget->rowCount()-1,
                    ui->tableWidget->columnCount()-1,
                    new QTableWidgetItem(QString::number(entity.getProfit()))
                    );
    }
}
