cmake_minimum_required(VERSION  3.20)

# Boost Library

set(BOOST_SOURCE_DIR        ${CMAKE_SOURCE_DIR}/3rd_party_libs/boost-src)
set(BOOST_STATE_DIR         ${CMAKE_BINARY_DIR}/boost-state)
set(BOOST_INSTALL_DIR       ${CMAKE_BINARY_DIR}/boost-install)


set(GIT_REPO_NAME       Boost)
set(GIT_REPO_URL        https://github.com/boostorg/boost.git)
set(GIT_BRANCH          master)
set(GIT_CLONE_DEPTH     10)


find_program(GIT_EXECUTABLE git REQUIRED)
if (NOT EXISTS ${BOOST_SOURCE_DIR}/.git)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone --recurse-submodules --depth=${GIT_CLONE_DEPTH} --branch=${GIT_BRANCH} ${GIT_REPO_URL} ${BOOST_SOURCE_DIR}
        RESULT_VARIABLE     git_clone_result
    )
    if (NOT git_clone_result EQUAL 0)
        message(FATAL_ERROR "Failed to git clone the ${GIT_REPO_NAME} repository!")
    endif()
else()
    execute_process(
        COMMAND ${GIT_EXECUTABLE} -C ${BOOST_SOURCE_DIR} rev-parse --abbrev-ref HEAD
        OUTPUT_VARIABLE     current_branch
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    if (NOT ${current_branch} STREQUAL ${GIT_BRANCH})
        execute_process(
            COMMAND ${GIT_EXECUTABLE} -C ${BOOST_SOURCE_DIR} fetch --depth=${GIT_CLONE_DEPTH} origin ${GIT_BRANCH}:${GIT_BRANCH}
            COMMAND ${GIT_EXECUTABLE} -C ${BOOST_SOURCE_DIR} checkout ${GIT_BRANCH}
            RESULT_VARIABLE     result
        )
        if (NOT result EQUAL 0)
            message(STATUS "Failed to switch to your expected ${GIT_BRANCH}")
        endif()
    endif()
endif()


include(ExternalProject)

if (ON)
    message(STATUS "Build/Install boost by using bootstrap.sh + b2")

    include(ProcessorCount)
    ProcessorCount(PROCESSOR_COUNT)
    message(STATUS "PROCESSOR_COUNT = ${PROCESSOR_COUNT}")

    # 自动检测Boost版本
    function(get_boost_version VERSION_OUTPUT)
        set(BOOST_VERSION_HPP   ${BOOST_SOURCE_DIR}/boost/version.hpp)
        if (EXISTS ${BOOST_VERSION_HPP})
            file(READ ${BOOST_VERSION_HPP} content)
            string(REGEX MATCH "#define BOOST_VERSION ([0-9]+)" _ ${content})
            set(ver_num ${CMAKE_MATCH_1})
            message(STATUS "ver_num = ${ver_num}")

            math(EXPR major "${ver_num} / 100000")
            message(STATUS "major = ${major}")

            math(EXPR minor "${ver_num} / 100 % 1000")
            message(STATUS "minor = ${minor}")

            math(EXPR patch "${ver_num} % 100")
            message(STATUS "patch = ${patch}")

            set(${VERSION_OUTPUT} "${major}.${minor}.${patch}" PARENT_SCOPE)
            message(STATUS "version = ${major}.${minor}.${patch}")
        else()
            set(${VERSION_OUTPUT} "1.90.0" PARENT_SCOPE)
        endif()
    endfunction()

    get_boost_version(BOOST_VERSION)
    message(STATUS "boost version = ${BOOST_VERSION}")
    
    set(BOOST_BUILD_ARGS
        --prefix=${BOOST_INSTALL_DIR}
        --with-test # 若还需其他模块，可直接在后面添加 --with-filesystem
        # link=shared
        # runtime-link=shared
        threading=multi
        visibility=global
        -J${PROCESSOR_COUNT}
        install)

    ExternalProject_Add(Boost
        PREFIX              ${BOOST_STATE_DIR}
        SOURCE_DIR          ${BOOST_SOURCE_DIR}
        DOWNLOAD_COMMAND    ""
        GIT_CONFIG          "core.worktree=${BOOST_SOURCE_DIR}"
        UPDATE_DISCONNECTED     TRUE
        CONFIGURE_COMMAND       cd ${BOOST_SOURCE_DIR} && ./bootstrap.sh --with-libraries=test
        BUILD_COMMAND           cd ${BOOST_SOURCE_DIR} && ./b2 ${BOOST_BUILD_ARGS}
        INSTALL_COMMAND         echo
        BUILD_ALWAYS            TRUE
        STEP_TARGETS            install
    )
else()
    message(STATUS "Build/Install boost by using CMAKE_ARGS")

    ExternalProject_Add(Boost
        PREFIX              ${BOOST_STATE_DIR}
        SOURCE_DIR          ${BOOST_SOURCE_DIR}
        DOWNLOAD_COMMAND    ""
        GIT_CONFIG          "core.worktree=${BOOST_SOURCE_DIR}"
        UPDATE_DISCONNECTED     TRUE
        CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DBUILD_SHARED_LIBS=ON
            -DCMAKE_INSTALL_PREFIX=${BOOST_INSTALL_DIR}
        BUILD_ALWAYS            TRUE
        STEP_TARGETS            install
    )
endif()


set(BOOST_INCLUDE_DIR       ${BOOST_INSTALL_DIR}/include)
set(BOOST_LIB_DIR           ${BOOST_INSTALL_DIR}/lib)