#ifndef STATIONDIALOG_H
#define STATIONDIALOG_H

#include <QDialog>

namespace Ui {
class StationDialog;
}

class StationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StationDialog(QWidget *parent = 0);
    ~StationDialog();
    bool m_validate = false;
    QString system();
    QString station();
    void setSystemList(QStringList list);

private slots:
    void on_acceptButton_clicked();

private:
    Ui::StationDialog *ui;
};

#endif // STATIONDIALOG_H
