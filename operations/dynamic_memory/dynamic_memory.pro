TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle qt

LIBS += -lCppUTest -lCppUTestExt


HEADERS += \
    manage_pointers.hpp \
    test_dynamic_memory.h++


SOURCES += \
    main.cpp \
    manage_pointers.cpp \
    test_dynamic_memory.c++
