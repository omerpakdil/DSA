#include "sparse_matrix.h"
#include <cassert>
#include <iostream>

void testSparseMatrix() {
    std::cout << "\nSparse Matrix Testleri..." << std::endl;
    
    // 4x4 sparse matrix oluştur
    SparseMatrix<int> sm(4, 4);
    
    // Elementleri ekle
    sm.addElement(0, 0, 1);
    sm.addElement(0, 3, 2);
    sm.addElement(2, 1, 3);
    sm.addElement(3, 3, 4);
    
    // Elementleri doğrula
    assert(sm.get(0, 0) == 1);
    assert(sm.get(0, 3) == 2);
    assert(sm.get(2, 1) == 3);
    assert(sm.get(3, 3) == 4);
    
    // Sıfır elementleri doğrula
    assert(sm.get(0, 1) == 0);
    assert(sm.get(1, 1) == 0);
    
    // Non-zero element sayısını kontrol et
    assert(sm.getNonZeroCount() == 4);
    
    std::cout << "Sparse Matrix:" << std::endl;
    sm.display();
}

void testPolynomial() {
    std::cout << "\nPolynomial Testleri..." << std::endl;
    
    // İlk polinom: 3x^2 + 2x + 1
    Polynomial<int> p1;
    p1.addTerm(2, 3);  // 3x^2
    p1.addTerm(1, 2);  // 2x
    p1.addTerm(0, 1);  // 1
    
    // İkinci polinom: 2x^2 + x
    Polynomial<int> p2;
    p2.addTerm(2, 2);  // 2x^2
    p2.addTerm(1, 1);  // x
    
    // Katsayıları doğrula
    assert(p1.getCoefficient(2) == 3);
    assert(p1.getCoefficient(1) == 2);
    assert(p1.getCoefficient(0) == 1);
    
    assert(p2.getCoefficient(2) == 2);
    assert(p2.getCoefficient(1) == 1);
    assert(p2.getCoefficient(0) == 0);
    
    // Dereceleri kontrol et
    assert(p1.getDegree() == 2);
    assert(p2.getDegree() == 2);
    
    std::cout << "Polynomial 1: ";
    p1.display();
    std::cout << "Polynomial 2: ";
    p2.display();
    
    // Toplama işlemini test et
    Polynomial<int> sum = p1 + p2;
    std::cout << "Toplam: ";
    sum.display();
    
    assert(sum.getCoefficient(2) == 5);  // 3 + 2
    assert(sum.getCoefficient(1) == 3);  // 2 + 1
    assert(sum.getCoefficient(0) == 1);  // 1 + 0
    
    // Çarpma işlemini test et
    Polynomial<int> product = p1 * p2;
    std::cout << "Çarpım: ";
    product.display();
    
    assert(product.getCoefficient(4) == 6);   // 3 * 2
    assert(product.getCoefficient(3) == 7);   // 3 * 1 + 2 * 2
    assert(product.getCoefficient(2) == 4);   // 2 * 1 + 1 * 2
    assert(product.getCoefficient(1) == 1);   // 1 * 1
    assert(product.getCoefficient(0) == 0);
}

int main() {
    try {
        testSparseMatrix();
        testPolynomial();
        
        std::cout << "\nTüm testler başarıyla tamamlandı!" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
        return 1;
    }
} 