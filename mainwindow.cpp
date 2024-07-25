#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Produkte laden (sollte zuerst passieren)
    speicher.importJsonProdukte();

    ui->setupUi(this);
    //Knöpfe verbinden
    connect(ui->actionProdukt_hinzuf_gen, SIGNAL(triggered()), this, SLOT(fensterNeusProdukt() ));




    //Tabellen setup
    QStringList tabelleUeBerschriftenListe = {"ArtNr","Menge","Bezeichnung","€","Preis €"};
    ui->tableWidget_ProdukteZumVerkauf->setColumnCount(tabelleUeBerschriftenListe.size());
    ui->tableWidget_ProdukteZumVerkauf->setHorizontalHeaderLabels(tabelleUeBerschriftenListe);



    ui->tableWidget_ProdukteZumVerkauf->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableWidget_ProdukteZumVerkauf->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableWidget_ProdukteZumVerkauf->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->tableWidget_ProdukteZumVerkauf->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->tableWidget_ProdukteZumVerkauf->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);



    // TODO
    QFontMetrics metrics_artnr(ui->tableWidget_ProdukteZumVerkauf->font());
    // Setze die Breite für 5 Artnr
    int breiteArtnr = metrics_artnr.horizontalAdvance("XXXXX");
    ui->tableWidget_ProdukteZumVerkauf->setColumnWidth(0, breiteArtnr);

    QFontMetrics metrics_preis(ui->tableWidget_ProdukteZumVerkauf->font());
    // Setze die Breite für 5 Artnr
    int breitePreisGes = metrics_preis.horizontalAdvance("XX.XXX,XX");
    ui->tableWidget_ProdukteZumVerkauf->setColumnWidth(4, breitePreisGes);
    ui->tableWidget_ProdukteZumVerkauf->setColumnWidth(3, breitePreisGes);

    hinzufuegenLeereZeile();


    //Tabelle verbinden
    connect(ui->tableWidget_ProdukteZumVerkauf, SIGNAL(cellChanged(int,int)), this, SLOT(beiCellChanged(int,int)));




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::fensterNeusProdukt()
{
    NeusProdukt nP(this);
    nP.setWindowTitle("Produkte Bearbeiten");
    nP.exec();
    return;
}

