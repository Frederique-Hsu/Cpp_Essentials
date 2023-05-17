cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(message LANGUAGES CXX)

# Expose options to the user
option(USE_LIBRARY "Compile sources into a library:" OFF)
message(STATUS "Compile sources into a library? ${USE_LIBRARY}")

include(CMakeDependentOption)

# second option depends on the value of the first option "USE_LIBRARY"
cmake_dependent_option(MAKE_STATIC_LIBRARY "Compile sources into a static library" OFF
    "USE_LIBRARY" ON)

# third option dependes on the value of first option "USE_LIBRARY"
cmake_dependent_option(MAKE_SHARED_LIBRARY "Compile sources into a shared library" ON
    "USE_LIBRARY" ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# list the sources
list(APPEND _sources Message.cpp Message.hpp)

if (USE_LIBRARY)
    message(STATUS "Compile sources into a STATIC library? ${MAKE_STATIC_LIBRARY}")
    message(STATUS "Compile sources into a SHARED library? ${MAKE_SHARED_LIBRARY}")

    if(MAKE_SHARED_LIBRARY)
        add_library(message SHARED ${_sources})
        add_executable(hello-world hello-world.cpp)
        target_link_libraries(hello-world message)
    endif()

    if(MAKE_STATIC_LIBRARY)
        add_library(message STATIC ${_sources})
        add_executable(hello-world hello-world.cpp)
        target_link_libraries(hello-world message)
    endif()
else()
    add_executable(hello-world hello-world.cpp ${_sources})
endif(USE_LIBRARY)