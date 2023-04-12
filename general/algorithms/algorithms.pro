TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS = -lCppUTest -lCppUTestExt
LIBS += -lgtest

SOURCES += \
        algorithms.cpp \
        main.cpp \
        phone_book.cpp \
        stream_iterator.cpp \
        test_algorithms.c++ \
        test_stream_iterator.c++ \
        test_user_defined_algorithms.c++

HEADERS += \
    algorithms.hpp \
    phone_book.hpp \
    stream_iterator.hpp \
    user_defined_algorithms.hpp
