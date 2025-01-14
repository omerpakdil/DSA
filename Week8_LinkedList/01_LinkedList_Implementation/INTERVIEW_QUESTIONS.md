# Linked List Mülakat Soruları

## Başlangıç Seviyesi (⭐)

### S1 ⭐ Linked List nedir ve array ile karşılaştırıldığında avantaj ve dezavantajları nelerdir?
**Cevap**: Linked List, her elemanın bir sonraki elemanın adresini tuttuğu dinamik bir veri yapısıdır.

Avantajları:
- Dynamic size (çalışma zamanında büyüyüp küçülebilir)
- O(1) insertion/deletion operasyonları (baştan)
- Memory kullanımı ihtiyaca göre

Dezavantajları:
- Random access yok (index ile erişim O(n))
- Her node için extra pointer memory gerekli
- Cache performance array'lere göre daha düşük

### S2 ⭐ Linked List'in başına ve sonuna eleman ekleme işlemlerinin time complexity'si nedir? Neden?
**Cevap**: 
- Head'e ekleme: O(1) - Sadece head pointer güncellenir
- Tail'e ekleme: 
  - Tail pointer varsa: O(1)
  - Tail pointer yoksa: O(n) - Liste sonuna kadar traverse edilmeli
```cpp
void pushFront(T value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

void pushBack(T value) {  // with tail
    Node* newNode = new Node(value);
    if (!tail) head = tail = newNode;
    else {
        tail->next = newNode;
        tail = newNode;
    }
}
```

### S3 ⭐ Linked List'te verilen bir elemanı silme işleminin time complexity'si nedir? Nasıl implemente edilir?
**Cevap**: O(n) - Node'u bulmak için liste traverse edilmeli
```cpp
void removeValue(T value) {
    Node* current = head;
    Node* prev = nullptr;
    
    while (current && current->data != value) {
        prev = current;
        current = current->next;
    }
    
    if (current) {  // node bulundu
        if (prev) prev->next = current->next;
        else head = current->next;
        delete current;
    }
}
```

### S4 ⭐ Linked List'in ortasındaki node'u nasıl bulursunuz?
**Cevap**: Two pointer tekniği kullanarak (slow ve fast pointer)
```cpp
Node* findMiddle() {
    if (!head) return nullptr;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}
```

### S5 ⭐ Linked List'te cycle olup olmadığını nasıl kontrol edersiniz?
**Cevap**: Floyd's cycle-finding algorithm ile (tortoise and hare)
```cpp
bool hasCycle() {
    if (!head) return false;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    
    return false;
}
```

## Orta Seviye (⭐⭐)

### S6 ⭐⭐ Linked List'i reverse etme işlemini nasıl gerçekleştirirsiniz?
**Cevap**: Three pointer tekniği kullanarak (prev, current, next)
```cpp
void reverse() {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    head = prev;
}
```

### S7 ⭐⭐ İki sorted Linked List'i merge etme işlemini nasıl gerçekleştirirsiniz?
**Cevap**: İki liste üzerinde iterasyon yaparak küçük node'u seçme
```cpp
LinkedList merge(const LinkedList& other) {
    LinkedList result;
    Node* p1 = head;
    Node* p2 = other.head;
    
    while (p1 && p2) {
        if (p1->data <= p2->data) {
            result.pushBack(p1->data);
            p1 = p1->next;
        } else {
            result.pushBack(p2->data);
            p2 = p2->next;
        }
    }
    
    while (p1) {
        result.pushBack(p1->data);
        p1 = p1->next;
    }
    
    while (p2) {
        result.pushBack(p2->data);
        p2 = p2->next;
    }
    
    return result;
}
```

### S8 ⭐⭐ Linked List'te k'ıncı node'u sondan nasıl bulursunuz?
**Cevap**: Two pointer tekniği kullanarak (aralarında k node mesafe olacak şekilde)
```cpp
Node* findFromEnd(int k) {
    if (!head || k <= 0) return nullptr;
    
    Node* fast = head;
    Node* slow = head;
    
    // Fast pointer'ı k adım ilerlet
    for (int i = 0; i < k; i++) {
        if (!fast) return nullptr;
        fast = fast->next;
    }
    
    // İki pointer'ı birlikte ilerlet
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}
```

### S9 ⭐⭐ Linked List'te palindrome kontrolünü nasıl yaparsınız?
**Cevap**: Middle node'u bul, ikinci yarıyı reverse et, karşılaştır
```cpp
bool isPalindrome() {
    if (!head || !head->next) return true;
    
    // 1. Middle node'u bul
    Node* slow = head;
    Node* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // 2. İkinci yarıyı reverse et
    Node* secondHalf = reverseList(slow->next);
    
    // 3. Karşılaştır
    Node* firstHalf = head;
    while (secondHalf) {
        if (firstHalf->data != secondHalf->data) return false;
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    
    return true;
}
```

