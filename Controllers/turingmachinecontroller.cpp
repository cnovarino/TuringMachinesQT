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

void TuringMachineController::execMachine(TuringMachine *tm, int steps, bool normalize)
{    

    if(tm->getInitial_state() == nullptr){
        if(!silent_mode)
            emit consolePrint("La maquina no tiene un estado inicial definido. Modifiquela.");
        return;
    }

    QList<QString> reached_states;

    if(normalize)
        reached_states.append(tm->getInitial_state()->getName());


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

            if(normalize)
                this->normalize(tm,reached_states);

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

        if(normalize && !reached_states.contains(tm->getCurrent_state()->getName())){
            reached_states.append(tm->getCurrent_state()->getName());
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
    QElapsedTimer elapsed_timer;
    elapsed_timer.start();

    QList<QString> state_vals;

    for(int i = 0; i < states; i++)
        state_vals.append(QString::number(i));

    int cols = 2;

    for(int generations = amount; generations > 0; generations--){

        QList<QString> pending_states = state_vals; // Uso el array para asegurarme que cada estado esta al menos una ves en la tabla
        TuringMachine *tmp = new TuringMachine();
        for(int i = 0; i < state_vals.size(); i++){

            StateAction tmp_zero;            
            StateAction tmp_one;

            tmp_zero.setWrite_val(static_cast<bool>(generator.bounded(2)));
            tmp_zero.setDirection_val(static_cast<bool>(generator.bounded(2)) == 0 ? StateAction::Direction::Left : StateAction::Direction::Rigth);

            if(not_deleting_only) // No borrantes
                tmp_one.setWrite_val(1);
            else
                tmp_one.setWrite_val(static_cast<bool>(generator.bounded(2)));

            tmp_one.setDirection_val(static_cast<bool>(generator.bounded(2)) == 0 ? StateAction::Direction::Left : StateAction::Direction::Rigth);

            if(i == 0){// Estado A
                tmp_zero.setDirection_val(StateAction::Direction::Rigth);
                tmp_zero.setNext_state_val(pending_states.takeAt(1));

                tmp_one.setNext_state_val(state_vals.at(generator.bounded(0,state_vals.size())));

            } else if (i == state_vals.size()-1){  // Ultimo estado
                int col = generator.bounded(0,cols);

                if(col){
                    tmp_one = StateAction::endAction();
                    tmp_zero.setNext_state_val(pending_states.takeAt(generator.bounded(0,pending_states.size())));//Estado de la lista de pendientes

                }else{
                    tmp_zero = StateAction::endAction();
                    tmp_one.setNext_state_val(pending_states.takeAt(generator.bounded(0,pending_states.size())));//Estado de la lista de pendientes
                }

            }else{

                if(generator.bounded(2)){
                    tmp_zero.setNext_state_val(state_vals.at(generator.bounded(0,state_vals.size()))); //Estado random
                    tmp_one.setNext_state_val(pending_states.takeAt(generator.bounded(0,pending_states.size()))); //Estado de la lista de pendientes

                }else{
                    tmp_zero.setNext_state_val(pending_states.takeAt(generator.bounded(0,pending_states.size()))); //Estado de la lista de pendientes
                    tmp_one.setNext_state_val(state_vals.at(generator.bounded(0,state_vals.size()))); //Estado random
                }

            }

            tmp_zero.updateRender();
            tmp_one.updateRender();

            tmp->addState(state_vals.at(i),tmp_zero,tmp_one,(i == 0));
        }

        interesting_machines.append(tmp);
    }

    emit consolePrint("<b>Duración: " + TimeHelper::print_elapsed_time(elapsed_timer.nsecsElapsed()) + "</b><br>");
}

void TuringMachineController::normalize(TuringMachine *tm, QList<QString> reached_states)
{
    for(int i = tm->getStates().size()-1; i >= 0; i--){
        State * state = tm->getStateAt(i);
        if(!reached_states.contains(state->getName()))
            tm->removeState(state);
    }
}

int TuringMachineController::getLast_search() const
{
    return last_search;
}

void TuringMachineController::listPendingMachines()
{
    if(interesting_machines.size() == 0)
        emit consolePrint("No hay maquinas pendientes de ejecución.");
    else{
        foreach(TuringMachine *tm , interesting_machines){
            emit consolePrint(tm->toTable());
        }
    }
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

            execMachine(tm,steps,true);

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
