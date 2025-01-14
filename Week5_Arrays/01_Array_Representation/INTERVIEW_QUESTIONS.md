# Array Representation Mülakat Soruları

## Temel Kavramlar ve Tanımlamalar

### S1 ⭐
**Soru**: Array nedir ve neden kullanılır? Stack ve Heap'te array tanımlamanın farkları nelerdir?

**Cevap**: Array, aynı türden elemanları ardışık bellek konumlarında saklayan bir veri yapısıdır. 

Stack'te array tanımlama:
- Compile-time'da boyut bilinmelidir
- Otomatik bellek yönetimi
- Daha hızlı erişim
- Sınırlı boyut

Heap'te array tanımlama:
- Runtime'da boyut belirlenebilir
- Manuel bellek yönetimi gerektirir
- Daha büyük boyutlar mümkün
- Hafif performans kaybı

Örnek:
```cpp
// Stack array
int A[5] = {1, 2, 3, 4, 5};  

// Heap array
int* B = new int[5];  
```

### S2 ⭐
**Soru**: Aşağıdaki kod parçasının çıktısı ne olur ve neden?

```cpp
int arr[5] = {1, 2};
for(int i = 0; i < 5; i++)
    cout << arr[i] << " ";
```

**Cevap**: Çıktı: `1 2 0 0 0`

Çünkü:
- Array initialize edilirken eksik eleman verildiğinde, kalan elemanlar otomatik olarak 0 ile doldurulur
- İlk iki eleman verilen değerleri alır (1 ve 2)
- Kalan üç eleman 0 değerini alır

### S3 ⭐⭐
**Soru**: Array'lerde boundary checking nedir? C++'ta array bounds checking nasıl yapılır ve neden önemlidir?

**Cevap**: Boundary checking, array erişimlerinin geçerli indeks aralığında olup olmadığının kontrolüdür.

C++'ta varsayılan olarak boundary checking yapılmaz, bu da buffer overflow gibi hatalara yol açabilir:

```cpp
int arr[5] = {1, 2, 3, 4, 5};
arr[5] = 6;  // Buffer overflow - undefined behavior
```

Güvenli erişim için:
1. std::array kullanımı:
```cpp
std::array<int, 5> arr = {1, 2, 3, 4, 5};
arr.at(5);  // throws std::out_of_range exception
```

2. Manuel kontrol:
```cpp
if(index < 0 || index >= size) {
    throw std::out_of_range("Invalid index");
}
```

## 2D Arrays ve Memory Layout

### S4 ⭐
**Soru**: 2D array'leri heap'te tanımlamanın farklı yöntemleri nelerdir? Her birinin avantaj ve dezavantajları nedir?

**Cevap**: İki temel yöntem vardır:

1. Tek blok halinde (Contiguous memory):
```cpp
int* arr = new int[rows * cols];
// Erişim: arr[i * cols + j]
```
Avantajları:
- Daha az bellek overhead'i
- Cache-friendly
- Tek allocation/deallocation

Dezavantajları:
- Karmaşık indeksleme
- Boyut değişikliği zor

2. Pointer array'i:
```cpp
int** arr = new int*[rows];
for(int i = 0; i < rows; i++)
    arr[i] = new int[cols];
// Erişim: arr[i][j]
```
Avantajları:
- Kolay indeksleme
- Her satır bağımsız olarak yeniden boyutlandırılabilir

Dezavantajları:
- Daha fazla bellek overhead'i
- Cache performance düşük
- Çoklu allocation/deallocation

### S5 ⭐⭐
**Soru**: Row-major ve column-major düzeni nedir? Hangisi daha verimlidir ve neden?

**Cevap**: 
Row-major düzeni: Elemanlar satır satır saklanır
```
[1 2 3]    Memory: 1 2 3 4 5 6 7 8 9
[4 5 6]
[7 8 9]
```

Column-major düzeni: Elemanlar sütun sütun saklanır
```
[1 2 3]    Memory: 1 4 7 2 5 8 3 6 9
[4 5 6]
[7 8 9]
```

