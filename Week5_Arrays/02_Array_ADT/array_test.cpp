#include "array_adt.h"
#include <iostream>
#include <string>
#include <cassert>

void testBasicOperations() {
    std::cout << "\n=== Testing Basic Operations ===\n";
    
    Array<int> arr(5);
    arr.append(10);
    arr.append(20);
    arr.append(30);
    
    std::cout << "Array after append: ";
    for(int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    
    arr.insert(1, 15);
    std::cout << "Array after insert(1, 15): ";
    for(int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    
    int removed = arr.remove(2);
    std::cout << "Removed element: " << removed << "\n";
    std::cout << "Array after remove(2): ";
    for(int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

void testSearchOperations() {
    std::cout << "\n=== Testing Search Operations ===\n";
    
    Array<int> arr(5);
    arr.append(10);
    arr.append(20);
    arr.append(30);
    arr.append(40);
    
    std::cout << "Linear search for 30: " << arr.linearSearch(30) << "\n";
    std::cout << "Linear search for 50: " << arr.linearSearch(50) << "\n";
    
    std::cout << "Improved linear search for 30: " << arr.improvedLinearSearch(30) << "\n";
    std::cout << "Array after improved search: ";
    for(int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

void testUtilityOperations() {
    std::cout << "\n=== Testing Utility Operations ===\n";
    
    Array<int> arr(5);
    arr.append(30);
    arr.append(10);
    arr.append(50);
    arr.append(20);
    
    std::cout << "Maximum: " << arr.getMax() << "\n";
    std::cout << "Minimum: " << arr.getMin() << "\n";
    std::cout << "Average: " << arr.getAverage() << "\n";
    
    arr.reverse();
    std::cout << "Array after reverse: ";
    for(int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

void testSetOperations() {
    std::cout << "\n=== Testing Set Operations ===\n";
    
    Array<int> arr1(5);
    Array<int> arr2(5);
    
    arr1.append(1);
    arr1.append(2);
    arr1.append(3);
    
    arr2.append(2);
    arr2.append(3);
    arr2.append(4);
    
    Array<int> unionArr = arr1.getUnion(arr2);
    Array<int> intersectionArr = arr1.getIntersection(arr2);
    Array<int> differenceArr = arr1.getDifference(arr2);
    
    std::cout << "Union: ";
    for(int i = 0; i < unionArr.getSize(); i++) {
        std::cout << unionArr[i] << " ";
    }
    std::cout << "\n";
    
    std::cout << "Intersection: ";
    for(int i = 0; i < intersectionArr.getSize(); i++) {
        std::cout << intersectionArr[i] << " ";
    }
    std::cout << "\n";
    
    std::cout << "Difference: ";
    for(int i = 0; i < differenceArr.getSize(); i++) {
        std::cout << differenceArr[i] << " ";
    }
    std::cout << "\n";
}

void testStringOperations() {
    std::cout << "\n=== Testing String Operations ===\n";
    
    Array<std::string> arr(5);
    arr.append("C++");
    arr.append("Java");
    arr.append("Python");
    
    std::cout << "Original array: ";
    for(int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    
    arr.reverse();
    std::cout << "After reverse: ";
    for(int i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    
    try {
        arr.getAverage();  // Should throw exception
    } catch (const std::runtime_error& e) {
        std::cout << "Expected error caught: " << e.what() << "\n";
    }
}

int main() {
    try {
        testBasicOperations();
        testSearchOperations();
        testUtilityOperations();
        testSetOperations();
        testStringOperations();
        
        std::cout << "\nAll tests completed successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 