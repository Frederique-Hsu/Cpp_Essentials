cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(abstraction_mechanisms LANGUAGES CXX)


list(APPEND COMPILE_OPTIONS
    "-Wall"
    "-Wpedantic"
   "-Werror"
    "-Wno-unused-variable")

option(BUILD_UNIT_TEST_FRAMWORK_FROM_SOURCE "Git clone the unit test framework and build from source" ON)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_DIR ${ROOT_DIR}/build)


include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)     # 设置该变量，告诉CMake不要在断网情况下检查更新，而是使用先前已下载好的代码库。
                                                # 若已存在代码库的情况下，不要去再次下载，这样可大幅节省Re/Configure CMake的时间。
if(BUILD_UNIT_TEST_FRAMWORK_FROM_SOURCE)
    FetchContent_Declare(cpputest
        GIT_REPOSITORY  https://github.com/cpputest/cpputest.git
        GIT_TAG         master)
    FetchContent_MakeAvailable(cpputest)

    FetchContent_Declare(Catch2
        GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
        GIT_TAG         v3.7.0)
    FetchContent_MakeAvailable(Catch2)

    FetchContent_Declare(Boost
        GIT_REPOSITORY      https://github.com/boostorg/boost.git
        GIT_TAG             master
        GIT_SHALLOW         TRUE
        CMAKE_ARGS
            -DBUILD_SHARED_LIBS=ON)
    FetchContent_MakeAvailable(Boost)

    FetchContent_Declare(GTest
        GIT_REPOSITORY  https://github.com/google/googletest.git
        GIT_TAG         v1.17.0
        GIT_SHALLOW     TRUE)
    FetchContent_MakeAvailable(GTest)
else()
    find_package(GTest REQUIRED CONFIG)
    find_package(CppUTest REQUIRED)
    find_package(Catch2 REQUIRED CONFIG)
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)
endif()


#===============================================================================

enable_testing()

add_subdirectory(Inheritance)
add_subdirectory(Hierarchies)
add_subdirectory(generic_prog)
if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_subdirectory(RTTI)
endif()
add_subdirectory(Interface_Polymorph)
add_subdirectory(Cast)
add_subdirectory(classes)
add_subdirectory(templates)
add_subdirectory(experiment)
add_subdirectory(concepts)
add_subdirectory(templates_and_class_hierarchies)
add_subdirectory(meta_prog)
