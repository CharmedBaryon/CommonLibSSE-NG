# Builds dependencies with clang-cl targeting the MSVC ABI; vcpkg's default
# x64-windows triplet assumes real MSVC on PATH.
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)

# Do not set VCPKG_CMAKE_SYSTEM_NAME to "Windows": vcpkg only sets
# VCPKG_TARGET_IS_WINDOWS when it is undefined or empty, so naming it
# silently unsets that. The chainloaded toolchain does the real targeting.

# Path is relative to this file; update it if you copy this triplet into a
# different layout.
set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/../../../cmake/toolchain-linux-clangcl.cmake")
