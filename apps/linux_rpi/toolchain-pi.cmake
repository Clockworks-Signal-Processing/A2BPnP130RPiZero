# toolchain-pi.cmake
# CMake cross-compilation toolchain for Raspberry Pi Zero 2W
# Target: 32-bit Raspberry Pi OS (armhf) on ARM Cortex-A53
# Host:   x86_64 Linux (WSL2)
# Toolchain package: crossbuild-essential-armhf

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Cross-compiler binaries installed by crossbuild-essential-armhf
set(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)

# crossbuild-essential-armhf configures the compiler's own sysroot
# automatically — do NOT set CMAKE_SYSROOT here, as it causes CMake to
# prepend the path to every library reference (e.g., libc.so.6 becomes
# /sysroot/usr/arm-linux-gnueabihf/lib/libc.so.6) which breaks linking.
#
# If you later deploy a full Debian armhf sysroot (e.g., via
# debootstrap or qemu-debootstrap) for finer-grained control, you can
# set CMAKE_SYSROOT to that path and re-enable the lines below.

# Search host system for build tools (cmake, make), but limit library
# and header searches to cross-compiled prefix.
set(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Ensure we target hard-float ABI (armhf) — Pi Zero 2W has VFPv4
set(CMAKE_C_FLAGS_INIT   "-march=armv8-a -mfpu=neon-fp-armv8 -mfloat-abi=hard")
set(CMAKE_CXX_FLAGS_INIT "-march=armv8-a -mfpu=neon-fp-armv8 -mfloat-abi=hard")
