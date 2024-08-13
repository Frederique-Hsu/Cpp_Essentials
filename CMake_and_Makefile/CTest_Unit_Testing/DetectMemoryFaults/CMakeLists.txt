cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(DetectMemoryFaults LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)


add_library(check_memory_leaks SHARED
    leaky_implementation.cpp
    leaky_implementation.hpp)

add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test PRIVATE check_memory_leaks)

find_program(MEMORYCHECK_COMMAND NAMES valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=fullfl")

# add memcheck test action
include(CTest)

enable_testing()
add_test(NAME cpp_test
    COMMAND $<TARGET_FILE:cpp_test>)