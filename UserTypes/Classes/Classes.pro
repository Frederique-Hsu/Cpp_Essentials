TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        Date.cpp \
        basics.cpp \
        main.cpp \
        test_basics.c++ \
        test_date.c++

HEADERS += \
    Date.hpp \
    basics.hpp \
    member_type.hpp \
    test_date.h++
