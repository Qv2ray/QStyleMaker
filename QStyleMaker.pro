#-------------------------------------------------
#
# Project created by QtCreator 2013-07-08T11:03:40
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = QStyleMaker
TEMPLATE = app

CONFIG += c++17

DEPENDPATH += \
            src/main \
            src/defines \
            src/debug \
            src/dialogs/about \
            src/common

INCLUDEPATH += \
            src/main \
            src/defines \
            src/debug \
            src/dialogs/about \
            src/common

SOURCES +=  src/main/main.cpp\
            src/main/maindialog.cpp \
            src/dialogs/about/about.cpp \
            src/dialogs/test/testdialog.cpp \
            src/dialogs/test/testmainwindow.cpp \
            src/dialogs/qsseditor/highlighter.cpp

HEADERS  += \
            src/main/maindialog.h \
            src/defines/defines.h \
            src/debug/debughelper.h \
            src/dialogs/about/about.h \
            src/common/stringcommon.h \
            src/dialogs/test/testdialog.h \
            src/dialogs/test/testmainwindow.h \
            src/dialogs/qsseditor/highlighter.h

FORMS    += \
            src/main/maindialog.ui \
            src/dialogs/about/about.ui \
            src/dialogs/test/testdialog.ui \
            src/dialogs/test/testmainwindow.ui

RESOURCES += \
    resources/resources.qrc
