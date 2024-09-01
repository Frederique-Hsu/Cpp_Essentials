set(CURRENT_PROJECT_NAME experiment)

project(${CURRENT_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources *.c*)
file(GLOB_RECURSE headers *.h*)

add_executable(${CURRENT_PROJECT_NAME} ${sources} ${headers})
target_link_libraries(${CURRENT_PROJECT_NAME} PRIVATE GTest::gtest)