TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest

SOURCES += \
        atomic.cpp \
        main.cpp \
        memory_location.cpp

HEADERS += \
    atomic.hpp \
    atomic_impl.hpp \
    memory_location.hpp
