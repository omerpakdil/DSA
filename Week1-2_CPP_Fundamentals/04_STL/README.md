# C++ Standard Template Library (STL)

## İçindekiler
1. [Containers](#containers)
2. [Iterators](#iterators)
3. [Algorithms](#algorithms)
4. [Function Objects](#function-objects)
5. [Utility Components](#utility-components)

## Containers

### Sequence Containers
- **vector**: Dinamik dizi yapısı
  ```cpp
  std::vector<int> vec = {1, 2, 3};
  vec.push_back(4);  // [1, 2, 3, 4]
  ```

- **list**: Çift yönlü bağlı liste
  ```cpp
  std::list<int> lst = {1, 2, 3};
  lst.push_front(0);  // [0, 1, 2, 3]
  ```

- **deque**: Çift yönlü kuyruk
  ```cpp
  std::deque<int> dq = {1, 2, 3};
  dq.push_front(0);   // [0, 1, 2, 3]
  dq.push_back(4);    // [0, 1, 2, 3, 4]
  ```

### Associative Containers
- **set/multiset**: Sıralı benzersiz/tekrarlı elemanlar
  ```cpp
  std::set<int> s = {3, 1, 4, 1, 5};  // {1, 3, 4, 5}
  std::multiset<int> ms = {3, 1, 4, 1, 5};  // {1, 1, 3, 4, 5}
  ```

- **map/multimap**: Anahtar-değer çiftleri
  ```cpp
  std::map<std::string, int> m;
  m["one"] = 1;
  m["two"] = 2;
  ```

### Unordered Containers
- **unordered_set/map**: Hash tabanlı yapılar
  ```cpp
  std::unordered_map<std::string, int> um;
  um["apple"] = 1;  // Ortalama O(1) erişim
  ```

## Iterators

### Iterator Kategorileri
1. **Input Iterator**: İleri yönlü, sadece okuma
2. **Output Iterator**: İleri yönlü, sadece yazma
3. **Forward Iterator**: İleri yönlü, okuma-yazma
4. **Bidirectional Iterator**: Çift yönlü
5. **Random Access Iterator**: Rastgele erişim

### Temel İşlemler
```cpp
auto it = container.begin();  // İlk eleman
auto end = container.end();   // Son elemandan sonraki konum

++it;      // Sonraki eleman
--it;      // Önceki eleman (bidirectional ise)
it += n;   // n adım ileri (random access ise)

*it;       // Elemana erişim
it->mem;   // Üye erişimi
```

## Algorithms

### Sıralama ve Arama
```cpp
std::sort(vec.begin(), vec.end());  // Varsayılan artan sıralama
std::sort(vec.begin(), vec.end(), std::greater<>());  // Azalan sıralama

auto it = std::find(vec.begin(), vec.end(), value);
auto it = std::binary_search(vec.begin(), vec.end(), value);
```

### Dizi Modifikasyonları
```cpp
std::transform(in.begin(), in.end(), out.begin(), func);
std::remove_if(vec.begin(), vec.end(), predicate);
std::replace(vec.begin(), vec.end(), old_val, new_val);
```

### Sayısal İşlemler
```cpp
int sum = std::accumulate(vec.begin(), vec.end(), 0);
int product = std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<>());
```

## Function Objects

### Functors
```cpp
struct Compare {
    bool operator()(const T& a, const T& b) {
        return a < b;
    }
};
```

### Lambda İfadeleri
```cpp
auto lambda = [capture](params) { body };
auto add = [](int a, int b) { return a + b; };
```

### Standart Function Objects
```cpp
std::plus<>()        // Toplama operatörü
std::minus<>()       // Çıkarma operatörü
std::greater<>()     // Büyüktür operatörü
std::less<>()        // Küçüktür operatörü
```

## Utility Components

### Pairs ve Tuples
```cpp
std::pair<int, std::string> p = {1, "one"};
std::tuple<int, std::string, double> t = {1, "one", 1.0};
```

### Smart Pointers
```cpp
std::unique_ptr<T> up(new T());
std::shared_ptr<T> sp = std::make_shared<T>();
std::weak_ptr<T> wp = sp;
```

### Optional ve Variant
```cpp
std::optional<int> opt = func();
if(opt) use(*opt);

std::variant<int, std::string> var = "hello";
std::visit(visitor, var);
```

## Best Practices

1. **Container Seçimi:**
   - `vector`: Varsayılan seçim, sürekli bellek
   - `list`: Ortadan sık ekleme/silme
   - `deque`: İki uçtan sık ekleme/silme
   - `set/map`: Sıralı veriler için hızlı arama
   - `unordered_set/map`: Hash tabanlı hızlı arama

2. **Iterator Kullanımı:**
   - Iterator geçerliliğini her zaman kontrol edin
   - Mümkünse range-based for kullanın
   - end() iterator'ını tekrar kullanım için saklayın

3. **Algorithm Verimliliği:**
   - Manuel döngüler yerine standart algoritmalar kullanın
   - Sıralı/sırasız algoritmaları göz önünde bulundurun
   - Container'ın özel üye fonksiyonlarını kontrol edin

4. **Bellek Yönetimi:**
   - Yeniden tahsis önlemek için reserve() kullanın
   - push_back() yerine emplace_back() tercih edin
   - Iterator invalidation kurallarına dikkat edin

## Common Pitfalls

1. **Iterator Invalidation:**
   ```cpp
   vec.push_back(x);  // Iterator'ları geçersiz kılabilir
   it = vec.erase(it);  // Silme sonrası iterator'ı güncelleyin
   ```

2. **Container Modifikasyonları:**
   ```cpp
   // Yanlış: iterasyon sırasında container modifikasyonu
   for(auto it = vec.begin(); it != vec.end(); ++it) {
       if(condition) vec.push_back(x);  // Iterator invalidation!
   }
   ```

3. **Algorithm Önkoşulları:**
   ```cpp
   // Yanlış: binary_search sıralı range gerektirir
   std::binary_search(vec.begin(), vec.end(), x);  // Sıralı değilse tanımsız
   ```

4. **Bellek Yönetimi:**
   ```cpp
   // Yanlış: bellek sızıntısı
   std::vector<int*> vec;
   vec.push_back(new int(42));  // Manuel temizlik gerekli
   
   // Doğru: smart pointer kullanımı
   std::vector<std::unique_ptr<int>> vec;
   vec.push_back(std::make_unique<int>(42));
   ```
``` 