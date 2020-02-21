TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        component.cpp \
        componentmanager.cpp \
        entity.cpp \
        main.cpp \
        typecounter.cpp

HEADERS += \
    TypeCounter.h \
    component.h \
    componentmanager.h \
    entity.h
