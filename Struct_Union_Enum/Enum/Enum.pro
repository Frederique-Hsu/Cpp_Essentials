TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgtest -lpthread

SOURCES += \
    enumerate.cpp \
    main.cpp \
    test_enumerate.c++

HEADERS += \
    enumerate.hpp
