#-------------------------------------------------
#
# Project created by QtCreator 2018-10-11T09:25:48
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TuringMachines
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    Models/state.cpp \
    Models/turingmachine.cpp \
    turingmachineform.cpp \
    Utils/clickeableqlabel.cpp \
    Models/stateaction.cpp \
    machineimporterform.cpp \
    QR/BitBuffer.cpp \
    QR/QrCode.cpp \
    QR/QrSegment.cpp

HEADERS += \
        mainwindow.h \
    Models/state.h \
    Models/stateaction.h \
    Models/turingmachine.h \
    turingmachineform.h \
    Utils/clickeableqlabel.h \
    Utils/timehelper.h \
    machineimporterform.h \
    QR/BitBuffer.hpp \
    QR/QrCode.hpp \
    QR/QrSegment.hpp

FORMS += \
        mainwindow.ui \
    turingmachineform.ui \
    machineimporterform.ui
