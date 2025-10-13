cmake_minimum_required(VERSION  3.20)

project(OOC   LANGUAGES C)

set(C_STANDARD      11)
set(C_EXTENSIONS    OFF)
set(C_STANDARD_REQUIRED     ON)


file(GLOB_RECURSE sources "*.c")
file(GLOB_RECURSE headers "*.h")
list(FILTER sources EXCLUDE REGEX "build/*")
list(FILTER headers EXCLUDE REGEX "build/*")


add_executable(${PROJECT_NAME}
    ${sources}
    ${headers})

target_link_libraries(${PROJECT_NAME} PUBLIC
    m)

# target_compile_options(${PROJECT_NAME} PUBLIC
#     "-Wall"
#     "-Wextra"
#     "-Werror")