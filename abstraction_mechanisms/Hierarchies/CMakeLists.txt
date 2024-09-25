set(CURRENT_PROJECT_NAME Hierarchies)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# find_package(Boost REQUIRED COMPONENTS unit_test_framework)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME} "")
target_sources(${CURRENT_PROJECT_NAME} PRIVATE
    ${sources}
    ${headers})


target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_compile_options(${CURRENT_PROJECT_NAME} PRIVATE "-Wno-reorder")
target_compile_options(${CURRENT_PROJECT_NAME} PRIVATE "-Wno-unused-private-field")

target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE boost_unit_test_framework)


if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${CURRENT_PROJECT_NAME} PRIVATE "DEBUG_WITH_LOG")
endif()

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes 
            $<TARGET_FILE:${CURRENT_PROJECT_NAME}> --log_level=test_suite --report_level=short)