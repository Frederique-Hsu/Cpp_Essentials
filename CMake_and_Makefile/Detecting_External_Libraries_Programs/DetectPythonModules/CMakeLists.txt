cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(DetectPythonModules LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} EXACT REQUIRED)

# Find NumPy location
execute_process(COMMAND
    ${PYTHON_EXECUTABLE} "-c"
    "import re, numpy; print(re.compile('/__init__.py.*').sub('',numpy.__file__))"
    RESULT_VARIABLE _numpy_status
    OUTPUT_VARIABLE _numpy_location
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE)

if(NOT _numpy_status)
    set(NumPy ${_numpy_location} CACHE STRING "Location of NumPy")
endif()

# Check the NumPy version
execute_process(COMMAND
    ${PYTHON_EXECUTABLE} "-c" "import numpy; print(numpy.__version__)"
    OUTPUT_VARIABLE _numpy_version
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NumPy
    FOUND_VAR       NumPy_FOUND
    REQUIRED_VARS   NumPy
    VERSION_VAR     _numpy_version)

add_executable(${PROJECT_NAME} use_numpy.py)

target_sources(${PROJECT_NAME} PRIVATE
    Py${PYTHON_VERSION_MAJOR}-pure-embedding.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PYTHON_LIBRARIES})

# Make sure the use_numpy.py would be available under the build/ directory
add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/use_numpy.py
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/use_numpy.py ${CMAKE_CURRENT_BINARY_DIR}/use_numpy.py
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/use_numpy.py
    )

# Make sure building the project will trigger the above custom command
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/use_numpy.py)