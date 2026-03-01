add_executable(mylib_app main.cpp)

# Link against the library
target_link_libraries(mylib_app mylib)

# Use C++17
target_compile_features(mylib_app PUBLIC cxx_std_17)

mylib_enable_sanitizers(mylib_app)
