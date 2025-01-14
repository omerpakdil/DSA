#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <vector>
#include <stdexcept>
#include <iostream>

// Temel Matrix sınıfı - tüm matrix türleri için base class
template<typename T>
class Matrix {
protected:
    std::vector<T> elements;
    size_t rows;
    size_t cols;

public:
    // Constructor - boyutları alır ve belleği ayırır
    Matrix(size_t r, size_t c) : elements(r * c), rows(r), cols(c) {}
    
    // Virtual destructor - polymorphic davranış için
    virtual ~Matrix() = default;
    
    // Temel matrix operasyonları
    virtual T get(size_t i, size_t j) const = 0;
    virtual void set(size_t i, size_t j, const T& value) = 0;
    
    // Utility fonksiyonları
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    bool isSquare() const { return rows == cols; }
    
    // Matrix'i ekrana yazdırma
    void display() const {
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < cols; ++j) {
                std::cout << get(i, j) << " ";
            }
            std::cout << "\n";
        }
    }
};

// Diagonal Matrix - sadece köşegen elemanları sıfırdan farklı
template<typename T>
class DiagonalMatrix : public Matrix<T> {
public:
    // n x n boyutunda diagonal matrix oluşturur
    DiagonalMatrix(size_t n) : Matrix<T>(n, n) {
        this->elements.resize(n);
    }
    
    T get(size_t i, size_t j) const override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        return (i == j) ? this->elements[i] : T();
    }
    
    void set(size_t i, size_t j, const T& value) override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        if(i == j)
            this->elements[i] = value;
        else if(value != T())
            throw std::invalid_argument("Non-diagonal elements must be zero");
    }
};

// Lower Triangular Matrix - alt üçgensel matrix
template<typename T>
class LowerTriangularMatrix : public Matrix<T> {
public:
    // n x n boyutunda alt üçgensel matrix oluşturur
    LowerTriangularMatrix(size_t n) : Matrix<T>(n, n) {
        this->elements.resize((n * (n + 1)) / 2);
    }
    
    T get(size_t i, size_t j) const override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        return (i >= j) ? this->elements[(i * (i + 1)) / 2 + j] : T();
    }
    
    void set(size_t i, size_t j, const T& value) override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        if(i >= j)
            this->elements[(i * (i + 1)) / 2 + j] = value;
        else if(value != T())
            throw std::invalid_argument("Upper triangular elements must be zero");
    }
};

// Upper Triangular Matrix - üst üçgensel matrix
template<typename T>
class UpperTriangularMatrix : public Matrix<T> {
public:
    // n x n boyutunda üst üçgensel matrix oluşturur
    UpperTriangularMatrix(size_t n) : Matrix<T>(n, n) {
        this->elements.resize((n * (n + 1)) / 2);
    }
    
    T get(size_t i, size_t j) const override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        return (i <= j) ? this->elements[(j * (j + 1)) / 2 + i] : T();
    }
    
    void set(size_t i, size_t j, const T& value) override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        if(i <= j)
            this->elements[(j * (j + 1)) / 2 + i] = value;
        else if(value != T())
            throw std::invalid_argument("Lower triangular elements must be zero");
    }
};

// Symmetric Matrix - simetrik matrix (aij = aji)
template<typename T>
class SymmetricMatrix : public Matrix<T> {
public:
    // n x n boyutunda simetrik matrix oluşturur
    SymmetricMatrix(size_t n) : Matrix<T>(n, n) {
        this->elements.resize((n * (n + 1)) / 2);
    }
    
    T get(size_t i, size_t j) const override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        return (i <= j) ? 
               this->elements[(j * (j + 1)) / 2 + i] : 
               this->elements[(i * (i + 1)) / 2 + j];
    }
    
    void set(size_t i, size_t j, const T& value) override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        if(i <= j)
            this->elements[(j * (j + 1)) / 2 + i] = value;
        else
            this->elements[(i * (i + 1)) / 2 + j] = value;
    }
};

// Tridiagonal Matrix - üç köşegenli matrix
template<typename T>
class TridiagonalMatrix : public Matrix<T> {
public:
    // n x n boyutunda üç köşegenli matrix oluşturur
    TridiagonalMatrix(size_t n) : Matrix<T>(n, n) {
        // n×n matrix için:
        // n eleman ana köşegen için
        // (n-1) eleman üst köşegen için
        // (n-1) eleman alt köşegen için
        this->elements.resize(3 * n - 2);
    }
    
    T get(size_t i, size_t j) const override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
            
        if(i == j) // Ana köşegen
            return this->elements[i];
        else if(i == j + 1) // Alt köşegen
            return this->elements[this->rows + j];
        else if(i + 1 == j) // Üst köşegen
            return this->elements[2 * this->rows - 1 + i];
        return T();
    }
    
    void set(size_t i, size_t j, const T& value) override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
            
        if(i == j) // Ana köşegen
            this->elements[i] = value;
        else if(i == j + 1) // Alt köşegen
            this->elements[this->rows + j] = value;
        else if(i + 1 == j) // Üst köşegen
            this->elements[2 * this->rows - 1 + i] = value;
        else if(value != T())
            throw std::invalid_argument("Only tridiagonal elements can be non-zero");
    }
};

// Toeplitz Matrix - her köşegende sabit değerli matrix
template<typename T>
class ToeplitzMatrix : public Matrix<T> {
public:
    // n x n boyutunda Toeplitz matrix oluşturur
    ToeplitzMatrix(size_t n) : Matrix<T>(n, n) {
        this->elements.resize(2 * n - 1);  // n eleman ilk satır + (n-1) eleman ilk sütun için
    }
    
    T get(size_t i, size_t j) const override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        int diff = j - i;
        if(diff >= 0)
            return this->elements[diff];  // Üst üçgen ve köşegen
        return this->elements[this->rows - 1 - diff];  // Alt üçgen
    }
    
    void set(size_t i, size_t j, const T& value) override {
        if(i >= this->rows || j >= this->cols)
            throw std::out_of_range("Index out of range");
        int diff = j - i;
        if(diff >= 0)
            this->elements[diff] = value;  // Üst üçgen ve köşegen
        else
            this->elements[this->rows - 1 - diff] = value;  // Alt üçgen
    }
};

#endif // MATRIX_OPS_H 