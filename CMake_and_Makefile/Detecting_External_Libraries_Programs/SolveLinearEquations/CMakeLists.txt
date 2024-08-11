cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(SolveLinearEquations LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(OpenMP REQUIRED)
find_package(Eigen3 3.4 REQUIRED CONFIG)

if(TARGET Eigen3::Eigen)
    message(STATUS "Eigen3 v${EIGEN3_VERSION_STRING} found in ${EIGEN3_INCLUDE_DIR}")
endif()

add_executable(${PROJECT_NAME} linear-algebra.cpp)

find_package(BLAS)
if(BLAS_FOUND)
    message(STATUS "Eigen will use some subroutines from BLAS.")
    message(STATUS "see http://eigen.tuxfamily.org/dox-devel/TopicUsingBlasLapack.html")

    target_compile_options(${PROJECT_NAME} PRIVATE ${EIGEN_USE_BLAS})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${BLAS_LIBRARIES})
else()
    message(STATUS "BLAS not found.  Using Eigen own functions")
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen OpenMP::OpenMP_CXX)