# Queue Mülakat Soruları

## Temel Queue Soruları

### S1 ⭐ Queue veri yapısı nedir ve hangi prensibe göre çalışır?
Queue, FIFO (First In First Out) prensibine göre çalışan bir veri yapısıdır. İlk giren eleman ilk çıkar.

**Örnek Kod:**
```cpp
template<typename T>
class Queue {
    // ... implementation details
    void enqueue(const T& value);  // Sona eleman ekler
    T dequeue();                   // Baştaki elemanı çıkarır
};
```

**Time Complexity:** Enqueue ve Dequeue operasyonları O(1)

### S2 ⭐ Queue ile Stack arasındaki temel farklar nelerdir?
- Queue FIFO, Stack LIFO prensibi
- Queue'da front ve rear pointer, Stack'te sadece top pointer
- Queue'da eleman ekleme rear'dan, çıkarma front'tan; Stack'te her ikisi de top'tan

### S3 ⭐⭐ Circular Queue nedir ve neden kullanılır?
Circular Queue, normal queue'nun dezavantajlarını gidermek için kullanılan bir implementasyondur. Array'in sonuna gelindiğinde başa dönerek boş alanları kullanır.

**Örnek Kod:**
```cpp
template<typename T>
class CircularQueue {
private:
    T* elements;
    int front, rear, size, capacity;
    
public:
    void enqueue(const T& value) {
        if (isFull()) resize();
        rear = (rear + 1) % capacity;
        elements[rear] = value;
        size++;
    }
};
```

**Time Complexity:** Normal operasyonlar O(1), resize gerektiğinde O(n)

### S4 ⭐⭐ Priority Queue nasıl implemente edilir ve hangi veri yapısını kullanır?
Priority Queue genellikle Heap (Binary Heap) kullanılarak implemente edilir. Her eleman bir öncelik değerine sahiptir.

**Örnek Kod:**
```cpp
template<typename T>
class PriorityQueue {
private:
    vector<T> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);
    
public:
    void enqueue(const T& value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }
};
```

**Time Complexity:** Enqueue ve Dequeue O(log n)

### S5 ⭐⭐ Deque (Double Ended Queue) nedir ve nasıl implemente edilir?
Deque, her iki ucundan da ekleme ve çıkarma yapılabilen bir queue türüdür. Genellikle doubly linked list ile implemente edilir.

**Örnek Kod:**
```cpp
template<typename T>
class Deque {
private:
    struct Node {
        T data;
        Node *prev, *next;
    };
    Node *front, *rear;
    
public:
    void addFront(const T& value);
    void addRear(const T& value);
    T removeFront();
    T removeRear();
};
```

**Time Complexity:** Tüm operasyonlar O(1)

### S6 ⭐⭐ İki stack kullanarak queue nasıl implemente edilir?
İki stack kullanarak queue implementasyonu, bir stack'i enqueue için diğerini dequeue için kullanır.

**Örnek Kod:**
```cpp
template<typename T>
class StackQueue {
private:
    stack<T> s1; // Enqueue için
    stack<T> s2; // Dequeue için
    
public:
    void enqueue(const T& value) {
        s1.push(value);
    }
    
    T dequeue() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        T value = s2.top();
        s2.pop();
        return value;
    }
};
```

**Time Complexity:** Enqueue O(1), Dequeue amortized O(1)

### S7 ⭐⭐ Queue'yu thread-safe yapmak için neler yapılmalıdır?
Thread-safe queue implementasyonu için mutex ve lock kullanılmalıdır.

**Örnek Kod:**
```cpp
template<typename T>
class ThreadSafeQueue {
private:
    queue<T> q;
    mutable mutex mtx;
    
public:
    void enqueue(const T& value) {
        lock_guard<mutex> lock(mtx);
        q.push(value);
    }
    
    T dequeue() {
        lock_guard<mutex> lock(mtx);
        if (q.empty()) throw runtime_error("Queue is empty");
        T value = q.front();
        q.pop();
        return value;
    }
};
```

