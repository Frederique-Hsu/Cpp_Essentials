cmake_minimum_required(VERSION 3.20)

# 定义永久存储目录
set(GTEST_SRC_DIR       ${CMAKE_SOURCE_DIR}/external/gtest-src)
set(GTEST_STATE_DIR     ${CMAKE_BINARY_DIR}/gtest-state)
set(GTEST_INSTALL_DIR   ${CMAKE_BINARY_DIR}/gtest-install)


# 首次下载检查
if (NOT EXISTS "${GTEST_SRC_DIR}/.git")
    message(STATUS "Initial GTest downloading...")

    file(MAKE_DIRECTORY "${GTEST_SRC_DIR}")
    find_program(GIT_EXECUTABLE git REQUIRED)

    message(STATUS "GIT_EXECUTABLE = ${GIT_EXECUTABLE}")

    set(GIT_BRANCH_NAME     main)
    set(GIT_TAG_NAME        v1.17.0)

    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone --depth 10 --branch "${GIT_TAG_NAME}" https://github.com/google/googletest.git "${GTEST_SRC_DIR}"
        WORKING_DIRECTORY   "${CMAKE_CURRENT_BINARY_DIR}"
        RESULT_VARIABLE     GIT_CLONE_RESULT
    )

    if (NOT GIT_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to git clone googletest repo.")
    endif()
endif()

include(ExternalProject)

ExternalProject_Add(GTest
    PREFIX              ${GTEST_STATE_DIR}      # 构建状态隔离存储
    SOURCE_DIR          ${GTEST_SRC_DIR}        # 绑定永久源码目录
    DOWNLOAD_COMMAND    ""                      # 禁用默认下载
    GIT_CONFIG          "core.worktree=${GTEST_SRC_DIR}"    # 强制绑定本地仓库
    UPDATE_DISCONNECTED     ON          # 绝对禁用远程更新
    CMAKE_ARGS
        # -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBUILD_SHARED_LIBS=ON
        -DCMAKE_INSTALL_PREFIX=${GTEST_INSTALL_DIR}
    BUILD_ALWAYS            TRUE
    LOG_BUILD               ON
    STEP_TARGETS            install
)

set(GTEST_INCLUDE_DIR       ${GTEST_INSTALL_DIR}/include)
set(GTEST_LIB_DIR           ${GTEST_INSTALL_DIR}/lib)