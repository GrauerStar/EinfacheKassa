#include "neusprodukt.h"
#include "ui_neusprodukt.h"

NeusProdukt::NeusProdukt(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NeusProdukt)
{
    ui->setupUi(this);

    aenderungenNichtGespeichert = 0;

    //combobox befüllen
    const quint8* mwstArray = speicher.getMwst();
    for(int i = 0; i < speicher.getMwstIndex(); i++)
    {
        ui->comboBox_MwSt->addItem(QString::number(mwstArray[i]) + " %", mwstArray[i]);
    }
    //setup
    maxProduktSetzen();
    aktuellesProduktSetzen(speicher.aktuellesProduktVisuell());
    produkDatenSetzen(speicher.aktuellesProdukt());

    //Buttons Verbinden
    connect(ui->pushButton_Nachstes, SIGNAL(clicked(bool)),this ,SLOT(naechstesProdukt()));
    connect(ui->pushButton_Vorher, SIGNAL(clicked(bool)), this, SLOT(vorherigesProdukt()));
    connect(ui->pushButton_Speichern, SIGNAL(clicked(bool)), this, SLOT(speichern()));
    connect(ui->pushButton_GeheZuArtNr, SIGNAL(clicked(bool)), this, SLOT(gehZuArtNrAbfrage()));







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

bool NeusProdukt::sicherheitesFrageUngespeichert(quint8 frage)
{
    QList<Produkt> produkte = speicher.getProdukte();

    Produkt p = produkte[speicher.aktuellesProdukt()];
    Produkt v;

    // Produkte auslesen und in v speichern
    v.setName(ui->lineEdit_ProduktName->text());
    v.setArtnr(ui->lineEdit_ArtNr->text().toUInt());

    // Umrechnung des Preises von Euro in Cent
    QString tempString = ui->lineEdit_PreisInEuro->text();
    tempString.replace(",", ".");

    //quint64 preisInCent = tempString.toDouble() * 100;
    quint64 preisInCent = 0;
    quint64 temp = 0;
    for(quint32 i = 0; i < tempString.length(); i++)
    {
        if(tempString[i] != '.')
        {
            preisInCent = preisInCent*10;
            temp = QString(tempString[i]).toUInt();
            preisInCent += temp;
        }
    }


    v.setPreisInCent(preisInCent);
    v.setMwst(ui->comboBox_MwSt->currentData().toUInt());
    v.setInfo(ui->plainTextEdit_Info->toPlainText());

    // Vergleich der Werte
    if(p.getName() != v.getName())
    {
        qDebug() << "Name";
        aenderungenNichtGespeichert++;
    }

    if(p.getArtnr() != v.getArtnr())
    {
        qDebug() << "ArtNr";
        aenderungenNichtGespeichert++;
    }

    if(p.getPreisInCent() != v.getPreisInCent())
    {
        qDebug() << "Preis " << v.getPreisInCent();
        aenderungenNichtGespeichert++;
    }

    if(p.getMwst() != v.getMwst())
    {
        qDebug() << "MwSt" << v.getMwst();
        aenderungenNichtGespeichert++;
    }

    if(p.getInfo() != v.getInfo())
    {
        qDebug() << "Info";
        aenderungenNichtGespeichert++;
    }



    if(abfrageAenderungen(frage))
    {
        return true;
    }
    else
    {
        return false;
    }

}

void NeusProdukt::naechstesProdukt()
{
    if(!sicherheitesFrageUngespeichert(0))
    {
        return;
    }

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
    if(!sicherheitesFrageUngespeichert(0))
    {
        return;
    }

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

bool NeusProdukt::abfrageAenderungen(quint8 frage = 0)
{

    if(aenderungenNichtGespeichert > 0)
    {
        QString msgText = "Änderungen wurden noch nicht gespeichert. ";

        switch (frage)
        {
        case 0:
            msgText += "Wollen Sie wirklich fortfahren?";
            break;
        case 1:
            msgText += "Wollen Sie wirklich schließen?";
            break;
        case 2:
            msgText += "Wollen Sie zu andem Artikel springen?";
            break;

        default:
            msgText += "FEHLER BEI SWITCH CASE.";
            break;
        }



        // Erstellung der QMessageBox
        QMessageBox msgBox;
        msgBox.setWindowTitle("Änderungen nicht gespeichert");
        msgBox.setText(msgText);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        // Ändern der Texte der Buttons
        msgBox.button(QMessageBox::Yes)->setText("Ja");
        msgBox.button(QMessageBox::No)->setText("Nein");

        // Anzeigen der Nachricht und Rückgabe des geklickten Buttons
        QMessageBox::StandardButton frage = static_cast<QMessageBox::StandardButton>(msgBox.exec());

        // Entscheidung basierend auf der Benutzerwahl
        if(frage == QMessageBox::No)
        {
            return false;
        }
        else
        {
            aenderungenNichtGespeichert = 0;
            return true;
        }
    }

    // sollte kein Änderungen erfolgt sein
    return true;
}



void NeusProdukt::closeEvent(QCloseEvent *event)
{
    if(!abfrageAenderungen(1))
    {
        event->ignore();
    }
    else
    {
        event->accept();
    }

}

void NeusProdukt::speichern()
{
    // Umrechnung des Preises von Euro in Cent
    QString tempString = ui->lineEdit_PreisInEuro->text();
    tempString.replace(",", ".");

    quint64 preisInCent = 0;
    quint64 temp = 0;
    for(quint32 i = 0; i < tempString.length(); i++)
    {
        if(tempString[i] != '.')
        {
            preisInCent = preisInCent*10;
            temp = QString(tempString[i]).toUInt();
            preisInCent += temp;
        }
    }



    if(preisInCent == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fehler bei Preis");
        msgBox.setText("Der Preis ist Fehlerhaft, bitte korrigieren vor dem Speichern.");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
    }


    QList<Produkt>* produkte = speicher.getProduktePointer();

    Produkt& v = (*produkte)[speicher.aktuellesProdukt()];



    //Wenn die ArtNr gleich ist nichts machen
    if(v.getArtnr() != ui->lineEdit_ArtNr->text().toUInt())
    {
        //Ansonsten checken ob die ArtNr schon existiert
        if(speicher.sucheArtNr(ui->lineEdit_ArtNr->text().toUInt()))
        {
            quint64 naechsteFreieArtNr = ui->lineEdit_ArtNr->text().toUInt() ;
            quint64 maxArtNr = -1;

            for(;naechsteFreieArtNr != maxArtNr ; naechsteFreieArtNr++)
            {
                if(speicher.sucheArtNr(naechsteFreieArtNr) == 0)
                {
                    break;
                }
            }

            QString text = "Die ArtNr existiert schon, bitte eine andere eingeben.\n";
            text += "Die nächste freie ArtNr wäre: ";
            text += QString::number(naechsteFreieArtNr);

            QMessageBox Box;
            Box.setWindowTitle("ArtNr existiert schon");
            Box.setText(text);
            Box.addButton(QMessageBox::Ok);
            Box.exec();
            return;
        }
    }

    // Produkte auslesen und in v speichern
    v.setName(ui->lineEdit_ProduktName->text());
    v.setArtnr(ui->lineEdit_ArtNr->text().toUInt());

    v.setPreisInCent(preisInCent);

    v.setMwst(ui->comboBox_MwSt->currentData().toUInt());
    v.setInfo(ui->plainTextEdit_Info->toPlainText());

    aenderungenNichtGespeichert = 0;
}

void NeusProdukt::gehZuArtNrAbfrage()
{
    quint64 eingegebenArtnr = 0;

    if(!sicherheitesFrageUngespeichert(2))
    {
        return;
    }



    QDialog dialog;
    dialog.setWindowTitle("ArtNr suchen");

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("Bitte geben Sie die ArtNr ein:");
    mainLayout->addWidget(label);

    QLineEdit *artNrLineEdit = new QLineEdit(&dialog);
    mainLayout->addWidget(artNrLineEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *okButton = new QPushButton("Ok", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(buttonLayout);

    QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Die Funktion muss noch angepasst werden, die ARTN muss geprüft werden und anschließend muss er auf das Aktuelle Produkt lt Index gesetzt werden

    if (dialog.exec() == QDialog::Accepted) {

        QString artNr = artNrLineEdit->text();
        eingegebenArtnr = artNr.toUInt();

        if(eingegebenArtnr == 0)
        {
            QMessageBox errorBox;
            errorBox.setWindowTitle("Fehler bei ArtNr");
            errorBox.setText("Eingabe nicht erkannt");
            errorBox.addButton(QMessageBox::Ok);
            errorBox.exec();
            return;
        }

        quint64 index = speicher.sucheArtNr(eingegebenArtnr);

        if(index == 0)
        {
            QMessageBox errorBox2;
            errorBox2.setWindowTitle("ArtNr nicht gefunden");
            errorBox2.setText("Die eingegebene ArtNr nicht gefunden.");
            errorBox2.addButton(QMessageBox::Ok);
            errorBox2.exec();
            return;
        }

        speicher.setAktuellesProdukt(index);
        springZuProdukt(index);

    } else {
        QMessageBox::information(nullptr, "Abgebrochen", "Die Eingabe wurde abgebrochen.");
    }


}


void NeusProdukt::springZuProdukt(quint64 indexProduktListe)
{
    maxProduktSetzen();
    aktuellesProduktSetzen(indexProduktListe);
    produkDatenSetzen(indexProduktListe);
}
