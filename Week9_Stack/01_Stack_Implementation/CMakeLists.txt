cmake_minimum_required(VERSION 3.10)
project(stack_implementation)

# C++ standardını ayarla
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Test executable'ı oluştur
add_executable(stack_test stack_test.cpp)

# Compiler flag'leri ayarla
if(MSVC)
    target_compile_options(stack_test PRIVATE /W4)
else()
    target_compile_options(stack_test PRIVATE -Wall -Wextra -Wpedantic)
endif()
