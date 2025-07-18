cmake_minimum_required(VERSION 3.20)


set(CppUTest_SRC_DIR            ${CMAKE_SOURCE_DIR}/external/cpputest-src)
set(CppUTest_STATE_DIR          ${CMAKE_BINARY_DIR}/cpputest-state)
set(CppUTest_INSTALL_DIR        ${CMAKE_BINARY_DIR}/cpputest-install)

set(GIT_TAG_NAME        master)
set(GIT_CLONE_DEPTH     10)

find_program(GIT_EXECUTABLE git REQUIRED)

# 首次克隆或检查版本变更处理
if (NOT EXISTS "${CppUTest_SRC_DIR}/.git")
    message(STATUS "git cloning (shallow) cpputest repository...")

    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone --depth=${GIT_CLONE_DEPTH} --branch=${GIT_TAG_NAME} https://github.com/cpputest/cpputest.git ${CppUTest_SRC_DIR}
        WORKING_DIRECTORY       ${CMAKE_CURRENT_BINARY_DIR}
        RESULT_VARIABLE         GIT_CLONE_RESULT
    )

    if (NOT GIT_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to git clone the cpputest repository!")
    endif()
else()
    execute_process(
        COMMAND ${GIT_EXECUTABLE} -C ${CppUTest_SRC_DIR} describe --tags --exact-match HEAD
        OUTPUT_VARIABLE current_version_tag
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (NOT "${current_version_tag}" STREQUAL "${GIT_TAG_NAME}")
        message(STATUS "Switching cpputest to ${GIT_TAG_NAME}...")

        execute_process(
            COMMAND ${GIT_EXECUTABLE} -C ${CppUTest_SRC_DIR} fetch --depth=${GIT_CLONE_DEPTH} origin ${GIT_TAG_NAME}:${GIT_TAG_NAME}
            COMMAND ${GIT_EXECUTABLE} -C ${CppUTest_SRC_DIR} checkout ${GIT_TAG_NAME}
            RESULT_VARIABLE result
        )
        if (NOT result EQUAL 0)
            message(STATUS "Failed to switch to your expected ${GIT_TAG_NAME}")
        endif()
    endif()
endif()


include(ExternalProject)
ExternalProject_Add(cpputest
    PREFIX                  ${CppUTest_STATE_DIR}
    SOURCE_DIR              ${CppUTest_SRC_DIR}
    DOWNLOAD_COMMAND        ""
    GIT_CONFIG              "core.worktree=${CppUTest_SRC_DIR}"
    UPDATE_DISCONNECTED     TRUE
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBUILD_SHARED_LIBS=ON
        -DCMAKE_INSTALL_PREFIX=${CppUTest_INSTALL_DIR}
    BUILD_ALWAYS            TRUE
    LOG_BUILD               ON
    STEP_TARGETS            install
)


set(CppUTest_INCLUDE_DIR        ${CppUTest_INSTALL_DIR}/include)
set(CppUTest_LIB_DIR            ${CppUTest_INSTALL_DIR}/lib)
