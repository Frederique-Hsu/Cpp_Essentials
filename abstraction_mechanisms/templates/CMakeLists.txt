cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CURRENT_PROJECT_NAME templates)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE GTest::gtest)
target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC 
    "-Wno-pedantic"
    "-Wno-sign-compare")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # target_compile_definitions(${CURRENT_PROJECT_NAME} PRIVATE "DEBUG_WITH_LOG")
endif()


add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND valgrind --leak-check=full $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)
    
include(GoogleTest)
gtest_discover_tests(${CURRENT_PROJECT_NAME})