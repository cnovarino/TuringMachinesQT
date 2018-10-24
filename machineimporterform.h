#ifndef MACHINEIMPORTERFORM_H
#define MACHINEIMPORTERFORM_H

#include <QWidget>

#include <Models/turingmachine.h>

namespace Ui {
class MachineImporterForm;
}

class MachineImporterForm : public QWidget
{
    Q_OBJECT

public:
    explicit MachineImporterForm(QWidget *parent = nullptr);
    ~MachineImporterForm();

private slots:
    void on_btnClose_clicked();

    void on_btnImport_clicked();

private:
    Ui::MachineImporterForm *ui;

signals:
    void onTuringMachineDeserialized(TuringMachine *tm);
};

#endif // MACHINEIMPORTERFORM_H
