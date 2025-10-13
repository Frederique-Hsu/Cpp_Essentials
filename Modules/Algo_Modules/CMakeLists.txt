cmake_minimum_required(VERSION  3.28.2)

project(Algo_Modules LANGUAGES CXX)


set(CMAKE_CXX_EXTENSIONS            FALSE)
set(CMAKE_CXX_VISIBILITY_PRESET     hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

add_library(Algo SHARED)

target_sources(Algo
    PRIVATE
        algo-impl.cpp
    PUBLIC
        FILE_SET    CXX_MODULES
        FILES
            algo-interface.cppm
)


# CMake requires the language standard to be specified as compiler feature
# when a target provides C++20 modules and the target will be installed
target_compile_features(Algo PUBLIC 
    cxx_std_20)