Row-major genellikle daha verimlidir çünkü:
1. Cache locality: Ardışık bellek erişimleri cache hit oranını artırır
2. Modern CPU'lar prefetching yapar
3. C++ row-major düzenini kullanır

Örnek performans karşılaştırması:
```cpp
// Row-major (daha hızlı)
for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
        sum += arr[i][j];

// Column-major (daha yavaş)
for(int j = 0; j < cols; j++)
    for(int i = 0; i < rows; i++)
        sum += arr[i][j];
```

## Memory Management ve Optimizasyon

### S6 ⭐⭐
**Soru**: Aşağıdaki kod parçasındaki memory leak'i bulun ve düzeltin:

```cpp
void processArray() {
    int* arr = new int[5];
    for(int i = 0; i < 5; i++)
        arr[i] = i;
        
    if(arr[0] == 0)
        return;  // Memory leak!
        
    delete[] arr;
}
```

**Cevap**: Bu kodda erken return durumunda memory leak oluşur. Düzeltmek için RAII veya smart pointer kullanılabilir:

```cpp
// Çözüm 1: unique_ptr kullanımı
void processArray() {
    std::unique_ptr<int[]> arr(new int[5]);
    for(int i = 0; i < 5; i++)
        arr[i] = i;
        
    if(arr[0] == 0)
        return;  // No leak
}

// Çözüm 2: try-finally benzeri yapı
void processArray() {
    int* arr = new int[5];
    bool success = false;
    
    try {
        for(int i = 0; i < 5; i++)
            arr[i] = i;
            
        if(arr[0] == 0) {
            delete[] arr;
            return;
        }
        
        success = true;
    }
    catch(...) {
        delete[] arr;
        throw;
    }
    
    if(!success)
        delete[] arr;
}
```

### S7 ⭐⭐
**Soru**: Array'lerde cache locality nedir ve performansı nasıl etkiler? Örnek üzerinden açıklayın.

**Cevap**: Cache locality, bellek erişimlerinin cache'te bulunma olasılığını ifade eder. İki türü vardır:

1. Temporal Locality: Yakın zamanda erişilen veriye tekrar erişilme olasılığı
2. Spatial Locality: Yakın bellek konumlarındaki veriye erişilme olasılığı

Örnek:
```cpp
const int size = 10000;
int arr[size][size];

// İyi cache locality (hızlı)
for(int i = 0; i < size; i++)
    for(int j = 0; j < size; j++)
        arr[i][j] = 0;

// Kötü cache locality (yavaş)
for(int j = 0; j < size; j++)
    for(int i = 0; i < size; i++)
        arr[i][j] = 0;
```

İlk döngü row-major düzeni kullanır ve cache line'ları etkin kullanır. İkinci döngü cache miss'lere neden olur.

## Özel Durumlar ve Teknikler

### S8 ⭐
**Soru**: Array'lerde shallow copy ve deep copy arasındaki fark nedir? Örnek üzerinden açıklayın.

**Cevap**: 
Shallow copy: Pointer kopyalama
- Aynı bellek bölgesini paylaşır
- Hızlıdır
- Tehlikelidir (double free)

Deep copy: Veri kopyalama
- Yeni bellek bölgesi oluşturur
- Yavaştır
- Güvenlidir

Örnek:
```cpp
// Shallow copy
int* arr1 = new int[5] {1, 2, 3, 4, 5};
int* arr2 = arr1;  // Shallow copy

// Deep copy
int* arr3 = new int[5];
for(int i = 0; i < 5; i++)
    arr3[i] = arr1[i];  // Deep copy

delete[] arr1;  // arr2 artık dangling pointer
delete[] arr3;  // Güvenli
```

### S9 ⭐⭐
**Soru**: Aşağıdaki kod parçasının çıktısı ne olur ve neden?

```cpp
int arr[3][3] = {{1, 2, 3}, {4, 5, 6}};
cout << sizeof(arr) << endl;
cout << sizeof(arr[0]) << endl;
cout << sizeof(arr[0][0]) << endl;
```

**Cevap**: 
```
36  // 3 * 3 * sizeof(int) = 3 * 3 * 4 = 36 bytes
12  // 3 * sizeof(int) = 3 * 4 = 12 bytes
4   // sizeof(int) = 4 bytes
```

