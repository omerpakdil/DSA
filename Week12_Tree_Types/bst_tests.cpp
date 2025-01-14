#include "BinarySearchTree.hpp"
#include <cassert>
#include <iostream>

void testBasicOperations() {
    BinarySearchTree<int> bst;
    
    // Test insertion
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Test search
    assert(bst.search(50) == true);
    assert(bst.search(30) == true);
    assert(bst.search(70) == true);
    assert(bst.search(90) == false);
    
    // Test iterative search
    assert(bst.searchIterative(20) == true);
    assert(bst.searchIterative(90) == false);
    
    // Test min/max
    assert(bst.findMinimum() == 20);
    assert(bst.findMaximum() == 80);
    
    // Test deletion
    bst.remove(20);  // Yaprak düğüm silme
    assert(bst.search(20) == false);
    
    bst.remove(30);  // Tek çocuklu düğüm silme
    assert(bst.search(30) == false);
    
    bst.remove(70);  // İki çocuklu düğüm silme
    assert(bst.search(70) == false);
    
    std::cout << "All basic operations tests passed!" << std::endl;
}

void testTraversals() {
    BinarySearchTree<int> bst;
    
    // Test empty tree
    bst.inorderTraversal();
    bst.inorderIterative();
    
    // Insert elements
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    
    std::cout << "Recursive inorder traversal: ";
    bst.inorderTraversal();
    
    std::cout << "Iterative inorder traversal: ";
    bst.inorderIterative();
    
    std::cout << "Traversal tests completed!" << std::endl;
}

void testEdgeCases() {
    BinarySearchTree<int> bst;
    
    // Test empty tree operations
    try {
        bst.findMinimum();
        assert(false);  // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }
    
    try {
        bst.findMaximum();
        assert(false);  // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }
    
    // Test single node
    bst.insert(50);
    assert(bst.findMinimum() == 50);
    assert(bst.findMaximum() == 50);
    
    // Test duplicate insertion
    bst.insert(50);  // Should not change the tree
    
    std::cout << "Edge cases tests passed!" << std::endl;
}

int main() {
    std::cout << "Starting BST tests..." << std::endl;
    
    testBasicOperations();
    testTraversals();
    testEdgeCases();
    
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
} 