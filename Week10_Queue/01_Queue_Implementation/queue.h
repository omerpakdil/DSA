#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <string>
#include <vector>

// Array tabanlı basit Queue implementasyonu
template<typename T>
class ArrayQueue {
private:
    T* elements;
    int front;
    int rear;
    int capacity;
    int size;

public:
    // Kurucu fonksiyon
    ArrayQueue(int cap = 10) : capacity(cap), front(0), rear(-1), size(0) {
        elements = new T[capacity];
    }

    // Kopyalama kurucusu
    ArrayQueue(const ArrayQueue& other) : capacity(other.capacity), front(other.front),
                                        rear(other.rear), size(other.size) {
        elements = new T[capacity];
        for (int i = 0; i < capacity; i++) {
            elements[i] = other.elements[i];
        }
    }

    // Taşıma kurucusu
    ArrayQueue(ArrayQueue&& other) noexcept : elements(other.elements), capacity(other.capacity),
                                            front(other.front), rear(other.rear), size(other.size) {
        other.elements = nullptr;
        other.capacity = other.front = other.rear = other.size = 0;
    }

    // Yıkıcı fonksiyon
    ~ArrayQueue() {
        delete[] elements;
    }

    // Queue'ya eleman ekleme
    void enqueue(const T& value) {
        if (isFull()) {
            throw std::overflow_error("Queue is full");
        }
        rear = (rear + 1) % capacity;
        elements[rear] = value;
        size++;
    }

    // Queue'dan eleman çıkarma
    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        T value = elements[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }

    // Queue'nun başındaki elemanı görüntüleme
    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return elements[front];
    }

    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }
    int getSize() const { return size; }
};

// Dairesel Queue implementasyonu
template<typename T>
class CircularQueue {
private:
    T* elements;
    int front;
    int rear;
    int capacity;
    int size;

public:
    CircularQueue(int cap = 10) : capacity(cap), front(0), rear(0), size(0) {
        elements = new T[capacity];
    }

    ~CircularQueue() {
        delete[] elements;
    }

    void enqueue(const T& value) {
        if (isFull()) {
            // Dairesel queue dolu ise kapasiteyi iki katına çıkar
            int newCapacity = capacity * 2;
            T* newElements = new T[newCapacity];
            
            // Mevcut elemanları yeni array'e kopyala
            for (int i = 0; i < size; i++) {
                newElements[i] = elements[(front + i) % capacity];
            }
            
            delete[] elements;
            elements = newElements;
            front = 0;
            rear = size;
            capacity = newCapacity;
        }
        
        elements[rear] = value;
        rear = (rear + 1) % capacity;
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        T value = elements[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return elements[front];
    }

    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }
    int getSize() const { return size; }
};

// Linked List tabanlı Queue implementasyonu
template<typename T>
class LinkedQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int size;

public:
    LinkedQueue() : front(nullptr), rear(nullptr), size(0) {}

    ~LinkedQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        Node* temp = front;
        T value = front->data;
        front = front->next;
        delete temp;
        size--;
        if (size == 0) {
            rear = nullptr;
        }
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return front->data;
    }

    bool isEmpty() const { return size == 0; }
    int getSize() const { return size; }
};

// Double Ended Queue (Deque) implementasyonu
template<typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int size;

public:
    Deque() : front(nullptr), rear(nullptr), size(0) {}

    ~Deque() {
        while (!isEmpty()) {
            removeFront();
        }
    }

    // Ön tarafa eleman ekleme
    void addFront(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        size++;
    }

    // Arka tarafa eleman ekleme
    void addRear(const T& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // Ön taraftan eleman çıkarma
    T removeFront() {
        if (isEmpty()) {
            throw std::underflow_error("Deque is empty");
        }
        Node* temp = front;
        T value = front->data;
        front = front->next;
        if (front) {
            front->prev = nullptr;
        } else {
            rear = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    // Arka taraftan eleman çıkarma
    T removeRear() {
        if (isEmpty()) {
            throw std::underflow_error("Deque is empty");
        }
        Node* temp = rear;
        T value = rear->data;
        rear = rear->prev;
        if (rear) {
            rear->next = nullptr;
        } else {
            front = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    T peekFront() const {
        if (isEmpty()) {
            throw std::underflow_error("Deque is empty");
        }
        return front->data;
    }

    T peekRear() const {
        if (isEmpty()) {
            throw std::underflow_error("Deque is empty");
        }
        return rear->data;
    }

    bool isEmpty() const { return size == 0; }
    int getSize() const { return size; }
};

// Priority Queue implementasyonu (Min Heap kullanarak)
template<typename T>
class PriorityQueue {
private:
    std::vector<T> heap;

    // Heap yardımcı fonksiyonları
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] > heap[index]) {
                std::swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (true) {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }

            if (smallest == index) {
                break;
            }

            std::swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    void enqueue(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Priority Queue is empty");
        }
        T value = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!isEmpty()) {
            heapifyDown(0);
        }
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Priority Queue is empty");
        }
        return heap[0];
    }

    bool isEmpty() const { return heap.empty(); }
    int getSize() const { return heap.size(); }
};

// İki stack kullanarak Queue implementasyonu
template<typename T>
class StackQueue {
private:
    std::vector<T> stack1; // Enqueue için
    std::vector<T> stack2; // Dequeue için

    // Stack2'yi doldur
    void fillStack2() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push_back(stack1.back());
                stack1.pop_back();
            }
        }
    }

public:
    void enqueue(const T& value) {
        stack1.push_back(value);
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        fillStack2();
        T value = stack2.back();
        stack2.pop_back();
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        if (!stack2.empty()) {
            return stack2.back();
        }
        return stack1.front();
    }

    bool isEmpty() const { return stack1.empty() && stack2.empty(); }
    int getSize() const { return stack1.size() + stack2.size(); }
};

#endif // QUEUE_H
