#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    adjustTables();
    ui->NProcesosQSB->clear();

    srand(time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Aceptar_clicked()
{
    if(ui->NProcesosQSB->value()<=0 || ui->NProcesosQSB->text().length()<=0)
    {
        message.setText("Ingresa un número de procesos válido."
                        " Intentálo de nuevo.");
        message.setIcon(QMessageBox::Critical);
        message.setWindowTitle("¡Error!");
        message.setWindowIcon(QIcon(":/images/cancelar.png"));
        message.exec();
    }
    else
    {
        message.setText("Generando información de los procesos.");
        message.setIcon(QMessageBox::Information);
        message.setWindowTitle("Por favor espere.");
        message.setWindowIcon(QIcon(":/images/comprobar.png"));
        message.exec();
        generateData();
    }
}

void MainWindow::generateData()
{
    for (int i=0; i < ui->NProcesosQSB->value(); ++i)
    {
        aux.setIdProceso(i+1);
        if(i%4==0 && i>0)
        {
            lote++;
        }
        aux.setLote(lote);
        aux.setTiempoMaximo(TME());
        setOperation();
        aux.setTiempoTranscurrido(0);
        Procesos.push_back(aux);
    }
    delay();
    ui->MainQSW->setCurrentIndex(1);
    this->grabKeyboard();
    Proceesing();
}

int MainWindow::TME()
{
    return 6+rand()%(16-6);
}

void MainWindow::setOperation()
{
    int opera, op1, op2;

    //Asignar valores aleatorios.
    opera = randomNumbers(0,4);
    //Comprobar rango de valores válidos para la operación.
    if(operaciones[opera]=="%" || operaciones[opera]=="/")
    {
        op2 = randomNumbers(1,100);
    }
    else
    {
        op2 = randomNumbers(0,100);
    }
    op1 = randomNumbers(0,100);

    //Asignación de resultado de la operación.
    if(operaciones[opera]=="+")
    {
        aux.setResultado(op1+op2);
    }
    else if(operaciones[opera]=="-")
    {
        aux.setResultado(op1-op2);
    }
    else if(operaciones[opera]=="*")
    {
        aux.setResultado(op1*op2);
    }
    else if(operaciones[opera]=="/")
    {
        aux.setResultado((float)op1/(float)op2);
    }
    else
    {
        aux.setResultado(op1%op2);
    }
    //Guardar el formato de la operación.
    aux.setOperacion(QString::number(op1) + " " + operaciones[opera] + " " + QString::number(op2));
}

int MainWindow::randomNumbers(int x, int y)
{
    return x+rand()%(y+1-x);
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_I)
    {
        if(activate)
        {
            aux2.setInterrumpido(true);
        }
    }
    else if(ev->key()==Qt::Key_W)
    {
        if(activate)
        {
            aux2.setError(true);
        }
    }
    else if(ev->key()==Qt::Key_P)
    {
        activate = false;
        while(!activate)
        {
            delay();
        }
    }
    else if(ev->key()==Qt::Key_C)
    {
        activate = true;
    }
}

void MainWindow::clearExec()
{
    ui->IDActualQLE->clear();
    ui->OperacionActualQLE->clear();
    ui->TMEActualQLE->clear();
    ui->TiempoRestanteQLE->clear();
    ui->TiempoTranscurridoQLE->clear();
}

void MainWindow::adjustTables()
{
    ui->PendientesQTV->setColumnWidth(0,80);
    ui->PendientesQTV->setColumnWidth(1,80);
    ui->PendientesQTV->setColumnWidth(2,80);
    ui->ProcTerminadosQTW->setColumnWidth(0,80);
}

void MainWindow::Proceesing()
{
    bool continueLoop = true;
    while(true)
    {
        ui->NoLotesPendientesQLE->setText(QString::number(lote-1));
        for (int i =0; i<4 ;++i)
        {
            Pendientes.push_back(Procesos.front());
            Procesos.erase(Procesos.begin());
            if(Procesos.empty())
            {
                continueLoop = false;
                break;
            }
        }
        lote--;
        showData();
        if(!continueLoop)
        {
            break;
        }
    }
    message.setText("El programa ha terminado");
    message.setIcon(QMessageBox::Information);
    message.setWindowTitle("¡Listo!");
    message.setWindowIcon(QIcon(":/images/comprobar.png"));
    message.exec();
}

void MainWindow::populateFinished()
{
    ui->ProcTerminadosQTW->clearSpans();
    ui->ProcTerminadosQTW->setRowCount(Terminados.size());
    for (size_t i =0; i<Terminados.size(); ++i)
    {
        aux=Terminados[i];
        QTableWidgetItem *ID = new QTableWidgetItem(QString::number(aux.getIdProceso()));
        QTableWidgetItem *Operacion = new QTableWidgetItem(aux.getOperacion());
        QTableWidgetItem *Resultado;
        if(aux.getError())
        {
            Resultado = new QTableWidgetItem("Error");
        }
        else
        {
            Resultado = new QTableWidgetItem(QString::number(aux.getResultado()));
        }
        QTableWidgetItem *Lote = new QTableWidgetItem(QString::number(aux.getLote()));
        ui->ProcTerminadosQTW->setItem(i,0,ID);
        ui->ProcTerminadosQTW->setItem(i,1,Operacion);
        ui->ProcTerminadosQTW->setItem(i,2,Resultado);
        ui->ProcTerminadosQTW->setItem(i,3,Lote);
    }
}

void MainWindow::populatePendingTable()
{
    ui->PendientesQTV->setRowCount(Pendientes.size());
    for (size_t i =0; i<Pendientes.size() ; ++i)
    {
        aux = Pendientes[i];
        QTableWidgetItem *TME = new QTableWidgetItem(QString::number(aux.getTiempoMaximo()));
        QTableWidgetItem *ID = new QTableWidgetItem(QString::number(aux.getIdProceso()));
        QTableWidgetItem *TT = new QTableWidgetItem(QString::number(aux.getTiempoTranscurrido()));

        ui->PendientesQTV->setItem(i,0,ID);
        ui->PendientesQTV->setItem(i,1,TME);
        ui->PendientesQTV->setItem(i,2,TT);
    }
}

void MainWindow::showData()
{
    while(!Pendientes.empty())
    {
        populatePendingTable();
        delay();

        aux2 = Pendientes.front();
        Pendientes.erase(Pendientes.begin());

        ui->PendientesQTV->clearSpans();
        populatePendingTable();

        ui->IDActualQLE->setText(QString::number(aux2.getIdProceso()));
        ui->OperacionActualQLE->setText(aux2.getOperacion());
        ui->TMEActualQLE->setText(QString::number(aux2.getTiempoMaximo()));

        aux2.setInterrumpido(false);
        for (int i =1+aux2.getTiempoTranscurrido(); i <= aux2.getTiempoMaximo() ; ++i )
        {
            if(!aux2.getInterrumpido() && !aux2.getError())
            {
                ui->TiempoRestanteQLE->setText(QString::number(aux2.getTiempoMaximo()-i));
                ui->TiempoTranscurridoQLE->setText(QString::number(i));
                ui->ContadorQLE->setText(QString::number(contador++));
                delay();
            }
            else
            {
                aux2.setTiempoTranscurrido(i-1);
                break;
            }
        }
        if(aux2.getInterrumpido())
        {
            Pendientes.push_back(aux2);
        }
        else
        {
            Terminados.push_back(aux2);
            populateFinished();
        }
        clearExec();
        ui->PendientesQTV->clearSpans();
    }
}

void MainWindow::delay()
{
    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

