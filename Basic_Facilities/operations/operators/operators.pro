TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle qt

LIBS += -lgtest -lpthread



HEADERS += \
    operators.hpp


SOURCES += \
    main.cpp \
    operators.cpp \
    test_operators.c++
