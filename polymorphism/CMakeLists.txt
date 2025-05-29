cmake_minimum_required(VERSION  3.20)

project(polymorphism)

file(GLOB_RECURSE sources "*.c*")
file(GLOB_RECURSE headers "*.h*")
list(FILTER sources EXCLUDE REGEX "build/*")
list(FILTER headers EXCLUDE REGEX "build/*")

include(ExternalProject)
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED   TRUE)

FetchContent_Declare(GTest
    GIT_REPOSITORY      https://github.com/google/googletest.git
    GIT_TAG             main
    GIT_SHALLOW         TRUE
    GIT_PROGRESS        TRUE)

FetchContent_MakeAvailable(GTest)


add_executable(${PROJECT_NAME}
    ${sources}
    ${headers})
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD    20
    CXX_EXTENSIONS  NO
    CXX_STANDARD_REQUIRED   YES)
target_compile_options(${PROJECT_NAME} PUBLIC
    "-Wall"
    "-Wextra"
    "-Werror")
target_link_libraries(${PROJECT_NAME} PRIVATE
    gtest)

enable_testing()

add_test(NAME UTest_${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})