# Contributing to CommonLibSSE-NG

## Development Workflow

### Conventional Commits

This project uses [Conventional Commits](https://www.conventionalcommits.org/) for automated versioning and changelog generation.

**Commit Format:** `<type>(<scope>): <subject>`

See the [Conventional Commits specification](https://www.conventionalcommits.org/) for full details.

**Common types and their effect on versioning:**
- `feat:` → Minor version bump (1.2.0 → 1.3.0)
- `fix:`, `perf:`, `refactor:`, `style:` → Patch version bump (1.2.0 → 1.2.1)
- `BREAKING CHANGE:` or `!` → Major version bump (1.2.0 → 2.0.0)
- `docs:`, `test:`, `chore:`, `ci:`, `build:` → No version bump

**Examples:**
```bash
feat(actor): add new combat utility functions
fix(memory): resolve heap allocation bug in ScrapHeap
style: apply automated maintenance (formatting & file lists)
```

### Pre-commit Hooks

Install pre-commit hooks to automatically format code and generate CMake lists:

```bash
pip install pre-commit
pre-commit install
```

This will run before each commit:
1. **clang-format** - Format C/C++ code according to `.clang-format`
2. **cmake-generate** - Regenerate `cmake/sourcelist.cmake` from source files

### Automated Maintenance

The maintenance workflow runs automatically on:
- **Push** to `ng` branch
- **Pull Requests** targeting `ng` branch

It performs:
1. Code formatting with clang-format
2. CMake file list generation
3. Auto-commit with message: `style: apply automated maintenance (formatting & file lists)`

This ensures PRs can be squash-merged without requiring follow-up maintenance commits.

### Semantic Versioning

Version bumps are **fully automated** using [semantic-release](https://github.com/semantic-release/semantic-release) based on conventional commits. When changes are merged to `ng` branch:

1. Analyzes commits since last release
2. Determines next version number (based on commit types above)
3. Updates `vcpkg.json` and `CMakeLists.txt` versions
4. Generates `CHANGELOG.md`
5. Creates GitHub release
6. Commits changes with auto-generated message

**Note:** Semantic versioning is handled by the [cycjimmy/semantic-release-action](https://github.com/cycjimmy/semantic-release-action) GitHub Action. C++ dependencies are managed in `vcpkg.json`.

### Pull Request Workflow

1. **Create feature branch** from `ng`
2. **Make changes** and commit using conventional commit format
3. **Push branch** - maintenance workflow auto-formats on PR
4. **Review** - ensure CI passes and maintenance commits are applied
5. **Squash merge** - GitHub will preserve conventional commit format
6. **Automatic release** - semantic-release runs on merge to `ng`

### Local Development

**Format code manually:**
```bash
clang-format -i -style=file path/to/file.cpp
```

**Regenerate CMake lists:**
```bash
python scripts/cmake_generate.py
```

**Check pending release version:**

Review commits since last release using conventional commit types to determine the next version that would be released.

## Code Style

- Follow `.clang-format` configuration (enforced by pre-commit)
- Use C++23 features where appropriate
- Add header guards to all headers
- Keep lines readable (no strict column limit, but be reasonable)
- Use CRLF line endings (Windows-first project)

## Testing

- Add tests for new features in `tests/`
- Ensure all tests pass before submitting PR
- Consumer integration test validates dependency usage

## Questions?

Open an issue for questions about contributing or the development workflow.
