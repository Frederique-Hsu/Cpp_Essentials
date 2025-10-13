cmake_minimum_required(VERSION  3.20)

project(choose_runtime_threads_count)

file(GLOB_RECURSE code_files 
    "*.c*"
    "*.h*")

message(STATUS "${PROJECT_NAME} project's code files list:")
foreach(code_file ${code_files})
    message(STATUS "\t\t ${code_file}")
endforeach()


add_executable(${PROJECT_NAME} ${code_files})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD        17
    CXX_EXTENSIONS      NO
    CXX_STANDARD_REQUIRED   YES)

target_compile_options(${PROJECT_NAME} PRIVATE
    "-Wall"
    "-Wextra"
    "-Wpedantic"
    "-Werror")


enable_testing()

add_test(NAME   ${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>)
