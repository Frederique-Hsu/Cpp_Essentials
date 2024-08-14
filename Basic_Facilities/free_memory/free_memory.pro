TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        free_memory.cpp \
        main.cpp \
        placement.cpp \
        test_free_memory.c++ \
        test_placement.c++

HEADERS += \
    free_memory.hpp \
    placement.hpp
