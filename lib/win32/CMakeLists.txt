# Note that this file can be used as a top level CMakeLists.txt to build all the Demos (it includes
# them all, but they are usable in their own right, which is why no common work is done here)


add_subdirectory(pnp)
#add_subdirectory(stack)
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
if(CYPRESS_MSVC)
add_subdirectory(USBiNet)
endif()
endif()
