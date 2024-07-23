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

void Speicher::importJsonProdukte()
{
    QString datenPfad = m_DataPfad + m_DateiNameProdukte;
    QFile datei(datenPfad);
    QString fehlermeldungString;
    QJsonDocument jsonDoc;
    QJsonObject jsonObj;
    QJsonArray jsonArray;
    QJsonValue jsonValue;
    QMessageBox box;

    Produkt p;

    box.setWindowTitle("Fehler");
    box.setIcon(QMessageBox::Critical);
    box.addButton(QMessageBox::Ok);



    if(!datei.open(QFile::ReadOnly))
    {
        fehlermeldungString = "Die Produkte konnten nicht geladen werden!\n" + datenPfad;
        box.setText(fehlermeldungString);
        box.exec();
        return;
    }
    else
    {
        jsonDoc = QJsonDocument::fromJson(datei.readAll());
        datei.close();
        if(!jsonDoc.isArray())
        {
            box.setText("Die Produkte konnten nicht geladen werden! Die Datei ist keine Json Array Datei!");
            box.exec();
            return;
        }

        jsonArray = jsonDoc.array();

        for(int i = 0; i < jsonArray.size(); ++i)
        {
            const QJsonValue & value = jsonArray[i];
            if(!value.isObject())
            {
                fehlermeldungString ="Ein Element im Array hat einen Fehler!\nBei dem Produkt Nummer: " + QString::number(i);
                box.setText(fehlermeldungString);
                box.exec();
                continue;
            }

            jsonObj = value.toObject();



            // quint32 pr_artnr = static_cast<quint32>(jsonObj["artnr"].toInt());
            // quint64 pr_preisInCent = static_cast<quint64>(jsonObj["preisInCent"].toDouble());
            // QString pr_name = jsonObj["name"].toString();
            // QString pr_info = jsonObj["info"].toString();
            // qint8 pr_mwst = mwst[static_cast<qint8>(jsonObj["mwst"].toInt())];

            quint32 pr_artnr = jsonObj["artNr"].toInt();
            quint64 pr_preisInCent = jsonObj["preisInCent"].toInt();
            QString pr_name = jsonObj["name"].toString();
            QString pr_info = jsonObj["info"].toString();
            qint8 pr_mwst = mwst[static_cast<qint8>(jsonObj["mwstIndex"].toInt())];


            p.setArtnr(pr_artnr);
            p.setPreisInCent(pr_preisInCent);
            p.setName(pr_name);
            p.setInfo(pr_info);
            p.setMwst(pr_mwst);

            m_produkte.append(p);

        }

    }


}
