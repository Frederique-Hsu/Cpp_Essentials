# File name     : CMakeLists.txt
# Description   : Write a CMake script to build current project.
# Author        : Frederique Hsu
# Date          : Thur.     18 May 2023
#
#


cmake_minimum_required(VERSION 3.10)

project(Sqrt VERSION 1.0)
configure_file(Config.h.in Config.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Sqrt Calc_sqrt.cpp)

target_include_directories(Sqrt PUBLIC "${PROJECT_BINARY_DIR}")