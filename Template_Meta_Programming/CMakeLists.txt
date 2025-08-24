cmake_minimum_required(VERSION  3.20)

project(Template_Meta_Programming)


file(GLOB_RECURSE sources "*.c*")
file(GLOB_RECURSE headers "*.h*")

message(STATUS "${PROJECT_NAME} project's code files list: ")
foreach(source ${sources})
    message(STATUS "\t\t ${source}")
endforeach()
foreach(header ${headers})
    message(STATUS "\t\t ${header}")
endforeach()


add_executable(${PROJECT_NAME} ${sources} ${headers})

add_dependencies(${PROJECT_NAME} catch2)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD        20
    CXX_EXTENSIONS      NO
    CXX_STANDARD_REQUIRED   YES)

target_compile_options(${PROJECT_NAME} PRIVATE
    "-Wall"
    "-Wextra"
    # "-Werror"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CATCH2_INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${CATCH2_LIB_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2d)


enable_testing()

add_test(NAME UTest_${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}> -s)
