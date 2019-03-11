#ifndef PATHDIALOG_H
#define PATHDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QList>
#include <QSqlDatabase>

namespace Ui {
class PathDialog;
}

class PathDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit PathDialog(QWidget *parent = 0);
        ~PathDialog();
        void fill(QSqlDatabase *database);
        QMap<QString, QVariant> getData();

    private slots:
            void on_systemCBox_currentIndexChanged(const QString &arg1);

            void on_catCBox_currentIndexChanged(const QString &arg1);

private:
            Ui::PathDialog *ui;
            QSqlDatabase *m_database;
};

#endif // PATHDIALOG_H
