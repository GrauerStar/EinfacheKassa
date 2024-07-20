/********************************************************************************
** Form generated from reading UI file 'neusprodukt.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEUSPRODUKT_H
#define UI_NEUSPRODUKT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NeusProdukt
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_NeuesProduktHinzufuegen;
    QFrame *line_1;
    QHBoxLayout *horizontalLayout_TextAktuellesMaxProdukte;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_AktuellesProdukt;
    QLabel *label_1_slash;
    QLabel *label_AnzahlProdukte;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_ProduktAktuellundMax;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *lineEdit_aktuellesProdukt;
    QLabel *label_2_slash;
    QLineEdit *lineEdit_maxProdukte;
    QSpacerItem *horizontalSpacer_5;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_ProduktName;
    QLabel *label_ProduktName;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *lineEdit_ProduktName;
    QHBoxLayout *horizontalLayout_ArtNr;
    QLabel *label_ArtNr;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_ArtNr;
    QHBoxLayout *horizontalLayout_PreisInEuro;
    QLabel *label_PreisInEuro;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *lineEdit_PreisInEuro;
    QHBoxLayout *horizontalLayout_MwSt;
    QLabel *label_MwSt;
    QSpacerItem *horizontalSpacer_9;
    QComboBox *comboBox_MwSt;
    QFormLayout *formLayout_Info;
    QPlainTextEdit *plainTextEdit_Info;
    QLabel *label_9;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_ProduktAuswahl;
    QPushButton *pushButton_ErstesProdukt;
    QPushButton *pushButton_Vorher;
    QPushButton *pushButton_NeusProdukt;
    QPushButton *pushButton_Nachstes;
    QPushButton *pushButton_LetztesProdukt;
    QHBoxLayout *horizontalLayout_LoeschenSpeichern;
    QPushButton *pushButton_AllesLoeschen;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_Speichern;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_AbbrechenFertig;
    QPushButton *pushButton_Abbrechen;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Fertig;

    void setupUi(QDialog *NeusProdukt)
    {
        if (NeusProdukt->objectName().isEmpty())
            NeusProdukt->setObjectName("NeusProdukt");
        NeusProdukt->resize(452, 580);
        verticalLayout = new QVBoxLayout(NeusProdukt);
        verticalLayout->setObjectName("verticalLayout");
        label_NeuesProduktHinzufuegen = new QLabel(NeusProdukt);
        label_NeuesProduktHinzufuegen->setObjectName("label_NeuesProduktHinzufuegen");

        verticalLayout->addWidget(label_NeuesProduktHinzufuegen);

        line_1 = new QFrame(NeusProdukt);
        line_1->setObjectName("line_1");
        line_1->setFrameShape(QFrame::Shape::HLine);
        line_1->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_1);

        horizontalLayout_TextAktuellesMaxProdukte = new QHBoxLayout();
        horizontalLayout_TextAktuellesMaxProdukte->setObjectName("horizontalLayout_TextAktuellesMaxProdukte");
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_TextAktuellesMaxProdukte->addItem(horizontalSpacer_13);

        label_AktuellesProdukt = new QLabel(NeusProdukt);
        label_AktuellesProdukt->setObjectName("label_AktuellesProdukt");

        horizontalLayout_TextAktuellesMaxProdukte->addWidget(label_AktuellesProdukt);

        label_1_slash = new QLabel(NeusProdukt);
        label_1_slash->setObjectName("label_1_slash");

        horizontalLayout_TextAktuellesMaxProdukte->addWidget(label_1_slash);

        label_AnzahlProdukte = new QLabel(NeusProdukt);
        label_AnzahlProdukte->setObjectName("label_AnzahlProdukte");

        horizontalLayout_TextAktuellesMaxProdukte->addWidget(label_AnzahlProdukte);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_TextAktuellesMaxProdukte->addItem(horizontalSpacer_11);


        verticalLayout->addLayout(horizontalLayout_TextAktuellesMaxProdukte);

        horizontalLayout_ProduktAktuellundMax = new QHBoxLayout();
        horizontalLayout_ProduktAktuellundMax->setObjectName("horizontalLayout_ProduktAktuellundMax");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_ProduktAktuellundMax->addItem(horizontalSpacer_6);

        lineEdit_aktuellesProdukt = new QLineEdit(NeusProdukt);
        lineEdit_aktuellesProdukt->setObjectName("lineEdit_aktuellesProdukt");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_aktuellesProdukt->sizePolicy().hasHeightForWidth());
        lineEdit_aktuellesProdukt->setSizePolicy(sizePolicy);
        lineEdit_aktuellesProdukt->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_ProduktAktuellundMax->addWidget(lineEdit_aktuellesProdukt);

        label_2_slash = new QLabel(NeusProdukt);
        label_2_slash->setObjectName("label_2_slash");

        horizontalLayout_ProduktAktuellundMax->addWidget(label_2_slash);

        lineEdit_maxProdukte = new QLineEdit(NeusProdukt);
        lineEdit_maxProdukte->setObjectName("lineEdit_maxProdukte");
        sizePolicy.setHeightForWidth(lineEdit_maxProdukte->sizePolicy().hasHeightForWidth());
        lineEdit_maxProdukte->setSizePolicy(sizePolicy);
        lineEdit_maxProdukte->setReadOnly(true);

        horizontalLayout_ProduktAktuellundMax->addWidget(lineEdit_maxProdukte);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_ProduktAktuellundMax->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_ProduktAktuellundMax);

        line_2 = new QFrame(NeusProdukt);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_ProduktName = new QHBoxLayout();
        horizontalLayout_ProduktName->setObjectName("horizontalLayout_ProduktName");
        label_ProduktName = new QLabel(NeusProdukt);
        label_ProduktName->setObjectName("label_ProduktName");

        horizontalLayout_ProduktName->addWidget(label_ProduktName);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_ProduktName->addItem(horizontalSpacer_8);

        lineEdit_ProduktName = new QLineEdit(NeusProdukt);
        lineEdit_ProduktName->setObjectName("lineEdit_ProduktName");

        horizontalLayout_ProduktName->addWidget(lineEdit_ProduktName);


        verticalLayout->addLayout(horizontalLayout_ProduktName);

        horizontalLayout_ArtNr = new QHBoxLayout();
        horizontalLayout_ArtNr->setObjectName("horizontalLayout_ArtNr");
        label_ArtNr = new QLabel(NeusProdukt);
        label_ArtNr->setObjectName("label_ArtNr");

        horizontalLayout_ArtNr->addWidget(label_ArtNr);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_ArtNr->addItem(horizontalSpacer);

        lineEdit_ArtNr = new QLineEdit(NeusProdukt);
        lineEdit_ArtNr->setObjectName("lineEdit_ArtNr");

        horizontalLayout_ArtNr->addWidget(lineEdit_ArtNr);


        verticalLayout->addLayout(horizontalLayout_ArtNr);

        horizontalLayout_PreisInEuro = new QHBoxLayout();
        horizontalLayout_PreisInEuro->setObjectName("horizontalLayout_PreisInEuro");
        label_PreisInEuro = new QLabel(NeusProdukt);
        label_PreisInEuro->setObjectName("label_PreisInEuro");

        horizontalLayout_PreisInEuro->addWidget(label_PreisInEuro);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_PreisInEuro->addItem(horizontalSpacer_7);

        lineEdit_PreisInEuro = new QLineEdit(NeusProdukt);
        lineEdit_PreisInEuro->setObjectName("lineEdit_PreisInEuro");

        horizontalLayout_PreisInEuro->addWidget(lineEdit_PreisInEuro);


        verticalLayout->addLayout(horizontalLayout_PreisInEuro);

        horizontalLayout_MwSt = new QHBoxLayout();
        horizontalLayout_MwSt->setObjectName("horizontalLayout_MwSt");
        label_MwSt = new QLabel(NeusProdukt);
        label_MwSt->setObjectName("label_MwSt");

        horizontalLayout_MwSt->addWidget(label_MwSt);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_MwSt->addItem(horizontalSpacer_9);

        comboBox_MwSt = new QComboBox(NeusProdukt);
        comboBox_MwSt->setObjectName("comboBox_MwSt");

        horizontalLayout_MwSt->addWidget(comboBox_MwSt);


        verticalLayout->addLayout(horizontalLayout_MwSt);

        formLayout_Info = new QFormLayout();
        formLayout_Info->setObjectName("formLayout_Info");
        plainTextEdit_Info = new QPlainTextEdit(NeusProdukt);
        plainTextEdit_Info->setObjectName("plainTextEdit_Info");

        formLayout_Info->setWidget(0, QFormLayout::FieldRole, plainTextEdit_Info);

        label_9 = new QLabel(NeusProdukt);
        label_9->setObjectName("label_9");

        formLayout_Info->setWidget(0, QFormLayout::LabelRole, label_9);


        verticalLayout->addLayout(formLayout_Info);

        line_3 = new QFrame(NeusProdukt);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout_ProduktAuswahl = new QHBoxLayout();
        horizontalLayout_ProduktAuswahl->setObjectName("horizontalLayout_ProduktAuswahl");
        pushButton_ErstesProdukt = new QPushButton(NeusProdukt);
        pushButton_ErstesProdukt->setObjectName("pushButton_ErstesProdukt");

        horizontalLayout_ProduktAuswahl->addWidget(pushButton_ErstesProdukt);

        pushButton_Vorher = new QPushButton(NeusProdukt);
        pushButton_Vorher->setObjectName("pushButton_Vorher");

        horizontalLayout_ProduktAuswahl->addWidget(pushButton_Vorher);

        pushButton_NeusProdukt = new QPushButton(NeusProdukt);
        pushButton_NeusProdukt->setObjectName("pushButton_NeusProdukt");

        horizontalLayout_ProduktAuswahl->addWidget(pushButton_NeusProdukt);

        pushButton_Nachstes = new QPushButton(NeusProdukt);
        pushButton_Nachstes->setObjectName("pushButton_Nachstes");

        horizontalLayout_ProduktAuswahl->addWidget(pushButton_Nachstes);

        pushButton_LetztesProdukt = new QPushButton(NeusProdukt);
        pushButton_LetztesProdukt->setObjectName("pushButton_LetztesProdukt");

        horizontalLayout_ProduktAuswahl->addWidget(pushButton_LetztesProdukt);


        verticalLayout->addLayout(horizontalLayout_ProduktAuswahl);

        horizontalLayout_LoeschenSpeichern = new QHBoxLayout();
        horizontalLayout_LoeschenSpeichern->setObjectName("horizontalLayout_LoeschenSpeichern");
        pushButton_AllesLoeschen = new QPushButton(NeusProdukt);
        pushButton_AllesLoeschen->setObjectName("pushButton_AllesLoeschen");

        horizontalLayout_LoeschenSpeichern->addWidget(pushButton_AllesLoeschen);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_LoeschenSpeichern->addItem(horizontalSpacer_4);

        pushButton_Speichern = new QPushButton(NeusProdukt);
        pushButton_Speichern->setObjectName("pushButton_Speichern");

        horizontalLayout_LoeschenSpeichern->addWidget(pushButton_Speichern);


        verticalLayout->addLayout(horizontalLayout_LoeschenSpeichern);

        line_4 = new QFrame(NeusProdukt);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_4);

        horizontalLayout_AbbrechenFertig = new QHBoxLayout();
        horizontalLayout_AbbrechenFertig->setObjectName("horizontalLayout_AbbrechenFertig");
        pushButton_Abbrechen = new QPushButton(NeusProdukt);
        pushButton_Abbrechen->setObjectName("pushButton_Abbrechen");

        horizontalLayout_AbbrechenFertig->addWidget(pushButton_Abbrechen);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_AbbrechenFertig->addItem(horizontalSpacer_2);

        pushButton_Fertig = new QPushButton(NeusProdukt);
        pushButton_Fertig->setObjectName("pushButton_Fertig");

        horizontalLayout_AbbrechenFertig->addWidget(pushButton_Fertig);


        verticalLayout->addLayout(horizontalLayout_AbbrechenFertig);


        retranslateUi(NeusProdukt);

        QMetaObject::connectSlotsByName(NeusProdukt);
    } // setupUi

    void retranslateUi(QDialog *NeusProdukt)
    {
        NeusProdukt->setWindowTitle(QCoreApplication::translate("NeusProdukt", "Dialog", nullptr));
        label_NeuesProduktHinzufuegen->setText(QCoreApplication::translate("NeusProdukt", "<html><head/><body><p align=\"center\">Neus Produkt hinzuf\303\274gen</p></body></html>", nullptr));
        label_AktuellesProdukt->setText(QCoreApplication::translate("NeusProdukt", "aktuelles Produkt ", nullptr));
        label_1_slash->setText(QCoreApplication::translate("NeusProdukt", "/", nullptr));
        label_AnzahlProdukte->setText(QCoreApplication::translate("NeusProdukt", "Anzahl  Produkte", nullptr));
        label_2_slash->setText(QCoreApplication::translate("NeusProdukt", "/", nullptr));
        label_ProduktName->setText(QCoreApplication::translate("NeusProdukt", "Produkt Name:", nullptr));
        label_ArtNr->setText(QCoreApplication::translate("NeusProdukt", "ArtkNr:", nullptr));
        label_PreisInEuro->setText(QCoreApplication::translate("NeusProdukt", "Preis in \342\202\254:", nullptr));
        label_MwSt->setText(QCoreApplication::translate("NeusProdukt", "MwSt:", nullptr));
        label_9->setText(QCoreApplication::translate("NeusProdukt", "Produkt Info:", nullptr));
        pushButton_ErstesProdukt->setText(QCoreApplication::translate("NeusProdukt", "Erstes Produkt", nullptr));
        pushButton_Vorher->setText(QCoreApplication::translate("NeusProdukt", "|<", nullptr));
        pushButton_NeusProdukt->setText(QCoreApplication::translate("NeusProdukt", "Neus Produkt", nullptr));
        pushButton_Nachstes->setText(QCoreApplication::translate("NeusProdukt", ">|", nullptr));
        pushButton_LetztesProdukt->setText(QCoreApplication::translate("NeusProdukt", "Letzes Produkt", nullptr));
        pushButton_AllesLoeschen->setText(QCoreApplication::translate("NeusProdukt", "Alles l\303\266schen", nullptr));
        pushButton_Speichern->setText(QCoreApplication::translate("NeusProdukt", "Speichern", nullptr));
        pushButton_Abbrechen->setText(QCoreApplication::translate("NeusProdukt", "Abbrechen", nullptr));
        pushButton_Fertig->setText(QCoreApplication::translate("NeusProdukt", "Fertig", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NeusProdukt: public Ui_NeusProdukt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEUSPRODUKT_H
