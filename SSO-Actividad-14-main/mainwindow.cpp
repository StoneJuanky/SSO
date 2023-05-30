#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    adjustTables();
    ui->NProcesosQSB->clear();
    ui->QuantumQSB->clear();
    srand(time(NULL));
    inicializarPaginas();

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
    else if(ui->QuantumQSB->value()<=0 || ui->QuantumQSB->text().length()<=0)
    {
        message.setText("Ingresa un valor de Quantum válido."
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
        aux.setTamanio(randomNumbers(6,26));
        Procesos.push_back(aux);
    }
    delay();
    ui->MainQSW->setCurrentIndex(1);
    this->grabKeyboard();
    Quantum = ui->QuantumQSB->value();
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
    ax.setTamanio(randomNumbers(6,25));
    Procesos.push_back(ax);
    llenarTabla();
    ui->NoProcPendientesQLE->setText(QString::number(Procesos.size()));
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
    QTableWidgetItem *Tamanio;

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
    Tamanio = new QTableWidgetItem(QString::number(aux.getTamanio()));


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
    ui->BCPQTW->setItem(i,12,Tamanio);
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
        Tamanio = new QTableWidgetItem(QString::number(aux.getTamanio()));

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
        ui->BCPQTW->setItem(i,12,Tamanio);

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
        TBloq = new QTableWidgetItem(QString::number(7-aux.getTBloqueado()));
        TRes = new QTableWidgetItem(QString::number(aux.getTiempoMaximo()-aux.getTSer()));
        Tamanio = new QTableWidgetItem(QString::number(aux.getTamanio()));

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
        ui->BCPQTW->setItem(i,12,Tamanio);

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
        Tamanio = new QTableWidgetItem(QString::number(aux.getTamanio()));

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
        ui->BCPQTW->setItem(i,12,Tamanio);
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
        Tamanio = new QTableWidgetItem(QString::number(aux.getTamanio()));

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
        ui->BCPQTW->setItem(i,12,Tamanio);
        ++i;
    }
}

void MainWindow::inicializarPaginas()
{
    sistemaOperativo.setEstado("SO");
    frame.setEstado("Disponible");
    for(int i =0; i < paginasDisponibles; ++i)
    {
        if(i<2)
        {
            Paginas.push_back(sistemaOperativo);
        }
        else
        {
            Paginas.push_back(frame);
        }
    }
    paginasDisponibles-=2;
}

void MainWindow::tablaDePaginas()
{
    for(int i =0; i<Paginas.size(); i++)
    {
        if(Paginas.at(i).getEstado()=="SO")
        {
            ui->PaginasQTW->setItem(i,0,new QTableWidgetItem("SO"));
            ui->PaginasQTW->setItem(i,1,new QTableWidgetItem("SO"));
            ui->PaginasQTW->setItem(i,2,new QTableWidgetItem("SO"));

            ui->PaginasQTW->item(i,0)->setBackground(Qt::magenta);
            ui->PaginasQTW->item(i,1)->setBackground(Qt::magenta);
            ui->PaginasQTW->item(i,2)->setBackground(Qt::magenta);
        }
        if(Paginas.at(i).getEstado()=="Disponible")
        {
            ui->PaginasQTW->setItem(i,0,new QTableWidgetItem("-"));
            ui->PaginasQTW->setItem(i,1,new QTableWidgetItem("-"));
            ui->PaginasQTW->setItem(i,2,new QTableWidgetItem(Paginas.at(i).getEstado()));

            ui->PaginasQTW->item(i,0)->setBackground(Qt::white);
            ui->PaginasQTW->item(i,1)->setBackground(Qt::white);
            ui->PaginasQTW->item(i,2)->setBackground(Qt::white);

        }
        else if(Paginas.at(i).getEstado()=="Listo")
        {
            ui->PaginasQTW->setItem(i,0,new QTableWidgetItem(QString::number(Paginas.at(i).getIdProceso())));
            ui->PaginasQTW->setItem(i,1,new QTableWidgetItem(QString::number(Paginas.at(i).getNumPaginas())+"/5"));
            ui->PaginasQTW->setItem(i,2,new QTableWidgetItem(Paginas.at(i).getEstado()));

            ui->PaginasQTW->item(i,0)->setBackground(Qt::green);
            ui->PaginasQTW->item(i,1)->setBackground(Qt::green);
            ui->PaginasQTW->item(i,2)->setBackground(Qt::green);
        }
        else if(Paginas.at(i).getEstado()=="Bloqueado")
        {
            ui->PaginasQTW->setItem(i,0,new QTableWidgetItem(QString::number(Paginas.at(i).getIdProceso())));
            ui->PaginasQTW->setItem(i,1,new QTableWidgetItem(QString::number(Paginas.at(i).getNumPaginas())+"/5"));
            ui->PaginasQTW->setItem(i,2,new QTableWidgetItem(Paginas.at(i).getEstado()));

            ui->PaginasQTW->item(i,0)->setBackground(Qt::red);
            ui->PaginasQTW->item(i,1)->setBackground(Qt::red);
            ui->PaginasQTW->item(i,2)->setBackground(Qt::red);
        }
        else if(Paginas.at(i).getEstado()=="Ejecución")
        {
            ui->PaginasQTW->setItem(i,0,new QTableWidgetItem(QString::number(Paginas.at(i).getIdProceso())));
            ui->PaginasQTW->setItem(i,1,new QTableWidgetItem(QString::number(Paginas.at(i).getNumPaginas())+"/5"));
            ui->PaginasQTW->setItem(i,2,new QTableWidgetItem(Paginas.at(i).getEstado()));

            ui->PaginasQTW->item(i,0)->setBackground(Qt::cyan);
            ui->PaginasQTW->item(i,1)->setBackground(Qt::cyan);
            ui->PaginasQTW->item(i,2)->setBackground(Qt::cyan);
        }
    }
}

