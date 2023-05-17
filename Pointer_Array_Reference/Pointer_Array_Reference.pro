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
        main.cpp

HEADERS += \
    Array.hpp \
    Pointer.hpp \
    Reference.hpp
