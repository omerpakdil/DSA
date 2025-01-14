# C++ STL Mülakat Soruları

## İçindekiler
1. [Containers](#containers)
2. [Iterators](#iterators)
3. [Algorithms](#algorithms)
4. [Function Objects](#function-objects)
5. [Kod Çıktı Soruları](#kod-çıktı-soruları)

## Containers

### S1: STL container'larının temel kategorileri nelerdir? ⭐
**Cevap:**
1. **Sequence Containers:**
   - vector, list, deque
   - Elemanlar insertion sırasına göre saklanır

2. **Associative Containers:**
   - set, map, multiset, multimap
   - Elemanlar sıralı şekilde saklanır (genelde Red-Black Tree implementasyonu)

3. **Unordered Containers:**
   - unordered_set, unordered_map
   - Hash table implementasyonu
   - O(1) average case erişim

```cpp
// Örnek kullanımlar:
std::vector<int> vec = {1, 2, 3};           // Sequence
std::map<std::string, int> map;             // Associative
std::unordered_set<int> hashset = {1, 2};   // Unordered
```

### S2: vector ve list arasındaki performans farklarını açıklayın. ⭐⭐
**Cevap:**
```cpp
std::vector<int> vec;
std::list<int> lst;

// 1. Random Access
vec[5];      // O(1) - direct access
// lst[5];   // Not possible, O(n) traversal required

// 2. Insertion/Deletion at middle
vec.insert(vec.begin() + 5, 42);  // O(n) - shift elements
lst.insert(std::next(lst.begin(), 5), 42);  // O(1) - just relink

// 3. Memory layout
// vector: Contiguous memory, better cache performance
// list: Scattered nodes, worse cache performance but no reallocation
```

### S3: Aşağıdaki kodun çıktısı ne olur? ⭐
```cpp
int main() {
    std::vector<int> vec = {1, 2, 3};
    vec.reserve(10);
    std::cout << vec.size() << " " << vec.capacity() << "\n";
    
    vec.push_back(4);
    vec.push_back(5);
    std::cout << vec.size() << " " << vec.capacity();
    return 0;
}
```
**Cevap:** `3 10\n5 10`
- reserve() size'ı değiştirmez, sadece capacity'yi ayarlar
- push_back() size'ı artırır ama capacity yeterli olduğu için değişmez

## Iterators

### S4: Iterator kategorilerini açıklayın. ⭐⭐
**Cevap:**
1. **Input Iterator:**
   - Forward traversal, read-only
   - istream_iterator

2. **Output Iterator:**
   - Forward traversal, write-only
   - ostream_iterator

3. **Forward Iterator:**
   - Forward traversal, read-write
   - forward_list

4. **Bidirectional Iterator:**
   - Both directions, read-write
   - list, set, map

5. **Random Access Iterator:**
   - Random access, read-write
   - vector, deque

```cpp
// Örnek:
std::vector<int> vec = {1, 2, 3};
auto it = vec.begin();  // Random access iterator
it += 2;                // OK for random access
std::cout << *it;       // 3

std::list<int> lst = {1, 2, 3};
auto lit = lst.begin(); // Bidirectional iterator
++lit;                  // OK
// lit += 2;           // Error: no random access
```

### S5: Iterator invalidation durumlarını açıklayın. ⭐⭐
**Cevap:**
```cpp
std::vector<int> vec = {1, 2, 3};
auto it = vec.begin();

// 1. Reallocation invalidation
vec.push_back(4);  // May invalidate all iterators if reallocation occurs

// 2. Deletion invalidation
vec.erase(it);     // Invalidates it and all following iterators

// Safe usage:
auto it2 = vec.begin();
it2 = vec.erase(it2);  // erase returns valid iterator
```

## Algorithms

### S6: Aşağıdaki kodun çıktısı ne olur? ⭐
```cpp
int main() {
    std::vector<int> vec = {3, 1, 4, 1, 5};
    std::sort(vec.begin(), vec.end());
    
    auto it = std::lower_bound(vec.begin(), vec.end(), 4);
    std::cout << *it << " " << (it - vec.begin());
    return 0;
}
```
**Cevap:** `4 3`
- sort: {1, 1, 3, 4, 5}
- lower_bound 4 için index 3'ü bulur

### S7: find ve find_if arasındaki fark nedir? ⭐
**Cevap:**
```cpp
std::vector<int> vec = {1, 2, 3, 4, 5};

// find: Exact match
auto it1 = std::find(vec.begin(), vec.end(), 3);

// find_if: Custom predicate
auto it2 = std::find_if(vec.begin(), vec.end(), 
    [](int x) { return x % 2 == 0; });  // First even number

std::cout << *it1 << " " << *it2;  // 3 2
```

## Function Objects

### S8: Lambda capture modes arasındaki farkları açıklayın. ⭐⭐
**Cevap:**
```cpp
int x = 1, y = 2;

// 1. By value
auto lambda1 = [=]() { return x + y; };  // Copy x and y

// 2. By reference
auto lambda2 = [&]() { ++x; ++y; };      // Reference to x and y

// 3. Mixed
auto lambda3 = [=, &x]() { ++x; return y; };  // x by ref, y by value

// 4. Init capture (C++14)
auto lambda4 = [z = x + y]() { return z; };   // Compute and store
```

### S9: Aşağıdaki kodun çıktısı ne olur? ⭐⭐
```cpp
struct Compare {
    bool operator()(int a, int b) { return a > b; }
};

int main() {
    std::set<int, Compare> s = {1, 2, 3};
    s.insert(0);
    
    for(auto x : s) std::cout << x << " ";
    return 0;
}
```
**Cevap:** `3 2 1 0`
- Compare fonctor'ı büyükten küçüğe sıralama yapar
- set bu sıralamayı kullanır

### S10: std::function ne için kullanılır? ⭐⭐
**Cevap:**
```cpp
// Different callable types
int add(int a, int b) { return a + b; }
auto lambda = [](int a, int b) { return a * b; };
struct Divider { int operator()(int a, int b) { return a / b; } };

// std::function can store any callable with matching signature
std::function<int(int,int)> func;

void example() {
    func = add;        // Store function
    std::cout << func(10, 5) << " ";  // 15
    
    func = lambda;     // Store lambda
    std::cout << func(10, 5) << " ";  // 50
    
    func = Divider{}; // Store functor
    std::cout << func(10, 5);         // 2
}
```

## Kod Çıktı Soruları

### S11: Aşağıdaki kodun çıktısı ne olur? ⭐⭐
```cpp
int main() {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}};
    
    auto it = m.find(2);
    if(it != m.end()) m.erase(it);
    
    m[2] = "TWO";
    std::cout << m.size() << " " << m[2];
    return 0;
}
```
**Cevap:** `2 TWO`
- find(2) iterator'ı bulur
- erase ile silindi
- m[2] yeni element insert eder

### S12: Aşağıdaki kodda hata nedir? ⭐⭐
```cpp
int main() {
    std::vector<int> vec = {1, 2, 3};
    
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        if(*it == 2) {
            vec.push_back(4);  // Iterator invalidation!
        }
    }
    return 0;
}
```
**Cevap:** Iterator invalidation. push_back() reallocation yapabilir ve tüm iterator'ları invalidate eder.
Çözüm:
```cpp
// 1. İlk size'ı sakla
size_t size = vec.size();
for(size_t i = 0; i < size; ++i) {
    if(vec[i] == 2) vec.push_back(4);
}

// 2. Ya da önceden reserve yap
vec.reserve(vec.size() * 2);
```

### S13: emplace_back ve push_back arasındaki fark nedir? ⭐⭐
**Cevap:**
```cpp
class Point {
public:
    Point(int x, int y) {}
    Point(const Point&) { std::cout << "C"; }
    Point(Point&&) { std::cout << "M"; }
};

int main() {
    std::vector<Point> vec;
    
    // push_back: Temporary object + move/copy
    vec.push_back(Point(1, 2));  // Temporary + M
    
    // emplace_back: In-place construction
    vec.emplace_back(1, 2);      // Direct construction
    return 0;
}
```

### S14: Aşağıdaki kodun çıktısı ne olur? ⭐⭐
```cpp
int main() {
    std::vector<bool> vec = {true, false, true};
    bool& ref = vec[0];  // Error: vector<bool> special case
    
    vec[1] = true;
    std::cout << vec[0] << vec[1] << vec[2];
    return 0;
}
```
**Cevap:** Compilation error. vector<bool> özel bir durumdur ve bit field kullanır. bool& referans alamazsınız.
Çözüm:
```cpp
std::vector<bool> vec = {true, false, true};
auto value = vec[0];  // Copy the value
// Ya da
std::deque<bool> vec = {true, false, true};  // Normal bool storage
```

### S15: Aşağıdaki kodun çıktısı ne olur? ⭐
```cpp
int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    auto it = std::remove_if(vec.begin(), vec.end(),
        [](int x) { return x % 2 == 0; });
        
    std::cout << vec.size() << " ";
    for(auto i = vec.begin(); i != it; ++i)
        std::cout << *i;
    return 0;
}
```
**Cevap:** `5 135`
- remove_if tek sayıları başa taşır
- size değişmez (remove_if silmez)
- Logical end (it) öncesi elemanlar: 1,3,5
``` 