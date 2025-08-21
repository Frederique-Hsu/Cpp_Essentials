cmake_minimum_required(VERSION 3.5)

project(BigFiveSectors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
list(FILTER sources EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/build/")

add_executable(${PROJECT_NAME} ${sources} ${headers})

add_dependencies(${PROJECT_NAME} catch2)

target_include_directories(${PROJECT_NAME} PRIVATE ${CATCH2_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${CATCH2_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2d)

add_test(NAME UTest_${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>)
