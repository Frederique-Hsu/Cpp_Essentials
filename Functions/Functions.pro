TEMPLATE = app
CONFIG += console
CONFIG += -std=c++11
CONFIG -= app_bundle qt

LIBS += -lgtest -lpthread


HEADERS += \
    constexpr_fns.hpp \
    constexpr_fns_impl.hpp \
    function_template.hpp \
    functions.hpp


SOURCES += \
    constexpr_fns.cpp \
    functions.cpp \
    main.cpp \
    test_constexpr_fns.cpp \
    test_functions.c++

DISTFILES += \
    Makefile