Çünkü:
- arr: 3x3 int array = 36 bytes
- arr[0]: Bir satır = 3 int = 12 bytes
- arr[0][0]: Tek bir int = 4 bytes
- İkinci satırın eksik elemanları 0 ile doldurulur

### S10 ⭐⭐
**Soru**: C++'ta array decay nedir? Fonksiyonlara array geçirirken nelere dikkat edilmelidir?

**Cevap**: Array decay, array'in pointer'a dönüşmesidir. Fonksiyonlara array geçirildiğinde boyut bilgisi kaybolur.

```cpp
void printArray(int arr[]) {  // Aslında: int* arr
    // sizeof(arr) pointer size verir!
    cout << sizeof(arr) << endl;  // 8 (64-bit sistemde)
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    cout << sizeof(arr) << endl;  // 20 (5 * sizeof(int))
    printArray(arr);
}
```

Çözümler:
1. Boyutu parametre olarak geçmek:
```cpp
void printArray(int arr[], int size)
```

2. Reference kullanmak:
```cpp
template<size_t N>
void printArray(int (&arr)[N]) {
    cout << sizeof(arr) << endl;  // N * sizeof(int)
}
```

3. std::array kullanmak:
```cpp
void printArray(const std::array<int, 5>& arr) {
    cout << arr.size() << endl;
}
``` 

## Pratik Kullanım ve Optimizasyon

### S11 ⭐
**Soru**: C++'ta std::vector ile raw array arasındaki temel farklar nelerdir? Hangi durumlarda hangisini tercih etmeliyiz?

**Cevap**: std::vector ve raw array arasındaki temel farklar:

1. Boyut Yönetimi:
   - Raw array: Sabit boyut (stack) veya manuel yönetim (heap)
   - std::vector: Dinamik boyut, otomatik büyüme

2. Memory Management:
   - Raw array: Manuel (new/delete)
   - std::vector: Otomatik (RAII)

3. Güvenlik:
   - Raw array: Boundary checking yok
   - std::vector: at() metodu ile güvenli erişim

4. Fonksiyonellik:
   - Raw array: Temel operasyonlar
   - std::vector: push_back, insert, erase gibi zengin API

Tercih kriterleri:
```cpp
// Raw array tercih edilir:
int arr[1000];  // Stack'te küçük, sabit boyutlu array
int matrix[3][3];  // Çok boyutlu array

// std::vector tercih edilir:
std::vector<int> vec;  // Dinamik boyut
vec.push_back(42);  // Kolay ekleme
vec.resize(100);  // Boyut değiştirme
```

### S12 ⭐⭐
**Soru**: Aşağıdaki kod parçasında potansiyel performans sorunları nelerdir ve nasıl optimize edilebilir?

```cpp
void processMatrix(int** matrix, int rows, int cols) {
    int sum = 0;
    for(int j = 0; j < cols; j++)
        for(int i = 0; i < rows; i++)
            sum += matrix[i][j];
}
```

**Cevap**: Bu kodda birkaç performans sorunu var:

1. Cache locality sorunu:
   - Column-major erişim cache miss'lere neden olur
   - Row-major erişim daha verimli olur

2. Pointer indirection overhead:
   - Her erişimde iki pointer dereferencing
   - Tek boyutlu array daha verimli olur

Optimize edilmiş versiyon:
```cpp
// Versiyon 1: Loop order değişimi
void processMatrix(int** matrix, int rows, int cols) {
    int sum = 0;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            sum += matrix[i][j];
}

// Versiyon 2: Tek boyutlu array kullanımı
void processMatrix(int* matrix, int rows, int cols) {
    int sum = 0;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            sum += matrix[i * cols + j];
}
```

### S13 ⭐⭐
**Soru**: Array'lerde false sharing nedir ve nasıl önlenir? Örnek üzerinden açıklayın.

**Cevap**: False sharing, farklı thread'lerin aynı cache line üzerindeki farklı değişkenlere erişmesi sonucu oluşan performans sorunudur.

