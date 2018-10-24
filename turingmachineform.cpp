#include "turingmachineform.h"
#include "ui_turingmachineform.h"
#include "machineimporterform.h"
#include "Utils/clickeableqlabel.h"
#include <QMessageBox>

TuringMachineForm::TuringMachineForm(int index, TuringMachine *tm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TuringMachineForm)
{
    ui->setupUi(this);
    if(tm == nullptr){
        this->tm = new TuringMachine();
        update_mode = false;
        ui->btnCreate->setText("Crear");
    }else{
        this->update_index = index;
        this->tm = new TuringMachine(tm);
        update_mode = true;
        ui->btnCreate->setText("Actualizar");
    }

    ui->leMachineName->setText(this->tm->getName());
    init_table_states();
    redraw_table();
}

TuringMachineForm::~TuringMachineForm()
{
    delete ui;
}

void TuringMachineForm::on_btnClose_clicked()
{
    if(!update_mode)
        delete tm;
    close();
}

void TuringMachineForm::on_btnAddState_clicked()
{
    if(ui->leStateName->text().isEmpty() || ui->leOnOne->text().isEmpty() || ui->leOnZero->text().isEmpty()){
        ui->tbConsole->append("Debe ingresar todos los parametros");
        return;
    }

    StateAction on_zero(ui->leOnZero->text().toLower());

    if(on_zero.validateAction() == StateAction::ParseError){
        ui->tbConsole->append("Error al parsear En 0: " + on_zero.getRendering());
        return;
    }

    StateAction on_one(ui->leOnOne->text().toLower());

    if(on_one.validateAction() == StateAction::ParseError){
        ui->tbConsole->append("Error al parsear En 1: " + on_one.getRendering());
        return;
    }

    State * new_state = new State(ui->leStateName->text().toLower(),on_zero,on_one);

    if(tm->addState(new_state,ui->chkStart->isChecked()) == TuringMachine::StateError::AlreadyExists){
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Estado Duplicado", "El estado con el nombre " + new_state->getName() + " ya esxiste. Desea reemplazarlo?",
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::No) {
              ui->tbConsole->append("El estado con el nombre " + new_state->getName() + " Ya existe.");
              delete new_state;
              return;
          } else {
              if(!tm->updateState(new_state,ui->chkStart->isChecked())){
                  ui->tbConsole->append("Error al actualizar el estado");
                  delete new_state;
                  return;
              }
          }
          new_state = nullptr;
    }

    ui->tbConsole->append("El estado " + ui->leStateName->text().toLower() + " fue agregado correctamente.");
    if(ui->chkStart->isChecked()){
        ui->tbConsole->append("El estado " + ui->leStateName->text().toLower() + " fue asignado como el estado inicial.");
    }

    ui->chkStart->setChecked(false);
    ui->leStateName->clear();
    ui->leOnOne->clear();
    ui->leOnZero->clear();

    redraw_table();

    ui->leStateName->setFocus();

}

void TuringMachineForm::onStateDelete(QString reference)
{
    State *state = tm->getState(reference);

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Eliminar Estado", "Seguro que desea eliminar el estado " + reference + "?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::No) {
          return;
      } else {
          if(tm->removeState(state)){
              ui->tbConsole->append("El estado " + reference + " fue eliminado correctamente.");
              redraw_table();
          }else{
              ui->tbConsole->append("Error al eliminar el estado " + reference + ".");
          }
      }
}

void TuringMachineForm::init_table_states()
{
    ui->tableStates->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableStates->setColumnCount(5);
    ui->tableStates->setHorizontalHeaderLabels(QStringList() << "Nombre" << "En 0" << "En 1" << "Estado Inicial" << "Borrar");

}

