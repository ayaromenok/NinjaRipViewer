#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Andrey Yaromenok");
    QApplication::setOrganizationDomain("ayaromenok.info");
    QApplication::setApplicationName("NinjaRipViewer");
    QApplication::setApplicationVersion("0.0.1");

    MainWindow w;
    w.show();

    return a.exec();
}
