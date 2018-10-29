#include "turingmachine.h"
#include "Utils/timehelper.h"
#include <QDebug>
#include <QTextBrowser>
#include <QJsonValue>
#include <QElapsedTimer>
//#include <QStringBuilder>

QString TuringMachine::serialize()
{
    if(getStatesCount() == 0)
        return "";

    QString result = "";

    foreach(State* state, getStates()){
        result.append(state->getName());
        result.append(";");
        if(state->getOn_zero().isEnd_action())
            result.append("FIN");
        else
            result.append(state->getOn_zero().getRendering());
        result.append(";");
        if(state->getOn_one().isEnd_action())
            result.append("FIN");
        else
            result.append(state->getOn_one().getRendering());
        result.append("|");
    }

    result.remove(result.length()-1,1);

    return result;
}

void TuringMachine::setExec_error(bool value)
{
    exec_error = value;
}

void TuringMachine::setExec_paused(bool value)
{
    exec_paused = value;
}

void TuringMachine::setExec_finished(bool value)
{
    exec_finished = value;
}

int TuringMachine::getCursor() const
{
    return cursor;
}

void TuringMachine::setCursor(int value)
{
    cursor = value;
}

QMap<int, bool> TuringMachine::getTape() const
{
    return tape;
}

void TuringMachine::setTape(const QMap<int, bool> &value)
{
    tape = value;
}

bool TuringMachine::getExec_error() const
{
    return exec_error;
}

bool TuringMachine::getExec_paused() const
{
    return exec_paused;
}

void TuringMachine::setStep(int value)
{
    step = value;
}

TuringMachine *TuringMachine::deserialize(QString string)
{
    TuringMachine *tm = new TuringMachine();

    QStringList states = string.trimmed().split("|");

    if(states.size() == 0)
        return nullptr;

    foreach(QString serialized_state, states){
        QStringList deserialized = serialized_state.split(";");
        if(deserialized.size() != 3)
            return nullptr;

        tm->addState(deserialized.at(0),StateAction(deserialized.at(1)),StateAction(deserialized.at(2)));
    }

    tm->validateStates();
    tm->setInitial_state(tm->getStateAt(0));
    return tm;
}

TuringMachine::TuringMachine()
{
    initial_state = nullptr;
    resetMachine();

    this->name = "";
}

TuringMachine::TuringMachine(const TuringMachine *other)
{
    this->name = other->getName();
    if(other->initial_state != nullptr)
        this->initial_state = new State(other->initial_state);
    else
        this->initial_state = nullptr;

    foreach(State * state, other->getStates()){
        State * tmp = new State(state);
        tmp->validateActions();
        this->addState(tmp);
    }

    this->resetMachine();
}

TuringMachine::StateError TuringMachine::addState(QString state_name,StateAction on_zero,StateAction on_one, bool starting_state)
{
    return addState(new State(state_name,on_zero,on_one),starting_state);
}

TuringMachine::StateError TuringMachine::addState(State *state, bool initial_state)
{
    if(this->contains(state))
        return StateError::AlreadyExists;
    else{

        if(initial_state){
            this->initial_state = state;
            this->current_state = state;
        }

        this->states.append(state);

        return StateError::NoError;
    }

}

TuringMachine::~TuringMachine()
{
    foreach(State* state, states)
        delete state;

    states.clear();

}

int TuringMachine::getStatesCount()
{
    return states.count();
}

const QString TuringMachine::toTable()
{
    QString table = "";
    table.append(QString("\t 0\t 1\n"));
    foreach (State * state, states) {

        if(initial_state != nullptr)
            if(*state == *initial_state)
                table.append("*");

        table.append(state->toString() + "\n");
    }

    return table;

}

bool TuringMachine::updateState(State *new_state, bool initial_state)
{
    foreach (State * state , states) {
        if(*state == *new_state){

            state->setOn_one(new_state->getOn_one());
            state->setOn_zero(new_state->getOn_zero());

            if(initial_state)
                setInitial_state(state);
            else{
                if((this->initial_state != nullptr) && (*this->initial_state == *state))
                    this->initial_state = nullptr;
            }
            delete new_state;
            return true;
        }
    }

    return false;

}

TuringMachine::MachineError TuringMachine::validateMachine(QString &error)
{
    error.clear();

    if(states.isEmpty()){
        error = "La maquina no tiene cargada ningun estado.";
        return  MachineError::EmptyMachine;
    }

    bool has_end = false;

    if(initial_state == nullptr){
        error = "La maquina no tiene un estado inicial definido.";
        return MachineError::MissingInitialState;
    }

    foreach (State *state, states) {
        StateAction on_zero = state->getOn_zero();

        if(on_zero.isEnd_action())
            has_end = true;
        else{
            State *tmp_state = new State(on_zero.getNext_state_val());

            if(!contains(tmp_state)){
                error = "Error en el estado:" + state->toString() + "\nEl estado: " + tmp_state->getName() + " no existe en esta maquina.";
                delete tmp_state;
                return MachineError::MissingStates;
            }

            delete tmp_state;
        }

        StateAction on_one = state->getOn_one();

        if(on_one.isEnd_action())
            has_end = true;
        else{
           State * tmp_state = new State(on_one.getNext_state_val());

            if(!contains(tmp_state)){
                error = "Error en el estado:" + state->toString() + "\nEl estado: " + tmp_state->getName() + " no existe en esta maquina.";
                delete tmp_state;
                return MachineError::MissingStates;
            }

            delete tmp_state;
        }

    }

    if(!has_end){
        error = "La maquina no tiene la instruccion FIN en ninguno de sus estados.";
        return MachineError::NoEnd;
    }

    error = "La maquina de turing es valida.";
    return MachineError::NoError;

}

