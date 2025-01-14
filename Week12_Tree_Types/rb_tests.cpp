#include "RedBlackTree.hpp"
#include <cassert>
#include <iostream>

void testBasicOperations() {
    RedBlackTree<int> rbt;
    
    // Test insertion
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);
    
    // Verify Red-Black properties
    assert(rbt.isRedBlackValid());
    
    // Test search
    assert(rbt.search(20) == true);
    assert(rbt.search(15) == true);
    assert(rbt.search(40) == false);
    
    std::cout << "Tree after insertions: ";
    rbt.inorderTraversal();
    
    std::cout << "Basic operations test passed!" << std::endl;
}

void testDeletion() {
    RedBlackTree<int> rbt;
    
    // Insert nodes
    rbt.insert(50);
    rbt.insert(30);
    rbt.insert(70);
    rbt.insert(20);
    rbt.insert(40);
    rbt.insert(60);
    rbt.insert(80);
    
    std::cout << "\nInitial tree: ";
    rbt.inorderTraversal();
    assert(rbt.isRedBlackValid());
    
    // Test leaf node deletion
    rbt.remove(20);
    assert(rbt.search(20) == false);
    assert(rbt.isRedBlackValid());
    std::cout << "After removing 20: ";
    rbt.inorderTraversal();
    
    // Test node with one child
    rbt.remove(30);
    assert(rbt.search(30) == false);
    assert(rbt.isRedBlackValid());
    std::cout << "After removing 30: ";
    rbt.inorderTraversal();
    
    // Test node with two children
    rbt.remove(50);
    assert(rbt.search(50) == false);
    assert(rbt.isRedBlackValid());
    std::cout << "After removing 50: ";
    rbt.inorderTraversal();
    
    std::cout << "Deletion tests passed!" << std::endl;
}

void testRedBlackProperties() {
    RedBlackTree<int> rbt;
    
    // Test property 1: Every node is either red or black (implicit in implementation)
    // Test property 2: Root is black (checked in isRedBlackValid)
    // Test property 3: All leaves (NIL) are black (implicit in implementation)
    // Test property 4: If a node is red, then both its children are black
    // Test property 5: Every path from root to leaves has same number of black nodes
    
    // Insert nodes to test properties
    rbt.insert(10);
    assert(rbt.isRedBlackValid());
    
    rbt.insert(20);
    assert(rbt.isRedBlackValid());
    
    rbt.insert(30);
    assert(rbt.isRedBlackValid());
    
    rbt.insert(40);
    assert(rbt.isRedBlackValid());
    
    rbt.insert(50);
    assert(rbt.isRedBlackValid());
    
    std::cout << "\nTree after testing properties: ";
    rbt.inorderTraversal();
    
    std::cout << "Red-Black properties test passed!" << std::endl;
}

void testEdgeCases() {
    RedBlackTree<int> rbt;
    
    // Test empty tree
    assert(rbt.search(10) == false);
    
    // Test single node
    rbt.insert(10);
    assert(rbt.isRedBlackValid());
    
    // Test duplicate insertion
    rbt.insert(10);
    assert(rbt.isRedBlackValid());
    
    // Test removing non-existent node
    rbt.remove(20);
    assert(rbt.isRedBlackValid());
    
    std::cout << "Edge cases test passed!" << std::endl;
}

int main() {
    std::cout << "Starting Red-Black Tree tests..." << std::endl;
    
    testBasicOperations();
    testDeletion();
    testRedBlackProperties();
    testEdgeCases();
    
    std::cout << "\nAll Red-Black Tree tests passed successfully!" << std::endl;
    return 0;
} 