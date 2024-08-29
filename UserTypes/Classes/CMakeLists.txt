cmake_minimum_required(VERSION 3.5)

project(Classes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED CONFIG)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
list(FILTER sources EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/build/")

add_executable(${PROJECT_NAME} ${sources} ${headers})

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest)

add_test(NAME UTest_${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>)