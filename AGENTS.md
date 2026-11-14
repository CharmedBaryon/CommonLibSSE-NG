# AGENTS.md

Guidance for AI coding agents (and human contributors) working in this repository.
See `CLAUDE.md` for Claude-specific project/architecture detail and `CONTRIBUTING.md`
for the human-facing contribution workflow; this file is the agent-facing summary of
both, plus the code-quality bar every change here is expected to meet.

## Project snapshot

CommonLibSSE-NG is a C++23 library for SKSE plugin development targeting Skyrim SE, AE,
and VR from a single codebase. See `CLAUDE.md` for the multi-runtime architecture,
build presets, and conditional-compilation patterns (`ENABLE_SKYRIM_SE/AE/VR`,
`EXCLUSIVE_SKYRIM_FLAT/VR`, `SKYRIM_CROSS_VR`) in detail — read that before touching any
code gated by those macros; getting a three-way conditional wrong silently breaks one
runtime's vtable layout without a compile error.

Base branch for PRs: **`ng`** (not `main`/`master`). Never push directly to `ng`.

## Build & verify before claiming done

```bash
.\scripts\build-all-presets.cmd --clang   # fast iteration
.\scripts\build-all-presets.cmd            # full MSVC matrix
```

A change to any `RE::` header must build clean across **all** presets (se/ae/vr/flatrim/all)
before it's done — a runtime-exclusive virtual function or vtable-shift bug frequently
compiles fine in one preset and fails only in another.

For low-level ABI code (raw vtable synthesis, hand-written trampolines, `REL::Relocation`
sites anchored at instruction offsets rather than function entry): compiling and passing
the existing Catch2 regression test is **necessary but not sufficient**. Those tests exercise
typed C++ calls through your own compiler-generated vtable, which cannot catch a bug that
only shows up in the real engine's blind, fixed-slot dispatch. Verify such a change against
a real running Skyrim process before trusting it — a local, non-CI, manual test harness is the
established pattern for this (see `test_consumer_live/` and its README).

## Address-library ids: verify, never assume

