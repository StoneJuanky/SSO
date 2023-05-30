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
        setOperation(aux);
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

void MainWindow::setOperation(Proceso &auxiliar)
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
        auxiliar.setResultado(op1+op2);
    }
    else if(operaciones[opera]=="-")
    {
        auxiliar.setResultado(op1-op2);
    }
    else if(operaciones[opera]=="*")
    {
        auxiliar.setResultado(op1*op2);
    }
    else if(operaciones[opera]=="/")
    {
        auxiliar.setResultado((float)op1/(float)op2);
    }
    else
    {
        auxiliar.setResultado(op1%op2);
    }
    //Guardar el formato de la operación.
    auxiliar.setOperacion(QString::number(op1) + " " + operaciones[opera] + " " + QString::number(op2));
}

int MainWindow::randomNumbers(int x, int y)
{
    return x+rand()%(y+1-x);
}

void MainWindow::createNew()
{
    Proceso ax;
    ui->NProcesosQSB->setValue(ui->NProcesosQSB->value()+1);
    ax.setIdProceso(ui->NProcesosQSB->value());
    ax.setTiempoMaximo(TME());
    setOperation(ax);
    ax.setTiempoTranscurrido(0);

    if(maxAmmount())
    {
        ax.setTLlegada(contador-1);
        Pendientes.push_back(ax);
        populatePendingTable();
    }
    else
    {
        Procesos.push_back(ax);
        ui->NoProcPendientesQLE->setText(QString::number(Procesos.size()));
    }
}

