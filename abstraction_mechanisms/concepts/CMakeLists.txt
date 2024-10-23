cmake_minimum_required(VERSION 3.20)

set(CURRENT_PROJECT_NAME concepts)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME}
    ${sources}
    ${headers})
set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
    CXX_STANDARD            20
    CXX_EXTENSIONS          OFF
    CXX_STANDARD_REQUIRED   ON)

target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC
    ${COMPILE_OPTIONS}
    "-Wno-unused-but-set-variable"
    "-Wno-sign-compare")
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE Catch2::Catch2)


enable_testing()

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND valgrind --leak-check=full $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)
