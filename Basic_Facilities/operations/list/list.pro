TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle qt

LIBS += -lgtest

SOURCES += \
    list.cpp \
    main.cpp \
    test_list.c++


HEADERS += \
    list.hpp
