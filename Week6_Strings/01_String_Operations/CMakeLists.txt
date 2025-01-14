cmake_minimum_required(VERSION 3.10)
project(string_operations)

# C++ standart ayarı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Kaynak dosyaları
add_executable(string_test 
    string_ops.cpp
    string_test.cpp
)

# Compiler flags
if(MSVC)
    target_compile_options(string_test PRIVATE /W4)
else()
    target_compile_options(string_test PRIVATE -Wall -Wextra -Wpedantic)
endif() 