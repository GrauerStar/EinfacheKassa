#ifndef PRODUKT_H
#define PRODUKT_H

#include <QString>


class Produkt
{
public:
    Produkt(quint32 artnr = 0, quint64 preisInCent = 0, QString name = "leer", QString info = "leer", qint8 mwst = 0);





    //getter und setter
    quint32 getArtnr() const;
    void setArtnr(quint32 newArtnr);

    quint64 getPreisInCent() const;
    void setPreisInCent(quint64 newPreisInCent);

    QString getName() const;
    void setName(const QString &newName);

    QString getInfo() const;
    void setInfo(const QString &newInfo);

    qint8 getMwst() const;
    void setMwst(qint8 newMwst);

    QString getPreisAsString() const;

private:
    quint32 artnr;
    quint64 preisInCent;
    QString name;
    QString info;
    qint8 mwst;

};

#endif // PRODUKT_H
