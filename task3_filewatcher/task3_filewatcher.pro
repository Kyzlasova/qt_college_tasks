QT += core gui widgets

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
    individualfilestrategy.cpp \
    overallfilestrategy.cpp \
    main.cpp

HEADERS += \
    abstractstrategy.h \
    individualfilestrategy.h \
    overallfilestrategy.h

DESTDIR = $$PWD/../out
