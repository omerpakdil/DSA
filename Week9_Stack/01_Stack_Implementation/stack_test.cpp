#include "stack.h"
#include <cassert>
#include <iostream>
#include <string>

// Array Stack için test fonksiyonları
void testArrayStackBasicOperations() {
    // Test: Constructor ve temel operasyonlar
    ArrayStack<int> stack(5);
    assert(stack.isEmpty());
    assert(stack.size() == 0);
    
    // Test: Push operasyonu
    stack.push(1);
    stack.push(2);
    stack.push(3);
    assert(!stack.isEmpty());
    assert(stack.size() == 3);
    assert(stack.peek() == 3);
    
    // Test: Pop operasyonu
    assert(stack.pop() == 3);
    assert(stack.pop() == 2);
    assert(stack.size() == 1);
    
    // Test: Clear operasyonu
    stack.clear();
    assert(stack.isEmpty());
    assert(stack.size() == 0);
}

void testArrayStackErrorCases() {
    // Test: Stack overflow
    ArrayStack<int> stack(2);
    stack.push(1);
    stack.push(2);
    try {
        stack.push(3);
        assert(false); // Bu satıra ulaşılmamalı
    } catch (const std::overflow_error& e) {
        // Beklenen durum
    }
    
    // Test: Stack underflow
    ArrayStack<int> emptyStack(1);
    try {
        emptyStack.pop();
        assert(false); // Bu satıra ulaşılmamalı
    } catch (const std::underflow_error& e) {
        // Beklenen durum
    }
}

void testArrayStackWithStrings() {
    ArrayStack<std::string> stack(3);
    stack.push("Merhaba");
    stack.push("Dünya");
    assert(stack.peek() == "Dünya");
    assert(stack.pop() == "Dünya");
    assert(stack.pop() == "Merhaba");
    assert(stack.isEmpty());
}

// Linked Stack için test fonksiyonları
void testLinkedStackBasicOperations() {
    // Test: Constructor ve temel operasyonlar
    LinkedStack<int> stack;
    assert(stack.isEmpty());
    assert(stack.size() == 0);
    
    // Test: Push operasyonu
    stack.push(1);
    stack.push(2);
    stack.push(3);
    assert(!stack.isEmpty());
    assert(stack.size() == 3);
    assert(stack.peek() == 3);
    
    // Test: Pop operasyonu
    assert(stack.pop() == 3);
    assert(stack.pop() == 2);
    assert(stack.size() == 1);
    
    // Test: Clear operasyonu
    stack.clear();
    assert(stack.isEmpty());
    assert(stack.size() == 0);
}

void testLinkedStackErrorCases() {
    // Test: Stack underflow
    LinkedStack<int> emptyStack;
    try {
        emptyStack.pop();
        assert(false); // Bu satıra ulaşılmamalı
    } catch (const std::underflow_error& e) {
        // Beklenen durum
    }
    
    try {
        emptyStack.peek();
        assert(false); // Bu satıra ulaşılmamalı
    } catch (const std::underflow_error& e) {
        // Beklenen durum
    }
}

void testLinkedStackWithStrings() {
    LinkedStack<std::string> stack;
    stack.push("Merhaba");
    stack.push("Dünya");
    assert(stack.peek() == "Dünya");
    assert(stack.pop() == "Dünya");
    assert(stack.pop() == "Merhaba");
    assert(stack.isEmpty());
}

// Copy ve Move semantics testleri
void testStackCopyAndMove() {
    // Array Stack Copy Test
    ArrayStack<int> arrStack1(3);
    arrStack1.push(1);
    arrStack1.push(2);
    
    ArrayStack<int> arrStack2 = arrStack1; // Copy constructor
    assert(arrStack2.size() == arrStack1.size());
    assert(arrStack2.pop() == arrStack1.pop());
    
    // Linked Stack Copy Test
    LinkedStack<int> linkedStack1;
    linkedStack1.push(1);
    linkedStack1.push(2);
    
    LinkedStack<int> linkedStack2 = linkedStack1; // Copy constructor
    assert(linkedStack2.size() == linkedStack1.size());
    assert(linkedStack2.pop() == linkedStack1.pop());
    
    // Move semantics test
    ArrayStack<int> arrStack3 = std::move(arrStack1);
    LinkedStack<int> linkedStack3 = std::move(linkedStack1);
}

int main() {
    std::cout << "Stack testleri başlıyor...\n";
    
    // Array Stack testleri
    std::cout << "Array Stack testleri:\n";
    testArrayStackBasicOperations();
    testArrayStackErrorCases();
    testArrayStackWithStrings();
    
    // Linked Stack testleri
    std::cout << "Linked Stack testleri:\n";
    testLinkedStackBasicOperations();
    testLinkedStackErrorCases();
    testLinkedStackWithStrings();
    
    // Copy ve Move testleri
    std::cout << "Copy ve Move semantics testleri:\n";
    testStackCopyAndMove();
    
    std::cout << "Tüm testler başarıyla tamamlandı!\n";
    return 0;
}
