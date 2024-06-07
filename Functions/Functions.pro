TEMPLATE = app
CONFIG += console
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        arguments.cpp \
        constexpr_functions.cpp \
        functions.cpp \
        main.cpp \
        test_arguments.c++ \
        test_constexpr_functions.c++ \
        test_functions.c++

HEADERS += \
    arguments.hpp \
    constexpr_functions.hpp \
    function_templates.hpp \
    functions.hpp \
    test_arguments.h++ \
    test_constexpr_functions.h++
