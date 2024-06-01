TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        lambdas.cpp \
        lambdas_ext.cpp \
        main.cpp \
        test_lambdas.c++

HEADERS += \
    lambdas.hpp \
    lambdas_ext.hpp \
    test_lambdas.h++
