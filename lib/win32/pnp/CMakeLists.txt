

include_directories(${A2B_STACK_ROOT}/a2bstack/inc
${A2B_STACK_ROOT}/a2bstack/inc/a2b
${A2B_APP_ROOT}/win32/a2bstack-pal/platform/
${A2B_STACK_ROOT}/a2bstack/src
${A2B_STACK_ROOT}/a2bstack-protobuf/inc
${A2B_STACK_ROOT}/a2bstack-protobuf/src
${A2B_STACK_ROOT}/a2bplugin-master/inc
${A2B_STACK_ROOT}/a2bplugin-master/src
${A2B_STACK_ROOT}/a2bplugin-slave/inc
${A2B_STACK_ROOT}/a2bplugin-slave/src
${A2B_PNP_ROOT}
)

#add_definitions(-DA2B_SS_STACK=1)

file(GLOB_RECURSE SRC_FILES_PNP_LIB 
${A2B_PNP_ROOT}/*.c
${A2B_PNP_ROOT}/*.cpp 
)




if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    # Tell CMake where to find the executable source file
    add_library(${A2B_PNP_LIB}  
    ${SRC_FILES_PNP_LIB}
    )
    target_compile_options(${A2B_PNP_LIB}  PUBLIC -Wall -Wextra -Wl,--export-dynamic)
    add_custom_command(TARGET ${A2B_PNP_LIB}  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${A2B_PNP_BUILD}/lib/win32/pnp/lib${A2B_PNP_LIB}.a"
            "${A2B_LIB_ROOT}/win32/pnp/lib${A2B_PNP_LIB}.a"
    COMMENT "Copying file after build"
)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Tell CMake where to find the executable source file
    add_library(${A2B_PNP_LIB}  
    ${SRC_FILES_PNP_LIB}
    )
    target_compile_options(${A2B_PNP_LIB}  PUBLIC -Wall)
    
endif()






