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

add_dependencies(${CURRENT_PROJECT_NAME} catch2)

target_sources(${CURRENT_PROJECT_NAME} PRIVATE ${sources} ${headers})

target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC 
    ${COMPILE_OPTIONS}
    "-Wno-invalid-constexpr")

target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${CATCH2_INCLUDE_DIR})
target_link_directories(${CURRENT_PROJECT_NAME} PRIVATE ${CATCH2_LIB_DIR})

target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE 
    $<$<CONFIG:Debug>:Catch2d>
    $<$<NOT:$<CONFIG:Debug>>:Catch2>)

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}> --success)
    

if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    include(Catch)
    catch_discover_tests(${CURRENT_PROJECT_NAME})
endif()
