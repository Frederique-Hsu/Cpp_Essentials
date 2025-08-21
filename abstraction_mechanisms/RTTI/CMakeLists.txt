cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CURRENT_PROJECT_NAME RTTI)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME} ${sources} ${headers})

add_dependencies(${CURRENT_PROJECT_NAME} cpputest)

target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${CPPUTEST_INCLUDE_DIR})
target_link_directories(${CURRENT_PROJECT_NAME} PRIVATE ${CPPUTEST_LIB_DIR})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE CppUTest)

#===============================================================================

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}> -c -v)