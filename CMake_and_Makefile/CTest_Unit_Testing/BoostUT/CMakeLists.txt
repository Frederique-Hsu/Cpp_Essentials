cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(BoostUT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(sum_integers OBJECT
    sum_integers.cpp
    sum_integers.hpp)
set_target_properties(sum_integers PROPERTIES
    POSITION_INDEPENDENT_CODE YES)

add_library(sum_integers-static STATIC $<TARGET_OBJECTS:sum_integers>)
set_target_properties(sum_integers-static PROPERTIES OUTPUT_NAME "sum_integers")

add_library(sum_integers-shared SHARED $<TARGET_OBJECTS:sum_integers>)
set_target_properties(sum_integers-shared PROPERTIES OUTPUT_NAME "sum_integers")

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(cpp_test main.cpp test.cpp)
target_link_libraries(cpp_test PRIVATE sum_integers-shared Boost::unit_test_framework)
target_compile_definitions(cpp_test PRIVATE BOOST_TEST_DYN_LINK)


#===============================================================================

enable_testing()

add_test(NAME boost_test
    COMMAND $<TARGET_FILE:cpp_test>)