Örnek:
```cpp
struct Data {
    int x;  // Thread 1 tarafından kullanılır
    int y;  // Thread 2 tarafından kullanılır
};  // x ve y aynı cache line'da

// False sharing'e neden olan kod
void processData(Data& data) {
    thread t1([&]() {
        for(int i = 0; i < 1000000; i++)
            data.x++;
    });
    
    thread t2([&]() {
        for(int i = 0; i < 1000000; i++)
            data.y++;
    });
}
```

Çözüm - Padding kullanımı:
```cpp
struct Data {
    int x;
    char padding1[60];  // Cache line separation
    int y;
    char padding2[60];
};

// Alternatif çözüm - alignas
struct alignas(64) Data {
    int x;
    int y;
};
```

### S14 ⭐
**Soru**: C++'ta array initialization yöntemlerini karşılaştırın. Her birinin avantaj ve dezavantajları nelerdir?

**Cevap**: Array initialization yöntemleri:

1. Default Initialization:
```cpp
int arr[5];  // Değerler undefined
```
- Avantaj: Hızlı
- Dezavantaj: Güvensiz, undefined values

2. Zero Initialization:
```cpp
int arr[5] = {};  // Tüm elemanlar 0
```
- Avantaj: Güvenli, temiz başlangıç
- Dezavantaj: Gereksiz initialization overhead olabilir

3. Aggregate Initialization:
```cpp
int arr[] = {1, 2, 3, 4, 5};  // Size auto-deduced
int arr2[5] = {1, 2};  // Kalan elemanlar 0
```
- Avantaj: Açık ve okunabilir
- Dezavantaj: Tüm değerler compile-time'da bilinmeli

4. Uniform Initialization (C++11):
```cpp
int arr[5]{1, 2, 3, 4, 5};  // Modern syntax
```
- Avantaj: Consistent syntax
- Dezavantaj: Narrowing conversion'ları engeller

### S15 ⭐⭐
**Soru**: Aşağıdaki kod parçasında potansiyel sorunlar nelerdir ve nasıl düzeltilebilir?

```cpp
class Matrix {
    int* data;
    int rows, cols;
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int[rows * cols];
    }
    
    Matrix(const Matrix& other) {
        rows = other.rows;
        cols = other.cols;
        data = other.data;  // Shallow copy!
    }
    
    ~Matrix() {
        delete[] data;
    }
};
```

**Cevap**: Bu kodda birkaç ciddi sorun var:

1. Shallow copy sorunu:
   - Copy constructor pointer kopyalıyor
   - Double free ve dangling pointer'a neden olur

2. Assignment operator eksik:
   - Rule of Three/Five ihlali
   - Memory leak potansiyeli

3. Exception safety sorunu:
   - Constructor'da allocation başarısız olabilir
   - Exception durumunda cleanup yok

Düzeltilmiş versiyon:
```cpp
class Matrix {
    std::unique_ptr<int[]> data;
    int rows, cols;
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = std::make_unique<int[]>(rows * cols);
    }
    
    Matrix(const Matrix& other) 
        : rows(other.rows), cols(other.cols) {
        data = std::make_unique<int[]>(rows * cols);
        std::copy(other.data.get(), 
                 other.data.get() + rows * cols,
                 data.get());
    }
    
    Matrix& operator=(const Matrix& other) {
        if(this != &other) {
            Matrix temp(other);  // Copy-and-swap idiom
            std::swap(rows, temp.rows);
            std::swap(cols, temp.cols);
            std::swap(data, temp.data);
        }
        return *this;
    }
    
    // Move semantics
    Matrix(Matrix&&) noexcept = default;
    Matrix& operator=(Matrix&&) noexcept = default;
    
    // Destructor artık gerekli değil (unique_ptr kullanıldığı için)
};
``` 

## Modern C++ ve Pratik Uygulamalar

### S16 ⭐
**Soru**: std::span (C++20) nedir ve array'lerle nasıl kullanılır? Avantajları nelerdir?

**Cevap**: std::span, contiguous memory sequence'lar için non-owning view sağlayan bir container adapter'dır.

Avantajları:
1. Zero overhead abstraction
2. Array view için uniform interface
3. Boundary checking desteği
4. Raw array ve STL container'lar ile çalışabilme

