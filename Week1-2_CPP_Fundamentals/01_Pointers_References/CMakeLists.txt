cmake_minimum_required(VERSION 3.10)
project(PointerReferences)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pointer örnekleri için executable
add_executable(pointer_examples pointer_examples.cpp)

# Reference örnekleri için executable
add_executable(reference_examples reference_examples.cpp) 