#include "RedBlackTree.hpp"
#include <iostream>

void demonstrateBasicOperations() {
    std::cout << "\n=== Temel Red-Black Tree İşlemleri ===\n";
    
    RedBlackTree<int> rbt;
    
    // Ekleme işlemleri
    std::cout << "\nArdışık ekleme işlemleri yapılıyor...\n";
    std::cout << "Her düğümün yanındaki (R) kırmızı, (B) siyah rengi gösterir.\n\n";
    
    rbt.insert(10);
    std::cout << "10 eklendi: ";
    rbt.inorderTraversal();
    
    rbt.insert(20);
    std::cout << "20 eklendi: ";
    rbt.inorderTraversal();
    
    rbt.insert(30);
    std::cout << "30 eklendi (renk değişimi ve rotasyon): ";
    rbt.inorderTraversal();
    
    rbt.insert(15);
    std::cout << "15 eklendi: ";
    rbt.inorderTraversal();
    
    rbt.insert(25);
    std::cout << "25 eklendi: ";
    rbt.inorderTraversal();
    
    // Arama işlemleri
    std::cout << "\nArama işlemleri:\n";
    std::cout << "20 ağaçta " << (rbt.search(20) ? "var" : "yok") << std::endl;
    std::cout << "40 ağaçta " << (rbt.search(40) ? "var" : "yok") << std::endl;
}

void demonstrateRecoloring() {
    std::cout << "\n=== Red-Black Tree Renk Değişimi ===\n";
    
    RedBlackTree<int> rbt;
    
    std::cout << "\nRenk değişimi gerektiren durumlar:\n";
    
    // Amca düğüm kırmızı olduğunda renk değişimi
    rbt.insert(20);  // Kök (siyah)
    std::cout << "20 eklendi (kök): ";
    rbt.inorderTraversal();
    
    rbt.insert(10);  // Sol çocuk (kırmızı)
    std::cout << "10 eklendi: ";
    rbt.inorderTraversal();
    
    rbt.insert(30);  // Sağ çocuk (kırmızı)
    std::cout << "30 eklendi (renk değişimi): ";
    rbt.inorderTraversal();
    
    rbt.insert(5);   // Yeni kırmızı düğüm
    std::cout << "5 eklendi: ";
    rbt.inorderTraversal();
}

void demonstrateRotations() {
    std::cout << "\n=== Red-Black Tree Rotasyonları ===\n";
    
    // Sol-Sol Durumu
    std::cout << "\n1. Sol-Sol Durumu:\n";
    RedBlackTree<int> ll;
    ll.insert(30);
    ll.insert(20);
    ll.insert(10);
    std::cout << "30-20-10 eklendi: ";
    ll.inorderTraversal();
    
    // Sağ-Sağ Durumu
    std::cout << "\n2. Sağ-Sağ Durumu:\n";
    RedBlackTree<int> rr;
    rr.insert(10);
    rr.insert(20);
    rr.insert(30);
    std::cout << "10-20-30 eklendi: ";
    rr.inorderTraversal();
    
    // Sol-Sağ Durumu
    std::cout << "\n3. Sol-Sağ Durumu:\n";
    RedBlackTree<int> lr;
    lr.insert(30);
    lr.insert(10);
    lr.insert(20);
    std::cout << "30-10-20 eklendi: ";
    lr.inorderTraversal();
    
    // Sağ-Sol Durumu
    std::cout << "\n4. Sağ-Sol Durumu:\n";
    RedBlackTree<int> rl;
    rl.insert(10);
    rl.insert(30);
    rl.insert(20);
    std::cout << "10-30-20 eklendi: ";
    rl.inorderTraversal();
}

void demonstrateDeletion() {
    std::cout << "\n=== Red-Black Tree Silme İşlemleri ===\n";
    
    RedBlackTree<int> rbt;
    
    // Ağaç oluştur
    rbt.insert(50);
    rbt.insert(30);
    rbt.insert(70);
    rbt.insert(20);
    rbt.insert(40);
    rbt.insert(60);
    rbt.insert(80);
    
    std::cout << "\nBaşlangıç ağacı: ";
    rbt.inorderTraversal();
    
    // Yaprak düğüm silme
    rbt.remove(20);
    std::cout << "20 silindi (yaprak): ";
    rbt.inorderTraversal();
    
    // Tek çocuklu düğüm silme
    rbt.remove(30);
    std::cout << "30 silindi (tek çocuk): ";
    rbt.inorderTraversal();
    
    // İki çocuklu düğüm silme
    rbt.remove(50);
    std::cout << "50 silindi (iki çocuk): ";
    rbt.inorderTraversal();
}

int main() {
    std::cout << "Red-Black Tree Örnekleri\n";
    std::cout << "========================\n";
    
    demonstrateBasicOperations();
    demonstrateRecoloring();
    demonstrateRotations();
    demonstrateDeletion();
    
    return 0;
} 