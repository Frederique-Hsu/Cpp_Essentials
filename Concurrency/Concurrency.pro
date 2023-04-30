TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest

SOURCES += \
    Concurrency.cpp \
    calc.cpp \
    multi_threads.cpp \
    test_multi_threads_calc.c++ \
    test_parallel_accumulate.c++

HEADERS += \
    calc.hpp \
    multi_threads.hpp \
    share_data.hpp \
    test_parallel_accumulate.h++
