TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lCppUTest -lCppUTestExt

SOURCES += \
        desktop_calculator/calculator.cpp \
        main.cpp \
        test_expression_operators.c++

HEADERS += \
    desktop_calculator/calculator.hpp
