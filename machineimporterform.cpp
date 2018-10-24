#include "machineimporterform.h"
#include "ui_machineimporterform.h"
#include "Models/state.h"
#include "Models/stateaction.h"
#include <QMessageBox>
#include <QStringList>
#include <QDebug>

MachineImporterForm::MachineImporterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MachineImporterForm)
{
    ui->setupUi(this);
}

MachineImporterForm::~MachineImporterForm()
{
    delete ui;
}

void MachineImporterForm::on_btnClose_clicked()
{
    this->close();
}

void MachineImporterForm::on_btnImport_clicked()
{

    TuringMachine *tm = TuringMachine::deserialize(ui->leDeserialize->text());

    if(tm == nullptr){
        QMessageBox::about(this,"Error","El string ingresado no es el de una maquina valida.");
    }else{
        emit onTuringMachineDeserialized(tm);
        this->close();
    }

//    if(ui->editText->toPlainText().isEmpty()){
//        QMessageBox::about(this,"Error","Escriba la tabla de una maquina de turing");
//        return;
//    }

//    QString table = ui->editText->toPlainText().trimmed();

//    QStringList lines = table.split('\n');

//    QList<State*> states;

//    foreach(QString line , lines){
//        QStringList cols = line.split('\t');

//        if(cols.size() != 3)
//            continue;

//        bool initial_state = false;

//        QString col0 = cols.at(0);
//        QString col1 = cols.at(1);
//        QString col2 = cols.at(2);


//        if(col0.startsWith("*")){
//            col0.remove(0,1);
//            initial_state = true;
//        }

//        State* tmp = new State(col0,StateAction(col1),StateAction(col2));
//        tmp->validateActions();
//        states.append(tmp);

//    }

//    qDebug() << lines;



}
