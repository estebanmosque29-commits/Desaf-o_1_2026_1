TEMPLATE = app
CONFIG -= app_bundle
CONFIG += console
QT -= core gui widgets

SOURCES += main.cpp \
    consola.cpp \
    pieza.cpp \
    tablero.cpp \
    juego.cpp

HEADERS += consola.h \
    pieza.h \
    tablero.h \
    juego.h
