cmake_minimum_required(VERSION 3.20)

project(Bjarne_Stroustrup_CPP)


include(CMake_and_Makefile/cmakes/googletest.cmake)
include(CMake_and_Makefile/cmakes/boost.cmake)
include(CMake_and_Makefile/cmakes/catch2.cmake)
include(CMake_and_Makefile/cmakes/cpputest.cmake)

enable_testing()

add_subdirectory(abstraction_mechanisms)
add_subdirectory(Concurrency)
add_subdirectory(UserTypes)

# add_subdirectory(UserSmartPointer)

add_subdirectory(Template_Meta_Programming)