Örnek kullanım:
```cpp
void processArray(std::span<int> arr) {
    for(int x : arr)
        std::cout << x << ' ';
}

int main() {
    int raw_array[] = {1, 2, 3, 4, 5};
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    
    // Hepsi aynı fonksiyonu kullanabilir
    processArray(raw_array);
    processArray(vec);
    processArray(arr);
    
    // Partial view
    processArray(std::span(raw_array, 3));  // İlk 3 eleman
}
```

### S17 ⭐⭐
**Soru**: Array'lerde SIMD (Single Instruction Multiple Data) optimizasyonu nasıl yapılır? Örnek üzerinden açıklayın.

**Cevap**: SIMD, aynı işlemi birden fazla veri üzerinde aynı anda yapabilme yeteneğidir.

```cpp
#include <immintrin.h>  // AVX intrinsics

// Normal versiyon
void addArrays(float* a, float* b, float* result, int size) {
    for(int i = 0; i < size; i++)
        result[i] = a[i] + b[i];
}

// SIMD versiyon (AVX)
void addArraysSIMD(float* a, float* b, float* result, int size) {
    int i = 0;
    
    // 8 float'ı aynı anda işle
    for(; i <= size - 8; i += 8) {
        __m256 va = _mm256_load_ps(&a[i]);
        __m256 vb = _mm256_load_ps(&b[i]);
        __m256 vresult = _mm256_add_ps(va, vb);
        _mm256_store_ps(&result[i], vresult);
    }
    
    // Kalan elemanları normal işle
    for(; i < size; i++)
        result[i] = a[i] + b[i];
}
```

Önemli noktalar:
1. Memory alignment önemli
2. Compiler optimizasyonları ile karşılaştırılmalı
3. Hardware support kontrol edilmeli

### S18 ⭐⭐
**Soru**: Array'lerde custom allocator kullanımı ne zaman gereklidir ve nasıl implement edilir? Örnek üzerinden açıklayın.

**Cevap**: Custom allocator'lar özel memory yönetimi gerektiren durumlarda kullanılır:
1. Memory pool implementation
2. Shared memory kullanımı
3. Özel alignment gereksinimleri
4. Performance optimization

Örnek implementation:
```cpp
template<typename T>
class PoolAllocator {
    static constexpr size_t POOL_SIZE = 1024;
    char pool[POOL_SIZE];
    size_t offset = 0;
    
public:
    using value_type = T;
    
    T* allocate(size_t n) {
        size_t size = n * sizeof(T);
        if(offset + size > POOL_SIZE)
            throw std::bad_alloc();
            
        T* result = reinterpret_cast<T*>(&pool[offset]);
        offset += size;
        return result;
    }
    
    void deallocate(T* p, size_t n) {
        // Basit implementasyon - no deallocation
    }
    
    template<typename U>
    struct rebind {
        using other = PoolAllocator<U>;
    };
};

// Kullanım
std::vector<int, PoolAllocator<int>> vec;
```

### S19 ⭐
**Soru**: Range-based for loop ile array'leri kullanırken dikkat edilmesi gereken noktalar nelerdir? Örnek üzerinden açıklayın.

**Cevap**: Range-based for loop kullanırken dikkat edilmesi gereken noktalar:

1. Array Decay:
```cpp
void processArray(int arr[]) {
    // HATALI: arr pointer'a decay olduğu için çalışmaz
    for(int x : arr) { }
}

// DOĞRU: Template kullanımı
template<size_t N>
void processArray(int (&arr)[N]) {
    for(int x : arr) { }
}
```

2. Reference kullanımı:
```cpp
// Kopyalama yapar
for(int x : arr) {
    x *= 2;  // Original array değişmez
}

// Reference ile değişiklik
for(int& x : arr) {
    x *= 2;  // Original array değişir
}
```

3. const correctness:
```cpp
// Read-only access
for(const int& x : arr) {
    std::cout << x;  // Değişiklik yapılamaz
}
```

4. Auto kullanımı:
```cpp
// Type deduction
for(const auto& x : arr) {
    // x'in tipi array elemanının tipi
}
```

