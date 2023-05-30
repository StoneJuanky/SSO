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

    void on_VerTiemposQPB_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    void clearExec();
    void adjustTables();
    void Processing();
    void populateFinished();
    void populatePendingTable();
    void populateBlocked();
    void showData();
    void delay();
    void calculateTimes();
    void generateData();
    int TME();
    void setOperation(Proceso &auxiliar);
    int randomNumbers(int x, int y);
    bool bandera = false;
    bool activate = true;
    bool exec = false;
    void createNew();
    void showPCB();
    bool maxAmmount();


    QString operaciones[5] = {"+", "-", "*", "/", "%"};
    QMessageBox message;
    vector <Proceso> Procesos, Pendientes, Terminados, Bloqueados;

    Proceso aux, aux2, aux3;

    int contador = 1, oe;
    int Quantum;
    bool Q = false;

};
#endif // MAINWINDOW_H
