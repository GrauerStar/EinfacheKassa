#ifndef NEUSPRODUKT_H
#define NEUSPRODUKT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "speicher.h"

namespace Ui {
class NeusProdukt;
}

class NeusProdukt : public QDialog
{
    Q_OBJECT

public:
    explicit NeusProdukt(QWidget *parent = nullptr);
    ~NeusProdukt();

private:
    Ui::NeusProdukt *ui;
    Speicher& speicher = Speicher::instance();

    //Speichert wenn änderungen gemacht werden die nicht gespeichert werden
    quint8 aenderungenNichtGespeichert;
    bool abfrageAenderungen(quint8 frage);


private slots:
    void maxProduktSetzen();
    void naechstesProdukt();
    void vorherigesProdukt();
    void aktuellesProduktSetzen(quint64 wert);
    bool aktuelleProduktPruefen(quint64 aktuellesProdukt);
    void produkDatenSetzen(quint64 wert);
    bool sicherheitesFrageUngespeichert(quint8 frage);
    void speichern();
    void gehZuArtNrAbfrage();
    void springZuProdukt(quint64 indexProduktListe);

public slots:
    void closeEvent(QCloseEvent *event);

};

#endif // NEUSPRODUKT_H
