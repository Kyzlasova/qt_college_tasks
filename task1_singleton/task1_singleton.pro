QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        abstractcompany.cpp \
        concrete_companies.cpp \
        main.cpp

HEADERS += \
    abstractcompany.h \
    concrete_companies.h

DESTDIR = $$PWD/../out
