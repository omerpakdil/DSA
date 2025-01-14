#include <iostream>
#include <memory>
#include <vector>
#include <chrono>

// Stack memory kullanım gösterimi
void stackExample() {
    std::cout << "\n=== Stack Memory Example ===" << std::endl;
    
    // Stack üzerinde değişken oluşturma
    int number = 42;
    double values[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    
    std::cout << "Stack değişkeni: " << number << std::endl;
    std::cout << "Stack array ilk eleman: " << values[0] << std::endl;
    
    // Scope sonunda otomatik temizlenir
}

// Heap memory kullanım gösterimi
void heapExample() {
    std::cout << "\n=== Heap Memory Example ===" << std::endl;
    
    // Heap üzerinde tek değer
    int* number = new int(42);
    std::cout << "Heap değişkeni: " << *number << std::endl;
    delete number;
    
    // Heap üzerinde array
    int* array = new int[5]{1, 2, 3, 4, 5};
    std::cout << "Heap array ilk eleman: " << array[0] << std::endl;
    delete[] array;
}

// Stack overflow gösterimi
void recursiveFunction(int n) {
    if (n == 0) return;
    
    // Her recursive çağrıda stack'te büyük bir array oluştur
    int array[1000];
    recursiveFunction(n - 1);
}

void stackOverflowExample() {
    std::cout << "\n=== Stack Overflow Example ===" << std::endl;
    try {
        recursiveFunction(1000);
    } catch (const std::exception& e) {
        std::cout << "Stack overflow yakalandı: " << e.what() << std::endl;
    }
}

// Memory leak gösterimi
void memoryLeakExample() {
    std::cout << "\n=== Memory Leak Example ===" << std::endl;
    
    // Memory leak - pointer silinmedi
    int* leakedPtr = new int(42);
    std::cout << "Oluşturulan memory leak boyutu: " << sizeof(int) << " bytes" << std::endl;
    // delete leakedPtr; // Düzeltmek için yorumu kaldırın
}

// Smart pointer kullanım gösterimi
void smartPointerExample() {
    std::cout << "\n=== Smart Pointer Example ===" << std::endl;
    
    // unique_ptr - tekil sahiplik
    std::unique_ptr<int> uniquePtr = std::make_unique<int>(42);
    std::cout << "unique_ptr değeri: " << *uniquePtr << std::endl;
    
    // shared_ptr - paylaşımlı sahiplik
    std::shared_ptr<int> sharedPtr1 = std::make_shared<int>(100);
    std::shared_ptr<int> sharedPtr2 = sharedPtr1;
    
    std::cout << "shared_ptr değeri: " << *sharedPtr1 << std::endl;
    std::cout << "shared_ptr referans sayısı: " << sharedPtr1.use_count() << std::endl;
}

// RAII gösterimi
class Resource {
    int* resource;
public:
    Resource() : resource(new int(42)) {
        std::cout << "Resource oluşturuldu" << std::endl;
    }
    
    ~Resource() {
        delete resource;
        std::cout << "Resource temizlendi" << std::endl;
    }
    
    void use() {
        std::cout << "Resource kullanılıyor" << std::endl;
    }
};

void raiiExample() {
    std::cout << "\n=== RAII Example ===" << std::endl;
    {
        Resource resource; // Constructor çağrılır
    } // Destructor otomatik çağrılır
}

// Stack ve Heap performans karşılaştırması
void performanceComparison() {
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    
    const int size = 1000000;
    auto start = std::chrono::high_resolution_clock::now();
    
    // Stack allocation
    {
        std::vector<int> stackArray(size);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Stack allocation süresi: " << duration.count() << " mikrosaniye" << std::endl;
    }
    
    // Heap allocation
    start = std::chrono::high_resolution_clock::now();
    {
        int* heapArray = new int[size];
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Heap allocation süresi: " << duration.count() << " mikrosaniye" << std::endl;
        delete[] heapArray;
    }
}

int main() {
    std::cout << "=== Memory Management Examples ===" << std::endl;
    
    stackExample();
    heapExample();
    stackOverflowExample();
    memoryLeakExample();
    smartPointerExample();
    raiiExample();
    performanceComparison();
    
    return 0;
} 