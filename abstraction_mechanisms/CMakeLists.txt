cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(abstraction_mechanisms LANGUAGES CXX)


list(APPEND COMPILE_OPTIONS
    "-Wall"
    "-Wpedantic"
   "-Werror"
    "-Wno-unused-variable")

#===============================================================================

enable_testing()

add_subdirectory(Inheritance)
add_subdirectory(Hierarchies)
add_subdirectory(generic_prog)
if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_subdirectory(RTTI)
endif()
add_subdirectory(Interface_Polymorph)
add_subdirectory(Cast)
add_subdirectory(classes)
add_subdirectory(templates)
add_subdirectory(experiment)
add_subdirectory(concepts)
add_subdirectory(templates_and_class_hierarchies)
add_subdirectory(meta_prog)
