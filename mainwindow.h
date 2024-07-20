#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "produkt.h"
#include "speicher.h"
#include "neusprodukt.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Speicher& speicher = Speicher::instance();


private slots:
    void fensterNeusProdukt();

};
#endif // MAINWINDOW_H
