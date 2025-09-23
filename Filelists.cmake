# This file is to be included into an application CMakeLists.txt to use OpenBSW.
# The variable OPENBSW_DIR should be set to the location of the OpenBSW root and
# OPENBSW_APP_DIR to the root of the application sources.

cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

if (CMAKE_CXX_STANDARD AND NOT ${CMAKE_CXX_STANDARD} EQUAL 14)
    message(WARNING "Using custom CXX standard (C++${CMAKE_CXX_STANDARD})")
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()
if (CMAKE_C_STANDARD AND NOT ${CMAKE_C_STANDARD} EQUAL 11)
    message(WARNING "Using custom C standard (C${CMAKE_C_STANDARD})")
else ()
    set(CMAKE_C_STANDARD 11)
endif ()

# Set preprocessor defines based on cmake options by the same name to configure
# platform features.
get_cmake_property(_all_vars VARIABLES)
foreach (var ${_all_vars})
    if (var MATCHES "^PLATFORM_SUPPORT_")
        if (${var})
            add_compile_definitions(${var}=1)
        endif ()
    endif ()
endforeach ()

project(
    "Eclipse OpenBSW"
    VERSION 0.1.0
    DESCRIPTION
        "BSW workspace with reference application for multiple platforms"
    LANGUAGES CXX C ASM)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/admin/cmake")

option(BUILD_UNIT_TESTS "Build unit tests" OFF)

option(BUILD_TRACING "Build CTF tracing" OFF)

add_compile_options(
    "$<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:-O2;-g3;-Werror;-Wall;-Wextra;-Wvla;-Wno-deprecated-volatile>"
    # todo: enforce -Wunused-parameter
    "$<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:-Wno-error=unused-parameter>"
    # note: the below warnings are often false positive
    "$<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wno-error=stringop-overflow;-Wno-error=maybe-uninitialized>"
)

add_compile_options(
    "$<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-O2;-g3;-Werror;-Wall;-Wextra>")

add_link_options(-Wl,--noinhibit-exec)

if (BUILD_UNIT_TESTS)
    add_compile_definitions(UNIT_TEST=1)
    include(GoogleTest)
    include(CTest)
    include(CodeCoverage)
    append_coverage_compiler_flags()
    enable_testing()
endif ()

if (BUILD_TRACING)
    add_compile_definitions(TRACING=1)
    if (TRACING_BUFFER_SIZE)
        add_compile_definitions(TRACING_BUFFER_SIZE=${TRACING_BUFFER_SIZE})
    endif ()
endif ()

set(INCLUDE_OPENBSW_LIBS_BSP
    ON
    CACHE BOOL "Include openbsw/libs/bsp/ in build")

set(OPENBSW_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE PATH "Path to Eclipse OpenBSW")
add_subdirectory(${OPENBSW_DIR}/libs openbsw/libs)
add_subdirectory(${OPENBSW_DIR}/platforms openbsw/platforms)
