cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CURRENT_PROJECT_NAME templates)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME} ${sources} ${headers})
add_dependencies(${CURRENT_PROJECT_NAME} googletest)

target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${GOOGLETEST_INCLUDE_DIR})
target_link_directories(${CURRENT_PROJECT_NAME} PRIVATE ${GOOGLETEST_LIB_DIR})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE gtest)
target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC 
    ${COMPILE_OPTIONS}
    "-Wno-pedantic"
    "-Wno-sign-compare"
    "-Wno-c++20-extensions")
set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
    CXX_STANDARD            17
    CXX_EXTENSIONS          OFF
    CXX_STANDARD_REQUIRED   ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # target_compile_definitions(${CURRENT_PROJECT_NAME} PRIVATE "DEBUG_WITH_LOG")
endif()


add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)
    
if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    include(GoogleTest)
    gtest_discover_tests(${CURRENT_PROJECT_NAME})
endif()
