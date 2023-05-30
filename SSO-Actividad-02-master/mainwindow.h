#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <vector>

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
    void on_Aceptar_Botton_clicked();

    void on_CapturaProceso_Botton_clicked();

private:
    Ui::MainWindow *ui;
    void setProcesses(int number);
    void enableProcessesDataIngress();
    void validator();
    void clear();
    void clearExec();
    void assigneData(int noLote);
    void adjustTables();
    void Proceesing();
    void populateFinished();
    void populatePendingTable();
    void showData();
    void delay();

    QMessageBox message;
    QList <int> idEnUso;
    vector <Proceso> Procesos,Pendientes, Terminados;

    Proceso aux, aux2;

    int lote = 1;
    int procesos = 0;
    int contador = 1;
};
#endif // MAINWINDOW_H
