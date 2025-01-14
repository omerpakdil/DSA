#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>

template<typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    // Private yardımcı fonksiyonlar
    void destroyTree(Node* node);
    Node* copyTree(Node* node);
    int getHeightHelper(Node* node) const;
    int getNodeCountHelper(Node* node) const;
    int getLeafCountHelper(Node* node) const;
    void preorderHelper(Node* node, std::vector<T>& result) const;
    void inorderHelper(Node* node, std::vector<T>& result) const;
    void postorderHelper(Node* node, std::vector<T>& result) const;
    
    // Traversal'lardan ağaç oluşturma yardımcı fonksiyonları
    Node* buildFromPreInorder(const std::vector<T>& preorder, const std::vector<T>& inorder,
                            int preStart, int preEnd, int inStart, int inEnd,
                            std::unordered_map<T, int>& inorderMap);
                            
    Node* buildFromPostInorder(const std::vector<T>& postorder, const std::vector<T>& inorder,
                             int postStart, int postEnd, int inStart, int inEnd,
                             std::unordered_map<T, int>& inorderMap);
    
public:
    // Temel fonksiyonlar
    BinaryTree() : root(nullptr) {}
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree& other);
    
    // Ağaç oluşturma ve düğüm ekleme
    void createFromPreorderInorder(const std::vector<T>& preorder, const std::vector<T>& inorder);
    void createFromPostorderInorder(const std::vector<T>& postorder, const std::vector<T>& inorder);
    void insert(const T& value);
    
    // Ağaç özellikleri
    bool isEmpty() const { return root == nullptr; }
    int getHeight() const { return getHeightHelper(root); }
    int getNodeCount() const { return getNodeCountHelper(root); }
    int getLeafCount() const { return getLeafCountHelper(root); }
    
    // Traversal fonksiyonları
    std::vector<T> preorderTraversal() const;
    std::vector<T> inorderTraversal() const;
    std::vector<T> postorderTraversal() const;
    std::vector<T> levelorderTraversal() const;
    
    // İteratif traversal fonksiyonları
    std::vector<T> iterativePreorder() const;
    std::vector<T> iterativeInorder() const;
    std::vector<T> iterativePostorder() const;
    
    // Kolay traversal metodları
    void easyTraversalMethod1() const;
    void easyTraversalMethod2() const;
    void easyTraversalMethod3() const;
};

