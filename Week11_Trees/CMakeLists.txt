cmake_minimum_required(VERSION 3.15)
project(DSA_Trees CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add example executables
add_executable(binary_tree_examples examples/binary_tree_examples.cpp)
target_include_directories(binary_tree_examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(nary_tree_examples examples/nary_tree_examples.cpp)
target_include_directories(nary_tree_examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(array_tree_examples examples/array_tree_examples.cpp)
target_include_directories(array_tree_examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Enable testing
enable_testing()
find_package(GTest REQUIRED)

add_executable(tree_tests test/tree_tests.cpp)
target_include_directories(tree_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tree_tests GTest::GTest GTest::Main) 