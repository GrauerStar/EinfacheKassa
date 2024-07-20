#include "neusprodukt.h"
#include "ui_neusprodukt.h"

NeusProdukt::NeusProdukt(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NeusProdukt)
{
    ui->setupUi(this);

    //setup
    maxProduktSetzen();
    aktuellesProduktSetzen(speicher.aktuellesProduktVisuell());
    produkDatenSetzen(speicher.aktuellesProdukt());
    //combobox befüllen
    const quint8* mwstArray = speicher.getMwst();
    for(int i = 0; i < speicher.getMwstIndex(); i++)
    {
        ui->comboBox_MwSt->addItem(QString::number(mwstArray[i]) + " %", mwstArray[i]);
    }
    //Buttons Verbinden
    connect(ui->pushButton_Nachstes, SIGNAL(clicked(bool)),this ,SLOT(naechstesProdukt()));
    connect(ui->pushButton_Vorher, SIGNAL(clicked(bool)), this, SLOT(vorherigesProdukt()));







}

NeusProdukt::~NeusProdukt()
{
    delete ui;
}



// Funktionen:
void NeusProdukt::maxProduktSetzen()
{
    ui->lineEdit_maxProdukte->setText(QString::number(speicher.anzahlProdukte()));
    return;
}

bool NeusProdukt::aktuelleProduktPruefen(quint64 aktuellesProdukt)
{
    quint64 maxProdukte = speicher.anzahlProdukte();

    if( aktuellesProdukt >= maxProdukte )
    {
        // Wenn Aktuelles Produkt größer als Max Produkte ist
        return false;
    }
    else if(aktuellesProdukt <= 0)
    {
        // oder kleiner gleich 0
        return false;
    }
    else
    {
        return true;
    }
}

void NeusProdukt::naechstesProdukt()
{
    quint64 tempVar = speicher.aktuellesProdukt() + 1;

    if(aktuelleProduktPruefen(tempVar))
    {
        speicher.setAktuellesProdukt(tempVar);
        aktuellesProduktSetzen(speicher.aktuellesProduktVisuell());
        produkDatenSetzen(speicher.aktuellesProdukt());
    }
    else
    {
        //Fehlermeldung ausgeben
        QMessageBox msgBox;
        msgBox.setWindowTitle("Zu viele Produkte");
        if(speicher.anzahlProdukte() > 1)
        {
            msgBox.setText("Es gibt noch nicht mehr als " + QString::number(tempVar) + " Produkte!");
        }
        else
        {
            msgBox.setText("Aktuell gibts nur ein Produkt!");
        }
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.addButton("Ok", QMessageBox::AcceptRole);
        msgBox.exec();
    }
}

void NeusProdukt::vorherigesProdukt()
{
    quint64 tempVar = speicher.aktuellesProdukt();

    if(aktuelleProduktPruefen(tempVar))
    {
        speicher.setAktuellesProdukt(--tempVar);
        aktuellesProduktSetzen(speicher.aktuellesProduktVisuell());
        produkDatenSetzen(speicher.aktuellesProdukt());
    }
    else
    {
        //Fehlermeldung ausgeben
        QMessageBox msgBox;
        msgBox.setWindowTitle("Zu wenig Produkte");
        msgBox.setText("Weniger wie 1 ist nicht möglich!");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.addButton("Ok", QMessageBox::AcceptRole);
        msgBox.exec();
    }
}

void NeusProdukt::aktuellesProduktSetzen(quint64 wert)
{
    ui->lineEdit_aktuellesProdukt->setText(QString::number(wert));
}

void NeusProdukt::produkDatenSetzen(quint64 wert)
{
    Produkt tempP = speicher.getProdukte()[wert];

    ui->lineEdit_ProduktName->setText(tempP.getName());
    ui->lineEdit_ArtNr->setText(QString::number(tempP.getArtnr()));
    ui->lineEdit_PreisInEuro->setText(tempP.getPreisAsString());

    // Setzt den Combobox wert auf den Index der über die Funktion mwstUmwandelnIndexMwst() umgewandelt wird
    ui->comboBox_MwSt->setCurrentIndex(speicher.mwstUmwandelnIndexMwst(tempP.getMwst()));



    ui->plainTextEdit_Info->setPlainText(tempP.getInfo());
    aktuellesProduktSetzen(wert +1 );

}

