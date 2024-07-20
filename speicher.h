#ifndef SPEICHER_H
#define SPEICHER_H

#include <QList>


#include "produkt.h"


class Produkt;

class Speicher
{
public:
    //Funktionen
    void addProdukt(Produkt &produkt);


    //Getter und Setter
    static Speicher& instance();
    QList<Produkt>& getProdukte();
    quint64 anzahlProdukte();

    static quint8 getMwstIndex();
    static const quint8* getMwst();
    quint8 mwstUmwandelnIndexMwst(quint8 wert);     //wandelt den wert der eingegeben wurde in die Index von der Combobox um wenn er vorhanden ist ansonsten wir 0 zurück gegeben





    quint64 aktuellesProdukt() const;
    quint64 aktuellesProduktVisuell() const;
    void setAktuellesProdukt(quint64 newAktuelleProdukt);


private:
    Speicher();
    ~Speicher();

    Speicher(const Speicher&) = delete;
    Speicher& operator=(const Speicher&) = delete;


    static const quint8 mwst[];
    static const quint8 mwstIndex;


    QList<Produkt> m_produkte;

    quint64 m_aktuellesProdukt;



};

#endif // SPEICHER_H