**Time Complexity:** Her operasyon için ek thread synchronization overhead'i

### S8 ⭐⭐ Queue kullanarak LRU Cache nasıl implemente edilir?
LRU (Least Recently Used) Cache, queue ve hash map kombinasyonu kullanılarak implemente edilir.

**Örnek Kod:**
```cpp
template<typename K, typename V>
class LRUCache {
private:
    int capacity;
    list<pair<K,V>> items;
    unordered_map<K, list<pair<K,V>>::iterator> cache;
    
public:
    void put(const K& key, const V& value) {
        if (cache.find(key) != cache.end()) {
            items.erase(cache[key]);
        }
        items.push_front({key, value});
        cache[key] = items.begin();
        
        if (cache.size() > capacity) {
            cache.erase(items.back().first);
            items.pop_back();
        }
    }
};
```

**Time Complexity:** Get ve Put operasyonları O(1)

### S9 ⭐⭐⭐ Sliding Window Maximum problemi queue kullanarak nasıl çözülür?
Deque kullanarak sliding window maximum problemi etkin bir şekilde çözülebilir.

**Örnek Kod:**
```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq;
    
    for (int i = 0; i < nums.size(); i++) {
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}
```

**Time Complexity:** O(n), her eleman en fazla bir kez deque'ya girer ve çıkar

### S10 ⭐⭐⭐ Queue kullanarak Graph'ta Level Order Traversal nasıl yapılır?
BFS (Breadth First Search) algoritması queue kullanılarak implemente edilir.

**Örnek Kod:**
```cpp
void levelOrderTraversal(Node* root) {
    if (!root) return;
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << endl;
    }
}
```

**Time Complexity:** O(n), her node bir kez ziyaret edilir

### S11 ⭐ Queue kullanarak string'deki kelimeleri ters sırada yazdırma
Queue ve stack kullanarak bir string'deki kelimeleri ters sırada yazdırma.

**Örnek Kod:**
```cpp
void reverseWords(string& s) {
    queue<string> words;
    string word;
    stringstream ss(s);
    
    // Kelimeleri queue'ya ekle
    while (ss >> word) {
        words.push(word);
    }
    
    // Stack'e aktar
    stack<string> reverseOrder;
    while (!words.empty()) {
        reverseOrder.push(words.front());
        words.pop();
    }
    
    // Ters sırada yazdır
    s.clear();
    while (!reverseOrder.empty()) {
        s += reverseOrder.top() + " ";
        reverseOrder.pop();
    }
}
```

**Time Complexity:** O(n), n kelime sayısı

### S12 ⭐ Queue kullanarak binary sayıları sıralı üretme
1'den n'e kadar binary sayıları queue kullanarak üretme.

**Örnek Kod:**
```cpp
vector<string> generateBinary(int n) {
    vector<string> result;
    queue<string> q;
    q.push("1");
    
    while (n--) {
        string current = q.front();
        q.pop();
        result.push_back(current);
        
        q.push(current + "0");
        q.push(current + "1");
    }
    return result;
}
```

**Time Complexity:** O(n)

### S13 ⭐⭐ Queue kullanarak task scheduling
Priority queue kullanarak task scheduling implementasyonu.

**Örnek Kod:**
```cpp
struct Task {
    int id;
    int priority;
    string name;
    
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};

class TaskScheduler {
private:
    priority_queue<Task> tasks;
    
public:
    void addTask(const Task& task) {
        tasks.push(task);
    }
    
    Task getNextTask() {
        if (tasks.empty()) throw runtime_error("No tasks available");
        Task next = tasks.top();
        tasks.pop();
        return next;
    }
};
```

**Time Complexity:** Add ve Get operasyonları O(log n)

### S14 ⭐ Queue'da first unique character bulma
Queue kullanarak bir string'deki ilk tekrar etmeyen karakteri bulma.

**Örnek Kod:**
```cpp
char firstUnique(string s) {
    queue<char> q;
    unordered_map<char, int> count;
    
    for (char c : s) {
        q.push(c);
        count[c]++;
    }
    
    while (!q.empty() && count[q.front()] > 1) {
        q.pop();
    }
    
    return q.empty() ? '\0' : q.front();
}
```

