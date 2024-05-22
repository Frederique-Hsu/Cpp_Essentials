TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

LIBS = -lgtest -lpthread

SOURCES +=  \
    loop.cpp \
    main.cpp \
    statements.cpp \
    test_statements.c++


HEADERS +=  \
    loop.hpp \
    statements.hpp