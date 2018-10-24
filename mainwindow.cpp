#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Models/stateaction.h"
#include "Models/state.h"
#include "turingmachineform.h"
#include "Models/turingmachine.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QR/QrCode.hpp>
#include <QtSvg>

using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    last_search = 0;
    continue_aux = false;
    generator = QRandomGenerator::securelySeeded();

    loadMachines();

    for(int i = 0; i< machines.length(); i++){
        ui->cmbMachines->addItem(machines.at(i)->getName(),QVariant(i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearConsole()
{
    ui->tbConsole->clear();
}

void MainWindow::loadMachines()
{
    QFile file("machines.json");

    if(!file.open(QFile::ReadOnly)){
        initDefaultMachines();
        saveMachines();
        QMessageBox::about(this,"Error","No se encontro el archivo machines.json. Se genero uno por defecto.");
        return;
    }else{

        QJsonArray machines_array = QJsonDocument::fromJson(file.readAll()).array();
        file.close();

        foreach(QJsonValue val, machines_array){

            QJsonObject obj = val.toObject();
            QJsonObject initial_state_obj = obj.value("initial_state").toObject();
            QJsonArray states_array = obj.value("states").toArray();

            TuringMachine *tm = new TuringMachine();
            tm->setName(obj.value("name").toString());
            State *tmp = new State(initial_state_obj.value("name").toString());

            foreach(QJsonValue val2, states_array){
                QJsonObject state_obj = val2.toObject();
                QJsonObject on_zero_obj = state_obj.value("on_zero").toObject();
                QJsonObject on_one_obj = state_obj.value("on_one").toObject();

                State * state = new State(state_obj.value("name").toString(),StateAction(on_zero_obj.value("rendering").toString()),StateAction(on_one_obj.value("rendering").toString()));
                state->validateActions();
                tm->addState(state,(*state == *tmp));
            }

            delete tmp;

            machines.append(tm);
        }
    }

}

void MainWindow::saveMachines()
{
    QJsonArray machines_array;

    foreach(TuringMachine *tm, machines)
        machines_array.append(tm->toJson());

    QJsonDocument doc(machines_array);

    QFile file("machines.json");

    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
        QMessageBox::about(this,"Error","No se puede generar el archivo machines.json. Se encuentra en uso?");
        close();
    }else{
        file.write(doc.toJson());
    }

    if(file.isOpen())
        file.close();


}

void MainWindow::initDefaultMachines()
{
    QString dummy;

    TuringMachine *tm10 = new TuringMachine();
    tm10->setName("Busy Beaver 2 Estados");
    tm10->addState("a",StateAction("1>b"),StateAction("1<b"),true);
    tm10->addState("b",StateAction("1<a"),StateAction::endAction());
    tm10->validateStates();
    machines.append(tm10);

    TuringMachine *tm11 = new TuringMachine();
    tm11->setName("Busy Beaver 3 Estados");
    tm11->addState("a",StateAction("1>b"),StateAction::endAction(),true);
    tm11->addState("b",StateAction("0>c"),StateAction("1>b"));
    tm11->addState("c",StateAction("1<c"),StateAction("1<a"));
    tm11->validateStates();
    machines.append(tm11);

    TuringMachine *tm12 = new TuringMachine();
    tm12->setName("Busy Beaver 4 Estados");
    tm12->addState("a",StateAction("1>b"),StateAction("1<b"),true);
    tm12->addState("b",StateAction("1<a"),StateAction("0<c"));
    tm12->addState("c",StateAction::endAction(),StateAction("1<d"));
    tm12->addState("d",StateAction("1>d"),StateAction("0>a"));
    tm12->validateStates();
    machines.append(tm12);

    TuringMachine *tm13 = new TuringMachine();
    tm13->setName("Busy Beaver 5 Estados");
    tm13->addState("a",StateAction("1>b"),StateAction("1<c"),true);
    tm13->addState("b",StateAction("1>c"),StateAction("1>b"));
    tm13->addState("c",StateAction("1>d"),StateAction("0<e"));
    tm13->addState("d",StateAction("1<a"),StateAction("1<d"));
    tm13->addState("e",StateAction::endAction(),StateAction("0<a"));
    tm13->validateStates();
    machines.append(tm13);

}

void MainWindow::selectMachine()
{
    if(ui->cmbMachines->count() > 0){
        selected_tm = machines.at(ui->cmbMachines->currentData().toInt());
        ui->tbConsole->append("<b>Maquina " + selected_tm->getName() + " seleccionada.</b>");
    }
}

QList<TuringMachine*> MainWindow::search_interesting_machines(int amount, int states, bool not_deleting_only)
{

    QList<QString> write_vals;
    write_vals.append("0");
    write_vals.append("1");
    QList<QString> direction_vals;
    direction_vals.append("<");
    direction_vals.append(">");
    QList<QString> state_vals;

    for(int i = 0; i < states; i++)
        state_vals.append(QString::number(i));

    QList<QString> actions;

    foreach(QString write_val, write_vals)
        foreach(QString direction_val, direction_vals)
            foreach(QString state_val, state_vals)
                actions.append(write_val+direction_val+state_val);

    QList<TuringMachine*> temp_machines;

    int cols = 2;
    int rows = state_vals.size();

    for(int generations = amount; generations > 0; generations--){

        qDebug() << generations;

        TuringMachine *tmp = new TuringMachine();
        for(int i = 0; i < state_vals.size(); i++){

            StateAction tmp_zero = StateAction(actions.at(generator.bounded(0,actions.size())));
            StateAction tmp_one = StateAction(actions.at(generator.bounded(0,actions.size())));

            if(not_deleting_only)
                tmp_one.setRendering(tmp_one.getRendering().replace(0,1,'1'));

            tmp_zero.validateAction();
            tmp_one.validateAction();

            tmp->addState(state_vals.at(i),tmp_zero,tmp_one,(i == 0));
        }

        int col = 0;
        int row = 0;

        while(col+row == 0){
            col = generator.bounded(0,cols);
            row = generator.bounded(0,rows);
        }

        TuringMachine * tmp_copy = new TuringMachine(tmp);
        State * tmp_state = tmp_copy->getStateAt(row);

        if(col)
            tmp_state->setOn_one(StateAction::endAction());
        else
            tmp_state->setOn_zero(StateAction::endAction());

        QList<QString> vals(state_vals);

        foreach(State* state, tmp_copy->getStates()){
            if(!state->getOn_one().isEnd_action()){
                int index = vals.indexOf(state->getOn_one().getNext_state_val());

                if(index != -1){
                    vals.removeAt(index);
                }
            }

            if(!state->getOn_one().isEnd_action()){
                int index = vals.indexOf(state->getOn_zero().getNext_state_val());

                if(index != -1){
                    vals.removeAt(index);
                }
            }
        }

        if(vals.size() > 0){
            delete tmp_copy;
            tmp_copy = nullptr;
            delete tmp;
            generations++;
            continue;
        }

        if(tmp_copy != nullptr){
            foreach(TuringMachine *other_machine,temp_machines){
                if(tmp_copy->isEquivalent(*other_machine)){
                    delete tmp_copy;
                    tmp_copy = nullptr;
                    break;
                }
            }
        }

        if(tmp_copy != nullptr){
            tmp_copy->validateStates();
            temp_machines.append(tmp_copy);
        }

        delete tmp;
    }

//    for(int i = temp_machines.size()-1; i >= 0 ; i--){

//        TuringMachine *tm = temp_machines.at(i);

//        QList<QString> vals(state_vals);

//        foreach(State* state, tm->getStates()){
//            if(!state->getOn_one().isEnd_action()){
//                int index = vals.indexOf(state->getOn_one().getNext_state_val());

//                if(index != -1){
//                    vals.removeAt(index);
//                }
//            }

//            if(!state->getOn_one().isEnd_action()){
//                int index = vals.indexOf(state->getOn_zero().getNext_state_val());

//                if(index != -1){
//                    vals.removeAt(index);
//                }
//            }
//        }

//        if(vals.size() > 0){
//            temp_machines.removeAt(i);
//            delete tm;
//        }

//    }


    return  temp_machines;
}

qint64 MainWindow::posible_machines(int c, int n)
{
    return static_cast<qint64>(pow(3*(c+1)*(n+2),(c+1)*n));
}

void MainWindow::on_btnShowTable_clicked()
{
    if(selected_tm == nullptr)
        return;

    if(selected_tm->getStatesCount() == 0)
        ui->tbConsole->append("La maquina no tiene ningun estado.");
    else
        ui->tbConsole->append(selected_tm->toTable());
}

void MainWindow::on_btnReset_clicked()
{
    if(selected_tm == nullptr)
        return;

    selected_tm->resetMachine();
    ui->tbConsole->append("La maquina volvio a su estado inicial.");
}


void MainWindow::on_btnExecute_clicked()
{
    if(selected_tm == nullptr)
        return;

    selected_tm->setPrint_steps(ui->chkPrintSteps->isChecked());
    selected_tm->setPrint_final_tape(ui->chkPrintFinalTape->isChecked());

    if(selected_tm->getExec_finished()){
        QMessageBox::about(this,"Ejecucion Finalizada","La maquina ya termino su ejecución. Reiniciela para poder ejecutarla nuevamente.");
        selected_tm->print_final_state(ui->tbConsole);
        return;
    }

    selected_tm->exec_machine(ui->spnSteps->value(),ui->tbConsole);
}

void MainWindow::on_btnAddMachine_clicked()
{
    TuringMachineForm *tmForm = new TuringMachineForm();
    tmForm->show();
    connect(tmForm,SIGNAL(machineCreated(TuringMachine*)),this,SLOT(onMachineCreated(TuringMachine*)));
}


void MainWindow::on_cmbMachines_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    selectMachine();
}

void MainWindow::on_btnClearLog_clicked()
{
    clearConsole();
}

void MainWindow::on_btnModifyMachine_clicked()
{
    if(selected_tm == nullptr)
        return;

    TuringMachineForm *tmForm = new TuringMachineForm(machines.indexOf(selected_tm),selected_tm);
    tmForm->show();
    connect(tmForm,SIGNAL(machineUpdated(int,TuringMachine*)),this,SLOT(onMachineUpdated(int,TuringMachine*)));
}

void MainWindow::onMachineCreated(TuringMachine *tm)
{
    machines.append(tm);
    int new_index = machines.size()-1;
    ui->cmbMachines->addItem(tm->getName(),QVariant(new_index));
    saveMachines();

    ui->tbConsole->append("Maquina agregada correctamente.");
}

void MainWindow::onMachineUpdated(int update_index, TuringMachine *tm)
{
    delete machines.at(update_index);
    machines.replace(update_index,tm);
    selected_tm = tm;

    ui->cmbMachines->setItemText(update_index,tm->getName());
    saveMachines();
    ui->tbConsole->append("Maquina actualizada correctamente.");

}

void MainWindow::on_btnSearch_clicked()
{

    QList<TuringMachine*> max_steps_machines;
    int max_steps = 0;

    if(!continue_aux){

        last_search = 0;

        if(interesting_machines.size() > 0){
            foreach(TuringMachine *tm, interesting_machines)
                delete tm;

            interesting_machines.clear();
        }

        interesting_machines = search_interesting_machines(ui->spnAmount->value(),ui->spnStates->value(),ui->chkNotDeleting->isChecked());
    }

    int finished = 0;
    foreach(TuringMachine *tm, interesting_machines){

        tm->setPrint_steps(ui->chkPrintSteps->isChecked());
        tm->setPrint_final_tape(ui->chkPrintFinalTape->isChecked());

        if(tm->getExec_finished())
            continue;

        tm->exec_machine(ui->spnInterestingSteps->value(),nullptr);

        if(tm->getExec_finished()){
            if(tm->getStep() > max_steps){
                max_steps = tm->getStep();
                max_steps_machines.clear();
                max_steps_machines.append(tm);

            }else if(tm->getStep() == max_steps){
                max_steps_machines.append(tm);
            }

            finished++;
        }

    }
    last_search += ui->spnInterestingSteps->value();

    foreach(TuringMachine *tm, max_steps_machines){
        ui->tbConsole->append("---------------------------------------------------------------");
        ui->tbConsole->append("Serialized:\n" + TuringMachine::serialize(*tm) + "\n");
        ui->tbConsole->append(tm->toTable());
        tm->print_final_state(ui->tbConsole);
    }

    ui->lblCompleted->setText("Finalizadas: " + QString::number(finished));
    ui->lblPending->setText("Pendientes: " + QString::number(interesting_machines.size() - finished));

    ui->tbConsole->append("<b>---------------------------------------------------------------</b>");
    ui->tbConsole->append("<b>Quedan " + QString::number(interesting_machines.size() - finished) + " maquinas que siguen ejecutandose despues de " + QString::number(last_search) +" pasos</b>");

    for(int i = interesting_machines.size()-1;i >= 0;i--){
        TuringMachine *tmp = interesting_machines.at(i);
        if(tmp->getExec_finished()){
            delete tmp;
            interesting_machines.removeAt(i);
        }
    }

    continue_aux = false;
}

void MainWindow::on_btnContinue_clicked()
{
    if(last_search == 0){
        QMessageBox::about(this,"Buscar","Debe realizar primero una busqueda de maquinas interesantes.");
        return;
    }

    continue_aux = true;
    on_btnSearch_clicked();

}

void MainWindow::on_btnShowQR_clicked()
{
    if(selected_tm == nullptr)
        return;

    QrCode qr = QrCode::encodeText(TuringMachine::serialize(*selected_tm).toUtf8(),QrCode::Ecc::MEDIUM);

    QString svg = QString::fromStdString(qr.toSvgString(8));

    QSvgWidget *wid = new QSvgWidget();

    wid->show();
    wid->resize(320,320);
    wid->load(svg.toUtf8());

}