void MainWindow::actualizarTabla(Pagina &p, QString estado)
{
    int lastpos = 1;
    int times = Paginas.count(p);
    for (int i =0; i <times ; ++i)
    {
        int pos = Paginas.indexOf(p,lastpos+1);
        lastpos = pos;
        if(pos>0)
        {
            marcoaux = Paginas.at(pos);
            marcoaux.setEstado(estado);
            Paginas.replace(pos,marcoaux);
        }
    }
    tablaDePaginas();
}

void MainWindow::llenarTabla()
{
    while(!Procesos.empty())
    {
        int marcos = Procesos.front().getTamanio()/5;
        if(Procesos.front().getTamanio()%5>0)
        {
            marcos+=1;
        }
        if(marcos<=paginasDisponibles)
        {
            Procesos.front().setTLlegada(contador-1);
            Pendientes.push_back(Procesos.front());
            Procesos.erase(Procesos.begin());
            paginasDisponibles-=marcos;
            insertarMarco(Pendientes.back());
        }
        else
            break;
    }
    tablaDePaginas();
}

void MainWindow::insertarMarco(Proceso &p)
{
    int paginas = p.getTamanio();
    for(int i =0; i < Paginas.size(); ++i)
    {
        if(Paginas.at(i).getEstado()=="Disponible")
        {
            frame.setEstado("Listo");
            frame.setIdProceso(p.getIdProceso());
            if(paginas>=5)
            {
                frame.setNumPaginas(5);
                Paginas.replace(i,frame);
                paginas-=5;
            }
            else if (paginas>0)
            {
                frame.setNumPaginas(paginas);
                Paginas.replace(i,frame);
                paginas-=paginas;
            }
            if(paginas==0)
                break;
        }
    }
    tablaDePaginas();
}

