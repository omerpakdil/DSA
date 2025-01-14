#include <iostream>
#include <chrono>
#include <iomanip>
#include <memory>
using namespace std;

// Array tanımlama ve gösterim örnekleri
namespace ArrayDeclaration {
    void staticArrayExample() {
        cout << "\n=== Static Array Examples ===\n";
        
        // Stack'te array tanımlama
        int A[5];  // Uninitialized
        int B[5] = {1, 2, 3, 4, 5};  // Initialized
        int C[] = {1, 2, 3, 4, 5};   // Size auto-determined
        
        cout << "Array B: ";
        for(int i = 0; i < 5; i++)
            cout << B[i] << " ";
        cout << endl;
        
        // Array adresleri ve boyut
        cout << "Array B address: " << B << endl;
        cout << "Size of int: " << sizeof(int) << " bytes\n";
        cout << "Size of array B: " << sizeof(B) << " bytes\n";
    }
    
    void dynamicArrayExample() {
        cout << "\n=== Dynamic Array Examples ===\n";
        
        // Heap'te array tanımlama
        int* arr1 = new int[5];  // C++ style
        int* arr2 = (int*)malloc(5 * sizeof(int));  // C style
        
        // Initialize
        for(int i = 0; i < 5; i++) {
            arr1[i] = i + 1;
            arr2[i] = (i + 1) * 10;
        }
        
        cout << "Array 1: ";
        for(int i = 0; i < 5; i++)
            cout << arr1[i] << " ";
        cout << endl;
        
        cout << "Array 2: ";
        for(int i = 0; i < 5; i++)
            cout << arr2[i] << " ";
        cout << endl;
        
        // Memory cleanup
        delete[] arr1;
        free(arr2);
    }
}

// Array boyutunu artırma örnekleri
namespace ArrayResizing {
    void resizeExample() {
        cout << "\n=== Array Resizing Example ===\n";
        
        // İlk array
        int size = 5;
        int* arr = new int[size];
        for(int i = 0; i < size; i++)
            arr[i] = i + 1;
            
        cout << "Original array: ";
        for(int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
        
        // Boyutu artır
        int newSize = size * 2;
        int* newArr = new int[newSize];
        
        // Eski elemanları kopyala
        for(int i = 0; i < size; i++)
            newArr[i] = arr[i];
            
        // Yeni elemanlara değer ata
        for(int i = size; i < newSize; i++)
            newArr[i] = i + 1;
            
        delete[] arr;  // Eski array'i temizle
        arr = newArr;  // Pointer'ı güncelle
        
        cout << "Resized array: ";
        for(int i = 0; i < newSize; i++)
            cout << arr[i] << " ";
        cout << endl;
        
        delete[] arr;  // Son temizlik
    }
}

// 2D Array örnekleri
namespace TwoDArrays {
    void staticTwoDArray() {
        cout << "\n=== Static 2D Array Example ===\n";
        
        int arr[3][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        };
        
        cout << "2D Array contents:\n";
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 4; j++)
                cout << setw(3) << arr[i][j] << " ";
            cout << endl;
        }
    }
    
    void dynamicTwoDArray() {
        cout << "\n=== Dynamic 2D Array Examples ===\n";
        
        int rows = 3, cols = 4;
        
        // Method 1: Single block
        cout << "Method 1 - Single block:\n";
        int* arr1 = new int[rows * cols];
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                arr1[i * cols + j] = i * cols + j + 1;
                
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++)
                cout << setw(3) << arr1[i * cols + j] << " ";
            cout << endl;
        }
        
        // Method 2: Array of pointers
        cout << "\nMethod 2 - Array of pointers:\n";
        int** arr2 = new int*[rows];
        for(int i = 0; i < rows; i++)
            arr2[i] = new int[cols];
            
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                arr2[i][j] = i * cols + j + 1;
                
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++)
                cout << setw(3) << arr2[i][j] << " ";
            cout << endl;
        }
        
        // Memory cleanup
        delete[] arr1;
        
        for(int i = 0; i < rows; i++)
            delete[] arr2[i];
        delete[] arr2;
    }
}

// Row Major vs Column Major karşılaştırması
namespace RowVsColumnMajor {
    void compareAccess() {
        cout << "\n=== Row vs Column Major Access Comparison ===\n";
        
        const int rows = 1000;
        const int cols = 1000;
        int** arr = new int*[rows];
        for(int i = 0; i < rows; i++)
            arr[i] = new int[cols];
            
        // Initialize
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                arr[i][j] = i * cols + j;
                
        // Row Major access timing
        auto start = chrono::high_resolution_clock::now();
        int sum1 = 0;
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                sum1 += arr[i][j];
        auto end = chrono::high_resolution_clock::now();
        auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);
        
        // Column Major access timing
        start = chrono::high_resolution_clock::now();
        int sum2 = 0;
        for(int j = 0; j < cols; j++)
            for(int i = 0; i < rows; i++)
                sum2 += arr[i][j];
        end = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << "Row Major access time: " << duration1.count() << " microseconds\n";
        cout << "Column Major access time: " << duration2.count() << " microseconds\n";
        
        // Memory cleanup
        for(int i = 0; i < rows; i++)
            delete[] arr[i];
        delete[] arr;
    }
}

int main() {
    // Array tanımlama örnekleri
    ArrayDeclaration::staticArrayExample();
    ArrayDeclaration::dynamicArrayExample();
    
    // Array boyutunu artırma örneği
    ArrayResizing::resizeExample();
    
    // 2D Array örnekleri
    TwoDArrays::staticTwoDArray();
    TwoDArrays::dynamicTwoDArray();
    
    // Row vs Column Major karşılaştırması
    RowVsColumnMajor::compareAccess();
    
    return 0;
} 