#include "mainwindow.h"
#include "speicher.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    Speicher& speicher = Speicher::instance();

    if(speicher.SpeicherSicherheitscode != 1306)
    {
        qDebug() << "Speicher wurde nicht erstellt! " << speicher.SpeicherSicherheitscode;
        return -1;
    }


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
