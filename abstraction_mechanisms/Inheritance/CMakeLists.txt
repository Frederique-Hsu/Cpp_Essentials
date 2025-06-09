cmake_minimum_required(VERSION 3.20)

set(CURRENT_PROJECT_NAME Inheritance)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB_RECURSE sources "*.c*")
file(GLOB_RECURSE headers "*.h*")

add_executable(${CURRENT_PROJECT_NAME}
    ${sources}
    ${headers})

message(STATUS "Current COMPILE_OPTIONS = ${COMPILE_OPTIONS}")
target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC
    ${COMPILE_OPTIONS}
    "-Wno-unused-but-set-variable"
    "-Wno-unused-private-field"
    "-Wno-overloaded-virtual")
target_link_libraries(${CURRENT_PROJECT_NAME} PUBLIC gtest)

message(STATUS "Current CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${CURRENT_PROJECT_NAME} PRIVATE "DEBUG_WITH_LOG")
endif()


#===============================================================================

enable_testing()

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)

if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    include(GoogleTest)
    gtest_discover_tests(${CURRENT_PROJECT_NAME})
endif()
