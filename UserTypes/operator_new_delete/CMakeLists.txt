cmake_minimum_required(VERSION 3.5)

project(operator_new_delete LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
list(FILTER sources EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/build/")

add_executable(${PROJECT_NAME} ${sources} ${headers})

add_test(NAME UTest_${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>)