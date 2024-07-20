#ifndef NEUSPRODUKT_H
#define NEUSPRODUKT_H

#include <QDialog>
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


private slots:
    void maxProduktSetzen();
    void naechstesProdukt();
    void vorherigesProdukt();
    void aktuellesProduktSetzen(quint64 wert);
    bool aktuelleProduktPruefen(quint64 aktuellesProdukt);
    void produkDatenSetzen(quint64 wert);

};

#endif // NEUSPRODUKT_H
