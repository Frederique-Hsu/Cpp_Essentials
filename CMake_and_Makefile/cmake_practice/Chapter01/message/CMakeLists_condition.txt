cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(message LANGUAGES CXX)

# set(USE_LIBRARY OFF)
# message(STATUS "Compile sources into a library? ${USE_LIBRARY}")
option(USE_LIBRARY "Compile sources into a library?" OFF)

set(BUILD_SHARED_LIBS OFF)

list(APPEND _sources Message.hpp Message.cpp)

if(USE_LIBRARY)
    # add_library will create a static library, since BUILD_SHARED_LIBS is OFF.
    add_library(message ${_sources})
    add_executable(hello-world hello-world.cpp)
    target_link_libraries(hello-world message)
else()
    add_executable(hello-world hello-world.cpp ${_sources})
endif()