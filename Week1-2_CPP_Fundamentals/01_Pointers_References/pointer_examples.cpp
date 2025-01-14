#include <iostream>

// Temel pointer kullanımı gösterimi
void basicPointerUsage() {
    int number = 42;
    int* ptr = &number;
    
    std::cout << "Değer: " << number << std::endl;
    std::cout << "Adres: " << ptr << std::endl;
    std::cout << "Pointer üzerinden değer: " << *ptr << std::endl;
    
    // Value değiştirme işlemi
    *ptr = 100;
    std::cout << "Yeni değer: " << number << std::endl;
}

// Pointer arithmetic gösterimi
void pointerArithmetic() {
    int arr[] = {1, 2, 3, 4, 5};
    int* ptr = arr;
    
    std::cout << "\nPointer Arithmetic:" << std::endl;
    for(int i = 0; i < 5; i++) {
        std::cout << "Element " << i << ": " << *ptr << std::endl;
        ptr++;  // Sonraki elemana geç
    }
}

// Dynamic memory allocation gösterimi
void dynamicMemoryAllocation() {
    // Single integer için memory allocation
    int* singlePtr = new int(42);
    std::cout << "\nTek değer: " << *singlePtr << std::endl;
    delete singlePtr;  // Memory serbest bırakma
    
    // Array için memory allocation
    int size = 5;
    int* arrayPtr = new int[size];
    
    // Array'i doldur
    for(int i = 0; i < size; i++) {
        arrayPtr[i] = i * 10;
    }
    
    // Array'i yazdır
    std::cout << "Dinamik array elemanları:" << std::endl;
    for(int i = 0; i < size; i++) {
        std::cout << arrayPtr[i] << " ";
    }
    std::cout << std::endl;
    
    delete[] arrayPtr;  // Array memory serbest bırakma
}

// Double pointer gösterimi
void doublePointerExample() {
    int value = 42;
    int* ptr = &value;
    int** pptr = &ptr;
    
    std::cout << "\nDouble Pointer:" << std::endl;
    std::cout << "Değer: " << value << std::endl;
    std::cout << "Ptr üzerinden değer: " << *ptr << std::endl;
    std::cout << "PPtr üzerinden değer: " << **pptr << std::endl;
}

// Function pointer gösterimi
void printNumber(int num) {
    std::cout << "Sayı: " << num << std::endl;
}

void functionPointerExample() {
    // Function pointer tanımlama
    void (*funcPtr)(int) = &printNumber;
    
    std::cout << "\nFunction Pointer:" << std::endl;
    // Function pointer çağrısı
    funcPtr(42);
}

int main() {
    std::cout << "=== Pointer Examples ===" << std::endl;
    
    basicPointerUsage();
    pointerArithmetic();
    dynamicMemoryAllocation();
    doublePointerExample();
    functionPointerExample();
    
    return 0;
} 