### S20 ⭐⭐
**Soru**: Aşağıdaki kod parçasını modern C++ özellikleri kullanarak nasıl iyileştirebiliriz?

```cpp
class ImageProcessor {
    int* buffer;
    size_t size;
    
public:
    ImageProcessor(size_t n) : size(n) {
        buffer = new int[n];
    }
    
    void process() {
        for(size_t i = 0; i < size; i++) {
            if(buffer[i] < 0) buffer[i] = 0;
            buffer[i] = buffer[i] * 2;
        }
    }
    
    ~ImageProcessor() {
        delete[] buffer;
    }
};
```

**Cevap**: Modern C++ özellikleri kullanarak iyileştirilmiş versiyon:

```cpp
class ImageProcessor {
    std::vector<int> buffer;  // RAII için vector
    
public:
    explicit ImageProcessor(size_t n) 
        : buffer(n) {}  // Modern initialization
    
    void process() {
        // Algorithm ve lambda kullanımı
        std::transform(buffer.begin(), buffer.end(), 
                      buffer.begin(),
                      [](int x) {
                          return std::max(0, x) * 2;
                      });
        
        // Alternatif: range-based for
        for(auto& x : buffer) {
            x = std::max(0, x) * 2;
        }
    }
    
    // Rule of zero: No destructor needed
    
    // View için span kullanımı
    std::span<const int> getBuffer() const {
        return buffer;
    }
    
    // Optional olarak move semantics
    ImageProcessor(ImageProcessor&&) noexcept = default;
    ImageProcessor& operator=(ImageProcessor&&) noexcept = default;
    
    // Copy operations
    ImageProcessor(const ImageProcessor&) = default;
    ImageProcessor& operator=(const ImageProcessor&) = default;
};
```

İyileştirmeler:
1. RAII için std::vector kullanımı
2. Modern initialization syntax
3. Algorithm library kullanımı
4. Lambda expressions
5. Range-based for loop
6. std::span ile view semantics
7. Rule of zero
8. Move semantics
9. Explicit constructor
10. const correctness 

### S21 ⭐
**Soru**: Bir array'in duplicate elemanlarını nasıl bulursunuz? En verimli çözümü açıklayın.

**Cevap**: Duplicate elemanları bulmanın birkaç yöntemi vardır:

1. Naive Approach (O(n²)):
```cpp
void findDuplicates(int arr[], int n) {
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            if(arr[i] == arr[j])
                cout << arr[i] << " ";
}
```

2. Sorting Approach (O(n log n)):
```cpp
void findDuplicates(int arr[], int n) {
    sort(arr, arr + n);
    for(int i = 1; i < n; i++)
        if(arr[i] == arr[i-1])
            cout << arr[i] << " ";
}
```

3. Hash Table Approach (O(n)):
```cpp
void findDuplicates(int arr[], int n) {
    unordered_map<int, int> freq;
    for(int i = 0; i < n; i++) {
        freq[arr[i]]++;
        if(freq[arr[i]] == 2)
            cout << arr[i] << " ";
    }
}
```

En verimli çözüm Hash Table yaklaşımıdır (O(n) time, O(n) space).

### S22 ⭐
**Soru**: Bir array'i in-place olarak nasıl reverse edersiniz? Ekstra bellek kullanmadan çözümü açıklayın.

**Cevap**: Two-pointer yaklaşımı kullanarak O(n) time ve O(1) space complexity ile çözülebilir:

```cpp
void reverseArray(int arr[], int n) {
    int start = 0;
    int end = n - 1;
    
    while(start < end) {
        // Swap without extra variable
        arr[start] = arr[start] ^ arr[end];
        arr[end] = arr[start] ^ arr[end];
        arr[start] = arr[start] ^ arr[end];
        
        start++;
        end--;
    }
}

// Alternatif swap yöntemi:
void reverseArray(int arr[], int n) {
    for(int i = 0; i < n/2; i++) {
        swap(arr[i], arr[n-1-i]);
    }
}
```

### S23 ⭐⭐
**Soru**: Bir array'de missing number'ı nasıl bulursunuz? Array 1'den n'e kadar sayıları içeriyor ve bir sayı eksik. En optimal çözümü açıklayın.

