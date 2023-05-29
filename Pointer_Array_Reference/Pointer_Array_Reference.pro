TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest

SOURCES += \
        Array.cpp \
        Array_Utils.cpp \
        Pointer.cpp \
        Reference.cpp \
        main.cpp \
        test_Reference.c++

HEADERS += \
    Array.hpp \
    Pointer.hpp \
    Reference.hpp \
    test_Reference.h++
