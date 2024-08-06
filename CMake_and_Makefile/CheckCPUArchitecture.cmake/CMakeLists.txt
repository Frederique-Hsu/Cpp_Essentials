cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(CheckCPUArchitecture LANGUAGES CXX)

add_executable(${PROJECT_NAME} arch-dependent.cpp)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_definitions(${PROJECT_NAME} PUBLIC "IS_64_BIT_ARCH")
    message(STATUS "Target CPU is ${CMAKE_SIZEOF_VOID_P}-bits architecture.")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "IS_32_BIT_ARCH")
    message(STATUS "Target CPU is 32-bits architecture.")
endif()

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i386")
    message(STATUS "i386 architecture detected")
    target_sources(${PROJECT_NAME} PRIVATE
        arch-dependent-i386.cpp)
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i686")
    message(STATUS "i686 architecture detected")
    target_sources(${PROJECT_NAME} PRIVATE
        arch-dependent-i686.cpp)
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    message(STATUS "x86_64 architecture detected")
    target_sources(${PROJECT_NAME} PRIVATE
        arch-dependent-x86_64.cpp)
else()
    message(STATUS "host processor architecture is unknown.")
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC "ARCHITECTURE=${CMAKE_HOST_SYSTEM_PROCESSOR}")