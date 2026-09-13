# Linux-host clang-cl toolchain targeting the MSVC ABI against an `xwin`
# Windows SDK/CRT sysroot. Pair with the vcpkg overlay triplet/port in
# examples/linux-cross-compile/.
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR AMD64)

# Debian/Ubuntu register only versioned names, so keep the fallbacks. Newest
# first: an older version present alongside a newer one (e.g. a transitive
# apt dependency) must not silently win over one a caller explicitly installed.
set(_clangcl_names clang-cl clang-cl-20 clang-cl-19 clang-cl-18 clang-cl-17 clang-cl-16 clang-cl-15)
set(_lldlink_names lld-link lld-link-20 lld-link-19 lld-link-18 lld-link-17 lld-link-16 lld-link-15)
set(_llvmrc_names  llvm-rc llvm-rc-20 llvm-rc-19 llvm-rc-18 llvm-rc-17 llvm-rc-16 llvm-rc-15)
set(_llvmmt_names  llvm-mt llvm-mt-20 llvm-mt-19 llvm-mt-18 llvm-mt-17 llvm-mt-16 llvm-mt-15)

find_program(CMAKE_C_COMPILER NAMES ${_clangcl_names} REQUIRED)
find_program(CMAKE_CXX_COMPILER NAMES ${_clangcl_names} REQUIRED)
find_program(CMAKE_LINKER NAMES ${_lldlink_names} REQUIRED)

# Every link on this toolset runs a resource compiler and manifest tool,
# including CMake's own ABI-detection try-compile; unset, they default to
# "rc"/"mt", which exist only in a real MSVC install.
find_program(CMAKE_RC_COMPILER NAMES ${_llvmrc_names})
find_program(CMAKE_MT NAMES ${_llvmmt_names})

# The sysroot must come from `xwin ... splat --use-winsysroot-style
# --preserve-ms-arch-notation`; without either flag nothing under
# /winsysroot resolves. Override the path with -DXWIN_SYSROOT or $XWIN_SYSROOT.
if(DEFINED XWIN_SYSROOT)
    set(_xwin_sysroot "${XWIN_SYSROOT}")
elseif(DEFINED ENV{XWIN_SYSROOT})
    set(_xwin_sysroot "$ENV{XWIN_SYSROOT}")
else()
    set(_xwin_sysroot "$ENV{HOME}/xwin-out")
endif()

# This file is chainloaded several times per configure, so the guard must
# stay: without it CACHE...FORCE re-appends these flags on every pass.
# /EHsc belongs here rather than in the consumer's flags because vcpkg
# builds each dependency in an isolated configure that inherits only this
# file, and clang-cl otherwise defaults to exceptions disabled.
set(_xwin_compile_flags "--target=x86_64-pc-windows-msvc /winsysroot${_xwin_sysroot}")

if(NOT CMAKE_CXX_FLAGS MATCHES "winsysroot")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${_xwin_compile_flags}" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_xwin_compile_flags} /EHsc" CACHE STRING "" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /winsysroot:${_xwin_sysroot}" CACHE STRING "" FORCE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /winsysroot:${_xwin_sysroot}" CACHE STRING "" FORCE)
endif()

# CMAKE_RC_FLAGS is separate from CMAKE_C_FLAGS/CMAKE_CXX_FLAGS; needs its own sysroot guard or winres.h etc. fail to resolve.
if(NOT CMAKE_RC_FLAGS MATCHES "winsysroot")
    set(CMAKE_RC_FLAGS "${CMAKE_RC_FLAGS} ${_xwin_compile_flags}" CACHE STRING "" FORCE)
endif()
