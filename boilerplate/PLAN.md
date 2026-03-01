# Plan: Complete C++ Engineering Lifecycle

## TL;DR
Build a production-ready C++17 library with a comprehensive engineering workflow: CMake build, GTest unit tests, static analysis (clang-tidy), code formatting (clang-format), sanitizers (ASan/UBSan), documentation (Doxygen), and CI/CD (GitHub Actions).

Note: Do not use unit/checkmark symbols in documentation.

## Project Structure

```
boilerplate/
├── CMakeLists.txt              # Top-level build config (with options)
├── PLAN.md                     # This file
├── README.md                   # Project documentation
├── .gitignore                  # Ignore build/docs/coverage outputs
├── app/
│   ├── CMakeLists.txt
│   └── main.cpp                # Demo executable
├── include/
│   └── mylib/
│       └── mylib.hpp           # Public API header
├── src/
│   ├── CMakeLists.txt
│   └── mylib.cpp               # Library implementation
└── tests/
    ├── CMakeLists.txt
    └── test_mylib.cpp          # Unit tests (GTest)
```

## Core Pipeline

### 1. Build & Test (Default)
```bash
cd boilerplate
mkdir build && cd build
cmake ..
cmake --build .
ctest --output-on-failure
./app/mylib_app
```

### 2. Code Formatting
```bash
clang-format -i include/mylib/mylib.hpp src/mylib.cpp
```

### 3. Static Analysis (clang-tidy)
```bash
cmake -S . -B build-tidy -DENABLE_TIDY=ON
cmake --build build-tidy
```

### 4. Sanitizers (ASan + UBSan)
```bash
cmake -S . -B build-sanitize -DENABLE_SANITIZERS=ON
cmake --build build-sanitize
ctest --test-dir build-sanitize --output-on-failure
```

### 5. Documentation (Doxygen)
```bash
doxygen Doxyfile
```
Output: `docs/html/index.html` (if a Doxyfile exists in the repo root)

### 6. CI/CD (GitHub Actions)
- Optional: if a workflow exists in the repo root

## Key Features

### Build System
- **CMake 3.20+** - Modern, cross-platform builds
- **C++17 Standard** - Modern language features
- **GTest via ExternalProject** - Self-contained, reproducible testing
- **Compiler Warnings** - `-Wall -Wextra -Wpedantic` enabled by default
- **compile_commands.json** - Export for IDE tooling

### Code Quality
- **clang-format** - Automatic code formatting
- **clang-tidy** - Static analysis (opt-in via `-DENABLE_TIDY=ON`)
- **Sanitizers** - ASan + UBSan (opt-in via `-DENABLE_SANITIZERS=ON`)

### Documentation
- **Doxygen** - API documentation generation (optional if config exists)
- **README.md** - Usage and development guide
- **Inline comments** - Well-documented code

### Testing & Automation
- **Unit Tests** - GTest framework with 6+ tests
- **CTest** - Test runner integration
- **GitHub Actions** - Optional CI on Linux (Debug/Release)
- **Demo App** - Quick manual verification

### Project Structure
- **Clear Separation** - src/ (implementation), include/ (headers), tests/ (tests), app/ (demo)
- **.gitignore** - Ignores build artifacts, docs, and coverage outputs

## Implementation Steps

### Phase 1: Foundation (Core Library)
1. Create CMakeLists.txt with C++17, warnings, GTest ExternalProject
2. Implement `mylib::add()` and `mylib::multiply()` functions
3. Write unit tests with GTest
4. Create demo app (`mylib_app`)
5. Document with README.md

### Phase 2: Quality Tools (Optional Additions)
6. Add `.clang-format` for code formatting
7. Add `.clang-tidy` for static analysis with `-DENABLE_TIDY=ON` option
8. Add sanitizers with `-DENABLE_SANITIZERS=ON` option
9. Add `Doxyfile` for documentation generation

### Phase 3: Automation (Optional Additions)
10. Add GitHub Actions workflow (`.github/workflows/ci.yml`)
11. Configure for Linux Debug/Release builds and tests
12. Include clang-tidy checks in CI

### Phase 4: Future Enhancements (Optional)
- Code coverage with lcov/gcovr
- Install rules and CPack for distribution
- Benchmarking with google/benchmark
- More comprehensive static analysis
- Windows and macOS CI support

## Decision Rationale

**Build System**: CMake is the industry standard for C++ projects, enables cross-platform builds, and integrates well with modern tooling.

**Testing**: GTest via ExternalProject ensures reproducible builds across machines without system-wide dependencies.

**Tooling**: clang-format and clang-tidy are opt-in to keep default builds fast, but easily available for code review and CI enforcement.

**Sanitizers**: ASan and UBSan catch memory errors and undefined behavior; opt-in flag prevents performance impact on regular builds.

**Documentation**: Doxygen generates HTML docs from source code; kept local by default but easily automated in CI.

**CI/CD**: GitHub Actions provides free, integrated CI; future expansion to other platforms is straightforward.

## Verification Checklist

- [ ] Build successful: `cmake --build build`
- [ ] Tests passing: `ctest --test-dir build --output-on-failure`
- [ ] Demo app runs: `./app/mylib_app`
- [ ] Code formatted: `clang-format` runs without errors
- [ ] No tidy warnings: `-DENABLE_TIDY=ON` builds clean
- [ ] No sanitizer errors: `-DENABLE_SANITIZERS=ON` runs without issues
- [ ] Docs generated (if configured): `doxygen Doxyfile` creates HTML
- [ ] CI passes (if configured): GitHub Actions workflow green on push

## Next Steps

1. Verify each component works locally
2. Push to GitHub and confirm CI runs
3. Extend library functionality as needed
4. Add code coverage (lcov) for target metrics
