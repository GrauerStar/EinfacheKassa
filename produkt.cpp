#include "produkt.h"

Produkt::Produkt(quint32 artnr, quint64 preisInCent, QString name, QString info, qint8 mwst)
    :artnr(artnr), preisInCent(preisInCent), name(name), info(info), mwst(mwst)
{

}





//getter und setter
quint32 Produkt::getArtnr() const
{
    return artnr;
}

void Produkt::setArtnr(quint32 newArtnr)
{
    artnr = newArtnr;
}

quint64 Produkt::getPreisInCent() const
{
    return preisInCent;
}

void Produkt::setPreisInCent(quint64 newPreisInCent)
{
    preisInCent = newPreisInCent;
}

QString Produkt::getName() const
{
    return name;
}

void Produkt::setName(const QString &newName)
{
    name = newName;
}

QString Produkt::getInfo() const
{
    return info;
}

void Produkt::setInfo(const QString &newInfo)
{
    info = newInfo;
}

qint8 Produkt::getMwst() const
{
    return mwst;
}

void Produkt::setMwst(qint8 newMwst)
{
    mwst = newMwst;
}


QString Produkt::getPreisAsString() const
{
    return QString::number(preisInCent / 100) + "," + QString::number(preisInCent % 100);
}
