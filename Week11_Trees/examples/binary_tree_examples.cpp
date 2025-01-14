#include <iostream>
#include "../include/BinaryTree.hpp"

using namespace std;

int main() {
    BinaryTree<int> tree;
    
    // Temel ağaç oluşturma
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    
    cout << "Binary Tree Özellikleri:\n";
    cout << "Yükseklik: " << tree.getHeight() << endl;
    cout << "Düğüm sayısı: " << tree.getNodeCount() << endl;
    cout << "Yaprak sayısı: " << tree.getLeafCount() << endl;
    
    cout << "\nKolay Traversal Metodları:\n";
    tree.easyTraversalMethod1();
    tree.easyTraversalMethod2();
    tree.easyTraversalMethod3();
    
    cout << "\nTraversal'lardan Ağaç Oluşturma:\n";
    vector<int> preorder = {1, 2, 4, 5, 3};
    vector<int> inorder = {4, 2, 5, 1, 3};
    
    BinaryTree<int> newTree;
    newTree.createFromPreorderInorder(preorder, inorder);
    
    cout << "Yeni ağaç preorder traversal: ";
    for (int val : newTree.preorderTraversal()) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
} 