TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS = -lCppUTest -lCppUTestExt

SOURCES += \
        algorithms.cpp \
        main.cpp \
        phone_book.cpp \
        test_algorithms.c++

HEADERS += \
    algorithms.hpp \
    phone_book.hpp
