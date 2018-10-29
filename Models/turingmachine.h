#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QString>
#include <QList>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>

#include "state.h"

class QTextBrowser;


class TuringMachine
{    

public:

    enum class StateError
    {
        NoError = 0,
        AlreadyExists = 1
    };

    enum class MachineError
    {
        NoError = 0,
        NoEnd = 1,
        UnreachableEnd = 2,
        MissingStates = 3,
        MissingInitialState = 4,
        EmptyMachine = 5
    };

    static TuringMachine*  deserialize(QString string);

    TuringMachine();
    TuringMachine(const TuringMachine* other);
    TuringMachine::StateError addState(QString state_name,StateAction on_zero,StateAction on_one, bool starting_state = false);
    TuringMachine::StateError addState(State * state, bool initial_sate = false);
    ~TuringMachine();


    //Getters & Setters

    QList<State *> getStates() const;
    State * getState(QString name);
    State * getStateAt(int row);

    int getStatesCount();

    QString getName() const;
    void setName(const QString &value);

    State *getCurrent_state() const;
    void setCurrent_state(State *value);

    State *getInitial_state() const;
    void setInitial_state(State *value);

    bool getExec_finished() const;
    void setExec_finished(bool value);

    bool getPrint_steps() const;
    void setPrint_steps(bool value);

    bool getPrint_final_tape() const;
    void setPrint_final_tape(bool value);

    int getStep() const;
    void setStep(int value);

    bool getExec_error() const;
    void setExec_error(bool value);

    bool getExec_paused() const;
    void setExec_paused(bool value);

    QMap<int, bool> getTape() const;
    void setTape(const QMap<int, bool> &value);

    int getCursor() const;
    void setCursor(int value);

    //Show

    const QString toTable();
    QJsonObject toJson();
    QString printTape();
    QString print_final_state();

    //Modifiers
    void resetMachine();

    bool updateState(State* new_state, bool initial_state = false);    
    bool removeState(State*);

    void tapeInsert(int pos,bool val);

    //Helpers

    MachineError validateMachine(QString &error);
    void validateStates();

    bool contains(State*);
    bool itsNotDeleting();
    bool isEquivalent(TuringMachine &other);

    QString serialize();




private:
    QString name;
    int step;

    int cursor;
    State* initial_state;
    State* current_state;
    QList<State*> states;
    QMap<int,bool> tape;

    bool exec_finished;
    bool exec_error;
    bool exec_paused;

    bool print_steps = false;
    bool print_final_tape = false;


};

#endif // TURINGMACHINE_H
