cmake_minimum_required(VERSION 3.20)

set(CURRENT_PROJECT_NAME    unit_tests)
project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

file(GLOB_RECURSE cppsources "*.c*")
file(GLOB_RECURSE cppheaders "*.h*")

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED   TRUE)

option(BUILD_UT_FROM_SRC
       "Git clone the repository of Unit Test Framework from GitHub, and built it from source"
        ON)
if(${BUILD_UT_FROM_SRC})
    FetchContent_Declare(GTest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             main)
    
    FetchContent_MakeAvailable(GTest)
endif()

add_executable(${CURRENT_PROJECT_NAME}
    ${cppsources}
    ${cppheaders})
set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
    CXX_STANDARD            14
    CXX_EXTENSIONS          NO
    CXX_STANDARD_REQUIRED   YES)
target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC
    "-Wall"
    "-Wextra"
    "-Werror")
target_link_libraries(${CURRENT_PROJECT_NAME} PUBLIC gtest NGSolveET)


enable_testing()
add_test(NAME ${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)

include(GoogleTest)
gtest_discover_tests(${CURRENT_PROJECT_NAME})
