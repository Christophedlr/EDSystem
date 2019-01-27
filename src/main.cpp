#include <QApplication>
#include <QSettings>
#include "menu.h"
#include "configuration/firstconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FirstConfig config;
    Menu w;

    QSettings settings("Christophedlr", "EDSystem");
    QVariant installed = settings.value("installed");

    if (installed.isValid() == false || installed.toBool() == false)
    {
        config.setWindowModality(Qt::ApplicationModal);
        config.show();
    }

    w.show();

    return a.exec();
}
