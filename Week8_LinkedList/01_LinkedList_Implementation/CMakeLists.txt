cmake_minimum_required(VERSION 3.10)
project(linked_list)

# C++ standardını ayarla
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Test executable'ı oluştur
add_executable(linked_list_test linked_list_test.cpp)

# Compiler flag'leri ayarla
if(MSVC)
    target_compile_options(linked_list_test PRIVATE /W4)
else()
    target_compile_options(linked_list_test PRIVATE -Wall -Wextra -Wpedantic)
endif()
