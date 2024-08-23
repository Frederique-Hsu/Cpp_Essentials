set(CURRENT_PROJECT_NAME Hierarchies)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME} "")
target_sources(${CURRENT_PROJECT_NAME} PRIVATE
    ${sources}
    ${headers})

target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC ${COMPILE_OPTIONS})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE Boost::unit_test_framework)
target_compile_definitions(${CURRENT_PROJECT_NAME} PRIVATE BOOST_TEST_DYN_LINK)

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}> -p)