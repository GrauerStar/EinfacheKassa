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
    speicher.setAktuellesProdukt(1);
    produkDatenSetzen(speicher.aktuellesProdukt());

    //Buttons Verbinden
    connect(ui->pushButton_Nachstes, SIGNAL(clicked(bool)),this ,SLOT(naechstesProdukt()));
    connect(ui->pushButton_Vorher, SIGNAL(clicked(bool)), this, SLOT(vorherigesProdukt()));
    connect(ui->pushButton_Speichern, SIGNAL(clicked(bool)), this, SLOT(speichern()));
    connect(ui->pushButton_GeheZuArtNr, SIGNAL(clicked(bool)), this, SLOT(gehZuArtNrAbfrage()));
    connect(ui->pushButton_ErstesProdukt, SIGNAL(clicked(bool)), this, SLOT(springenZuErsten()));
    connect(ui->pushButton_LetztesProdukt, SIGNAL(clicked(bool)), this, SLOT(springenZuLetzten()));
    connect(ui->pushButton_AllesLoeschen, SIGNAL(clicked(bool)), this, SLOT(loescheLineEditsNonAuto()));
    connect(ui->pushButton_NeusProdukt, SIGNAL(clicked(bool)), this, SLOT(erstelleNeuesProdukt()));
    connect(ui->pushButton_Fertig, SIGNAL(clicked(bool)), this, SLOT(produkteExportierenToJson()));
    connect(ui->pushButton_Abbrechen, SIGNAL(clicked(bool)), this, SLOT(abbrechen()));

    //LineEdits Verbinden
    connect(ui->lineEdit_aktuellesProdukt, SIGNAL(returnPressed()) , this, SLOT(springenWenObenEingegeben()));





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
//Die Funktion checkt ob das aktuelle Produkt in der Liste vorhanden ist oder zu hoch
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

    quint64 tempVar = speicher.aktuellesProdukt();

    if(aktuelleProduktPruefen(tempVar))
    {
        speicher.setAktuellesProdukt(tempVar + 1);
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

    quint64 tempVar = speicher.aktuellesProdukt() -1;

    if(aktuelleProduktPruefen(tempVar))
    {
        speicher.setAktuellesProdukt(tempVar);
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

void NeusProdukt::produkDatenSetzen(quint64 wert)
{
    Produkt tempP = speicher.getProdukte()[wert];

    ui->lineEdit_aktuellesProdukt->setText(QString::number(wert));
    ui->lineEdit_ProduktName->setText(tempP.getName());
    ui->lineEdit_ArtNr->setText(QString::number(tempP.getArtnr()));
    ui->lineEdit_PreisInEuro->setText(tempP.getPreisAsString());

    // Setzt den Combobox wert auf den Index der über die Funktion mwstUmwandelnIndexMwst() umgewandelt wird
    ui->comboBox_MwSt->setCurrentIndex(speicher.mwstUmwandelnIndexMwst(tempP.getMwst()));



    ui->plainTextEdit_Info->setPlainText(tempP.getInfo());
    //aktuellesProduktSetzen(wert +1 );

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
        case 3:
            msgText += "Wollen Sie wirklich Abbrechen?";
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
    QString textPreisInEuro = ui->lineEdit_PreisInEuro->text();
    textPreisInEuro.replace(",", ".");

    if (!textPreisInEuro.contains('.'))
    {
        textPreisInEuro.append(".00");
    }

    // Sicherstellen, dass der String mindestens zwei Dezimalstellen hat
    int positionPunkt = textPreisInEuro.indexOf('.');
    int anzahlDezimalstellen = textPreisInEuro.length() - positionPunkt - 1;

    if (anzahlDezimalstellen == 1)
    {
        textPreisInEuro.append("0");
    }
    else if (anzahlDezimalstellen > 2)
    {
        // Runden auf zwei Dezimalstellen
        double wert = textPreisInEuro.toDouble();
        wert = qRound64(wert * 100.0) / 100.0;
        textPreisInEuro = QString::number(wert, 'f', 2);
    }


    // Umwandlung des Strings in Cent
    quint64 preisInCent = 0;
    bool ok = false;
    preisInCent = qRound64(textPreisInEuro.toDouble(&ok) * 100.0);

    if (!ok || preisInCent == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fehler bei Preis");
        msgBox.setText("Der Preis ist fehlerhaft, bitte korrigieren vor dem Speichern.");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if (ui->lineEdit_ProduktName->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fehler bei Produktname");
        msgBox.setText("Der Produktname ist leer, bitte korrigieren vor dem Speichern.");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if (ui->lineEdit_ArtNr->text().isEmpty() || ui->lineEdit_ArtNr->text().toUInt() == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fehler bei ArtNr");
        msgBox.setText("Das Feld für die ArtNr ist leer, bitte korrigieren vor dem Speichern.");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    if (ui->plainTextEdit_Info->toPlainText().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fehler bei Info");
        msgBox.setText("Das Info-Feld ist leer, bitte korrigieren vor dem Speichern.");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    // Weitere Verarbeitung und Validierung...

    QList<Produkt>* produkte = speicher.getProduktePointer();

    if (ui->lineEdit_aktuellesProdukt->text() == "neu")
    {
        Produkt neuesProdukt;

        // Prüfen, ob die Artikelnummer bereits existiert
        if (speicher.sucheArtNr(ui->lineEdit_ArtNr->text().toUInt()))
        {
            quint64 naechsteFreieArtNr = ui->lineEdit_ArtNr->text().toUInt();
            quint64 maxArtNr = -1;

            for (; naechsteFreieArtNr != maxArtNr; naechsteFreieArtNr++)
            {
                if (speicher.sucheArtNr(naechsteFreieArtNr) == 0)
                {
                    break;
                }
            }

            QString text = "Die ArtNr existiert schon, bitte eine andere eingeben.\n";
            text += "Die nächste freie ArtNr wäre: ";
            text += QString::number(naechsteFreieArtNr);

            QMessageBox msgBox;
            msgBox.setWindowTitle("ArtNr existiert schon");
            msgBox.setText(text);
            msgBox.addButton(QMessageBox::Ok);
            msgBox.exec();
            return;
        }

        // Produktdaten auslesen und in neuesProdukt speichern
        neuesProdukt.setName(ui->lineEdit_ProduktName->text());
        neuesProdukt.setArtnr(ui->lineEdit_ArtNr->text().toUInt());
        neuesProdukt.setPreisInCent(preisInCent);
        ui->lineEdit_PreisInEuro->setText(neuesProdukt.getPreisAsString());
        neuesProdukt.setMwst(ui->comboBox_MwSt->currentData().toUInt());
        neuesProdukt.setInfo(ui->plainTextEdit_Info->toPlainText());

        aenderungenNichtGespeichert = 0;

        speicher.addProdukt(neuesProdukt);
        speicher.setAktuellesProdukt(speicher.anzahlProdukte());

        maxProduktSetzen();
        springZuProdukt(speicher.aktuellesProdukt());
        return;
    }

    Produkt& aktuellesProdukt = (*produkte)[speicher.aktuellesProdukt()];

    // Wenn die ArtNr gleich ist, nichts machen
    if (aktuellesProdukt.getArtnr() != ui->lineEdit_ArtNr->text().toUInt())
    {
        // Ansonsten prüfen, ob die ArtNr bereits existiert
        if (speicher.sucheArtNr(ui->lineEdit_ArtNr->text().toUInt()))
        {
            quint64 naechsteFreieArtNr = ui->lineEdit_ArtNr->text().toUInt();
            quint64 maxArtNr = -1;

            for (; naechsteFreieArtNr != maxArtNr; naechsteFreieArtNr++)
            {
                if (speicher.sucheArtNr(naechsteFreieArtNr) == 0)
                {
                    break;
                }
            }

            QString text = "Die ArtNr existiert schon, bitte eine andere eingeben.\n";
            text += "Die nächste freie ArtNr wäre: ";
            text += QString::number(naechsteFreieArtNr);

            QMessageBox msgBox;
            msgBox.setWindowTitle("ArtNr existiert schon");
            msgBox.setText(text);
            msgBox.addButton(QMessageBox::Ok);
            msgBox.exec();
            return;
        }
    }

    // Produktdaten auslesen und in aktuellesProdukt speichern
    aktuellesProdukt.setName(ui->lineEdit_ProduktName->text());
    aktuellesProdukt.setArtnr(ui->lineEdit_ArtNr->text().toUInt());
    aktuellesProdukt.setPreisInCent(preisInCent);
    ui->lineEdit_PreisInEuro->setText(aktuellesProdukt.getPreisAsString());
    aktuellesProdukt.setMwst(ui->comboBox_MwSt->currentData().toUInt());
    aktuellesProdukt.setInfo(ui->plainTextEdit_Info->toPlainText());

    aenderungenNichtGespeichert = 0;
}




void NeusProdukt::gehZuArtNrAbfrage()
{
    if(!sicherheitesFrageUngespeichert(2))
    {
        return;
    }

    quint64 eingegebenArtnr = 0;

    QDialog dialog;
    dialog.setWindowTitle("ArtNr suchen");

    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);

    QLabel *label = new QLabel("Bitte geben Sie die ArtNr ein:");
    mainLayout->addWidget(label);

    QLineEdit *artNrLineEdit = new QLineEdit(&dialog);
    mainLayout->addWidget(artNrLineEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *okButton = new QPushButton("Ok", &dialog);
    QPushButton *cancelButton = new QPushButton("Abbruch", &dialog);

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
    produkDatenSetzen(indexProduktListe);
}

void NeusProdukt::springenWenObenEingegeben()
{
    if(!sicherheitesFrageUngespeichert(2))
    {
        return;
    }

    quint64 aktuellesProduktInit = ui->lineEdit_aktuellesProdukt->text().toUInt();
    if(aktuellesProduktInit > speicher.anzahlProdukte() || aktuellesProduktInit <= 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fehler bei Eingabe");
        msgBox.setText("Eingabe nicht erkannt.");
        msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        ui->lineEdit_aktuellesProdukt->setText(QString::number(speicher.aktuellesProdukt()));
        return;
    }
    else
    {
        speicher.setAktuellesProdukt(aktuellesProduktInit);
        produkDatenSetzen(aktuellesProduktInit);

    }

}

void NeusProdukt::springenZuErsten()
{
    if(!sicherheitesFrageUngespeichert(2))
    {
        return;
    }

    speicher.setAktuellesProdukt(1);
    produkDatenSetzen(1);
}

void NeusProdukt::springenZuLetzten()
{
    if(!sicherheitesFrageUngespeichert(2))
    {
        return;
    }

    speicher.setAktuellesProdukt(speicher.anzahlProdukte());
    produkDatenSetzen(speicher.anzahlProdukte());
}

void NeusProdukt::loescheLineEditsNonAuto()
{
    ui->lineEdit_ArtNr->clear();
    ui->lineEdit_PreisInEuro->clear();
    ui->lineEdit_ProduktName->clear();
    ui->plainTextEdit_Info->clear();
}

void NeusProdukt::erstelleNeuesProdukt()
{
    ui->lineEdit_aktuellesProdukt->setText("neu");
    loescheLineEditsNonAuto();
    aenderungenNichtGespeichert = 1;
    ui->comboBox_MwSt->setCurrentIndex(2);


    QString maxProdukteErweitern = ui->lineEdit_maxProdukte->text();
    maxProdukteErweitern += " (";
    maxProdukteErweitern += QString::number(speicher.anzahlProdukte() + 1);
    maxProdukteErweitern += ")";

    ui->lineEdit_maxProdukte->setText(maxProdukteErweitern);
}

void NeusProdukt::produkteExportierenToJson()
{
    if(!sicherheitesFrageUngespeichert(2))
    {
        return;
    }


    QList<Produkt> produkte = speicher.getProdukte();

    QString dateiname = speicher.DataPfad();
    dateiname += speicher.DateiNameProdukte();

    QFile pfad(dateiname);
    if(!pfad.open(QFile::WriteOnly))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fehler beim Speichern");
        msgBox.setText("Die Produkte wurde nicht gespeichert!");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    QJsonArray jsonArray;

    //Bei 1 Starten da das DEBUG Produkt beim Programm start geschrieben wird
    for(quint64 i = 1; i <= speicher.anzahlProdukte(); i++)
    {
        QJsonObject jsonObject;
        jsonObject["artNr"] = static_cast<int>(produkte[i].getArtnr());
        jsonObject["preisInCent"] = static_cast<qint64>(produkte[i].getPreisInCent());
        jsonObject["name"] = produkte[i].getName();
        jsonObject["info"] = produkte[i].getInfo();
        jsonObject["mwstIndex"] = speicher.mwstUmwandelnIndexMwst(produkte[i].getMwst());


        jsonArray.append(jsonObject);
    }

    QJsonDocument jsonDocument;
    jsonDocument.setArray(jsonArray);

    pfad.write(jsonDocument.toJson());
    pfad.close();

    QMessageBox box;
    box.setWindowTitle("Info");
    box.setText("Die Produkte wurde (extern) gespeichert");
    box.setIcon(QMessageBox::Information);
    box.addButton("Ok", QMessageBox::AcceptRole);
    box.exec();


}

void NeusProdukt::abbrechen()
{
    if(!sicherheitesFrageUngespeichert(3))
    {
        return;
    }
    else
    {
        QMessageBox info;
        info.setWindowTitle("Info");
        info.setText("Die Änderungen wurden nur gespeichert so lange das Programm läuft.\nDas heißt beim nächsten Programmstart sind die Änderungen/Erweiterungen nicht mehr vorhanden.");
        info.addButton(QMessageBox::Yes);
        info.addButton(QMessageBox::No);
        info.setIcon(QMessageBox::Information);

        info.button(QMessageBox::Yes)->setText("Verstanden");
        info.button(QMessageBox::No)->setText("Abbrechen");

        if(info.exec() == QMessageBox::Yes)
        {
            close();
        }
        else
        {
            return;
        }


    }
}
