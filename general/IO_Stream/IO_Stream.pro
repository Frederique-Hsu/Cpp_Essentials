TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest

SOURCES += \
        in_stream.cpp \
        main.cpp \
        test_IOStream.c++ \
        user_defined_IO.cpp

HEADERS += \
    in_stream.h \
    user_defined_IO.hpp