**Time Complexity:** O(n)

### S15 ⭐⭐ Queue kullanarak moving average hesaplama
Sliding window moving average hesaplama.

**Örnek Kod:**
```cpp
class MovingAverage {
private:
    queue<int> window;
    int size;
    double sum;
    
public:
    MovingAverage(int size) : size(size), sum(0) {}
    
    double next(int val) {
        if (window.size() == size) {
            sum -= window.front();
            window.pop();
        }
        
        window.push(val);
        sum += val;
        
        return sum / window.size();
    }
};
```

**Time Complexity:** Her next çağrısı O(1)

### S16 ⭐⭐ Queue kullanarak process scheduling
Round-robin process scheduling implementasyonu.

**Örnek Kod:**
```cpp
struct Process {
    int id;
    int burstTime;
};

void roundRobin(vector<Process>& processes, int quantum) {
    queue<Process> q;
    for (auto& p : processes) {
        q.push(p);
    }
    
    while (!q.empty()) {
        Process current = q.front();
        q.pop();
        
        if (current.burstTime > quantum) {
            current.burstTime -= quantum;
            q.push(current);
        }
        // Process tamamlandı
    }
}
```

**Time Complexity:** O(n * m), n process sayısı, m toplam burst time

### S17 ⭐ Queue kullanarak palindrome kontrolü
Deque kullanarak palindrome kontrolü yapma.

**Örnek Kod:**
```cpp
bool isPalindrome(string s) {
    deque<char> dq;
    
    // Sadece alfanumerik karakterleri al
    for (char c : s) {
        if (isalnum(c)) {
            dq.push_back(tolower(c));
        }
    }
    
    while (dq.size() > 1) {
        if (dq.front() != dq.back()) {
            return false;
        }
        dq.pop_front();
        dq.pop_back();
    }
    
    return true;
}
```

**Time Complexity:** O(n)

### S18 ⭐⭐ Queue kullanarak stock span hesaplama
Stock prices için span değerlerini hesaplama.

**Örnek Kod:**
```cpp
vector<int> calculateSpan(vector<int>& prices) {
    vector<int> spans(prices.size(), 1);
    stack<int> st;
    
    for (int i = 0; i < prices.size(); i++) {
        while (!st.empty() && prices[st.top()] <= prices[i]) {
            st.pop();
        }
        
        spans[i] = st.empty() ? i + 1 : i - st.top();
        st.push(i);
    }
    
    return spans;
}
```

**Time Complexity:** O(n)

### S19 ⭐⭐ Queue kullanarak tree zigzag traversal
Binary tree'yi zigzag sırada dolaşma.

**Örnek Kod:**
```cpp
vector<vector<int>> zigzagTraversal(Node* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<Node*> q;
    q.push(root);
    bool leftToRight = true;
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);
        
        for (int i = 0; i < size; i++) {
            Node* node = q.front();
            q.pop();
            
            int index = leftToRight ? i : size - 1 - i;
            level[index] = node->val;
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        leftToRight = !leftToRight;
        result.push_back(level);
    }
    
    return result;
}
```

**Time Complexity:** O(n)

### S20 ⭐⭐ Queue kullanarak medyan bulma
Priority queue kullanarak sliding window medyan bulma.

**Örnek Kod:**
```cpp
class MedianFinder {
private:
    priority_queue<int> maxHeap; // Sol yarı
    priority_queue<int, vector<int>, greater<int>> minHeap; // Sağ yarı
    
public:
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};
```

**Time Complexity:** Add O(log n), Find O(1)

### S21 ⭐ Queue kullanarak string'deki sayıları toplama
Queue kullanarak bir string içindeki sayıları toplama işlemi.

