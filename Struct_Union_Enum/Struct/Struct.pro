TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgtest

SOURCES += \
    Structs.cpp \
    main.cpp


HEADERS += \
    Structs.hpp
