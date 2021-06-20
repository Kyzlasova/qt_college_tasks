QT += core gui widgets charts

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
    filetablemodel.cpp \
    individualfilestrategy.cpp \
    mainwindow.cpp \
    overallfilestrategy.cpp \
    main.cpp

HEADERS += \
    abstractstrategy.h \
    filetablemodel.h \
    individualfilestrategy.h \
    mainwindow.h \
    overallfilestrategy.h \
    statsupdater.h

FORMS += \
    mainwindow.ui

DESTDIR = $$PWD/../out