**Örnek Kod:**
```cpp
int sumNumbers(string s) {
    queue<int> numbers;
    int currentNum = 0;
    int sum = 0;
    
    for (char c : s) {
        if (isdigit(c)) {
            currentNum = currentNum * 10 + (c - '0');
        } else if (currentNum > 0) {
            numbers.push(currentNum);
            currentNum = 0;
        }
    }
    if (currentNum > 0) numbers.push(currentNum);
    
    while (!numbers.empty()) {
        sum += numbers.front();
        numbers.pop();
    }
    return sum;
}
```

**Time Complexity:** O(n), n string uzunluğu

### S22 ⭐ Queue kullanarak özel karakterleri kaldırma
Queue kullanarak bir string'den özel karakterleri kaldırma.

**Örnek Kod:**
```cpp
string removeSpecialChars(string s) {
    queue<char> chars;
    for (char c : s) {
        if (isalnum(c)) {
            chars.push(c);
        }
    }
    
    string result;
    while (!chars.empty()) {
        result += chars.front();
        chars.pop();
    }
    return result;
}
```

**Time Complexity:** O(n)

### S23 ⭐⭐ Queue kullanarak nested parantezleri genişletme
Queue kullanarak nested parantez içindeki sayıları genişletme.

**Örnek Kod:**
```cpp
string expandString(string s) {
    queue<char> result;
    stack<int> counts;
    stack<queue<char>> stored;
    int num = 0;
    
    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '(') {
            counts.push(num);
            stored.push(result);
            num = 0;
            queue<char> empty;
            result = empty;
        } else if (c == ')') {
            queue<char> temp = result;
            result = stored.top();
            stored.pop();
            int count = counts.top();
            counts.pop();
            while (count--) {
                queue<char> tempCopy = temp;
                while (!tempCopy.empty()) {
                    result.push(tempCopy.front());
                    tempCopy.pop();
                }
            }
        } else {
            result.push(c);
        }
    }
    
    string finalResult;
    while (!result.empty()) {
        finalResult += result.front();
        result.pop();
    }
    return finalResult;
}
```

**Time Complexity:** O(n * m), n string uzunluğu, m maksimum tekrar sayısı

### S24 ⭐⭐ Queue kullanarak palindrom alt dizileri bulma
Queue ve deque kullanarak bir string'deki palindrom alt dizileri bulma.

**Örnek Kod:**
```cpp
vector<string> findPalindromicSubstrings(string s) {
    vector<string> result;
    deque<char> dq;
    
    for (int i = 0; i < s.length(); i++) {
        // Tek uzunluklu palindromlar
        dq.clear();
        dq.push_back(s[i]);
        expandPalindrome(s, i-1, i+1, dq, result);
        
        // Çift uzunluklu palindromlar
        if (i < s.length()-1 && s[i] == s[i+1]) {
            dq.clear();
            dq.push_back(s[i]);
            dq.push_back(s[i+1]);
            expandPalindrome(s, i-1, i+2, dq, result);
        }
    }
    return result;
}

void expandPalindrome(string& s, int left, int right, deque<char>& dq, vector<string>& result) {
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
        dq.push_front(s[left]);
        dq.push_back(s[right]);
        string palindrome;
        queue<char> temp(dq);
        while (!temp.empty()) {
            palindrome += temp.front();
            temp.pop();
        }
        result.push_back(palindrome);
        left--;
        right++;
    }
}
```

**Time Complexity:** O(n²)

### S25 ⭐ Queue kullanarak kelime sayısını bulma
Queue kullanarak bir string'deki kelime sayısını bulma.

**Örnek Kod:**
```cpp
int countWords(string s) {
    queue<char> chars;
    int wordCount = 0;
    bool inWord = false;
    
    for (char c : s) {
        if (isspace(c)) {
            if (inWord) {
                wordCount++;
                inWord = false;
            }
        } else {
            inWord = true;
        }
    }
    if (inWord) wordCount++;
    
    return wordCount;
}
```

**Time Complexity:** O(n)

### S26 ⭐⭐ Queue kullanarak nested function call derinliğini bulma
Queue ve stack kullanarak nested function call'ların maksimum derinliğini bulma.

