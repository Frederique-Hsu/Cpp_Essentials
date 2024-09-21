set(CURRENT_PROJECT_NAME generic_prog)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
# list(FILTER sources EXCLUDE REGEX "${CURRENT_DIR}/Concepts/string.cpp")
# list(FILTER headers EXCLUDE REGEX "${CURRENT_DIR}/Concepts/string.hpp")

add_executable(${CURRENT_PROJECT_NAME} "")
target_sources(${CURRENT_PROJECT_NAME} PRIVATE ${sources} ${headers})

target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE Catch2::Catch2)

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}> --success)