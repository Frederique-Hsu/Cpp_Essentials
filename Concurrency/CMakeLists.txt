cmake_minimum_required(VERSION 3.20)

project(Concurrency)


option(BUILD_UT_FROM_SRC 
       "Git clone repository of the unit test framework from GitHub, and build the library from source"
       ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
if (${BUILD_UT_FROM_SRC})
    FetchContent_Declare(GTest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             main)
    
    FetchContent_MakeAvailable(GTest)
endif()

enable_testing()

add_subdirectory(basics)
add_subdirectory(Memory_Model)
add_subdirectory(multi_threads)