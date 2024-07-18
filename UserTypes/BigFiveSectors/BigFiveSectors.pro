TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lCatch2

DEFINES += DEBUG

SOURCES += \
        big_five_sectors.cpp \
        constructor_destructor.cpp \
        initialization.cpp \
        main.cpp \
        test_big_five_sectors.c++ \
        test_constructor_destructor.c++ \
        test_initialization.c++ \
        test_my_container.c++

DISTFILES += \
    CMakeLists.txt

HEADERS += \
    big_five_sectors.hpp \
    constructor_destructor.hpp \
    finally.hpp \
    finally_impl.hpp \
    initialization.hpp \
    my_container.hpp \
    pointers.hpp \
    pointers_impl.hpp
