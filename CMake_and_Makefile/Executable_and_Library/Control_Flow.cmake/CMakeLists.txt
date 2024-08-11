cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Control_Flow LANGUAGES CXX)

add_library(geometry OBJECT
    geometry_circle.cpp
    geometry_circle.hpp
    geometry_polygon.cpp
    geometry_polygon.hpp
    geometry_rhombus.cpp
    geometry_rhombus.hpp
    geometry_square.cpp
    geometry_square.hpp)

add_library(geometry-static STATIC $<TARGET_OBJECTS:geometry>)
set_target_properties(geometry-static PROPERTIES OUTPUT_NAME "geometry")

add_library(geometry-shared SHARED $<TARGET_OBJECTS:geometry>)
set_target_properties(geometry-shared PROPERTIES OUTPUT_NAME "geometry")
target_compile_options(geometry-shared PRIVATE -O3)

list(APPEND sources_with_lower_optimization
    geometry_circle.cpp
    geometry_rhombus.cpp)

message(STATUS "Setting source properties using IN Lists syntax: ")
foreach(_source ${sources_with_lower_optimization})
    set_source_files_properties(${_source} PROPERTIES COMPILE_FLAGS -O2)
    message(STATUS "Appending -O2 flag for ${_source}")
endforeach()

message(STATUS "Querying sources properties using plain syntax:")
foreach(_source ${sources_with_lower_optimization})
    get_source_file_property(_flags ${_source} COMPILE_FLAGS)
    message(STATUS "Source ${_source} has the following extra COMPILE_FLAGS: ${_flags}")
endforeach()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} geometry-shared)