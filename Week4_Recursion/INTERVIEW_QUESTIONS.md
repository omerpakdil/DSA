# Recursion Mülakat Soruları

## S1 ⭐
**Soru**: Recursion nedir ve iterative çözümlerden farkı nedir? Avantaj ve dezavantajlarını açıklayın.

**Cevap**:
Recursion, bir fonksiyonun kendisini çağırarak problemi daha küçük alt problemlere bölen bir çözüm yöntemidir.

**Avantajları**:
1. Kod daha okunabilir ve anlaşılır
2. Karmaşık problemleri basitleştirir
3. Tree ve graph traversal için doğal çözüm

**Dezavantajları**:
1. Stack overflow riski
2. Extra memory kullanımı (call stack)
3. Function call overhead

## S2 ⭐
**Soru**: Aşağıdaki recursive fonksiyonun çıktısı ne olur? Adım adım açıklayın.
```cpp
void printNumber(int n) {
    if(n < 1) return;
    cout << n << " ";
    printNumber(n-2);
    cout << n << " ";
}

// Çağrı: printNumber(5);
```

**Cevap**:
Çıktı: `5 3 1 1 3 5`

Adım adım:
1. `printNumber(5)`: Yazdır "5", çağır `printNumber(3)`
2. `printNumber(3)`: Yazdır "3", çağır `printNumber(1)`
3. `printNumber(1)`: Yazdır "1", çağır `printNumber(-1)`
4. `printNumber(-1)`: Return (base case)
5. `printNumber(1)`: Yazdır "1"
6. `printNumber(3)`: Yazdır "3"
7. `printNumber(5)`: Yazdır "5"

## S3 ⭐
**Soru**: Base case nedir ve neden önemlidir? Base case olmadan ne olur?

**Cevap**:
Base case, recursive fonksiyonun durma koşuludur. Önemlidir çünkü:
1. Recursion'ı sonlandırır
2. Stack overflow'u önler
3. Fonksiyonun doğru sonuç vermesini sağlar

Base case olmazsa:
1. Sonsuz recursion oluşur
2. Stack overflow hatası alınır
3. Program çöker

## S4 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonun time ve space complexity'sini analiz edin:
```cpp
int recursiveSum(int n) {
    if(n <= 0) return 0;
    return n + recursiveSum(n-1);
}
```

**Cevap**:
1. **Time Complexity**: O(n)
   - Her çağrıda n bir azalır
   - n'den 0'a kadar n adet çağrı yapılır
   - Her çağrıda O(1) işlem yapılır

2. **Space Complexity**: O(n)
   - Call stack'te n adet frame birikir
   - Her frame'de sabit alan kullanılır
   - Maximum stack derinliği n olur

## S5 ⭐⭐
**Soru**: Tail recursion nedir? Aşağıdaki iki fonksiyondan hangisi tail recursive'dir? Neden?
```cpp
// Versiyon 1
int factorial1(int n) {
    if(n <= 1) return 1;
    return n * factorial1(n-1);
}

// Versiyon 2
int factorial2(int n, int acc = 1) {
    if(n <= 1) return acc;
    return factorial2(n-1, n * acc);
}
```

**Cevap**:
Tail recursion, recursive çağrının fonksiyonun son işlemi olmasıdır.

- `factorial1` tail recursive DEĞİL çünkü:
  - Recursive çağrı dönüşünde çarpma işlemi var
  - Her çağrı stack'te beklemeli

- `factorial2` tail recursive çünkü:
  - Recursive çağrı son işlem
  - Dönüş değeri direkt olarak iletiliyor
  - Compiler optimize edebilir

## S6 ⭐
**Soru**: Memoization nedir ve ne zaman kullanılmalıdır? Fibonacci örneği üzerinden açıklayın.

**Cevap**:
Memoization, hesaplanan değerleri cache'leyerek tekrar hesaplamayı önleyen bir optimizasyon tekniğidir.

