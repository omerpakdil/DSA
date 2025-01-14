#ifndef NARY_TREE_HPP
#define NARY_TREE_HPP

#include <vector>
#include <queue>
#include <iostream>

template<typename T>
class NAryTree {
private:
    struct Node {
        T data;
        std::vector<Node*> children;
        
        Node(const T& value) : data(value) {}
    };
    
    Node* root;
    
    Node* findNode(Node* node, const T& value) {
        if (!node) return nullptr;
        if (node->data == value) return node;
        
        for (Node* child : node->children) {
            Node* found = findNode(child, value);
            if (found) return found;
        }
        return nullptr;
    }
    
    void destroyTree(Node* node) {
        if (!node) return;
        for (Node* child : node->children) {
            destroyTree(child);
        }
        delete node;
    }
    
    Node* copyTree(Node* node) {
        if (!node) return nullptr;
        
        Node* newNode = new Node(node->data);
        for (Node* child : node->children) {
            newNode->children.push_back(copyTree(child));
        }
        return newNode;
    }
    
    int getHeightHelper(Node* node) const {
        if (!node) return -1;
        
        int maxHeight = -1;
        for (Node* child : node->children) {
            maxHeight = std::max(maxHeight, getHeightHelper(child));
        }
        return 1 + maxHeight;
    }
    
    int getNodeCountHelper(Node* node) const {
        if (!node) return 0;
        
        int count = 1;
        for (Node* child : node->children) {
            count += getNodeCountHelper(child);
        }
        return count;
    }
    
    int getLeafCountHelper(Node* node) const {
        if (!node) return 0;
        if (node->children.empty()) return 1;
        
        int leafCount = 0;
        for (Node* child : node->children) {
            leafCount += getLeafCountHelper(child);
        }
        return leafCount;
    }
    
    int getDegreeHelper(Node* node) const {
        if (!node) return 0;
        
        int maxDegree = node->children.size();
        for (Node* child : node->children) {
            maxDegree = std::max(maxDegree, getDegreeHelper(child));
        }
        return maxDegree;
    }
    
public:
    NAryTree() : root(nullptr) {}
    
    ~NAryTree() {
        destroyTree(root);
    }
    
    NAryTree(const NAryTree& other) {
        root = copyTree(other.root);
    }
    
    NAryTree& operator=(const NAryTree& other) {
        if (this != &other) {
            destroyTree(root);
            root = copyTree(other.root);
        }
        return *this;
    }
    
    void insert(const T& parentValue, const T& value) {
        Node* newNode = new Node(value);
        
        if (!root) {
            root = newNode;
            return;
        }
        
        Node* parent = findNode(root, parentValue);
        if (parent) {
            parent->children.push_back(newNode);
        } else {
            delete newNode;
        }
    }
    
    bool isEmpty() const { return root == nullptr; }
    int getHeight() const { return getHeightHelper(root); }
    int getNodeCount() const { return getNodeCountHelper(root); }
    int getLeafCount() const { return getLeafCountHelper(root); }
    int getMaxDegree() const { return getDegreeHelper(root); }
    
    std::vector<T> levelOrderTraversal() const {
        std::vector<T> result;
        if (!root) return result;
        
        std::queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            
            result.push_back(current->data);
            
            for (Node* child : current->children) {
                q.push(child);
            }
        }
        
        return result;
    }
    
    std::vector<T> preorderTraversal() const {
        std::vector<T> result;
        preorderHelper(root, result);
        return result;
    }
    
    std::vector<T> postorderTraversal() const {
        std::vector<T> result;
        postorderHelper(root, result);
        return result;
    }
    
private:
    void preorderHelper(Node* node, std::vector<T>& result) const {
        if (!node) return;
        
        result.push_back(node->data);
        for (Node* child : node->children) {
            preorderHelper(child, result);
        }
    }
    
    void postorderHelper(Node* node, std::vector<T>& result) const {
        if (!node) return;
        
        for (Node* child : node->children) {
            postorderHelper(child, result);
        }
        result.push_back(node->data);
    }
};

#endif // NARY_TREE_HPP 