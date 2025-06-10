cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(UserTypes)

enable_testing()

add_subdirectory(BigFiveSectors)
add_subdirectory(String)
add_subdirectory(Classes)
if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_subdirectory(operator_new_delete)
endif()
# add_subdirectory(OverloadingOperators)
# add_subdirectory(SpecialOperators)
# add_subdirectory(Test_User_UniquePtr)
