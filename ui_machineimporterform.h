/********************************************************************************
** Form generated from reading UI file 'machineimporterform.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MACHINEIMPORTERFORM_H
#define UI_MACHINEIMPORTERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MachineImporterForm
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *leDeserialize;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnImport;
    QPushButton *btnClose;

    void setupUi(QWidget *MachineImporterForm)
    {
        if (MachineImporterForm->objectName().isEmpty())
            MachineImporterForm->setObjectName(QStringLiteral("MachineImporterForm"));
        MachineImporterForm->resize(232, 109);
        verticalLayout = new QVBoxLayout(MachineImporterForm);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        leDeserialize = new QLineEdit(MachineImporterForm);
        leDeserialize->setObjectName(QStringLiteral("leDeserialize"));

        verticalLayout->addWidget(leDeserialize);

        verticalSpacer = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnImport = new QPushButton(MachineImporterForm);
        btnImport->setObjectName(QStringLiteral("btnImport"));

        horizontalLayout->addWidget(btnImport);

        btnClose = new QPushButton(MachineImporterForm);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MachineImporterForm);

        QMetaObject::connectSlotsByName(MachineImporterForm);
    } // setupUi

    void retranslateUi(QWidget *MachineImporterForm)
    {
        MachineImporterForm->setWindowTitle(QApplication::translate("MachineImporterForm", "Form", nullptr));
        leDeserialize->setPlaceholderText(QApplication::translate("MachineImporterForm", "Ej: a;1<b;0<a|b;FIN;1>a", nullptr));
        btnImport->setText(QApplication::translate("MachineImporterForm", "Importar", nullptr));
        btnClose->setText(QApplication::translate("MachineImporterForm", "Cerrar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MachineImporterForm: public Ui_MachineImporterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MACHINEIMPORTERFORM_H
