cmake_minimum_required(VERSION  3.20)

project(cpp14_meta_programming)

file(GLOB_RECURSE sources "*.c*")
file(GLOB_RECURSE headers "*.h*")
message(STATUS "${PROJECT_NAME} project's code files list: ")
foreach(source ${sources})
    message(STATUS "\t\t ${source}")
endforeach()
foreach(header ${headers})
    message(STATUS "\t\t ${header}")
endforeach()
message(STATUS "\n")


add_executable(${PROJECT_NAME}
    ${sources}
    ${headers})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD        14
    CXX_EXTENSIONS      NO
    CXX_STANDARD_REQUIRED   YES)

target_compile_options(${PROJECT_NAME} PRIVATE
    "-Wall"
    "-Wextra"
    "-Werror")