**Örnek Kod:**
```cpp
int maxCallDepth(string s) {
    stack<string> calls;
    queue<char> current;
    int maxDepth = 0;
    
    for (char c : s) {
        if (c == '(') {
            string funcName;
            while (!current.empty()) {
                funcName += current.front();
                current.pop();
            }
            calls.push(funcName);
            maxDepth = max(maxDepth, (int)calls.size());
        } else if (c == ')') {
            if (!calls.empty()) calls.pop();
        } else if (!isspace(c)) {
            current.push(c);
        }
    }
    
    return maxDepth;
}
```

**Time Complexity:** O(n)

### S27 ⭐ Queue kullanarak en uzun kelimeyi bulma
Queue kullanarak bir string'deki en uzun kelimeyi bulma.

**Örnek Kod:**
```cpp
string findLongestWord(string s) {
    queue<char> current;
    string longest;
    
    for (char c : s) {
        if (isspace(c)) {
            if (current.size() > longest.length()) {
                longest.clear();
                while (!current.empty()) {
                    longest += current.front();
                    current.pop();
                }
            } else {
                while (!current.empty()) current.pop();
            }
        } else {
            current.push(c);
        }
    }
    
    // Son kelimeyi kontrol et
    if (current.size() > longest.length()) {
        longest.clear();
        while (!current.empty()) {
            longest += current.front();
            current.pop();
        }
    }
    
    return longest;
}
```

**Time Complexity:** O(n)

### S28 ⭐⭐ Queue kullanarak XML tag'lerini validate etme
Queue ve stack kullanarak XML tag'lerinin doğruluğunu kontrol etme.

**Örnek Kod:**
```cpp
bool validateXML(string xml) {
    stack<string> tags;
    queue<char> current;
    bool inTag = false;
    
    for (char c : xml) {
        if (c == '<') {
            inTag = true;
        } else if (c == '>') {
            string tag;
            while (!current.empty()) {
                tag += current.front();
                current.pop();
            }
            
            if (tag[0] == '/') {
                if (tags.empty() || tags.top() != tag.substr(1)) {
                    return false;
                }
                tags.pop();
            } else {
                tags.push(tag);
            }
            inTag = false;
        } else if (inTag) {
            current.push(c);
        }
    }
    
    return tags.empty();
}
```

**Time Complexity:** O(n)

### S29 ⭐ Queue kullanarak rakamları ayırma
Queue kullanarak bir string'deki rakamları ayırma ve sıralama.

**Örnek Kod:**
```cpp
vector<int> extractNumbers(string s) {
    queue<int> numbers;
    int currentNum = 0;
    
    for (char c : s) {
        if (isdigit(c)) {
            currentNum = currentNum * 10 + (c - '0');
        } else if (currentNum > 0) {
            numbers.push(currentNum);
            currentNum = 0;
        }
    }
    if (currentNum > 0) numbers.push(currentNum);
    
    vector<int> result;
    while (!numbers.empty()) {
        result.push_back(numbers.front());
        numbers.pop();
    }
    sort(result.begin(), result.end());
    return result;
}
```

**Time Complexity:** O(n log n) (sıralama nedeniyle)

### S30 ⭐⭐ Queue kullanarak JSON yapısını validate etme
Queue ve stack kullanarak basit bir JSON yapısının doğruluğunu kontrol etme.

**Örnek Kod:**
```cpp
bool validateJSON(string json) {
    stack<char> brackets;
    queue<char> current;
    bool inString = false;
    
    for (char c : json) {
        if (c == '"' && (current.empty() || current.back() != '\\')) {
            inString = !inString;
        } else if (!inString) {
            if (c == '{' || c == '[') {
                brackets.push(c);
            } else if (c == '}') {
                if (brackets.empty() || brackets.top() != '{') return false;
                brackets.pop();
            } else if (c == ']') {
                if (brackets.empty() || brackets.top() != '[') return false;
                brackets.pop();
            }
        }
        current.push(c);
    }
    
    return brackets.empty() && !inString;
}
```

**Time Complexity:** O(n)
