cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Distributed_Parallelize LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(MPI REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC MPI::MPI_CXX)