TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS = -lgtest

SOURCES += \
        Character_Type/character_literal.cpp \
        Integer_Type/integer.cpp \
        Miscellaneous/misc.cpp \
        Miscellaneous/scope.cpp \
        initialization.cpp \
        main.cpp \
        type_deduction.cpp \
        type_size.cpp

HEADERS += \
    Miscellaneous/scope.hpp \
    type_deduction.hpp
