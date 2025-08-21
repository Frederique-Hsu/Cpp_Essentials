set(CURRENT_PROJECT_NAME Interface_Polymorph)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME} ${sources} ${headers})

add_dependencies(${CURRENT_PROJECT_NAME} Boost)

target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_include_directories(${CURRENT_PROJECT_NAME} PRIVATE ${BOOST_INCLUDE_DIR})
target_link_directories(${CURRENT_PROJECT_NAME} PRIVATE ${BOOST_LIB_DIR})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE boost_unit_test_framework)


add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}>  --log_level=test_suite --report_level=short)