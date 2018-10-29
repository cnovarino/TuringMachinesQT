#include "turingmachinecontroller.h"
#include "Models/turingmachine.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QElapsedTimer>
#include <QFile>

#include <Utils/timehelper.h>

TuringMachineController::TuringMachineController()
{
    last_search = 0;
    continue_aux = false;
    generator = QRandomGenerator::securelySeeded();
}

void TuringMachineController::loadMachines()
{
    QFile file("machines.json");

    if(!file.open(QFile::ReadOnly)){
        initDefaultMachines();
        saveMachines();
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

    emit machinesLoaded();
}

void TuringMachineController::saveMachines()
{
    QJsonArray machines_array;

    foreach(TuringMachine *tm, machines)
        machines_array.append(tm->toJson());

    QJsonDocument doc(machines_array);

    QFile file("machines.json");

    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
        emit jsonFileError();

    }else{
        file.write(doc.toJson());
    }

    if(file.isOpen())
        file.close();
}

void TuringMachineController::initDefaultMachines()
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

TuringMachine *TuringMachineController::getSelected_tm() const
{
    return selected_tm;
}

QList<TuringMachine *> TuringMachineController::getMachines() const
{
    return machines;
}

void TuringMachineController::execMachine(TuringMachine *tm, int steps)
{
    if(tm->getInitial_state() == nullptr){
        if(!silent_mode)
            emit consolePrint("La maquina no tiene un estado inicial definido. Modifiquela.");
        return;
    }

    QElapsedTimer elapsed_timer;
    elapsed_timer.start();

    while (!tm->getExec_error() && !tm->getExec_finished() && (steps--) > 0) {

        if(getPrint_steps())
            if(!silent_mode)
                emit consolePrint("Paso " + QString::number(tm->getStep()) + ": " + tm->printTape());

        tm->setStep(tm->getStep()+1);

        StateAction action = tm->getCurrent_state()->getAction(static_cast<int>(tm->getTape().value(tm->getCursor())));

        if(action.isEnd_action()){
            if(!silent_mode){
                emit consolePrint(tm->print_final_state());
                if(print_final_tape)
                    emit consolePrint(tm->printTape());
            }

            tm->setExec_finished(true);

            continue;
        }


        tm->tapeInsert(tm->getCursor(),action.getWrite_val());
        tm->setCursor(tm->getCursor() + action.getDirection_val());

        if(!tm->getTape().contains(tm->getCursor()))
            tm->tapeInsert(tm->getCursor(),0);

        tm->setCurrent_state(tm->getState(action.getNext_state_val()));

        if(tm->getCurrent_state() == nullptr){
            if(!silent_mode)
                emit consolePrint("Error de ejecucion en el paso " + QString::number(tm->getStep()) + ". COMO PASO ?<br>");
            tm->setExec_error(true);
            continue;
        }

    }

    if(steps == -1 && !tm->getExec_finished() && !tm->getExec_error()){

        if(!silent_mode)
            emit consolePrint("La maquina " + tm->getName() + " sigue ejecutandose despues de " + QString::number(tm->getStep()) + " pasos. Presione ejecutar nuevamente para continuar.");

        if(print_final_tape)
            if(!silent_mode)
                emit consolePrint("Cinta " + tm->printTape());

    }

    if(!silent_mode)
        emit consolePrint("<b>Duración: " + TimeHelper::print_elapsed_time(elapsed_timer.nsecsElapsed()) + "</b><br>");
}

void TuringMachineController::showCurrentTable()
{
    if(getSelected_tm() == nullptr)
        return;

    if(getSelected_tm()->getStatesCount() == 0)
        emit consolePrint("La maquina no tiene ningun estado.");
    else
        emit consolePrint(getSelected_tm()->toTable());
}

void TuringMachineController::resetCurrentMachine()
{
    if(getSelected_tm() == nullptr)
        return;

    getSelected_tm()->resetMachine();
    emit consolePrint("La maquina volvio a su estado inicial.");
}

void TuringMachineController::generateRandomMachines(int amount, int states, bool not_deleting_only)
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
            foreach(TuringMachine *other_machine,interesting_machines){
                if(tmp_copy->isEquivalent(*other_machine)){
                    delete tmp_copy;
                    tmp_copy = nullptr;
                    break;
                }
            }
        }

        if(tmp_copy != nullptr){
            tmp_copy->validateStates();
            interesting_machines.append(tmp_copy);
        }

        delete tmp;
    }
}

int TuringMachineController::getLast_search() const
{
    return last_search;
}

bool TuringMachineController::getContinue_aux() const
{
    return continue_aux;
}

void TuringMachineController::setContinue_aux(bool value)
{
    continue_aux = value;
}

bool TuringMachineController::getPrint_final_tape() const
{
    return print_final_tape;
}

void TuringMachineController::setPrint_final_tape(bool value)
{
    print_final_tape = value;
}

void TuringMachineController::filterInterestingMachines(int steps,int amount, int states, bool not_deleting_only)
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

            generateRandomMachines(amount,states,not_deleting_only);
        }

        silent_mode = true;
        int finished = 0;
        foreach(TuringMachine *tm, interesting_machines){


            if(tm->getExec_finished())
                continue;

            execMachine(tm,steps);

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
        last_search += steps;
        silent_mode = false;

        foreach(TuringMachine *tm, max_steps_machines){
            emit consolePrint("---------------------------------------------------------------");
            emit consolePrint("Serialized:\n" + tm->serialize() + "\n");
            emit consolePrint(tm->toTable());
            emit consolePrint(tm->print_final_state());
        }

        emit updateCompletedLabel(finished);
        emit updatePendingLabel(interesting_machines.size() - finished);

        emit consolePrint("<b>---------------------------------------------------------------</b>");
        emit consolePrint("<b>Quedan " + QString::number(interesting_machines.size() - finished) + " maquinas que siguen ejecutandose despues de " + QString::number(last_search) +" pasos</b>");

        for(int i = interesting_machines.size()-1;i >= 0;i--){
            TuringMachine *tmp = interesting_machines.at(i);
            if(tmp->getExec_finished()){
                delete tmp;
                interesting_machines.removeAt(i);
            }
        }

        continue_aux = false;
}

bool TuringMachineController::getPrint_steps() const
{
    return print_steps;
}

void TuringMachineController::setPrint_steps(bool value)
{
    print_steps = value;
}

void TuringMachineController::onMachineSelected(int index)
{
    selected_tm = machines.at(index);
    emit consolePrint("<b>Maquina " + selected_tm->getName() + " seleccionada.</b>");
}

void TuringMachineController::onMachineCreated(TuringMachine *tm)
{
        machines.append(tm);
        saveMachines();

        emit machineCreated(tm->getName(),machines.size()-1);
        emit consolePrint("Maquina agregada correctamente.");
}

void TuringMachineController::onMachineUpdated(int update_index, TuringMachine *tm)
{
        delete machines.at(update_index);
        machines.replace(update_index,tm);
        selected_tm = tm;

        saveMachines();
        emit machineUpdated(tm->getName(),update_index);
        emit consolePrint("Maquina actualizada correctamente.");
}
