#include "mainwindow.h"
#include "speicher.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    Speicher& speicher = Speicher::instance();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