// Template implementasyonları header'da olmalı
template<typename T>
void BinaryTree<T>::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copyTree(Node* node) {
    if (!node) return nullptr;
    
    Node* newNode = new Node(node->data);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) {
    root = copyTree(other.root);
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    destroyTree(root);
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other) {
    if (this != &other) {
        destroyTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

template<typename T>
int BinaryTree<T>::getHeightHelper(Node* node) const {
    if (!node) return -1;
    return 1 + std::max(getHeightHelper(node->left), getHeightHelper(node->right));
}

template<typename T>
int BinaryTree<T>::getNodeCountHelper(Node* node) const {
    if (!node) return 0;
    return 1 + getNodeCountHelper(node->left) + getNodeCountHelper(node->right);
}

template<typename T>
int BinaryTree<T>::getLeafCountHelper(Node* node) const {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return getLeafCountHelper(node->left) + getLeafCountHelper(node->right);
}

template<typename T>
void BinaryTree<T>::insert(const T& value) {
    Node* newNode = new Node(value);
    if (!root) {
        root = newNode;
        return;
    }
    
    std::queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        if (!current->left) {
            current->left = newNode;
            return;
        }
        if (!current->right) {
            current->right = newNode;
            return;
        }
        
        q.push(current->left);
        q.push(current->right);
    }
}

// Traversal implementasyonları header'da olmalı
template<typename T>
void BinaryTree<T>::preorderHelper(Node* node, std::vector<T>& result) const {
    if (node) {
        result.push_back(node->data);
        preorderHelper(node->left, result);
        preorderHelper(node->right, result);
    }
}

template<typename T>
void BinaryTree<T>::inorderHelper(Node* node, std::vector<T>& result) const {
    if (node) {
        inorderHelper(node->left, result);
        result.push_back(node->data);
        inorderHelper(node->right, result);
    }
}

template<typename T>
void BinaryTree<T>::postorderHelper(Node* node, std::vector<T>& result) const {
    if (node) {
        postorderHelper(node->left, result);
        postorderHelper(node->right, result);
        result.push_back(node->data);
    }
}

template<typename T>
std::vector<T> BinaryTree<T>::preorderTraversal() const {
    std::vector<T> result;
    preorderHelper(root, result);
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::inorderTraversal() const {
    std::vector<T> result;
    inorderHelper(root, result);
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::postorderTraversal() const {
    std::vector<T> result;
    postorderHelper(root, result);
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::levelorderTraversal() const {
    std::vector<T> result;
    if (!root) return result;
    
    std::queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        result.push_back(current->data);
        
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::iterativePreorder() const {
    std::vector<T> result;
    if (!root) return result;
    
    std::stack<Node*> s;
    s.push(root);
    
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        
        result.push_back(current->data);
        
        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
    
    return result;
}

template<typename T>
std::vector<T> BinaryTree<T>::iterativeInorder() const {
    std::vector<T> result;
    if (!root) return result;
    
    std::stack<Node*> s;
    Node* current = root;
    
    while (current || !s.empty()) {
        while (current) {
            s.push(current);
            current = current->left;
        }
        
        current = s.top();
        s.pop();
        
        result.push_back(current->data);
        current = current->right;
    }
    
    return result;
}

// Traversal'lardan ağaç oluşturma fonksiyonları
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::buildFromPreInorder(const std::vector<T>& preorder, const std::vector<T>& inorder,
                                                               int preStart, int preEnd, int inStart, int inEnd,
                                                               std::unordered_map<T, int>& inorderMap) {
    if (preStart > preEnd) return nullptr;
    
    Node* root = new Node(preorder[preStart]);
    int rootIndex = inorderMap[root->data];
    int leftSubtreeSize = rootIndex - inStart;
    
    root->left = buildFromPreInorder(preorder, inorder,
                                   preStart + 1, preStart + leftSubtreeSize,
                                   inStart, rootIndex - 1,
                                   inorderMap);
                                   
    root->right = buildFromPreInorder(preorder, inorder,
                                    preStart + leftSubtreeSize + 1, preEnd,
                                    rootIndex + 1, inEnd,
                                    inorderMap);
    
    return root;
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::buildFromPostInorder(const std::vector<T>& postorder, const std::vector<T>& inorder,
                                                                int postStart, int postEnd, int inStart, int inEnd,
                                                                std::unordered_map<T, int>& inorderMap) {
    if (postStart > postEnd) return nullptr;
    
    Node* root = new Node(postorder[postEnd]);
    int rootIndex = inorderMap[root->data];
    int leftSubtreeSize = rootIndex - inStart;
    
    root->left = buildFromPostInorder(postorder, inorder,
                                    postStart, postStart + leftSubtreeSize - 1,
                                    inStart, rootIndex - 1,
                                    inorderMap);
                                    
    root->right = buildFromPostInorder(postorder, inorder,
                                     postStart + leftSubtreeSize, postEnd - 1,
                                     rootIndex + 1, inEnd,
                                     inorderMap);
    
    return root;
}

// Traversal'lardan ağaç oluşturma public fonksiyonları
template<typename T>
void BinaryTree<T>::createFromPreorderInorder(const std::vector<T>& preorder, const std::vector<T>& inorder) {
    if (preorder.size() != inorder.size() || preorder.empty())
        return;
        
    std::unordered_map<T, int> inorderMap;
    for (int i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }
    
    destroyTree(root);
    root = buildFromPreInorder(preorder, inorder, 0, preorder.size() - 1,
                             0, inorder.size() - 1, inorderMap);
}

template<typename T>
void BinaryTree<T>::createFromPostorderInorder(const std::vector<T>& postorder, const std::vector<T>& inorder) {
    if (postorder.size() != inorder.size() || postorder.empty())
        return;
        
    std::unordered_map<T, int> inorderMap;
    for (int i = 0; i < inorder.size(); ++i) {
        inorderMap[inorder[i]] = i;
    }
    
    destroyTree(root);
    root = buildFromPostInorder(postorder, inorder, 0, postorder.size() - 1,
                              0, inorder.size() - 1, inorderMap);
}

// Kolay traversal metodları
template<typename T>
void BinaryTree<T>::easyTraversalMethod1() const {
    std::cout << "Method 1: Preorder Traversal\n";
    std::cout << "1. Visit root\n";
    std::cout << "2. Go to left subtree\n";
    std::cout << "3. Go to right subtree\n";
    
    std::cout << "Result: ";
    for (const T& val : preorderTraversal()) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

template<typename T>
void BinaryTree<T>::easyTraversalMethod2() const {
    std::cout << "Method 2: Inorder Traversal\n";
    std::cout << "1. Go to left subtree\n";
    std::cout << "2. Visit root\n";
    std::cout << "3. Go to right subtree\n";
    
    std::cout << "Result: ";
    for (const T& val : inorderTraversal()) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

template<typename T>
void BinaryTree<T>::easyTraversalMethod3() const {
    std::cout << "Method 3: Level Order Traversal\n";
    std::cout << "1. Use a queue\n";
    std::cout << "2. Push root to queue\n";
    std::cout << "3. While queue is not empty:\n";
    std::cout << "   - Pop front node and visit it\n";
    std::cout << "   - Push its left and right children\n";
    
    std::cout << "Result: ";
    for (const T& val : levelorderTraversal()) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

#endif // BINARY_TREE_HPP 