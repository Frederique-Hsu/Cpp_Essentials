cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(compute-areas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")

list(APPEND flags "-fPIC" "-Wall" "-Werror")
if(NOT WIN32)
    list(APPEND flags "-Wextra" "-Wpedantic")
endif()

set(COMPILER_FLAGS)
set(COMPILER_FLAGS_DEBUG)
set(COMPILER_FLAGS_RELEASE)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    list(APPEND CXX_FLAGS "-fno-rtti" "-fno-exceptions")
    list(APPEND CXX_FLAGS_DEBUG
        "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override")
    list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    list(APPEND CXX_FLAGS "-fno-rtti" "-Qunused-arguments" "-fcolor-diagnostics")
    list(APPEND CXX_FLAGS_DEBUG "-Wdocumentation")
    list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()


file(GLOB geometry_sources geometry_*.cpp)
file(GLOB geometry_headers geometry_*.hpp)

add_library(geometry STATIC
    ${geometry_sources}
    ${geometry_headers})
target_compile_options(geometry PRIVATE
    ${CXX_FLAGS}
    "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>"
    "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>")

add_executable(${PROJECT_NAME} compute-areas.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC")

target_link_libraries(${PROJECT_NAME} geometry)