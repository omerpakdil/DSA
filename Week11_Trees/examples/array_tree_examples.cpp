#include <iostream>
#include "../include/ArrayBinaryTree.hpp"

using namespace std;

int main() {
    ArrayBinaryTree<int> tree(-1);  // -1 null değer olarak kullanılacak
    
    // Dizi tabanlı ağaç oluşturma
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    
    cout << "Dizi Tabanlı İkili Ağaç Özellikleri:\n";
    cout << "Boyut: " << tree.getSize() << endl;
    cout << "Yükseklik: " << tree.getHeight() << endl;
    cout << "Yaprak sayısı: " << tree.getLeafCount() << endl;
    
    cout << "\nTraversal Sonuçları:\n";
    
    cout << "Level-order traversal: ";
    for (int val : tree.levelOrderTraversal()) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "Preorder traversal: ";
    for (int val : tree.preorderTraversal()) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "Inorder traversal: ";
    for (int val : tree.inorderTraversal()) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "Postorder traversal: ";
    for (int val : tree.postorderTraversal()) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
} 