cmake_minimum_required(VERSION 3.20)
project(mylib VERSION 1.0.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

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

# Add source and app subdirectories
add_subdirectory(src)
add_subdirectory(app)

# Enable testing (optional)
include(CTest)
if(BUILD_TESTING)
    include(FetchContent)

    set(INSTALL_GTEST OFF CACHE BOOL "Disable GTest install targets" FORCE)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    find_package(Threads REQUIRED)

    add_subdirectory(tests)
endif()

# Install target export
install(EXPORT mylibTargets
    NAMESPACE mylib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mylib
)

set(MYLIB_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/mylib)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/mylibConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/mylibConfig.cmake
    INSTALL_DESTINATION ${MYLIB_INSTALL_CMAKEDIR}
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/mylibConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mylibConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/mylibConfigVersion.cmake
    DESTINATION ${MYLIB_INSTALL_CMAKEDIR}
)
