cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Parallelize LANGUAGES CXX Fortran C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS NO)
set(CMAKE_C_STANDARD_REQUIRED YES)

find_package(OpenMP REQUIRED)


add_executable(${PROJECT_NAME}-cxx parallel_main.cpp)
target_link_libraries(${PROJECT_NAME}-cxx PUBLIC OpenMP::OpenMP_CXX)


file(GLOB fortran_sources *.f90)
add_executable(${PROJECT_NAME}-fortran ${fortran_sources})
target_link_libraries(${PROJECT_NAME}-fortran PUBLIC OpenMP::OpenMP_Fortran)


include(CMakePrintHelpers)
cmake_print_properties(
    TARGETS
        OpenMP::OpenMP_CXX
    PROPERTIES
        INTERFACE_COMPILE_OPTIONS
        INTERFACE_INCLUDE_DIRECTORIES
        INTERFACE_LINK_LIBRARIES
    )

add_executable(${PROJECT_NAME}-c parallel.c)
target_link_libraries(${PROJECT_NAME}-c PUBLIC OpenMP::OpenMP_C)