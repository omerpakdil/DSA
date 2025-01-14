#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include <string>

// Array tabanlı stack implementasyonu
template<typename T>
class ArrayStack {
private:
    T* elements;           // Stack elemanlarını tutan array
    int capacity;          // Maximum kapasite
    int topIndex;          // Top elemanın indeksi
    
public:
    // Constructor: Verilen kapasite ile stack'i initialize eder
    explicit ArrayStack(int cap) : capacity(cap), topIndex(-1) {
        if (cap <= 0) {
            throw std::invalid_argument("Kapasite pozitif olmalıdır");
        }
        elements = new T[capacity];
    }
    
    // Copy constructor
    ArrayStack(const ArrayStack& other) : capacity(other.capacity), topIndex(other.topIndex) {
        elements = new T[capacity];
        for (int i = 0; i <= topIndex; i++) {
            elements[i] = other.elements[i];
        }
    }
    
    // Move constructor
    ArrayStack(ArrayStack&& other) noexcept : elements(other.elements), 
                                            capacity(other.capacity), 
                                            topIndex(other.topIndex) {
        other.elements = nullptr;
        other.capacity = 0;
        other.topIndex = -1;
    }
    
    // Destructor
    ~ArrayStack() {
        delete[] elements;
    }
    
    // Stack'e eleman ekler
    void push(const T& value) {
        if (isFull()) {
            throw std::overflow_error("Stack dolu");
        }
        elements[++topIndex] = value;
    }
    
    // Stack'ten eleman çıkarır ve döndürür
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack boş");
        }
        return elements[topIndex--];
    }
    
    // Stack'in en üstündeki elemanı döndürür
    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack boş");
        }
        return elements[topIndex];
    }
    
    // Stack'in boş olup olmadığını kontrol eder
    bool isEmpty() const {
        return topIndex == -1;
    }
    
    // Stack'in dolu olup olmadığını kontrol eder
    bool isFull() const {
        return topIndex == capacity - 1;
    }
    
    // Stack'teki eleman sayısını döndürür
    int size() const {
        return topIndex + 1;
    }
    
    // Stack'i temizler
    void clear() {
        topIndex = -1;
    }
};

// Linked List tabanlı stack implementasyonu
template<typename T>
class LinkedStack {
private:
    // Node yapısı
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* top;    // Stack'in en üstündeki node
    int count;    // Eleman sayısı
    
public:
    // Constructor
    LinkedStack() : top(nullptr), count(0) {}
    
    // Copy constructor
    LinkedStack(const LinkedStack& other) : top(nullptr), count(0) {
        if (other.top) {
            // İlk node'u kopyala
            top = new Node(other.top->data);
            Node* current = top;
            Node* otherCurrent = other.top->next;
            count = 1;
            
            // Diğer node'ları kopyala
            while (otherCurrent) {
                current->next = new Node(otherCurrent->data);
                current = current->next;
                otherCurrent = otherCurrent->next;
                count++;
            }
        }
    }
    
    // Move constructor
    LinkedStack(LinkedStack&& other) noexcept : top(other.top), count(other.count) {
        other.top = nullptr;
        other.count = 0;
    }
    
    // Destructor
    ~LinkedStack() {
        clear();
    }
    
    // Stack'e eleman ekler
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        count++;
    }
    
    // Stack'ten eleman çıkarır ve döndürür
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack boş");
        }
        Node* temp = top;
        T value = temp->data;
        top = top->next;
        delete temp;
        count--;
        return value;
    }
    
    // Stack'in en üstündeki elemanı döndürür
    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack boş");
        }
        return top->data;
    }
    
    // Stack'in boş olup olmadığını kontrol eder
    bool isEmpty() const {
        return top == nullptr;
    }
    
    // Stack'teki eleman sayısını döndürür
    int size() const {
        return count;
    }
    
    // Stack'i temizler
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

#endif // STACK_H
