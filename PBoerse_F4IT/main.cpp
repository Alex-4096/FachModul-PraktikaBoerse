#include "mainwindow.h"
#include <QApplication>
//hallo ich bin ein testkommentar
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
