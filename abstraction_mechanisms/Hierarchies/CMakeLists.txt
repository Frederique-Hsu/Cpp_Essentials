set(CURRENT_PROJECT_NAME Hierarchies)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)


file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME} "")
target_sources(${CURRENT_PROJECT_NAME} PRIVATE
    ${sources}
    ${headers})

add_dependencies(${CURRENT_PROJECT_NAME} Boost)

target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_compile_options(${CURRENT_PROJECT_NAME} PRIVATE "-Wno-reorder")
target_compile_options(${CURRENT_PROJECT_NAME} PRIVATE "-Wno-unused-private-field")

target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${BOOST_INCLUDE_DIR})
target_link_directories(${CURRENT_PROJECT_NAME} PRIVATE ${BOOST_LIB_DIR})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE boost_unit_test_framework)

target_compile_definitions(${CURRENT_PROJECT_NAME} PRIVATE "DEBUG_WITH_LOG")


add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}> --log_level=test_suite --report_level=short)