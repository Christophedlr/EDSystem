#include <QInputDialog>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
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
        QSettings settings("Christophedlr", "EDSystem");
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

        db.setHostName(settings.value("host").toString());
        db.setPort(settings.value("port").toInt());
        db.setUserName(settings.value("username").toString());
        db.setPassword(settings.value("password").toString());
        db.setDatabaseName(settings.value("dbname").toString());

        if (db.open()) {
            QSqlQuery query;

            query.prepare("INSERT INTO `system` (`name`) VALUES(?)");
            query.bindValue(0, name);
            if (query.exec()) {
                QMessageBox::information(this,
                            "Ajout",
                            "La ligne a bien été ajoutée dans la table"
                            );
            }

            db.close();
            this->refreshTable();
        } else {
            QMessageBox::critical(
                        this,
                        "Connexion BDD",
                        "Impossible d'établir une connexion avec la base de données."
                        " Il est peut être nécessaire de réinstaller la base."
                        );
        }
    }
}

void Systems::refreshTable()
{
    QSettings settings("Christophedlr", "EDSystem");
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(settings.value("host").toString());
    db.setPort(settings.value("port").toInt());
    db.setUserName(settings.value("username").toString());
    db.setPassword(settings.value("password").toString());
    db.setDatabaseName(settings.value("dbname").toString());

    if (db.open()) {
        QSqlQuery query;

        if (query.exec("SELECT * FROM `system`")) {
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);

            while (query.next()) {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-2, new QTableWidgetItem(query.value("id").toString()));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, ui->tableWidget->columnCount()-1, new QTableWidgetItem(query.value("name").toString()));
            }
        }
    }

    db.close();
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

        QSettings settings("Christophedlr", "EDSystem");
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

        db.setHostName(settings.value("host").toString());
        db.setPort(settings.value("port").toInt());
        db.setUserName(settings.value("username").toString());
        db.setPassword(settings.value("password").toString());
        db.setDatabaseName(settings.value("dbname").toString());

        if (db.open()) {
            QSqlQuery query;

            query.prepare("DELETE FROM `system` WHERE `id`=?");
            query.bindValue(0, ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text());
            if (query.exec()) {
                QMessageBox::information(this,
                            "Suppression",
                            "La ligne a bien été supprimée de la table"
                            );
            }

            db.close();
            this->refreshTable();
        } else {
            QMessageBox::critical(
                        this,
                        "Connexion BDD",
                        "Impossible d'établir une connexion avec la base de données."
                        " Il est peut être nécessaire de réinstaller la base."
                        );
        }
    }
}

void Systems::on_changeButton_clicked()
{
    QString name = QInputDialog::getText(this, "Modification", "Nom du système :");

    if (!name.isEmpty())
    {
        QSettings settings("Christophedlr", "EDSystem");
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

        db.setHostName(settings.value("host").toString());
        db.setPort(settings.value("port").toInt());
        db.setUserName(settings.value("username").toString());
        db.setPassword(settings.value("password").toString());
        db.setDatabaseName(settings.value("dbname").toString());

        if (db.open()) {
            QSqlQuery query;

            query.prepare("UPDATE `system` SET `name`=? WHERE `id`=?");
            query.bindValue(0, name);
            query.bindValue(1, ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->text());

            if (query.exec()) {
                QMessageBox::information(this,
                            "Modification",
                            "La ligne a bien été modifiée dans la table"
                            );
            }

            db.close();
            this->refreshTable();
        } else {
            QMessageBox::critical(
                        this,
                        "Connexion BDD",
                        "Impossible d'établir une connexion avec la base de données."
                        " Il est peut être nécessaire de réinstaller la base."
                        );
        }
    }
}