```cpp
// Without memoization: O(2^n)
int fib(int n) {
    if(n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

// With memoization: O(n)
unordered_map<int, int> memo;
int fibMemo(int n) {
    if(n <= 1) return n;
    if(memo.count(n)) return memo[n];
    
    memo[n] = fibMemo(n-1) + fibMemo(n-2);
    return memo[n];
}
```

Kullanım durumları:
1. Tekrarlanan hesaplamalar varsa
2. Alt problemler örtüşüyorsa
3. Time complexity önemliyse

## S7 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonu tail recursive hale getirin:
```cpp
int sum(vector<int>& arr, int n) {
    if(n <= 0) return 0;
    return arr[n-1] + sum(arr, n-1);
}
```

**Cevap**:
```cpp
int sumTail(vector<int>& arr, int n, int acc = 0) {
    if(n <= 0) return acc;
    return sumTail(arr, n-1, acc + arr[n-1]);
}
```

Değişiklikler:
1. Accumulator parametresi eklendi
2. Base case accumulator'ü döndürüyor
3. Recursive çağrı son işlem
4. Her adımda toplam accumulator'de birikiyor

## S8 ⭐⭐
**Soru**: Aşağıdaki kod parçasının çıktısı ne olur? Call stack'i adım adım açıklayın:
```cpp
void mystery(int n) {
    if(n > 0) {
        cout << n << " ";
        mystery(n-1);
        mystery(n-1);
    }
}

// Çağrı: mystery(2);
```

**Cevap**:
Çıktı: `2 1 1`

Call stack analizi:
1. `mystery(2)`:
   - Yazdır: "2"
   - Çağır: `mystery(1)` [ilk]
     - Yazdır: "1"
     - Çağır: `mystery(0)` [return]
     - Çağır: `mystery(0)` [return]
   - Çağır: `mystery(1)` [ikinci]
     - Yazdır: "1"
     - Çağır: `mystery(0)` [return]
     - Çağır: `mystery(0)` [return]

Time Complexity: O(2^n) çünkü her seviyede çağrı sayısı 2 katına çıkıyor.

## S9 ⭐⭐
**Soru**: Backtracking nedir? N-Queens probleminde backtracking nasıl kullanılır?

**Cevap**:
Backtracking, çözüm uzayında sistematik arama yapan ve geçersiz çözümleri geri alarak optimal çözümü bulan bir tekniktir.

N-Queens'te backtracking:
1. Her sütuna sırayla queen yerleştir
2. Yerleştirme geçerliyse devam et
3. Geçersizse geri al ve başka pozisyon dene

```cpp
bool solveNQueens(vector<vector<int>>& board, int col, int N) {
    if(col >= N) return true;  // Tüm queen'ler yerleşti
    
    for(int row = 0; row < N; row++) {
        if(isSafe(board, row, col)) {
            board[row][col] = 1;  // Queen yerleştir
            
            if(solveNQueens(board, col + 1, N))
                return true;
                
            board[row][col] = 0;  // Backtrack
        }
    }
    return false;
}
```

## S10 ⭐
**Soru**: Recursive binary search ile iterative binary search arasındaki farklar nelerdir?

**Cevap**:
1. **Memory Kullanımı**:
   - Recursive: O(log n) stack space
   - Iterative: O(1) stack space

2. **Okunabilirlik**:
   - Recursive daha temiz ve anlaşılır
   - Iterative daha karmaşık görünebilir

3. **Performance**:
   - Recursive function call overhead var
   - Iterative daha performanslı olabilir

```cpp
// Recursive
int binarySearchRec(vector<int>& arr, int target, int left, int right) {
    if(left > right) return -1;
    
    int mid = left + (right - left) / 2;
    if(arr[mid] == target) return mid;
    
    if(arr[mid] > target)
        return binarySearchRec(arr, target, left, mid-1);
    return binarySearchRec(arr, target, mid+1, right);
}

// Iterative
int binarySearchIter(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) return mid;
        
        if(arr[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1;
}
``` 

