# Stack (Yığın) Veri Yapısı

## İçindekiler
1. [Genel Bakış](#genel-bakış)
2. [Stack Türleri](#stack-türleri)
3. [Operasyonlar](#operasyonlar)
4. [Performans Analizi](#performans-analizi)
5. [Kullanım Örnekleri](#kullanım-örnekleri)
6. [Derleme ve Test](#derleme-ve-test)

## Genel Bakış
Stack (Yığın), LIFO (Last In First Out - Son Giren İlk Çıkar) prensibiyle çalışan bir veri yapısıdır. Bu implementasyon, array ve linked list tabanlı olmak üzere iki farklı yaklaşımı içermektedir.

## Stack Türleri

### Array Stack
Array tabanlı stack implementasyonu, sabit boyutlu bir dizi kullanarak elemanları saklar. Bu yaklaşım, bellek kullanımı açısından daha verimlidir ancak maksimum kapasite sınırlaması vardır.

```cpp
ArrayStack<int> stack(5); // 5 elemanlık bir stack oluşturur
```

### Linked Stack
Linked list tabanlı stack implementasyonu, dinamik bellek kullanarak elemanları saklar. Bu yaklaşım, boyut sınırlaması olmadan çalışabilir ancak her eleman için ekstra bellek gerektirir.

```cpp
LinkedStack<int> stack; // Sınırsız kapasiteli bir stack oluşturur
```

## Operasyonlar

### Temel Operasyonlar
- `push(T value)`: Stack'e yeni bir eleman ekler
- `pop()`: Stack'in en üstündeki elemanı çıkarır ve döndürür
- `peek()`: Stack'in en üstündeki elemanı döndürür (çıkarmadan)
- `isEmpty()`: Stack'in boş olup olmadığını kontrol eder
- `size()`: Stack'teki eleman sayısını döndürür
- `clear()`: Stack'i temizler

### Array Stack için Ek Operasyonlar
- `isFull()`: Stack'in dolu olup olmadığını kontrol eder

## Performans Analizi

| Operasyon | Array Stack | Linked Stack |
|-----------|-------------|--------------|
| push      | O(1)        | O(1)         |
| pop       | O(1)        | O(1)         |
| peek      | O(1)        | O(1)         |
| isEmpty   | O(1)        | O(1)         |
| isFull    | O(1)        | N/A          |
| size      | O(1)        | O(1)         |
| clear     | O(1)        | O(n)         |

## Kullanım Örnekleri

### Array Stack Örneği
```cpp
ArrayStack<int> stack(3);
stack.push(1);
stack.push(2);
stack.push(3);

while (!stack.isEmpty()) {
    std::cout << stack.pop() << " "; // 3 2 1
}
```

### Linked Stack Örneği
```cpp
LinkedStack<std::string> stack;
stack.push("Merhaba");
stack.push("Dünya");

std::cout << stack.peek() << std::endl; // "Dünya"
stack.pop();
std::cout << stack.peek() << std::endl; // "Merhaba"
```

## Derleme ve Test

Projeyi derlemek ve testleri çalıştırmak için:

```bash
mkdir build && cd build
cmake ..
make
./stack_test
```

Test sonuçları, her iki stack implementasyonu için temel operasyonların, hata durumlarının ve özel durumların kontrolünü içerir.
