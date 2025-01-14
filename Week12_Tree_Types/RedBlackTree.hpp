#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>
#include <stdexcept>

template<typename T>
class RedBlackTree {
private:
    enum Color { RED, BLACK };
    
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;
        Color color;
        
        Node(const T& value) : 
            data(value), 
            left(nullptr), 
            right(nullptr), 
            parent(nullptr), 
            color(RED) {}
    };
    
    Node* root;
    Node* NIL;  // Sentinel node (siyah yaprak düğüm)
    
    // Yardımcı fonksiyonlar
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        
        if (y->left != NIL)
            y->left->parent = x;
            
        y->parent = x->parent;
        
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
            
        y->left = x;
        x->parent = y;
    }
    
    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        
        if (x->right != NIL)
            x->right->parent = y;
            
        x->parent = y->parent;
        
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
            
        x->right = y;
        y->parent = x;
    }
    
    void insertFixup(Node* z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                
                if (y->color == RED) {
                    // Durum 1: Amca düğüm kırmızı
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // Durum 2: Amca siyah, z sağ çocuk
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Durum 3: Amca siyah, z sol çocuk
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                // Simetrik durumlar (sağ-sol değişimi)
                Node* y = z->parent->parent->left;
                
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }
    
    Node* minimum(Node* node) const {
        while (node->left != NIL)
            node = node->left;
        return node;
    }
    
    void deleteFixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                // Simetrik durumlar
                Node* w = x->parent->left;
                
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    
    void inorderRec(Node* node) const {
        if (node != NIL) {
            inorderRec(node->left);
            std::cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
            inorderRec(node->right);
        }
    }
    
    void destroyRec(Node* node) {
        if (node != NIL) {
            destroyRec(node->left);
            destroyRec(node->right);
            delete node;
        }
    }
    
public:
    RedBlackTree() {
        NIL = new Node(T());
        NIL->color = BLACK;
        root = NIL;
    }
    
    ~RedBlackTree() {
        destroyRec(root);
        delete NIL;
    }
    
    void insert(const T& value) {
        Node* z = new Node(value);
        z->left = NIL;
        z->right = NIL;
        
        Node* y = nullptr;
        Node* x = root;
        
        while (x != NIL) {
            y = x;
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        
        z->parent = y;
        
        if (y == nullptr)
            root = z;
        else if (z->data < y->data)
            y->left = z;
        else
            y->right = z;
            
        insertFixup(z);
    }
    
    void remove(const T& value) {
        Node* z = root;
        while (z != NIL) {
            if (value < z->data)
                z = z->left;
            else if (value > z->data)
                z = z->right;
            else
                break;
        }
        
        if (z == NIL)
            return;
            
        Node* y = z;
        Node* x;
        Color y_original_color = y->color;
        
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            
            if (y->parent == z)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        
        if (y_original_color == BLACK)
            deleteFixup(x);
            
        delete z;
    }
    
    bool search(const T& value) const {
        Node* current = root;
        while (current != NIL) {
            if (value == current->data)
                return true;
            current = (value < current->data) ? current->left : current->right;
        }
        return false;
    }
    
    void inorderTraversal() const {
        inorderRec(root);
        std::cout << std::endl;
    }
    
    bool isRedBlackValid() const {
        if (root->color != BLACK)
            return false;
            
        int black_height = 0;
        Node* node = root;
        while (node != NIL) {
            if (node->color == BLACK)
                black_height++;
            node = node->left;
        }
        
        return isRedBlackValidRec(root, black_height, 0);
    }
    
private:
    bool isRedBlackValidRec(Node* node, int black_height, int current_black_height) const {
        if (node == NIL)
            return current_black_height == black_height;
            
        if (node->color == BLACK)
            current_black_height++;
            
        if (node->color == RED && node->parent && node->parent->color == RED)
            return false;
            
        return isRedBlackValidRec(node->left, black_height, current_black_height) &&
               isRedBlackValidRec(node->right, black_height, current_black_height);
    }
};

#endif // RED_BLACK_TREE_HPP 