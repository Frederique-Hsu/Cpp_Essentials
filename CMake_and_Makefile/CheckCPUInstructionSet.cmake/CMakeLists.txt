cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(CheckCPUInstructionSet LANGUAGES CXX)

add_executable(${PROJECT_NAME} "")

target_compile_options(${PROJECT_NAME} PUBLIC "-Wall")
target_compile_options(${PROJECT_NAME} PUBLIC "-Wextra")
target_compile_options(${PROJECT_NAME} PUBLIC "-Werror")
target_compile_options(${PROJECT_NAME} PUBLIC "-Wpedantic")

target_sources(${PROJECT_NAME} PRIVATE
    processor-info.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_BINARY_DIR})

foreach(key IN ITEMS
    NUMBER_OF_LOGICAL_CORES
    NUMBER_OF_PHYSICAL_CORES
    TOTAL_VIRTUAL_MEMORY
    AVAILABLE_VIRTUAL_MEMORY
    TOTAL_PHYSICAL_MEMORY
    AVAILABLE_PHYSICAL_MEMORY
    IS_64BIT
    HAS_FPU
    HAS_MMX
    HAS_MMX_PLUS
    HAS_SSE
    HAS_SSE2
    HAS_SSE_FP
    HAS_SSE_MMX
    HAS_AMD_3DNOW
    HAS_AMD_3DNOW_PLUS
    HAS_IA64
    OS_NAME
    OS_RELEASE
    OS_VERSION
    OS_PLATFORM)
    cmake_host_system_information(RESULT _${key} QUERY ${key})
endforeach()

configure_file(config.h.in config.h @ONLY)