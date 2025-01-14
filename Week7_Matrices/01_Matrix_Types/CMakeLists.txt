cmake_minimum_required(VERSION 3.10)
project(matrix_operations)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(matrix_test matrix_test.cpp)

# Set compiler flags
if(MSVC)
    target_compile_options(matrix_test PRIVATE /W4)
else()
    target_compile_options(matrix_test PRIVATE -Wall -Wextra -Wpedantic)
endif() 