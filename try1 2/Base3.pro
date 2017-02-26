#-------------------------------------------------
#
# Project created by QtCreator 2016-05-10T21:34:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Base3
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    universebody.cpp \
    universecomposite.cpp \
    config.cpp \
    zodiac.cpp \
    universecomponentfactory.cpp \
    visitor.cpp \
    visitablepart.cpp \
    concretevisitor.cpp

HEADERS  += dialog.h \
    universecomponent.h \
    universecomposite.h \
    universebody.h \
    config.h \
    zodiac.h \
    universecomponentfactory.h \
    visitor.h \
    visitablepart.h \
    concretevisitor.h

FORMS    += dialog.ui

OTHER_FILES +=
