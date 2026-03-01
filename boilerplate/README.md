# mylib - C++17 Library with CMake & GTest

[![CI](https://github.com/mailmezorro/cppboilerplate/actions/workflows/ci.yml/badge.svg)](https://github.com/mailmezorro/cppboilerplate/actions/workflows/ci.yml)

A modern C++ library with unit tests using CMake and Google Test Framework.

## Structure

```
boilerplate/
├── CMakeLists.txt          # Top-level CMake configuration
├── app/                     # Demo executable
│   ├── CMakeLists.txt
│   └── main.cpp
├── include/mylib/          # Public headers
│   └── mylib.hpp
├── src/                    # Implementation
│   ├── CMakeLists.txt
│   └── mylib.cpp
├── tests/                  # Unit tests (GTest)
│   ├── CMakeLists.txt
│   └── test_mylib.cpp
├── .gitignore
└── README.md
```

## Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.20+
- Internet connection (GTest is downloaded from Google)

## Build & Test

```bash
# Navigate to boilerplate directory
cd boilerplate

# Create build directory
mkdir build && cd build

# Run CMake
cmake ..

# Build
cmake --build .

# Run tests
ctest --output-on-failure

# Build without tests
# cmake -S . -B build -DBUILD_TESTING=OFF

# Run demo app
./app/mylib_app
```

## Install

```bash
cmake -S . -B build
cmake --build build
cmake --install build
```

## Use in Another CMake Project

```cmake
find_package(mylib REQUIRED)
target_link_libraries(your_app PRIVATE mylib::mylib)
```

## Functions

The library currently provides the following functions:

- `mylib::add(int a, int b)` - Adds two numbers
- `mylib::multiply(int a, int b)` - Multiplies two numbers

## Features

- **CMake Build System** - Modern, cross-platform build
- **GTest Framework** - Modern unit tests with FetchContent
- **C++17** - Modern C++ standard
- **Compiler Warnings** - `-Wall -Wextra -Wpedantic` by default
- **Clear Structure** - src/include/tests separation
- **Static Analysis** - clang-tidy via `-DENABLE_TIDY=ON`
- **Sanitizers** - ASan + UBSan via `-DENABLE_SANITIZERS=ON`
- **Formatting** - Supported if a .clang-format exists
- **Docs** - Optional if a Doxyfile exists
- **CI** - GitHub Actions workflow for Linux (GCC/Clang, Build + CTest)

## Development

To extend the library:

1. Declare new function in `include/mylib/mylib.hpp`
2. Add implementation in `src/mylib.cpp`
3. Write tests in `tests/test_mylib.cpp`
4. Run `cmake --build . && ctest --output-on-failure`

## Formatting

```bash
clang-format -i \
	include/mylib/mylib.hpp \
	src/mylib.cpp \
	tests/test_mylib.cpp \
	app/main.cpp
```

## Static Analysis (clang-tidy)

```bash
cmake -S . -B build-tidy -DENABLE_TIDY=ON
cmake --build build-tidy
```

## Sanitizers (ASan + UBSan)

```bash
cmake -S . -B build-sanitize -DENABLE_SANITIZERS=ON
cmake --build build-sanitize
ctest --test-dir build-sanitize --output-on-failure
```

## Documentation (Doxygen)

```bash
doxygen Doxyfile
```

Output: `docs/html/index.html` (if a Doxyfile exists in the repo root)

## Optional (to be added later)

- Code coverage (gcov/lcov)
