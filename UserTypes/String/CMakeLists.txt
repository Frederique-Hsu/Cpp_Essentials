cmake_minimum_required(VERSION 3.5)

project(String LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
list(FILTER sources EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/build/")

find_package(Catch2 3 REQUIRED)

add_executable(${PROJECT_NAME} ${sources} ${headers})

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2)