### S10 ⭐⭐ İki Linked List'in intersection point'ini nasıl bulursunuz?
**Cevap**: Two pointer tekniği kullanarak, listelerin sonuna gelince diğer listenin başına geçerek
```cpp
Node* findIntersection(LinkedList& other) {
    if (!head || !other.head) return nullptr;
    
    Node* p1 = head;
    Node* p2 = other.head;
    
    while (p1 != p2) {
        p1 = p1 ? p1->next : other.head;
        p2 = p2 ? p2->next : head;
    }
    
    return p1;
}
```

### S11 ⭐ Linked List'te verilen n'inci node'u nasıl bulursunuz? Recursive ve iterative çözümleri nelerdir?
**Cevap**: İki yaklaşım da mümkündür:

Iterative çözüm (O(n)):
```cpp
Node* getNthNode(int n) {
    if (n < 0) return nullptr;
    Node* current = head;
    for (int i = 0; i < n && current; i++) {
        current = current->next;
    }
    return current;
}
```

Recursive çözüm (O(n)):
```cpp
Node* getNthNodeRecursive(Node* head, int n) {
    if (!head || n < 0) return nullptr;
    if (n == 0) return head;
    return getNthNodeRecursive(head->next, n-1);
}
```

### S12 ⭐⭐ Linked List'te loop'un başlangıç node'unu nasıl bulursunuz?
**Cevap**: Floyd's cycle detection algorithm'in modifiye edilmiş versiyonu ile:
```cpp
Node* findLoopStart() {
    Node* slow = head;
    Node* fast = head;
    bool hasLoop = false;
    
    // Loop'u tespit et
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            hasLoop = true;
            break;
        }
    }
    
    if (!hasLoop) return nullptr;
    
    // Loop başlangıcını bul
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}
```

### S13 ⭐⭐ Linked List'i recursive olarak nasıl reverse edersiniz?
**Cevap**: Recursive yaklaşım:
```cpp
Node* reverseRecursive(Node* head) {
    if (!head || !head->next) return head;
    
    Node* rest = reverseRecursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    
    return rest;
}
```

### S14 ⭐ Linked List'te belirli bir değere sahip tüm node'ları nasıl silersiniz?
**Cevap**: Tüm listeyi traverse ederek:
```cpp
void removeAllOccurrences(const T& value) {
    Node* current = head;
    Node* prev = nullptr;
    
    while (current) {
        if (current->data == value) {
            Node* temp = current;
            if (prev) prev->next = current->next;
            else head = current->next;
            current = current->next;
            delete temp;
        } else {
            prev = current;
            current = current->next;
        }
    }
}
```

### S15 ⭐⭐ İki Linked List'in toplamını yeni bir Linked List olarak nasıl döndürürsünüz? (Sayılar ters sırada verilmiş)
**Cevap**: Her basamağı toplayıp carry'i takip ederek:
```cpp
LinkedList<int> addTwoNumbers(const LinkedList<int>& l1, const LinkedList<int>& l2) {
    LinkedList<int> result;
    Node* p1 = l1.head;
    Node* p2 = l2.head;
    int carry = 0;
    
    while (p1 || p2 || carry) {
        int sum = carry;
        if (p1) {
            sum += p1->data;
            p1 = p1->next;
        }
        if (p2) {
            sum += p2->data;
            p2 = p2->next;
        }
        
        result.pushBack(sum % 10);
        carry = sum / 10;
    }
    
    return result;
}
```

### S16 ⭐⭐ Linked List'i her k node'da bir nasıl gruplar halinde reverse edersiniz?
**Cevap**: Her k node için recursive yaklaşım:
```cpp
Node* reverseKGroup(Node* head, int k) {
    // Yeterli node var mı kontrol et
    Node* current = head;
    int count = 0;
    while (current && count < k) {
        current = current->next;
        count++;
    }
    
    if (count < k) return head;
    
    // k node'u reverse et
    current = head;
    Node* prev = nullptr;
    Node* next = nullptr;
    count = 0;
    
    while (current && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    
    // Recursive olarak devam et
    if (next) {
        head->next = reverseKGroup(next, k);
    }
    
    return prev;
}
```

### S17 ⭐ Linked List'te alternate node'ları nasıl silersiniz?
**Cevap**: Her ikinci node'u atlayarak:
```cpp
void deleteAlternate() {
    Node* current = head;
    
    while (current && current->next) {
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        current = current->next;
    }
}
```

