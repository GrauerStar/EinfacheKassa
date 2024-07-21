#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Knöpfe verbinden
    connect(ui->actionProdukt_hinzuf_gen, SIGNAL(triggered()), this, SLOT(fensterNeusProdukt() ));




    //Test funktionen
    Produkt p;

    p.setArtnr(1001);
    p.setName("TestProdukt2");
    p.setInfo("Das ist noch eine Information");
    p.setMwst(10);
    p.setPreisInCent(1000);

    speicher.addProdukt(p);

    p.setArtnr(1002);
    p.setName("TestProdukt3");
    p.setInfo("Das ist schon wieder eine Information");
    p.setMwst(13);
    p.setPreisInCent(1599);

    speicher.addProdukt(p);

    p.setArtnr(1003);
    p.setName("TestProdukt4");
    p.setInfo("Das ist schon wieder eine Information.\nOida");
    p.setMwst(20);
    p.setPreisInCent(1988);

    speicher.addProdukt(p);

    p.setArtnr(1004);
    p.setName("TestProdukt5");
    p.setInfo("Zu fü info...");
    p.setMwst(10);
    p.setPreisInCent(1990);

    speicher.addProdukt(p);



    Produkt tempP = speicher.getProdukte()[2];


     ui->plainTextEdit->setPlainText("Produkt Info:\nArtNr:\t" + QString::number(tempP.getArtnr())
                                    + "\nName:\t" + tempP.getName()
                                    + "\nInfo:\t" + tempP.getInfo()
                                    + "\nMwSt:\t" + QString::number(tempP.getMwst())
                                    + "\nPreis in Cent:\t" + QString::number(tempP.getPreisInCent())
                                    + "\nPreis:\t" + tempP.getPreisAsString());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::fensterNeusProdukt()
{
    NeusProdukt nP(this);
    nP.setWindowTitle("Produkte Bearbeiten");
    nP.exec();
    return;
}
