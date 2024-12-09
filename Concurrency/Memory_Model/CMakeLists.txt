cmake_minimum_required(VERSION 3.20)

set(CURRENT_PROJECT_NAME    Memory_Model)
project(${CURRENT_PROJECT_NAME})

set(CURRENT_PROJECT_ROOT_DIR    ${CMAKE_CURRENT_SOURCE_DIR})
set(CURRENT_PROJECT_BUILD_DIR   ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
list(FILTER sources EXCLUDE REGEX "${CURRENT_PROJECT_BUILD_DIR}/*")
list(FILTER headers EXCLUDE REGEX "${CURRENT_PROJECT_BUILD_DIR}/*")

add_executable(${CURRENT_PROJECT_NAME}
    ${sources}
    ${headers})
set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
    CXX_STANDARD            17
    CXX_EXTENSIONS          NO
    CXX_STANDARD_REQUIRED   YES)
target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC
    ${CXXFLAGS}
    "-Wno-unused-but-set-variable"
    "-Wno-unused-variable")
target_link_libraries(${CURRENT_PROJECT_NAME} PUBLIC gtest atomic)


enable_testing()
add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)


include(GoogleTest)
gtest_discover_tests(${CURRENT_PROJECT_NAME})