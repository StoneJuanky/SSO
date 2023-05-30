#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include <QString>
#include <vector>
//Utilidades.
#include <QMessageBox>
#include <QTime>
#include <QDebug>
//Números aleatorios
#include <time.h>
#include <stdlib.h>
//Para las interrupciones
#include <QKeyEvent>
#include <QEvent>

#include "proceso.h"

using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Aceptar_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    void clearExec();
    void adjustTables();
    void Proceesing();
    void populateFinished();
    void populatePendingTable();
    void showData();
    void delay();
    void generateData();
    int TME();
    void setOperation();
    int randomNumbers(int x, int y);
    bool bandera, activate = false;


    QString operaciones[5] = {"+", "-", "*", "/", "%"};
    QMessageBox message;
    vector <Proceso> Procesos, Pendientes, Terminados;

    Proceso aux, aux2;

    int lote = 1;
    int contador = 1;

};
#endif // MAINWINDOW_H

