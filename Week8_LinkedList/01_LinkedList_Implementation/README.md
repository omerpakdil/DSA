# Linked List (Bağlı Liste) Veri Yapısı

## İçindekiler
1. [Genel Bakış](#genel-bakış)
2. [Veri Yapısı](#veri-yapısı)
3. [Operasyonlar](#operasyonlar)
4. [Karmaşıklık Analizi](#karmaşıklık-analizi)
5. [Kullanım Örnekleri](#kullanım-örnekleri)
6. [Derleme ve Test](#derleme-ve-test)

## Genel Bakış
Bu implementasyon, template kullanılarak generic bir Linked List veri yapısını gerçekleştirir. Modern C++ özellikleri kullanılarak geliştirilmiş olup, temel ve ileri düzey operasyonları destekler.

## Veri Yapısı
```cpp
template<typename T>
class LinkedList {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;    // Başlangıç düğümü
    Node* tail;    // Son düğüm
    size_t size;   // Liste uzunluğu
};
```

## Operasyonlar
### Temel Operasyonlar
- `pushFront(value)`: Başa eleman ekleme
- `pushBack(value)`: Sona eleman ekleme
- `insert(index, value)`: Araya eleman ekleme
- `popFront()`: Baştan eleman silme
- `popBack()`: Sondan eleman silme
- `remove(index)`: İndexteki elemanı silme
- `removeValue(value)`: Değere göre silme

### Erişim Operasyonları
- `front()`: İlk elemana erişim
- `back()`: Son elemana erişim
- `at(index)`: İndexteki elemana erişim

### Arama ve Sorgulama
- `contains(value)`: Değer arama
- `find(value)`: İndex bulma
- `empty()`: Boş kontrolü
- `getSize()`: Uzunluk bilgisi

### İstatistiksel Operasyonlar
- `getMax()`: En büyük değer
- `getMin()`: En küçük değer
- `getSum()`: Toplam
- `getAverage()`: Ortalama

### Liste Manipülasyonu
- `reverse()`: Listeyi ters çevirme
- `sort()`: Sıralama (merge sort)
- `clear()`: Tüm elemanları silme

### Liste Birleştirme
- `concat(other)`: Liste birleştirme
- `merge(other)`: Sıralı birleştirme

### Özel Operasyonlar
- `findMiddle()`: Ortadaki elemanı bulma
- `findIntersection(other)`: Kesişim noktası bulma

## Karmaşıklık Analizi

| Operasyon | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| pushFront | O(1) | O(1) |
| pushBack | O(1) | O(1) |
| insert | O(n) | O(1) |
| popFront | O(1) | O(1) |
| popBack | O(n) | O(1) |
| remove | O(n) | O(1) |
| find | O(n) | O(1) |
| sort | O(n log n) | O(log n) |
| reverse | O(n) | O(1) |
| concat | O(n) | O(1) |
| merge | O(n + m) | O(n + m) |

## Kullanım Örnekleri
```cpp
// Integer list örneği
LinkedList<int> numbers;
numbers.pushBack(1);
numbers.pushBack(2);
numbers.pushBack(3);

// String list örneği
LinkedList<std::string> words;
words.pushBack("Hello");
words.pushBack("World");
```

## Derleme ve Test
```bash
# Build klasörü oluştur
mkdir build && cd build

# CMake ile konfigüre et
cmake ..

# Derle
make

# Testleri çalıştır
./linked_list_test
```
