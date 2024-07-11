TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Driver.cpp \
        Error.cpp \
        Lexer.cpp \
        Parser.cpp \
        Table.cpp \
        main.cpp \
        test_desktop_calculator.c++

HEADERS += \
    Driver.hpp \
    Error.hpp \
    Lexer.hpp \
    Parser.hpp \
    Parser_Impl.hpp \
    Table.hpp
