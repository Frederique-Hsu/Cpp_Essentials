cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(abstraction_mechanisms LANGUAGES CXX)


list(APPEND COMPILE_OPTIONS
    "-Wall"
    "-Wpedantic"
    "-Werror"
    "-Wno-overloaded-virtual"
    "-Wno-unused-variable")

enable_testing()

add_subdirectory(Inheritance)
add_subdirectory(Hierarchies)
add_subdirectory(generic_prog)
add_subdirectory(RTTI)
add_subdirectory(Interface_Polymorph)
add_subdirectory(Cast)
add_subdirectory(classes)