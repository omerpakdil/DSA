#include "matrix_ops.h"
#include <cassert>
#include <iostream>

void testDiagonalMatrix() {
    std::cout << "\nTesting Diagonal Matrix..." << std::endl;
    DiagonalMatrix<int> dm(3);
    
    // Köşegen elementleri ayarla
    dm.set(0, 0, 1);
    dm.set(1, 1, 2);
    dm.set(2, 2, 3);
    
    // Köşegen elementleri doğrula
    assert(dm.get(0, 0) == 1);
    assert(dm.get(1, 1) == 2);
    assert(dm.get(2, 2) == 3);
    
    // Köşegen dışı elementlerin sıfır olduğunu doğrula
    assert(dm.get(0, 1) == 0);
    assert(dm.get(1, 0) == 0);
    
    std::cout << "Diagonal Matrix:" << std::endl;
    dm.display();
}

void testLowerTriangularMatrix() {
    std::cout << "\nTesting Lower Triangular Matrix..." << std::endl;
    LowerTriangularMatrix<int> ltm(3);
    
    // Elementleri ayarla
    ltm.set(0, 0, 1);
    ltm.set(1, 0, 2);
    ltm.set(1, 1, 3);
    ltm.set(2, 0, 4);
    ltm.set(2, 1, 5);
    ltm.set(2, 2, 6);
    
    // Elementleri doğrula
    assert(ltm.get(0, 0) == 1);
    assert(ltm.get(1, 0) == 2);
    assert(ltm.get(1, 1) == 3);
    assert(ltm.get(2, 0) == 4);
    assert(ltm.get(2, 1) == 5);
    assert(ltm.get(2, 2) == 6);
    assert(ltm.get(0, 1) == 0);
    
    std::cout << "Lower Triangular Matrix:" << std::endl;
    ltm.display();
}

void testUpperTriangularMatrix() {
    std::cout << "\nTesting Upper Triangular Matrix..." << std::endl;
    UpperTriangularMatrix<int> utm(3);
    
    // Elementleri ayarla
    utm.set(0, 0, 1);
    utm.set(0, 1, 2);
    utm.set(0, 2, 3);
    utm.set(1, 1, 4);
    utm.set(1, 2, 5);
    utm.set(2, 2, 6);
    
    // Elementleri doğrula
    assert(utm.get(0, 0) == 1);
    assert(utm.get(0, 1) == 2);
    assert(utm.get(0, 2) == 3);
    assert(utm.get(1, 1) == 4);
    assert(utm.get(1, 2) == 5);
    assert(utm.get(2, 2) == 6);
    assert(utm.get(1, 0) == 0);
    
    std::cout << "Upper Triangular Matrix:" << std::endl;
    utm.display();
}

void testSymmetricMatrix() {
    std::cout << "\nTesting Symmetric Matrix..." << std::endl;
    SymmetricMatrix<int> sm(3);
    
    // Elementleri ayarla
    sm.set(0, 0, 1);
    sm.set(0, 1, 2);
    sm.set(0, 2, 3);
    sm.set(1, 1, 4);
    sm.set(1, 2, 5);
    sm.set(2, 2, 6);
    
    // Elementleri ve simetriyi doğrula
    assert(sm.get(0, 0) == 1);
    assert(sm.get(0, 1) == 2);
    assert(sm.get(1, 0) == 2);  // Simetrik
    assert(sm.get(0, 2) == 3);
    assert(sm.get(2, 0) == 3);  // Simetrik
    assert(sm.get(1, 1) == 4);
    assert(sm.get(1, 2) == 5);
    assert(sm.get(2, 1) == 5);  // Simetrik
    assert(sm.get(2, 2) == 6);
    
    std::cout << "Symmetric Matrix:" << std::endl;
    sm.display();
}

void testTridiagonalMatrix() {
    std::cout << "\nTesting Tridiagonal Matrix..." << std::endl;
    TridiagonalMatrix<int> tdm(4);
    
    // Köşegen elementleri ayarla
    tdm.set(0, 0, 1);  // Ana köşegen
    tdm.set(1, 1, 2);
    tdm.set(2, 2, 3);
    tdm.set(3, 3, 4);
    
    // Üst köşegen elementleri ayarla
    tdm.set(0, 1, 5);
    tdm.set(1, 2, 6);
    tdm.set(2, 3, 7);
    
    // Alt köşegen elementleri ayarla
    tdm.set(1, 0, 8);
    tdm.set(2, 1, 9);
    tdm.set(3, 2, 10);
    
    // Elementleri doğrula
    assert(tdm.get(0, 0) == 1);
    assert(tdm.get(0, 1) == 5);
    assert(tdm.get(1, 0) == 8);
    assert(tdm.get(1, 1) == 2);
    assert(tdm.get(2, 2) == 3);
    assert(tdm.get(0, 2) == 0);  // Sıfır olmalı
    
    std::cout << "Tridiagonal Matrix:" << std::endl;
    tdm.display();
}

void testToeplitzMatrix() {
    std::cout << "\nTesting Toeplitz Matrix..." << std::endl;
    ToeplitzMatrix<int> tm(3);
    
    // İlk satırı ayarla
    tm.set(0, 0, 1);  // Köşegen
    tm.set(0, 1, 2);
    tm.set(0, 2, 3);
    
    // İlk sütunu ayarla (köşegen hariç)
    tm.set(1, 0, 4);
    tm.set(2, 0, 5);
    
    // Toeplitz özelliğini doğrula
    assert(tm.get(0, 0) == 1);
    assert(tm.get(0, 1) == 2);
    assert(tm.get(1, 2) == 2);  // (0,1) ile aynı
    assert(tm.get(0, 2) == 3);
    assert(tm.get(1, 0) == 4);
    assert(tm.get(2, 1) == 4);  // (1,0) ile aynı
    assert(tm.get(2, 0) == 5);
    
    std::cout << "Toeplitz Matrix:" << std::endl;
    tm.display();
}

int main() {
    try {
        testDiagonalMatrix();
        testLowerTriangularMatrix();
        testUpperTriangularMatrix();
        testSymmetricMatrix();
        testTridiagonalMatrix();
        testToeplitzMatrix();
        
        std::cout << "\nTüm testler başarıyla tamamlandı!" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
        return 1;
    }
} 