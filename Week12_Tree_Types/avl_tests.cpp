#include "AVLTree.hpp"
#include <cassert>
#include <iostream>

void testBasicOperations() {
    AVLTree<int> avl;
    
    // Test insertion and balancing
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);  // Should trigger left rotation
    
    assert(avl.isBalanced());
    assert(avl.getTreeHeight() == 2);  // Root should be 20
    
    avl.insert(40);
    avl.insert(50);  // Should trigger another rotation
    
    assert(avl.isBalanced());
    
    // Test search
    assert(avl.search(30) == true);
    assert(avl.search(25) == false);
    
    // Test minimum
    assert(avl.findMinimum() == 10);
    
    std::cout << "Basic operations test passed!" << std::endl;
}

void testRotations() {
    AVLTree<int> avl;
    
    // Test Left-Left case
    std::cout << "\nTesting Left-Left rotation:" << std::endl;
    avl.insert(30);
    avl.insert(20);
    avl.insert(10);  // Should trigger right rotation
    avl.inorderTraversal();
    assert(avl.isBalanced());
    
    // Test Right-Right case
    AVLTree<int> avl2;
    std::cout << "\nTesting Right-Right rotation:" << std::endl;
    avl2.insert(10);
    avl2.insert(20);
    avl2.insert(30);  // Should trigger left rotation
    avl2.inorderTraversal();
    assert(avl2.isBalanced());
    
    // Test Left-Right case
    AVLTree<int> avl3;
    std::cout << "\nTesting Left-Right rotation:" << std::endl;
    avl3.insert(30);
    avl3.insert(10);
    avl3.insert(20);  // Should trigger left-right rotation
    avl3.inorderTraversal();
    assert(avl3.isBalanced());
    
    // Test Right-Left case
    AVLTree<int> avl4;
    std::cout << "\nTesting Right-Left rotation:" << std::endl;
    avl4.insert(10);
    avl4.insert(30);
    avl4.insert(20);  // Should trigger right-left rotation
    avl4.inorderTraversal();
    assert(avl4.isBalanced());
    
    std::cout << "Rotation tests passed!" << std::endl;
}

void testDeletion() {
    AVLTree<int> avl;
    
    // Insert some nodes
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    
    std::cout << "\nBefore deletion:" << std::endl;
    avl.inorderTraversal();
    
    // Test various deletion cases
    avl.remove(50);  // Leaf node
    assert(avl.search(50) == false);
    assert(avl.isBalanced());
    
    avl.remove(30);  // Node with two children
    assert(avl.search(30) == false);
    assert(avl.isBalanced());
    
    avl.remove(10);  // Node with one child
    assert(avl.search(10) == false);
    assert(avl.isBalanced());
    
    std::cout << "After deletions:" << std::endl;
    avl.inorderTraversal();
    
    std::cout << "Deletion tests passed!" << std::endl;
}

void testEdgeCases() {
    AVLTree<int> avl;
    
    // Test empty tree
    try {
        avl.findMinimum();
        assert(false);  // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }
    
    // Test single node
    avl.insert(10);
    assert(avl.getTreeHeight() == 1);
    assert(avl.isBalanced());
    
    // Test duplicate insertion
    avl.insert(10);  // Should not change the tree
    assert(avl.getTreeHeight() == 1);
    
    std::cout << "Edge cases tests passed!" << std::endl;
}

int main() {
    std::cout << "Starting AVL Tree tests..." << std::endl;
    
    testBasicOperations();
    testRotations();
    testDeletion();
    testEdgeCases();
    
    std::cout << "\nAll AVL Tree tests passed successfully!" << std::endl;
    return 0;
} 