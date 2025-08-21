cmake_minimum_required(VERSION  3.20)

# CppUTest : C++ unit test framework

set(CPPUTEST_SOURCE_DIR         ${CMAKE_SOURCE_DIR}/3rd_party_libs/cpputest-src)
set(CPPUTEST_STATE_DIR          ${CMAKE_BINARY_DIR}/cpputest-state)
set(CPPUTEST_INSTALL_DIR        ${CMAKE_BINARY_DIR}/cpputest-install)


set(GIT_REPO_NAME           CppUTest)
set(GIT_REPO_URL            https://github.com/cpputest/cpputest.git)
set(GIT_BRANCH              master)
set(GIT_CLONE_DEPTH         10)

find_program(GIT_EXECUTABLE git REQUIRED)
if (NOT EXISTS ${CPPUTEST_SOURCE_DIR}/.git)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone --recurse-submodules --depth=${GIT_CLONE_DEPTH} --branch=${GIT_BRANCH} ${GIT_REPO_URL} ${CPPUTEST_SOURCE_DIR}
        RESULT_VARIABLE     git_clone_result
    )
    if (NOT git_clone_result EQUAL 0)
        message(FATAL_ERROR "Failed to git clone the ${GIT_REPO_NAME} repository!")
    endif()
else()
    execute_process(
        COMMAND ${GIT_EXECUTABLE} -C ${CPPUTEST_SOURCE_DIR} rev-parse --abbrev-ref HEAD
        OUTPUT_VARIABLE     current_branch
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (NOT ${current_branch} STREQUAL ${GIT_BRANCH})
        execute_process(
            COMMAND ${GIT_EXECUTABLE} -C ${CPPUTEST_SOURCE_DIR} fetch --depth=${GIT_CLONE_DEPTH} origin ${GIT_BRANCH}:${GIT_BRANCH}
            COMMAND ${GIT_EXECUTABLE} -C ${CPPUTEST_SOURCE_DIR} checkout ${GIT_BRANCH}
            RESULT_VARIABLE     result
        )
        if (NOT result EQUAL 0)
            message(STATUS "Failed to switch to your expected ${GIT_BRANCH}")
        endif()
    endif()
endif()


include(ExternalProject)

ExternalProject_Add(cpputest
    PREFIX              ${CPPUTEST_STATE_DIR}
    SOURCE_DIR          ${CPPUTEST_SOURCE_DIR}
    DOWNLOAD_COMMAND    ""
    GIT_CONFIG          "core.worktree=${CPPUTEST_SOURCE_DIR}"
    UPDATE_DISCONNECTED     TRUE
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBUILD_SHARED_LIBS=ON
        -DCMAKE_INSTALL_PREFIX=${CPPUTEST_INSTALL_DIR}
    if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        -DCPPUTEST_BUILD_TESTING=OFF
        -DCPPUTEST_EXAMPLES=OFF
    endif()
    BUILD_ALWAYS            TRUE
    STEP_TARGETS            install
)

set(CPPUTEST_INCLUDE_DIR      ${CPPUTEST_INSTALL_DIR}/include)
set(CPPUTEST_LIB_DIR          ${CPPUTEST_INSTALL_DIR}/lib)