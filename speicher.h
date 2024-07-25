#ifndef SPEICHER_H
#define SPEICHER_H

#include <QList>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include <QMessageBox>


#include "produkt.h"


class Produkt;

class Speicher
{
public:
    //Sicherheitscode
    quint64 SpeicherSicherheitscode = 1306;

    //Funktionen
    void addProdukt(Produkt &produkt);
    quint64 sucheArtNr(quint64 artnr);
    quint8 mwstUmwandelnIndexMwst(quint8 wert);     //wandelt den wert der eingegeben wurde in die Index von der Combobox um wenn er vorhanden ist ansonsten wir 0 zurück gegeben

    void importJsonProdukte();


    QString preisUmwandelnAlsString(quint64 preisInCent);
    quint64 preisUmwandelnAlsCentrbetrag(QString preisAlsString);


    //Getter und Setter
    static Speicher& instance();
    QList<Produkt>& getProdukte();
    QList<Produkt>* getProduktePointer();
    quint64 anzahlProdukte();

    static quint8 getMwstIndex();
    static const quint8* getMwst();


    quint64 aktuellesProdukt() const;
    quint64 aktuellesProduktVisuell() const;
    void setAktuellesProdukt(quint64 newAktuelleProdukt);

    QString DateiNameProdukte() const;

    QString DataPfad() const;
    void setDataPfad(const QString &newDataPfad);

private:
    Speicher();
    ~Speicher();


    Speicher(const Speicher&) = delete;
    Speicher& operator=(const Speicher&) = delete;


    static const quint8 mwst[];
    static const quint8 mwstIndex;


    QList<Produkt> m_produkte;
    quint64 m_aktuellesProdukt = 1;
    QString m_DateiNameProdukte = "Produkte.json";
    QString m_DataPfad;




};

#endif // SPEICHER_H
