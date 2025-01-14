# Recursion (Özyineleme)

## İçerik
1. [Temel Kavramlar](#temel-kavramlar)
2. [Recursion Türleri](#recursion-türleri)
3. [Recursion vs Iteration](#recursion-vs-iteration)
4. [Call Stack ve Memory](#call-stack-ve-memory)
5. [Recursion Patterns](#recursion-patterns)
6. [Recursion Optimization](#recursion-optimization)
7. [Özel Recursion Konuları](#özel-recursion-konuları)
8. [Best Practices](#best-practices)
9. [Common Pitfalls](#common-pitfalls)

## Temel Kavramlar
- Base Case (Temel Durum)
- Recursive Case (Özyinelemeli Durum)
- Stack Overflow
- Call Stack

## Recursion Türleri
1. **Direct Recursion**: Fonksiyon doğrudan kendini çağırır
   ```cpp
   void directRecursion(int n) {
       if(n <= 0) return;  // base case
       directRecursion(n-1);  // recursive case
   }
   ```

2. **Indirect Recursion**: Fonksiyonlar birbirini çağırır
   ```cpp
   void odd(int n);  // forward declaration
   
   void even(int n) {
       if(n <= 0) return;
       odd(n-1);
   }
   
   void odd(int n) {
       if(n <= 0) return;
       even(n-1);
   }
   ```

3. **Tail Recursion**: Son işlem recursive çağrı
   ```cpp
   int factorial(int n, int acc = 1) {
       if(n <= 1) return acc;
       return factorial(n-1, n * acc);
   }
   ```

4. **Tree Recursion**: Bir fonksiyon kendini birden fazla kez çağırır
   ```cpp
   void treeRecursion(int n) {
       if(n <= 0) return;
       treeRecursion(n-1);
       treeRecursion(n-1);
   }
   ```

5. **Nested Recursion**: Recursive çağrının parametresi recursive bir çağrı
   ```cpp
   int nestedRecursion(int n) {
       if(n <= 100) return n - 10;
       return nestedRecursion(nestedRecursion(n - 1));
   }
   ```

## Recursion vs Iteration
1. **Memory Kullanımı**
   - Recursion: O(n) stack space
   - Iteration: O(1) space

2. **Okunabilirlik**
   - Recursion: Karmaşık problemlerde daha temiz kod
   - Iteration: Basit problemlerde daha anlaşılır

3. **Performance**
   - Recursion: Stack overhead
   - Iteration: Genelde daha hızlı

## Call Stack ve Memory
1. **Stack Frame**: Her recursive çağrı için
   - Return address
   - Parameters
   - Local variables

2. **Stack Overflow**: Çok derin recursion
   ```cpp
   void infiniteRecursion() {
       infiniteRecursion();  // YANLIŞ: Stack overflow
   }
   ```

## Recursion Patterns
1. **Linear Recursion**: Tek recursive çağrı
   ```cpp
   int sum(int n) {
       if(n <= 0) return 0;
       return n + sum(n-1);
   }
   ```

2. **Binary Recursion**: İki recursive çağrı
   ```cpp
   int fibonacci(int n) {
       if(n <= 1) return n;
       return fibonacci(n-1) + fibonacci(n-2);
   }
   ```

3. **Exponential Recursion**: Multiple recursive çağrılar
   ```cpp
   void exponentialRecursion(int n) {
       if(n <= 0) return;
       for(int i = 0; i < n; i++)
           exponentialRecursion(n-1);
   }
   ```

4. **Mutual Recursion**: İki fonksiyon birbirini çağırır
   ```cpp
   bool isEven(int n) {
       if(n == 0) return true;
       return isOdd(n-1);
   }
   
   bool isOdd(int n) {
       if(n == 0) return false;
       return isEven(n-1);
   }
   ```

## Recursion Optimization
1. **Tail Recursion Optimization**
   ```cpp
   // Before optimization
   int factorial(int n) {
       if(n <= 1) return 1;
       return n * factorial(n-1);
   }
   
   // After optimization
   int factorial(int n, int acc = 1) {
       if(n <= 1) return acc;
       return factorial(n-1, n * acc);
   }
   ```

2. **Memoization**
   ```cpp
   map<int, int> memo;
   
   int fibonacci(int n) {
       if(n <= 1) return n;
       if(memo.count(n)) return memo[n];
       return memo[n] = fibonacci(n-1) + fibonacci(n-2);
   }
   ```

## Özel Recursion Konuları
1. **Backtracking**
   ```cpp
   void nQueens(vector<vector<int>>& board, int col) {
       if(col >= board.size()) {
           printSolution(board);
           return;
       }
       for(int i = 0; i < board.size(); i++) {
           if(isSafe(board, i, col)) {
               board[i][col] = 1;
               nQueens(board, col + 1);
               board[i][col] = 0;  // backtrack
           }
       }
   }
   ```

2. **Divide and Conquer**
   ```cpp
   int binarySearch(vector<int>& arr, int target, int left, int right) {
       if(left > right) return -1;
       
       int mid = left + (right - left) / 2;
       if(arr[mid] == target) return mid;
       
       if(arr[mid] > target)
           return binarySearch(arr, target, left, mid-1);
       return binarySearch(arr, target, mid+1, right);
   }
   ```

3. **Power Calculation (Üs Hesaplama)**
   - Bir sayının üssünü recursive olarak hesaplama yöntemi
   - İki farklı yaklaşım:
     1. Normal Recursion: O(n) time complexity
     2. Optimized Version: O(log n) time complexity (divide and conquer yaklaşımı)
   - Negatif üsler için özel durum kontrolü
   ```cpp
   // Normal recursion: O(n)
   int power(int base, int exp) {
       if(exp == 0) return 1;
       if(exp < 0) return 1 / power(base, -exp);
       return base * power(base, exp - 1);
   }
   
   // Optimized version: O(log n)
   int powerOptimized(int base, int exp) {
       if(exp == 0) return 1;
       if(exp % 2 == 0) {
           int half = powerOptimized(base, exp/2);
           return half * half;
       }
       return base * powerOptimized(base, exp-1);
   }
   ```

4. **Taylor Series (Taylor Serisi)**
   - e^x'in Taylor serisi açılımını recursive olarak hesaplama
   - İki farklı yaklaşım:
     1. Normal Recursion: Her terimi ayrı ayrı hesaplar
     2. Horner's Rule: Daha optimize edilmiş versiyonu
   - Static değişkenler kullanarak factorial ve power değerlerini takip eder
   ```cpp
   // Normal recursion
   double taylor(int x, int n) {
       static double factorial = 1;
       static double power = 1;
       if(n == 0) return 1;
       
       double result = taylor(x, n-1);
       factorial *= n;
       power *= x;
       return result + power/factorial;
   }
   
   // Horner's Rule - Daha optimize
   double taylorHorner(int x, int n) {
       static double result = 1;
       if(n == 0) return result;
       
       result = 1 + x * result/n;
       return taylorHorner(x, n-1);
   }
   ```

5. **Combination (nCr - Kombinasyon)**
   - Pascal üçgeni mantığını kullanarak kombinasyon hesaplama
   - Recursive formül: C(n,r) = C(n-1,r-1) + C(n-1,r)
   - Base case: r=0 veya r=n olduğunda 1 döner
   - Time complexity: O(2^n) - Optimize edilmemiş versiyon
   ```cpp
   int nCr(int n, int r) {
       if(r == 0 || r == n) return 1;
       return nCr(n-1, r-1) + nCr(n-1, r);
   }
   ```

6. **Tower of Hanoi (Hanoi Kulesi)**
   - Klasik recursion problemi
   - n diskli bir kuleden başka bir kuleye disk taşıma
   - Kurallar:
     1. Her seferinde bir disk taşınabilir
     2. Büyük disk küçük diskin üzerine konulamaz
     3. Ara kule olarak yardımcı kule kullanılabilir
   - Time complexity: O(2^n)
   - Her n için optimal çözümü verir
   ```cpp
   void towerOfHanoi(int n, char from, char aux, char to) {
       if(n == 1) {
           cout << "Move disk 1 from " << from << " to " << to << endl;
           return;
       }
       towerOfHanoi(n-1, from, to, aux);  // n-1 diski yardımcı kuleye taşı
       cout << "Move disk " << n << " from " << from << " to " << to << endl;
       towerOfHanoi(n-1, aux, from, to);  // n-1 diski hedef kuleye taşı
   }
   ```

## Best Practices
1. Her zaman base case tanımlayın
2. Stack overflow'u önleyin
3. Mümkünse tail recursion kullanın
4. Gereksiz recursive çağrılardan kaçının
5. Time ve space complexity'yi analiz edin

## Common Pitfalls
1. Base case unutmak
2. Stack overflow'u düşünmemek
3. Gereksiz recursive çağrılar yapmak
4. Memory kullanımını göz ardı etmek
5. Infinite recursion'a düşmek