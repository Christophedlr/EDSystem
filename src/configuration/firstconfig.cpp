#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include "firstconfig.h"
#include "ui_firstconfig.h"

FirstConfig::FirstConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstConfig)
{
    ui->setupUi(this);
}

FirstConfig::~FirstConfig()
{
    delete ui;
}

void FirstConfig::on_testConnectionButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(ui->hostEdit->text());
    db.setPort(ui->portEdit->text().toInt());
    db.setUserName(ui->usernameEdit->text());
    db.setPassword(ui->passwordEdit->text());
    db.setDatabaseName(ui->dbnameEdit->text());

    if (db.open())
    {
        QMessageBox::information(0, "Test connection BDD", "La connexion a réussie");
    }
    else {
        QMessageBox::information(0, "Test connection BDD", "La connexion a échouée");
    }
}

void FirstConfig::on_validateButton_clicked()
{
    QSettings settings("Christophedlr", "EDSystem");
    settings.setValue("host", ui->hostEdit->text());
    settings.setValue("port", ui->portEdit->text().toInt());
    settings.setValue("username", ui->usernameEdit->text());
    settings.setValue("password", ui->passwordEdit->text());
    settings.setValue("dbname", ui->dbnameEdit->text());
    settings.setValue("installed", true);

    QFile sqlfile(QDir::currentPath()+"/sql/base.sql");

    if (sqlfile.open(QIODevice::ReadOnly))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(ui->hostEdit->text());
        db.setPort(ui->portEdit->text().toInt());
        db.setUserName(ui->usernameEdit->text());
        db.setPassword(ui->passwordEdit->text());
        db.setDatabaseName(ui->dbnameEdit->text());
        db.transaction();

        if (db.open())
        {
            QTextStream stream(&sqlfile);
            QSqlQuery query;

            while (!stream.atEnd()) {
                QString line = stream.readLine();
                if (!line.isEmpty())
                {
                    if (!query.exec(line))
                    {
                        db.rollback();
                        QMessageBox::information(
                                    0,
                                    "Base de donnée",
                                    "Un problème est survenu lors de la création de la base,"
                                    "il peut être nécessaire de réinstaller le logiciel."
                                    "Si le problème persiste, merci de nous contacter."
                                    );

                        return;
                    }
                }
            }

            db.commit();
            QMessageBox::information(
                        0,
                        "Base de donnée",
                        "La configuration est enregistrée et la base de donnée a bien été créer."
                        );

            db.close();
            this->close();
            return;
        }
        else {
            QMessageBox::information(
                        0,
                        "Base de donnée",
                        "Impossible d'établir la connexion avec le serveur."
                        "Si le problème persiste, merci de nous contacter."
                        );
        }
    }
    else {
        QMessageBox::information(
                    0,
                    "Base de donnée",
                    "Impossible de trouver le fichier SQL, merci de réinstaller le logiciel."
                    );
    }
}
