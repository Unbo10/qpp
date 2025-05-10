add_executable(tests division.cpp) # Include tests.cpp if it contains more tests
target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main Numbers utils)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) # Include current directory for your test-specific headers
target_include_directories(tests PRIVATE ${googletest_SOURCE_DIR}/googletest/include) # Explicitly include gtest headers

# Register the test suite so ctest can run it
include(GoogleTest)
gtest_discover_tests(tests)