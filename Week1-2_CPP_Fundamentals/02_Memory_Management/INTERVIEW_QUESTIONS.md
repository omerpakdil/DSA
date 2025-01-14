# C++ Memory Management Mülakat Soruları

## İçindekiler
1. [Stack vs Heap](#stack-vs-heap)
2. [Memory Leaks](#memory-leaks)
3. [Smart Pointers](#smart-pointers)
4. [RAII Pattern](#raii-pattern)
5. [Kod Çıktı Soruları](#kod-çıktı-soruları)

## Stack vs Heap

### S1: Stack ve Heap memory arasındaki temel farklar nelerdir?
**Cevap:**
1. **Yönetim:**
   - Stack: Otomatik (scope-based)
   - Heap: Manuel (programmer-managed)

2. **Boyut:**
   - Stack: Sınırlı (genelde birkaç MB)
   - Heap: RAM ile sınırlı

3. **Hız:**
   - Stack: Daha hızlı (LIFO yapısı)
   - Heap: Daha yavaş (fragmentation olabilir)

4. **Kullanım:**
```cpp
void example() {
    int stackVar = 42;           // Stack allocation
    int* heapVar = new int(42);  // Heap allocation
    delete heapVar;              // Manual cleanup
}  // stackVar otomatik cleanup
```

### S2: Aşağıdaki kodun çıktısı ne olur?
```cpp
class MyClass {
public:
    MyClass() { std::cout << "C"; }
    ~MyClass() { std::cout << "D"; }
};

void foo() {
    MyClass stackObj;            // Stack object
    MyClass* heapObj = new MyClass();  // Heap object
}  // Memory leak!

int main() {
    foo();
    std::cout << "E";
    return 0;
}
```
**Cevap:** `CCDE`
- İlk C: stackObj constructor
- İkinci C: heapObj constructor
- D: stackObj destructor (otomatik)
- E: main'deki output
- heapObj destructor'ı hiç çağrılmaz (memory leak)

### S3: Stack overflow nasıl oluşur? Bir örnek veriniz.
**Cevap:** Genelde recursive fonksiyonlarda veya çok büyük stack allocation'larda oluşur:
```cpp
void recursiveFunction(int n) {
    char largeArray[1000000];  // Büyük stack allocation
    recursiveFunction(n + 1);   // Sonsuz recursion
}

// Ya da:
void stackOverflow() {
    int arr[1000000];  // Stack'te çok büyük array
}
```

## Memory Leaks

### S4: Memory leak'in oluşabileceği durumlar nelerdir?
**Cevap:**
1. Delete unutulması
2. Exception durumunda cleanup yapılmaması
3. Circular references
4. Pointer reassignment

Örnek:
```cpp
void leakExamples() {
    // 1. Basic leak
    int* p1 = new int(42);  // Leak: delete unutuldu
    
    // 2. Exception leak
    try {
        int* p2 = new int(42);
        throw std::runtime_error("Error");
        delete p2;  // Never reached
    } catch(...) {}
    
    // 3. Pointer reassignment
    int* p3 = new int(1);
    p3 = new int(2);  // İlk allocation leak oldu
}
```

### S5: Aşağıdaki kodda kaç memory leak vardır?
```cpp
class Resource {
    int* data;
public:
    Resource() : data(new int(0)) {}
    ~Resource() { delete data; }
    void update(int val) {
        data = new int(val);  // Leak 1
    }
    Resource(const Resource& other) {
        data = other.data;    // Leak 2
    }
};

int main() {
    Resource r1;
    r1.update(42);
    Resource r2 = r1;  // Leak 3
    return 0;
}
```
**Cevap:** 3 leak var:
1. update'te eski data delete edilmiyor
2. Copy constructor shallow copy yapıyor
3. Destructor çağrıldığında aynı pointer iki kez delete ediliyor

### S6: RAII kullanarak memory leak nasıl önlenir?
**Cevap:**
```cpp
class RAIIResource {
    int* data;
public:
    RAIIResource(int val) : data(new int(val)) {}
    ~RAIIResource() { delete data; }
    
    // Copy constructor
    RAIIResource(const RAIIResource& other) : data(new int(*other.data)) {}
    
    // Copy assignment
    RAIIResource& operator=(const RAIIResource& other) {
        if (this != &other) {
            int* temp = new int(*other.data);
            delete data;
            data = temp;
        }
        return *this;
    }
};
```

## Smart Pointers

### S7: weak_ptr ne zaman kullanılmalıdır?
**Cevap:** Circular reference'ları önlemek için kullanılır:
```cpp
class Node {
    std::shared_ptr<Node> next;  // Circular reference olabilir
    std::weak_ptr<Node> prev;    // Circular reference önlenir
};

void example() {
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    
    node1->next = node2;
    node2->prev = node1;  // weak_ptr kullanıldığı için leak olmaz
}
```

### S8: Aşağıdaki kodun çıktısı ne olur?
```cpp
void checkPointer(std::weak_ptr<int> wp) {
    if (auto sp = wp.lock()) {
        std::cout << *sp;
    } else {
        std::cout << "X";
    }
}

int main() {
    std::weak_ptr<int> wp;
    {
        auto sp = std::make_shared<int>(42);
        wp = sp;
        checkPointer(wp);  // 42
    }  // sp destroyed
    checkPointer(wp);  // X
    return 0;
}
```
**Cevap:** `42X`
- İlk checkPointer: shared_ptr hala yaşıyor
- İkinci checkPointer: shared_ptr destroyed

### S9: enable_shared_from_this ne için kullanılır?
**Cevap:** Bir class'ın kendi this pointer'ını shared_ptr olarak paylaşması için:
```cpp
class Widget : public std::enable_shared_from_this<Widget> {
public:
    std::shared_ptr<Widget> getShared() {
        return shared_from_this();
    }
};

void example() {
    auto w = std::make_shared<Widget>();
    auto w2 = w->getShared();  // Safe sharing
}
```

## RAII Pattern

### S10: RAII pattern'i mutex için nasıl kullanılır?
**Cevap:**
```cpp
class LockGuard {
    std::mutex& mtx;
public:
    LockGuard(std::mutex& m) : mtx(m) {
        mtx.lock();
    }
    ~LockGuard() {
        mtx.unlock();
    }
};

void threadSafeFunction() {
    static std::mutex mtx;
    LockGuard guard(mtx);
    // Critical section
}  // Mutex otomatik unlock edilir
```

## Kod Çıktı Soruları

### S11: Aşağıdaki kodun çıktısı ne olur?
```cpp
class Counter {
public:
    Counter() { std::cout << "C"; }
    ~Counter() { std::cout << "D"; }
};

void foo() {
    static Counter c1;         // Static storage
    Counter c2;               // Automatic storage
    Counter* c3 = new Counter(); // Dynamic storage
}

int main() {
    std::cout << "M";
    foo();
    std::cout << "E";
    return 0;
}
```
**Cevap:** `MCCDME`
- M: main başlangıç
- C: c1 constructor (static, program sonunda destroy edilir)
- C: c2 constructor
- D: c2 destructor
- M: main'deki output
- E: program sonunda c1 destructor

### S12: Aşağıdaki kodun problemi nedir?
```cpp
class Base {
public:
    Base() { std::cout << "B"; }
    ~Base() { std::cout << "~B"; }
};

class Derived : public Base {
    int* ptr = new int(42);
public:
    Derived() { std::cout << "D"; }
    ~Derived() { 
        std::cout << "~D";
        delete ptr;
    }
};

int main() {
    Base* b = new Derived();
    delete b;  // Memory leak!
    return 0;
}
```
**Cevap:** Virtual destructor eksik. Derived class destructor'ı çağrılmaz.
Çözüm:
```cpp
class Base {
public:
    virtual ~Base() { std::cout << "~B"; }
};
```

### S13: Aşağıdaki kodun çıktısı ne olur?
```cpp
int main() {
    std::shared_ptr<int> sp1(new int(1));
    std::shared_ptr<int> sp2(new int(2));
    std::cout << sp1.use_count() << sp2.use_count() << " ";
    
    sp2 = sp1;
    std::cout << sp1.use_count() << sp2.use_count();
    return 0;
}
```
**Cevap:** `11 22`
- Başlangıçta her pointer'ın bir referansı var
- sp2 = sp1 sonrası iki pointer aynı yeri gösterir ve ref count 2 olur

### S14: Placement new nedir ve ne için kullanılır?
**Cevap:** Belirli bir bellek alanında constructor çağırmak için kullanılır:
```cpp
class Object {
public:
    Object() { std::cout << "C"; }
    ~Object() { std::cout << "D"; }
};

int main() {
    alignas(Object) char buffer[sizeof(Object)];
    
    Object* obj = new (&buffer) Object();  // Placement new
    obj->~Object();  // Manuel destructor call
    return 0;
}
```

### S15: Custom deleter nasıl kullanılır?
**Cevap:**
```cpp
struct FileDeleter {
    void operator()(FILE* fp) {
        if (fp) fclose(fp);
    }
};

void example() {
    // Custom deleter ile file handle yönetimi
    std::unique_ptr<FILE, FileDeleter> file(fopen("test.txt", "r"));
    
    // Lambda ile custom deleter
    auto deleter = [](int* p) {
        std::cout << "Deleting: " << *p;
        delete p;
    };
    std::shared_ptr<int> ptr(new int(42), deleter);
}  // Automatic cleanup with custom deletion
```