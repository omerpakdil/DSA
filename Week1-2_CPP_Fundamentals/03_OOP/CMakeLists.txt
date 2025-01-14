# Minimum CMake sürümü gereksinimi
cmake_minimum_required(VERSION 3.10)

# Proje adı
project(OOP_Ornekleri)

# C++ standardı ayarı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Çalıştırılabilir dosya oluşturma
add_executable(oop_ornekleri oop_examples.cpp) 