# Create static library
add_library(mylib STATIC mylib.cpp)

# Expose public header directory
target_include_directories(mylib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

# Set C++ standard for this target
target_compile_features(mylib PUBLIC cxx_std_17)

mylib_enable_sanitizers(mylib)
