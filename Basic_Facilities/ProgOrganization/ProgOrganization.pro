TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lCppUTest

SOURCES += \
        link_fn_ptr.cpp \
        linking/file1.cpp \
        linking/file2.cpp \
        linking/test_linking.c++ \
        main.cpp \
        my.string.cpp \
        test.my.string.c++ \
        test_link_fn_ptr.c++

HEADERS += \
    link_fn_ptr.hpp \
    linking/common.hpp \
    my.string.hpp \
    test_link_fn_ptr.h++

DISTFILES += \
    cmyio
