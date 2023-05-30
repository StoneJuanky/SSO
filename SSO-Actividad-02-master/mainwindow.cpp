#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clear();
    adjustTables();
    ui->NP_SpinBox->clear();
    ui->Menu_StackedWidget->setCurrentIndex(0);
    QPixmap pix(":/rcs/Images/carpeta.png");
    ui->PictureMenu_label->setPixmap(pix);
    ui->PictureMenu2_label->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Aceptar_Botton_clicked()
{
    if(ui->NP_SpinBox->value()<=0 || ui->NP_SpinBox->text().length()<=0)
    {
        message.setText("Ingresa un número de procesos válido."
                        " Intentálo de nuevo.");
        message.setIcon(QMessageBox::Critical);
        message.setWindowTitle("¡Error!");
        message.exec();
    }
    else
    {
        ui->Menu_StackedWidget->setCurrentIndex(1);
        ui->NoProceso_LineEdit->setText(QString::number(procesos+1));
    }
}

void MainWindow::enableProcessesDataIngress()
{
    if(ui->NomProg_LineEdit->text().length() > 0 && ui->OperacionNo1_SpinBox->text().length()>0 &&
       ui->OperacionNo2_SpinBox->text().length()>0 && ui->TiempoMax_SpinBox->text().length()>0 && ui->IDProceso_SpinBox->text().length()>0)
    {
        ui->CapturaProceso_Botton->setEnabled(true);
    }
    else
    {
        ui->CapturaProceso_Botton->setEnabled(false);
    }
}

void MainWindow::validator()
{
    bool valid = true;
    if(ui->OperacionSigno_ComboBox->currentText()=="%" || ui->OperacionSigno_ComboBox->currentText()=="/")
    {
        if(ui->OperacionNo2_SpinBox->text()=="0")
        {
            message.setText("No puedes hacer esta operación. Ingresa un número válido.");
            message.setIcon(QMessageBox::Critical);
            message.setWindowTitle("¡Error!");
            message.exec();
            valid = false;
        }
    }
    if(ui->TiempoMax_SpinBox->value()==0)
    {
        message.setText("Ingresa un tiempo válido.");
        message.setIcon(QMessageBox::Critical);
        message.setWindowTitle("¡Error!");
        message.exec();
        valid = false;
    }
    if(ui->IDProceso_SpinBox->value()==0)
    {
        message.setText("Ingresa un identificador válido.");
        message.setIcon(QMessageBox::Critical);
        message.setWindowTitle("¡Error!");
        message.exec();
        valid = false;
    }
    if(idEnUso.contains(ui->IDProceso_SpinBox->value()))
    {
        message.setText("Este identificador ya está en uso.");
        message.setIcon(QMessageBox::Critical);
        message.setWindowTitle("¡Error!");
        message.exec();
        valid = false;
    }
    if(valid)
    {
        idEnUso.append(ui->IDProceso_SpinBox->value());
        if(procesos%4==0 && procesos>0)
        {
            lote++;
        }
        procesos++;
        assigneData(lote);
        clear();
        if(procesos>=ui->NP_SpinBox->value())
        {
            ui->Menu_StackedWidget->setCurrentIndex(2);
            Proceesing();
        }
        ui->NoProceso_LineEdit->setText(QString::number(procesos+1));
    }
}

void MainWindow::clear()
{
    ui->NomProg_LineEdit->clear();
    ui->OperacionNo1_SpinBox->clear();
    ui->OperacionSigno_ComboBox->setCurrentIndex(0);
    ui->OperacionNo2_SpinBox->clear();
    ui->TiempoMax_SpinBox->clear();
    ui->IDProceso_SpinBox->clear();
}

void MainWindow::clearExec()
{
    ui->LoteActID_LineEdit->clear();
    ui->LoteActNombre_LineEdit->clear();
    ui->LoteActOperacion_LineEdit->clear();
    ui->LoteActTiempoAct_LineEdit->clear();
    ui->LoteActTiempoRes_LineEdit->clear();
    ui->LoteActTiempoTra_LineEdit->clear();
}


void MainWindow::adjustTables()
{
    ui->LoteEjecucion_Table->setColumnWidth(0,180);
    ui->LoteEjecucion_Table->setColumnWidth(1,80);
    ui->ProcesosTerm_Table->setColumnWidth(0,80);
}

