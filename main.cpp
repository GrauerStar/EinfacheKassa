#include "mainwindow.h"
#include "speicher.h"
#include "produkt.h"


#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{

    Speicher& speicher = Speicher::instance();

    if(speicher.SpeicherSicherheitscode != 1306)
    {
        qDebug() << "Speicher wurde nicht erstellt! " << speicher.SpeicherSicherheitscode;
        return -1;
    }

    // Pfad zum Verzeichnis des ausführbaren Programms
    QFileInfo executableFile(argv[0]);
    QString executablePath = executableFile.absolutePath();


    // Pfad zum Ordner "data"
    QString dataPath = executablePath + "/data";
    QDir ordner(dataPath);

    // QDir ordner(DataSpeicherPfadString);
     if(!ordner.exists())
     {
         if(ordner.mkpath(dataPath))
         {
             qDebug() << "Data Ordner wurde erstellt: ";
         }
         else
         {
             qDebug() << "Ordner konnte nicht erstellt werden: ";
             return -1;
         }
     }
     else
     {
         //TODO Load Produkte
     }

     dataPath += "/";

     //Data Pafd in Speicher
     speicher.setDataPfad(dataPath);


    //Das 0er Produkt einfügen
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
