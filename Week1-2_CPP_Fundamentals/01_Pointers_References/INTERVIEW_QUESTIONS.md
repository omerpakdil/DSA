# C++ Pointers ve References Mülakat Soruları

## İçindekiler
1. [Temel Kavramlar](#temel-kavramlar)
2. [Pointer Aritmetiği](#pointer-aritmetiği)
3. [References](#references)
4. [Smart Pointers](#smart-pointers)
5. [Kod Çıktı Soruları](#kod-çıktı-soruları)

## Temel Kavramlar

### S1: Pointer ve reference arasındaki temel farklar nelerdir?
**Cevap:**
1. Pointer null olabilir, reference olamaz
2. Pointer reassign edilebilir, reference edilemez
3. Pointer aritmetiği yapılabilir, reference'ta yapılamaz
4. Reference declare edildiğinde initialize edilmeli, pointer edilmeyebilir

Örnek:
```cpp
int x = 5;
int* ptr = nullptr;  // Legal
int& ref = x;        // Must initialize
ptr = &x;           // Legal
// ref = &x;        // Illegal
```

### S2: Dangling pointer nedir? Nasıl önlenir?
**Cevap:** Dangling pointer, işaret ettiği bellek alanı serbest bırakılmış pointer'dır.
```cpp
int* createDangling() {
    int local = 5;
    return &local;  // Dangling pointer! local değişken scope dışında yok olur
}

// Çözüm 1: Smart pointer kullanmak
std::unique_ptr<int> safe(new int(5));

// Çözüm 2: Bellek yönetimini dikkatli yapmak
int* safe = new int(5);
delete safe;
safe = nullptr;  // Reset pointer after delete
```

### S3: Aşağıdaki kodun çıktısı ne olur?
```cpp
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int* p1 = arr;
    int* p2 = &arr[2];
    
    std::cout << *p1 << " ";
    std::cout << p2 - p1 << " ";
    std::cout << *(p1 + 2);
    return 0;
}
```
**Cevap:** `1 2 3`
- *p1: arr[0] yani 1
- p2 - p1: pointer farkı 2 eleman
- *(p1 + 2): arr[2] yani 3

## Pointer Aritmetiği

### S4: Aşağıdaki kodda hata nedir?
```cpp
int main() {
    int arr[] = {1, 2, 3};
    int* ptr = arr;
    
    for(int i = 0; i <= 3; i++) {  // Hata!
        std::cout << *ptr++ << " ";
    }
    return 0;
}
```
**Cevap:** Buffer overflow. Array bounds aşılıyor. Son iterasyonda geçersiz bellek erişimi var.

### S5: void pointer nedir ve ne için kullanılır?
**Cevap:** void pointer herhangi bir türdeki verinin adresini tutabilir, ancak dereferencing için cast edilmesi gerekir.
```cpp
void* vptr = nullptr;
int x = 42;
vptr = &x;
// *vptr;           // Error: void* dereferencing yapılamaz
int* iptr = static_cast<int*>(vptr);  // Cast gerekli
std::cout << *iptr;  // OK: 42
```

## References

### S6: Reference collapsing kuralları nelerdir?
**Cevap:**
- T& & → T&
- T& && → T&
- T&& & → T&
- T&& && → T&&

Örnek:
```cpp
template<typename T>
void foo(T&& x) {  // Universal reference
    using Type1 = T&;          // T& için T&
    using Type2 = T&&;         // T& için T&, T&& için T&&
    using Type3 = Type1&&;     // Her zaman T&
}
```

### S7: Aşağıdaki kodun çıktısı ne olur?
```cpp
void modifyValue(int& x) { x *= 2; }
void modifyPointer(int* p) { *p += 3; }

int main() {
    int num = 10;
    int& ref = num;
    int* ptr = &num;
    
    modifyValue(ref);
    modifyPointer(ptr);
    std::cout << num;
    return 0;
}
```
**Cevap:** `23`
- modifyValue: 10 * 2 = 20
- modifyPointer: 20 + 3 = 23

### S8: Rvalue reference ne zaman kullanılır?
**Cevap:** Move semantics ve perfect forwarding için kullanılır:
```cpp
class String {
    char* data;
public:
    // Move constructor
    String(String&& other) noexcept {
        data = other.data;
        other.data = nullptr;  // Transfer ownership
    }
};

// Perfect forwarding
template<typename T>
void wrapper(T&& arg) {
    foo(std::forward<T>(arg));
}
```

## Smart Pointers

### S9: unique_ptr ve shared_ptr arasındaki farklar nelerdir?
**Cevap:**
```cpp
// unique_ptr: Tek sahiplik
std::unique_ptr<int> up1(new int(42));
// std::unique_ptr<int> up2 = up1;  // Error: Copy constructor deleted
auto up2 = std::move(up1);          // OK: Transfer ownership

// shared_ptr: Paylaşımlı sahiplik
std::shared_ptr<int> sp1(new int(42));
auto sp2 = sp1;  // OK: Reference count artırılır
std::cout << sp1.use_count();  // 2
```

### S10: Aşağıdaki kodun problemi nedir?
```cpp
class Resource {
public:
    Resource() { std::cout << "Create"; }
    ~Resource() { std::cout << "Destroy"; }
};

void foo() {
    Resource* ptr = new Resource();
    throw std::runtime_error("Error");
    delete ptr;  // Never reached!
}

int main() {
    try {
        foo();
    } catch(...) {}
    return 0;
}
```
**Cevap:** Memory leak. Exception durumunda delete çağrılmaz. Çözüm:
```cpp
void foo() {
    std::unique_ptr<Resource> ptr(new Resource());
    throw std::runtime_error("Error");
}  // ptr otomatik delete edilir
```

## Kod Çıktı Soruları

### S11: Aşağıdaki kodun çıktısı ne olur?
```cpp
int main() {
    int x = 10;
    int& ref = x;
    int* ptr = &x;
    
    ++ref;
    ++*ptr;
    ++ptr;  // ptr farklı yere işaret eder
    ++*ptr; // Undefined behavior!
    
    std::cout << x;
    return 0;
}
```
**Cevap:** `12`
- ++ref: x = 11
- ++*ptr: x = 12
- ++ptr: ptr farklı adrese gider
- ++*ptr: Undefined behavior!

### S12: Aşağıdaki kodun çıktısı ne olur?
```cpp
void foo(int*& p) {  // Reference to pointer
    int x = 42;
    p = &x;  // Dangling reference!
}

int main() {
    int* ptr = nullptr;
    foo(ptr);
    std::cout << *ptr;  // Undefined behavior
    return 0;
}
```
**Cevap:** Undefined behavior. Local değişkenin adresi return ediliyor.

### S13: const ile pointer kullanımındaki farklar nelerdir?
**Cevap:**
```cpp
int value = 42;
const int* p1 = &value;      // Pointer to const int
int const* p2 = &value;      // Aynı şey
int* const p3 = &value;      // Const pointer to int
const int* const p4 = &value;  // Const pointer to const int

// *p1 = 43;    // Error: Cannot modify through p1
p1 = nullptr;   // OK: p1 can be changed
*p3 = 43;       // OK: Can modify through p3
// p3 = nullptr;  // Error: p3 cannot be changed
```

### S14: Aşağıdaki kodun çıktısı ne olur?
```cpp
int main() {
    int arr[] = {1, 2, 3};
    int* p = arr;
    int (&ref)[3] = arr;  // Reference to array
    
    ++p;
    std::cout << *p << " ";
    std::cout << ref[0] << " ";
    std::cout << arr[1];
    return 0;
}
```
**Cevap:** `2 1 2`
- *p: arr[1] yani 2 (pointer increment edildi)
- ref[0]: arr[0] yani 1
- arr[1]: 2

### S15: Function pointer syntax'ı nasıldır?
**Cevap:**
```cpp
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main() {
    // Function pointer declaration
    int (*operation)(int, int);
    
    operation = add;
    std::cout << operation(5, 3) << " ";  // 8
    
    operation = subtract;
    std::cout << operation(5, 3);         // 2
    return 0;
}
```
``` 