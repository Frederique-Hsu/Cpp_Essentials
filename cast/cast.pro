TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle qt

LIBS += -lgtest -lpthread

SOURCES += \
    cast.cpp \
    main.cpp \
    test_cast.c++



HEADERS += \
    cast.hpp
