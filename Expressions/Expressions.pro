TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lCppUTest -lCppUTestExt

SOURCES += \
        constant_expression.cpp \
        desktop_calculator/calculator.cpp \
        main.cpp \
        test_complex.c++ \
        test_constant_expression.c++ \
        test_expression_operators.c++ \
        test_temporary_object.c++ \
        test_type_cast.c++ \
        utilities.cpp

HEADERS += \
    complex.hpp \
    complex_impl.hpp \
    constant_expression.hpp \
    desktop_calculator/calculator.hpp \
    test_constant_expression.h++ \
    test_temporary_object.h++ \
    utilities.hpp
