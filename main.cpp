#include "mainwindow.h"
#include "speicher.h"
#include "produkt.h"


#include <QApplication>

int main(int argc, char *argv[])
{

    Speicher& speicher = Speicher::instance();

    if(speicher.SpeicherSicherheitscode != 1306)
    {
        qDebug() << "Speicher wurde nicht erstellt! " << speicher.SpeicherSicherheitscode;
        return -1;
    }

    Produkt p;
    p.setArtnr(0);
    p.setName("DEBUG Produkt");
    p.setInfo("NICHT LÖSCHEN!");
    p.setMwst(20);
    p.setPreisInCent(999);

    speicher.addProdukt(p);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
