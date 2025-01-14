# Pointers and References in C++

## Theoretical Knowledge

### Pointers
Pointer'lar, bellekteki bir değerin adresini tutan değişkenlerdir. C++'da memory management ve data structures implementasyonunda kritik rol oynarlar.

#### Key Concepts
1. **Pointer Declaration**: 
   ```cpp
   int* ptr;     // int tipinde bir pointer
   double* dptr; // double tipinde bir pointer
   ```

2. **Address Operator (&)**:
   ```cpp
   int x = 10;
   int* ptr = &x; // x'in adresini ptr'ye atar
   ```

3. **Dereference Operator (*)**:
   ```cpp
   int value = *ptr; // ptr'nin gösterdiği değeri alır
   ```

### References
Reference'lar bir değişkenin alternatif ismidir. Pointer'lardan farklı olarak, initialize edildikten sonra başka bir değişkeni referans edemezler.

#### Key Concepts
1. **Reference Declaration**:
   ```cpp
   int x = 10;
   int& ref = x; // x'e referans
   ```

2. **Reference vs Pointer**:
   - Reference'lar NULL olamaz
   - Initialize edildikten sonra değiştirilemezler
   - Dereference operator'ü gerektirmezler

## Code Examples

### 1. Pointer Usage Examples
```cpp
// pointer_examples.cpp
#include <iostream>

void pointerBasics() {
    int number = 42;
    int* ptr = &number;
    
    std::cout << "Değer: " << number << std::endl;
    std::cout << "Adres: " << ptr << std::endl;
    std::cout << "Pointer üzerinden değer: " << *ptr << std::endl;
    
    // Değer değiştirme
    *ptr = 100;
    std::cout << "Yeni değer: " << number << std::endl;
}
```

### 2. Reference Usage Examples
```cpp
// reference_examples.cpp
void referenceBasics() {
    int number = 42;
    int& ref = number;
    
    std::cout << "Değer: " << number << std::endl;
    std::cout << "Referans üzerinden değer: " << ref << std::endl;
    
    // Değer değiştirme
    ref = 100;
    std::cout << "Yeni değer: " << number << std::endl;
}
```

## Common Interview Questions

1. **Pointer ve Reference arasındaki farklar nelerdir?**
   - Pointer'lar reassign edilebilir, reference'lar initialize edildikten sonra değiştirilemez
   - Pointer'lar NULL olabilir, reference'lar olamaz
   - Pointer'lar arithmetic işlemlere tabi tutulabilir, reference'lar tutulamaz

2. **Dangling Pointer nedir? Nasıl önlenir?**
   ```cpp
   int* createDanglingPointer() {
       int local = 10;
       return &local; // Dangling pointer! local değişken scope dışında yok olur
   }
   ```

3. **Smart Pointer'lar neden kullanılır?**
   - Memory leak'leri önlemek için
   - RAII (Resource Acquisition Is Initialization) prensibini uygulamak için
   - Exception safety sağlamak için

## Practice Exercises

1. **Pointer Arithmetic**
   - Array üzerinde pointer arithmetic kullanarak iteration
   - Array elemanlarını pointer kullanarak modification

2. **Reference Parameters**
   - Function'lara reference parameter passing
   - Pass by reference vs pass by value comparison

3. **Smart Pointer Implementation**
   - `std::unique_ptr` ve `std::shared_ptr` usage
   - Custom deleter implementation

| Feature | Pointer | Reference |
|---------|---------|-----------|
| Reassignment | ✅ Possible | ❌ Not possible |
| Null value | ✅ Can be null | ❌ Cannot be null |
| Initialization | Optional | Required |
| Syntax | Uses `*` and `->` | Like normal variable |
| Arithmetic | ✅ Possible | ❌ Not possible |

## Complexity Analysis

- **Space Complexity**: 
  - Pointer: Sistemin word size'ı kadar yer kaplar (32-bit sistemlerde 4 byte, 64-bit sistemlerde 8 byte)
  - Reference: Referans edilen type kadar yer kaplar

- **Time Complexity**:
  - Pointer dereferencing: O(1)
  - Reference access: O(1)

## LeetCode Problems

1. [146. LRU Cache](https://leetcode.com/problems/lru-cache/) - Pointer kullanımı
2. [138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/)
3. [2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/) - Linked List ve pointer manipulation

## Common Mistakes and Best Practices

1. **Memory Leaks**
   ```cpp
   int* ptr = new int(10);
   // ... ptr kullanımı ...
   // delete ptr; // Memory leak! delete unutulmuş
   ```

2. **Null Pointer Dereferencing**
   ```cpp
   int* ptr = nullptr;
   *ptr = 10; // Crash! Null pointer dereferencing
   ```

3. **Dangling References**
   ```cpp
   int& getDanglingReference() {
       int x = 10;
       return x; // Dangling reference! x scope dışında yok olur
   }
   ```

## Advanced Topics

1. **Pointer to Pointer (Double Pointer)**
   ```cpp
   int x = 10;
   int* ptr = &x;
   int** pptr = &ptr;
   ```

2. **Function Pointers**
   ```cpp
   void (*funcPtr)(int) = &someFunction;
   ```

3. **Reference to Pointer**
   ```cpp
   int* ptr = nullptr;
   int*& refPtr = ptr;
   ```

## Additional Resources

1. [C++ Reference - Pointers](https://en.cppreference.com/w/cpp/language/pointer)
2. [C++ Reference - References](https://en.cppreference.com/w/cpp/language/reference)
3. [Smart Pointers in Modern C++](https://www.modernescpp.com/index.php/memory-management-with-modern-c)
``` 