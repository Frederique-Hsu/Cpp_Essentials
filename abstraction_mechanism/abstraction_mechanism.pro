TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lgmock -lpthread

SOURCES += \
        classes/Container.cpp \
        classes/List_container.cpp \
        classes/Vector.cpp \
        classes/Vector_container.cpp \
        classes/complex.cpp \
        classes/hierarchy/Circle.cpp \
        classes/hierarchy/Point.cpp \
        classes/hierarchy/Shape.cpp \
        classes/test_Container.cpp \
        classes/test_Vector.cpp \
        main.cpp

HEADERS += \
    classes/Container.hpp \
    classes/List_container.hpp \
    classes/Vector.hpp \
    classes/Vector_container.hpp \
    classes/complex.hpp \
    classes/hierarchy/Circle.hpp \
    classes/hierarchy/Point.hpp \
    classes/hierarchy/Shape.hpp
