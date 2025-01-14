#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <stdexcept>
#include <string>

// Genel amaçlı bağlı liste sınıfı
template <typename T>
class LinkedList {
private:
    // Düğüm yapısı
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;    // Listenin başlangıç düğümü
    Node* tail;    // Listenin son düğümü
    size_t size;   // Liste uzunluğu

    // Özel yardımcı fonksiyonlar
    Node* getNode(size_t index) const {
        Node* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }

    // İki sıralı alt listeyi birleştir
    Node* merge(Node* left, Node* right) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        
        Node* result = nullptr;
        
        if (left->data <= right->data) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }
        
        return result;
    }

    // Merge sort için yardımcı fonksiyon
    Node* mergeSortHelper(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        // Ortayı bul
        Node* slow = head;
        Node* fast = head->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Listeyi böl
        Node* right = slow->next;
        slow->next = nullptr;
        
        // Rekürsif olarak sırala
        Node* left = mergeSortHelper(head);
        right = mergeSortHelper(right);
        
        // Birleştir
        return merge(left, right);
    }

public:
    // Yapıcı fonksiyon
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Kopyalama yapıcı fonksiyonu
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }

    // Yıkıcı fonksiyon
    ~LinkedList() {
        clear();
    }

    // Temel operasyonlar
    bool empty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    // Başa eleman ekleme
    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insert(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            pushFront(value);
            return;
        }
        if (index == size) {
            pushBack(value);
            return;
        }

        Node* current = head;
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }

    void popFront() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        if (empty()) {
            tail = nullptr;
        }
    }

    void popBack() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        if (size == 1) {
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
        size--;
    }

    void remove(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            popFront();
            return;
        }
        if (index == size - 1) {
            popBack();
            return;
        }
        
        Node* prev = getNode(index - 1);
        Node* temp = prev->next;
        prev->next = temp->next;
        delete temp;
        size--;
    }

    void removeValue(const T& value) {
        Node* current = head;
        Node* prev = nullptr;
        
        while (current != nullptr) {
            if (current->data == value) {
                if (prev == nullptr) {
                    head = current->next;
                    if (head == nullptr) {
                        tail = nullptr;
                    }
                } else {
                    prev->next = current->next;
                    if (current == tail) {
                        tail = prev;
                    }
                }
                delete current;
                size--;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // Erişim operasyonları
    T& front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }

    T& back() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return tail->data;
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return tail->data;
    }

    T& at(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return getNode(index)->data;
    }

    const T& at(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return getNode(index)->data;
    }

    // Arama operasyonları
    size_t find(const T& value) const {
        Node* current = head;
        size_t index = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return size;
    }

    bool contains(const T& value) const {
        return find(value) != size;
    }

    // İstatistiksel operasyonlar
    T getMax() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        T maxVal = head->data;
        Node* current = head->next;
        while (current != nullptr) {
            if (current->data > maxVal) {
                maxVal = current->data;
            }
            current = current->next;
        }
        return maxVal;
    }

    T getMin() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        T minVal = head->data;
        Node* current = head->next;
        while (current != nullptr) {
            if (current->data < minVal) {
                minVal = current->data;
            }
            current = current->next;
        }
        return minVal;
    }

    T getSum() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        T sum = T();
        Node* current = head;
        while (current != nullptr) {
            sum += current->data;
            current = current->next;
        }
        return sum;
    }

    double getAverage() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return static_cast<double>(getSum()) / size;
    }

    // Manipülasyon operasyonları
    void reverse() {
        if (size <= 1) return;

        Node* prev = nullptr;
        Node* current = head;
        tail = head;

        while (current != nullptr) {
            Node* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    void sort() {
        if (size <= 1) return;
        head = mergeSortHelper(head);
        // Update tail
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        tail = current;
    }

    void clear() {
        while (!empty()) {
            popFront();
        }
    }

    // Birleştirme operasyonları
    void concat(const LinkedList& other) {
        Node* current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }

    LinkedList merge(const LinkedList& other) const {
        LinkedList result;
        Node* p1 = head;
        Node* p2 = other.head;
        
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->data <= p2->data) {
                result.pushBack(p1->data);
                p1 = p1->next;
            } else {
                result.pushBack(p2->data);
                p2 = p2->next;
            }
        }
        
        while (p1 != nullptr) {
            result.pushBack(p1->data);
            p1 = p1->next;
        }
        
        while (p2 != nullptr) {
            result.pushBack(p2->data);
            p2 = p2->next;
        }
        
        return result;
    }

    // Özel operasyonlar
    Node* findMiddle() const {
        if (empty()) return nullptr;
        Node* slow = head;
        Node* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node* findIntersection(const LinkedList& other) const {
        if (empty() || other.empty()) return nullptr;
        Node* current1 = head;
        while (current1 != nullptr) {
            Node* current2 = other.head;
            while (current2 != nullptr) {
                if (current1 == current2) {
                    return current1;
                }
                current2 = current2->next;
            }
            current1 = current1->next;
        }
        return nullptr;
    }
};

#endif // LINKED_LIST_H
