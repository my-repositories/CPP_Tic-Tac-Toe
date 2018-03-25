#-------------------------------------------------
#
# Project created by QtCreator 2017-01-02T12:15:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tic-tac-toe
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        game_qt.cpp

HEADERS  += game_qt.h

FORMS    += game_qt.ui

Release:DESTDIR = ../../product/qt_win420-Release
Release:OBJECTS_DIR = release/
Release:MOC_DIR = release/
Release:RCC_DIR = release/
Release:UI_DIR = release/

Debug:DESTDIR = ../../product/qt_win420-Debug
Debug:OBJECTS_DIR = debug
Debug:MOC_DIR = debug/
Debug:RCC_DIR = debug/
Debug:UI_DIR = debug/