QT += core
QT -= gui

CONFIG += c++14

TARGET = SHALoader
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    shaloader.cpp

HEADERS += \
    shaloader.h
