cmake_minimum_required(VERSION 3.5)

project(BigFiveSectors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
list(FILTER sources EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/build/")

add_executable(BigFiveSectors ${sources} ${headers})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Catch2::Catch2)
