cmake_minimum_required(VERSION 3.20)

set(CURRENT_PROJECT_NAME concepts)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME}
    ${sources}
    ${headers})

add_dependencies(${CURRENT_PROJECT_NAME} catch2)

set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
    CXX_STANDARD            20
    CXX_EXTENSIONS          OFF
    CXX_STANDARD_REQUIRED   ON)

target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC
    ${COMPILE_OPTIONS}
    "-Wno-unused-but-set-variable"
    "-Wno-sign-compare")

target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${CATCH2_INCLUDE_DIR})
target_link_directories(${CURRENT_PROJECT_NAME} PRIVATE ${CATCH2_LIB_DIR})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE Catch2d)


enable_testing()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_test(NAME UTest_${CURRENT_PROJECT_NAME}
        COMMAND valgrind --leak-check=full $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)
else()
    add_test(NAME UTest_${CURRENT_PROJECT_NAME}
        COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)
endif()