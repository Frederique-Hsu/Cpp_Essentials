cmake_minimum_required(VERSION 3.20)

project(suppress_external_project_duplicated_download)


include(googletest.cmake)
include(boost.cmake)
include(cpputest.cmake)


file(GLOB_RECURSE sources 
    LIST_DIRECTORIES false  # 此参数可避免将目录本身包含在结果中
    CONFIGURE_DEPENDS       # 该选项会监控文件系统变化，当新增/删除文件时会自动触发CMake重新配置
    "*.c*")
file(GLOB_RECURSE headers 
    LIST_DIRECTORIES false 
    CONFIGURE_DEPENDS 
    "*.h*")
list(FILTER sources EXCLUDE REGEX "./external/*")
list(FILTER headers EXCLUDE REGEX "./external/*")
list(FILTER sources EXCLUDE REGEX "./build/*")
list(FILTER headers EXCLUDE REGEX "./build/*")
list(FILTER sources EXCLUDE REGEX ".*\\.cmake$")    # 使用正则表达式排除所有的.cmake文件

message(STATUS "source files list: ")
foreach(source ${sources})
    message(STATUS "\t\t ${source}")
endforeach()

message(STATUS "header files list: ")
foreach(header ${headers})
    message(STATUS "\t\t ${header}")
endforeach()




message(STATUS "CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}")

add_executable(${CMAKE_PROJECT_NAME}
    ${sources}
    ${headers})

add_dependencies(${CMAKE_PROJECT_NAME} GTest cpputest Boost)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD        17
    CXX_EXTENSIONS      NO
    CXX_STANDARD_REQUIRED   YES)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${GTEST_INCLUDE_DIR})

target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${GTEST_LIB_DIR})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    gtest)


#===============================================================================

enable_testing()

add_test(NAME UTest_${CMAKE_PROJECT_NAME}
    COMMAND $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)

include(GoogleTest)
gtest_discover_tests(${CMAKE_PROJECT_NAME})