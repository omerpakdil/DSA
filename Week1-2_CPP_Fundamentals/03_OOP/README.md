# Object-Oriented Programming in C++

Bu rehber, C++'da Object-Oriented Programming (OOP) temel kavramlarını, pratik örnekler ve açıklamalarla birlikte kapsamaktadır.

## İçindekiler
1. [Classes and Objects](#classes-and-objects)
2. [Inheritance](#inheritance)
3. [Polymorphism](#polymorphism)
4. [Encapsulation](#encapsulation)
5. [Multiple Inheritance](#multiple-inheritance)
6. [Templates](#templates)
7. [Smart Pointers](#smart-pointers)

## Classes and Objects

### Temel Kavramlar
- Class'lar, veri ve fonksiyonları kapsülleyen kullanıcı tanımlı veri tipleridir
- Object'ler, class'ların örnekleridir
- Constructor ve Destructor'lar
- Member function'lar ve data member'lar
- Access specifier'lar (public, private, protected)

### Örnek
```cpp
class Ogrenci {
private:
    int numara;
    std::string ad;
    float ortalama;

public:
    Ogrenci(int n, std::string a, float o);
    void goster() const;
};
```

## Inheritance

### Temel Kavramlar
- Base ve derived class'lar
- Inheritance türleri (public, private, protected)
- Virtual function'lar
- Abstract class'lar ve pure virtual function'lar

### Örnek
```cpp
class Sekil {
public:
    virtual double alan() const = 0;  // Pure virtual function
};

class Daire : public Sekil {
public:
    double alan() const override;
};
```

## Polymorphism

### Temel Kavramlar
- Runtime polymorphism (virtual function'lar)
- Compile-time polymorphism (function overloading)
- Virtual destructor'lar
- Override ve final specifier'lar

### Örnek
```cpp
class Hayvan {
public:
    virtual void sesCikar() const = 0;
};

class Kopek : public Hayvan {
public:
    void sesCikar() const override;
};
```

## Encapsulation

### Temel Kavramlar
- Data hiding
- Access control
- Getter ve setter function'lar
- Const correctness

### En İyi Uygulamalar
1. Data member'ları private yapın
2. Public interface'i member function'larla sağlayın
3. Uygun olduğunda const member function'ları kullanın
4. Getter ve setter'ları sadece gerektiğinde uygulayın

## Multiple Inheritance

### Temel Kavramlar
- Birden fazla base class'tan inheritance
- Diamond problem
- Virtual inheritance
- Interface segregation

### Örnek
```cpp
class Yazici {
public:
    virtual void yazdir() const;
};

class Tarayici {
public:
    virtual void tara() const;
};

class HepsibirArada : public Yazici, public Tarayici {
    // Her iki interface'i de uygular
};
```

## Templates

### Temel Kavramlar
- Generic programming
- Template class'lar ve function'lar
- Template specialization
- Type deduction

### Örnek
```cpp
template<typename T>
class Konteyner {
private:
    std::vector<T> elemanlar;
public:
    void ekle(const T& eleman);
    const T& getir(size_t indeks) const;
};
```

## Smart Pointers

### Temel Kavramlar
- RAII (Resource Acquisition Is Initialization)
- Smart pointer türleri:
  - `unique_ptr`
  - `shared_ptr`
  - `weak_ptr`
- Memory management
- Exception safety

### Örnek
```cpp
std::unique_ptr<Kaynak> kaynak = std::make_unique<Kaynak>();
kaynak->kullan();  // Scope dışına çıkınca otomatik delete edilir
```

## Common Interview Questions

1. OOP'nin dört temel prensibi nelerdir?
   - Encapsulation
   - Inheritance
   - Polymorphism
   - Abstraction

2. Virtual function ile pure virtual function arasındaki fark nedir?
   - Virtual function'lar base class'ta bir implementasyon içerir
   - Pure virtual function'lar `= 0` ile tanımlanır ve derived class'lar tarafından implement edilmelidir

3. Multiple inheritance'ta diamond problem nedir?
   - Bir class, ortak bir base class'a sahip iki class'tan inherit edildiğinde oluşur
   - Virtual inheritance kullanılarak çözülebilir

4. `unique_ptr` ve `shared_ptr` arasındaki fark nedir?
   - `unique_ptr` resource'un exclusive ownership'ine sahiptir
   - `shared_ptr` multiple pointer'ların ownership'i paylaşmasına izin verir

## Practice Exercises

1. Bir shape system için class hierarchy oluşturun
   - Abstract base class `Sekil`'i implement edin
   - Farklı shape'ler için derived class'lar oluşturun
   - Area ve perimeter hesaplamalarını implement edin

2. Bir template container class implement edin
   - Element ekleme ve alma method'ları ekleyin
   - Type safety sağlayın
   - Edge case'leri handle edin

3. Bir resource management system tasarlayın
   - Smart pointer'lar kullanın
   - RAII implement edin
   - Memory leak'leri prevent edin

## Additional Resources

1. Books
   - "Effective C++" - Scott Meyers
   - "Modern C++ Design" - Andrei Alexandrescu

2. Online Resources
   - [CPP Reference](https://en.cppreference.com/)
   - [ISO CPP Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

3. Practice Problems
   - [LeetCode OOP Problems](https://leetcode.com/tag/object-oriented-programming/)
   - [Design Patterns in C++](https://refactoring.guru/design-patterns/cpp)
``` 