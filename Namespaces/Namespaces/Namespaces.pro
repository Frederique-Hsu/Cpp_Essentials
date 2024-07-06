TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Graph.lib.cpp \
        Text.lib.cpp \
        main.cpp \
        misc.cpp \
        namespace_combination_selection/A.cpp \
        namespace_combination_selection/B.cpp \
        namespace_combination_selection/namespace_combination_selection.cpp \
        namespace_combination_selection/namespace_for_versioning.cpp \
        namespace_combination_selection/test_namespace_for_versioning.c++ \
        namespace_combination_selection/test_std_extension.c++ \
        namespace_combination_selection/test_user.c++ \
        namespace_combination_selection/user.cpp \
        test_libs.c++ \
        test_namespaces.c++ \
        utils.cpp

HEADERS += \
    Graph.lib.hpp \
    Text.lib.hpp \
    misc.hpp \
    namespace_combination_selection/A.h \
    namespace_combination_selection/B.h \
    namespace_combination_selection/namespace_combination_selection.hpp \
    namespace_combination_selection/namespace_for_versioning.hpp \
    namespace_combination_selection/std_extension.hpp \
    namespace_combination_selection/user.h \
    utils.hpp
