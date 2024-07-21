#include "speicher.h"

const quint8 Speicher::mwst[] = {10,13,20};
const quint8 Speicher::mwstIndex = sizeof(mwst)/sizeof(mwst[0]);


Speicher::Speicher()
{

}

QString Speicher::DataPfad() const
{
    return m_DataPfad;
}

void Speicher::setDataPfad(const QString &newDataPfad)
{
    m_DataPfad = newDataPfad;
}


QString Speicher::DateiNameProdukte() const
{
    return m_DateiNameProdukte;
}

quint64 Speicher::aktuellesProdukt() const
{
    return m_aktuellesProdukt;
}

quint64 Speicher::aktuellesProduktVisuell() const
{
    return m_aktuellesProdukt + 1;
}

void Speicher::setAktuellesProdukt(quint64 newAktuelleProdukt)
{
    m_aktuellesProdukt = newAktuelleProdukt;
}



Speicher::~Speicher()
{

}





Speicher &Speicher::instance()
{
    static Speicher instance;
    return instance;
}

void Speicher::addProdukt(Produkt &produkt)
{
    m_produkte.append(produkt);
}

QList<Produkt> &Speicher::getProdukte()
{
    return m_produkte;
}

QList<Produkt> *Speicher::getProduktePointer()
{
    return &m_produkte;
}

quint64 Speicher::anzahlProdukte()
{
    //-1 weil 0 das Debug ist
    return m_produkte.size() -1 ;
}

const quint8* Speicher::getMwst()
{
    return mwst;
}

quint8 Speicher::getMwstIndex()
{
    return mwstIndex;
}




//Funktionen:

quint8 Speicher::mwstUmwandelnIndexMwst(quint8 wert)
{
    for(int i = 0; i < mwstIndex; i++)
    {
        if(wert == mwst[i])
        {
            return i;
        }
    }
    return 0;
}

quint64 Speicher::sucheArtNr(quint64 artnr)
{
    for(int i = 0; i < m_produkte.size(); i++)
    {
        if(m_produkte[i].getArtnr() == artnr)
        {
            return i;
        }
    }
    return 0;
}