void TuringMachine::validateStates()
{
    foreach(State * state , states){
        state->validateActions();
    }

}

QString TuringMachine::getName() const
{
    return name;
}

void TuringMachine::setName(const QString &value)
{
    name = value;
}

State *TuringMachine::getCurrent_state() const
{
    return current_state;
}

void TuringMachine::setCurrent_state(State *value)
{
    current_state = value;
}

QList<State *> TuringMachine::getStates() const
{
    return states;
}

bool TuringMachine::contains(State *state)
{
    foreach (State* other, states) {
        if(*other == *state)
            return true;
    }

    return false;
}

State *TuringMachine::getState(QString name)
{
    State *tmp = new State(name);

    foreach (State* other, states) {
        if(*other == *tmp){
            delete tmp;
            return other;
        }
    }

    delete tmp;

    return nullptr;

}

State *TuringMachine::getStateAt(int row)
{
    return states.at(row);
}

bool TuringMachine::removeState(State *state)
{
    int index = -1;
    bool found = false;
    foreach (State* other, states) {
        index++;
        if(*other == *state){
            found = true;
            break;
        }
    }

    if(!found)
        return false;
    else{
        states.removeAt(index);

        if(initial_state != nullptr && *state == *initial_state){
            initial_state = nullptr;
            current_state = nullptr;
        }

        delete state;
        return true;
    }
}

void TuringMachine::tapeInsert(int pos, bool val)
{
    tape.insert(pos,val);
}

QString TuringMachine::printTape()
{
    QString result = "";

    foreach (int key, tape.keys()) {
        QString val = tape.value(key) ? "1":"0";
        result.append((key==cursor) ? ("<b>" + val + "</b>") : val);
        if(key == cursor)
            result.append("<b><u>" + current_state->getName() + "</u></b>");
    }

    return result;
}

QString TuringMachine::print_final_state()
{
    QString result = "";

    if(exec_finished)
        result += "La maquina " + name + " finalizo su ejecucion en el paso " + QString::number(step);
    else
        result += "La maquina " + name + " sigue ejecutandose luego de " + QString::number(step) + " pasos.";

    return result;
}

void TuringMachine::resetMachine()
{
    this->tape.clear();
    this->cursor = 0;
    this->step = 0;
    this->current_state = initial_state;
    this->exec_finished = false;
    this->exec_error = false;
    this->exec_paused = false;
    tape.insert(0,false);
}

QJsonObject TuringMachine::toJson()
{
    QJsonObject result;
    result.insert("name",name);
    result.insert("initial_state",((getInitial_state() == nullptr) ? QJsonValue() : getInitial_state()->toJson()));

    QJsonArray states_array;

    foreach(State *state , states)
        states_array.append(state->toJson());

    result.insert("states",states_array);

    return result;
}

State *TuringMachine::getInitial_state() const
{
    return initial_state;
}

void TuringMachine::setInitial_state(State *value)
{
    initial_state = value;
    current_state = initial_state;
}

bool TuringMachine::getExec_finished() const
{
    return exec_finished;
}

bool TuringMachine::getPrint_steps() const
{
    return print_steps;
}

void TuringMachine::setPrint_steps(bool value)
{
    print_steps = value;
}

bool TuringMachine::getPrint_final_tape() const
{
    return print_final_tape;
}

void TuringMachine::setPrint_final_tape(bool value)
{
    print_final_tape = value;
}

bool TuringMachine::itsNotDeleting()
{
    bool not_deleting = true;
    foreach(State* state, states){

        StateAction on_one_action = state->getOn_one();

        if (!on_one_action.isEnd_action() && !on_one_action.getWrite_val()) {
            not_deleting = false;
            break;
        }

    }

    return not_deleting;
}

int TuringMachine::getStep() const
{
    return step;
}

bool TuringMachine::isEquivalent(TuringMachine &other)
{

    if(this->states.size() != other.getStatesCount())
        return false;

    for(int i = 0; i < this->states.size();i++){
        State* this_state = this->states.at(i);
        State* other_state = other.getStateAt(i);

        if(!(this_state->getOn_zero() == other_state->getOn_zero())){
            return false;
        }

        if(!(this_state->getOn_one() == other_state->getOn_one())){
            return false;
        }
    }

    return true;

}


