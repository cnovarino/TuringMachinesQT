#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "turingmachineform.h"
#include <QMessageBox>
#include <QR/QrCode.hpp>
#include <QtSvg>

using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //UI connects
    connect(ui->cmbMachines,SIGNAL(currentIndexChanged(int)),&controller,SLOT(onMachineSelected(int)));
    connect(ui->btnShowTable,SIGNAL(clicked()),&controller,SLOT(showCurrentTable()));
    connect(ui->btnReset,SIGNAL(clicked()),&controller,SLOT(resetCurrentMachine()));

    //Controller connects
    connect(&controller,SIGNAL(jsonFileError()),this,SLOT(onJsonFileError()));
    connect(&controller,SIGNAL(consolePrint(QString)),this,SLOT(onConsolePrint(QString)));
    connect(&controller,SIGNAL(machinesLoaded()),this,SLOT(onMachinesLoaded()));
    connect(&controller,SIGNAL(machineCreated(QString,int)),this,SLOT(onMachineCreated(QString,int)));
    connect(&controller,SIGNAL(machineUpdated(QString,int)),this,SLOT(onMachineUpdated(QString,int)));
    connect(&controller,SIGNAL(updatePendingLabel(int)),this,SLOT(onUpdatePendingLabel(int)));
    connect(&controller,SIGNAL(updateCompletedLabel(int)),this,SLOT(onUpdateCompletedLabel(int)));

    controller.loadMachines();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearConsole()
{
    ui->tbConsole->clear();
}

qint64 MainWindow::posible_machines(int c, int n)
{
    return static_cast<qint64>(pow(3*(c+1)*(n+2),(c+1)*n));
}


void MainWindow::on_btnExecute_clicked()
{
    if(controller.getSelected_tm() == nullptr)
        return;

    controller.setPrint_steps(ui->chkPrintSteps->isChecked());
    controller.setPrint_final_tape(ui->chkPrintFinalTape->isChecked());

    if(controller.getSelected_tm()->getExec_finished()){
        QMessageBox::about(this,"Ejecucion Finalizada","La maquina ya termino su ejecución. Reiniciela para poder ejecutarla nuevamente.");
        return;
    }

    controller.execMachine(controller.getSelected_tm(),ui->spnSteps->value());
}

void MainWindow::on_btnAddMachine_clicked()
{
    TuringMachineForm *tmForm = new TuringMachineForm();
    tmForm->show();
    connect(tmForm,SIGNAL(machineCreated(TuringMachine*)),&controller,SLOT(onMachineCreated(TuringMachine*)));
}


void MainWindow::on_btnClearLog_clicked()
{
    clearConsole();
}

void MainWindow::on_btnModifyMachine_clicked()
{
    if(controller.getSelected_tm() == nullptr)
        return;

    TuringMachineForm *tmForm = new TuringMachineForm(ui->cmbMachines->currentIndex(),controller.getSelected_tm());
    tmForm->show();
    connect(tmForm,SIGNAL(machineUpdated(int,TuringMachine*)),&controller,SLOT(onMachineUpdated(int,TuringMachine*)));
}

void MainWindow::onMachineCreated(QString name, int index)
{
    ui->cmbMachines->addItem(name,QVariant(index));
}

void MainWindow::onMachineUpdated(QString name, int index)
{
    ui->cmbMachines->setItemText(index,name);
}

void MainWindow::on_btnSearch_clicked()
{
    controller.filterInterestingMachines(ui->spnInterestingSteps->value(),ui->spnAmount->value(),ui->spnStates->value(),ui->chkNotDeleting->isChecked());
}

void MainWindow::on_btnContinue_clicked()
{
    if(controller.getLast_search() == 0){
        QMessageBox::about(this,"Buscar","Debe realizar primero una busqueda de maquinas interesantes.");
        return;
    }

    controller.setContinue_aux(true);
    controller.filterInterestingMachines(ui->spnInterestingSteps->value());

}

void MainWindow::on_btnShowQR_clicked()
{
    if(controller.getSelected_tm() == nullptr)
        return;

    QrCode qr = QrCode::encodeText(controller.getSelected_tm()->serialize().toUtf8(),QrCode::Ecc::MEDIUM);

    QString svg = QString::fromStdString(qr.toSvgString(8));

    QSvgWidget *wid = new QSvgWidget();

    wid->show();
    wid->resize(320,320);
    wid->load(svg.toUtf8());

}

void MainWindow::onMachinesLoaded()
{
    for(int i = 0; i< controller.getMachines().length(); i++)
        ui->cmbMachines->addItem(controller.getMachines().at(i)->getName(),QVariant(i));
}

void MainWindow::onConsolePrint(QString text)
{
    ui->tbConsole->append(text);
}

void MainWindow::onJsonFileError()
{
    QMessageBox::about(this,"Error","No se puede generar el archivo machines.json. Se encuentra en uso?");
    close();
}

void MainWindow::onUpdatePendingLabel(int val)
{
    ui->lblPending->setText("Pendientes: " + QString::number(val));
}

void MainWindow::onUpdateCompletedLabel(int val)
{
    ui->lblCompleted->setText("Finalizadas: " + QString::number(val));
}
