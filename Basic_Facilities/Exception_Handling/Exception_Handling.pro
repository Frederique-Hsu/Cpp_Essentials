TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest

CONFIG(debug, debug | release) DEFINES += DEBUG

DEFINES += CURRENT_MODE=0 CURRENT_LEVEL=2

SOURCES += \
        assertion.cpp \
        exception.cpp \
        main.cpp \
        my.vector/my.vector.cpp \
        my.vector/test.my.vector.c++ \
        resource_management.cpp \
        termination.cpp \
        test_assertion.c++ \
        test_exception.c++ \
        test_resource_management.c++ \
        test_throw_catch_exception.c++ \
        throw_catch_exception.cpp

HEADERS += \
    assertion.hpp \
    exception.hpp \
    my.vector/my.vector.hpp \
    my.vector/test.my.vector.h++ \
    resource_management.hpp \
    termination.hpp \
    test_resource_management.h++ \
    throw_catch_exception.hpp
