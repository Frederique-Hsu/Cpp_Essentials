cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(message LANGUAGES CXX)

add_library(message SHARED
    Message.hpp
    Message.cpp)

add_executable(hello-world hello-world.cpp)

target_link_libraries(hello-world message)