## S11 ⭐
**Soru**: String'i recursive olarak tersine çeviren bir fonksiyon yazın. İki farklı yaklaşım kullanın:
1. String'i bölerek (substring kullanarak)
2. İki index kullanarak (pointer yaklaşımı)

**Cevap**:
```cpp
// 1. Yaklaşım: String bölme
string reverse1(string str) {
    if(str.empty() || str.length() == 1) return str;
    return reverse1(str.substr(1)) + str[0];
}

// 2. Yaklaşım: İki index
void reverse2(string& str, int left, int right) {
    if(left >= right) return;
    swap(str[left], str[right]);
    reverse2(str, left + 1, right - 1);
}
```

Analiz:
1. İlk yaklaşım:
   - Her adımda yeni string oluşturur (memory intensive)
   - Time: O(n²), Space: O(n)
   
2. İkinci yaklaşım:
   - In-place değişiklik yapar
   - Time: O(n), Space: O(n) - call stack için

## S12 ⭐
**Soru**: Recursive olarak bir sayının palindrom olup olmadığını kontrol eden bir fonksiyon yazın.
Örnek: 12321 -> true, 12345 -> false

**Cevap**:
```cpp
bool isPalindrome(int num) {
    string str = to_string(num);
    return isPalindromeHelper(str, 0, str.length() - 1);
}

bool isPalindromeHelper(const string& str, int left, int right) {
    if(left >= right) return true;
    if(str[left] != str[right]) return false;
    return isPalindromeHelper(str, left + 1, right - 1);
}
```

Açıklama:
1. Sayıyı string'e çeviririz
2. İki pointer kullanarak karşılaştırma yaparız
3. Base case: left >= right (ortaya ulaştık)
4. Recursive case: karakterler eşitse devam et

## S13 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonun amacı nedir? Time complexity'si nedir?
```cpp
int mystery(int a, int b) {
    if(b == 0) return 0;
    if(b % 2 == 0)
        return mystery(a + a, b / 2);
    return mystery(a + a, b / 2) + a;
}
```

**Cevap**:
Bu fonksiyon çarpma işlemini recursive olarak gerçekleştirir (a * b).

Çalışma mantığı:
1. b çift ise: a * b = (2a) * (b/2)
2. b tek ise: a * b = (2a) * (b/2) + a

Örnek: mystery(3, 4)
- mystery(6, 2)
- mystery(12, 1)
- mystery(24, 0) + 12
- 12
- Sonuç: 3 * 4 = 12

Time Complexity: O(log b) çünkü her adımda b'yi 2'ye böleriz

## S14 ⭐
**Soru**: 1'den n'e kadar olan sayıların toplamını recursive olarak hesaplayan üç farklı fonksiyon yazın:
1. Normal recursion
2. Tail recursion
3. Formula kullanarak (tek adımda)

**Cevap**:
```cpp
// 1. Normal recursion - O(n) space
int sum1(int n) {
    if(n <= 0) return 0;
    return n + sum1(n-1);
}

// 2. Tail recursion - O(n) space (compiler optimization ile O(1))
int sum2(int n, int acc = 0) {
    if(n <= 0) return acc;
    return sum2(n-1, acc + n);
}

// 3. Formula - O(1) space
int sum3(int n) {
    if(n <= 0) return 0;
    return (n * (n + 1)) / 2;
}
```

Karşılaştırma:
1. Normal recursion: Basit ama stack kullanımı fazla
2. Tail recursion: Optimize edilebilir
3. Formula: En verimli çözüm

## S15 ⭐⭐
**Soru**: Verilen bir string'deki tüm alt stringleri (substrings) recursive olarak üreten bir fonksiyon yazın.
Örnek: "abc" -> "a", "b", "c", "ab", "bc", "abc"

