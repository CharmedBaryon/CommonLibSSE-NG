# Prebuilt CommonLib bundles

Each release attaches prebuilt **static-library bundles** so downstream projects can
consume CommonLib without recompiling it (CommonLib is the bulk of a plugin's build
time). There is one bundle per build system — **xmake** and **CMake** — both baked with
the same config below. They are produced and self-tested by
`.github/workflows/prebuilt.yml` and attached to the release.

Both build systems **auto-fetch** their bundle on a clean release tag (see the auto-fetch
sections), so in the common case you change nothing in your repo.

## What's in the xmake bundle

`commonlibsse-ng-prebuilt-<tag>-all-msvc.7z` is a drop-in replacement for the
`lib/commonlibsse-ng` source tree:

```
xmake.lua            # the same build script, which auto-detects lib/commonlibsse-ng.lib
                     #   and links it instead of compiling src/ ("prebuilt mode")
include/             # public headers (RE/ REL/ REX/ SKSE/)
res/                 # commonlibsse-ng.plugin rule templates
extern/openvr/headers/   # VR headers (the "all" config enables VR)
lib/commonlibsse-ng.lib  # the prebuilt static library
PREBUILT.md
```

## Baked configuration (must match in the consumer)

The library is compiled **once**, for the config our xmake consumers use:

| Axis | Value |
|------|-------|
| Runtime | **all** — `skyrim_se` + `skyrim_ae` + `skyrim_vr` |
| REX | **`rex_ini` + `rex_json` + `rex_toml`** on (the full superset) |
| Trampoline | **`skse_xbyak`** on |
| Patch diagnostics | **`skse_patch_safety`** on |
| Build | `releasedbg`, x64, **MSVC** |
| C++ | C++23 |

A prebuilt static library bakes its config and toolchain in. To link it safely a
consumer **must** build with a compatible setup:

- Compatible options: keep the `skyrim_*` runtimes **all on** (they default on and are the
  one layout-critical axis — disabling a runtime is **not** served, build from source). Every
  REX config (`rex_ini`/`rex_json`/`rex_toml`) and `skse_xbyak` is additive and **all baked**,
  so the lib is a full superset: a consumer may enable any combination (or none) and still
  link — the symbols are present regardless.
- Same mode/ABI: xmake `releasedbg` (release CRT `/MD`, `NDEBUG`). No `debug` bundle
  is published. A true `debug` build must compile from source.
- Patch diagnostics are compiled into the bundle. To disable them with
  `--skse_patch_safety=n`, build CommonLib from source.
- Same compiler family (**MSVC**) and a compatible MSVC toolset version. Toolset drift
  between this bundle and the consumer is the most common cause of link/ABI errors.

## How to consume (xmake)

Replace the `lib/commonlibsse-ng` **source submodule** with the **extracted bundle**
(same path). Your existing build is otherwise unchanged:

```lua
set_config("rex_ini", true)      -- match the bundle
set_config("skse_xbyak", true)
includes("lib/commonlibsse-ng")  -- now a prebuilt bundle, not source

target("my-plugin")
    add_deps("commonlibsse-ng")
    add_rules("commonlibsse-ng.plugin", { name = "my-plugin", author = "you" })
    add_files("src/**.cpp")
```

`includes()` runs the bundled `xmake.lua`, which sees `lib/commonlibsse-ng.lib` and
switches to prebuilt mode — same target, same `commonlibsse-ng.plugin` rule, same
transitive deps (`directxmath`, `directxtk`, `spdlog`, `simpleini`, `xbyak`,
`rapidcsv`), just no CommonLib recompile.

## Automatic fetch on a clean release tag (no bundle swap needed)

You don't have to extract the bundle by hand. When CommonLib is consumed as a normal
**source submodule** pinned to a clean release **tag**, `xmake.lua` will — in CI
(`GITHUB_ACTIONS`), or anywhere with `COMMONLIB_PREBUILT=1` — download that tag's bundle
from the GitHub release, verify its `.sha256`, and link it instead of compiling. So a
plugin whose `lib/commonlibsse-ng` submodule sits on `vX.Y.Z` gets the prebuilt for free
on CI, with zero changes to its repo.

It falls back to a normal **source build** whenever the prebuilt can't be used safely:
not on an exact tag, a dirty submodule, a missing/unverified asset, or no network. Once
fetched, a disabled runtime (an ABI-incompatible header layout) is refused so it can't
silently mislink. The download is cached under `build/.prebuilt/<tag>` and attempted at most
once per tag. Local dev builds stay source-by-default (set `COMMONLIB_PREBUILT=1` to opt in).
The consumer only needs the `skyrim_*` runtimes on (the default); `rex_ini`/`rex_json`/
`rex_toml`/`skse_xbyak` are all optional (the lib bakes them all).

## Size & cost

The `releasedbg` "all" library carries full debug info for three runtimes, so it is
**~1.2 GB extracted** — but compresses ~24× to a **~52 MB** download. A consumer build
against it is **seconds** (e.g. ~6 s for the self-test plugin) versus a full source
build (minutes cold). The large on-disk size is the trade for keeping CommonLib frames
symbolicatable in crash logs; the extra link cost is negligible.

## CMake bundle

`commonlibsse-ng-prebuilt-<tag>-all-msvc-cmake.zip` serves **`add_subdirectory`**
consumers (the common extern-path setup). It carries just the build outputs the consumer
links against:

```
lib/CommonLibSSE.lib     # the prebuilt static library (Release)
lib/openvr_api.lib       # linked PUBLIC by the target (the "all" config enables VR)
include/                 # public headers (RE/ REL/ REX/ SKSE/)
extern/openvr/headers/   # VR headers
PREBUILT.md
```

