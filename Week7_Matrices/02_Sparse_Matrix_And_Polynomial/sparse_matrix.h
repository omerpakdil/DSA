#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <vector>
#include <map>
#include <iostream>
#include <stdexcept>

// Sparse matrix için element yapısı
template<typename T>
struct Element {
    size_t row;
    size_t col;
    T value;
    
    Element(size_t r, size_t c, const T& v) : row(r), col(c), value(v) {}
    
    // Sıralama için operator overloading
    bool operator<(const Element& other) const {
        if(row != other.row) return row < other.row;
        return col < other.col;
    }
};

// Sparse Matrix sınıfı - Coordinate List (COO) formatını kullanır
template<typename T>
class SparseMatrix {
private:
    size_t rows;
    size_t cols;
    std::vector<Element<T>> elements;  // Sıfır olmayan elementler

public:
    // Constructor - matrix boyutlarını alır
    SparseMatrix(size_t r, size_t c) : rows(r), cols(c) {}
    
    // Element ekleme - sıfır olmayan elementler için
    void addElement(size_t i, size_t j, const T& value) {
        if(i >= rows || j >= cols)
            throw std::out_of_range("Index out of range");
            
        if(value != T()) {  // Sıfır değilse ekle
            elements.emplace_back(i, j, value);
        }
    }
    
    // Element alma
    T get(size_t i, size_t j) const {
        if(i >= rows || j >= cols)
            throw std::out_of_range("Index out of range");
            
        for(const auto& elem : elements) {
            if(elem.row == i && elem.col == j)
                return elem.value;
        }
        return T();  // Element bulunamazsa default değer (sıfır) döndür
    }
    
    // Matrix boyutlarını getir
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    size_t getNonZeroCount() const { return elements.size(); }
    
    // Matrix'i ekrana yazdır
    void display() const {
        std::map<std::pair<size_t,size_t>, T> elemMap;
        for(const auto& elem : elements) {
            elemMap[{elem.row, elem.col}] = elem.value;
        }
        
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < cols; ++j) {
                auto it = elemMap.find({i,j});
                if(it != elemMap.end())
                    std::cout << it->second << " ";
                else
                    std::cout << "0 ";
            }
            std::cout << "\n";
        }
    }
};

// Polynomial sınıfı - sparse vector olarak temsil edilir
template<typename T>
class Polynomial {
private:
    std::map<size_t, T> coefficients;  // {üs: katsayı} şeklinde
    size_t degree;

public:
    // Constructor - default olarak sabit polinom (derece 0)
    Polynomial() : degree(0) {}
    
    // Terim ekleme
    void addTerm(size_t power, const T& coeff) {
        if(coeff != T()) {  // Sıfır katsayılı terim ekleme
            coefficients[power] = coeff;
            degree = std::max(degree, power);
        }
    }
    
    // Katsayı alma
    T getCoefficient(size_t power) const {
        auto it = coefficients.find(power);
        return (it != coefficients.end()) ? it->second : T();
    }
    
    // Polinom derecesini getir
    size_t getDegree() const { return degree; }
    
    // Polinomu ekrana yazdır
    void display() const {
        bool first = true;
        for(auto it = coefficients.rbegin(); it != coefficients.rend(); ++it) {
            if(!first && it->second > T()) std::cout << "+";
            first = false;
            
            if(it->second != T(1) || it->first == 0)
                std::cout << it->second;
                
            if(it->first > 0) {
                std::cout << "x";
                if(it->first > 1)
                    std::cout << "^" << it->first;
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
    
    // Polynomial toplama
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        
        // This polinomunun terimlerini ekle
        for(const auto& term : coefficients) {
            result.addTerm(term.first, term.second);
        }
        
        // Other polinomunun terimlerini ekle
        for(const auto& term : other.coefficients) {
            T sum = result.getCoefficient(term.first) + term.second;
            result.addTerm(term.first, sum);
        }
        
        return result;
    }
    
    // Polynomial çarpma
    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;
        
        // Her terimi diğer polinomun her terimi ile çarp
        for(const auto& term1 : coefficients) {
            for(const auto& term2 : other.coefficients) {
                size_t power = term1.first + term2.first;
                T coeff = term1.second * term2.second;
                T sum = result.getCoefficient(power) + coeff;
                result.addTerm(power, sum);
            }
        }
        
        return result;
    }
};

#endif // SPARSE_MATRIX_H 