**Cevap**:
```cpp
void printSubstrings(string str) {
    generateSubstrings(str, 0, "");
}

void generateSubstrings(string& str, int index, string current) {
    // Base case: string sonuna geldik
    if(index == str.length()) {
        if(!current.empty()) 
            cout << current << endl;
        return;
    }
    
    // Current karakteri dahil etmeden devam et
    generateSubstrings(str, index + 1, current);
    
    // Current karakteri dahil ederek devam et
    generateSubstrings(str, index + 1, current + str[index]);
}
```

Analiz:
1. Her karakter için iki seçenek var: al veya alma
2. Time Complexity: O(2ⁿ)
3. Space Complexity: O(n) - call stack için

## S16 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonun çıktısı ne olur? Stack kullanımını açıklayın:
```cpp
void pattern(int n) {
    if(n < 1) return;
    pattern(n-1);
    for(int i = 0; i < n; i++)
        cout << "*";
    cout << endl;
    pattern(n-1);
}

// Çağrı: pattern(3);
```

**Cevap**:
Çıktı:
```
*
**
***
**
*
```

Stack analizi:
1. pattern(3) çağrılır
   - pattern(2) çağrılır
     - pattern(1) çağrılır
       - pattern(0) return eder
       - "*" yazdırır
       - pattern(0) return eder
     - "**" yazdırır
     - pattern(1) çağrılır
       - pattern(0) return eder
       - "*" yazdırır
       - pattern(0) return eder
   - "***" yazdırır
   - pattern(2) tekrar çağrılır
     - ... (benzer süreç tekrarlanır)

Time Complexity: O(2ⁿ) çünkü her n için fonksiyon 2 kez çağrılıyor

## S17 ⭐
**Soru**: Recursive olarak bir dizinin elemanlarını yazdıran iki farklı fonksiyon yazın:
1. Baştan sona doğru
2. Sondan başa doğru

**Cevap**:
```cpp
// 1. Baştan sona
void printForward(vector<int>& arr, int index = 0) {
    if(index == arr.size()) return;
    cout << arr[index] << " ";
    printForward(arr, index + 1);
}

// 2. Sondan başa
void printBackward(vector<int>& arr, int index) {
    if(index < 0) return;
    cout << arr[index] << " ";
    printBackward(arr, index - 1);
}
```

Özellikler:
1. Her iki fonksiyon da O(n) time complexity'ye sahip
2. Stack space: O(n)
3. Base case: dizinin sınırlarına ulaşmak

## S18 ⭐⭐
**Soru**: Verilen bir sayının binary (ikili) gösterimini recursive olarak yazdıran bir fonksiyon yazın.
Örnek: 10 -> 1010

**Cevap**:
```cpp
void printBinary(int n) {
    if(n < 0) {
        cout << "-";
        printBinary(-n);
        return;
    }
    if(n < 2) {
        cout << n;
        return;
    }
    printBinary(n / 2);
    cout << n % 2;
}
```

Çalışma mantığı:
1. Sayıyı sürekli 2'ye böleriz
2. Geri dönerken kalan değerleri yazdırırız
3. Base case: sayı 2'den küçük olduğunda

Örnek: printBinary(10)
- printBinary(5) -> 1
- printBinary(2) -> 0
- printBinary(1) -> 1
- Sonuç: 1010

## S19 ⭐
**Soru**: Recursive olarak bir dizinin en büyük elemanını bulan bir fonksiyon yazın.

**Cevap**:
```cpp
int findMax(vector<int>& arr, int n) {
    // Base case: tek eleman
    if(n == 1) return arr[0];
    
    // Recursive case: son elemanı al ve kalanlarla karşılaştır
    int maxRest = findMax(arr, n-1);
    return max(maxRest, arr[n-1]);
}
```

