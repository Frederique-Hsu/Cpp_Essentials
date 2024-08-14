TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest

SOURCES += \
        main.cpp \
        test_type_functions.c++ \
        test_type_predicate.c++ \
        test_universal_iterator.c++ \
        type_predicate.cpp

HEADERS += \
    type_predicate.hpp \
    universal_iterator.hpp
