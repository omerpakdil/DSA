#ifndef ARRAY_BINARY_TREE_HPP
#define ARRAY_BINARY_TREE_HPP

#include <vector>
#include <cmath>
#include <stdexcept>

template<typename T>
class ArrayBinaryTree {
private:
    std::vector<T> tree;
    size_t size;
    T nullValue;  // Boş düğümleri temsil etmek için kullanılacak değer
    
    // İndeks hesaplama yardımcı fonksiyonları
    size_t leftChild(size_t index) const { return 2 * index + 1; }
    size_t rightChild(size_t index) const { return 2 * index + 2; }
    size_t parent(size_t index) const { return (index - 1) / 2; }
    
    bool isValidIndex(size_t index) const {
        return index < tree.size() && tree[index] != nullValue;
    }
    
    int getHeightHelper(size_t index) const {
        if (!isValidIndex(index)) return -1;
        
        int leftHeight = getHeightHelper(leftChild(index));
        int rightHeight = getHeightHelper(rightChild(index));
        
        return 1 + std::max(leftHeight, rightHeight);
    }
    
    int getLeafCountHelper(size_t index) const {
        if (!isValidIndex(index)) return 0;
        
        if (!isValidIndex(leftChild(index)) && !isValidIndex(rightChild(index)))
            return 1;
            
        return getLeafCountHelper(leftChild(index)) + 
               getLeafCountHelper(rightChild(index));
    }
    
public:
    ArrayBinaryTree() : size(0), nullValue(T()) {}
    ArrayBinaryTree(const T& nullVal) : size(0), nullValue(nullVal) {}
    
    void insert(const T& value) {
        if (tree.empty()) {
            tree.push_back(value);
            size++;
            return;
        }
        
        // Level-order insertion
        for (size_t i = 0; i < tree.size(); ++i) {
            if (tree[i] == nullValue) {
                tree[i] = value;
                size++;
                return;
            }
        }
        
        tree.push_back(value);
        size++;
    }
    
    T get(size_t index) const {
        if (index >= tree.size())
            throw std::out_of_range("Index out of bounds");
        return tree[index];
    }
    
    void set(size_t index, const T& value) {
        if (index >= tree.size())
            throw std::out_of_range("Index out of bounds");
        tree[index] = value;
    }
    
    // Temel özellikler
    bool isEmpty() const { return size == 0; }
    size_t getSize() const { return size; }
    int getHeight() const { return getHeightHelper(0); }
    int getLeafCount() const { return getLeafCountHelper(0); }
    
    // Traversal işlemleri
    std::vector<T> preorderTraversal() const {
        std::vector<T> result;
        preorderHelper(0, result);
        return result;
    }
    
    std::vector<T> inorderTraversal() const {
        std::vector<T> result;
        inorderHelper(0, result);
        return result;
    }
    
    std::vector<T> postorderTraversal() const {
        std::vector<T> result;
        postorderHelper(0, result);
        return result;
    }
    
    std::vector<T> levelOrderTraversal() const {
        std::vector<T> result;
        for (size_t i = 0; i < tree.size(); ++i) {
            if (tree[i] != nullValue) {
                result.push_back(tree[i]);
            }
        }
        return result;
    }
    
private:
    void preorderHelper(size_t index, std::vector<T>& result) const {
        if (!isValidIndex(index)) return;
        
        result.push_back(tree[index]);
        preorderHelper(leftChild(index), result);
        preorderHelper(rightChild(index), result);
    }
    
    void inorderHelper(size_t index, std::vector<T>& result) const {
        if (!isValidIndex(index)) return;
        
        inorderHelper(leftChild(index), result);
        result.push_back(tree[index]);
        inorderHelper(rightChild(index), result);
    }
    
    void postorderHelper(size_t index, std::vector<T>& result) const {
        if (!isValidIndex(index)) return;
        
        postorderHelper(leftChild(index), result);
        postorderHelper(rightChild(index), result);
        result.push_back(tree[index]);
    }
};

#endif // ARRAY_BINARY_TREE_HPP 