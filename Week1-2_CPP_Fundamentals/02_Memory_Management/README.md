# Memory Management in C++

## Theoretical Knowledge

### Stack Memory
Stack, otomatik memory management'in yapıldığı, LIFO (Last In First Out) prensibiyle çalışan memory bölgesidir.

#### Properties:
- Hızlı access ve management
- Sınırlı size (genellikle birkaç MB)
- Automatic memory management
- Scope-based lifetime
- Value type'lar ve local variable'lar burada saklanır

### Heap Memory
Heap, dynamic memory management'in yapıldığı, manuel olarak yönetilen memory bölgesidir.

#### Properties:
- Daha yavaş access
- Büyük size (RAM limitleri dahilinde)
- Manual memory management (new/delete)
- Programmer-controlled lifetime
- Dynamic olarak oluşturulan object'ler burada saklanır

## Code Examples

### 1. Stack Memory Usage
```cpp
void stackExample() {
    // Variables created on stack
    int number = 42;              // Integer on stack
    double values[5] = {1,2,3,4,5}; // Array on stack
    
    // Automatically cleaned up at end of scope
}
```

### 2. Heap Memory Usage
```cpp
void heapExample() {
    // Single value on heap
    int* number = new int(42);
    delete number;  // Manual cleanup
    
    // Array on heap
    int* array = new int[5];
    delete[] array;  // Array cleanup
}
```

## Common Interview Questions

1. **Stack ve Heap arasındaki farklar nelerdir?**
   - Stack: Automatic management, fast, limited size
   - Heap: Manual management, slower, large size
   - Stack: Compile-time size determination
   - Heap: Runtime size determination

2. **Memory Leak nedir? Nasıl önlenir?**
   ```cpp
   void memoryLeakExample() {
       int* ptr = new int(42);
       // delete ptr; unutulursa memory leak oluşur
   }
   ```

3. **RAII nedir?**
   - Resource Acquisition Is Initialization
   - Resource'ların constructor'da acquire edilip destructor'da release edilmesi
   - Smart pointer'ların temel principle'ı

## Practice Exercises

1. **Stack Overflow**
   - Stack overflow oluşturmak için recursive function'lar
   - Stack limit testing

2. **Heap Fragmentation**
   - Farklı size'larda memory allocation
   - Fragmentation observation

3. **Smart Pointer Usage**
   - `std::unique_ptr` implementation
   - `std::shared_ptr` use cases

## Complexity Analysis

### Stack Operations
- Push: O(1)
- Pop: O(1)
- Access: O(1)

### Heap Operations
- Allocation: O(1) - O(n)
- Deallocation: O(1)
- Access: O(1)

## Common Mistakes and Best Practices

1. **Double Deletion**
```cpp
int* ptr = new int(42);
delete ptr;
delete ptr;  // Undefined behavior!
```

2. **Dangling Pointer**
```cpp
int* ptr1 = new int(42);
int* ptr2 = ptr1;
delete ptr1;  // ptr2 is now a dangling pointer
```

3. **Memory Leak**
```cpp
void memoryLeak() {
    while(true) {
        int* ptr = new int[1000];
        // delete[] ptr; // Memory leak!
    }
}
```

## Advanced Topics

1. **Custom Memory Allocator**
```cpp
template<typename T>
class CustomAllocator {
    // Custom allocation logic
};
```

2. **Memory Pools**
```cpp
class MemoryPool {
    // Fixed-size block allocation
};
```

3. **Garbage Collection in C++**
   - Smart Pointers
   - Reference Counting
   - Weak References

## Additional Resources

1. [C++ Memory Model](https://en.cppreference.com/w/cpp/language/memory_model)
2. [Smart Pointers](https://en.cppreference.com/w/cpp/memory)
3. [RAII and Resource Management](https://en.cppreference.com/w/cpp/language/raii)

## LeetCode Problems

1. [146. LRU Cache](https://leetcode.com/problems/lru-cache/) - Memory management
2. [460. LFU Cache](https://leetcode.com/problems/lfu-cache/)
3. [Implementation of Memory Pool](https://leetcode.com/discuss/interview-question/125218/implement-a-memory-pool/)
``` 