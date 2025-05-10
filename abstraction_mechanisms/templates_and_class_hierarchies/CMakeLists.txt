cmake_minimum_required(VERSION 3.10)

set(CURRENT_PROJECT_NAME templates_and_hierarchies)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
list(FILTER sources EXCLUDE REGEX "linearizing_class_hierarchies/")
list(FILTER headers EXCLUDE REGEX "linearizing_class_hierarchies/")

add_executable(${CURRENT_PROJECT_NAME}
    ${sources}
    ${headers})
set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
    CXX_STANDARD            20
    CXX_EXTENSIONS          OFF
    CXX_STANDARD_REQUIRED   ON)
target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC
    ${COMPILE_OPTIONS}
    "-Wno-unused-but-set-variable")
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE GTest::gtest)


enable_testing()

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND valgrind --leak-check=full $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)

include(GoogleTest)
gtest_discover_tests(${CURRENT_PROJECT_NAME})