# C++ Templates

## İçindekiler
1. [Function Templates](#function-templates)
2. [Class Templates](#class-templates)
3. [Template Specialization](#template-specialization)
4. [Variadic Templates](#variadic-templates)
5. [Template Metaprogramming](#template-metaprogramming)
6. [SFINAE](#sfinae)

## Function Templates

Function templates, farklı veri tipleriyle çalışabilen generic fonksiyonlar oluşturmamızı sağlar.

### Temel Syntax
```cpp
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}
```

### Kullanım Örnekleri
```cpp
int i = max(10, 20);        // T = int
double d = max(3.14, 2.72); // T = double
string s = max("abc", "def"); // T = string
```

### Multiple Template Parameters
```cpp
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}
```

## Class Templates

Class templates, farklı veri tipleriyle çalışabilen generic sınıflar oluşturmamızı sağlar.

### Temel Syntax
```cpp
template <typename T>
class Array {
private:
    T* data;
    size_t size;
public:
    Array(size_t s) : size(s) {
        data = new T[size];
    }
    T& operator[](size_t index) {
        return data[index];
    }
};
```

### Kullanım Örnekleri
```cpp
Array<int> intArray(10);
Array<string> stringArray(5);
```

## Template Specialization

Template specialization, belirli tipler için özel davranışlar tanımlamamızı sağlar.

### Full Specialization
```cpp
template <>
class Array<bool> {
    // bool tipi için özel implementasyon
};
```

### Partial Specialization
```cpp
template <typename T>
class Array<T*> {
    // pointer tipleri için özel implementasyon
};
```

## Variadic Templates

Variadic templates, değişken sayıda template parametresi kullanmamızı sağlar.

### Temel Syntax
```cpp
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << '\n';
}
```

### Recursive Variadic Templates
```cpp
template<typename T>
T sum(T t) {
    return t;
}

template<typename T, typename... Rest>
T sum(T first, Rest... rest) {
    return first + sum(rest...);
}
```

## Template Metaprogramming

Template metaprogramming, derleme zamanında hesaplamalar yapmamızı sağlar.

### Compile-Time Calculations
```cpp
template <unsigned N>
struct Factorial {
    static const unsigned value = N * Factorial<N-1>::value;
};

template <>
struct Factorial<0> {
    static const unsigned value = 1;
};
```

### Type Traits
```cpp
template <typename T>
struct is_pointer {
    static const bool value = false;
};

template <typename T>
struct is_pointer<T*> {
    static const bool value = true;
};
```

## SFINAE (Substitution Failure Is Not An Error)

SFINAE, template overload resolution sırasında geçersiz substitution'ların hata vermeden elenmesini sağlar.

### Enable_if Kullanımı
```cpp
template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd(T i) {
    return bool(i % 2);
}
```

### Type Traits ile SFINAE
```cpp
template <typename T>
auto get_value(T t) -> typename std::enable_if<
    std::is_pointer<T>::value,
    typename std::remove_pointer<T>::type>::type {
    return *t;
}
```

## Best Practices

1. **Template Parameter İsimlendirme:**
   - Tek tip parametre için genelde `T` kullanın
   - Multiple parametreler için `T`, `U`, `V` veya anlamlı isimler kullanın
   - Type template parametreleri için `typename` keyword'ünü tercih edin

2. **Code Bloat Önleme:**
   - Template instantiation sayısını minimize edin
   - Common code'u non-template base class'lara taşıyın
   - Template parametrelerini sınırlandırmak için concepts (C++20) kullanın

3. **Error Handling:**
   - Static assertions kullanarak compile-time kontroller ekleyin
   - Template error mesajlarını anlaşılır hale getirin
   - Type traits ile tip kontrolü yapın

4. **Performance:**
   - Template metaprogramming ile compile-time optimizasyonlar yapın
   - Gereksiz template instantiation'lardan kaçının
   - Template specialization ile özel durumları optimize edin

## Common Pitfalls

1. **Template Code Visibility:**
   ```cpp
   // Header'da tam template tanımı gerekli
   template <typename T>
   T add(T a, T b) {
       return a + b;
   }
   ```

2. **Template Type Deduction:**
   ```cpp
   template <typename T>
   void func(T param);
   
   func(42);    // T = int
   func<int>(42); // Explicit type
   ```

3. **Dependent Names:**
   ```cpp
   template <typename T>
   void func() {
       typename T::type var; // 'typename' keyword gerekli
   }
   ```

4. **Template Instantiation Depth:**
   ```cpp
   template <typename T>
   struct Recurse {
       Recurse<T*> next; // Sonsuz recursion!
   };
   ``` 