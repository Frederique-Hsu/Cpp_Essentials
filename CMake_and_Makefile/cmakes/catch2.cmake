cmake_minimum_required(VERSION  3.20)

# Catch2 C++ unit test framework

set(CATCH2_SOURCE_DIR           ${CMAKE_SOURCE_DIR}/3rd_party_libs/catch2-src)
set(CATCH2_STATE_DIR            ${CMAKE_BINARY_DIR}/catch2-state)
set(CATCH2_INSTALL_DIR          ${CMAKE_BINARY_DIR}/catch2-install)

set(GIT_REPO_NAME           Catch2)
set(GIT_REPO_URL            https://github.com/catchorg/Catch2.git)
# set(GIT_TAG                 v3.9.1)
set(GIT_TAG                 v3.7.0)
set(GIT_CLONE_DEPTH         10)



find_program(GIT_EXECUTABLE git REQUIRED)
if (NOT EXISTS ${CATCH2_SOURCE_DIR}/.git)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone --recurse-submodules --depth=${GIT_CLONE_DEPTH} --branch=${GIT_TAG} ${GIT_REPO_URL} ${CATCH2_SOURCE_DIR}
        RESULT_VARIABLE     git_clone_result
    )
    if (NOT git_clone_result EQUAL 0)
        message(FATAL_ERROR "Failed to git clone the ${GIT_REPO_NAME} repository!")
    endif()
else()
    execute_process(
        COMMAND ${GIT_EXECUTABLE} -C ${CATCH2_SOURCE_DIR} describe --tags --exact-match HEAD
        OUTPUT_VARIABLE     current_tag
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (NOT ${current_tag} STREQUAL ${GIT_TAG})
        execute_process(
            COMMAND ${GIT_EXECUTABLE} -C ${CATCH2_SOURCE_DIR} fetch --depth=${GIT_CLONE_DEPTH} origin ${GIT_TAG}:${GIT_TAG}
            COMMAND ${GIT_EXECUTABLE} -C ${CATCH2_SOURCE_DIR} checkout ${GIT_TAG}
            RESULT_VARIABLE     result
        )
        if (NOT result EQUAL 0)
            message(STATUS "Failed to switch to your expected ${GIT_TAG}")
        endif()
    endif()
endif()


include(ExternalProject)

ExternalProject_Add(catch2
    PREFIX              ${CATCH2_STATE_DIR}
    SOURCE_DIR          ${CATCH2_SOURCE_DIR}
    DOWNLOAD_COMMAND    ""
    GIT_CONFIG          "core.worktree=${CATCH2_SOURCE_DIR}"
    UPDATE_DISCONNECTED     TRUE
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBUILD_SHARED_LIBS=ON
        -DCMAKE_INSTALL_PREFIX=${CATCH2_INSTALL_DIR}
    BUILD_ALWAYS            TRUE
    STEP_TARGETS            install
)

set(CATCH2_INCLUDE_DIR      ${CATCH2_INSTALL_DIR}/include)
set(CATCH2_LIB_DIR          ${CATCH2_INSTALL_DIR}/lib)