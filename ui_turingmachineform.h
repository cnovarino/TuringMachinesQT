/********************************************************************************
** Form generated from reading UI file 'turingmachineform.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TURINGMACHINEFORM_H
#define UI_TURINGMACHINEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TuringMachineForm
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblName;
    QLineEdit *leMachineName;
    QPushButton *btnImport;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *leStateName;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *leOnZero;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *leOnOne;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *chkStart;
    QPushButton *btnAddState;
    QLabel *lblName_2;
    QTableWidget *tableStates;
    QTextBrowser *tbConsole;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnValidate;
    QPushButton *btnCreate;
    QPushButton *btnClose;

    void setupUi(QWidget *TuringMachineForm)
    {
        if (TuringMachineForm->objectName().isEmpty())
            TuringMachineForm->setObjectName(QStringLiteral("TuringMachineForm"));
        TuringMachineForm->resize(704, 501);
        verticalLayout_5 = new QVBoxLayout(TuringMachineForm);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lblName = new QLabel(TuringMachineForm);
        lblName->setObjectName(QStringLiteral("lblName"));
        lblName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(lblName);

        leMachineName = new QLineEdit(TuringMachineForm);
        leMachineName->setObjectName(QStringLiteral("leMachineName"));

        horizontalLayout_4->addWidget(leMachineName);

        btnImport = new QPushButton(TuringMachineForm);
        btnImport->setObjectName(QStringLiteral("btnImport"));

        horizontalLayout_4->addWidget(btnImport);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox = new QGroupBox(TuringMachineForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        leStateName = new QLineEdit(groupBox);
        leStateName->setObjectName(QStringLiteral("leStateName"));

        verticalLayout->addWidget(leStateName);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        leOnZero = new QLineEdit(groupBox);
        leOnZero->setObjectName(QStringLiteral("leOnZero"));

        verticalLayout_2->addWidget(leOnZero);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        leOnOne = new QLineEdit(groupBox);
        leOnOne->setObjectName(QStringLiteral("leOnOne"));

        verticalLayout_3->addWidget(leOnOne);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        chkStart = new QCheckBox(groupBox);
        chkStart->setObjectName(QStringLiteral("chkStart"));

        verticalLayout_4->addWidget(chkStart);

        btnAddState = new QPushButton(groupBox);
        btnAddState->setObjectName(QStringLiteral("btnAddState"));

        verticalLayout_4->addWidget(btnAddState);


        horizontalLayout->addLayout(verticalLayout_4);


        horizontalLayout_2->addWidget(groupBox);


        verticalLayout_5->addLayout(horizontalLayout_2);

        lblName_2 = new QLabel(TuringMachineForm);
        lblName_2->setObjectName(QStringLiteral("lblName_2"));
        lblName_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_5->addWidget(lblName_2);

        tableStates = new QTableWidget(TuringMachineForm);
        if (tableStates->columnCount() < 4)
            tableStates->setColumnCount(4);
        tableStates->setObjectName(QStringLiteral("tableStates"));
        tableStates->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableStates->setSelectionMode(QAbstractItemView::SingleSelection);
        tableStates->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableStates->setColumnCount(4);

        verticalLayout_5->addWidget(tableStates);

        tbConsole = new QTextBrowser(TuringMachineForm);
        tbConsole->setObjectName(QStringLiteral("tbConsole"));

        verticalLayout_5->addWidget(tbConsole);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btnValidate = new QPushButton(TuringMachineForm);
        btnValidate->setObjectName(QStringLiteral("btnValidate"));

        horizontalLayout_3->addWidget(btnValidate);

        btnCreate = new QPushButton(TuringMachineForm);
        btnCreate->setObjectName(QStringLiteral("btnCreate"));

        horizontalLayout_3->addWidget(btnCreate);

        btnClose = new QPushButton(TuringMachineForm);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout_3->addWidget(btnClose);


        verticalLayout_5->addLayout(horizontalLayout_3);


        retranslateUi(TuringMachineForm);

        QMetaObject::connectSlotsByName(TuringMachineForm);
    } // setupUi

    void retranslateUi(QWidget *TuringMachineForm)
    {
        TuringMachineForm->setWindowTitle(QApplication::translate("TuringMachineForm", "Form", nullptr));
        lblName->setText(QApplication::translate("TuringMachineForm", "Nombre", nullptr));
        leMachineName->setPlaceholderText(QString());
        btnImport->setText(QApplication::translate("TuringMachineForm", "Importar", nullptr));
        groupBox->setTitle(QApplication::translate("TuringMachineForm", "Agregar Estado", nullptr));
        label->setText(QApplication::translate("TuringMachineForm", "Nombre", nullptr));
        leStateName->setPlaceholderText(QApplication::translate("TuringMachineForm", "a", nullptr));
        label_2->setText(QApplication::translate("TuringMachineForm", "En 0", nullptr));
        leOnZero->setPlaceholderText(QApplication::translate("TuringMachineForm", "1>b", nullptr));
        label_3->setText(QApplication::translate("TuringMachineForm", "En 1", nullptr));
        leOnOne->setPlaceholderText(QApplication::translate("TuringMachineForm", "FIN", nullptr));
        chkStart->setText(QApplication::translate("TuringMachineForm", "Inicial", nullptr));
        btnAddState->setText(QApplication::translate("TuringMachineForm", "Agregar", nullptr));
        lblName_2->setText(QApplication::translate("TuringMachineForm", "Estados", nullptr));
        btnValidate->setText(QApplication::translate("TuringMachineForm", "Validar", nullptr));
        btnCreate->setText(QApplication::translate("TuringMachineForm", "Crear", nullptr));
        btnClose->setText(QApplication::translate("TuringMachineForm", "Salir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TuringMachineForm: public Ui_TuringMachineForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TURINGMACHINEFORM_H
