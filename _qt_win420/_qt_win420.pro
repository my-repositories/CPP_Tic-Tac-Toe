#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T00:37:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = _qt_win420
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

SRC_DIR = ../source
INC_DIR = ../include


SOURCES += \
        $${SRC_DIR}/main.cpp \
        $${SRC_DIR}/board.cpp \
        $${SRC_DIR}/base_game.cpp \
        $${SRC_DIR}/game_qt.cpp

HEADERS  += \
        $${INC_DIR}/settings.h \
        $${INC_DIR}/board.h \
        $${INC_DIR}/base_game.h \
        $${INC_DIR}/game_qt.h \

FORMS    += game_qt.ui

Release:DESTDIR = ../../product/qt_win420-Release
Release:OBJECTS_DIR = .
Release:MOC_DIR = .
Release:RCC_DIR = .
Release:UI_DIR = .

Debug:DESTDIR = ../../product/qt_win420-Debug
Debug:OBJECTS_DIR = .
Debug:MOC_DIR = .
Debug:RCC_DIR = .
Debug:UI_DIR = .
