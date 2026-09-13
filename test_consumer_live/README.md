# Live Verification Harness

This directory builds a real SKSE plugin used to verify `RE::detail::VtableShimBase`-style
adapters (currently `RE::MenuEventHandlerEx`) against a real, running Skyrim process --
not just a compile/link check.

## Purpose

Some CommonLib adapter classes exist specifically because a plugin can no longer safely
derive from an RE:: interface directly (the real engine vtable's slot layout differs by
runtime in a way a single compile-time C++ vtable can't represent -- see
`include/RE/M/MenuEventHandlerEx.h`). Getting the adapter's slot-patching logic right is
low-level ABI work (raw vtable synthesis, index math, pointer-cast thunks); it is
possible to write code that compiles cleanly, passes a Catch2 unit test, and is still
wrong, because a unit test only exercises **typed calls through the plugin's own
compiler-generated vtable** -- never the real engine's actual dispatch path (a blind
indexed call through the synthesized/patched table). That gap is exactly where a real
bug shipped once already (an off-by-one in `MenuEventHandlerEx`'s slot patching, caught
only by running this harness against a live game).

## What it does

At `kDataLoaded`, `RunSelfTest()`:
1. Constructs a `TestHandler : public RE::MenuEventHandlerEx`.
2. Logs each vtable slot's owning module (game vs. this plugin), confirming real default
   slots were copied from the game and only the intended slots were patched.
3. Calls a slot both the normal typed way (`h->ProcessButton(...)`) **and** via a raw,
   engine-style blind indexed call (`vtbl[N](h, ...)`, `N` computed the same way the real
   engine's dispatcher would pick it for the current runtime) -- the raw call is what
   actually proves the vtable is shaped the way an *external* caller expects, not just
   that our own code can call itself.
4. Checks `typeid(*h).name()` resolves to the real interface's name, confirming the
   Complete Object Locator reuse is valid.

`RunEndToEndTest()` goes one step further: rather than calling through a manually-held
pointer at all, it registers the handler with the real `RE::MenuControls`, constructs a
real `RE::ButtonEvent` via `RE::ButtonEvent::Create`, and injects it through
`RE::BSInputDeviceManager::SendEvent` -- the same public entry point real hardware input
uses (`MenuControls` is itself a registered `BSTEventSink<InputEvent*>` of that source).
This is the one test that proves the *real* dispatcher reaches the handler, not just that
our own simulation of it does.

`RunBrokenComparison()` (off by default -- see below) reproduces the *original* bug for
a controlled before/after: a class deriving directly from the real interface (the
pre-adapter pattern) has a genuinely too-short compiler vtable, so the same raw indexed
call reads past its end into adjacent `.rdata` and, when called, crashes -- the same
failure class as the upstream issue this adapter fixes.

## Running it

Requires a real Skyrim SE/AE install and `CrashLoggerSSE` installed if you want a crash
log from the broken-path comparison. Not part of CI -- GitHub Actions has no game to
launch against.

```powershell
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
# copy build/CommonLibSSELiveVerify.dll to <Skyrim SE/AE>/Data/SKSE/Plugins/
# launch skse64_loader.exe, load into a save (kDataLoaded fires once per process)
# read <Documents>/My Games/Skyrim Special Edition/SKSE/CommonLibSSELiveVerify.log
```

Builds flat (SE+AE) by default. For the VR variant, add `-DLIVE_VERIFY_VR=ON` to the
`cmake -B` line (use a separate build directory), deploy to `<SkyrimVR>/Data/SKSE/Plugins/`,
launch `sksevr_loader.exe` instead, and read the log under
`.../My Games/Skyrim VR/SKSE/`.

To also run the deliberate-crash comparison: configure with
`-DCMAKE_CXX_FLAGS=-DRUN_BROKEN_COMPARISON=1` (or edit the `#define` at the top of
`src/plugin.cpp`) and rebuild. **This will crash the game process** -- that's the
point; check `CrashLoggerSSE`'s output afterward.

## Adapting this for a different adapter

`PlayerInputHandler`/`HeldStateHandler` have the same underlying bug as
`MenuEventHandler` did, not yet fixed as of this writing. When a
`PlayerInputHandlerEx`/`HeldStateHandlerEx` lands, this harness generalizes directly:
swap `TestHandler`/`BrokenHandler`'s base classes and `RealProcessButtonSlot()`'s
returned values for the new adapter's real per-runtime slot layout (documented in the
adapter's own header).

## Relationship to Other Tests

- `tests/` - Unit (Catch2) tests of CommonLib functionality; run in CI, no real game.
- `test_package/` - Tests CommonLib as a Conan package (via `find_package`).
- `test_consumer/` - Tests CommonLib as a subdirectory dependency compiles (via
  `add_subdirectory`); run in CI, no real game.
- `test_consumer_live/` (this directory) - Tests specific low-level ABI adapters against
  a **real running game process**; local/manual only, not run in CI.
