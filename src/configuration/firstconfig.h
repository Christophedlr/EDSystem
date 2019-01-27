#ifndef FIRSTCONFIG_H
#define FIRSTCONFIG_H

#include <QWidget>

namespace Ui {
class FirstConfig;
}

class FirstConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FirstConfig(QWidget *parent = 0);
    ~FirstConfig();

public slots:
    void on_testConnectionButton_clicked();
    void on_validateButton_clicked();

private:
    Ui::FirstConfig *ui;
};

#endif // FIRSTCONFIG_H