Alternatif yaklaşım (divide and conquer):
```cpp
int findMaxDC(vector<int>& arr, int left, int right) {
    // Base case: tek eleman
    if(left == right) return arr[left];
    
    // Diziyi ortadan böl
    int mid = left + (right - left) / 2;
    int leftMax = findMaxDC(arr, left, mid);
    int rightMax = findMaxDC(arr, mid + 1, right);
    
    return max(leftMax, rightMax);
}
```

Karşılaştırma:
1. İlk yaklaşım: O(n) time, O(n) space
2. İkinci yaklaşım: O(n) time, O(log n) space

## S20 ⭐⭐
**Soru**: Recursive olarak verilen bir string'deki tüm permütasyonları üreten bir fonksiyon yazın.
Örnek: "abc" -> "abc", "acb", "bac", "bca", "cab", "cba"

**Cevap**:
```cpp
void permutations(string str) {
    generatePermutations(str, 0);
}

void generatePermutations(string& str, int index) {
    // Base case: son karaktere ulaştık
    if(index == str.length() - 1) {
        cout << str << endl;
        return;
    }
    
    // Her pozisyon için current karakteri swap yap
    for(int i = index; i < str.length(); i++) {
        swap(str[index], str[i]);  // Değişiklik yap
        generatePermutations(str, index + 1);  // Recursive çağrı
        swap(str[index], str[i]);  // Geri al (backtrack)
    }
}
```

Analiz:
1. Time Complexity: O(n!)
2. Space Complexity: O(n) - call stack için
3. Backtracking kullanılıyor
4. Her adımda bir karakteri sabitleyip diğerleriyle permütasyon oluşturuluyor

## S21 ⭐
**Soru**: Recursive olarak bir dizideki tüm elemanların toplamını hesaplayan üç farklı yaklaşım yazın:
1. Normal recursion
2. Tail recursion
3. Divide and conquer

**Cevap**:
```cpp
// 1. Normal recursion
int sum1(vector<int>& arr, int n) {
    if(n <= 0) return 0;
    return arr[n-1] + sum1(arr, n-1);
}

// 2. Tail recursion
int sum2(vector<int>& arr, int n, int acc = 0) {
    if(n <= 0) return acc;
    return sum2(arr, n-1, acc + arr[n-1]);
}

// 3. Divide and conquer
int sum3(vector<int>& arr, int left, int right) {
    if(left == right) return arr[left];
    if(left > right) return 0;
    
    int mid = left + (right - left) / 2;
    return sum3(arr, left, mid) + sum3(arr, mid + 1, right);
}
```

Karşılaştırma:
1. Normal recursion: O(n) time, O(n) space
2. Tail recursion: O(n) time, O(n) space (optimizasyon ile O(1))
3. Divide and conquer: O(n) time, O(log n) space

## S22 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonun çıktısı ne olur? Time complexity'sini hesaplayın:
```cpp
void printNumbers(int n) {
    if(n <= 0) return;
    printNumbers(n-1);
    for(int i = 1; i <= n; i++)
        cout << i << " ";
    cout << endl;
}

// Çağrı: printNumbers(3);
```

**Cevap**:
Çıktı:
```
1 
1 2 
1 2 3 
```

Analiz:
1. Call stack:
   - printNumbers(3)
     - printNumbers(2)
       - printNumbers(1)
         - printNumbers(0) return
         - print: "1"
       - print: "1 2"
     - print: "1 2 3"

2. Time Complexity: O(n²)
   - n recursive çağrı
   - Her çağrıda 1'den n'e kadar sayı yazdırma
   - Toplam: 1 + 2 + 3 + ... + n = n(n+1)/2

3. Space Complexity: O(n) - call stack için

## S23 ⭐
**Soru**: Recursive olarak bir string'in palindrom olup olmadığını kontrol eden bir fonksiyon yazın. Boşlukları ve noktalama işaretlerini yok sayın, büyük/küçük harf duyarsız olsun.
Örnek: "A man, a plan, a canal: Panama" -> true

