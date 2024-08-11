cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Option LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_LIBRARY "Compile sources into a library?" OFF)

include(CMakeDependentOption)

# second option depends on the value of the first one
CMAKE_DEPENDENT_OPTION(
    MAKE_STATIC_LIBRARY "Compile sources into a static library" OFF
    "USE_LIBRARY" ON)

# third option depends on the value of the first one
CMAKE_DEPENDENT_OPTION(
    MAKE_SHARED_LIBRARY "Compile sources into a shared library" ON
    "USE_LIBRARY" ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

list(APPEND _sources Message.cpp Message.hpp)

if(USE_LIBRARY)
    message(STATUS "Compile sources into a STATIC library? ${MAKE_STATIC_LIBRARY}")
    message(STATUS "Compile sources into a SHARED library? ${MAKE_SHARED_LIBRARY}")

    if(MAKE_STATIC_LIBRARY)
        add_library(Message STATIC ${_sources})
        add_executable(${PROJECT_NAME} main.cpp)
        target_link_libraries(${PROJECT_NAME} Message)
    endif()

    if(MAKE_SHARED_LIBRARY)
        add_library(Message SHARED ${_sources})
        add_executable(${PROJECT_NAME} main.cpp)
        target_link_libraries(${PROJECT_NAME} Message)
    endif()
else()
    add_executable(${PROJECT_NAME} main.cpp ${_sources})
endif()