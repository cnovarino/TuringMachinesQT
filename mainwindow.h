#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRandomGenerator>

class TuringMachine;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnAddMachine_clicked();
    void on_btnShowTable_clicked();
    void on_btnReset_clicked();
    void on_btnExecute_clicked();
    void on_cmbMachines_currentIndexChanged(int index);
    void on_btnClearLog_clicked();
    void on_btnModifyMachine_clicked();

    void onMachineCreated(TuringMachine *tm);
    void onMachineUpdated(int update_index,TuringMachine *tm);

    void on_btnSearch_clicked();

    void on_btnContinue_clicked();

    void on_btnShowQR_clicked();

private:
    Ui::MainWindow *ui;
    TuringMachine *selected_tm;
    QList<TuringMachine*> machines;

    qint64 posible_machines(int c, int n);
    QRandomGenerator generator;

    void clearConsole();
    void loadMachines();
    void saveMachines();
    void initDefaultMachines();
    void selectMachine();


    QList<TuringMachine*> interesting_machines;
    QList<TuringMachine *> search_interesting_machines(int amount,int states,bool not_deleting_only);

    int last_search;

    bool continue_aux;


};

#endif // MAINWINDOW_H

