#include <iostream>

// Temel reference kullanımı gösterimi
void basicReferenceUsage() {
    int number = 42;
    int& ref = number;
    
    std::cout << "Değer: " << number << std::endl;
    std::cout << "Reference üzerinden değer: " << ref << std::endl;
    
    // Value değiştirme işlemi
    ref = 100;
    std::cout << "Yeni değer: " << number << std::endl;
}

// Pass by value ve pass by reference karşılaştırması
void passByValue(int num) {
    num = 100;  // Orijinal değeri etkilemez
}

void passByReference(int& num) {
    num = 100;  // Orijinal değeri değiştirir
}

void parameterPassingExample() {
    int value1 = 42;
    int value2 = 42;
    
    std::cout << "\nParameter Passing:" << std::endl;
    std::cout << "Başlangıç değerleri: value1 = " << value1 << ", value2 = " << value2 << std::endl;
    
    passByValue(value1);
    passByReference(value2);
    
    std::cout << "Pass by value sonrası: " << value1 << std::endl;
    std::cout << "Pass by reference sonrası: " << value2 << std::endl;
}

// Const reference gösterimi
void constReferenceExample() {
    int number = 42;
    const int& constRef = number;
    
    std::cout << "\nConst Reference:" << std::endl;
    std::cout << "Değer: " << constRef << std::endl;
    // constRef = 100;  // Hata! Const reference değiştirilemez
    
    number = 100;  // Fakat orijinal değişken değiştirilebilir
    std::cout << "Yeni değer: " << constRef << std::endl;
}

// Array elements için reference kullanımı
void arrayReferenceExample() {
    int arr[] = {1, 2, 3, 4, 5};
    
    std::cout << "\nArray References:" << std::endl;
    for(int& element : arr) {  // Reference kullanarak array elemanlarını değiştir
        element *= 2;
    }
    
    // Değiştirilmiş array'i yazdır
    for(const int& element : arr) {  // Const reference ile oku
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Reference to pointer gösterimi
void referenceToPointerExample() {
    int value = 42;
    int* ptr = &value;
    int*& refPtr = ptr;  // Pointer'a reference
    
    std::cout << "\nReference to Pointer:" << std::endl;
    std::cout << "Pointer üzerinden değer: " << *ptr << std::endl;
    std::cout << "Reference üzerinden değer: " << *refPtr << std::endl;
    
    // Reference üzerinden pointer'ı değiştir
    int newValue = 100;
    refPtr = &newValue;
    
    std::cout << "Yeni değer: " << *ptr << std::endl;
}

int main() {
    std::cout << "=== Reference Examples ===" << std::endl;
    
    basicReferenceUsage();
    parameterPassingExample();
    constReferenceExample();
    arrayReferenceExample();
    referenceToPointerExample();
    
    return 0;
} 