cmake_minimum_required(VERSION 3.10)
project(array_adt)

# C++ standart ayarı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Test executable oluşturma
add_executable(array_test array_test.cpp)

# Compiler flags
if(MSVC)
    target_compile_options(array_test PRIVATE /W4)
else()
    target_compile_options(array_test PRIVATE -Wall -Wextra -Wpedantic)
endif()
