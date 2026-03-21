

include_directories(${A2B_STACK_ROOT}/a2bstack/inc
${A2B_APP_ROOT}/win32/a2bstack-pal
${A2B_STACK_ROOT}/a2bstack/inc/a2b
${A2B_APP_ROOT}/win32/a2bstack-pal/platform/
${A2B_STACK_ROOT}/a2bstack/src
${A2B_STACK_ROOT}/a2bstack-protobuf/inc
${A2B_STACK_ROOT}/a2bstack-protobuf/src
${A2B_STACK_ROOT}/a2bplugin-master/inc
${A2B_STACK_ROOT}/a2bplugin-master/src
${A2B_STACK_ROOT}/a2bplugin-slave/inc
${A2B_STACK_ROOT}/a2bplugin-slave/src
)

#add_definitions(-DA2B_SS_STACK=1)

file(GLOB_RECURSE SRC_FILES_LIB ${A2B_STACK_ROOT}/a2bstack/src/*.c 
${A2B_STACK_ROOT}/a2bplugin-master/src/*.c
${A2B_STACK_ROOT}/a2bplugin-slave/src/*.c 
${A2B_STACK_ROOT}/a2bstack-protobuf/src/*.c )

# Tell CMake where to find the executable source file
add_library(${A2B_STACK_LIB}  
${SRC_FILES_LIB}
)


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${A2B_STACK_LIB}  PUBLIC -Wall -Wextra -Wl,--export-dynamic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${A2B_STACK_LIB}  PUBLIC -Wall)
endif()



