/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cmbMachines;
    QPushButton *btnModifyMachine;
    QPushButton *btnAddMachine;
    QPushButton *btnShowTable;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnShowQR;
    QTextBrowser *tbConsole;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnReset;
    QPushButton *btnClearLog;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QSpinBox *spnAmount;
    QLabel *label_5;
    QSpinBox *spnStates;
    QCheckBox *chkNotDeleting;
    QLabel *label_7;
    QSpinBox *spnInterestingSteps;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lblCompleted;
    QLabel *lblPending;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnSearch;
    QPushButton *btnContinue;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSpinBox *spnSteps;
    QVBoxLayout *verticalLayout;
    QPushButton *btnExecute;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *chkPrintSteps;
    QCheckBox *chkPrintFinalTape;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(598, 539);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        cmbMachines = new QComboBox(centralWidget);
        cmbMachines->setObjectName(QStringLiteral("cmbMachines"));
        cmbMachines->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout->addWidget(cmbMachines);

        btnModifyMachine = new QPushButton(centralWidget);
        btnModifyMachine->setObjectName(QStringLiteral("btnModifyMachine"));

        horizontalLayout->addWidget(btnModifyMachine);

        btnAddMachine = new QPushButton(centralWidget);
        btnAddMachine->setObjectName(QStringLiteral("btnAddMachine"));

        horizontalLayout->addWidget(btnAddMachine);


        horizontalLayout_5->addLayout(horizontalLayout);

        btnShowTable = new QPushButton(centralWidget);
        btnShowTable->setObjectName(QStringLiteral("btnShowTable"));

        horizontalLayout_5->addWidget(btnShowTable);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        btnShowQR = new QPushButton(centralWidget);
        btnShowQR->setObjectName(QStringLiteral("btnShowQR"));

        horizontalLayout_5->addWidget(btnShowQR);


        verticalLayout_2->addLayout(horizontalLayout_5);

        tbConsole = new QTextBrowser(centralWidget);
        tbConsole->setObjectName(QStringLiteral("tbConsole"));

        verticalLayout_2->addWidget(tbConsole);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btnReset = new QPushButton(centralWidget);
        btnReset->setObjectName(QStringLiteral("btnReset"));

        horizontalLayout_4->addWidget(btnReset);

        btnClearLog = new QPushButton(centralWidget);
        btnClearLog->setObjectName(QStringLiteral("btnClearLog"));

        horizontalLayout_4->addWidget(btnClearLog);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        spnAmount = new QSpinBox(groupBox);
        spnAmount->setObjectName(QStringLiteral("spnAmount"));
        spnAmount->setMinimum(1);
        spnAmount->setMaximum(50000000);
        spnAmount->setValue(1000);

        gridLayout->addWidget(spnAmount, 0, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        spnStates = new QSpinBox(groupBox);
        spnStates->setObjectName(QStringLiteral("spnStates"));
        spnStates->setMinimum(1);
        spnStates->setMaximum(50000000);
        spnStates->setValue(2);

        gridLayout->addWidget(spnStates, 1, 2, 1, 1);

        chkNotDeleting = new QCheckBox(groupBox);
        chkNotDeleting->setObjectName(QStringLiteral("chkNotDeleting"));

        gridLayout->addWidget(chkNotDeleting, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 2, 1, 1, 1);

        spnInterestingSteps = new QSpinBox(groupBox);
        spnInterestingSteps->setObjectName(QStringLiteral("spnInterestingSteps"));
        spnInterestingSteps->setMaximum(50000000);
        spnInterestingSteps->setValue(50);

        gridLayout->addWidget(spnInterestingSteps, 2, 2, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        lblCompleted = new QLabel(groupBox);
        lblCompleted->setObjectName(QStringLiteral("lblCompleted"));

        horizontalLayout_7->addWidget(lblCompleted);

        lblPending = new QLabel(groupBox);
        lblPending->setObjectName(QStringLiteral("lblPending"));

        horizontalLayout_7->addWidget(lblPending);


        gridLayout->addLayout(horizontalLayout_7, 3, 0, 1, 3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnSearch = new QPushButton(groupBox);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        btnSearch->setMinimumSize(QSize(120, 0));
        btnSearch->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_3->addWidget(btnSearch);

        btnContinue = new QPushButton(groupBox);
        btnContinue->setObjectName(QStringLiteral("btnContinue"));
        btnContinue->setMinimumSize(QSize(120, 0));
        btnContinue->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_3->addWidget(btnContinue);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 3);


        horizontalLayout_8->addWidget(groupBox);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        spnSteps = new QSpinBox(centralWidget);
        spnSteps->setObjectName(QStringLiteral("spnSteps"));
        spnSteps->setMaximum(50000000);
        spnSteps->setValue(50);

        horizontalLayout_2->addWidget(spnSteps);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        btnExecute = new QPushButton(centralWidget);
        btnExecute->setObjectName(QStringLiteral("btnExecute"));
        btnExecute->setMinimumSize(QSize(120, 0));
        btnExecute->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(btnExecute);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_6->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        chkPrintSteps = new QCheckBox(centralWidget);
        chkPrintSteps->setObjectName(QStringLiteral("chkPrintSteps"));

        verticalLayout_5->addWidget(chkPrintSteps);

        chkPrintFinalTape = new QCheckBox(centralWidget);
        chkPrintFinalTape->setObjectName(QStringLiteral("chkPrintFinalTape"));

        verticalLayout_5->addWidget(chkPrintFinalTape);


        horizontalLayout_6->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_6);


        horizontalLayout_8->addLayout(verticalLayout_6);


        verticalLayout_2->addLayout(horizontalLayout_8);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "Maquinas:", nullptr));
        btnModifyMachine->setText(QApplication::translate("MainWindow", "Modificar", nullptr));
        btnAddMachine->setText(QApplication::translate("MainWindow", "Crear Maquina", nullptr));
        btnShowTable->setText(QApplication::translate("MainWindow", "Mostrar Tabla", nullptr));
        btnShowQR->setText(QApplication::translate("MainWindow", "Ver QR", nullptr));
        btnReset->setText(QApplication::translate("MainWindow", "Reiniciar Maquina", nullptr));
        btnClearLog->setText(QApplication::translate("MainWindow", "Limpiar Log", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Maquinas Interesantes", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Cantidad:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Estados:", nullptr));
        chkNotDeleting->setText(QApplication::translate("MainWindow", "Solo no Borrantes", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Pasos:", nullptr));
        lblCompleted->setText(QApplication::translate("MainWindow", "Finalizadas: 0", nullptr));
        lblPending->setText(QApplication::translate("MainWindow", "Pendientes: 0", nullptr));
        btnSearch->setText(QApplication::translate("MainWindow", "Buscar", nullptr));
        btnContinue->setText(QApplication::translate("MainWindow", "Continuar", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Pasos:", nullptr));
        btnExecute->setText(QApplication::translate("MainWindow", "Ejecutar Maquina", nullptr));
        chkPrintSteps->setText(QApplication::translate("MainWindow", "Imprimir Pasos", nullptr));
        chkPrintFinalTape->setText(QApplication::translate("MainWindow", "Imprimir Cinta Final", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