- Never trust a `FUN_<addr>`/auto-analyzed name, an existing comment, or a decompiler's
  auto-inferred signature as ground truth — cross-check against the actual binary via Ghidra,
  and against the canonical offsets CSVs in
  [`skyrim_vr_address_library`](https://github.com/alandtse/skyrim_vr_address_library) for
  id-to-address mappings. A decompiler's default calling-convention analysis routinely drops
  real parameters and return values silently (shows up as `in_EDX`/`in_R8`-style unclaimed
  inputs, or a value written to `AL` right before `RET` with no `return` in the pseudo-C) —
  verify a signature by hand from the raw disassembly, don't take the decompiler's first pass
  at face value.
- A name, signature, or address applies across SE/AE/VR only if you've actually checked it
  there — AE in particular sometimes differs in register allocation, instruction order, or
  (across its own point releases, e.g. 1.6.1170 vs 1.7.99 vs 1.7.104) real vtable/slot-count
  differences. Confirm byte-for-byte identity (or the actual divergence) before reusing a
  patch, guard, or struct layout across runtimes.
- If a fix depends on a `skyrim_vr_address_library` id that has no VR (or AE) mapping yet,
  say so explicitly and land that address-library PR first — a `REL::ID()` call for an id
  missing from the currently-released address library aborts the game at load
  (`REL/IDDB.cpp`'s `report_id_lookup_failure`), not a soft failure.

## Code quality

- **Comments state a fact and its consequence, nothing more.** Default to none. Only write
  one when the *why* is genuinely non-obvious from the code alone — a hidden invariant, a
  workaround for a specific real bug, a case that looks safe to change but isn't. Target
  1–2 lines; the extraordinary-invariant exception (a fact whose loss would silently
  reintroduce a bug) tops out at 3–4 lines. Don't restate what a well-named identifier already
  says, don't narrate design rationale that belongs in the PR body, and don't describe code
  that used to be there.
- **Minimal churn.** Touch only what the change requires — no drive-by reformatting, no
  renaming adjacent identifiers, no unrelated cleanup folded into the same diff. Spotted
  something else worth fixing? Note it in the PR description or open a follow-up.
- **No placeholders, complete solutions.** Ship complete, working code — no `TODO`/stub
  bodies outside genuine scaffolding work, and real resource management (RAII / explicit
  cleanup), not just the happy path.
- **Descriptive naming**, one job per function, magic numbers named as constants.

## Constructive proactivity

- Flag performance, security, and cross-runtime-compatibility concerns proactively; suggest a
  more idiomatic pattern when one exists in this codebase already.
- Explain the reasoning behind a non-obvious or high-blast-radius change (e.g. a new
  three-way-conditional pattern) in the PR body, not just in the diff.
- Prefer surfacing a problem plus a concrete option over silently working around it — e.g. a
  missing address-library id is a blocker to say out loud, not something to paper over with a
  raw offset and move on.
- **Verify identifying facts; don't confabulate.** A relocation id, a runtime's real slot
  layout, whether a struct field exists — read it from the binary or the address library
  before stating it. "Unverified" beats a plausible-sounding guess.

## Security & input validation

- Validate external input this library actually parses (save data, config/INI-style values,
  anything from a game file) — malformed input must not crash or corrupt state.
- Bounds-check any buffer/array access derived from an external or game-controlled value,
  especially in the low-level ABI/relocation code described above.
- A GitHub Actions `run:` step must receive any workflow-dispatch-tainted value via `env:`
  indirection, never direct `${{ }}` template interpolation — a crafted value there injects
  shell commands.

## Error handling

- Log with enough context to diagnose (which runtime, which id/offset) at an appropriate
  severity — not silently swallowed, not spammed every frame.
- Degrade gracefully where the engine allows it (an unresolved id, a missing feature on a
  given runtime) rather than hard-crashing when a soft failure is possible; but see the
  address-library note above — a genuinely missing dependency should fail loudly at load,
  not corrupt state quietly.

## Testing & validation

- Build and run the relevant tests after any significant change before calling it done —
  don't rely on CI alone to catch a preset-specific break.
- **Never bypass commit verification** (`--no-verify` or otherwise skipping pre-commit/
  commit-msg hooks) unless the user explicitly directs it for a specific commit. If a hook
  fails, fix the underlying cause.

## Commits & PRs

- Conventional Commits (`type(scope): description`), title ≤ 50 chars, body wrapped at 72.
  See `CONTRIBUTING.md` for the full type table and this repo's squash-merge/semantic-release
  flow — get the PR title's type right, since squash-merge makes it the commit semantic-release
  reads for the version bump. **`ci` is its own type, not a scope** — a workflow/CI-config-only
  change is `ci: ...`, never `fix(ci): ...`/`feat(ci): ...`.
- PR/commit descriptions describe the change for a reviewer evaluating the current diff, not
  the session history that produced it (no "resolved via rebase," no git-mechanics narration).
- Treat `git commit`/`gh pr create` as a hard checkpoint: re-read this file's Commits & PRs and
  Collaboration sections immediately before either, not just once at the start of a task.

## Collaboration / git safety

- Never force-push or rewrite history on `ng` or any other shared/already-reviewed branch
  without explicit instruction. Confirm before pushing to any remote.
- Addressing a bot or human review comment: fix it, then resolve the review thread — don't
  reply with prose, and never post as the maintainer's own identity via a token that isn't
  yours.
- A review sweep must read each review's full body text, not just inline `reviewThreads` —
  "outside diff range" findings (CodeRabbit and similar) are often embedded in the review body
  with no inline thread, so a threads-only query can report "no comments" while real findings
  exist.
- Don't manually create release tags or hand-edit `vcpkg.json`/`CMakeLists.txt` version
  fields — semantic-release owns both on merge to `ng`.
- Know this repo's actual default PR branch (`ng`, not `main`) before opening or targeting a
  PR.