It is **not** a `find_package` install tree: instead the consumer's
`add_subdirectory(<commonlib>)` runs `cmake/Prebuilt.cmake`, which resolves the bundle
and defines `CommonLibSSE` as an **IMPORTED** target pointing at these local paths. This
sidesteps `find_package`/`install(EXPORT)` relocatability entirely — the paths are the
just-extracted bundle's own.

The bundle is baked the same as the xmake one (skyrim all + `skse_xbyak` + all REX configs,
MSVC, **`Release`** `/MD NDEBUG`, C++23), but the consumer only has to match the part that
is ABI-critical. The **runtime set** (`ENABLE_SKYRIM_SE/AE/VR=ON`) changes the layout of
dozens of public headers, so a consumer **must** build for all three. Every REX config
(`REX_OPTION_INI`/`JSON`/`TOML`) and `SKSE_SUPPORT_XBYAK` is **additive** — each adds a
self-contained `#if`'d namespace/block with no layout change (xbyak adds one non-virtual
`Trampoline` method, again no data member) — and the bundle **bakes them all**, so the lib is
a full **superset**: a consumer may enable any combination, or none, and still link (it sees
only the API it enabled, since the IMPORTED target defines only the consumer's options).

### Automatic fetch on a clean release tag (CMake)

When CommonLib is consumed via `add_subdirectory` from a source submodule pinned to a
clean release **tag**, `cmake/Prebuilt.cmake` will — in CI (`GITHUB_ACTIONS`), or anywhere
with `-DCOMMONLIB_PREBUILT=ON` — download that tag's `…-cmake.zip`, verify its `.sha256`,
extract it, and expose the IMPORTED target instead of compiling `src/`. A plugin whose
submodule sits on `vX.Y.Z` gets the prebuilt for free on CI, unchanged.

It falls back to a normal **source build** whenever the prebuilt can't be used safely: the
top-level project is CommonLib itself (you only auto-fetch when *consumed*), a Debug or
multi-config build (the bundle is Release `/MD`; a Debug `/MDd` link would be an ABI
mismatch), a **static-CRT** consumer (`/MT` / the `x64-windows-static` triplet — the bundle
is `/MD`, so the CRTs would collide), not on an exact tag, a dirty tree, options that don't
match the baked config, a missing/unverified asset, or a **different MSVC toolset** than the
one that produced the bundle (see below).

A CRT/config match doesn't guarantee the bundle links: its objects may reference MSVC STL
internal dispatch helpers (e.g. `__std_replace_copy_2`) that only exist in the import libs of
a specific toolset/SDK vintage — not part of the stable ABI, so a toolset mismatch in either
direction can hit a deep `LNK2001` at final link that a CRT/config check can't predict. The
bundle carries a `TOOLSET_VERSION.txt` stamp (the producing `cl.exe` version); `Prebuilt.cmake`
rejects the bundle — falling back to source, with a `STATUS` message — unless the consumer's
toolset shares the same **major.minor** version (an exact patch/build match would over-trigger
on ordinary servicing updates that change nothing relevant). This only protects against
version *drift*, not a preview/Insiders channel that has genuinely dropped or not-yet-added a
given internal symbol at the same nominal version — that residual case still needs a manual
`-DCOMMONLIB_PREBUILT=OFF`. A bundle published before this stamp existed, or a non-MSVC/clang-cl
compiler (whose reported version isn't the cl.exe toolset version this stamp compares against),
is treated as compatible (no change for already-published tags).

A **multi-config generator** (Visual Studio) is skipped by default because the config is
chosen at build time, so Debug can't be ruled out. A consumer that only ever builds
release-like configs can opt in with **`-DCOMMONLIB_PREBUILT_MULTICONFIG=ON`** (e.g. in its
preset's `cacheVariables`): the IMPORTED target serves Release (RelWithDebInfo/MinSizeRel map
onto it) and maps **Debug to nothing**, so a stray Debug build fails loudly rather than
silently linking the Release lib into a `/MDd` target.

The download is cached under
`${CMAKE_CURRENT_BINARY_DIR}/.prebuilt/<tag>` — with the advertised
`add_subdirectory(… commonlib)` layout that is the CommonLib sub-build dir, e.g.
`<build>/commonlib/.prebuilt/<tag>` — and attempted at most once per tag. Local dev builds
stay source-by-default (`-DCOMMONLIB_PREBUILT=ON` to opt in), or point
`-DCOMMONLIB_PREBUILT_DIR=<extracted bundle>` at a bundle to skip the download.

The headers link `spdlog`/`DirectXTK` PUBLIC, so the consumer provides those header deps
from **its own `vcpkg.json`** (`spdlog`, `fmt`, `directxtk`, `directxmath`) — exactly as a
source build already requires. The REX config parsers (simpleini / nlohmann / toml11) live
only in `REX.cpp` and their public headers (`REX::INI/JSON/TOML`) are dep-free, so a prebuilt
consumer using them needs **nothing extra** — the parser is baked into the lib. The one
exception is **`xbyak`**: `SKSE/ContextHook.h` includes `<xbyak/xbyak.h>` directly, so a
consumer that enables `SKSE_SUPPORT_XBYAK` must add `xbyak`. As with any CommonLibSSE-NG
plugin, the consumer also supplies a **PCH** that includes `<SKSE/Impl/PCH.h>` and
`using namespace std::literals;` (the headers are PCH-dependent). See
`tests/prebuilt-consumer-cmake/` for a minimal working consumer.

### vcpkg-port consumers

Consumers that pull `"commonlibsse-ng"` through `vcpkg.json` (rather than
`add_subdirectory`) are served by **vcpkg binary caching** (a shared GHA/NuGet/S3 backend)
so the port builds once and is restored across CI — idiomatic, no custom artifact.
