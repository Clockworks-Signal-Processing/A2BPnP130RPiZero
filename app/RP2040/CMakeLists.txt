cmake_minimum_required (VERSION 3.13)
project(RP2040_A2B_App)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# NOTE: pico_sdk_init() is called in the root CMakeLists.txt - do not call again here

file(GLOB_RECURSE SRC_FILES_EXEC
    ${CMAKE_CURRENT_SOURCE_DIR}/a2bapp_rp2040.c
    ${CMAKE_CURRENT_SOURCE_DIR}/CSP_EVM_adi_a2b_busconfig.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ADI_EVM_adi_a2b_busconfig.c
    ${CMAKE_CURRENT_SOURCE_DIR}/12_a2b_busconfig.c
    ${CMAKE_CURRENT_SOURCE_DIR}/platform_inits.c
    ${CMAKE_CURRENT_SOURCE_DIR}/a2bstack-pal/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/a2bstack-pal/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/a2bstack-pal/*.hpp
)

file(GLOB_RECURSE SRC_FILES_APP_COMMON
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/*.c
)

file(GLOB_RECURSE SRC_FILES_PNP_LIB
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bpnp/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bpnp/*.cpp
)

file(GLOB_RECURSE SRC_FILES_LIB
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bstack/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bcommchannel/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bplugin-master/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bplugin-slave/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bstack-protobuf/src/*.c
)

file(GLOB_RECURSE SRC_FILES_APP_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../test/cJSON-master/*.c
)

add_definitions(-DA2B_STATIC_PLUGIN -DPB_FIELD_16BIT=1)

add_executable(${PROJECT_NAME}
    ${SRC_FILES_EXEC}
    ${SRC_FILES_APP_COMMON}
    ${SRC_FILES_PNP_LIB}
    ${SRC_FILES_APP_TEST}
    ${SRC_FILES_LIB}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    ${CMAKE_CURRENT_SOURCE_DIR}/a2bstack-pal
    ${CMAKE_CURRENT_SOURCE_DIR}/a2bstack-pal/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bpnp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bstack/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bstack/inc/a2b
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bstack/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bcommchannel/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bplugin-master/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bplugin-master/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bplugin-slave/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bplugin-slave/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../a2bstack/a2bstack-protobuf/inc
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/a2bstack-pal/spi.pio)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pico_stdlib
    pico_stdio
    pico_unique_id
    hardware_pio
    pico_multicore
    hardware_adc
    hardware_spi
    hardware_pwm
    hardware_uart
    hardware_gpio
    hardware_dma
    hardware_i2c
)

# Enable USB stdio
pico_enable_stdio_usb(${PROJECT_NAME} 1)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    _CRT_SECURE_NO_WARNINGS
)

pico_add_extra_outputs(${PROJECT_NAME})
