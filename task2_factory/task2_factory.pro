QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        classunit.cpp \
        cppclassunit.cpp \
        cppmethodunit.cpp \
        main.cpp

HEADERS += \
    abstractfactory.h \
    classunit.h \
    cppclassunit.h \
    cppfactory.h \
    cppmethodunit.h \
    cppprintoperatorunit.h \
    methodunit.h \
    printoperatorunit.h \
    unit.h

DESTDIR = $$PWD/../out