void MainWindow::assigneData(int noLote)
{
    aux.setNombre(ui->NomProg_LineEdit->text());
    aux.setIdProceso(ui->IDProceso_SpinBox->value());
    aux.setOperacion(ui->OperacionSigno_ComboBox->currentText());
    aux.setLote(noLote);
    aux.setTiempoMaximo(ui->TiempoMax_SpinBox->value());

    if(ui->OperacionSigno_ComboBox->currentText()=="+")
        aux.setResultado(ui->OperacionNo1_SpinBox->value()+ui->OperacionNo2_SpinBox->value());
    if(ui->OperacionSigno_ComboBox->currentText()=="-")
        aux.setResultado(ui->OperacionNo1_SpinBox->value()-ui->OperacionNo2_SpinBox->value());
    if(ui->OperacionSigno_ComboBox->currentText()=="*")
        aux.setResultado(ui->OperacionNo1_SpinBox->value()*ui->OperacionNo2_SpinBox->value());
    if(ui->OperacionSigno_ComboBox->currentText()=="/")
        aux.setResultado((float)(ui->OperacionNo1_SpinBox->value()) / (float)(ui->OperacionNo2_SpinBox->value()));
    if(ui->OperacionSigno_ComboBox->currentText()=="%")
        aux.setResultado(ui->OperacionNo1_SpinBox->value()%ui->OperacionNo2_SpinBox->value());

    aux.setOperacion(QString::number(ui->OperacionNo1_SpinBox->value()) + " " +
                     ui->OperacionSigno_ComboBox->currentText() + " " +
                     QString::number(ui->OperacionNo2_SpinBox->value()));
    Procesos.push_back(aux);
}

void MainWindow::Proceesing()
{
    bool continueLoop = true;
    while(true)
    {
        ui->NoLotesP_LineEdit->setText(QString::number(lote-1));
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
    message.exec();
}

void MainWindow::populateFinished()
{
    ui->ProcesosTerm_Table->clearSpans();
    ui->ProcesosTerm_Table->setRowCount(Terminados.size());
    for (size_t i =0; i<Terminados.size(); ++i)
    {
        aux=Terminados[i];
        QTableWidgetItem *ID = new QTableWidgetItem(QString::number(aux.getIdProceso()));
        QTableWidgetItem *Operacion = new QTableWidgetItem(aux.getOperacion());
        QTableWidgetItem *Resultado = new QTableWidgetItem(QString::number(aux.getResultado()));
        QTableWidgetItem *Lote = new QTableWidgetItem(QString::number(aux.getLote()));
        ui->ProcesosTerm_Table->setItem(i,0,ID);
        ui->ProcesosTerm_Table->setItem(i,1,Operacion);
        ui->ProcesosTerm_Table->setItem(i,2,Resultado);
        ui->ProcesosTerm_Table->setItem(i,3,Lote);
    }
}

void MainWindow::populatePendingTable()
{
    ui->LoteEjecucion_Table->setRowCount(Pendientes.size());
    for (size_t i =0; i<Pendientes.size() ; ++i)
    {
        aux = Pendientes[i];
        QTableWidgetItem *Nombre = new QTableWidgetItem(aux.getNombre());
        QTableWidgetItem *TME = new QTableWidgetItem(QString::number(aux.getTiempoMaximo()));
        ui->LoteEjecucion_Table->setItem(i,0,Nombre);
        ui->LoteEjecucion_Table->setItem(i,1,TME);
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

        ui->LoteEjecucion_Table->clearSpans();
        populatePendingTable();

        ui->LoteActID_LineEdit->setText(QString::number(aux2.getIdProceso()));
        ui->LoteActNombre_LineEdit->setText(aux2.getNombre());
        ui->LoteActOperacion_LineEdit->setText(aux2.getOperacion());
        ui->LoteActTiempoAct_LineEdit->setText(QString::number(aux2.getTiempoMaximo()));

        for (int i =1; i <= aux2.getTiempoMaximo() ; ++i )
        {
            ui->LoteActTiempoRes_LineEdit->setText(QString::number(aux2.getTiempoMaximo()-i));
            ui->LoteActTiempoTra_LineEdit->setText(QString::number(i));
            ui->Contador_LineEdit->setText(QString::number(contador++));
            delay();
        }
        Terminados.push_back(aux2);
        populateFinished();
        clearExec();
        ui->LoteEjecucion_Table->clearSpans();
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

void MainWindow::on_CapturaProceso_Botton_clicked()
{
    validator();
}

