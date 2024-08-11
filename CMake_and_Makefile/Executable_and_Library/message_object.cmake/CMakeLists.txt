cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(message LANGUAGES CXX)


add_library(Message OBJECT
    Message.cpp
    Message.hpp)

set_target_properties(Message PROPERTIES
    POSITION_INDEPENDENT_CODE 1)

add_library(Message-shared SHARED $<TARGET_OBJECTS:Message>)
set_target_properties(Message-shared PROPERTIES OUTPUT_NAME "Message")

add_library(Message-static STATIC $<TARGET_OBJECTS:Message>)
set_target_properties(Message-static PROPERTIES OUTPUT_NAME "Message")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Message-shared)