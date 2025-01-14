#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

// Time Complexity örnekleri

// O(1) - Constant Time
int getFirst(const std::vector<int>& arr) {
    if(arr.empty()) throw std::runtime_error("Array is empty");
    return arr[0];
}

// O(n) - Linear Time
int linearSearch(const std::vector<int>& arr, int target) {
    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] == target) return i;
    }
    return -1;
}

// O(log n) - Logarithmic Time
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) return mid;
        if(arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// O(n log n) - Linearithmic Time
void mergeSort(std::vector<int>& arr) {
    if(arr.size() <= 1) return;
    
    int mid = arr.size() / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());
    
    mergeSort(left);
    mergeSort(right);
    
    std::merge(left.begin(), left.end(),
              right.begin(), right.end(),
              arr.begin());
}

// O(n²) - Quadratic Time
void bubbleSort(std::vector<int>& arr) {
    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < arr.size() - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Space Complexity örnekleri

// O(1) Space - Constant Space
int sumArray(const std::vector<int>& arr) {
    int sum = 0;  // Sadece bir değişken kullanılıyor
    for(int x : arr) sum += x;
    return sum;
}

// O(n) Space - Linear Space
std::vector<int> duplicateArray(const std::vector<int>& arr) {
    std::vector<int> result = arr;  // n elemanlı yeni dizi
    return result;
}

// O(n²) Space - Quadratic Space
std::vector<std::vector<int>> createMatrix(int n) {
    // n x n boyutunda 2D matris
    return std::vector<std::vector<int>>(n, std::vector<int>(n));
}

// Performans ölçüm yardımcı fonksiyonu
template<typename Func>
long long measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
    // Test verileri hazırlama
    std::vector<int> smallArray = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::vector<int> largeArray(10000);
    for(int i = 0; i < largeArray.size(); i++) {
        largeArray[i] = rand() % 10000;
    }
    
    std::cout << "\n=== Time Complexity Örnekleri ===\n";
    
    // O(1) test
    std::cout << "\nO(1) - Constant Time:\n";
    std::cout << "First element: " << getFirst(smallArray) << "\n";
    
    // O(n) test
    std::cout << "\nO(n) - Linear Time:\n";
    auto linearTime = measureTime([&]() {
        linearSearch(largeArray, -1);  // Worst case
    });
    std::cout << "Linear search time: " << linearTime << " microseconds\n";
    
    // O(log n) test
    std::cout << "\nO(log n) - Logarithmic Time:\n";
    std::sort(largeArray.begin(), largeArray.end());  // Binary search için sıralama
    auto logTime = measureTime([&]() {
        binarySearch(largeArray, -1);  // Worst case
    });
    std::cout << "Binary search time: " << logTime << " microseconds\n";
    
    // O(n log n) test
    std::cout << "\nO(n log n) - Linearithmic Time:\n";
    auto nLogNTime = measureTime([&]() {
        std::vector<int> temp = largeArray;
        mergeSort(temp);
    });
    std::cout << "Merge sort time: " << nLogNTime << " microseconds\n";
    
    // O(n²) test
    std::cout << "\nO(n²) - Quadratic Time:\n";
    auto quadraticTime = measureTime([&]() {
        std::vector<int> temp = smallArray;  // Küçük dizi kullanıyoruz
        bubbleSort(temp);
    });
    std::cout << "Bubble sort time: " << quadraticTime << " microseconds\n";
    
    std::cout << "\n=== Space Complexity Örnekleri ===\n";
    
    // Space complexity örnekleri
    std::cout << "\nO(1) Space - Array sum: " << sumArray(smallArray) << "\n";
    
    auto duplicated = duplicateArray(smallArray);
    std::cout << "O(n) Space - Duplicated array size: " << duplicated.size() << "\n";
    
    auto matrix = createMatrix(3);
    std::cout << "O(n²) Space - Matrix size: " << matrix.size() << "x" << matrix[0].size() << "\n";
    
    return 0;
} 