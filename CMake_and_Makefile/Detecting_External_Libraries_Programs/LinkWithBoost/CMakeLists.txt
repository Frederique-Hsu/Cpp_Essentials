cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(LinkWithBoost LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(Boost REQUIRED COMPONENTS filesystem)

add_executable(${PROJECT_NAME} path-info.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::filesystem)