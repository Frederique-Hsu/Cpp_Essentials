cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(message LANGUAGES CXX)

# add_library(Message STATIC
add_library(Message SHARED
# add_library(Message OBJECT
# add_library(Message MODULE
    Message.cpp
    Message.hpp)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Message)