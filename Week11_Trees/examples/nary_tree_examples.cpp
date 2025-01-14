#include <iostream>
#include "../include/NAryTree.hpp"

using namespace std;

int main() {
    NAryTree<int> tree;
    
    // N-li ağaç oluşturma
    tree.insert(-1, 1);  // root
    tree.insert(1, 2);   // 1'in çocuğu
    tree.insert(1, 3);   // 1'in çocuğu
    tree.insert(1, 4);   // 1'in çocuğu
    tree.insert(2, 5);   // 2'nin çocuğu
    tree.insert(2, 6);   // 2'nin çocuğu
    tree.insert(3, 7);   // 3'ün çocuğu
    
    cout << "N-li Ağaç Özellikleri:\n";
    cout << "Yükseklik: " << tree.getHeight() << endl;
    cout << "Düğüm sayısı: " << tree.getNodeCount() << endl;
    cout << "Yaprak sayısı: " << tree.getLeafCount() << endl;
    cout << "Maksimum derece: " << tree.getMaxDegree() << endl;
    
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
    
    cout << "Postorder traversal: ";
    for (int val : tree.postorderTraversal()) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
} 