TEMPLATE = app
CONFIG += console
CONFIG += c++20
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        arguments.cpp \
        functions.cpp \
        main.cpp \
        test_arguments.c++ \
        test_constexpr_functions.c++ \
        test_functions.c++

HEADERS += \
    arguments.hpp \
    function_templates.hpp \
    functions.hpp \
    test_arguments.h++ \
    test_constexpr_functions.h++
