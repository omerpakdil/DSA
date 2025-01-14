#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

using namespace std;

// Direct Recursion örnekleri
namespace DirectRecursion {
    // Factorial hesaplama
    int factorial(int n) {
        if(n <= 1) return 1;  // Base case
        return n * factorial(n-1);  // Recursive case
    }
    
    // Fibonacci hesaplama
    int fibonacci(int n) {
        if(n <= 1) return n;  // Base case
        return fibonacci(n-1) + fibonacci(n-2);  // Recursive case
    }
    
    // Array sum hesaplama
    int arraySum(vector<int>& arr, int n) {
        if(n <= 0) return 0;  // Base case
        return arraySum(arr, n-1) + arr[n-1];  // Recursive case
    }
}

// Indirect Recursion örnekleri
namespace IndirectRecursion {
    void funcB(int n);  // Forward declaration
    
    void funcA(int n) {
        if(n > 0) {
            cout << n << " ";
            funcB(n-1);
        }
    }
    
    void funcB(int n) {
        if(n > 1) {
            cout << n << " ";
            funcA(n/2);
        }
    }
}

// Tail Recursion örnekleri
namespace TailRecursion {
    // Normal factorial
    int factorial(int n) {
        if(n <= 1) return 1;
        return n * factorial(n-1);  // Not tail recursive
    }
    
    // Tail recursive factorial
    int factorialTail(int n, int acc = 1) {
        if(n <= 1) return acc;
        return factorialTail(n-1, n * acc);  // Tail recursive
    }
    
    // Normal string reverse
    void reverse(string& str, int start, int end) {
        if(start >= end) return;
        swap(str[start], str[end]);
        reverse(str, start+1, end-1);  // Not tail recursive
    }
    
    // Tail recursive string reverse
    void reverseTail(string& str, int start, int end) {
        if(start >= end) return;
        swap(str[start], str[end]);
        reverseTail(str, start+1, end-1);  // Tail recursive
    }
}

// Memoization örnekleri
namespace Memoization {
    // Normal fibonacci
    int fibonacci(int n) {
        if(n <= 1) return n;
        return fibonacci(n-1) + fibonacci(n-2);
    }
    
    // Memoized fibonacci
    unordered_map<int, int> memo;
    
    int fibonacciMemo(int n) {
        if(n <= 1) return n;
        if(memo.count(n)) return memo[n];
        
        memo[n] = fibonacciMemo(n-1) + fibonacciMemo(n-2);
        return memo[n];
    }
}

// Divide and Conquer örnekleri
namespace DivideConquer {
    // Binary Search
    int binarySearch(vector<int>& arr, int target, int left, int right) {
        if(left > right) return -1;
        
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) return mid;
        