**Cevap**: Bu problemi çözmenin birkaç yolu var:

1. XOR Approach (En optimal - O(n) time, O(1) space):
```cpp
int findMissing(int arr[], int n) {
    int xor1 = 0, xor2 = 0;
    
    for(int i = 0; i < n-1; i++) {
        xor2 = xor2 ^ arr[i];  // Array elemanları
        xor1 = xor1 ^ (i + 1); // 1'den n-1'e
    }
    xor1 = xor1 ^ n;  // Son elemanı da ekle
    
    return (xor1 ^ xor2);
}
```

2. Sum Approach (Overflow riski var):
```cpp
int findMissing(int arr[], int n) {
    int expectedSum = (n * (n + 1)) / 2;
    int actualSum = 0;
    for(int i = 0; i < n-1; i++)
        actualSum += arr[i];
    return expectedSum - actualSum;
}
```

### S24 ⭐⭐
**Soru**: Bir array'de majority element'i (n/2'den fazla tekrar eden eleman) nasıl bulursunuz? Boyer-Moore Voting Algorithm'ini açıklayın.

**Cevap**: Boyer-Moore Voting Algorithm O(n) time ve O(1) space complexity sağlar:

```cpp
int findMajority(int arr[], int n) {
    int candidate = arr[0];
    int count = 1;
    
    // Finding candidate
    for(int i = 1; i < n; i++) {
        if(count == 0) {
            candidate = arr[i];
            count = 1;
        }
        else if(arr[i] == candidate)
            count++;
        else
            count--;
    }
    
    // Verifying candidate
    count = 0;
    for(int i = 0; i < n; i++)
        if(arr[i] == candidate)
            count++;
            
    return count > n/2 ? candidate : -1;
}
```

### S25 ⭐
**Soru**: Bir array'i rotate etmenin en verimli yolu nedir? Örneğin, [1,2,3,4,5] array'ini 2 adım sağa rotate ederek [4,5,1,2,3] elde etmek istiyoruz.

**Cevap**: Reversal Algorithm kullanarak O(n) time ve O(1) space complexity ile çözülebilir:

```cpp
void reverse(int arr[], int start, int end) {
    while(start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

void rotateArray(int arr[], int n, int k) {
    k = k % n;  // k > n durumu için
    
    // Son k elemanı reverse et
    reverse(arr, n-k, n-1);
    
    // İlk n-k elemanı reverse et
    reverse(arr, 0, n-k-1);
    
    // Tüm array'i reverse et
    reverse(arr, 0, n-1);
}
```

### S26 ⭐⭐
**Soru**: Bir array'de subarray'lerin maksimum toplamını bulan Kadane's Algorithm'i açıklayın ve implement edin.

**Cevap**: Kadane's Algorithm, O(n) time complexity ile maximum subarray sum'ı bulur:

```cpp
int maxSubArraySum(int arr[], int n) {
    int maxSoFar = arr[0];
    int currMax = arr[0];
    
    for(int i = 1; i < n; i++) {
        currMax = max(arr[i], currMax + arr[i]);
        maxSoFar = max(maxSoFar, currMax);
    }
    
    return maxSoFar;
}

// Subarray'in kendisini de bulmak için:
void maxSubArray(int arr[], int n) {
    int maxSoFar = arr[0];
    int currMax = arr[0];
    int start = 0, end = 0, s = 0;
    
    for(int i = 1; i < n; i++) {
        if(arr[i] > currMax + arr[i]) {
            currMax = arr[i];
            s = i;
        } else {
            currMax = currMax + arr[i];
        }
        
        if(currMax > maxSoFar) {
            maxSoFar = currMax;
            start = s;
            end = i;
        }
    }
    
    cout << "Maximum sum: " << maxSoFar << endl;
    cout << "Subarray: ";
    for(int i = start; i <= end; i++)
        cout << arr[i] << " ";
}
```

### S27 ⭐⭐
**Soru**: Bir sorted array'de verilen bir sayının ilk ve son occurrence'ını bulan binary search implementasyonunu yazın.

**Cevap**: İki ayrı binary search ile O(log n) time complexity'de çözülebilir:

```cpp
pair<int,int> findFirstAndLast(int arr[], int n, int x) {
    auto findFirst = [&](int x) {
        int low = 0, high = n - 1;
        int result = -1;
        
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(arr[mid] == x) {
                result = mid;
                high = mid - 1;  // Sol tarafta ara
            }
            else if(arr[mid] > x)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return result;
    };
    
    auto findLast = [&](int x) {
        int low = 0, high = n - 1;
        int result = -1;
        
        while(low <= high) {
            int mid = low + (high - low)/2;
            if(arr[mid] == x) {
                result = mid;
                low = mid + 1;  // Sağ tarafta ara
            }
            else if(arr[mid] > x)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return result;
    };
    
    return {findFirst(x), findLast(x)};
}
```

### S28 ⭐
**Soru**: İki sorted array'i merge eden bir fonksiyon yazın. Extra space kullanmadan (in-place) nasıl yapılabilir?

**Cevap**: İki yaklaşım gösterelim:

1. Extra space kullanan basit çözüm (O(n+m) space):
```cpp
void merge(int arr1[], int arr2[], int n, int m) {
    int i = 0, j = 0, k = 0;
    int temp[n+m];
    
    while(i < n && j < m) {
        if(arr1[i] <= arr2[j])
            temp[k++] = arr1[i++];
        else
            temp[k++] = arr2[j++];
    }
    
    while(i < n) temp[k++] = arr1[i++];
    while(j < m) temp[k++] = arr2[j++];
    
    // Copy back
    for(i = 0; i < n+m; i++)
        arr1[i] = temp[i];
}
```

2. In-place çözüm (O(1) extra space):
```cpp
void merge(int arr1[], int arr2[], int n, int m) {
    // Compare elements from end of first array
    // and start of second array
    for(int i = n-1; i >= 0; i--) {
        int j, last = arr1[n-1];
        for(j = m-2; j >= 0 && arr2[j] > arr1[i]; j--)
            arr2[j+1] = arr2[j];
            
        if(j != m-2 || last > arr1[i]) {
            arr2[j+1] = arr1[i];
            arr1[i] = last;
        }
    }
}
```

### S29 ⭐⭐
**Soru**: Bir array'de equilibrium index'i nasıl bulursunuz? (Equilibrium index: sol tarafındaki elemanların toplamı sağ tarafındaki elemanların toplamına eşit olan index)

**Cevap**: Prefix sum yaklaşımı ile O(n) time complexity'de çözülebilir:

```cpp
int findEquilibrium(int arr[], int n) {
    int totalSum = 0;
    int leftSum = 0;
    
    // Calculate total sum
    for(int i = 0; i < n; i++)
        totalSum += arr[i];
    
    for(int i = 0; i < n; i++) {
        // Right sum = totalSum - leftSum - current element
        int rightSum = totalSum - leftSum - arr[i];
        
        if(leftSum == rightSum)
            return i;
            
        leftSum += arr[i];
    }
    
    return -1;  // No equilibrium index found
}
```

### S30 ⭐⭐
**Soru**: Bir array'de peak element'i (komşularından büyük olan element) binary search ile nasıl bulursunuz?

**Cevap**: Binary search kullanarak O(log n) time complexity'de çözülebilir:

```cpp
int findPeak(int arr[], int n) {
    int low = 0;
    int high = n - 1;
    
    while(low <= high) {
        int mid = low + (high - low)/2;
        
        // Compare middle element with its neighbors
        if((mid == 0 || arr[mid-1] <= arr[mid]) &&
           (mid == n-1 || arr[mid+1] <= arr[mid]))
            return mid;
            
        // If left neighbor is greater, peak must be on left side
        else if(mid > 0 && arr[mid-1] > arr[mid])
            high = mid - 1;
            
        // If right neighbor is greater, peak must be on right side
        else
            low = mid + 1;
    }
    
    return -1;  // No peak element
}
```

Bu implementasyon:
1. Array'in kenar durumlarını kontrol eder
2. Binary search mantığını kullanarak peak element'i bulur
3. O(log n) time complexity sağlar 