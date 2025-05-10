cmake_minimum_required(VERSION 3.14)
project(Q++)

# Enable testing functionality
enable_testing()

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Add subdirectories for your source code and tests
add_subdirectory(tests) # This will point to the CMakeLists.txt in the tests directory

# Build the main executable
add_executable(run main.cpp)