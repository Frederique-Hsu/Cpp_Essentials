TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgtest -lpthread

SOURCES += \
    entry.cpp \
    main.cpp \
    test_entry.c++ \
    test_union.c++ \
    union.cpp

HEADERS += \
    entry.hpp \
    test_entry.h++ \
    union.hpp
