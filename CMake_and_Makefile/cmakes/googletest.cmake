cmake_minimum_required(VERSION  3.20)

# GoogleTest Unit Test Framework

set(GOOGLETEST_SOURCE_DIR       ${CMAKE_SOURCE_DIR}/3rd_party_libs/gtest-src)
set(GOOGLETEST_STATE_DIR        ${CMAKE_BINARY_DIR}/gtest-state)
set(GOOGLETEST_INSTALL_DIR      ${CMAKE_BINARY_DIR}/gtest-install)

set(GIT_REPO_NAME       GoogleTest)
set(GIT_REPO_URL        https://github.com/google/googletest.git)
# set(GIT_TAG             v1.17.0)
set(GIT_BRANCH          main)
set(GIT_CLONE_DEPTH     10)


find_program(GIT_EXECUTABLE git REQUIRED)
if (NOT EXISTS ${GOOGLETEST_SOURCE_DIR}/.git)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone --recurse-submodules --depth=${GIT_CLONE_DEPTH} --branch=${GIT_BRANCH} ${GIT_REPO_URL} ${GOOGLETEST_SOURCE_DIR}
        RESULT_VARIABLE     git_clone_result
    )
    if (NOT git_clone_result EQUAL 0)
        message(FATAL_ERROR "Failed to git clone the ${GIT_REPO_NAME} repository!")
    endif()
else()
    execute_process(
        COMMAND ${GIT_EXECUTABLE} -C ${GOOGLETEST_SOURCE_DIR} describe --tags --exact-match HEAD
        OUTPUT_VARIABLE     current_tag
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (NOT ${current_tag} STREQUAL ${GIT_BRANCH})
        execute_process(
            COMMAND ${GIT_EXECUTABLE} -C ${GOOGLETEST_SOURCE_DIR} fetch --depth=${GIT_CLONE_DEPTH} origin ${GIT_BRANCH}:${GIT_BRANCH}
            COMMAND ${GIT_EXECUTABLE} -C ${GOOGLETEST_SOURCE_DIR} checkout ${GIT_BRANCH}
            RESULT_VARIABLE     result
        )
        if (NOT result EQUAL 0)
            message(STATUS "Failed to switch to your expected ${GIT_BRANCH}")
        endif()
    endif()
endif()


include(ExternalProject)


ExternalProject_Add(googletest
    PREFIX              ${GOOGLETEST_STATE_DIR}
    SOURCE_DIR          ${GOOGLETEST_SOURCE_DIR}
    DOWNLOAD_COMMAND    ""
    GIT_CONFIG          "core.worktree=${GOOGLETEST_SOURCE_DIR}"
    UPDATE_DISCONNECTED     TRUE
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBUILD_SHARED_LIBS=ON
        -DCMAKE_INSTALL_PREFIX=${GOOGLETEST_INSTALL_DIR}
        -DCMAKE_CXX_STANDARD=17
        -DCMAKE_CXX_EXTENSIONS=OFF
        -DCMAKE_CXX_STANDARD_REQUIRED=ON
    BUILD_ALWAYS            TRUE
    STEP_TARGETS            install
)

set(GOOGLETEST_INCLUDE_DIR      ${GOOGLETEST_INSTALL_DIR}/include)
set(GOOGLETEST_LIB_DIR          ${GOOGLETEST_INSTALL_DIR}/lib)