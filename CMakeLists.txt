
# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico CACHE STRING "Board type")
include(pico_sdk_import.cmake)

project(MIDI2A2B_Platform_App LANGUAGES C CXX ASM)
#not sure this next line is needed, but I keep getting a windows one
set(CMAKE_SYSTEM_PROCESSOR "cortex-m0plus")

# this seems like a very crude way to do this, why can't I set up different build configs directly like in Eclipse?
#debug = -O0 and -g ?
#NM, apparently this won't work, I guess this file is just looked at on import.  Edit the /build/cmakecashe thing instead.  But don't reimport...
# see https://forums.raspberrypi.com/viewtopic.php?t=376987
# darn, CMAKE configure deletes the cache version but seems to ignore this too?
set (CMAKE_BUILD_TYPE "Debug")

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


add_compile_definitions(A2B_LINK_STATIC=1)
add_compile_definitions(A2B_STATIC_PLUGIN PB_FIELD_16BIT=1)
#decide which library & compiler combination to tuse
set(LIBUSB_MSVC OFF)
set(CYPRESS_MSVC OFF)
set(LIBUSB_MINGW OFF)

if(CYPRESS_MSVC)
add_compile_definitions(A2B_USBI_DOT_NET_DRIVER=1)
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set( A2B_STACK_ROOT  ${PROJECT_SOURCE_DIR}/a2bstack )
set( A2B_COMMCH_ROOT  ${PROJECT_SOURCE_DIR}/a2bcommchannel )
set( A2B_PNP_ROOT  ${PROJECT_SOURCE_DIR}/a2bpnp)
set( A2B_APP_ROOT   ${PROJECT_SOURCE_DIR}/app )
set( A2B_LIB_ROOT   ${PROJECT_SOURCE_DIR}/lib )
set( A2B_PNP_BUILD   ${PROJECT_SOURCE_DIR}/build )
set( A2B_STACK_LIB  "a2b-stack-rp2040" )
set( A2B_PNP_LIB  "a2b-pnp-rp2040" )
# not clear how the SDK is deciding on baud rate...seems to be a compiler command line thing vs something in a call the user could do.
add_compile_definitions(PICO_DEFAULT_UART_BAUD_RATE=230400)

#Name of the USBi dot net library
#set( A2B_USBI_LIB "USBi_lib")

#there were getting pulled in even thoug not WIN32
#if(WIN32)
#add_subdirectory(lib/win32)
#add_subdirectory(app/win32)
#endif()
add_compile_definitions(PARAM_ASSERTIONS_ENABLE_ALL=1)
add_compile_options(-O0)

message("CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Pico SDK version ${PICO_SDK_VERSION_STRING}")
# some sort of Cmake bug for processor type
add_subdirectory(app/RP2040)


