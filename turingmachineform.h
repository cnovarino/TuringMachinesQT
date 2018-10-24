#ifndef TURINGMACHINEFORM_H
#define TURINGMACHINEFORM_H

#include <QWidget>
#include <QTableWidgetItem>
#include "Models/turingmachine.h"

namespace Ui {
class TuringMachineForm;
}

class TuringMachineForm : public QWidget
{
    Q_OBJECT

public:
    explicit TuringMachineForm(int index = -1,TuringMachine *tm = nullptr,QWidget *parent = nullptr);
    ~TuringMachineForm();

private slots:
    void on_btnClose_clicked();
    void on_btnAddState_clicked();
    void on_leStateName_returnPressed();
    void on_leOnZero_returnPressed();
    void on_btnValidate_clicked();
    void on_btnCreate_clicked();
    void on_leOnOne_returnPressed();
    void on_tableStates_itemDoubleClicked(QTableWidgetItem *item);

    void onStateDelete(QString reference);

    void on_btnImport_clicked();

    void onTuringMachineDeserialized(TuringMachine *tm);

private:
    Ui::TuringMachineForm *ui;
    TuringMachine *tm;
    int update_index;

    bool update_mode;

    void init_table_states();
    void append_state(State* state);
    void redraw_table();

    void saveMachine();
    bool autoAsignInitialState();
    bool notEndingMachine();

signals:
    void machineCreated(TuringMachine* tm);
    void machineUpdated(int update_index,TuringMachine* tm);
};

#endif // TURINGMACHINEFORM_H