### S18 ⭐⭐ Linked List'i node değerlerine göre nasıl partition edersiniz?
**Cevap**: İki ayrı liste oluşturup birleştirerek:
```cpp
void partition(const T& x) {
    Node* beforeStart = nullptr;
    Node* beforeEnd = nullptr;
    Node* afterStart = nullptr;
    Node* afterEnd = nullptr;
    
    // Partition yap
    Node* current = head;
    while (current) {
        Node* next = current->next;
        current->next = nullptr;
        
        if (current->data < x) {
            if (!beforeStart) {
                beforeStart = current;
                beforeEnd = beforeStart;
            } else {
                beforeEnd->next = current;
                beforeEnd = current;
            }
        } else {
            if (!afterStart) {
                afterStart = current;
                afterEnd = afterStart;
            } else {
                afterEnd->next = current;
                afterEnd = current;
            }
        }
        current = next;
    }
    
    // Listeleri birleştir
    if (!beforeStart) {
        head = afterStart;
    } else {
        head = beforeStart;
        beforeEnd->next = afterStart;
    }
}
```

### S19 ⭐⭐ Linked List'te belirli bir pattern'i nasıl ararsınız?
**Cevap**: Pattern matching algoritması kullanarak:
```cpp
bool searchPattern(LinkedList<T>& pattern) {
    Node* current = head;
    
    while (current) {
        Node* patternNode = pattern.head;
        Node* mainNode = current;
        
        while (patternNode) {
            if (!mainNode || mainNode->data != patternNode->data) break;
            mainNode = mainNode->next;
            patternNode = patternNode->next;
        }
        
        if (!patternNode) return true;  // Pattern bulundu
        current = current->next;
    }
    
    return false;
}
```

### S20 ⭐⭐ Linked List'te her node'un random pointer'ı da varsa, deep copy'sini nasıl çıkarırsınız?
**Cevap**: İki pass yaklaşımı ile:
```cpp
struct NodeWithRandom {
    T data;
    NodeWithRandom* next;
    NodeWithRandom* random;
};

LinkedList deepCopy() {
    LinkedList result;
    std::unordered_map<NodeWithRandom*, NodeWithRandom*> nodeMap;
    
    // İlk pass: node'ları kopyala
    NodeWithRandom* current = head;
    while (current) {
        nodeMap[current] = new NodeWithRandom(current->data);
        current = current->next;
    }
    
    // İkinci pass: pointer'ları bağla
    current = head;
    while (current) {
        NodeWithRandom* copy = nodeMap[current];
        copy->next = nodeMap[current->next];
        copy->random = nodeMap[current->random];
        current = current->next;
    }
    
    result.head = nodeMap[head];
    return result;
}
```

### S21 ⭐ Linked List'te tekrar eden node'ları nasıl kaldırırsınız? (sorted ve unsorted durumlar için)
**Cevap**: İki farklı yaklaşım:

Sorted liste için (O(n)):
```cpp
void removeDuplicatesSorted() {
    if (!head || !head->next) return;
    
    Node* current = head;
    while (current->next) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}
```

Unsorted liste için (O(n) space, O(n) time):
```cpp
void removeDuplicatesUnsorted() {
    if (!head || !head->next) return;
    
    std::unordered_set<T> seen;
    Node* current = head;
    Node* prev = nullptr;
    
    while (current) {
        if (seen.find(current->data) != seen.end()) {
            prev->next = current->next;
            delete current;
            current = prev->next;
        } else {
            seen.insert(current->data);
            prev = current;
            current = current->next;
        }
    }
}
```

### S22 ⭐ Linked List'te belirli bir pozisyondan sonra node eklemek için recursive çözüm nasıl olur?
**Cevap**: Recursive yaklaşım:
```cpp
Node* insertRecursive(Node* head, int position, T value) {
    if (position < 0) return head;
    
    if (position == 0) {
        Node* newNode = new Node(value);
        newNode->next = head;
        return newNode;
    }
    
    if (head) {
        head->next = insertRecursive(head->next, position - 1, value);
    }
    
    return head;
}
```

### S23 ⭐⭐ İki Linked List'in kesişim noktasını O(1) extra space ile nasıl bulursunuz?
**Cevap**: Length difference yaklaşımı:
```cpp
Node* findIntersectionOptimized(LinkedList& other) {
    int len1 = 0, len2 = 0;
    Node* ptr1 = head;
    Node* ptr2 = other.head;
    
    // Uzunlukları hesapla
    while (ptr1) { len1++; ptr1 = ptr1->next; }
    while (ptr2) { len2++; ptr2 = ptr2->next; }
    
    // Başlangıç noktalarını ayarla
    ptr1 = head;
    ptr2 = other.head;
    
    if (len1 > len2) {
        for (int i = 0; i < len1 - len2; i++) ptr1 = ptr1->next;
    } else {
        for (int i = 0; i < len2 - len1; i++) ptr2 = ptr2->next;
    }
    
    // Kesişim noktasını bul
    while (ptr1 && ptr2) {
        if (ptr1 == ptr2) return ptr1;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    
    return nullptr;
}
```

