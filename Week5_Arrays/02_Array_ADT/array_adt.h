#ifndef ARRAY_ADT_H
#define ARRAY_ADT_H

#include <stdexcept>
#include <string>
#include <algorithm>

template<typename T>
class Array {
private:
    T* arr;           // Pointer to array
    int size;         // Current size
    int capacity;     // Maximum capacity

public:
    // Constructors
    explicit Array(int cap) : capacity(cap), size(0) {
        if (capacity <= 0) throw std::invalid_argument("Capacity must be positive");
        arr = new T[capacity];
    }
    
    // Copy constructor
    Array(const Array& other) : capacity(other.capacity), size(other.size) {
        arr = new T[capacity];
        std::copy(other.arr, other.arr + size, arr);
    }
    
    // Move constructor
    Array(Array&& other) noexcept : arr(other.arr), size(other.size), capacity(other.capacity) {
        other.arr = nullptr;
        other.size = other.capacity = 0;
    }
    
    // Destructor
    ~Array() {
        delete[] arr;
    }
    
    // Copy assignment
    Array& operator=(const Array& other) {
        if (this != &other) {
            T* newArr = new T[other.capacity];
            std::copy(other.arr, other.arr + other.size, newArr);
            delete[] arr;
            arr = newArr;
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }
    
    // Move assignment
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] arr;
            arr = other.arr;
            size = other.size;
            capacity = other.capacity;
            other.arr = nullptr;
            other.size = other.capacity = 0;
        }
        return *this;
    }
    
    // Basic operations
    void append(const T& element) {
        if (size >= capacity) throw std::overflow_error("Array is full");
        arr[size++] = element;
    }
    
    void insert(int index, const T& element) {
        if (index < 0 || index > size) throw std::out_of_range("Invalid index");
        if (size >= capacity) throw std::overflow_error("Array is full");
        
        for (int i = size; i > index; i--) {
            arr[i] = arr[i-1];
        }
        arr[index] = element;
        size++;
    }
    
    T remove(int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Invalid index");
        
        T element = arr[index];
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i+1];
        }
        size--;
        return element;
    }
    
    // Search operations
    int linearSearch(const T& key) const {
        for (int i = 0; i < size; i++) {
            if (arr[i] == key) return i;
        }
        return -1;
    }
    
    int improvedLinearSearch(const T& key) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == key) {
                if (i > 0) std::swap(arr[i], arr[i-1]);
                return i > 0 ? i-1 : i;
            }
        }
        return -1;
    }
    
    int binarySearch(const T& key) const {
        if (!isSorted()) throw std::runtime_error("Array must be sorted for binary search");
        
        int low = 0, high = size - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] == key) return mid;
            if (arr[mid] < key) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }
    
    // Utility operations
    T get(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Invalid index");
        return arr[index];
    }
    
    void set(int index, const T& element) {
        if (index < 0 || index >= size) throw std::out_of_range("Invalid index");
        arr[index] = element;
    }
    
    T getMax() const {
        if (size == 0) throw std::runtime_error("Array is empty");
        return *std::max_element(arr, arr + size);
    }
    
    T getMin() const {
        if (size == 0) throw std::runtime_error("Array is empty");
        return *std::min_element(arr, arr + size);
    }
    
    double getAverage() const {
        if (size == 0) throw std::runtime_error("Array is empty");
        if constexpr (std::is_arithmetic_v<T>) {
            T sum = T();
            for (int i = 0; i < size; i++) {
                sum += arr[i];
            }
            return static_cast<double>(sum) / size;
        }
        throw std::runtime_error("Average operation not supported for this type");
    }
    
    // Array manipulation
    void reverse() {
        for (int i = 0; i < size/2; i++) {
            std::swap(arr[i], arr[size-1-i]);
        }
    }
    
    void leftShift() {
        if (size > 0) {
            for (int i = 0; i < size - 1; i++) {
                arr[i] = arr[i+1];
            }
            size--;
        }
    }
    
    void rightShift() {
        if (size < capacity) {
            for (int i = size; i > 0; i--) {
                arr[i] = arr[i-1];
            }
            size++;
        }
    }
    
    void rotate(int positions) {
        if (size == 0) return;
        positions = positions % size;
        if (positions < 0) positions += size;
        
        std::rotate(arr, arr + positions, arr + size);
    }
    
    // Array properties
    bool isSorted() const {
        for (int i = 1; i < size; i++) {
            if (arr[i] < arr[i-1]) return false;
        }
        return true;
    }
    
    int getSize() const { return size; }
    int getCapacity() const { return capacity; }
    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }
    
    // Array operations
    void merge(const Array& other) {
        if (size + other.size > capacity) throw std::overflow_error("Insufficient capacity for merge");
        
        std::copy(other.arr, other.arr + other.size, arr + size);
        size += other.size;
    }
    
    Array<T> findDuplicates() const {
        Array<T> duplicates(size);
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (arr[i] == arr[j]) {
                    duplicates.append(arr[i]);
                    break;
                }
            }
        }
        return duplicates;
    }
    
    void removeDuplicates() {
        if (size <= 1) return;
        
        int newSize = 1;
        for (int i = 1; i < size; i++) {
            bool isDuplicate = false;
            for (int j = 0; j < newSize; j++) {
                if (arr[i] == arr[j]) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate) {
                arr[newSize++] = arr[i];
            }
        }
        size = newSize;
    }
    
    Array<T> findMissingElements() const {
        if constexpr (std::is_arithmetic_v<T>) {
            if (!isSorted()) throw std::runtime_error("Array must be sorted");
            
            Array<T> missing(size);
            for (int i = 1; i < size; i++) {
                T diff = arr[i] - arr[i-1];
                if (diff > 1) {
                    for (T j = 1; j < diff; j++) {
                        missing.append(arr[i-1] + j);
                    }
                }
            }
            return missing;
        }
        throw std::runtime_error("Missing elements operation not supported for this type");
    }
    
    Array<T> findPairsWithSum(T sum) const {
        if constexpr (std::is_arithmetic_v<T>) {
            Array<T> pairs(size * 2);
            for (int i = 0; i < size; i++) {
                for (int j = i + 1; j < size; j++) {
                    if (arr[i] + arr[j] == sum) {
                        pairs.append(arr[i]);
                        pairs.append(arr[j]);
                    }
                }
            }
            return pairs;
        }
        throw std::runtime_error("Find pairs operation not supported for this type");
    }
    
    // Set operations
    Array<T> getUnion(const Array& other) const {
        Array<T> result(capacity + other.capacity);
        
        for (int i = 0; i < size; i++) {
            result.append(arr[i]);
        }
        
        for (int i = 0; i < other.size; i++) {
            if (result.linearSearch(other.arr[i]) == -1) {
                result.append(other.arr[i]);
            }
        }
        
        return result;
    }
    
    Array<T> getIntersection(const Array& other) const {
        Array<T> result(std::min(capacity, other.capacity));
        
        for (int i = 0; i < size; i++) {
            if (other.linearSearch(arr[i]) != -1) {
                result.append(arr[i]);
            }
        }
        
        return result;
    }
    
    Array<T> getDifference(const Array& other) const {
        Array<T> result(capacity);
        
        for (int i = 0; i < size; i++) {
            if (other.linearSearch(arr[i]) == -1) {
                result.append(arr[i]);
            }
        }
        
        return result;
    }
    
    // Operator overloading
    T& operator[](int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Invalid index");
        return arr[index];
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Invalid index");
        return arr[index];
    }
};

#endif // ARRAY_ADT_H