void TuringMachineForm::append_state(State *state)
{
    int row_position = ui->tableStates->rowCount();
    ui->tableStates->insertRow(row_position);

    QTableWidgetItem *name = new QTableWidgetItem(state->getName());
    QTableWidgetItem *on_zero = new QTableWidgetItem(state->getOn_zero().getRendering());
    QTableWidgetItem *on_one = new QTableWidgetItem(state->getOn_one().getRendering());
    QLabel *initial_state = new QLabel("",this);
    if(tm->getInitial_state() != nullptr){
        initial_state = new QLabel((*state == *tm->getCurrent_state()) ? "X" : "");
    }
    initial_state->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ClickeableQLabel *delete_state = new ClickeableQLabel(this);
    delete_state->setText("X");
    delete_state->setReference(state->getName());
    delete_state->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    delete_state->setStyleSheet("QLabel { font-size : 18px; font-weight : bold; color : red; }");

    connect(delete_state,SIGNAL(clicked(QString)),this,SLOT(onStateDelete(QString)));

    ui->tableStates->setItem(row_position,0,name);
    ui->tableStates->setItem(row_position,1,on_zero);
    ui->tableStates->setItem(row_position,2,on_one);
    ui->tableStates->setCellWidget(row_position,3,initial_state);
    ui->tableStates->setCellWidget(row_position,4,delete_state);

}

void TuringMachineForm::redraw_table()
{
    ui->tableStates->setRowCount(0);

    foreach(State *state, tm->getStates()){
        append_state(state);
    }

}

void TuringMachineForm::saveMachine()
{
    tm->setName(ui->leMachineName->text());

    if(update_mode)
        emit machineUpdated(update_index,tm);
    else
        emit machineCreated(tm);

    this->close();
}

bool TuringMachineForm::autoAsignInitialState()
{
    State *first = tm->getStates().first();

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Estado Inicial", "La maquina no tiene un estadio inicial asignado. Desea utilizar el estado " + first->getName() + " como estado por defecto ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::No) {
          return false;
      } else {
          tm->setInitial_state(first);
          return true;
      }
}

bool TuringMachineForm::notEndingMachine()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Maquina sin FIN", "Ningun estado de la maquian contiene la instruccion FIN. Desea guardarla de todas formas ?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::No) {
          return false;
      } else {
          return true;
      }
}

void TuringMachineForm::on_leStateName_returnPressed()
{
    if(!ui->leStateName->text().isEmpty())
        ui->leOnZero->setFocus();
}

void TuringMachineForm::on_leOnZero_returnPressed()
{
    if(!ui->leOnZero->text().isEmpty())
        ui->leOnOne->setFocus();
}

void TuringMachineForm::on_leOnOne_returnPressed()
{
    if(!ui->leOnOne->text().isEmpty())
        on_btnAddState_clicked();
}

void TuringMachineForm::on_btnValidate_clicked()
{
    QString error = "";
    tm->validateMachine(error);
    ui->tbConsole->append(error);
}

void TuringMachineForm::on_btnCreate_clicked()
{
    QString error = "";
    switch (tm->validateMachine(error)) {

    case TuringMachine::MachineError::EmptyMachine:
        QMessageBox::about(this,"Error",error);
        break;


    case TuringMachine::MachineError::NoError:
        saveMachine();
        break;

    case TuringMachine::MachineError::NoEnd:
        if(notEndingMachine())
            saveMachine();
        break;

    case TuringMachine::MachineError::MissingStates:
        QMessageBox::about(this,"Error",error);
        break;

    case TuringMachine::MachineError::MissingInitialState:
        if(autoAsignInitialState())
            saveMachine();
        break;

    default:
        break;
    }
}


void TuringMachineForm::on_tableStates_itemDoubleClicked(QTableWidgetItem *item)
{
    Q_UNUSED(item);
    int row =  ui->tableStates->selectedItems().first()->row();

    ui->leStateName->setText(ui->tableStates->item(row,0)->text());
    ui->leOnZero->setText(ui->tableStates->item(row,1)->text());
    ui->leOnOne->setText(ui->tableStates->item(row,2)->text());
    ui->chkStart->setChecked( (ui->tableStates->item(row,0)->text() == "X") ? true : false);
}

void TuringMachineForm::on_btnImport_clicked()
{
    MachineImporterForm *form = new MachineImporterForm();
    form->show();

    connect(form,SIGNAL(onTuringMachineDeserialized(TuringMachine*)),this,SLOT(onTuringMachineDeserialized(TuringMachine*)));
}

void TuringMachineForm::onTuringMachineDeserialized(TuringMachine *tm)
{
    delete  this->tm;
    this->tm = tm;
    redraw_table();
}
