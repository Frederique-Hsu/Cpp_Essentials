TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        Lists.cpp \
        main.cpp \
        test_lists.c++

HEADERS += \
    Lists.hpp
