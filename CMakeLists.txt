cmake_minimum_required(VERSION 3.20)
project(NumericalLib VERSION 1.0.0 LANGUAGES CXX)

# Headers
include_directories(include utils)

# Gather all source files recursively
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
)

# Shared Library
add_library(linearalgebra SHARED ${SRC_FILES})

target_include_directories(linearalgebra PUBLIC include utils)

set_target_properties(linearalgebra PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Install rule
install(TARGETS linearalgebra
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

# Example executables
file(GLOB EXAMPLE_SOURCES examples/*.cpp)
foreach(example_file ${EXAMPLE_SOURCES})
    get_filename_component(example_name ${example_file} NAME_WE)
    add_executable(${example_name} ${example_file})
    target_link_libraries(${example_name} linearalgebra)
endforeach()

# Testing executables (optional)
file(GLOB TEST_SOURCES Testing/*.cpp)
add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests linearalgebra)