void MainWindow::showPCB()
{
    ui->BCPQTW->clearSpans();
    ui->BCPQTW->setRowCount(ui->NProcesosQSB->value());
    size_t i = 0;

    QTableWidgetItem *ID;
    QTableWidgetItem *Estado;
    QTableWidgetItem *Operacion;
    QTableWidgetItem *Resultado;
    QTableWidgetItem *TLlegada;
    QTableWidgetItem *TFin;
    QTableWidgetItem *TRetorno;
    QTableWidgetItem *TRespuesta;
    QTableWidgetItem *TEspera;
    QTableWidgetItem *TServicio;
    QTableWidgetItem *TBloq;
    QTableWidgetItem *TRes;

    //Para el proceso en ejecución.
    aux = aux2;
    ID = new QTableWidgetItem(QString::number(aux.getIdProceso()));
    Estado = new QTableWidgetItem("Ejecución");
    Operacion = new QTableWidgetItem(aux.getOperacion());
    Resultado = new QTableWidgetItem("-");
    aux.setTSer(oe);
    aux.setTEsp((contador-aux.getTLlegada())-aux.getTSer());

    TLlegada = new QTableWidgetItem(QString::number(aux.getTLlegada()));
    TFin = new QTableWidgetItem("-");
    TRetorno = new QTableWidgetItem("-");
    TRespuesta = new QTableWidgetItem(QString::number(aux.getTRes()));
    TEspera = new QTableWidgetItem(QString::number(aux.getTEsp()));
    TServicio = new QTableWidgetItem(QString::number(aux.getTSer()));
    TBloq = new QTableWidgetItem("-");
    TRes = new QTableWidgetItem(QString::number(aux.getTiempoMaximo()-aux.getTSer()));

    ui->BCPQTW->setItem(i,0,ID);
    ui->BCPQTW->setItem(i,1,Estado);
    ui->BCPQTW->setItem(i,2,Operacion);
    ui->BCPQTW->setItem(i,3,Resultado);
    ui->BCPQTW->setItem(i,4,TLlegada);
    ui->BCPQTW->setItem(i,5,TFin);
    ui->BCPQTW->setItem(i,6,TRetorno);
    ui->BCPQTW->setItem(i,7,TEspera);
    ui->BCPQTW->setItem(i,8,TServicio);
    ui->BCPQTW->setItem(i,9,TRes);
    ui->BCPQTW->setItem(i,10,TRespuesta);
    ui->BCPQTW->setItem(i,11,TBloq);
    ++i;
    //Procesos que están esperando CPU.
    for (size_t o = 0; o < Pendientes.size(); ++o)
    {
        aux = Pendientes[o];
        ID = new QTableWidgetItem(QString::number(aux.getIdProceso()));
        Estado = new QTableWidgetItem("Pendiente");
        Operacion = new QTableWidgetItem(aux.getOperacion());
        Resultado = new QTableWidgetItem("-");
        aux.setTSer(aux.getTiempoTranscurrido());
        aux.setTEsp((contador-aux.getTLlegada())-aux.getTSer());

        TLlegada = new QTableWidgetItem(QString::number(aux.getTLlegada()));
        TFin = new QTableWidgetItem("-");
        TRetorno = new QTableWidgetItem("-");
        if(aux.getEjecutado())
        {
            TRespuesta = new QTableWidgetItem(QString::number(aux.getTRes()));
        }
        else
        {
            TRespuesta = new QTableWidgetItem("-");
        }
        TEspera = new QTableWidgetItem(QString::number(aux.getTEsp()));
        TServicio = new QTableWidgetItem(QString::number(aux.getTSer()));
        TBloq = new QTableWidgetItem("-");
        TRes = new QTableWidgetItem(QString::number(aux.getTiempoMaximo()-aux.getTSer()));

        ui->BCPQTW->setItem(i,0,ID);
        ui->BCPQTW->setItem(i,1,Estado);
        ui->BCPQTW->setItem(i,2,Operacion);
        ui->BCPQTW->setItem(i,3,Resultado);
        ui->BCPQTW->setItem(i,4,TLlegada);
        ui->BCPQTW->setItem(i,5,TFin);
        ui->BCPQTW->setItem(i,6,TRetorno);
        ui->BCPQTW->setItem(i,7,TEspera);
        ui->BCPQTW->setItem(i,8,TServicio);
        ui->BCPQTW->setItem(i,9,TRes);
        ui->BCPQTW->setItem(i,10,TRespuesta);
        ui->BCPQTW->setItem(i,11,TBloq);
        ++i;
    }
    //Procesos Bloqueados
    for (size_t e =0; e<Bloqueados.size(); ++e)
    {
        aux = Bloqueados[e];
        ID = new QTableWidgetItem(QString::number(aux.getIdProceso()));
        Estado = new QTableWidgetItem("Bloqueado");
        Operacion = new QTableWidgetItem(aux.getOperacion());
        Resultado = new QTableWidgetItem("-");
        aux.setTSer(aux.getTiempoTranscurrido());
        aux.setTEsp((contador-aux.getTLlegada())-aux.getTSer());

        TLlegada = new QTableWidgetItem(QString::number(aux.getTLlegada()));
        TFin = new QTableWidgetItem("-");
        TRetorno = new QTableWidgetItem("-");
        TRespuesta = new QTableWidgetItem(QString::number(aux.getTRes()));
        TEspera = new QTableWidgetItem(QString::number(aux.getTEsp()));
        TServicio = new QTableWidgetItem(QString::number(aux.getTSer()));
        TBloq = new QTableWidgetItem(QString::number(4-aux.getTBloqueado()));
        TRes = new QTableWidgetItem(QString::number(aux.getTiempoMaximo()-aux.getTSer()));


        ui->BCPQTW->setItem(i,0,ID);
        ui->BCPQTW->setItem(i,1,Estado);
        ui->BCPQTW->setItem(i,2,Operacion);
        ui->BCPQTW->setItem(i,3,Resultado);
        ui->BCPQTW->setItem(i,4,TLlegada);
        ui->BCPQTW->setItem(i,5,TFin);
        ui->BCPQTW->setItem(i,6,TRetorno);
        ui->BCPQTW->setItem(i,7,TEspera);
        ui->BCPQTW->setItem(i,8,TServicio);
        ui->BCPQTW->setItem(i,9,TRes);
        ui->BCPQTW->setItem(i,10,TRespuesta);
        ui->BCPQTW->setItem(i,11,TBloq);
        ++i;
    }
    //Procesos Terminados
    for (size_t u =0; u<Terminados.size(); ++u)
    {
        aux = Terminados[u];
        ID = new QTableWidgetItem(QString::number(aux.getIdProceso()));
        Estado = new QTableWidgetItem("Terminado");
        Operacion = new QTableWidgetItem(aux.getOperacion());
        if(aux.getError())
        {
            Resultado = new QTableWidgetItem("Error");
        }
        else
        {
            Resultado = new QTableWidgetItem(QString::number(aux.getResultado()));
        }
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
        TLlegada = new QTableWidgetItem(QString::number(aux.getTLlegada()));
        TFin = new QTableWidgetItem(QString::number(aux.getTFin()));
        TRetorno = new QTableWidgetItem(QString::number(aux.getTRet()));
        TRespuesta = new QTableWidgetItem(QString::number(aux.getTRes()));
        TEspera = new QTableWidgetItem(QString::number(aux.getTEsp()));
        TServicio = new QTableWidgetItem(QString::number(aux.getTSer()));
        TBloq = new QTableWidgetItem("-");
        TRes = new QTableWidgetItem("-");


        ui->BCPQTW->setItem(i,0,ID);
        ui->BCPQTW->setItem(i,1,Estado);
        ui->BCPQTW->setItem(i,2,Operacion);
        ui->BCPQTW->setItem(i,3,Resultado);
        ui->BCPQTW->setItem(i,4,TLlegada);
        ui->BCPQTW->setItem(i,5,TFin);
        ui->BCPQTW->setItem(i,6,TRetorno);
        ui->BCPQTW->setItem(i,7,TEspera);
        ui->BCPQTW->setItem(i,8,TServicio);
        ui->BCPQTW->setItem(i,9,TRes);
        ui->BCPQTW->setItem(i,10,TRespuesta);
        ui->BCPQTW->setItem(i,11,TBloq);
        ++i;
    }
    //Procesos Nuevos
    for (size_t a = 0; a < Procesos.size(); ++a)
    {
        aux = Procesos[a];
        ID = new QTableWidgetItem(QString::number(aux.getIdProceso()));
        Estado = new QTableWidgetItem("Nuevo");
        Operacion = new QTableWidgetItem(aux.getOperacion());
        Resultado = new QTableWidgetItem("-");

        TLlegada = new QTableWidgetItem("-");
        TFin = new QTableWidgetItem("-");
        TRetorno = new QTableWidgetItem("-");
        TRespuesta = new QTableWidgetItem("-");
        TEspera = new QTableWidgetItem("-");
        TServicio = new QTableWidgetItem("-");
        TBloq = new QTableWidgetItem("-");
        TRes = new QTableWidgetItem("-");

        ui->BCPQTW->setItem(i,0,ID);
        ui->BCPQTW->setItem(i,1,Estado);
        ui->BCPQTW->setItem(i,2,Operacion);
        ui->BCPQTW->setItem(i,3,Resultado);
        ui->BCPQTW->setItem(i,4,TLlegada);
        ui->BCPQTW->setItem(i,5,TFin);
        ui->BCPQTW->setItem(i,6,TRetorno);
        ui->BCPQTW->setItem(i,7,TEspera);
        ui->BCPQTW->setItem(i,8,TServicio);
        ui->BCPQTW->setItem(i,9,TRes);
        ui->BCPQTW->setItem(i,10,TRespuesta);
        ui->BCPQTW->setItem(i,11,TBloq);
        ++i;
    }
}

bool MainWindow::maxAmmount()
{
    if(Pendientes.size()+Bloqueados.size()+1<4)
    {
        return true;
    }
    else
    {
        return false;
    }
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
        if(int(Terminados.size())!=ui->NProcesosQSB->value() && ui->MainQSW->currentIndex()!=1)
        {
            ui->MainQSW->setCurrentIndex(1);
        }
        activate = true;
    }
    else if(ev->key()==Qt::Key_N)
    {
        if(activate)
        {
            createNew();
        }
    }
    else if(ev->key()==Qt::Key_B)
    {
        activate = false;
        ui->MainQSW->setCurrentIndex(3);
        showPCB();
        while(!activate)
        {
            delay();
        }
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
        if(Procesos.empty())
        {
            break;
        }
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
    this->releaseKeyboard();
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
        if(Bloqueados[i].getTBloqueado()>=8)
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
                if(maxAmmount())
                {
                    if(!Procesos.empty())
                    {
                        Pendientes.push_back(Procesos.front());
                        Procesos.erase(Procesos.begin());
                    }
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
                    oe = i;
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
