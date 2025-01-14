cmake_minimum_required(VERSION 3.10)
project(queue_implementation)

# C++ standardını ayarla
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Test executable'ı oluştur
add_executable(queue_test queue_test.cpp)

# Compiler flag'leri ayarla
if(MSVC)
    target_compile_options(queue_test PRIVATE /W4)
else()
    target_compile_options(queue_test PRIVATE -Wall -Wextra -Wpedantic)
endif()
