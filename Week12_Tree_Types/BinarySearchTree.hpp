#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <queue>
#include <stack>

template<typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    // Private helper functions
    Node* insertRec(Node* node, const T& value);
    Node* deleteRec(Node* node, const T& value);
    Node* findMin(Node* node) const;
    Node* findMax(Node* node) const;
    bool searchRec(Node* node, const T& value) const;
    void inorderRec(Node* node) const;
    void destroyRec(Node* node);
    
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { destroyRec(root); }
    
    // Temel İşlemler (Basic Operations)
    void insert(const T& value) { root = insertRec(root, value); }
    void remove(const T& value) { root = deleteRec(root, value); }
    bool search(const T& value) const { return searchRec(root, value); }
    
    // İteratif Arama (Iterative Search)
    bool searchIterative(const T& value) const {
        Node* current = root;
        while (current) {
            if (value == current->data) return true;
            current = (value < current->data) ? current->left : current->right;
        }
        return false;
    }
    
    // Minimum/Maximum Bulma (Finding Min/Max)
    T findMinimum() const {
        if (!root) throw std::runtime_error("Tree is empty");
        return findMin(root)->data;
    }
    
    T findMaximum() const {
        if (!root) throw std::runtime_error("Tree is empty");
        return findMax(root)->data;
    }
    
    // Inorder Traversal (Sıralı Erişim)
    void inorderTraversal() const {
        inorderRec(root);
        std::cout << std::endl;
    }
    
    // İteratif Inorder Traversal
    void inorderIterative() const {
        if (!root) return;
        
        std::stack<Node*> stack;
        Node* current = root;
        
        while (current || !stack.empty()) {
            while (current) {
                stack.push(current);
                current = current->left;
            }
            
            current = stack.top();
            stack.pop();
            
            std::cout << current->data << " ";
            current = current->right;
        }
        std::cout << std::endl;
    }
};

// Private helper function implementations
template<typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::insertRec(Node* node, const T& value) {
    if (!node) return new Node(value);
    
    if (value < node->data)
        node->left = insertRec(node->left, value);
    else if (value > node->data)
        node->right = insertRec(node->right, value);
    
    return node;
}

template<typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::deleteRec(Node* node, const T& value) {
    if (!node) return nullptr;
    
    if (value < node->data)
        node->left = deleteRec(node->left, value);
    else if (value > node->data)
        node->right = deleteRec(node->right, value);
    else {
        // Yaprak düğüm veya tek çocuklu düğüm
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        
        // İki çocuklu düğüm
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = deleteRec(node->right, temp->data);
    }
    return node;
}

template<typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findMin(Node* node) const {
    while (node->left)
        node = node->left;
    return node;
}

template<typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findMax(Node* node) const {
    while (node->right)
        node = node->right;
    return node;
}

template<typename T>
bool BinarySearchTree<T>::searchRec(Node* node, const T& value) const {
    if (!node) return false;
    if (value == node->data) return true;
    
    return value < node->data ? 
           searchRec(node->left, value) : 
           searchRec(node->right, value);
}

template<typename T>
void BinarySearchTree<T>::inorderRec(Node* node) const {
    if (node) {
        inorderRec(node->left);
        std::cout << node->data << " ";
        inorderRec(node->right);
    }
}

template<typename T>
void BinarySearchTree<T>::destroyRec(Node* node) {
    if (node) {
        destroyRec(node->left);
        destroyRec(node->right);
        delete node;
    }
}

#endif // BINARY_SEARCH_TREE_HPP 