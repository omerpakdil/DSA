cmake_minimum_required(VERSION 3.10)
project(sparse_matrix_polynomial)

# C++ standardını ayarla
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executable oluştur
add_executable(sparse_test sparse_test.cpp)

# Compiler flag'leri ayarla
if(MSVC)
    target_compile_options(sparse_test PRIVATE /W4)
else()
    target_compile_options(sparse_test PRIVATE -Wall -Wextra -Wpedantic)
endif() 