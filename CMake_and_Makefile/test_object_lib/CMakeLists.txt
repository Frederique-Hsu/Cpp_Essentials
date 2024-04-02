cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(test_object_lib LANGUAGES CXX)

# expose options to the user
option(USE_LIBRARY "Compile sources into a library" OFF)
message(STATUS "Compile sources into a library? ${USE_LIBRARY}")

include(CMakeDependentOption)
# second option depends on the value of the first
cmake_dependent_option(MAKE_STATIC_LIBRARY 
    "Compile sources into a static library" OFF
    "USE_LIBRARY" ON
)

# third option depends on the value of the first
cmake_dependent_option(MAKE_SHARED_LIBRARY
    "Compile sources into a shared library" ON
    "USE_LIBRARY" ON
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# list souces
list(APPEND _sources Message.cpp Message.hpp)

if (USE_LIBRARY)
    message(STATUS "Compile sources into a STATIC library? ${MAKE_STATIC_LIBRARY}")
    message(STATUS "Compile sources into a SHARED library? ${MAKE-SHARED_LIBRARY}")

    if (MAKE_SHARED_LIBRARY)
        add_library(message SHARED ${_sources})
        add_executable(${PROJECT_NAME} test_object.cpp)
        target_link_libraries(${PROJECT_NAME} message)
    endif()

    if (MAKE_STATIC_LIBRARY)
        add_library(message STATIC ${_sources})
        add_executable(${PROJECT_NAME} test_object.cpp)
        target_link_libraries(${PROJECT_NAME} message)
    endif()
else()
    add_executable(${PROJECT_NAME} test_object.cpp ${_sources})
endif(USE_LIBRARY)