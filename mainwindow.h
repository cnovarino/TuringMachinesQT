#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controllers/turingmachinecontroller.h"

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
    void on_btnExecute_clicked();
    void on_btnClearLog_clicked();
    void on_btnModifyMachine_clicked();

    void onMachineCreated(QString name, int index);
    void onMachineUpdated(QString name, int index);

    void on_btnSearch_clicked();

    void on_btnContinue_clicked();
    void on_btnShowQR_clicked();

    void onMachinesLoaded();
    void onConsolePrint(QString text);

    void onJsonFileError();

    void onUpdatePendingLabel(int val);
    void onUpdateCompletedLabel(int val);

    void on_btnReset_clicked();

private:
    Ui::MainWindow *ui;
    TuringMachineController controller;

    qint64 posible_machines(int c, int n);
    void clearConsole();

    void selectMachine();


};

#endif // MAINWINDOW_H

