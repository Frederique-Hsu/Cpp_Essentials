TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle qt

LIBS += -lgtest -lpthread


HEADERS += \
    function_template.hpp \
    function_template_impl.hpp \
    functions.hpp


SOURCES += \
    functions.cpp \
    main.cpp \
    test_functions.c++
