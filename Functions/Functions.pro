TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        functions.cpp \
        main.cpp \
        test_constexpr_functions.c++ \
        test_functions.c++

HEADERS += \
    function_templates.hpp \
    functions.hpp \
    test_constexpr_functions.h++
