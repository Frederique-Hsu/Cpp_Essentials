cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(EnableEigenVectorization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(Eigen3 3.4 REQUIRED CONFIG)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-march=native" _march_native_works)
check_cxx_compiler_flag("-xHost" _xhost_works)

set(_CXX_FLAGS)
if(_march_native_works)
    message(STATUS "Using processor's vector instructions (-march=native compiler flag set)")
    set(_CXX_FLAGS "-march=native")
elseif(_xhost_works)
    message(STATUS "Using processor's vector instructions (-xHost compiler flag set)")
    set(_CXX_FLAGS "-xHost")
else()
    message(STATUS "No suitable compiler flag found for vectorization")
endif()


add_executable(DisableEigenVectorization linear_algebra.cpp)
target_link_libraries(DisableEigenVectorization PRIVATE Eigen3::Eigen)

add_executable(EnableEigenVectorization linear_algebra.cpp)
target_compile_options(EnableEigenVectorization PRIVATE ${_CXX_FLAGS})
target_link_libraries(EnableEigenVectorization PRIVATE Eigen3::Eigen)