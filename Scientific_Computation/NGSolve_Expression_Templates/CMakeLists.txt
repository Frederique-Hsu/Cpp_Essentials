cmake_minimum_required(VERSION 3.20)

set(CURRENT_PROJECT_NAME    NGSolveET)
project(${CURRENT_PROJECT_NAME})

file(GLOB_RECURSE cppsources    "*.c*")
file(GLOB_RECURSE cppheaders    "*.h*")

add_library(${CURRENT_PROJECT_NAME} OBJECT
    ${cppsources}
    ${cppheaders})
set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
    CXX_STANDARD                17
    CXX_EXTENSIONS              NO
    CXX_STANDARD_REQUIRED       YES
    POSITION_INDEPENDENT_CODE   TRUE)
target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC
    "-Wall"
    "-Wextra"
    "-Werror")

add_library(${CURRENT_PROJECT_NAME}-static STATIC
    $<TARGET_OBJECTS:${CURRENT_PROJECT_NAME}>)
set_target_properties(${CURRENT_PROJECT_NAME}-static PROPERTIES
    OUTPUT_NAME "${CURRENT_PROJECT_NAME}")

add_library(${CURRENT_PROJECT_NAME}-shared SHARED
    $<TARGET_OBJECTS:${CURRENT_PROJECT_NAME}>)
set_target_properties(${CURRENT_PROJECT_NAME}-shared PROPERTIES
    OUTPUT_NAME "${CURRENT_PROJECT_NAME}")