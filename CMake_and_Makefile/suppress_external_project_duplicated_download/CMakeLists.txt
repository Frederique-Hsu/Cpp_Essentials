cmake_minimum_required(VERSION 3.20)

project(suppress_external_project_duplicated_download)


include(googletest.cmake)
# include(boost.cmake)

file(GLOB_RECURSE sources "*.cpp")
file(GLOB_RECURSE headers "*.hpp")
list(FILTER sources EXCLUDE REGEX "build/*")
list(FILTER headers EXCLUDE REGEX "build/*")


message(STATUS "CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}")

add_executable(${CMAKE_PROJECT_NAME}
    ${sources}
    ${headers})

add_dependencies(${CMAKE_PROJECT_NAME} GTest)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD        17
    CXX_EXTENSIONS      NO
    CXX_STANDARD_REQUIRED   YES)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${GTEST_INCLUDE_DIR})

target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${GTEST_LIB_DIR})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    gtest
    gmock)


#===============================================================================

enable_testing()

add_test(NAME UTest_${CMAKE_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})