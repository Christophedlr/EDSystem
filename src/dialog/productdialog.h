#ifndef PRODUCTDIALOG_H
#define PRODUCTDIALOG_H

#include <QDialog>

namespace Ui {
class ProductDialog;
}

class ProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductDialog(QWidget *parent = 0);
    ~ProductDialog();
    QString category();
    QString product();
    void setCategoryList(QStringList list);

private:
    Ui::ProductDialog *ui;
};

#endif // PRODUCTDIALOG_H
