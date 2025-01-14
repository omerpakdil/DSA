# Veri Yapıları ve Algoritmalara Giriş

## İçindekiler
1. [Stack vs Heap Memory](#stack-vs-heap-memory)
2. [ADT (Abstract Data Types)](#adt-abstract-data-types)
3. [Time and Space Complexity](#time-and-space-complexity)
4. [Asymptotic Notations](#asymptotic-notations)

## Stack vs Heap Memory

### Stack Memory
- Program çalışma zamanında otomatik olarak yönetilen bellek bölgesi
- LIFO (Last In First Out) prensibiyle çalışır
- Fonksiyon çağrıları ve yerel değişkenler için kullanılır
- Bellek yönetimi otomatiktir
- Hızlı erişim sağlar
- Sınırlı boyuta sahiptir

### Heap Memory
- Dinamik olarak yönetilen bellek bölgesi
- Manuel bellek yönetimi gerektirir (allocation/deallocation)
- Büyük veri yapıları için kullanılır
- Daha yavaş erişim sağlar
- Fragmentasyon problemi oluşabilir
- Bellek sızıntıları oluşabilir

## ADT (Abstract Data Types)

ADT, veri yapılarının matematiksel/mantıksal modelidir. Verinin nasıl saklanacağı ve işlemlerin nasıl gerçekleştirileceğinden bağımsız olarak, veri yapısının ne yapması gerektiğini tanımlar.

### ADT Bileşenleri
1. **Data/Variables**: Verinin kendisi
2. **Operations**: Veri üzerinde gerçekleştirilebilecek işlemler

### Örnek: List ADT
```cpp
class List {
public:
    // Basic Operations
    void add(int element);
    void remove(int element);
    bool search(int element);
    int get(int index);
    bool isEmpty();
    int size();
};
```

## Time and Space Complexity

### Time Complexity
Bir algoritmanın çalışma süresinin, girdi boyutuna göre nasıl değiştiğini gösteren matematiksel bir ifadedir.

#### Örnek Karmaşıklıklar
1. **O(1)** - Constant Time
   ```cpp
   int getFirst(vector<int>& arr) {
       return arr[0];
   }
   ```

2. **O(n)** - Linear Time
   ```cpp
   int sum(vector<int>& arr) {
       int total = 0;
       for(int x : arr) total += x;
       return total;
   }
   ```

3. **O(n²)** - Quadratic Time
   ```cpp
   void bubbleSort(vector<int>& arr) {
       for(int i = 0; i < arr.size(); i++)
           for(int j = 0; j < arr.size()-1; j++)
               if(arr[j] > arr[j+1])
                   swap(arr[j], arr[j+1]);
   }
   ```

### Space Complexity
Bir algoritmanın çalışması için gereken ekstra bellek miktarının, girdi boyutuna göre nasıl değiştiğini gösteren matematiksel bir ifadedir.

#### Örnek Space Complexities
1. **O(1)** - Constant Space
   ```cpp
   int sum(vector<int>& arr) {
       int total = 0;  // Sadece bir değişken
       for(int x : arr) total += x;
       return total;
   }
   ```

2. **O(n)** - Linear Space
   ```cpp
   vector<int> duplicate(vector<int>& arr) {
       vector<int> result = arr;  // n elemanlı yeni dizi
       return result;
   }
   ```

## Asymptotic Notations

### Big O Notation - O
- Algoritmanın çalışma süresinin üst sınırını gösterir
- Worst case scenario'yu temsil eder
- En yaygın kullanılan notasyondur

### Omega Notation - Ω
- Algoritmanın çalışma süresinin alt sınırını gösterir
- Best case scenario'yu temsil eder

### Theta Notation - θ
- Algoritmanın çalışma süresinin hem alt hem üst sınırını gösterir
- Average case scenario'yu temsil eder
- Big O ve Omega notasyonları eşit olduğunda kullanılır

### Karşılaştırma
```
O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(2ⁿ) < O(n!)
```

### Örnekler
1. **Binary Search**: O(log n)
2. **Linear Search**: O(n)
3. **Merge Sort**: O(n log n)
4. **Bubble Sort**: O(n²)
5. **Recursive Fibonacci**: O(2ⁿ)

## Best Practices

1. **Algoritma Seçimi:**
   - Input size'a göre uygun algoritma seçin
   - Space-time trade-off'ları değerlendirin
   - Özel durumları göz önünde bulundurun

2. **Optimizasyon:**
   - Gereksiz işlemlerden kaçının
   - Uygun veri yapısını seçin
   - Cache-friendly kod yazın

3. **Bellek Yönetimi:**
   - Stack ve Heap kullanımını dengeleyin
   - Memory leak'lerden kaçının
   - Gereksiz bellek kullanımından kaçının

## Common Pitfalls

1. **Time Complexity Analizi:**
   ```cpp
   // Yanlış: İç içe döngü her zaman O(n²) değildir
   for(int i = 0; i < n; i++)
       for(int j = i; j < n; j++)  // Bu O(n²/2)
   ```

2. **Space Complexity Analizi:**
   ```cpp
   // Recursion'da stack space unutulmamalı
   int factorial(int n) {
       if(n <= 1) return 1;
       return n * factorial(n-1);  // O(n) stack space
   }
   ```

3. **Big O Notasyonu:**
   ```cpp
   // O(2n) değil, O(n) olarak sadeleştirilmeli
   for(int i = 0; i < n; i++) { /* ... */ }
   for(int i = 0; i < n; i++) { /* ... */ }
   ```
``` 