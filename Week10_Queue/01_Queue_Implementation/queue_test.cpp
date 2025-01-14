#include "queue.h"
#include <cassert>
#include <iostream>
#include <string>

// Array Queue test fonksiyonları
void testArrayQueue() {
    std::cout << "Array Queue testleri başlıyor...\n";
    
    ArrayQueue<int> queue(5);
    assert(queue.isEmpty());
    assert(queue.getSize() == 0);
    
    // Temel operasyonlar testi
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    assert(queue.getSize() == 3);
    assert(queue.peek() == 1);
    
    // Dequeue operasyonları testi
    assert(queue.dequeue() == 1);
    assert(queue.dequeue() == 2);
    assert(queue.getSize() == 1);
    
    // Kapasite testi
    queue.enqueue(4);
    queue.enqueue(5);
    assert(queue.isFull());
    
    try {
        queue.enqueue(6); // Dolu queue'ya ekleme
        assert(false);
    } catch (const std::overflow_error&) {
        assert(true);
    }
    
    // Queue'yu boşaltma testi
    while (!queue.isEmpty()) {
        queue.dequeue();
    }
    assert(queue.isEmpty());
    
    try {
        queue.dequeue(); // Boş queue'dan çıkarma
        assert(false);
    } catch (const std::underflow_error&) {
        assert(true);
    }
}

// Circular Queue test fonksiyonları
void testCircularQueue() {
    std::cout << "Circular Queue testleri başlıyor...\n";
    
    CircularQueue<int> queue(3);
    
    // Temel operasyonlar testi
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    assert(queue.getSize() == 3);
    
    // Otomatik büyüme testi
    queue.enqueue(4); // Kapasite otomatik olarak artmalı
    assert(queue.getSize() == 4);
    assert(!queue.isFull());
    
    // FIFO davranışı testi
    assert(queue.dequeue() == 1);
    assert(queue.dequeue() == 2);
    assert(queue.peek() == 3);
    
    // Dairesel davranış testi
    queue.enqueue(5);
    queue.enqueue(6);
    assert(queue.dequeue() == 3);
    assert(queue.dequeue() == 4);
    assert(queue.dequeue() == 5);
}

// Linked Queue test fonksiyonları
void testLinkedQueue() {
    std::cout << "Linked Queue testleri başlıyor...\n";
    
    LinkedQueue<std::string> queue;
    
    // Temel operasyonlar testi
    queue.enqueue("first");
    queue.enqueue("second");
    queue.enqueue("third");
    assert(queue.getSize() == 3);
    
    // FIFO davranışı testi
    assert(queue.dequeue() == "first");
    assert(queue.peek() == "second");
    assert(queue.getSize() == 2);
    
    // Boşaltma ve hata kontrolü
    queue.dequeue();
    queue.dequeue();
    assert(queue.isEmpty());
    
    try {
        queue.dequeue();
        assert(false);
    } catch (const std::underflow_error&) {
        assert(true);
    }
}

// Deque test fonksiyonları
void testDeque() {
    std::cout << "Deque testleri başlıyor...\n";
    
    Deque<int> deque;
    
    // Ön tarafa ekleme testi
    deque.addFront(1);
    deque.addFront(2);
    assert(deque.peekFront() == 2);
    assert(deque.peekRear() == 1);
    
    // Arka tarafa ekleme testi
    deque.addRear(3);
    deque.addRear(4);
    assert(deque.peekRear() == 4);
    
    // Çift yönlü çıkarma testi
    assert(deque.removeFront() == 2);
    assert(deque.removeRear() == 4);
    assert(deque.getSize() == 2);
    
    // Boşaltma testi
    deque.removeFront();
    deque.removeRear();
    assert(deque.isEmpty());
    
    try {
        deque.removeFront();
        assert(false);
    } catch (const std::underflow_error&) {
        assert(true);
    }
}

// Priority Queue test fonksiyonları
void testPriorityQueue() {
    std::cout << "Priority Queue testleri başlıyor...\n";
    
    PriorityQueue<int> pq;
    
    // Öncelik sırası testi
    pq.enqueue(5);
    pq.enqueue(2);
    pq.enqueue(8);
    pq.enqueue(1);
    pq.enqueue(9);
    
    // En küçük elemanların sırayla çıkması
    assert(pq.dequeue() == 1);
    assert(pq.dequeue() == 2);
    assert(pq.dequeue() == 5);
    assert(pq.dequeue() == 8);
    assert(pq.dequeue() == 9);
    assert(pq.isEmpty());
}

// Stack Queue test fonksiyonları
void testStackQueue() {
    std::cout << "Stack Queue testleri başlıyor...\n";
    
    StackQueue<int> queue;
    
    // Temel operasyonlar testi
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    // FIFO davranışı testi
    assert(queue.dequeue() == 1);
    assert(queue.peek() == 2);
    assert(queue.getSize() == 2);
    
    // Yeni elemanlar ekleme
    queue.enqueue(4);
    queue.enqueue(5);
    
    // Sıralı çıkarma
    assert(queue.dequeue() == 2);
    assert(queue.dequeue() == 3);
    assert(queue.dequeue() == 4);
    assert(queue.dequeue() == 5);
    assert(queue.isEmpty());
}

int main() {
    try {
        testArrayQueue();
        testCircularQueue();
        testLinkedQueue();
        testDeque();
        testPriorityQueue();
        testStackQueue();
        
        std::cout << "Tüm testler başarıyla tamamlandı!\n";
    } catch (const std::exception& e) {
        std::cerr << "Test sırasında hata oluştu: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
