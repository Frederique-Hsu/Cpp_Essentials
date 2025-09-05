cmake_minimum_required(VERSION  3.20)


project(passing_arguments_to_thread_function)


file(GLOB_RECURSE sources "*.c*")
file(GLOB_RECURSE headers "*.h*")
list(FILTER sources EXCLUDE REGEX "./build/*")
list(FILTER headers EXCLUDE REGEX "./build/*")

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
    CXX_STANDARD        11
    CXX_EXTENSIONS      NO
    CXX_STANDARD_REQUIRED   YES)

target_compile_options(${PROJECT_NAME} PUBLIC
    "-Wall"
    "-Wextra"
    "-Werror")


enable_testing()

add_test(NAME   UTest_${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>)