void MainWindow::updateNext()
{
    if(!Procesos.empty())
    {
        ui->IDProximoQLE->setText(QString::number(Procesos.front().getIdProceso()));
        ui->TamanioQLE_2->setText(QString::number(Procesos.front().getTamanio()));
    }
    else
    {
        ui->IDProximoQLE->setText("-");
        ui->TamanioQLE_2->setText("-");
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
    else if(ev->key()==Qt::Key_P or ev->key()==Qt::Key_T)
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
    ui->QuantumRestanteQLE->clear();
    ui->TamanioQLE->clear();
}

void MainWindow::adjustTables()
{
    ui->PendientesQTV->setColumnWidth(0,80);
    ui->PendientesQTV->setColumnWidth(1,80);
    ui->PendientesQTV->setColumnWidth(2,80);
    ui->ProcTerminadosQTW->setColumnWidth(0,80);
    ui->BloqueadosQTW->setColumnWidth(0,80);
    ui->BloqueadosQTW->setColumnWidth(1,80);
    ui->PaginasQTW->setColumnWidth(0,80);
}

void MainWindow::Processing()
{
    llenarTabla();
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
        if(Bloqueados[i].getTBloqueado()>=5)
        {
            Bloqueados[i].setTBloqueado(0);
            Pendientes.push_back(Bloqueados[i]);
            ui->BloqueadosQTW->removeRow(i);
            marcoaux.setIdProceso(aux3.getIdProceso());
            actualizarTabla(marcoaux,"Listo");
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
    ui->QuantumQLEI->setText(QString::number(Quantum));
    llenarTabla();
    while(Pendientes.size() + Bloqueados.size()>0)
    {
        populatePendingTable();
        delay();
        ui->NoProcPendientesQLE->setText(QString::number(Procesos.size()));

        if(!Pendientes.empty())
        {
            updateNext();
            aux2 = Pendientes.front();
            Pendientes.erase(Pendientes.begin());

            ui->PendientesQTV->clearSpans();
            populatePendingTable();

            ui->IDActualQLE->setText(QString::number(aux2.getIdProceso()));
            ui->OperacionActualQLE->setText(aux2.getOperacion());
            ui->TMEActualQLE->setText(QString::number(aux2.getTiempoMaximo()));
            ui->TamanioQLE->setText(QString::number(aux2.getTamanio()));

            aux2.setInterrumpido(false);
            int QuantumAux = Quantum;
            frame.setIdProceso(aux2.getIdProceso());
            actualizarTabla(frame,"Ejecución");
            for (int i =1+aux2.getTiempoTranscurrido(); i <= aux2.getTiempoMaximo() ; ++i )
            {
                updateNext();
                if(aux2.getEjecutado()==false)
                {
                    aux2.setEjecutado(true);
                    aux2.setTRes((contador-aux2.getTLlegada())-1);
                }
                if(QuantumAux<=0)
                {
                    Q = true;
                    QuantumAux = Quantum;
                    aux2.setTiempoTranscurrido(i-1);
                    break;
                }
                if(!aux2.getInterrumpido() && !aux2.getError())
                {
                    ui->QuantumRestanteQLE->setText(QString::number(QuantumAux--));
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
                    if(!(i==aux2.getTiempoMaximo()))
                    {
                        aux2.setTiempoTranscurrido(i-1);
                        break;
                    }
                }
            }
            if(Q)
            {
                Q=false;
                Pendientes.push_back(aux2);
                actualizarTabla(frame,"Listo");
            }
            else
            {
                if(aux2.getInterrumpido())
                {
                    Bloqueados.push_back(aux2);
                    actualizarTabla(frame,"Bloqueado");
                }
                else
                {
                    aux2.setTFin(contador);
                    Terminados.push_back(aux2);
                    actualizarTabla(frame,"Disponible");
                    int marcos = Procesos.front().getTamanio()/5;
                    if(Procesos.front().getTamanio()%5>0)
                    {
                        marcos+=1;
                    }
                    paginasDisponibles+=marcos;
                    populateFinished();
                    llenarTabla();
                }
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
        llenarTabla();
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
        QTableWidgetItem *Tamanio = new QTableWidgetItem(QString::number(aux.getTamanio()));

        ui->TiemposQTW->setItem(i,0,ID);
        ui->TiemposQTW->setItem(i,1,Operacion);
        ui->TiemposQTW->setItem(i,2,Resultado);
        ui->TiemposQTW->setItem(i,3,TLlegada);
        ui->TiemposQTW->setItem(i,4,TFin);
        ui->TiemposQTW->setItem(i,5,TRetorno);
        ui->TiemposQTW->setItem(i,6,TRespuesta);
        ui->TiemposQTW->setItem(i,7,TEspera);
        ui->TiemposQTW->setItem(i,8,TServicio);
        ui->TiemposQTW->setItem(i,9,Tamanio);
    }
}

void MainWindow::on_VerTiemposQPB_clicked()
{
    ui->MainQSW->setCurrentIndex(2);
}