### S24 ⭐⭐ Linked List'te son n elementi nasıl reverse edersiniz?
**Cevap**: Two pointer ve reverse tekniği:
```cpp
void reverseLastN(int n) {
    if (n <= 1 || !head) return;
    
    Node* current = head;
    int length = 0;
    while (current) { length++; current = current->next; }
    
    if (n > length) n = length;
    
    Node* prev = nullptr;
    current = head;
    
    // n-length kadar ilerle
    for (int i = 0; i < length - n; i++) {
        prev = current;
        current = current->next;
    }
    
    // Son n elementi reverse et
    Node* last = current;
    Node* prev2 = nullptr;
    Node* next = nullptr;
    
    while (current) {
        next = current->next;
        current->next = prev2;
        prev2 = current;
        current = next;
    }
    
    if (prev) prev->next = prev2;
    else head = prev2;
    last->next = current;
}
```

### S25 ⭐ Linked List'te her k'ıncı elementi nasıl silersiniz?
**Cevap**: Counter kullanarak:
```cpp
void deleteEveryKth(int k) {
    if (k <= 1 || !head) return;
    
    Node* current = head;
    Node* prev = nullptr;
    int count = 1;
    
    while (current) {
        if (count == k) {
            Node* temp = current;
            if (prev) prev->next = current->next;
            else head = current->next;
            current = current->next;
            delete temp;
            count = 1;
        } else {
            prev = current;
            current = current->next;
            count++;
        }
    }
}
```

### S26 ⭐ Linked List'te ardışık node'ların yerini nasıl değiştirirsiniz?
**Cevap**: Pair-wise swap:
```cpp
void pairwiseSwap() {
    if (!head || !head->next) return;
    
    Node* prev = nullptr;
    Node* current = head;
    
    while (current && current->next) {
        Node* next = current->next;
        current->next = next->next;
        next->next = current;
        
        if (prev) prev->next = next;
        else head = next;
        
        prev = current;
        current = current->next;
    }
}
```

### S27 ⭐ Linked List'te belirli bir değerin frekansını nasıl bulursunuz?
**Cevap**: Iterative traversal:
```cpp
int frequency(const T& value) {
    int count = 0;
    Node* current = head;
    
    while (current) {
        if (current->data == value) count++;
        current = current->next;
    }
    
    return count;
}
```

### S28 ⭐⭐ İki Linked List'in farkını nasıl bulursunuz? (Set difference)
**Cevap**: Hash set kullanarak:
```cpp
LinkedList difference(const LinkedList& other) {
    LinkedList result;
    std::unordered_set<T> otherElements;
    
    // Diğer listenin elemanlarını hash set'e ekle
    Node* current = other.head;
    while (current) {
        otherElements.insert(current->data);
        current = current->next;
    }
    
    // Farklı elemanları bul
    current = head;
    while (current) {
        if (otherElements.find(current->data) == otherElements.end()) {
            result.pushBack(current->data);
        }
        current = current->next;
    }
    
    return result;
}
```

### S29 ⭐⭐ Linked List'te en çok tekrar eden elementi nasıl bulursunuz?
**Cevap**: Hash map kullanarak:
```cpp
T mostFrequent() {
    if (!head) throw std::runtime_error("List is empty");
    
    std::unordered_map<T, int> frequency;
    Node* current = head;
    T mostFreq = head->data;
    int maxCount = 0;
    
    while (current) {
        frequency[current->data]++;
        if (frequency[current->data] > maxCount) {
            maxCount = frequency[current->data];
            mostFreq = current->data;
        }
        current = current->next;
    }
    
    return mostFreq;
}
```

### S30 ⭐⭐ Linked List'te verilen iki indeks arasındaki node'ları nasıl reverse edersiniz?
**Cevap**: Three pointer tekniği ile belirli aralığı reverse etme:
```cpp
void reverseBetween(int start, int end) {
    if (start < 0 || end < 0 || start >= end || !head) return;
    
    Node dummy(T());  // Dummy node başa ekle
    dummy.next = head;
    Node* prev = &dummy;
    
    // Start pozisyonuna git
    for (int i = 0; i < start; i++) {
        if (!prev->next) return;
        prev = prev->next;
    }
    
    // Reverse işlemi
    Node* current = prev->next;
    Node* next = nullptr;
    Node* first = current;
    
    for (int i = 0; i <= end - start && current; i++) {
        next = current->next;
        current->next = prev->next;
        prev->next = current;
        current = next;
    }
    
    first->next = current;
    head = dummy.next;
}
```

Her soru için önemli noktalar:
- Time/Space complexity analizi
- Edge case'lerin kontrolü
- Memory management
- Optimizasyon fırsatları
- Test senaryoları
