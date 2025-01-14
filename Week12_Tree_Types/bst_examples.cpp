#include "BinarySearchTree.hpp"
#include <iostream>

void demonstrateBasicOperations() {
    std::cout << "\n=== Temel BST İşlemleri ===\n";
    
    BinarySearchTree<int> bst;
    
    // Ekleme işlemleri
    std::cout << "\nEkleme işlemleri yapılıyor...\n";
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Ağacın içeriğini göster
    std::cout << "Ağacın sıralı içeriği: ";
    bst.inorderTraversal();
    
    // Arama işlemleri
    std::cout << "\nArama işlemleri:\n";
    std::cout << "50 ağaçta " << (bst.search(50) ? "var" : "yok") << std::endl;
    std::cout << "90 ağaçta " << (bst.search(90) ? "var" : "yok") << std::endl;
    
    // Minimum ve maksimum değerler
    std::cout << "\nMinimum değer: " << bst.findMinimum() << std::endl;
    std::cout << "Maksimum değer: " << bst.findMaximum() << std::endl;
    
    // Silme işlemleri
    std::cout << "\nSilme işlemleri yapılıyor...\n";
    std::cout << "20 siliniyor (yaprak düğüm)\n";
    bst.remove(20);
    std::cout << "Yeni sıralı içerik: ";
    bst.inorderTraversal();
    
    std::cout << "70 siliniyor (iki çocuklu düğüm)\n";
    bst.remove(70);
    std::cout << "Yeni sıralı içerik: ";
    bst.inorderTraversal();
}

void demonstrateTraversalMethods() {
    std::cout << "\n=== BST Dolaşma Yöntemleri ===\n";
    
    BinarySearchTree<int> bst;
    
    // Ağaç oluştur
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Farklı dolaşma yöntemlerini göster
    std::cout << "\nÖzyinelemeli inorder dolaşma: ";
    bst.inorderTraversal();
    
    std::cout << "İteratif inorder dolaşma: ";
    bst.inorderIterative();
}

void demonstrateSearchMethods() {
    std::cout << "\n=== BST Arama Yöntemleri ===\n";
    
    BinarySearchTree<int> bst;
    
    // Ağaç oluştur
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    
    // Özyinelemeli ve iteratif aramaları karşılaştır
    int searchValue = 40;
    std::cout << "\n" << searchValue << " değeri için arama:\n";
    std::cout << "Özyinelemeli arama: " << (bst.search(searchValue) ? "bulundu" : "bulunamadı") << std::endl;
    std::cout << "İteratif arama: " << (bst.searchIterative(searchValue) ? "bulundu" : "bulunamadı") << std::endl;
    
    searchValue = 90;
    std::cout << "\n" << searchValue << " değeri için arama:\n";
    std::cout << "Özyinelemeli arama: " << (bst.search(searchValue) ? "bulundu" : "bulunamadı") << std::endl;
    std::cout << "İteratif arama: " << (bst.searchIterative(searchValue) ? "bulundu" : "bulunamadı") << std::endl;
}

int main() {
    std::cout << "Binary Search Tree Örnekleri\n";
    std::cout << "============================\n";
    
    demonstrateBasicOperations();
    demonstrateTraversalMethods();
    demonstrateSearchMethods();
    
    return 0;
} 