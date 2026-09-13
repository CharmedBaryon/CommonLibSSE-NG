# Linux-host cross-compilation

Build CommonLibSSE-NG (and plugins that statically link it) on a Linux
host, targeting the same Windows PE / MSVC ABI output as a native
Windows build, using `clang-cl` + `lld-link` against a Windows SDK/CRT
sysroot obtained with [`xwin`](https://github.com/Jake-Shadle/xwin).

## One-time setup

```bash
# Toolchain adjust for your distro
# Arch
sudo pacman -S clang lld llvm cmake ninja rust git

# Debian 13 "Trixie"
sudo apt-get install clang lld llvm cmake ninja-build rustup git
rustup default stable

# Wine + llvm-mingw: needed only to build/run the fxc2 shader-compile
# stand-in (see below), not for the main build itself.
# Arch
sudo pacman -S wine llvm-mingw

# Debian; Use manual install of llvm-mingw.
sudo apt-get install wine wget

# Manual llvm-mingw install for Distros that don't have a native package.
cd /tmp
wget https://github.com/mstorsjo/llvm-mingw/releases/download/20260826/llvm-mingw-20260826-ucrt-ubuntu-22.04-x86_64.tar.xz
tar -xf llvm-mingw-20260826-ucrt-ubuntu-22.04-x86_64.tar.xz
sudo mkdir /opt/llvm-mingw/
sudo mv llvm-mingw-20260826-ucrt-ubuntu-22.04-x86_64/* /opt/llvm-mingw/
export LLVM_MINGW_BIN=/opt/llvm-mingw/bin

# xwin, pinned for reproducibility
cargo install xwin --version 0.10.0 --locked
export PATH="$HOME/.cargo/bin:$PATH"

# Windows SDK + MSVC CRT sysroot. Both flags are required:
# without --use-winsysroot-style, /winsysroot finds nothing;
# without --preserve-ms-arch-notation, folders are named x86_64 instead of x64 and lld-link's auto-search fails.
mkdir -p ~/xwin-cache ~/xwin-out
xwin --accept-license --http-retry 10 --cache-dir ~/xwin-cache splat \
  --output ~/xwin-out --include-debug-libs \
  --use-winsysroot-style --preserve-ms-arch-notation

# vcpkg
git clone https://github.com/microsoft/vcpkg ~/.local/share/vcpkg
~/.local/share/vcpkg/bootstrap-vcpkg.sh -disableMetrics
export VCPKG_ROOT=~/.local/share/vcpkg
```

If your sysroot lives somewhere other than `~/xwin-out`, either pass
`-DXWIN_SYSROOT=<path>` to the configure step or export
`XWIN_SYSROOT=<path>` first.

## Build

```bash
cmake --preset build-release-linux-clangcl-vcpkg-all
cmake --build --preset release-linux-clangcl-vcpkg-all
```

`CommonLibSSETests.exe` will be a Windows PE executable, and
`CommonLibSSE.lib` will be a Windows COFF library archive, both in
`build/release-linux-clangcl-vcpkg-all/`. Verify the executable with:

```bash
file build/release-linux-clangcl-vcpkg-all/CommonLibSSETests.exe
# expect: PE32+ executable ... x86-64, for MS Windows
```

A clean build proves the toolchain, not runtime correctness: struct
layout or vtable mismatches between clang-cl output and the real MSVC
game binary compile fine and only surface as an in-game crash. Always
test any plugin built this way in-game.

## Why the shader-compile workaround exists

`directxtk` (a transitive dependency via `vcpkg.json`) compiles its
bundled HLSL shaders at build time using the Windows SDK's `fxc.exe`,
which doesn't exist in an `xwin` sysroot (`xwin` only stages headers
and import libraries, not SDK tools). This directory's overlay
`directxtk` port fetches and builds a small Wine-runnable stand-in from
[WasabiIceCream/fxc2](https://github.com/WasabiIceCream/fxc2) (a
patched `mozilla/fxc2`, MPL-2.0) instead, and patches DirectXTK's
shader-compile step to run under Wine.

## Files here

- `custom-triplets/x64-windows-clangcl.cmake`: vcpkg triplet that
  chainloads `../../cmake/toolchain-linux-clangcl.cmake` for every
  dependency vcpkg builds.
- `custom-ports/directxtk/`: overlay port implementing the shader-compile
  workaround above.

Both are wired in via the `build-*-linux-clangcl-vcpkg-*` presets in the
repo's top-level `CMakePresets.json` (`VCPKG_OVERLAY_TRIPLETS`/
`VCPKG_OVERLAY_PORTS`), not required by the core `CMakeLists.txt`/
`vcpkg.json` at all. A plugin that only needs the toolchain file itself
(not vcpkg, e.g. building `directxtk` some other way) can use
`cmake/toolchain-linux-clangcl.cmake` on its own.
