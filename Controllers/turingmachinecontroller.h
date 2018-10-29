#ifndef TURINGMACHINECONTROLLER_H
#define TURINGMACHINECONTROLLER_H

#include <QObject>
#include <QRandomGenerator>

class TuringMachine;

class TuringMachineController : public QObject
{
    Q_OBJECT

public:
    TuringMachineController();

    void loadMachines();
    void saveMachines();
    void initDefaultMachines();

    TuringMachine *getSelected_tm() const;
    QList<TuringMachine *> getMachines() const;

    void execMachine(TuringMachine *tm, int steps);

    bool getPrint_steps() const;
    void setPrint_steps(bool value);

    bool getPrint_final_tape() const;
    void setPrint_final_tape(bool value);

    void filterInterestingMachines(int steps, int amount = 0 , int states = 0, bool not_deleting_only = false);

    bool getContinue_aux() const;
    void setContinue_aux(bool value);

    int getLast_search() const;

private:
    QRandomGenerator generator;

    TuringMachine *selected_tm;
    QList<TuringMachine*> machines;

    QList<TuringMachine*> interesting_machines;
    void generateRandomMachines(int amount,int states,bool not_deleting_only);

    int last_search;
    bool continue_aux;    

    bool print_steps = false;
    bool print_final_tape = false;

    bool silent_mode = false;

signals:

    void machinesLoaded();
    void consolePrint(QString text);

    void machineCreated(QString name, int index);
    void machineUpdated(QString name, int index);

    void jsonFileError();

    void updatePendingLabel(int val);
    void updateCompletedLabel(int val);

public slots:

    void showCurrentTable();
    void resetCurrentMachine();
    void onMachineSelected(int index);

    void onMachineCreated(TuringMachine *tm);
    void onMachineUpdated(int update_index,TuringMachine *tm);

};

#endif // TURINGMACHINECONTROLLER_H
