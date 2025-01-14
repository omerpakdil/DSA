# C++ OOP Mülakat Soruları

## İçindekiler
1. [Temel OOP Kavramları](#temel-oop-kavramları)
2. [Inheritance](#inheritance)
3. [Polymorphism](#polymorphism)
4. [Encapsulation](#encapsulation)
5. [Abstraction](#abstraction)
6. [Constructor ve Destructor](#constructor-ve-destructor)
7. [Virtual Functions](#virtual-functions)
8. [Kod Çıktı Soruları](#kod-çıktı-soruları)

## Temel OOP Kavramları

### S1: Object-Oriented Programming nedir ve neden kullanılır?
**Cevap:** OOP, programlama mantığını gerçek hayattaki nesnelere benzer şekilde modelleyen bir programlama paradigmasıdır. Temel avantajları:
- Kod tekrarını azaltır (reusability)
- Kodun bakımını kolaylaştırır (maintainability)
- Veri güvenliğini artırır (data security)
- Karmaşık projeleri yönetilebilir parçalara böler

### S2: Class ve Object arasındaki fark nedir?
**Cevap:** Class bir şablondur (template), Object ise bu şablondan oluşturulan somut örnektir (instance).
```cpp
class Car {  // Class tanımı
    string brand;
    string model;
};

Car myCar;   // Object oluşturma
```

### S3: Struct ve Class arasındaki fark nedir?
**Cevap:** 
- Struct'ta varsayılan erişim belirteci (access specifier) `public`, Class'ta `private`'tır
- Struct genellikle sadece veri tutmak için kullanılır (POD - Plain Old Data)
- Class daha karmaşık davranışları ve inheritance yapılarını modellemek için kullanılır

## Inheritance

### S4: Multiple inheritance nedir ve hangi sorunlara yol açabilir?
**Cevap:** Bir class'ın birden fazla base class'tan türetilmesidir. Diamond problem en önemli sorunudur:
```cpp
class A { public: void show() {} };
class B : public A {};
class C : public A {};
class D : public B, public C {};  // Diamond problem
```

### S5: Virtual inheritance ne zaman kullanılır?
**Cevap:** Diamond problem'i çözmek için kullanılır:
```cpp
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};  // Artık sorun yok
```

## Polymorphism

### S6: Runtime ve Compile-time polymorphism arasındaki fark nedir?
**Cevap:**
- **Compile-time (Static) Polymorphism:** Function overloading ve operator overloading ile sağlanır
- **Runtime (Dynamic) Polymorphism:** Virtual functions ve inheritance ile sağlanır

Örnek:
```cpp
// Compile-time polymorphism
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    double add(double a, double b) { return a + b; }
};

// Runtime polymorphism
class Animal {
public:
    virtual void makeSound() = 0;
};

class Dog : public Animal {
public:
    void makeSound() override { std::cout << "Hav!"; }
};
```

### S7: Pure virtual function nedir ve ne için kullanılır?
**Cevap:** Sadece bildirimi yapılan, implementasyonu derived class'lara bırakılan fonksiyonlardır. Abstract class oluşturmak için kullanılır:
```cpp
class Shape {
public:
    virtual double area() = 0;  // Pure virtual function
};
```

## Encapsulation

### S8: Encapsulation nedir ve nasıl sağlanır?
**Cevap:** Veriyi ve bu veriyi işleyen metodları bir arada tutup, dış dünyadan erişimi kontrol etme mekanizmasıdır.
```cpp
class BankAccount {
private:
    double balance;  // Veri gizleme
public:
    void deposit(double amount) {  // Kontrollü erişim
        if (amount > 0) balance += amount;
    }
};
```

### S9: Access specifier'lar nelerdir ve farkları nedir?
**Cevap:**
- `private`: Sadece class içinden erişilebilir
- `protected`: Class içinden ve derived class'lardan erişilebilir
- `public`: Her yerden erişilebilir

## Constructor ve Destructor

### S10: Copy constructor ve move constructor arasındaki fark nedir?
**Cevap:**
```cpp
class MyClass {
public:
    // Copy constructor - Deep copy yapar
    MyClass(const MyClass& other) {
        // Kaynakları kopyala
    }
    
    // Move constructor - Kaynakları transfer eder
    MyClass(MyClass&& other) noexcept {
        // Kaynakları taşı
        // other'ı boşalt
    }
};
```

### S11: Aşağıdaki kodun çıktısı ne olur?
```cpp
class Test {
public:
    Test() { std::cout << "Constructor"; }
    Test(const Test&) { std::cout << "Copy"; }
    ~Test() { std::cout << "Destructor"; }
};

void foo() {
    Test t1;
    Test t2 = t1;
}

int main() {
    foo();
    return 0;
}
```
**Cevap:** `Constructor Copy Destructor Destructor`

## Virtual Functions

### S12: Virtual destructor neden gereklidir?
**Cevap:** Base class pointer üzerinden derived class object'i silinirken, derived class destructor'ının çağrılmasını sağlar:
```cpp
class Base {
public:
    virtual ~Base() = default;  // Virtual destructor
};

class Derived : public Base {
    int* ptr;
public:
    ~Derived() { delete ptr; }  // Memory leak olmaz
};
```

### S13: Virtual function table (vtable) nedir?
**Cevap:** Compiler tarafından oluşturulan, virtual function'ların adreslerini tutan bir tablodur. Her virtual function içeren class için bir vtable oluşturulur.

## Kod Çıktı Soruları

### S14: Aşağıdaki kodun çıktısı ne olur?
```cpp
class Base {
public:
    virtual void print() { std::cout << "Base"; }
};

class Derived : public Base {
public:
    void print() { std::cout << "Derived"; }
};

int main() {
    Base* ptr = new Derived();
    ptr->print();
    delete ptr;
    return 0;
}
```
**Cevap:** `Derived` (Runtime polymorphism örneği)

### S15: Bu kodda sorun nedir?
```cpp
class Resource {
    int* data;
public:
    Resource() : data(new int[100]) {}
    Resource(const Resource& other) {
        data = other.data;  // Shallow copy!
    }
    ~Resource() {
        delete[] data;
    }
};
```
**Cevap:** Shallow copy nedeniyle double free problemi oluşur. Copy constructor'da deep copy yapılmalıdır:
```cpp
Resource(const Resource& other) {
    data = new int[100];
    std::copy(other.data, other.data + 100, data);
}
```

### S16: RAII prensibi nedir ve neden önemlidir?
**Cevap:** Resource Acquisition Is Initialization, kaynakların constructor'da alınıp destructor'da serbest bırakılması prensibidir. Exception safety sağlar:
```cpp
class FileHandler {
    FILE* file;
public:
    FileHandler(const char* filename) {
        file = fopen(filename, "r");  // Resource acquisition
    }
    ~FileHandler() {
        if (file) fclose(file);       // Resource release
    }
};
```

### S17: Smart pointer'lar neden kullanılır ve türleri nelerdir?
**Cevap:**
- `std::unique_ptr`: Tek sahiplik, otomatik memory yönetimi
- `std::shared_ptr`: Paylaşımlı sahiplik, reference counting
- `std::weak_ptr`: Circular reference'ları önlemek için

Örnek:
```cpp
void example() {
    auto ptr1 = std::make_unique<int>(42);  // Unique ownership
    auto ptr2 = std::make_shared<int>(42);  // Shared ownership
    std::weak_ptr<int> ptr3 = ptr2;         // Weak reference
}
```

### S18: Friend function ve friend class ne zaman kullanılmalıdır?
**Cevap:** Encapsulation'ı bozmadan private üyelere erişim gereken özel durumlarda kullanılır:
```cpp
class MyClass {
private:
    int data;
    friend void specialFunction(MyClass& obj);  // Friend function
    friend class HelperClass;                   // Friend class
};
```

### S19: Static member variables ve functions ne için kullanılır?
**Cevap:** Class'ın tüm instance'ları arasında paylaşılan üyeler için kullanılır:
```cpp
class Counter {
    static int count;  // Tüm instance'lar için ortak
public:
    Counter() { ++count; }
    static int getCount() { return count; }
};
int Counter::count = 0;  // Static member initialization
```

### S20: const member functions neden önemlidir?
**Cevap:** Object'in state'ini değiştirmeyeceğini garanti eder ve const object'lerle kullanılabilir:
```cpp
class Date {
    int day, month, year;
public:
    int getYear() const { return year; }  // State değişmez
    void setYear(int y) { year = y; }     // State değişebilir
};
```

### S21: Rule of Three/Five/Zero nedir?
**Cevap:** Modern C++'ta kaynak yönetimi için uyulması gereken kurallardır:
- **Rule of Three**: Eğer bir class için destructor, copy constructor veya copy assignment operator'den birini tanımlıyorsanız, üçünü de tanımlamalısınız
- **Rule of Five**: Modern C++'ta move semantics ile birlikte move constructor ve move assignment operator da eklenir
- **Rule of Zero**: Eğer class özel kaynak yönetimi gerektirmiyorsa, hiçbirini tanımlamayın

Örnek:
```cpp
class RuleOfFive {
    int* data;
public:
    // Constructor
    RuleOfFive(int d) : data(new int(d)) {}
    
    // Destructor
    ~RuleOfFive() { delete data; }
    
    // Copy constructor
    RuleOfFive(const RuleOfFive& other) : data(new int(*other.data)) {}
    
    // Copy assignment
    RuleOfFive& operator=(const RuleOfFive& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }
    
    // Move constructor
    RuleOfFive(RuleOfFive&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }
    
    // Move assignment
    RuleOfFive& operator=(RuleOfFive&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};
```

### S22: Aşağıdaki kodun çıktısı ne olur ve neden?
```cpp
class Base {
public:
    Base() { print(); }
    virtual void print() { std::cout << "Base"; }
    virtual ~Base() { print(); }
};

class Derived : public Base {
public:
    Derived() { print(); }
    void print() override { std::cout << "Derived"; }
    ~Derived() { print(); }
};

int main() {
    Base* ptr = new Derived();
    delete ptr;
    return 0;
}
```
**Cevap:** Çıktı: `Base Derived Derived Base`
- Base constructor çağrıldığında virtual function tablosu henüz kurulmadığından "Base" yazdırılır
- Derived constructor çağrıldığında "Derived" yazdırılır
- delete işleminde önce Base destructor çağrılır ve "Derived" yazdırılır
- Son olarak Derived destructor çağrılır ve "Base" yazdırılır

### S23: Template metaprogramming nedir? Bir örnek veriniz.
**Cevap:** Compile-time'da hesaplama yapmayı sağlayan bir programlama tekniğidir:
```cpp
template<unsigned int N>
struct Factorial {
    static const unsigned int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static const unsigned int value = 1;
};

// Kullanımı
constexpr auto result = Factorial<5>::value;  // Compile-time'da hesaplanır
```

### S24: Perfect forwarding nedir ve ne için kullanılır?
**Cevap:** Template'lerde argümanların value/reference özelliklerini koruyarak iletilmesini sağlar:
```cpp
template<typename T>
void wrapper(T&& arg) {
    // std::forward ile arg'ın özelliklerini koruyarak iletme
    foo(std::forward<T>(arg));
}

// Kullanımı
int x = 42;
wrapper(x);        // x lvalue olarak iletilir
wrapper(42);       // 42 rvalue olarak iletilir
```

### S25: Bu kodda neden memory leak oluşur?
```cpp
class Base {
public:
    ~Base() {}
};

class Derived : public Base {
    int* ptr = new int(42);
public:
    ~Derived() { delete ptr; }
};

int main() {
    Base* b = new Derived();
    delete b;  // Memory leak!
    return 0;
}
```
**Cevap:** Base class destructor'ı virtual olmadığı için Derived class destructor'ı çağrılmaz ve ptr delete edilmez.

### S26: Operator overloading ile ilgili aşağıdaki kodun çıktısı ne olur?
```cpp
class Complex {
    int real, imag;
public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}
    
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        return os << c.real << "+" << c.imag << "i";
    }
};

int main() {
    Complex c1(1, 2), c2(3, 4);
    std::cout << c1 + c2;
    return 0;
}
```
**Cevap:** `4+6i`

### S27: CRTP (Curiously Recurring Template Pattern) nedir ve ne için kullanılır?
**Cevap:** Static polymorphism sağlamak için kullanılan bir design pattern'dir:
```cpp
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        std::cout << "Derived implementation";
    }
};
```

### S28: Aşağıdaki kodun problemi nedir?
```cpp
class Singleton {
private:
    static Singleton* instance;
    Singleton() {}
public:
    static Singleton* getInstance() {
        if (!instance) {
            instance = new Singleton();
        }
        return instance;
    }
};
```
**Cevap:** Thread-safe değil ve memory leak var. Düzeltilmiş hali:
```cpp
class Singleton {
private:
    Singleton() = default;
    
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
};
```

### S29: Exception handling ile ilgili aşağıdaki kodun çıktısı ne olur?
```cpp
class Resource {
public:
    Resource() { std::cout << "Create"; }
    ~Resource() { std::cout << "Destroy"; }
};

void foo() {
    Resource r;
    throw std::runtime_error("Error");
}

int main() {
    try {
        foo();
    } catch (const std::exception& e) {
        std::cout << "Caught";
    }
    return 0;
}
```
**Cevap:** `Create Destroy Caught`
Stack unwinding sırasında Resource destructor'ı çağrılır.

### S30: Modern C++'ta "this" pointer'ın auto deduction ile kullanımı nasıldır?
**Cevap:** C++23'te this parameter ile:
```cpp
class Calculator {
public:
    // C++23 deduced this
    auto add(this auto&& self, int x) {
        return self.value + x;
    }
private:
    int value{0};
};
```

Bu özellik özellikle template ve generic programlamada faydalıdır.

### S31: Aşağıdaki kodun çıktısı ne olur? Açıklayınız.
```cpp
class Base {
    int x = 1;
public:
    virtual int getValue() { return x; }
};

class Derived : public Base {
    int x = 2;
public:
    int getValue() override { return x; }
};

int main() {
    Base b;
    Derived d;
    Base& br = d;
    std::cout << b.getValue() << " ";
    std::cout << d.getValue() << " ";
    std::cout << br.getValue();
    return 0;
}
```
**Cevap:** `1 2 2`
- `b.getValue()` Base class'ın x'ini döndürür (1)
- `d.getValue()` Derived class'ın x'ini döndürür (2)
- `br.getValue()` virtual function olduğu için Derived class'ın implementasyonunu çağırır (2)

### S32: Bu kod neden derlenemez?
```cpp
class MyClass {
public:
    template<typename T>
    void process(T value) {
        helper(value);
    }
private:
    void helper(int x) { std::cout << "int"; }
    void helper(double x) { std::cout << "double"; }
};

int main() {
    MyClass obj;
    obj.process("hello");  // Compilation error!
    return 0;
}
```
**Cevap:** Template function instantiation sırasında string parametresi için uygun helper fonksiyonu bulunamaz. Çözüm:
1. String için helper overload eklemek
2. SFINAE veya concepts kullanarak kısıtlama getirmek
3. static_assert ile compile-time hata mesajı vermek

### S33: Aşağıdaki kodda kaç kez copy constructor çağrılır?
```cpp
class Counter {
public:
    Counter() { std::cout << "C"; }
    Counter(const Counter&) { std::cout << "Y"; }
    ~Counter() { std::cout << "D"; }
};

Counter foo() {
    Counter c;
    return c;
}

int main() {
    Counter c = foo();
    return 0;
}
```
**Cevap:** Modern derleyicilerde (RVO - Return Value Optimization sayesinde) çıktı `CD` olur. RVO olmasaydı `CYYD` olurdu.

### S34: Multiple inheritance'ta diamond problem'i çözmek için hangi yöntemler kullanılabilir?
**Cevap:**
1. Virtual inheritance kullanmak:
```cpp
class Animal {
public:
    virtual void eat() = 0;
};

class Mammal : virtual public Animal {
    void eat() override { std::cout << "Mammal eating"; }
};

class WingedAnimal : virtual public Animal {
    void eat() override { std::cout << "WingedAnimal eating"; }
};

class Bat : public Mammal, public WingedAnimal {
    void eat() override { std::cout << "Bat eating"; }
};
```

2. Interface segregation prensibini uygulamak
3. Composition kullanmak

### S35: Aşağıdaki kodun çıktısı ne olur ve neden?
```cpp
#include <memory>
#include <iostream>

class Resource {
public:
    Resource(int id) : id_(id) { 
        std::cout << "C" << id_; 
    }
    ~Resource() { 
        std::cout << "D" << id_; 
    }
private:
    int id_;
};

int main() {
    std::shared_ptr<Resource> ptr1(new Resource(1));
    {
        std::shared_ptr<Resource> ptr2 = ptr1;
        std::shared_ptr<Resource> ptr3(new Resource(2));
    }
    std::cout << "E";
    return 0;
}
```
**Cevap:** `C1C2D2ED1`
- İlk olarak Resource(1) oluşturulur: `C1`
- Sonra Resource(2) oluşturulur: `C2`
- Scope sonunda ptr3'ün gösterdiği Resource(2) silinir: `D2`
- "E" yazdırılır
- Program sonunda ptr1'in gösterdiği Resource(1) silinir: `D1`

### S36: Template specialization ile ilgili aşağıdaki kodun çıktısı ne olur?
```cpp
template<typename T>
class Container {
public:
    static void print() { std::cout << "General"; }
};

template<>
class Container<int> {
public:
    static void print() { std::cout << "Int"; }
};

template<typename T>
class Container<T*> {
public:
    static void print() { std::cout << "Pointer"; }
};

int main() {
    Container<double>::print();
    Container<int>::print();
    Container<int*>::print();
    return 0;
}
```
**Cevap:** `GeneralIntPointer`

### S37: Aşağıdaki kodda potansiyel sorunlar nelerdir?
```cpp
class Base {
public:
    Base() = default;
    Base(const Base&) = delete;
    virtual void foo() = 0;
};

class Derived : public Base {
public:
    void foo() override { std::cout << "Derived"; }
};

std::vector<Base> vec;  // Problem 1
Base b;                 // Problem 2
Derived d;
vec.push_back(d);      // Problem 3
```
**Cevap:**
1. Abstract class'tan vector oluşturulamaz
2. Abstract class'tan instance oluşturulamaz
3. Copy constructor deleted olduğu için push_back çalışmaz
Çözüm: `std::vector<std::unique_ptr<Base>>` kullanmak

### S38: Aşağıdaki kodun çıktısı ne olur?
```cpp
class Base {
public:
    Base() { std::cout << "B"; }
    virtual ~Base() { std::cout << "~B"; }
};

class Derived : public Base {
public:
    Derived() { std::cout << "D"; }
    ~Derived() { std::cout << "~D"; }
    
    // placement new operator overload
    void* operator new(size_t size, void* ptr) {
        std::cout << "N";
        return ptr;
    }
};

int main() {
    alignas(Derived) char buffer[sizeof(Derived)];
    Derived* ptr = new (&buffer) Derived();
    ptr->~Derived();
    return 0;
}
```
**Cevap:** `NBD~D~B`
Placement new kullanıldığında memory allocation yapılmaz, sadece constructor çağrılır.

### S39: std::function ve lambda ile ilgili aşağıdaki kodun çıktısı ne olur?
```cpp
class Counter {
    int value = 0;
public:
    std::function<void()> increment = [this]() {
        ++value;
        std::cout << value;
    };
};

int main() {
    Counter c1, c2;
    auto inc = c1.increment;
    c1.increment();
    c2.increment();
    inc();
    return 0;
}
```
**Cevap:** `112`
Lambda capture'da this kullanıldığı için her increment çağrısı kendi Counter instance'ınının value'sunu artırır.

### S40: Variadic templates ile ilgili aşağıdaki kodun çıktısı ne olur?
```cpp
template<typename T>
void print(T t) {
    std::cout << t << "E";
}

template<typename T, typename... Args>
void print(T t, Args... args) {
    std::cout << t << "B";
    print(args...);
}

int main() {
    print(1, 2.0, "3");
    return 0;
}
```
**Cevap:** `1B2B3E`
- İlk çağrıda t=1, args=(2.0, "3")
- İkinci çağrıda t=2.0, args=("3")
- Son çağrıda t="3", args=() (base case)

### S41: Aşağıdaki kodun çıktısı ne olur? Neden?
```cpp
class Base {
protected:
    int value;
public:
    Base(int v) : value(v) {}
    virtual void update() { value *= 2; }
    int getValue() const { return value; }
};

class Derived : public Base {
public:
    Derived(int v) : Base(v) {}
    void update() override { value += 5; }
};

int main() {
    Base* arr[2];
    arr[0] = new Base(10);
    arr[1] = new Derived(10);
    
    for(auto* ptr : arr) {
        ptr->update();
        std::cout << ptr->getValue() << " ";
    }
    return 0;
}
```
**Cevap:** `20 15`
- Base object için value 10'dan 20'ye çıkar (×2)
- Derived object için value 10'dan 15'e çıkar (+5)
- Virtual dispatch sayesinde doğru update fonksiyonları çağrılır

### S42: std::unique_ptr ve std::shared_ptr arasındaki farklar nelerdir? Hangisi ne zaman tercih edilmelidir?
**Cevap:**
1. **Ownership:**
   - `unique_ptr`: Tek sahiplik, transfer edilebilir ama paylaşılamaz
   - `shared_ptr`: Birden fazla sahip olabilir, reference counting kullanır

2. **Performance:**
   - `unique_ptr`: Overhead yok, raw pointer kadar hızlı
   - `shared_ptr`: Reference counting nedeniyle küçük bir overhead var

3. **Kullanım senaryoları:**
```cpp
// unique_ptr için ideal senaryo
class Engine {
    std::unique_ptr<Piston> piston;  // Piston sadece Engine'e ait
};

// shared_ptr için ideal senaryo
class Document {
    std::shared_ptr<DocumentState> state;  // State birden fazla view tarafından paylaşılabilir
};
```

### S43: Aşağıdaki kodda ne gibi sorunlar vardır?
```cpp
class String {
    char* data;
public:
    String(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }
    ~String() {
        delete[] data;
    }
    String(const String& other) {
        data = other.data;  // Sorun 1
    }
    String& operator=(String& other) {  // Sorun 2
        if(this != &other) {
            delete[] data;
            data = other.data;  // Sorun 3
        }
        return *this;
    }
};
```
**Cevap:**
1. Copy constructor shallow copy yapıyor, double free'ye yol açar
2. Assignment operator const reference almıyor
3. Assignment operator'da da shallow copy var
Düzeltilmiş hali:
```cpp
String(const String& other) {
    data = new char[strlen(other.data) + 1];
    strcpy(data, other.data);
}
String& operator=(const String& other) {
    if(this != &other) {
        char* temp = new char[strlen(other.data) + 1];
        strcpy(temp, other.data);
        delete[] data;
        data = temp;
    }
    return *this;
}
```

### S44: Aşağıdaki kodun çıktısı ne olur? Exception safety açısından değerlendiriniz.
```cpp
class Resource {
public:
    Resource(const std::string& s) { 
        std::cout << "R" << s;
        if(s == "throw") throw std::runtime_error("Error");
    }
    ~Resource() { std::cout << "D"; }
};

class Container {
    Resource r1{"1"};
    Resource r2{"2"};
public:
    Container() try : r1{"1"}, r2{"throw"} {
        std::cout << "C";
    } catch(...) {
        std::cout << "E";
        throw;  // rethrow
    }
};

int main() {
    try {
        Container c;
    } catch(...) {
        std::cout << "M";
    }
    return 0;
}
```
**Cevap:** `R1R2EDM`
- R1: İlk resource oluşturulur
- R2: İkinci resource exception fırlatır
- E: Constructor try-catch bloğu exception'ı yakalar
- D: r1 destroy edilir
- M: main'deki catch bloğu çalışır

### S45: Template metaprogramming kullanarak compile-time'da bir sayının asal olup olmadığını nasıl kontrol ederiz?
**Cevap:**
```cpp
template<unsigned int N, unsigned int D>
struct IsPrimeHelper {
    static constexpr bool value = (N % D != 0) && IsPrimeHelper<N, D-1>::value;
};

template<unsigned int N>
struct IsPrimeHelper<N, 1> {
    static constexpr bool value = true;
};

template<unsigned int N>
struct IsPrime {
    static constexpr bool value = N > 1 && IsPrimeHelper<N, N-1>::value;
};

// Kullanımı
static_assert(IsPrime<17>::value, "17 is prime");
static_assert(!IsPrime<15>::value, "15 is not prime");
```

### S46: std::move ve std::forward arasındaki fark nedir? Bir örnek üzerinde açıklayınız.
**Cevap:**
```cpp
class Widget {
public:
    Widget() = default;
    Widget(Widget&&) { std::cout << "Move"; }
    Widget(const Widget&) { std::cout << "Copy"; }
};

template<typename T>
void wrapper(T&& arg) {
    Widget w1(std::move(arg));     // Her zaman move
    Widget w2(std::forward<T>(arg));  // T'ye göre move veya copy
}

int main() {
    Widget w;
    wrapper(w);           // Copy Move (lvalue)
    wrapper(Widget());    // Move Move (rvalue)
    return 0;
}
```

### S47: Aşağıdaki kodun çıktısı ne olur? const member function davranışını açıklayınız.
```cpp
class Data {
    mutable int accessCount = 0;
    int value = 0;
public:
    int getValue() const {
        ++accessCount;  // mutable olduğu için değiştirilebilir
        return value;
    }
    void setValue(int v) {
        value = v;
        ++accessCount;
    }
    int getAccessCount() const { return accessCount; }
};

int main() {
    const Data d;
    std::cout << d.getValue() << " ";
    std::cout << d.getValue() << " ";
    std::cout << d.getAccessCount();
    return 0;
}
```
**Cevap:** `0 0 2`
- const object sadece const member function'ları çağırabilir
- mutable üyeler const member function'larda değiştirilebilir

### S48: SFINAE kullanarak bir type trait nasıl yazılır? Örnek veriniz.
**Cevap:**
```cpp
// has_toString type trait
template<typename T, typename = void>
struct has_toString : std::false_type {};

template<typename T>
struct has_toString<T, 
    std::void_t<decltype(std::declval<T>().toString())>> 
    : std::true_type {};

// Kullanım örneği
class WithToString {
public:
    std::string toString() { return "Hello"; }
};

class WithoutToString {};

static_assert(has_toString<WithToString>::value, "Has toString");
static_assert(!has_toString<WithoutToString>::value, "No toString");
```

### S49: Aşağıdaki kodun çıktısı ne olur? std::function davranışını açıklayınız.
```cpp
class Button {
    std::string name;
    std::function<void()> onClick;
public:
    Button(const std::string& n) : name(n) {}
    
    void setCallback(std::function<void()> cb) {
        onClick = std::move(cb);
    }
    
    void click() {
        if(onClick) {
            std::cout << name << ":";
            onClick();
        }
    }
};

int main() {
    int counter = 0;
    Button b1("B1"), b2("B2");
    
    auto callback = [&counter]() {
        ++counter;
        std::cout << counter << " ";
    };
    
    b1.setCallback(callback);
    b2.setCallback(callback);
    
    b1.click();
    b2.click();
    b1.click();
    
    return 0;
}
```
**Cevap:** `B1:1 B2:2 B1:3`
- Lambda capture by reference ile counter paylaşılır
- Her click'te aynı counter artırılır
- std::function, callable object'i kopyalar

### S50: Modern C++'ta aggregate initialization ile designated initializers arasındaki fark nedir?
**Cevap:**
```cpp
struct Point {
    int x = 0;
    int y = 0;
    const char* label = "default";
};

int main() {
    // Aggregate initialization (C++11)
    Point p1{1, 2, "first"};  // Sıralı initialization
    
    // Designated initializers (C++20)
    Point p2{.x = 1, .y = 2, .label = "second"};  // İsimli initialization
    
    // Karışık kullanılamaz
    // Point p3{.x = 1, 2, "third"};  // Error
    
    return 0;
}
```

### S51: Aşağıdaki kodun çıktısı ne olur? std::bind ve lambda davranışını açıklayınız.
```cpp
class Timer {
    int interval;
public:
    Timer(int i) : interval(i) {}
    
    template<typename Func>
    void setTimeout(Func f) {
        f(interval);
    }
};

void printNumber(int x) {
    std::cout << x << " ";
}

int main() {
    Timer t1(100), t2(200);
    auto boundFunc = std::bind(printNumber, std::placeholders::_1);
    auto lambda = [](int x) { printNumber(x * 2); };
    
    t1.setTimeout(boundFunc);
    t1.setTimeout(lambda);
    t2.setTimeout(boundFunc);
    return 0;
}
```
**Cevap:** `100 200 200`
- boundFunc parametreyi direkt iletir
- lambda parametreyi 2 ile çarparak iletir
- std::bind ile oluşturulan fonksiyon objesi her çağrıda yeni bir kopyası oluşturulur

### S52: Aşağıdaki kodda neden memory leak oluşabilir?
```cpp
class Node {
    int data;
    Node* next;
public:
    Node(int d) : data(d), next(nullptr) {}
    ~Node() { delete next; }  // Sorun burada
    
    void setNext(Node* n) { next = n; }
};

int main() {
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    
    n1->setNext(n2);
    n2->setNext(n3);
    n3->setNext(n1);  // Circular reference!
    
    delete n1;  // Stack overflow!
    return 0;
}
```
**Cevap:** Circular reference durumunda destructor sonsuz döngüye girer. Çözüm:
1. Smart pointer kullanmak
2. Destructor'da sadece current node'u silmek
3. Linked list mantığını değiştirmek

### S53: Aşağıdaki kodun çıktısı ne olur? std::optional kullanımını açıklayınız.
```cpp
#include <optional>

std::optional<int> divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

int main() {
    auto r1 = divide(10, 2);
    auto r2 = divide(10, 0);
    auto r3 = divide(15, 3);
    
    std::cout << r1.value_or(-1) << " ";
    std::cout << r2.value_or(-1) << " ";
    if (r3) std::cout << *r3;
    return 0;
}
```
**Cevap:** `5 -1 5`
- r1: Başarılı bölme, 5 döner
- r2: Başarısız bölme, value_or(-1) ile -1 döner
- r3: Başarılı bölme, has_value() true olduğu için değer yazdırılır

### S54: Aşağıdaki kodun çıktısı ne olur? std::variant davranışını açıklayınız.
```cpp
#include <variant>

class Visitor {
public:
    void operator()(int i) { std::cout << "I" << i; }
    void operator()(double d) { std::cout << "D" << d; }
    void operator()(const std::string& s) { std::cout << "S" << s; }
};

int main() {
    std::variant<int, double, std::string> var;
    var = 42;
    std::visit(Visitor{}, var);
    
    var = 3.14;
    std::visit(Visitor{}, var);
    
    var = "hello";
    std::visit(Visitor{}, var);
    return 0;
}
```
**Cevap:** `I42D3.14Shello`
- std::variant type-safe union gibi davranır
- std::visit ile variant içindeki aktif type'a göre doğru overload çağrılır

### S55: Aşağıdaki kodda ne gibi sorunlar olabilir?
```cpp
template<typename T>
class SharedState {
    T* data;
    std::atomic<int> refCount;
public:
    SharedState(T* ptr) : data(ptr), refCount(1) {}
    
    void addRef() { ++refCount; }
    
    void release() {
        if (--refCount == 0) {
            delete data;
            delete this;  // Self deletion!
        }
    }
    
    T* get() { return data; }
};
```
**Cevap:**
1. Thread safety sorunu: refCount değişimi atomic ama diğer operasyonlar değil
2. Exception safety yok
3. Self deletion tehlikeli olabilir
4. Move semantics eksik
Çözüm: std::shared_ptr kullanmak veya daha güvenli bir implementasyon yapmak

### S56: Aşağıdaki kodun çıktısı ne olur? std::any kullanımını açıklayınız.
```cpp
#include <any>

void printAny(const std::any& a) {
    try {
        if (a.type() == typeid(int))
            std::cout << std::any_cast<int>(a);
        else if (a.type() == typeid(std::string))
            std::cout << std::any_cast<std::string>(a);
        else
            std::cout << "Unknown";
    } catch(const std::bad_any_cast&) {
        std::cout << "Error";
    }
    std::cout << " ";
}

int main() {
    std::any a1 = 42;
    std::any a2 = std::string("Hello");
    std::any a3;
    
    printAny(a1);
    printAny(a2);
    printAny(a3);
    
    a1 = 3.14;  // Now double
    printAny(a1);
    return 0;
}
```
**Cevap:** `42 Hello Unknown Error`
- std::any type-safe bir container'dır
- any_cast ile güvenli type conversion yapılır
- has_value() ile değer kontrolü yapılabilir

### S57: Aşağıdaki kodun çıktısı ne olur? Coroutine davranışını açıklayınız.
```cpp
#include <coroutine>
#include <iostream>

struct Generator {
    struct promise_type {
        int value;
        Generator get_return_object() { return Generator{this}; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        std::suspend_always yield_value(int v) {
            value = v;
            return {};
        }
        void unhandled_exception() {}
    };
    
    std::coroutine_handle<promise_type> h;
    Generator(promise_type* p) : h(std::coroutine_handle<promise_type>::from_promise(*p)) {}
    
    int next() {
        h.resume();
        return h.promise().value;
    }
};

Generator count(int start, int end) {
    for(int i = start; i <= end; ++i) {
        co_yield i;
    }
}

int main() {
    auto gen = count(1, 3);
    for(int i = 0; i < 3; ++i) {
        std::cout << gen.next() << " ";
    }
    return 0;
}
```
**Cevap:** `1 2 3`
- Coroutine fonksiyon çağrısı askıya alınabilir ve devam ettirilebilir
- co_yield ile değer döndürülür ve fonksiyon askıya alınır
- next() ile coroutine devam ettirilir

### S58: Aşağıdaki kodun çıktısı ne olur? constexpr kullanımını açıklayınız.
```cpp
constexpr int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

int main() {
    constexpr int fib5 = fibonacci(5);
    constexpr int fact5 = Factorial<5>::value;
    
    std::cout << fib5 << " " << fact5;
    return 0;
}
```
**Cevap:** `5 120`
- constexpr fonksiyonlar compile-time'da hesaplanabilir
- Template metaprogramming ile de compile-time hesaplama yapılabilir
- Her iki hesaplama da runtime'da değil compile-time'da yapılır

### S59: Aşağıdaki kodun çıktısı ne olur? std::span kullanımını açıklayınız.
```cpp
#include <span>
#include <vector>
#include <array>

void printFirst3(std::span<const int> numbers) {
    for(size_t i = 0; i < std::min(numbers.size(), size_t(3)); ++i) {
        std::cout << numbers[i] << " ";
    }
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::array<int, 4> arr{6, 7, 8, 9};
    int c_arr[] = {10, 11, 12};
    
    printFirst3(vec);
    printFirst3(arr);
    printFirst3(c_arr);
    return 0;
}
```
**Cevap:** `1 2 3 6 7 8 10 11 12`
- std::span contiguous memory view sağlar
- Vector, array ve C-style array ile kullanılabilir
- Non-owning reference semantics sağlar

### S60: Aşağıdaki kodun çıktısı ne olur? CRTP ve static polymorphism'i açıklayınız.
```cpp
template<typename Derived>
class Shape {
public:
    void draw() {
        static_cast<Derived*>(this)->drawImpl();
    }
protected:
    void drawImpl() { std::cout << "Shape "; }
};

class Circle : public Shape<Circle> {
public:
    void drawImpl() { std::cout << "Circle "; }
};

class Square : public Shape<Square> {
    // drawImpl() yok, base class'ın implementasyonu kullanılacak
};

template<typename T>
void drawShape(Shape<T>& shape) {
    shape.draw();
}

int main() {
    Circle c;
    Square s;
    drawShape(c);
    drawShape(s);
    return 0;
}
```
**Cevap:** `Circle Shape`
- CRTP ile static (compile-time) polymorphism sağlanır
- Virtual function overhead'i olmaz
- Derived class'ta implementation yoksa base class'ın implementasyonu kullanılır