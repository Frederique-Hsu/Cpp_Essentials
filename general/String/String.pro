TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        String.cpp \
        main.cpp \
        test_String.c++

HEADERS += \
    String.hpp
