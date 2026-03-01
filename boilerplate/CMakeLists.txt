cmake_minimum_required(VERSION 3.20)
project(mylib)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler flags for warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

option(ENABLE_TIDY "Enable clang-tidy" OFF)
option(ENABLE_SANITIZERS "Enable sanitizers" OFF)

if(ENABLE_TIDY)
    find_program(CLANG_TIDY_EXE clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CLANG_TIDY_CONFIG "${PROJECT_SOURCE_DIR}/.clang-tidy")
        if(EXISTS "${CLANG_TIDY_CONFIG}")
            set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE} --config-file=${CLANG_TIDY_CONFIG})
        else()
            set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
            message(WARNING "clang-tidy config not found at ${CLANG_TIDY_CONFIG}; using default settings")
        endif()
    else()
        message(WARNING "clang-tidy not found; disabling ENABLE_TIDY")
    endif()
endif()

function(mylib_enable_sanitizers target)
    if(NOT ENABLE_SANITIZERS)
        return()
    endif()
    if(MSVC)
        message(WARNING "Sanitizers are not enabled for MSVC")
        return()
    endif()
    target_compile_options(${target} PRIVATE -O0 -g -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(${target} PRIVATE -fsanitize=address,undefined)
endfunction()

# Download and build Google Test
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

find_package(Threads REQUIRED)

# Add source, app, and test subdirectories
add_subdirectory(src)
add_subdirectory(app)

# Enable testing
enable_testing()
add_subdirectory(tests)