        if(arr[mid] > target)
            return binarySearch(arr, target, left, mid-1);
        return binarySearch(arr, target, mid+1, right);
    }
    
    // Merge Sort
    void merge(vector<int>& arr, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        
        while(i <= mid && j <= right) {
            if(arr[i] <= arr[j])
                temp[k++] = arr[i++];
            else
                temp[k++] = arr[j++];
        }
        
        while(i <= mid) temp[k++] = arr[i++];
        while(j <= right) temp[k++] = arr[j++];
        
        for(i = 0; i < k; i++)
            arr[left + i] = temp[i];
    }
    
    void mergeSort(vector<int>& arr, int left, int right) {
        if(left >= right) return;
        
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Backtracking örnekleri
namespace Backtracking {
    // N-Queens problem
    bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
        // Check row on left side
        for(int j = 0; j < col; j++)
            if(board[row][j]) return false;
            
        // Check upper diagonal on left side
        for(int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if(board[i][j]) return false;
            
        // Check lower diagonal on left side
        for(int i = row, j = col; i < N && j >= 0; i++, j--)
            if(board[i][j]) return false;
            
        return true;
    }
    
    bool solveNQueens(vector<vector<int>>& board, int col, int N) {
        if(col >= N) return true;
        
        for(int i = 0; i < N; i++) {
            if(isSafe(board, i, col, N)) {
                board[i][col] = 1;
                
                if(solveNQueens(board, col + 1, N))
                    return true;
                    
                board[i][col] = 0;  // Backtrack
            }
        }
        return false;
    }
}

// Power hesaplama örneği
int power(int base, int exp) {
    if(exp == 0) return 1;
    if(exp < 0) return 1 / power(base, -exp);
    return base * power(base, exp - 1);
}

// Power hesaplama (optimize edilmiş)
int powerOptimized(int base, int exp) {
    if(exp == 0) return 1;
    if(exp < 0) return 1 / powerOptimized(base, -exp);
    
    if(exp % 2 == 0) {
        int half = powerOptimized(base, exp/2);
        return half * half;
    }
    return base * powerOptimized(base, exp-1);
}

// Taylor Series hesaplama
double taylor(int x, int n) {
    static double factorial = 1;
    static double power = 1;
    double result;
    
    if(n == 0) return 1;
    
    result = taylor(x, n-1);
    factorial *= n;
    power *= x;
    return result + power/factorial;
}

// Taylor Series (Horner's Rule)
double taylorHorner(int x, int n) {
    static double result = 1;
    if(n == 0) return result;
    
    result = 1 + x * result/n;
    return taylorHorner(x, n-1);
}

// nCr hesaplama
int nCr(int n, int r) {
    if(r == 0 || r == n) return 1;
    return nCr(n-1, r-1) + nCr(n-1, r);
}

// Tower of Hanoi
void towerOfHanoi(int n, char from, char aux, char to) {
    if(n == 1) {
        cout << "Disk 1'i " << from << "'dan " << to << "'ya taşı\n";
        return;
    }
    towerOfHanoi(n-1, from, to, aux);
    cout << "Disk " << n << "'i " << from << "'dan " << to << "'ya taşı\n";
    towerOfHanoi(n-1, aux, from, to);
}

// Performance karşılaştırma fonksiyonları
void comparePerformance() {
    cout << "\n=== Performance Comparison ===\n";
    
    // Normal vs Memoized Fibonacci
    int n = 40;
    auto start = chrono::high_resolution_clock::now();
    int result1 = Memoization::fibonacci(n);
    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    start = chrono::high_resolution_clock::now();
    int result2 = Memoization::fibonacciMemo(n);
    end = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Normal Fibonacci(" << n << "): " << duration1.count() << "ms\n";
    cout << "Memoized Fibonacci(" << n << "): " << duration2.count() << "ms\n";
}

int main() {
    cout << "=== Direct Recursion Examples ===\n";
    cout << "Factorial(5): " << DirectRecursion::factorial(5) << endl;
    cout << "Fibonacci(7): " << DirectRecursion::fibonacci(7) << endl;
    vector<int> arr = {1, 2, 3, 4, 5};
    cout << "Array Sum: " << DirectRecursion::arraySum(arr, arr.size()) << endl;
    
    cout << "\n=== Indirect Recursion Example ===\n";
    IndirectRecursion::funcA(10);
    cout << endl;
    
    cout << "\n=== Tail Recursion Examples ===\n";
    cout << "Normal Factorial(5): " << TailRecursion::factorial(5) << endl;
    cout << "Tail Factorial(5): " << TailRecursion::factorialTail(5) << endl;
    
    string str = "Hello";
    TailRecursion::reverse(str, 0, str.length()-1);
    cout << "Reversed string: " << str << endl;
    
    cout << "\n=== Divide and Conquer Examples ===\n";
    vector<int> sorted_arr = {1, 3, 5, 7, 9, 11, 13};
    cout << "Binary Search(7): " << 
        DivideConquer::binarySearch(sorted_arr, 7, 0, sorted_arr.size()-1) << endl;
    
    vector<int> unsorted = {64, 34, 25, 12, 22, 11, 90};
    DivideConquer::mergeSort(unsorted, 0, unsorted.size()-1);
    cout << "Merge Sort Result: ";
    for(int x : unsorted) cout << x << " ";
    cout << endl;
    
    cout << "\n=== Backtracking Example ===\n";
    int N = 4;
    vector<vector<int>> board(N, vector<int>(N, 0));
    if(Backtracking::solveNQueens(board, 0, N)) {
        cout << "N-Queens Solution:\n";
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }
    
    cout << "\n=== Power Examples ===" << endl;
    cout << "2^5 = " << power(2, 5) << endl;
    cout << "2^5 (optimized) = " << powerOptimized(2, 5) << endl;
    cout << "2^-3 = " << power(2, -3) << endl;
    
    cout << "\n=== Taylor Series Examples ===" << endl;
    cout << "e^1 (4 terms) = " << taylor(1, 4) << endl;
    cout << "e^1 (4 terms, Horner) = " << taylorHorner(1, 4) << endl;
    
    cout << "\n=== nCr Example ===" << endl;
    cout << "C(5,2) = " << nCr(5, 2) << endl;
    
    cout << "\n=== Tower of Hanoi Example ===" << endl;
    towerOfHanoi(3, 'A', 'B', 'C');
    
    comparePerformance();
    
    return 0;
} 