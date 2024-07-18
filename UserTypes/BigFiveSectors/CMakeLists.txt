cmake_minimum_required(VERSION 3.5)

project(BigFiveSectors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)

add_executable(BigFiveSectors
    main.cpp
    constructor_destructor.cpp constructor_destructor.hpp
    test_constructor_destructor.c++
    big_five_sectors.cpp big_five_sectors.hpp test_big_five_sectors.c++
    finally.hpp
    finally_impl.hpp
    pointers.hpp pointers_impl.hpp
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Catch2::Catch2)