void MainWindow::hinzufuegenLeereZeile()
{
    int reihe = ui->tableWidget_ProdukteZumVerkauf->rowCount();
    ui->tableWidget_ProdukteZumVerkauf->insertRow(reihe);

    // Erstelle und setze die Zellen
    for (int spalte = 0; spalte < 4; ++spalte) {
        QTableWidgetItem *item = new QTableWidgetItem();
        if (spalte != 0 && spalte != 1) { // Nur ARTNr und Menge sollen bearbeitbar sein
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
        ui->tableWidget_ProdukteZumVerkauf->setItem(reihe, spalte, item);
    }

    ui->tableWidget_ProdukteZumVerkauf->editItem(ui->tableWidget_ProdukteZumVerkauf->item(reihe, 0)); // Startet die Bearbeitung der ARTNr-Zelle



}

void MainWindow::beiCellChanged(int reihe, int spalte)
{

    QTableWidgetItem tempItem;

    if(spalte == 0) // Überprüfe, ob die ARTNr-Spalte geändert wurde
    {
        QTableWidgetItem *item = ui->tableWidget_ProdukteZumVerkauf->item(reihe, spalte);
        if (!item) {
            return;
        }

        QString artNr = item->text();
        if (artNr.isEmpty()) {
            return;
        }

        if(speicher.sucheArtNr(artNr.toUInt()) == 0)
        {
            QMessageBox msgBox;
            msgBox.setText("Produkt nicht gefunden!");
            msgBox.setWindowTitle("ArtNr unbekannt");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.addButton(QMessageBox::Ok);
            msgBox.exec();
            ui->tableWidget_ProdukteZumVerkauf->setCurrentItem(item);
            //ui->tableWidget_ProdukteZumVerkauf->editItem(ui->tableWidget_ProdukteZumVerkauf->item(reihe, 0));
            return;
        }

        // Hier muss die Methode zum Suchen des Produkts basierend auf deiner bestehenden Code-Struktur implementiert werden.
        QList<Produkt> pL = speicher.getProdukte();
        quint64 index = speicher.sucheArtNr(artNr.toUInt());

        Produkt produkt = pL[index]; // Beispielhafte Methode zur Produktsuche


        ui->tableWidget_ProdukteZumVerkauf->setItem(reihe, 2, new QTableWidgetItem(produkt.getName()));
        ui->tableWidget_ProdukteZumVerkauf->setItem(reihe, 3, new QTableWidgetItem(produkt.getPreisAsString()));


        //Checkt ob die Reihe Neu ist oder bestehend
        //wenn Neu dann:
        if(ui->tableWidget_ProdukteZumVerkauf->rowCount() == reihe + 1)
        {
            QDialog dialog;
            QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
            QLineEdit *mengeLineEdit = new QLineEdit(&dialog);

            dialog.setWindowTitle("Menge eingeben");

            QLabel *label = new QLabel("Bitte geben Sie Anzahl der Produkte ein:");
            mainLayout->addWidget(label);
            mainLayout->addWidget(mengeLineEdit);

            QHBoxLayout *buttonLayout = new QHBoxLayout();
            QPushButton *okButton = new QPushButton("Ok", &dialog);
            QPushButton *cancelButton = new QPushButton("Abbruch", &dialog);

            buttonLayout->addWidget(okButton);
            buttonLayout->addWidget(cancelButton);

            mainLayout->addLayout(buttonLayout);

            QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
            QObject::connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
            int auswahl = 0;

            // Die Funktion muss noch angepasst werden, die ARTN muss geprüft werden und anschließend muss er auf das Aktuelle Produkt lt Index gesetzt werden
            while(mengeLineEdit->text().isEmpty() || mengeLineEdit->text().toUInt() <= 0)
            {
                mengeLineEdit->clear();
                auswahl = dialog.exec();
            }

            if(auswahl == QDialog::Accepted) {
                //Menge als String einfügen
                ui->tableWidget_ProdukteZumVerkauf->setItem(reihe, 1, new QTableWidgetItem(mengeLineEdit->text()));

            }
            else
            {
                return;
            }

            hinzufuegenLeereZeile();
            //Setzt den Cursor auf die neue Reihe um die ArtNr gleich direkt einzugeben
            ui->tableWidget_ProdukteZumVerkauf->setCurrentItem(ui->tableWidget_ProdukteZumVerkauf->item(reihe +1 , 0));

        }

        //Gesamte Preis setzen
        QTableWidgetItem *itemMenge = ui->tableWidget_ProdukteZumVerkauf->item(reihe,1);
        ui->tableWidget_ProdukteZumVerkauf->setItem(reihe, 4, new QTableWidgetItem(speicher.preisUmwandelnAlsString(produkt.getPreisInCent() * itemMenge->text().toUInt()   )));

    }

    gesammtePreisInEuroBerechnenUndSetzen();
    return;
}

void MainWindow::gesammtePreisInEuroBerechnenUndSetzen()
{
    quint64 gesamtePreisInCent = 0;

    for (int i = 0; i < ui->tableWidget_ProdukteZumVerkauf->rowCount(); ++i) {
        QTableWidgetItem *item = ui->tableWidget_ProdukteZumVerkauf->item(i, 4);
        if(item)
        {
            gesamtePreisInCent += speicher.preisUmwandelnAlsCentrbetrag(item->text());
        }
    }

    QFont schriftart;
    schriftart.setBold(true);
    schriftart.setPointSize(16);

    ui->label_PreisGesammtRechtsUnten->setText(speicher.preisUmwandelnAlsString(gesamtePreisInCent));
    ui->label_PreisGesammtRechtsUnten->setFont(schriftart);
    return;
}

