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
        aux.setTiempoMaximo(TME());
        setOperation();
        aux.setTiempoTranscurrido(0);
        Procesos.push_back(aux);
    }
    delay();
    ui->MainQSW->setCurrentIndex(1);
    this->grabKeyboard();
    Processing();
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
    if(ev->key()==Qt::Key_E)
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
    ui->BloqueadosQTW->setColumnWidth(0,80);
    ui->BloqueadosQTW->setColumnWidth(1,80);
}

void MainWindow::Processing()
{
    for (int i =0; i<4 ;++i)
    {
        //Los primeros 4 procesos llegan en el tiempo 0.
        aux3 = Procesos.front();
        aux3.setTLlegada(contador-1);

        Pendientes.push_back(aux3);
        Procesos.erase(Procesos.begin());
    }
    showData();
    message.setText("El programa ha terminado. "
                    "Puedes ver los tiempos haciendo clic en el botón "
                    "'Ver Tiempos' que está en la parte superior derecha.");
    message.setIcon(QMessageBox::Information);
    message.setWindowTitle("¡Listo!");
    message.setWindowIcon(QIcon(":/images/comprobar.png"));
    message.exec();
    calculateTimes();
    ui->VerTiemposQPB->setEnabled(true);
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
        ui->ProcTerminadosQTW->setItem(i,0,ID);
        ui->ProcTerminadosQTW->setItem(i,1,Operacion);
        ui->ProcTerminadosQTW->setItem(i,2,Resultado);
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

void MainWindow::populateBlocked()
{
    ui->BloqueadosQTW->clearSpans();
    ui->BloqueadosQTW->setRowCount(Bloqueados.size());
    for (size_t i =0; i<Bloqueados.size(); ++i)
    {
        aux3=Bloqueados[i];
        if(Bloqueados[i].getTBloqueado()>=7)
        {
            Bloqueados[i].setTBloqueado(0);
            Pendientes.push_back(Bloqueados[i]);
            ui->BloqueadosQTW->removeRow(i);
            populatePendingTable();
            Bloqueados.erase(Bloqueados.begin()+i);
        }
        aux3=Bloqueados[i];
        QTableWidgetItem *ID = new QTableWidgetItem(QString::number(aux3.getIdProceso()));
        QTableWidgetItem *TiempoBloqueado = new QTableWidgetItem(QString::number(aux3.getTBloqueado()+1));
        ui->BloqueadosQTW->setItem(i,0,ID);
        ui->BloqueadosQTW->setItem(i,1,TiempoBloqueado);
        Bloqueados[i].aumentarTBloq();
    }
}

void MainWindow::showData()
{
    while(Pendientes.size() + Bloqueados.size()>0)
    {
        populatePendingTable();
        delay();
        ui->NoProcPendientesQLE->setText(QString::number(Procesos.size()));

        if(!Pendientes.empty())
        {
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
                if(aux2.getEjecutado()==false)
                {
                    aux2.setEjecutado(true);
                    aux2.setTRes((contador-aux2.getTLlegada())-1);
                }
                if(!aux2.getInterrumpido() && !aux2.getError())
                {
                    ui->TiempoRestanteQLE->setText(QString::number(aux2.getTiempoMaximo()-i));
                    ui->TiempoTranscurridoQLE->setText(QString::number(i));
                    ui->ContadorQLE->setText(QString::number(contador++));
                    if(Bloqueados.size()>0)
                    {
                        populateBlocked();
                    }
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
                Bloqueados.push_back(aux2);
            }
            else
            {
                aux2.setTFin(contador);
                Terminados.push_back(aux2);
                populateFinished();
            }
        }
        else
        {
            populateBlocked();
            if(Pendientes.empty())
            {
                ui->ContadorQLE->setText(QString::number(contador++));
            }
        }
        ui->PendientesQTV->clearSpans();
        clearExec();
        if(Pendientes.size()+Bloqueados.size()+1<=4)
        {
            if(!Procesos.empty())
            {
                aux3=Procesos.front();
                aux3.setTLlegada(contador-1);
                Pendientes.push_back(aux3);
                Procesos.erase(Procesos.begin());
            }
        }
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

void MainWindow::calculateTimes()
{
    ui->TiemposQTW->clearSpans();
    ui->TiemposQTW->setRowCount(Terminados.size());
    ui->TiemposQTW->setColumnWidth(0,40);
    for (size_t i =0; i < Terminados.size(); ++i)
    {
        aux = Terminados[i];
        aux.setTRet(aux.getTFin()-aux.getTLlegada());
        if(aux.getError())
        {
            aux.setTSer(aux.getTiempoTranscurrido());
        }
        else
        {
            aux.setTSer(aux.getTiempoMaximo());
        }
        aux.setTEsp(aux.getTRet()-aux.getTSer());

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
        QTableWidgetItem *TLlegada = new QTableWidgetItem(QString::number(aux.getTLlegada()));
        QTableWidgetItem *TFin = new QTableWidgetItem(QString::number(aux.getTFin()));
        QTableWidgetItem *TRetorno = new QTableWidgetItem(QString::number(aux.getTRet()));
        QTableWidgetItem *TRespuesta = new QTableWidgetItem(QString::number(aux.getTRes()));
        QTableWidgetItem *TEspera = new QTableWidgetItem(QString::number(aux.getTEsp()));
        QTableWidgetItem *TServicio = new QTableWidgetItem(QString::number(aux.getTSer()));

        ui->TiemposQTW->setItem(i,0,ID);
        ui->TiemposQTW->setItem(i,1,Operacion);
        ui->TiemposQTW->setItem(i,2,Resultado);
        ui->TiemposQTW->setItem(i,3,TLlegada);
        ui->TiemposQTW->setItem(i,4,TFin);
        ui->TiemposQTW->setItem(i,5,TRetorno);
        ui->TiemposQTW->setItem(i,6,TRespuesta);
        ui->TiemposQTW->setItem(i,7,TEspera);
        ui->TiemposQTW->setItem(i,8,TServicio);

    }

}

void MainWindow::on_VerTiemposQPB_clicked()
{
    ui->MainQSW->setCurrentIndex(2);
}


