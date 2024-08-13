cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(GoogleTestUT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(sum_integers SHARED sum_integers.cpp sum_integers.hpp)


option(ENABLE_UNIT_TESTS "Enable unit tests" OFF)
message(STATUS "Enable testing : ${ENABLE_UNIT_TESTS}")

if(ENABLE_UNIT_TESTS)
    include(FetchContent)

    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2)

    FetchContent_GetProperties(googletest)

    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)

        # Prevent GoogleTest from overriding our compiler/linker options
        # when building with Visual Studio
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        # Prevent GoogleTest from using pthread
        set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

        # adds the targets: gtest, gtest_main, gmock, gmock_main
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

        # Silence std::tr1 warning on MSVC
        if(MSVC)
            foreach(_tgt gtest gtest_main gmock gmock_main)
                target_compile_definitions(${_tgt} PRIVATE
                    "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING")
            endforeach()
        endif()
    endif()

    add_executable(cpp_test "")
    target_sources(cpp_test PRIVATE main.cpp test.cpp)
    target_link_libraries(cpp_test PRIVATE sum_integers gtest)
else()
    find_package(GTest REQUIRED CONFIG)

    add_executable(cpp_test "")
    target_sources(cpp_test PRIVATE main.cpp test.cpp)
    target_link_libraries(cpp_test PUBLIC sum_integers gtest)
endif()

enable_testing()
add_test(NAME google_test
    COMMAND $<TARGET_FILE:cpp_test>)