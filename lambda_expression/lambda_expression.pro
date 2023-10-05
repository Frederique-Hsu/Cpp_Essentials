TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle qt

LIBS += -lgtest -lpthread

SOURCES += \
    lambda.cpp \
    lambda_expressions.cpp \
    main.cpp \
    test_lambda_expressions.c++


HEADERS += \
    lambda.hpp \
    lambda_expressions.hpp
