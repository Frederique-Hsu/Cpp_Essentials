cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Animals LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(animals OBJECT
    Animal.cpp
    Animal.hpp
    Cat.cpp
    Cat.hpp
    Dog.cpp
    Dog.hpp
    Factory.hpp
    Factory_Impl.hpp)
set_target_properties(animals PROPERTIES
    CXX_STANDARD 11
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1)

add_library(animals-static STATIC $<TARGET_OBJECTS:animals>)
set_target_properties(animals-static PROPERTIES OUTPUT_NAME "animals")

add_library(animals-shared SHARED $<TARGET_OBJECTS:animals>)
set_target_properties(animals-shared PROPERTIES OUTPUT_NAME "animals")

add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON)
target_link_libraries(${PROJECT_NAME} animals-shared)