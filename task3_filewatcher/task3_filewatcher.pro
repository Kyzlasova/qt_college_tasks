QT += core gui widgets charts

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
    diagramupdater.cpp \
    filetablemodel.cpp \
    individualfilestrategy.cpp \
    mainwindow.cpp \
    overallfilestrategy.cpp \
    main.cpp

HEADERS += \
    abstractstrategy.h \
    diagramupdater.h \
    filetablemodel.h \
    individualfilestrategy.h \
    mainwindow.h \
    overallfilestrategy.h

FORMS += \
    mainwindow.ui

DESTDIR = $$PWD/../out
