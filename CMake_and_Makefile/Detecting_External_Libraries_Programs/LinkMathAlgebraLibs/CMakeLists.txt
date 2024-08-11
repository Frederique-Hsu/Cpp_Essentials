cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(LinkMathAlgebraLibs LANGUAGES C CXX Fortran)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS NO)
set(CMAKE_C_STANDARD_REQUIRED YES)

include(FortranCInterface)
FortranCInterface_VERIFY(CXX)

FortranCInterface_HEADER(fc_mangle.h
    MACRO_NAMESPACE "FC_"
    SYMBOLS DSCAL DGESV)

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

add_library(math SHARED "")

target_sources(math PRIVATE
    CxxBLAS.cpp CxxBLAS.hpp
    CxxLAPACK.cpp CxxLAPACK.hpp)
target_include_directories(math PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(math PUBLIC ${LAPACK_LIBRARIES})


add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PRIVATE linear-algebra.cpp)
target_link_libraries(${PROJECT_NAME} math)