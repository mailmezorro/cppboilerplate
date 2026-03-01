# Create test executable
add_executable(mylib_tests test_mylib.cpp)

# Link against GTest and Threads
target_link_libraries(mylib_tests
    mylib
    GTest::gtest_main
    Threads::Threads
)

mylib_enable_sanitizers(mylib_tests)

# Register test
add_test(NAME mylib_tests COMMAND mylib_tests)
