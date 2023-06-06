TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgtest

SOURCES += \
    Bit_Field/test_struct_bit_field.c++ \
    POD/test_POD.c++ \
    Structs.cpp \
    main.cpp \
    test_Structs.c++


HEADERS += \
    Bit_Field/struct_bit_field.hpp \
    POD/pod.hpp \
    Structs.hpp \
    array.hpp \
    test_Structs.h++

DISTFILES += \
    Makefile
