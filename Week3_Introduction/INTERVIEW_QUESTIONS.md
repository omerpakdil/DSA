# Veri Yapıları ve Algoritmalara Giriş Mülakat Soruları

## İçindekiler
1. [Stack vs Heap Memory](#stack-vs-heap-memory)
2. [ADT (Abstract Data Types)](#adt-abstract-data-types)
3. [Time and Space Complexity](#time-and-space-complexity)
4. [Asymptotic Notations](#asymptotic-notations)

## Stack vs Heap Memory

### S1 ⭐
**Soru**: Stack ve Heap memory arasındaki temel farklar nelerdir? Hangisini ne zaman kullanmalıyız?

**Cevap**:
Stack ve Heap arasındaki temel farklar:
1. **Yönetim**: 
   - Stack: Otomatik bellek yönetimi
   - Heap: Manuel bellek yönetimi

2. **Erişim Hızı**: 
   - Stack: Daha hızlı (LIFO yapısı)
   - Heap: Daha yavaş (fragmentasyon olabilir)

3. **Boyut**: 
   - Stack: Sınırlı boyut
   - Heap: Daha büyük boyut (RAM limitlerine kadar)

Kullanım senaryoları:
- Stack: Yerel değişkenler, küçük objeler
- Heap: Büyük veri yapıları, dinamik boyutlu objeler

### S2 ⭐
**Soru**: Aşağıdaki kod parçasında hangi değişkenler Stack'te, hangileri Heap'te saklanır?
```cpp
void func() {
    int x = 5;                    // 1
    int* p = new int(10);         // 2
    vector<int> vec = {1,2,3};    // 3
    int arr[5] = {1,2,3,4,5};     // 4
    string str = "hello";         // 5
}
```

**Cevap**:
Stack'te saklananlar:
- x (1): Yerel değişken
- p: Pointer'ın kendisi (ama gösterdiği değer Heap'te)
- arr (4): Sabit boyutlu dizi
- vec: Vector objesi (ama elemanları Heap'te)
- str: String objesi (ama içeriği Heap'te)

Heap'te saklananlar:
- p'nin gösterdiği değer (2)
- vec'in elemanları (3)
- str'nin içeriği (5)

### S3 ⭐⭐
**Soru**: Stack overflow ve heap fragmentation nedir? Bu problemleri nasıl önleyebiliriz?

**Cevap**:
1. **Stack Overflow**:
   - Nedenleri:
     - Çok derin recursive çağrılar
     - Büyük yerel değişkenler
   - Önleme:
     - Recursive derinliği sınırlama
     - Büyük verileri heap'te saklama
     - Tail recursion kullanma

2. **Heap Fragmentation**:
   - Nedenleri:
     - Sürekli allocation/deallocation
     - Farklı boyutlarda bellek blokları
   - Önleme:
     - Memory pool kullanımı
     - Object pooling
     - Smart pointer'lar ile bellek yönetimi

## ADT (Abstract Data Types)

### S4 ⭐
**Soru**: ADT nedir ve neden önemlidir? Bir örnek vererek açıklayın.

**Cevap**:
ADT (Abstract Data Type):
- Veri yapısının davranışsal tanımıdır
- İmplementasyon detaylarından bağımsızdır
- Encapsulation sağlar

Örnek - Stack ADT:
```cpp
class Stack {
public:
    virtual void push(int x) = 0;
    virtual int pop() = 0;
    virtual int top() = 0;
    virtual bool isEmpty() = 0;
};
```

Bu ADT farklı şekillerde implemente edilebilir:
- Array kullanarak
- Linked List kullanarak
- Vector kullanarak

### S5 ⭐⭐
**Soru**: Aşağıdaki Queue ADT implementasyonundaki hataları bulun ve düzeltin:
```cpp
class Queue {
    int* arr;
    int front, rear;
public:
    Queue(int size) {
        arr = new int[size];
        front = rear = 0;
    }
    void enqueue(int x) {
        arr[rear++] = x;
    }
    int dequeue() {
        return arr[front++];
    }
};
```

**Cevap**:
Hatalı noktalar:
1. Kapasite kontrolü yok
2. Boş queue kontrolü yok
3. Circular queue yapısı yok
4. Destructor yok (memory leak)

Düzeltilmiş versiyon:
```cpp
class Queue {
    int* arr;
    int front, rear;
    int capacity;
    int size;
public:
    Queue(int cap) : capacity(cap) {
        arr = new int[capacity];
        front = rear = size = 0;
    }
    ~Queue() {
        delete[] arr;
    }
    void enqueue(int x) {
        if(size == capacity) 
            throw runtime_error("Queue is full");
        arr[rear] = x;
        rear = (rear + 1) % capacity;
        size++;
    }
    int dequeue() {
        if(size == 0)
            throw runtime_error("Queue is empty");
        int x = arr[front];
        front = (front + 1) % capacity;
        size--;
        return x;
    }
};
```

## Time and Space Complexity

### S6 ⭐
**Soru**: Aşağıdaki fonksiyonun time ve space complexity'si nedir?
```cpp
int sum(vector<vector<int>>& matrix) {
    int total = 0;
    for(int i = 0; i < matrix.size(); i++)
        for(int j = 0; j < matrix[0].size(); j++)
            total += matrix[i][j];
    return total;
}
```

**Cevap**:
- Time Complexity: O(n*m), n ve m matrisin boyutları
- Space Complexity: O(1), sadece total değişkeni kullanılıyor

### S7 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonun time ve space complexity'sini analiz edin:
```cpp
int func(int n) {
    if(n <= 1) return 1;
    return func(n-1) + func(n-1);
}
```

**Cevap**:
- Time Complexity: O(2ⁿ)
  - Her çağrı 2 yeni çağrı yapıyor
  - Recursive tree'nin derinliği n
  - Toplam node sayısı 2ⁿ

- Space Complexity: O(n)
  - Maximum recursion derinliği n
  - Her çağrı stack frame'de yer kaplıyor
  - Herhangi bir anda aktif olan çağrı sayısı n

### S8 ⭐⭐
**Soru**: Aşağıdaki kod parçasının time complexity'si nedir? Açıklayın.
```cpp
void func(int n) {
    for(int i = 1; i < n; i *= 2)
        for(int j = n; j > 0; j--)
            cout << i << j << endl;
}
```

**Cevap**:
- Time Complexity: O(n log n)
  - Dış döngü: O(log n)
    - i değeri 1'den başlayıp 2 ile çarpılıyor
    - n'e ulaşana kadar log n adım
  - İç döngü: O(n)
    - j değeri n'den 1'e kadar azalıyor
  - Toplam: O(n) * O(log n) = O(n log n)

## Asymptotic Notations

### S9 ⭐
**Soru**: Big O, Theta ve Omega notasyonları arasındaki fark nedir? Bir algoritma için bu üç notasyon ne zaman aynı olur?

**Cevap**:
- **Big O (O)**: Üst sınır
  - f(n) ≤ c * g(n)
  - Worst case

- **Omega (Ω)**: Alt sınır
  - f(n) ≥ c * g(n)
  - Best case

- **Theta (θ)**: Tam sınır
  - c₁ * g(n) ≤ f(n) ≤ c₂ * g(n)
  - Average case

Üç notasyon şu durumda aynı olur:
- Algoritmanın best, worst ve average case'leri aynı olduğunda
- Örnek: Array'de ilk elemana erişim O(1) = Ω(1) = θ(1)

### S10 ⭐⭐
**Soru**: Aşağıdaki karmaşıklıkları küçükten büyüğe sıralayın ve her biri için örnek bir algoritma verin:
```
O(n!), O(n), O(2ⁿ), O(n²), O(log n), O(n log n), O(1)
```

**Cevap**:
Sıralama (küçükten büyüğe):
1. O(1) - Constant
   - Array'in ilk elemanına erişim
   - Stack'e push/pop

2. O(log n) - Logarithmic
   - Binary search
   - Balanced BST'de arama

3. O(n) - Linear
   - Linear search
   - Array traversal

4. O(n log n) - Linearithmic
   - Merge sort
   - Quick sort (average case)

5. O(n²) - Quadratic
   - Bubble sort
   - Selection sort

6. O(2ⁿ) - Exponential
   - Recursive Fibonacci
   - Power set bulma

7. O(n!) - Factorial
   - Traveling Salesman (brute force)
   - Permütasyon üretme

### S11 ⭐⭐
**Soru**: Aşağıdaki kod parçasında memory leak var mı? Varsa nasıl düzeltirsiniz? Smart pointer kullanarak nasıl yeniden yazarsınız?
```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

void processNodes() {
    Node* head = new Node(1);
    head->next = new Node(2);
    
    if(head->data < 0)
        throw runtime_error("Negative value");
        
    delete head;
}
```

**Cevap**:
1. Memory leak var çünkü:
   - Exception durumunda hiçbir node delete edilmiyor
   - Normal durumda sadece head delete ediliyor, head->next leak yapıyor

2. Manuel düzeltme:
```cpp
void processNodes() {
    Node* head = new Node(1);
    try {
        head->next = new Node(2);
        if(head->data < 0) {
            delete head->next;
            delete head;
            throw runtime_error("Negative value");
        }
        delete head->next;
        delete head;
    } catch(...) {
        delete head;
        throw;
    }
}
```

3. Smart pointer ile çözüm:
```cpp
void processNodes() {
    auto head = make_unique<Node>(1);
    head->next = make_unique<Node>(2).release();
    
    if(head->data < 0)
        throw runtime_error("Negative value");
}
```

### S12 ⭐⭐
**Soru**: ADT implementasyonunda template metaprogramming kullanarak compile-time type checking yapın. Stack ADT'yi generic hale getirin ve sadece belirli tipleri kabul edecek şekilde kısıtlayın.

**Cevap**:
```cpp
// Type trait for allowed types
template<typename T>
struct is_stack_type : std::false_type {};

template<> struct is_stack_type<int> : std::true_type {};
template<> struct is_stack_type<double> : std::true_type {};
template<> struct is_stack_type<string> : std::true_type {};

template<typename T>
class Stack {
    static_assert(is_stack_type<T>::value, 
                 "Type not allowed in Stack");
private:
    vector<T> data;
    
public:
    void push(T value) {
        data.push_back(value);
    }
    
    T pop() {
        if(data.empty())
            throw runtime_error("Stack is empty");
        T value = data.back();
        data.pop_back();
        return value;
    }
};

// Kullanım
Stack<int> s1;      // OK
Stack<double> s2;   // OK
Stack<string> s3;   // OK
Stack<bool> s4;     // Compile error
```

### S13 ⭐⭐
**Soru**: Aşağıdaki kod parçasının amortized time complexity'sini analiz edin. Vector'ün capacity artışını göz önünde bulundurarak açıklayın.
```cpp
vector<int> numbers;
for(int i = 0; i < n; i++) {
    numbers.push_back(i);
}
```

**Cevap**:
- **Naive Analysis**: O(n) gibi görünür
- **Detailed Analysis**:
  1. Vector capacity dolduğunda, yeni alan allocation:
     - 2x büyüme stratejisi
     - Eski elemanları yeni alana kopyalama
  2. Capacity artışları:
     - 1 → 2 → 4 → 8 → 16 → ...
  3. Kopyalama maliyetleri:
     - 1 + 2 + 4 + 8 + ... + n/2
     - Bu geometric series toplamı ≈ n
  4. **Amortized Analysis**:
     - Toplam maliyet: O(n)
     - Her push_back için amortized O(1)

### S14 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonun space complexity'sini optimize edin. Tail recursion kullanarak stack overflow riskini azaltın.
```cpp
// Original
int factorial(int n) {
    if(n <= 1) return 1;
    return n * factorial(n-1);
}

// Your optimized version here
```

**Cevap**:
```cpp
// Tail recursive version
int factorial(int n, int acc = 1) {
    if(n <= 1) return acc;
    return factorial(n-1, n * acc);
}
```

Optimizasyon açıklaması:
1. **Original version**:
   - Her recursive çağrı stack'te bekliyor
   - Space Complexity: O(n)
   - Stack overflow riski yüksek

2. **Tail recursive version**:
   - Accumulator parametresi kullanıyor
   - Modern compiler'lar optimize edebilir
   - Space Complexity: O(1) olabilir
   - Stack overflow riski düşük

### S15 ⭐⭐
**Soru**: Aşağıdaki algoritmanın time complexity'sini analiz edin. Master Theorem kullanarak açıklayın.
```cpp
int algorithm(int n) {
    if(n <= 1) return 1;
    
    int sum = 0;
    for(int i = 0; i < 4; i++) {
        sum += algorithm(n/2);
    }
    return sum + n;
}
```

**Cevap**:
Master Theorem kullanarak analiz:

1. **Recursive relation**:
   - T(n) = 4T(n/2) + n
   - a = 4 (subproblem sayısı)
   - b = 2 (her subproblem'in boyut azalması)
   - f(n) = n (additional work)

2. **Master Theorem formülü**:
   - Compare n^(log_b(a)) vs f(n)
   - n^(log_2(4)) = n^2
   - n^2 vs n

3. **Sonuç**:
   - n^2 > n olduğu için
   - T(n) = O(n^2)

4. **Açıklama**:
   - Her seviyede 4 recursive çağrı
   - Derinlik log n
   - Toplam node sayısı n^2'ye yaklaşıyor

### S16 ⭐
**Soru**: Aşağıdaki kod parçasında hangi değişkenler için memory leak oluşabilir? Nasıl önlersiniz?
```cpp
void func() {
    int* p1 = new int(5);
    int* p2 = new int[10];
    
    if(*p1 > 10) {
        delete p1;
        return;
    }
    
    *p1 = 20;
    delete p1;
    delete[] p2;
}
```

**Cevap**:
1. Memory leak noktaları:
   - if bloğunda sadece p1 delete ediliyor, p2 leak yapıyor
   - Exception durumunda hiçbiri delete edilmiyor

2. Düzeltilmiş versiyon:
```cpp
void func() {
    int* p1 = new int(5);
    int* p2 = new int[10];
    
    try {
        if(*p1 > 10) {
            delete p1;
            delete[] p2;
            return;
        }
        
        *p1 = 20;
        delete p1;
        delete[] p2;
    } catch(...) {
        delete p1;
        delete[] p2;
        throw;
    }
}
```

3. Modern C++ çözümü:
```cpp
void func() {
    auto p1 = make_unique<int>(5);
    auto p2 = make_unique<int[]>(10);
    
    if(*p1 > 10) return;
    *p1 = 20;
}
```

### S17 ⭐
**Soru**: ADT'lerde encapsulation neden önemlidir? Bir örnek üzerinden açıklayın.

**Cevap**:
Encapsulation'ın faydaları:
1. Implementation details gizlenir
2. Interface değişmeden implementasyon değiştirilebilir
3. Data integrity sağlanır

Örnek:
```cpp
// Kötü tasarım
class Stack {
public:
    vector<int> data;  // Implementation details exposed
};

// İyi tasarım
class Stack {
private:
    vector<int> data;  // Implementation hidden
public:
    void push(int x) { data.push_back(x); }
    int pop() {
        if(data.empty()) throw runtime_error("Empty stack");
        int x = data.back();
        data.pop_back();
        return x;
    }
};
```

### S18 ⭐
**Soru**: Aşağıdaki algoritmaların best ve worst case time complexity'lerini belirtin:
1. Linear Search
2. Binary Search
3. Bubble Sort
4. Quick Sort

**Cevap**:
1. **Linear Search**:
   - Best Case: O(1) - İlk eleman aranan eleman
   - Worst Case: O(n) - Son eleman aranan eleman veya eleman yok

2. **Binary Search**:
   - Best Case: O(1) - Ortadaki eleman aranan eleman
   - Worst Case: O(log n) - Aranan eleman en sonda

3. **Bubble Sort**:
   - Best Case: O(n) - Array zaten sıralı
   - Worst Case: O(n²) - Array ters sıralı

4. **Quick Sort**:
   - Best Case: O(n log n) - Pivot her zaman ortada
   - Worst Case: O(n²) - Pivot her zaman en küçük/büyük

### S19 ⭐⭐
**Soru**: Aşağıdaki fonksiyonun space complexity'sini analiz edin:
```cpp
vector<int> generateSequence(int n) {
    vector<int> result;
    for(int i = 0; i < n; i++) {
        vector<int> temp(i);
        for(int j = 0; j < i; j++) {
            temp[j] = i + j;
        }
        result.insert(result.end(), temp.begin(), temp.end());
    }
    return result;
}
```

**Cevap**:
1. **Auxiliary Space Analysis**:
   - temp vector: Her iterasyonda i boyutunda
   - Maximum boyut: n-1
   - result vector: Final boyut = 0 + 1 + 2 + ... + (n-1) = n(n-1)/2

2. **Total Space Complexity**: O(n²)
   - temp vector: O(n)
   - result vector: O(n²)
   - Dominant term: O(n²)

### S20 ⭐
**Soru**: Aşağıdaki kod parçasının time complexity'si nedir? Neden?
```cpp
int count = 0;
for(int i = n; i > 0; i /= 2) {
    for(int j = 0; j < i; j++) {
        count++;
    }
}
```

**Cevap**:
1. **Dış Döngü Analizi**:
   - i değerleri: n, n/2, n/4, n/8, ...
   - log n kez çalışır

2. **İç Döngü Analizi**:
   - İlk iterasyon: n kez
   - İkinci iterasyon: n/2 kez
   - Üçüncü iterasyon: n/4 kez

3. **Toplam İşlem**:
   - n + n/2 + n/4 + n/8 + ...
   - = n * (1 + 1/2 + 1/4 + 1/8 + ...)
   - = n * 2
   - = O(n)
```

### S21 ⭐
**Soru**: Stack ve Heap memory kullanımının performans üzerindeki etkisini açıklayın. Aşağıdaki iki kod parçasını karşılaştırın:
```cpp
// Versiyon 1
void func1(int n) {
    int arr[1000];
    for(int i = 0; i < 1000; i++)
        arr[i] = i;
}

// Versiyon 2
void func2(int n) {
    int* arr = new int[1000];
    for(int i = 0; i < 1000; i++)
        arr[i] = i;
    delete[] arr;
}
```

**Cevap**:
1. **Stack Versiyon (func1)**:
   - Avantajlar:
     - Hızlı allocation ve deallocation
     - Cache-friendly (contiguous memory)
     - Memory leak riski yok
   - Dezavantajlar:
     - Boyut compile-time'da bilinmeli
     - Stack overflow riski

2. **Heap Versiyon (func2)**:
   - Avantajlar:
     - Runtime'da boyut belirlenebilir
     - Daha büyük boyutlar kullanılabilir
   - Dezavantajlar:
     - Daha yavaş allocation/deallocation
     - Memory leak riski
     - Fragmentation olabilir

### S22 ⭐
**Soru**: ADT kullanarak bir Priority Queue'nun temel operasyonlarını tanımlayın. Hangi operasyonlar gereklidir?

**Cevap**:
```cpp
template<typename T>
class PriorityQueue {
public:
    // Temel operasyonlar
    virtual void insert(T element, int priority) = 0;
    virtual T getHighestPriority() = 0;
    virtual T removeHighestPriority() = 0;
    virtual bool isEmpty() = 0;
    virtual int size() = 0;
    
    // Yardımcı operasyonlar
    virtual void clear() = 0;
    virtual int getPriority(T element) = 0;
};
```

Operasyonların önemi:
1. `insert`: Yeni eleman ekleme (O(log n))
2. `getHighestPriority`: En yüksek öncelikli elemanı görme (O(1))
3. `removeHighestPriority`: En yüksek öncelikli elemanı çıkarma (O(log n))
4. `isEmpty` ve `size`: Queue durumunu kontrol etme (O(1))

### S23 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonun time ve space complexity'sini analiz edin:
```cpp
int mystery(int n, int m) {
    if(n == 0) return m;
    if(m == 0) return n;
    return mystery(n-1, m) + mystery(n, m-1);
}
```

**Cevap**:
1. **Time Complexity Analysis**:
   - Her çağrı 2 yeni çağrı yapıyor
   - Derinlik: n + m
   - T(n,m) = T(n-1,m) + T(n,m-1) + O(1)
   - Total: O(2^(n+m))

2. **Space Complexity Analysis**:
   - Recursive call stack derinliği: O(n + m)
   - Her stack frame'de sabit alan
   - Total: O(n + m)

3. **Fonksiyonun Amacı**:
   - Bu fonksiyon (n+m) choose n hesaplıyor
   - Pascal üçgenindeki değerleri buluyor

### S24 ⭐
**Soru**: Aşağıdaki kod parçasının time complexity'sini hesaplayın:
```cpp
void process(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j += i + 1) {
            arr[j] *= 2;
        }
    }
}
```

**Cevap**:
1. **Dış Döngü**: n kez çalışır

2. **İç Döngü Analizi**:
   - i = 0 için: n kez
   - i = 1 için: n/2 kez
   - i = 2 için: n/3 kez
   - i = 3 için: n/4 kez

3. **Toplam İşlem**:
   - n + n/2 + n/3 + n/4 + ... + 1
   - = n * (1 + 1/2 + 1/3 + ... + 1/n)
   - = n * log n
   - Time Complexity: O(n log n)

### S25 ⭐⭐
**Soru**: Aşağıdaki kod parçasında potansiyel bellek problemlerini bulun ve düzeltin:
```cpp
class DataManager {
    int* data;
    int size;
public:
    DataManager(int n) : size(n) {
        data = new int[size];
    }
    
    DataManager(const DataManager& other) {
        size = other.size;
        data = other.data;
    }
    
    void operator=(DataManager& other) {
        size = other.size;
        data = other.data;
    }
    
    ~DataManager() {
        delete[] data;
    }
};
```

**Cevap**:
Problemler:
1. Shallow copy yapılıyor (double delete riski)
2. Assignment operator yanlış
3. Self-assignment kontrolü yok
4. Move semantics yok

Düzeltilmiş versiyon:
```cpp
class DataManager {
    int* data;
    int size;
public:
    DataManager(int n) : size(n) {
        data = new int[size];
    }
    
    // Copy constructor
    DataManager(const DataManager& other) : size(other.size) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
    }
    
    // Assignment operator
    DataManager& operator=(const DataManager& other) {
        if(this != &other) {  // Self-assignment check
            int* new_data = new int[other.size];
            std::copy(other.data, other.data + other.size, new_data);
            delete[] data;
            data = new_data;
            size = other.size;
        }
        return *this;
    }
    
    // Move constructor
    DataManager(DataManager&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
    
    // Move assignment
    DataManager& operator=(DataManager&& other) noexcept {
        if(this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    ~DataManager() {
        delete[] data;
    }
};
```

### S26 ⭐
**Soru**: Aşağıdaki kod parçasında memory kullanımını analiz edin. Stack ve heap kullanımını açıklayın:
```cpp
struct Point { int x, y; };

void processPoints(int n) {
    vector<Point> points;              // 1
    Point* dynamicPoint = new Point;   // 2
    Point staticPoint = {5, 10};       // 3
    
    for(int i = 0; i < n; i++) {
        points.push_back({i, i*2});    // 4
    }
    
    delete dynamicPoint;
}
```

**Cevap**:
Her satır için memory analizi:
1. `vector<Point>`:
   - Vector objesi stack'te
   - İçindeki Point'ler heap'te
   - Capacity artışları heap'te gerçekleşir

2. `Point* dynamicPoint`:
   - Pointer stack'te
   - Point objesi heap'te

3. `Point staticPoint`:
   - Tüm obje stack'te
   - Scope bitince otomatik temizlenir

4. `points.push_back()`:
   - Yeni Point'ler heap'teki vector içinde
   - Capacity yetmezse reallocation olur

### S27 ⭐
**Soru**: ADT'lerde interface ve implementation ayrımı neden önemlidir? Bir örnek üzerinden açıklayın.

**Cevap**:
Interface ve implementation ayrımının faydaları:
1. Loose coupling sağlar
2. Maintainability artar
3. Testing kolaylaşır

Örnek:
```cpp
// Interface (ADT)
class List {
public:
    virtual void add(int value) = 0;
    virtual void remove(int index) = 0;
    virtual int get(int index) = 0;
    virtual int size() const = 0;
    virtual ~List() = default;
};

// Implementation 1
class ArrayList : public List {
private:
    vector<int> data;
public:
    void add(int value) override { 
        data.push_back(value); 
    }
    // ... diğer metodlar
};

// Implementation 2
class LinkedList : public List {
private:
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
public:
    void add(int value) override {
        Node* newNode = new Node{value, head};
        head = newNode;
    }
    // ... diğer metodlar
};
```

### S28 ⭐⭐
**Soru**: Aşağıdaki recursive fonksiyonun time ve space complexity'sini analiz edin ve optimize edin:
```cpp
int findSum(vector<int>& arr, int start, int end) {
    if(start == end) return arr[start];
    int mid = (start + end) / 2;
    return findSum(arr, start, mid) + findSum(arr, mid + 1, end);
}
```

**Cevap**:
1. **Mevcut Analiz**:
   - Time Complexity: O(n), her eleman bir kez işleniyor
   - Space Complexity: O(log n), recursive call stack derinliği

2. **Problemler**:
   - Gereksiz recursive çağrılar
   - Stack space kullanımı

3. **Optimize Edilmiş Versiyon**:
```cpp
int findSum(vector<int>& arr) {
    int sum = 0;
    for(int num : arr) {
        sum += num;
    }
    return sum;
}
```

4. **Optimizasyon Sonuçları**:
   - Time Complexity: O(n)
   - Space Complexity: O(1)
   - Daha az memory kullanımı
   - Daha iyi cache performance

### S29 ⭐
**Soru**: Aşağıdaki algoritmaların average case time complexity'lerini belirtin ve nedenini açıklayın:
1. Insertion Sort
2. Merge Sort
3. Hash Table Search
4. Binary Search Tree Search

**Cevap**:
1. **Insertion Sort**: O(n²)
   - Her eleman için ortalama n/2 kaydırma
   - Input sıralamasından bağımsız

2. **Merge Sort**: O(n log n)
   - Her seviyede n eleman işlenir
   - log n seviye vardır
   - Input sıralamasından bağımsız

3. **Hash Table Search**: O(1)
   - İyi bir hash function ile
   - Load factor < 0.7 olduğunda
   - Collision resolution etkili ise

4. **Binary Search Tree Search**: O(log n)
   - Balanced tree varsayımı ile
   - Root'tan leaf'e ortalama log n adım
   - Perfect balance gerekmez

### S30 ⭐⭐
**Soru**: Aşağıdaki kod parçasının amortized time complexity'sini analiz edin:
```cpp
class DynamicArray {
    int* arr;
    int size;
    int capacity;
public:
    DynamicArray() : arr(new int[1]), size(0), capacity(1) {}
    
    void add(int x) {
        if(size == capacity) {
            capacity *= 2;
            int* temp = new int[capacity];
            for(int i = 0; i < size; i++)
                temp[i] = arr[i];
            delete[] arr;
            arr = temp;
        }
        arr[size++] = x;
    }
};
```

**Cevap**:
1. **Tek Operasyon Analizi**:
   - Normal durum (size < capacity): O(1)
   - Reallocation durumu: O(n)

2. **Amortized Analysis**:
   - n eleman eklemek için:
     - Reallocation: 1, 2, 4, 8, ..., n/2 elemanda
     - Toplam kopyalama: 1 + 2 + 4 + 8 + ... + n/2 ≈ n
     - Normal ekleme: n kez O(1)

3. **Sonuç**:
   - Toplam maliyet: O(n)
   - Amortized cost per operation: O(1)
   - Her add() operasyonu ortalamada O(1)
``` 