cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CURRENT_PROJECT_NAME meta_prog)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

# find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(${CURRENT_PROJECT_NAME}
    ${sources}
    ${headers})
set_target_properties(${CURRENT_PROJECT_NAME} PROPERTIES
    CXX_STANDARD            17
    CXX_EXTENSIONS          NO
    CXX_STANDARD_REQUIRED   YES)
target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC
    ${COMPILE_OPTIONS}
    "-g"
    "-Wno-pedantic"
    "-Wno-zero-length-array")
target_link_libraries(${CURRENT_PROJECT_NAME} PUBLIC boost_unit_test_framework)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    target_compile_definitions(${CURRENT_PROJECT_NAME} PUBLIC "CHOOSE_GCC")
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    target_compile_definitions(${CURRENT_PROJECT_NAME} PUBLIC "CHOOSE_CLANG")
    # target_compile_options(${CURRENT_PROJECT_NAME} PUBLIC
    #     "-fsanitize=address"
    #     "-fno-omit-frame-pointer"
    #     "-fsanitize=thread"
    #     "-fsanitize=memory"
    #     "-fsanitize=undefined")
endif()


enable_testing()
add_test(NAME UTest_${CURRENT_PROJECT_NAME}
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
            $<TARGET_FILE:${CURRENT_PROJECT_NAME}> --log_level=all --report_level=short)