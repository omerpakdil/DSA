#include "AVLTree.hpp"
#include <iostream>

void demonstrateBasicOperations() {
    std::cout << "\n=== Temel AVL Ağacı İşlemleri ===\n";
    
    AVLTree<int> avl;
    
    // Ekleme işlemleri ve otomatik dengeleme
    std::cout << "\nArdışık ekleme işlemleri yapılıyor...\n";
    std::cout << "Her düğümün yanındaki sayı denge faktörünü gösterir.\n\n";
    
    avl.insert(10);
    std::cout << "10 eklendi: ";
    avl.inorderTraversal();
    
    avl.insert(20);
    std::cout << "20 eklendi: ";
    avl.inorderTraversal();
    
    avl.insert(30);  // Sol rotasyon tetiklenecek
    std::cout << "30 eklendi (sol rotasyon): ";
    avl.inorderTraversal();
    
    avl.insert(40);
    std::cout << "40 eklendi: ";
    avl.inorderTraversal();
    
    avl.insert(50);  // Başka bir rotasyon tetiklenecek
    std::cout << "50 eklendi (sol rotasyon): ";
    avl.inorderTraversal();
    
    // Ağaç bilgileri
    std::cout << "\nAğaç yüksekliği: " << avl.getTreeHeight() << std::endl;
    std::cout << "Ağaç dengeli mi? " << (avl.isBalanced() ? "Evet" : "Hayır") << std::endl;
    std::cout << "Minimum değer: " << avl.findMinimum() << std::endl;
}

void demonstrateRotations() {
    std::cout << "\n=== AVL Rotasyon Örnekleri ===\n";
    
    // Sol-Sol Durumu (LL)
    std::cout << "\n1. Sol-Sol Durumu (Sağa Rotasyon):\n";
    AVLTree<int> ll;
    ll.insert(30);
    ll.insert(20);
    ll.insert(10);  // Sağa rotasyon tetiklenecek
    ll.inorderTraversal();
    
    // Sağ-Sağ Durumu (RR)
    std::cout << "\n2. Sağ-Sağ Durumu (Sola Rotasyon):\n";
    AVLTree<int> rr;
    rr.insert(10);
    rr.insert(20);
    rr.insert(30);  // Sola rotasyon tetiklenecek
    rr.inorderTraversal();
    
    // Sol-Sağ Durumu (LR)
    std::cout << "\n3. Sol-Sağ Durumu (Sol-Sağ Rotasyon):\n";
    AVLTree<int> lr;
    lr.insert(30);
    lr.insert(10);
    lr.insert(20);  // Sol-sağ rotasyon tetiklenecek
    lr.inorderTraversal();
    
    // Sağ-Sol Durumu (RL)
    std::cout << "\n4. Sağ-Sol Durumu (Sağ-Sol Rotasyon):\n";
    AVLTree<int> rl;
    rl.insert(10);
    rl.insert(30);
    rl.insert(20);  // Sağ-sol rotasyon tetiklenecek
    rl.inorderTraversal();
}

void demonstrateDeletion() {
    std::cout << "\n=== AVL Silme İşlemleri ===\n";
    
    AVLTree<int> avl;
    
    // Ağaç oluştur
    avl.insert(50);
    avl.insert(30);
    avl.insert(70);
    avl.insert(20);
    avl.insert(40);
    avl.insert(60);
    avl.insert(80);
    
    std::cout << "\nBaşlangıç ağacı: ";
    avl.inorderTraversal();
    
    // Yaprak düğüm silme
    std::cout << "\n20 siliniyor (yaprak düğüm): ";
    avl.remove(20);
    avl.inorderTraversal();
    
    // Tek çocuklu düğüm silme
    std::cout << "30 siliniyor (tek çocuk): ";
    avl.remove(30);
    avl.inorderTraversal();
    
    // İki çocuklu düğüm silme
    std::cout << "50 siliniyor (iki çocuk): ";
    avl.remove(50);
    avl.inorderTraversal();
    
    std::cout << "\nSon ağaç yüksekliği: " << avl.getTreeHeight() << std::endl;
    std::cout << "Ağaç hala dengeli mi? " << (avl.isBalanced() ? "Evet" : "Hayır") << std::endl;
}

int main() {
    std::cout << "AVL Ağacı Örnekleri\n";
    std::cout << "===================\n";
    
    demonstrateBasicOperations();
    demonstrateRotations();
    demonstrateDeletion();
    
    return 0;
} 