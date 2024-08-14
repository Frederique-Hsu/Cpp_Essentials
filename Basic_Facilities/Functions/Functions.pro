TEMPLATE = app
CONFIG += console
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lgtest -lpthread

SOURCES += \
        arguments/array_arguments.cpp \
        arguments/default_arguments.cpp \
        arguments/function_arguments.cpp \
        arguments/list_arguments.cpp \
        arguments/test_arguments.c++ \
        arguments/variadic_arguments.cpp \
        constexpr_functions.cpp \
        function_overload/function_overload.cpp \
        function_overload/test_function_overload.c++ \
        function_pointer/function_pointer.cpp \
        function_pointer/test_algorithm_with_function_pointer.c++ \
        function_pointer/test_function_pointer.c++ \
        functions.cpp \
        macros/macros.cpp \
        macros/test_macros.c++ \
        main.cpp \
        test_constexpr_functions.c++ \
        test_functions.c++

HEADERS += \
    arguments/array_arguments.hpp \
    arguments/default_arguments.hpp \
    arguments/function_arguments.hpp \
    arguments/list_arguments.hpp \
    arguments/test_arguments.h++ \
    arguments/variadic_arguments.hpp \
    constexpr_functions.hpp \
    function_overload/function_overload.hpp \
    function_pointer/function_pointer.hpp \
    function_pointer/test_algorithm_with_function_pointer.h++ \
    function_templates.hpp \
    functions.hpp \
    macros/macros.hpp \
    test_constexpr_functions.h++
