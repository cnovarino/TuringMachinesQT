/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
    QVBoxLayout *verticalLayout_3;
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
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QSpinBox *spnAmount;
    QLabel *label_5;
    QSpinBox *spnStates;
    QCheckBox *chkNotDeleting;
    QLabel *label_7;
    QSpinBox *spnInterestingSteps;
    QFormLayout *formLayout;
    QPushButton *btnSearch;
    QPushButton *btnContinue;
    QPushButton *pbListPending;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lblCompleted;
    QLabel *lblPending;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *chkPrintSteps;
    QCheckBox *chkPrintFinalTape;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSpinBox *spnSteps;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *btnClearLog;
    QPushButton *btnReset;
    QPushButton *btnExecute;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(560, 455);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
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


        verticalLayout_3->addLayout(horizontalLayout_5);

        tbConsole = new QTextBrowser(centralWidget);
        tbConsole->setObjectName(QStringLiteral("tbConsole"));

        verticalLayout_3->addWidget(tbConsole);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
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
        spnStates->setMinimum(2);
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

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        btnSearch = new QPushButton(groupBox);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        btnSearch->setMinimumSize(QSize(120, 0));
        btnSearch->setMaximumSize(QSize(120, 16777215));

        formLayout->setWidget(0, QFormLayout::LabelRole, btnSearch);

        btnContinue = new QPushButton(groupBox);
        btnContinue->setObjectName(QStringLiteral("btnContinue"));
        btnContinue->setMinimumSize(QSize(120, 0));
        btnContinue->setMaximumSize(QSize(120, 16777215));

        formLayout->setWidget(0, QFormLayout::FieldRole, btnContinue);

        pbListPending = new QPushButton(groupBox);
        pbListPending->setObjectName(QStringLiteral("pbListPending"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pbListPending);


        gridLayout->addLayout(formLayout, 4, 0, 1, 3);

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


        horizontalLayout_3->addWidget(groupBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);

        chkPrintSteps = new QCheckBox(centralWidget);
        chkPrintSteps->setObjectName(QStringLiteral("chkPrintSteps"));

        verticalLayout->addWidget(chkPrintSteps);

        chkPrintFinalTape = new QCheckBox(centralWidget);
        chkPrintFinalTape->setObjectName(QStringLiteral("chkPrintFinalTape"));

        verticalLayout->addWidget(chkPrintFinalTape);

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


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_2->addItem(verticalSpacer);

        btnClearLog = new QPushButton(centralWidget);
        btnClearLog->setObjectName(QStringLiteral("btnClearLog"));

        verticalLayout_2->addWidget(btnClearLog);

        btnReset = new QPushButton(centralWidget);
        btnReset->setObjectName(QStringLiteral("btnReset"));

        verticalLayout_2->addWidget(btnReset);

        btnExecute = new QPushButton(centralWidget);
        btnExecute->setObjectName(QStringLiteral("btnExecute"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnExecute->sizePolicy().hasHeightForWidth());
        btnExecute->setSizePolicy(sizePolicy);
        btnExecute->setMinimumSize(QSize(0, 0));
        btnExecute->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(btnExecute);


        horizontalLayout_4->addLayout(verticalLayout_2);


        horizontalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(horizontalLayout_3);

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
        groupBox->setTitle(QApplication::translate("MainWindow", "Maquinas Interesantes", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Cantidad:", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Estados:", nullptr));
        chkNotDeleting->setText(QApplication::translate("MainWindow", "Solo no Borrantes", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Pasos:", nullptr));
        btnSearch->setText(QApplication::translate("MainWindow", "Buscar", nullptr));
        btnContinue->setText(QApplication::translate("MainWindow", "Continuar", nullptr));
        pbListPending->setText(QApplication::translate("MainWindow", "Listar Pendientes", nullptr));
        lblCompleted->setText(QApplication::translate("MainWindow", "Finalizadas: 0", nullptr));
        lblPending->setText(QApplication::translate("MainWindow", "Pendientes: 0", nullptr));
        chkPrintSteps->setText(QApplication::translate("MainWindow", "Imprimir Pasos", nullptr));
        chkPrintFinalTape->setText(QApplication::translate("MainWindow", "Imprimir Cinta Final", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Pasos:", nullptr));
        btnClearLog->setText(QApplication::translate("MainWindow", "Limpiar Log", nullptr));
        btnReset->setText(QApplication::translate("MainWindow", "Reiniciar y Ejecutar", nullptr));
        btnExecute->setText(QApplication::translate("MainWindow", "Ejecutar Maquina", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
