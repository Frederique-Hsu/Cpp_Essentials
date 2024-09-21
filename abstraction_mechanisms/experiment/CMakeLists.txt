cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CURRENT_PROJECT_NAME experiment)

project(${CURRENT_PROJECT_NAME})

set(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)
list(FILTER sources EXCLUDE REGEX "${CURRENT_DIR}/Node/")
list(FILTER headers EXCLUDE REGEX "${CURRENT_DIR}/Node/")

add_executable(${CURRENT_PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE Catch2::Catch2)
set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
    CXX_STANDARD                14
    CXX_STANDARD_REQUIRED       ON
    CXX_STANDARD_EXTENSIONS     OFF)

#===================================================================================================

add_executable(lambda_with_template lambda_with_template.cpp)
set_target_properties(lambda_with_template PROPERTIES
    CXX_STANDARD                14
    CXX_STANDARD_EXTENSIONS     OFF
    CXX_STANDARD_REQUIRED       ON)
target_compile_definitions(lambda_with_template PRIVATE "ONLY_RESERVED_FOR_LABDA_WITH_TEMPLATE_PROJECT")


add_executable(check_c_standard_no check_c_standard_no.c)
set_target_properties(check_c_standard_no PROPERTIES
    C_STANDARD                  23
    C_STANDARD_EXTENSIONS       OFF
    C_STANDARD_REQUIRED         ON)
target_compile_definitions(check_c_standard_no PRIVATE "CHECK_C_STANDARD_NO")


add_executable(check_cpp_standard_no check_cpp_standard_no.cpp)
set_target_properties(check_cpp_standard_no PROPERTIES
    CXX_STANDARD                23
    CXX_STANDARD_EXTENSIONS     OFF
    CXX_STANDARD_REQUIRED       ON)
target_compile_definitions(check_cpp_standard_no PRIVATE "CHECK_CPP_STANDARD_NO")

add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CURRENT_PROJECT_NAME}>)

#===================================================================================================

add_test(NAME UTest_lambda_with_template
    COMMAND $<TARGET_FILE:lambda_with_template>)

add_test(NAME check_c_standard_no
    COMMAND $<TARGET_FILE:check_c_standard_no>)

add_test(NAME check_cpp_standard_no
    COMMAND $<TARGET_FILE:check_cpp_standard_no>)
    
#===================================================================================================
    
add_executable(Node "")

file(GLOB_RECURSE sources_node ${CURRENT_DIR}/Node/*.c*)
file(GLOB_RECURSE headers_node ${CURRENT_DIR}/Node/*.h*)

target_sources(Node PRIVATE
    ${sources_node}
    ${headers_node})

set_target_properties(Node PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)
target_compile_definitions(Node PRIVATE "NODE")
target_link_libraries(Node PRIVATE GTest::gtest)

add_test(NAME UTest_Node
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose 
            $<TARGET_FILE:Node>)