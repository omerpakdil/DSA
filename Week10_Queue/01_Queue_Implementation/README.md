# Queue (Kuyruk) Veri Yapısı

Bu projede, farklı Queue (Kuyruk) implementasyonları ve bunların kullanım örnekleri yer almaktadır.

## İçindekiler
1. [Genel Bakış](#genel-bakış)
2. [Queue Türleri](#queue-türleri)
3. [Operasyonlar](#operasyonlar)
4. [Performans Analizi](#performans-analizi)
5. [Kullanım Örnekleri](#kullanım-örnekleri)
6. [Derleme ve Test](#derleme-ve-test)

## Genel Bakış
Queue (Kuyruk), FIFO (First In First Out) prensibine göre çalışan bir veri yapısıdır. Bu implementasyonda aşağıdaki Queue türleri bulunmaktadır:
- Array Queue: Sabit boyutlu dizi tabanlı implementasyon
- Circular Queue: Dinamik büyüyen dairesel queue implementasyonu
- Linked Queue: Bağlı liste tabanlı implementasyon
- Deque: Çift yönlü queue implementasyonu
- Priority Queue: Öncelikli queue implementasyonu
- Stack Queue: İki stack kullanarak queue implementasyonu

## Queue Türleri

### Array Queue
```cpp
ArrayQueue<T> queue(10); // 10 elemanlık queue oluşturma
queue.enqueue(5);        // Eleman ekleme
int value = queue.dequeue(); // Eleman çıkarma
```

### Circular Queue
```cpp
CircularQueue<T> queue(5); // 5 elemanlık dairesel queue
// Kapasite aşıldığında otomatik büyür
queue.enqueue(1);
queue.enqueue(2);
```

### Linked Queue
```cpp
LinkedQueue<T> queue;    // Bağlı liste tabanlı queue
queue.enqueue(3);        // Eleman ekleme
T value = queue.peek();  // Baştaki elemanı görüntüleme
```

### Deque
```cpp
Deque<T> deque;         // Çift yönlü queue
deque.addFront(1);      // Başa ekleme
deque.addRear(2);       // Sona ekleme
deque.removeFront();    // Baştan çıkarma
deque.removeRear();     // Sondan çıkarma
```

### Priority Queue
```cpp
PriorityQueue<T> pq;    // Öncelikli queue (Min Heap)
pq.enqueue(5);          // Eleman ekleme
pq.enqueue(2);          // 2, 5'ten önce çıkar
```

### Stack Queue
```cpp
StackQueue<T> queue;     // İki stack ile queue
queue.enqueue(1);       // O(1) ekleme
queue.dequeue();        // Amortized O(1) çıkarma
```

## Operasyonlar

Her Queue türü için temel operasyonlar:
- `enqueue/addFront/addRear`: Eleman ekleme
- `dequeue/removeFront/removeRear`: Eleman çıkarma
- `peek/peekFront/peekRear`: Elemanı görüntüleme
- `isEmpty`: Boş olma kontrolü
- `getSize`: Eleman sayısını öğrenme

## Performans Analizi

| Operasyon | Array Queue | Circular Queue | Linked Queue | Deque | Priority Queue | Stack Queue |
|-----------|-------------|----------------|--------------|-------|----------------|-------------|
| Enqueue   | O(1)        | O(1)*         | O(1)         | O(1)  | O(log n)       | O(1)        |
| Dequeue   | O(1)        | O(1)          | O(1)         | O(1)  | O(log n)       | O(1)**      |
| Peek      | O(1)        | O(1)          | O(1)         | O(1)  | O(1)           | O(1)        |
| Space     | O(n)        | O(n)          | O(n)         | O(n)  | O(n)           | O(n)        |

\* Yeniden boyutlandırma gerektiğinde O(n)
\** Amortized analiz

## Kullanım Örnekleri

```cpp
// Integer queue örneği
ArrayQueue<int> numbers(5);
numbers.enqueue(1);
numbers.enqueue(2);
numbers.enqueue(3);
while (!numbers.isEmpty()) {
    std::cout << numbers.dequeue() << " ";
}

// String queue örneği
LinkedQueue<std::string> messages;
messages.enqueue("Hello");
messages.enqueue("World");
std::cout << messages.peek() << std::endl; // "Hello" yazdırır
```

## Derleme ve Test

Projeyi derlemek ve testleri çalıştırmak için:

```bash
mkdir build && cd build
cmake ..
make
./queue_test
```

Tüm testler başarılı olduğunda "Tüm testler başarıyla tamamlandı!" mesajı görüntülenir.
