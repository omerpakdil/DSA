#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;  // Dengeleme için yükseklik bilgisi
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    
    // Private yardımcı fonksiyonlar
    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }
    
    int getBalanceFactor(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    // Rotasyon işlemleri
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        return x;
    }
    
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        return y;
    }
    
    // Ekleme ve silme yardımcı fonksiyonları
    Node* insertRec(Node* node, const T& value) {
        // 1. Normal BST ekleme işlemi
        if (!node) return new Node(value);
        
        if (value < node->data)
            node->left = insertRec(node->left, value);
        else if (value > node->data)
            node->right = insertRec(node->right, value);
        else
            return node;  // Duplicate değerlere izin verilmiyor
            
        // 2. Yüksekliği güncelle
        updateHeight(node);
        
        // 3. Denge faktörünü kontrol et ve gerekirse dengele
        int balance = getBalanceFactor(node);
        
        // Sol Sol Durumu
        if (balance > 1 && value < node->left->data)
            return rotateRight(node);
            
        // Sağ Sağ Durumu
        if (balance < -1 && value > node->right->data)
            return rotateLeft(node);
            
        // Sol Sağ Durumu
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Sağ Sol Durumu
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    Node* findMin(Node* node) const {
        while (node && node->left)
            node = node->left;
        return node;
    }
    
    Node* deleteRec(Node* node, const T& value) {
        // 1. Normal BST silme işlemi
        if (!node) return nullptr;
        
        if (value < node->data)
            node->left = deleteRec(node->left, value);
        else if (value > node->data)
            node->right = deleteRec(node->right, value);
        else {
            // Tek çocuklu veya çocuksuz düğüm
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {  // Çocuksuz düğüm
                    temp = node;
                    node = nullptr;
                } else {  // Tek çocuklu düğüm
                    *node = *temp;
                }
                delete temp;
            } else {  // İki çocuklu düğüm
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteRec(node->right, temp->data);
            }
        }
        
        if (!node) return nullptr;
        
        // 2. Yüksekliği güncelle
        updateHeight(node);
        
        // 3. Denge faktörünü kontrol et ve gerekirse dengele
        int balance = getBalanceFactor(node);
        
        // Sol Sol Durumu
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rotateRight(node);
            
        // Sol Sağ Durumu
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        // Sağ Sağ Durumu
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return rotateLeft(node);
            
        // Sağ Sol Durumu
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    bool searchRec(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        
        return value < node->data ? 
               searchRec(node->left, value) : 
               searchRec(node->right, value);
    }
    
    void inorderRec(Node* node) const {
        if (node) {
            inorderRec(node->left);
            std::cout << node->data << "(" << getBalanceFactor(node) << ") ";
            inorderRec(node->right);
        }
    }
    
    void destroyRec(Node* node) {
        if (node) {
            destroyRec(node->left);
            destroyRec(node->right);
            delete node;
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroyRec(root); }
    
    // Temel işlemler
    void insert(const T& value) {
        root = insertRec(root, value);
    }
    
    void remove(const T& value) {
        root = deleteRec(root, value);
    }
    
    bool search(const T& value) const {
        return searchRec(root, value);
    }
    
    // Minimum/Maximum bulma
    T findMinimum() const {
        if (!root) throw std::runtime_error("Tree is empty");
        return findMin(root)->data;
    }
    
    // Traversal
    void inorderTraversal() const {
        inorderRec(root);
        std::cout << std::endl;
    }
    
    // Denge durumu kontrolü
    bool isBalanced() const {
        return std::abs(getBalanceFactor(root)) <= 1;
    }
    
    // Ağaç yüksekliği
    int getTreeHeight() const {
        return getHeight(root);
    }
};

#endif // AVL_TREE_HPP 