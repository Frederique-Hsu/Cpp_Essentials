set(CURRENT_PROJECT_NAME RTTI)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# include(FetchContent)
# FetchContent_Declare(CppUTest
#     GIT_REPOSITORY  https://github.com/cpputest/cpputest.git
#     GIT_TAG         master)

# set(TESTS OFF CACHE BOOL "Switch On CppUTest Test build")
# FetchContent_MakeAvailable(CppUTest)

find_package(CppUTest CONFIG)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE CppUTest::CppUTest)

#===============================================================================

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}> -c -v)