**Cevap**:
```cpp
bool isPalindrome(string str) {
    // String'i temizle
    string cleaned;
    for(char c : str) {
        if(isalnum(c))
            cleaned += tolower(c);
    }
    return isPalindromeHelper(cleaned, 0, cleaned.length() - 1);
}

bool isPalindromeHelper(const string& str, int left, int right) {
    if(left >= right) return true;
    if(str[left] != str[right]) return false;
    return isPalindromeHelper(str, left + 1, right - 1);
}
```

Özellikler:
1. Time Complexity: O(n)
2. Space Complexity: O(n)
3. İki aşamalı çözüm:
   - String'i temizleme
   - Recursive kontrol

## S24 ⭐⭐
**Soru**: Verilen bir sayının üssünü recursive olarak hesaplayan bir fonksiyon yazın. Negatif üsler de desteklensin.
Örnek: power(2, -3) = 1/8

**Cevap**:
```cpp
double power(double base, int exp) {
    // Base cases
    if(exp == 0) return 1;
    if(exp == 1) return base;
    if(exp == -1) return 1/base;
    
    // Recursive case
    double half = power(base, exp/2);
    double result = half * half;
    
    // Tek sayı durumu için
    if(exp % 2 != 0) {
        if(exp > 0)
            result *= base;
        else
            result /= base;
    }
    
    return result;
}
```

Özellikler:
1. Time Complexity: O(log n)
2. Space Complexity: O(log n)
3. Optimizasyon:
   - Üssü ikiye bölerek hesaplama
   - Gereksiz çarpma işlemlerinden kaçınma

## S25 ⭐⭐
**Soru**: Verilen bir dizide hedef toplamı veren tüm alt dizileri (contiguous subarrays) bulan recursive bir fonksiyon yazın.
Örnek: arr = [1, 2, 3, 4, 5], target = 9 -> [4, 5], [2, 3, 4]

**Cevap**:
```cpp
void findSubarrays(vector<int>& arr, int target) {
    for(int start = 0; start < arr.size(); start++) {
        findSubarraysHelper(arr, target, start, start, 0);
    }
}

void findSubarraysHelper(vector<int>& arr, int target, int start, int curr, int sum) {
    // Base case: hedef aşıldı veya dizi bitti
    if(curr >= arr.size() || sum > target) return;
    
    // Current elemanı ekle
    sum += arr[curr];
    
    // Hedef bulundu
    if(sum == target) {
        cout << "Found subarray: ";
        for(int i = start; i <= curr; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
    
    // Recursive call: bir sonraki elemana geç
    findSubarraysHelper(arr, target, start, curr + 1, sum);
}
```

Analiz:
1. Time Complexity: O(n²)
   - Her başlangıç noktası için O(n) işlem
2. Space Complexity: O(n) - call stack için
3. Özellikler:
   - Her alt diziyi kontrol eder
   - Toplamı hedefi geçince durur
   - Tüm olası çözümleri bulur

## S26 ⭐
**Soru**: Recursive olarak bir dizinin sıralı olup olmadığını kontrol eden bir fonksiyon yazın.
Örnek: [1, 3, 5, 7] -> true, [1, 5, 3, 7] -> false

**Cevap**:
```cpp
bool isSorted(vector<int>& arr, int n) {
    // Base case: dizi boş veya tek elemanlı
    if(n <= 1) return true;
    
    // Son iki elemanı karşılaştır ve kalan diziyi kontrol et
    if(arr[n-1] < arr[n-2]) return false;
    return isSorted(arr, n-1);
}
```

Özellikler:
1. Time Complexity: O(n)
2. Space Complexity: O(n) - call stack için
3. Avantajları:
   - Basit ve anlaşılır implementasyon
   - Erken return ile gereksiz kontrolleri engeller

## S27 ⭐⭐
**Soru**: Verilen bir sayının basamaklarının toplamını recursive olarak hesaplayan bir fonksiyon yazın. Negatif sayıları da destekleyin.
Örnek: sumDigits(123) = 6, sumDigits(-123) = 6

