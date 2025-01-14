cmake_minimum_required(VERSION 3.10)
project(Week12_Trees)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable targets for BST
add_executable(bst_examples bst_examples.cpp)
add_executable(bst_tests bst_tests.cpp)

# Add executable targets for AVL Tree
add_executable(avl_examples avl_examples.cpp)
add_executable(avl_tests avl_tests.cpp)

# Add executable targets for Red-Black Tree
add_executable(rb_examples rb_examples.cpp)
add_executable(rb_tests rb_tests.cpp)


# Enable testing
enable_testing()
add_test(NAME BSTTests COMMAND bst_tests)
add_test(NAME AVLTests COMMAND avl_tests)
add_test(NAME RBTests COMMAND rb_tests)