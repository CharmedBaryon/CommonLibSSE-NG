set(DIRECTXTK_TAG may2026)

if(VCPKG_TARGET_IS_MINGW)
    message(NOTICE "Building ${PORT} for MinGW requires the HLSL Compiler fxc.exe also be in the PATH. See https://aka.ms/windowssdk.")
endif()

# The patch reroutes shader compilation through `wine cmd /c`, so a native
# Windows build must not get it.
if(CMAKE_HOST_UNIX)
    set(DIRECTXTK_PATCHES PATCHES wine-shader-compile.patch)
else()
    set(DIRECTXTK_PATCHES "")
endif()

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO Microsoft/DirectXTK
    REF ${DIRECTXTK_TAG}
    SHA512 9306774b06f52b4c37938fe4b3a10df8c7a85652188a25dc25e60ae9ff6fbf9d2cf920b114de3fc3945c564054cbb166cc45fca073021129e75ce282a51636e7
    HEAD_REF main
    ${DIRECTXTK_PATCHES}
)

# Do not switch this back to trusting CompileShaders.cmd: under `wine cmd`
# both its exit status and its own messages report failure on fully
# successful runs, so success is decided by counting .inc files against the
# invocations it echoed, and stale .inc files are deleted first so they
# cannot mask a failure.
if(CMAKE_HOST_UNIX)
    file(WRITE "${SOURCE_PATH}/Src/Shaders/wine-compile-shaders.sh" "#!/bin/sh
set -u
CompileShadersOutput=\"$1\"
FxcTool=\"$2\"
shift 2
find \"$CompileShadersOutput\" -type f -name '*.inc' -delete 2>/dev/null || true
\"${CMAKE_COMMAND}\" -E env CompileShadersOutput=\"$CompileShadersOutput\" WINEDEBUG=-all LegacyShaderCompiler=\"$FxcTool\" wine cmd /c CompileShaders.cmd \"$@\" > \"$CompileShadersOutput/compileshaders.log\" 2>&1
if grep -q \"Got an error\" \"$CompileShadersOutput/compileshaders.log\"; then
    echo \"fxc2 reported shader compilation error(s); see $CompileShadersOutput/compileshaders.log\" >&2
    exit 1
fi
# Derived, not hardcoded, so a DirectXTK version bump can't silently
# invalidate it. grep -c exits 1 on no match, hence `|| true`.
expected_count=\$(grep -c '^\"' \"$CompileShadersOutput/compileshaders.log\" 2>/dev/null || true)
[ -n \"\$expected_count\" ] || expected_count=0
inc_count=\$(find \"$CompileShadersOutput\" -type f -name '*.inc' 2>/dev/null | wc -l)
if [ \"\$expected_count\" -eq 0 ] || [ \"\$inc_count\" -ne \"\$expected_count\" ]; then
    echo \"Shader compilation produced \$inc_count .inc file(s), expected \$expected_count; see $CompileShadersOutput/compileshaders.log\" >&2
    echo \"--- diagnostics ---\" >&2
    ls -la \"$FxcTool\" >&2 2>&1 || echo \"(no fxc2 binary at that path)\" >&2
    command -v file >/dev/null 2>&1 && file \"$FxcTool\" >&2 2>&1 || true
    wine --version >&2 2>&1 || true
    echo \"--- direct wine invocation, bypassing cmd.exe ---\" >&2
    WINEDEBUG=-all wine \"$FxcTool\" >&2 2>&1 || echo \"(direct wine invocation also failed)\" >&2
    exit 1
fi
exit 0
")
endif()

vcpkg_check_features(
    OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        gameinput BUILD_GAMEINPUT
        windows-gaming-input BUILD_WGI
        spectre ENABLE_SPECTRE_MITIGATION
        tools BUILD_TOOLS
        xaudio2-9 BUILD_XAUDIO_WIN10
        xaudio2-8 BUILD_XAUDIO_WIN8
        xaudio2redist BUILD_XAUDIO_REDIST
)

# A Linux host has no Windows SDK fxc.exe for DirectXTK to find, so build
# the fxc2 stand-in (MPL-2.0, runs under Wine) and pre-set
# DIRECTX_FXC_TOOL; find_program() leaves an already-set cache variable
# alone, so DirectXTK's own wiring then picks it up.
if(CMAKE_HOST_UNIX)
    # Keep this on HINTS rather than PATH: llvm-mingw ships its own
    # clang-cl/lld-link, and on PATH they shadow the real toolchain's and
    # break the link step with unrelated-looking errors.
    find_program(FXC2_MINGW_CLANGXX NAMES x86_64-w64-mingw32-clang++ HINTS "$ENV{LLVM_MINGW_BIN}")
    if(NOT FXC2_MINGW_CLANGXX)
        message(FATAL_ERROR "${PORT}: cross-compiling from a Linux host needs an llvm-mingw toolchain (x86_64-w64-mingw32-clang++) on PATH, or pointed at via the LLVM_MINGW_BIN environment variable, to build the fxc2 shader-compiler stand-in. See https://github.com/WasabiIceCream/fxc2.")
    endif()

    vcpkg_from_github(
        OUT_SOURCE_PATH FXC2_SOURCE_PATH
        REPO WasabiIceCream/fxc2
        REF v1.0.0
        SHA512 1d5d67157983058e0bbad3f5fca4c56caa46f29b12c0cdd3efa6a3efc7b3bd5321b4dcbb1c2cdac17569d9271146a8eef61225fb4469f41123584f52178d643e
        HEAD_REF master
    )

    set(FXC2_EXE "${CURRENT_BUILDTREES_DIR}/fxc2.exe")
    execute_process(
        COMMAND "${FXC2_MINGW_CLANGXX}" -static "${FXC2_SOURCE_PATH}/fxc2.cpp" -o "${FXC2_EXE}"
        RESULT_VARIABLE FXC2_BUILD_RESULT
    )
    if(NOT FXC2_BUILD_RESULT EQUAL 0)
        message(FATAL_ERROR "${PORT}: failed to build fxc2.exe from ${FXC2_SOURCE_PATH}")
    endif()
    file(COPY "${FXC2_SOURCE_PATH}/d3dcompiler_47.dll" DESTINATION "${CURRENT_BUILDTREES_DIR}")

    set(DIRECTXTK_FXC2_OPTIONS "-DDIRECTX_FXC_TOOL=${FXC2_EXE}")
else()
    set(DIRECTXTK_FXC2_OPTIONS "")
endif()

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${FEATURE_OPTIONS} ${DIRECTXTK_FXC2_OPTIONS}
)

vcpkg_cmake_install()
vcpkg_fixup_pkgconfig()
vcpkg_cmake_config_fixup(CONFIG_PATH share/directxtk)

if("tools" IN_LIST FEATURES)

  vcpkg_download_distfile(
    MAKESPRITEFONT_EXE
    URLS "https://github.com/Microsoft/DirectXTK/releases/download/${DIRECTXTK_TAG}/MakeSpriteFont.exe"
    FILENAME "makespritefont-${DIRECTXTK_TAG}.exe"
    SHA512 1b3f6e2b9394316bfb0ef828850368be9b3ca6227501c28e09a108763f63e2a010588222ee6a3f64233ca8deae663098ca407e41c2a0c93a745078dc24053f5f
  )

  file(MAKE_DIRECTORY "${CURRENT_PACKAGES_DIR}/tools/directxtk/")

  file(INSTALL "${MAKESPRITEFONT_EXE}" DESTINATION "${CURRENT_PACKAGES_DIR}/tools/directxtk/")

  file(RENAME "${CURRENT_PACKAGES_DIR}/tools/directxtk/makespritefont-${DIRECTXTK_TAG}.exe" "${CURRENT_PACKAGES_DIR}/tools/directxtk/makespritefont.exe")

  if(VCPKG_TARGET_ARCHITECTURE STREQUAL x64)

    vcpkg_download_distfile(
      XWBTOOL_EXE
      URLS "https://github.com/Microsoft/DirectXTK/releases/download/${DIRECTXTK_TAG}/XWBTool.exe"
      FILENAME "xwbtool-${DIRECTXTK_TAG}.exe"
      SHA512 1b79d2f2d46a656810e8ef9e2061c9f0071f8304187a144e2aebbfdba2da3d9133a91114e22dcfc178f0bcf8fdb421640252800caea993c27bf987f2e50abafa
    )

    file(INSTALL "${XWBTOOL_EXE}" DESTINATION "${CURRENT_PACKAGES_DIR}/tools/directxtk/")

    file(RENAME "${CURRENT_PACKAGES_DIR}/tools/directxtk/xwbtool-${DIRECTXTK_TAG}.exe" "${CURRENT_PACKAGES_DIR}/tools/directxtk/xwbtool.exe")

  elseif((VCPKG_TARGET_ARCHITECTURE STREQUAL arm64) OR (VCPKG_TARGET_ARCHITECTURE STREQUAL arm64ec))

    vcpkg_download_distfile(
      XWBTOOL_EXE
      URLS "https://github.com/Microsoft/DirectXTK/releases/download/${DIRECTXTK_TAG}/XWBTool_arm64.exe"
      FILENAME "xwbtool-${DIRECTXTK_TAG}-arm64.exe"
      SHA512 dabffcb328f440eb699fcc80f3e33bb093e2f067fa6114bf0a5c521eaa5ab935ac568195a2e25eccb5c228b0ab1b1979121d6936eadae7f3dec8a2aed648a9b4
    )

    file(INSTALL "${XWBTOOL_EXE}" DESTINATION "${CURRENT_PACKAGES_DIR}/tools/directxtk/")

    file(RENAME "${CURRENT_PACKAGES_DIR}/tools/directxtk/xwbtool-${DIRECTXTK_TAG}-arm64.exe" "${CURRENT_PACKAGES_DIR}/tools/directxtk/xwbtool.exe")

  else()

    vcpkg_copy_tools(
          TOOL_NAMES XWBTool
          SEARCH_DIR "${CURRENT_BUILDTREES_DIR}/${TARGET_TRIPLET}-rel/bin"
      )

  endif()
endif()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
