cmake_minimum_required(VERSION 3.13)

# ---------------------------------------------------------------------------
# Cross-compilation toolchain
# Configure with:
#   cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain-pi.cmake \
#         -DCMAKE_BUILD_TYPE=Debug ..
# ---------------------------------------------------------------------------
project(a2b_pnp
    LANGUAGES C CXX
    VERSION 1.0.0
)

# ---------------------------------------------------------------------------
# Require 32-bit ARM target — catch accidental host builds early
# ---------------------------------------------------------------------------
if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    message(WARNING
        "CMAKE_SYSTEM_PROCESSOR is '${CMAKE_SYSTEM_PROCESSOR}' — expected 'arm'. "
        "Did you forget -DCMAKE_TOOLCHAIN_FILE=../toolchain-pi.cmake?")
endif()

# ---------------------------------------------------------------------------
# Build types
# ---------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# ---------------------------------------------------------------------------
# Root paths — all relative to this CMakeLists.txt (apps/linux_rpi/)
# ---------------------------------------------------------------------------
set(PROJECT_ROOT        ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(A2B_STACK_ROOT      ${PROJECT_ROOT}/a2bstack)
set(A2B_PNP_ROOT        ${PROJECT_ROOT}/a2bpnp)
set(A2B_COMMCH_ROOT     ${PROJECT_ROOT}/a2bcommchannel)
set(APP_COMMON_ROOT     ${PROJECT_ROOT}/app/common)   # shared cmd_parse, cmd_queue, etc.

# ---------------------------------------------------------------------------
# Compile definitions (carry forward from Pico app)
# ---------------------------------------------------------------------------
add_compile_definitions(
    A2B_STATIC_PLUGIN
    A2B_LINK_STATIC=1
    PB_FIELD_16BIT=1
)

# ---------------------------------------------------------------------------
# Source file globs
# PAL source files (pal_i2c.c, pal_timer.c, pal_gpio.c) and main.c will be
# added in subsequent steps. CMake configure succeeds here with an empty
# PAL list so the toolchain and include paths can be validated first.
# ---------------------------------------------------------------------------
file(GLOB SRC_PAL
    ${CMAKE_CURRENT_SOURCE_DIR}/pal_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/pal_timer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/pal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

file(GLOB_RECURSE SRC_COMMON
    ${APP_COMMON_ROOT}/*.c
)

file(GLOB_RECURSE SRC_PNP
    ${A2B_PNP_ROOT}/*.c
    ${A2B_PNP_ROOT}/*.cpp
)

file(GLOB_RECURSE SRC_STACK
    ${A2B_STACK_ROOT}/a2bstack/src/*.c
    ${A2B_STACK_ROOT}/a2bplugin-master/src/*.c
    ${A2B_STACK_ROOT}/a2bplugin-slave/src/*.c
    ${A2B_STACK_ROOT}/a2bstack-protobuf/src/*.c
    ${A2B_COMMCH_ROOT}/src/*.c
)

# ---------------------------------------------------------------------------
# Report what was found (useful during build-system bring-up)
# ---------------------------------------------------------------------------
list(LENGTH SRC_PAL     _pal_count)
list(LENGTH SRC_COMMON  _common_count)
list(LENGTH SRC_PNP     _pnp_count)
list(LENGTH SRC_STACK   _stack_count)

message(STATUS "PAL/app sources found:    ${_pal_count}")
message(STATUS "Common sources found:     ${_common_count}")
message(STATUS "PnP sources found:        ${_pnp_count}")
message(STATUS "A2B stack sources found:  ${_stack_count}")

# ---------------------------------------------------------------------------
# Include directories
# ---------------------------------------------------------------------------
set(INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}                             # local headers (platform/a2b/)
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/a2b               # features.h, conf.h, ctypes.h
    ${APP_COMMON_ROOT}
    ${A2B_PNP_ROOT}
    ${A2B_STACK_ROOT}/a2bstack/inc
    ${A2B_STACK_ROOT}/a2bstack/inc/a2b
    ${A2B_STACK_ROOT}/a2bstack/src
    ${A2B_STACK_ROOT}/a2bplugin-master/inc
    ${A2B_STACK_ROOT}/a2bplugin-master/src
    ${A2B_STACK_ROOT}/a2bplugin-slave/inc
    ${A2B_STACK_ROOT}/a2bplugin-slave/src
    ${A2B_STACK_ROOT}/a2bstack-protobuf/inc
    ${A2B_COMMCH_ROOT}/inc
)

# ---------------------------------------------------------------------------
# Build target — only created when at least one PAL/app source exists.
# Run `cmake ..` with no source files present to validate the toolchain;
# add PAL source files (pal_i2c.c, pal_timer.c, pal_gpio.c, main.c) to
# enable the build target.
# ---------------------------------------------------------------------------
set(ALL_SOURCES ${SRC_PAL} ${SRC_COMMON} ${SRC_PNP} ${SRC_STACK})
list(LENGTH ALL_SOURCES _total_count)

if(_total_count GREATER 0)
    add_executable(a2b_pnp ${ALL_SOURCES})

    target_include_directories(a2b_pnp PRIVATE ${INCLUDE_DIRS})

    target_compile_definitions(a2b_pnp PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )

    # Link libgpiod v1 (pre-installed on Raspberry Pi OS)
    target_link_libraries(a2b_pnp PRIVATE gpiod m)

    # Per-build-type flags
    target_compile_options(a2b_pnp PRIVATE
        $<$<CONFIG:Debug>:   -O0 -g3>
        $<$<CONFIG:Release>: -O2>
        -Wall -Wextra
    )

    message(STATUS "Target 'a2b_pnp' configured with ${_total_count} source file(s).")
else()
    message(STATUS
        "No source files found yet — toolchain validation only. "
        "Add pal_i2c.c, pal_timer.c, pal_gpio.c, main.c to enable build target.")
endif()
