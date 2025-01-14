#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

// Function template örneği
template <typename T>
T max(T a, T b) {
    std::cout << "Generic max çağrıldı\n";
    return (a > b) ? a : b;
}

// Template specialization örneği
template <>
const char* max(const char* a, const char* b) {
    std::cout << "Specialized max çağrıldı\n";
    return (std::string(a) > std::string(b)) ? a : b;
}

// Class template örneği
template <typename T>
class Container {
private:
    T data;
public:
    Container(T value) : data(value) {}
    T getValue() const { return data; }
    void setValue(T value) { data = value; }
};

// Partial specialization örneği
template <typename T>
class Container<T*> {
private:
    T* data;
public:
    Container(T* value) : data(value) {}
    T* getValue() const { return data; }
    void setValue(T* value) { data = value; }
    T getDerefValue() const { return *data; }
};

// Variadic template örneği
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << '\n';
}

// Recursive variadic template örneği
template<typename T>
T sum(T t) {
    return t;
}

template<typename T, typename... Rest>
T sum(T first, Rest... rest) {
    return first + sum(rest...);
}

// Template metaprogramming örneği
template <unsigned N>
struct Factorial {
    static const unsigned value = N * Factorial<N-1>::value;
};

template <>
struct Factorial<0> {
    static const unsigned value = 1;
};

// SFINAE örneği
template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd(T i) {
    return bool(i % 2);
}

// Multiple template parameters örneği
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

int main() {
    // Function template örnekleri
    std::cout << "\n=== Function Template Örnekleri ===\n";
    std::cout << "max(10, 20): " << max(10, 20) << '\n';
    std::cout << "max(3.14, 2.72): " << max(3.14, 2.72) << '\n';
    std::cout << "max(\"abc\", \"def\"): " << max("abc", "def") << '\n';

    // Class template örnekleri
    std::cout << "\n=== Class Template Örnekleri ===\n";
    Container<int> intContainer(42);
    std::cout << "Int container value: " << intContainer.getValue() << '\n';
    
    int* ptr = new int(100);
    Container<int*> ptrContainer(ptr);
    std::cout << "Pointer container dereferenced value: " << ptrContainer.getDerefValue() << '\n';
    delete ptr;

    // Variadic template örnekleri
    std::cout << "\n=== Variadic Template Örnekleri ===\n";
    print("Hello", ' ', "World", '!', ' ', 42);
    std::cout << "Sum(1,2,3,4,5): " << sum(1,2,3,4,5) << '\n';

    // Template metaprogramming örnekleri
    std::cout << "\n=== Template Metaprogramming Örnekleri ===\n";
    std::cout << "Factorial<5>::value: " << Factorial<5>::value << '\n';

    // SFINAE örnekleri
    std::cout << "\n=== SFINAE Örnekleri ===\n";
    std::cout << "is_odd(42): " << is_odd(42) << '\n';
    // is_odd(3.14); // Derleme hatası: double için tanımlı değil

    // Multiple template parameters örnekleri
    std::cout << "\n=== Multiple Template Parameters Örnekleri ===\n";
    std::cout << "add(3, 4.5): " << add(3, 4.5) << '\n';
    
    return 0;
} 