**Cevap**:
```cpp
int sumDigits(int n) {
    // Negatif sayı kontrolü
    if(n < 0) return sumDigits(-n);
    
    // Base case: tek basamaklı sayı
    if(n < 10) return n;
    
    // Son basamağı al ve kalan sayı için recursive çağrı yap
    return n % 10 + sumDigits(n / 10);
}
```

Analiz:
1. Time Complexity: O(log n) - basamak sayısı kadar işlem
2. Space Complexity: O(log n)
3. Özellikler:
   - Negatif sayıları işler
   - Her recursive çağrıda bir basamak işlenir

## S28 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonun amacı nedir ve çıktısı ne olur? Time complexity'sini hesaplayın:
```cpp
int mystery(int n) {
    if(n == 0) return 0;
    if(n == 1) return 1;
    if(n % 2 == 0)
        return mystery(n/2);
    return mystery(n/2) + mystery(n/2 + 1);
}

// Çağrı: mystery(7)
```

**Cevap**:
Bu fonksiyon, verilen sayının binary gösterimindeki 1'lerin sayısını hesaplar.

Örnek: mystery(7)
- 7 -> 111 (binary)
- mystery(3) + mystery(4)
  - mystery(1) + mystery(2) + mystery(2)
    - 1 + mystery(1) + mystery(1)
      - 1 + 1 + 1 = 3

Time Complexity: O(n)
- Worst case: Her adımda iki recursive çağrı
- Best case: Tek recursive çağrı (çift sayılar için)

## S29 ⭐
**Soru**: Recursive olarak bir string'deki belirli bir karakterin tüm tekrarlarını kaldıran bir fonksiyon yazın.
Örnek: removeChar("hello", 'l') -> "heo"

**Cevap**:
```cpp
string removeChar(string str, char ch) {
    // Base case: string boş
    if(str.empty()) return "";
    
    // İlk karakter kontrolü ve recursive çağrı
    if(str[0] == ch)
        return removeChar(str.substr(1), ch);
    return str[0] + removeChar(str.substr(1), ch);
}
```

Alternatif yaklaşım (in-place):
```cpp
void removeCharInPlace(string& str, char ch, int index = 0) {
    // Base case: string sonu
    if(index >= str.length()) return;
    
    // Current karakter kontrolü
    if(str[index] == ch) {
        str.erase(index, 1);
        removeCharInPlace(str, ch, index);
    } else {
        removeCharInPlace(str, ch, index + 1);
    }
}
```

Karşılaştırma:
1. İlk yaklaşım: O(n²) time, O(n) space
2. İkinci yaklaşım: O(n) time, O(n) space - call stack için

## S30 ⭐⭐
**Soru**: Verilen bir sayının tüm faktörlerini (bölenlerini) recursive olarak bulan bir fonksiyon yazın. Faktörler sıralı olmalı.
Örnek: factors(12) -> [1, 2, 3, 4, 6, 12]

**Cevap**:
```cpp
void findFactors(int n, vector<int>& result, int start = 1) {
    // Base case: başlangıç sayısı n'in karekökünü geçti
    if(start * start > n) return;
    
    // Current sayı kontrolü
    if(n % start == 0) {
        result.push_back(start);
        // Eşit bölenler için kontrol
        if(start * start != n)
            result.push_back(n / start);
    }
    
    // Bir sonraki sayı için recursive çağrı
    findFactors(n, result, start + 1);
    
    // Son adımda sıralama
    if(start == 1) {
        sort(result.begin(), result.end());
    }
}
```

Analiz:
1. Time Complexity: O(√n)
2. Space Complexity: O(√n)
3. Özellikler:
   - Karekök optimizasyonu kullanır
   - Çift eklemeyi engeller
   - Sonucu sıralı verir
``` 