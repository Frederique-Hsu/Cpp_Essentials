cmake_minimum_required(VERSION 3.5)

project(Classes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
list(FILTER sources EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/build/")

add_executable(${PROJECT_NAME} ${sources} ${headers})

add_dependencies(${PROJECT_NAME} googletest)

target_include_directories(${PROJECT_NAME} PRIVATE ${GOOGLETEST_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${GOOGLETEST_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)

add_test(NAME UTest_${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>)
