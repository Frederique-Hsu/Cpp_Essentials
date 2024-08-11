# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(SimpleUT LANGUAGES CXX)

# require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PythonInterp REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)

# example library
add_library(sum_integers SHARED sum_integers.cpp)

# main code
add_executable(sum_up main.cpp)
target_link_libraries(sum_up sum_integers)

# testing binary
add_executable(cpp_test test.cpp)
target_link_libraries(cpp_test sum_integers)

# enable testing functionality
enable_testing()

# define tests
add_test(NAME bash_test
    COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh $<TARGET_FILE:sum_up>)

add_test(NAME cpp_test
    COMMAND $<TARGET_FILE:cpp_test>)

add_test(NAME python_test_long
    COMMAND ${PYTHON_EXECUTABLE} test.py --executable $<TARGET_FILE:sum_up>
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME python_test_short
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test.py --short --executable $<TARGET_FILE:sum_up>)

# add_test(NAME python_test
#     COMMAND
#         ${CMAKE_COMMAND} -E env
#         ACCOUNT_MODULE_PATH=${CMAKE_CURRENT_SOURCE_DIR}
#         ACCOUNT_HEADER_FILE=${CMAKE_CURRENT_SOURCE_DIR}/account/account.h
#         ACCOUNT_LIBRARY_FILE=$<TARGET_FILE:account>
#         ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/account/test.py
#     )