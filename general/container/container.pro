TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS = -lgtest

SOURCES += \
        main.cpp \
        test_vector_container.cpp \
        vector_container.cpp

HEADERS += \
    vector_container.hpp
