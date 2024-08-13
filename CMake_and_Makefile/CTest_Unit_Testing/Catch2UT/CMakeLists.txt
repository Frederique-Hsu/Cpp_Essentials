cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Catch2UT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(Catch2 REQUIRED)

add_library(sum_integers SHARED sum_integers.cpp sum_integers.hpp)

# Testing
add_executable(cpp_test main.cpp test.cpp)
target_link_libraries(cpp_test PUBLIC sum_integers Catch2::Catch2)

enable_testing()

add_test(NAME catch_test
    COMMAND $<TARGET_FILE:cpp_test> --success --colour-mode ansi)