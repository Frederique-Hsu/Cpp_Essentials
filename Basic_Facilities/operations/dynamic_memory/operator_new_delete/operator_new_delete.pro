TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle qt

LIBS += -lgtest

SOURCES += \
    main.cpp \
    operator_new_delete.cpp \
    test_operator_new_delete.c++


HEADERS += \
    operator_new_delete.hpp
