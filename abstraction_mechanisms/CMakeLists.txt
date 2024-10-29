cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(abstraction_mechanisms LANGUAGES CXX)


list(APPEND COMPILE_OPTIONS
    "-Wall"
    "-Wpedantic"
    "-Werror"
    "-Wno-unused-variable")

option(BUILD_UNIT_TEST_FRAMWORK_FROM_SOURCE "Git clone the unit test framework and build from source" ON)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BUILD_DIR ${ROOT_DIR}/build)


set(GTest_SOURCE_DIR ${BUILD_DIR}/_deps/gtest-src)
set(GTest_BINARY_DIR ${BUILD_DIR}/_deps/gtest-build)
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)     # 设置该变量，告诉CMake不要在断网情况下检查更新，而是使用先前已下载好的代码库。
                                                # 若已存在代码库的情况下，不要去再次下载，这样可大幅节省Re/Configure CMake的时间。

if(BUILD_UNIT_TEST_FRAMWORK_FROM_SOURCE)
    FetchContent_Declare(GTest
        GIT_REPOSITORY  https://github.com/google/googletest.git
        GIT_TAG         main)

    FetchContent_GetProperties(GTest)
    if (NOT GTest_POPULATED)
        FetchContent_Populate(GTest)
        add_subdirectory(${GTest_SOURCE_DIR} ${GTest_BINARY_DIR})

    endif()
else()
    find_package(GTest REQUIRED CONFIG)
endif()


set(CppUTest_SOURCE_DIR ${BUILD_DIR}/_deps/cpputest-src)
set(CppUTest_BINARY_DIR ${BUILD_DIR}/_deps/cpputest-build)
if(BUILD_UNIT_TEST_FRAMWORK_FROM_SOURCE)
    FetchContent_Declare(CppUTest
        GIT_REPOSITORY  https://github.com/cpputest/cpputest.git
        GIT_TAG         master)

    FetchContent_GetProperties(CppUTest)
    if(NOT CppUTest_POPULATED)
        FetchContent_Populate(CppUTest)
        add_subdirectory(${CppUTest_SOURCE_DIR} ${CppUTest_BINARY_DIR})
    endif()
else()
    find_package(CppUTest REQUIRED)
endif()


set(Catch2_SOURCE_DIR ${BUILD_DIR}/_deps/catch2-src)
set(Catch2_BINARY_DIR ${BUILD_DIR}/_deps/catch2-build)
if(BUILD_UNIT_TEST_FRAMWORK_FROM_SOURCE)
    FetchContent_Declare(Catch2
        GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
        GIT_TAG         v3.7.0)

    FetchContent_GetProperties(Catch2)
    if(NOT Catch2_POPULATED)
        FetchContent_Populate(Catch2)
        add_subdirectory(${Catch2_SOURCE_DIR} ${Catch2_BINARY_DIR})
    endif()
else()
    find_package(Catch2 REQUIRED CONFIG)
endif()


set(boost_unit_test_SOURCE_DIR ${BUILD_DIR}/_deps/boost-src)
set(boost_unit_test_BINARY_DIR ${BUILD_DIR}/_deps/boost-build)
if(BUILD_UNIT_TEST_FRAMWORK_FROM_SOURCE)
    FetchContent_Declare(Boost
        GIT_REPOSITORY      https://github.com/boostorg/boost.git
        GIT_TAG             master)

    FetchContent_GetProperties(Boost)
    if(NOT Boost_POPULATED)
        FetchContent_Populate(Boost)
        add_subdirectory(${boost_unit_test_SOURCE_DIR} ${boost_unit_test_BINARY_DIR})
    endif()
else()
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)
endif()


#===============================================================================

enable_testing()

add_subdirectory(Inheritance)
add_subdirectory(Hierarchies)
add_subdirectory(generic_prog)
add_subdirectory(RTTI)
add_subdirectory(Interface_Polymorph)
add_subdirectory(Cast)
add_subdirectory(classes)
add_subdirectory(templates)
add_subdirectory(experiment)
add_subdirectory(concepts)
add_subdirectory(templates_and_class_hierarchies)
add_subdirectory(meta_prog)