TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        explicit_type_conversion.cpp \
        implicit_type_conversion.cpp \
        main.cpp \
        test_named_casts.c++ \
        test_type_conversion.c++

HEADERS += \
    explicit_type_conversion.hpp \
    implicit_type_conversion.hpp
