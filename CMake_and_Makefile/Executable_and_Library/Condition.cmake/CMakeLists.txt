cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Condition LANGUAGES CXX)


# set(USE_LIBRARY ON)
option(USE_LIBRARY "Compile sources into a library?" OFF)

message(STATUS "Compile sources into a library?  ${USE_LIBRARY}")

set(BUILD_SHARED_LIBS YES)

list(APPEND lib_code Message.cpp Message.hpp)

if (USE_LIBRARY)
    add_library(Message ${lib_code})

    add_executable(${PROJECT_NAME} main.cpp)
    target_link_libraries(${PROJECT_NAME} Message)
else()
    add_executable(${PROJECT_NAME} main.cpp ${lib_code})
endif()