# Array ADT Mülakat Soruları

## S1 ⭐
**Soru**: Array ADT nedir ve neden önemlidir? Temel operasyonlarını ve kompleksitelerini açıklayın.

**Cevap**: Array ADT (Abstract Data Type), array veri yapısı üzerinde gerçekleştirilebilecek operasyonların soyut bir tanımıdır. Şu bileşenleri içerir:

1. **Veri Bileşenleri**:
   - Array (veri deposu)
   - Size (mevcut eleman sayısı)
   - Capacity (maksimum kapasite)

2. **Temel Operasyonlar ve Kompleksiteleri**:
   ```cpp
   // Temel Operasyonlar
   append(element)    -> O(1)  // Sona ekleme
   insert(index, element) -> O(n)  // Araya ekleme
   remove(index)     -> O(n)  // Silme
   get(index)        -> O(1)  // Okuma
   set(index, element) -> O(1)  // Yazma
   ```

## S2 ⭐
**Soru**: Array ADT'de memory management nasıl yapılır? RAII prensibini açıklayın.

**Cevap**: Modern C++'ta Array ADT'de memory management şu şekilde yapılır:

```cpp
template<typename T>
class Array {
private:
    T* arr;  // Raw pointer
    int size;
    int capacity;
    
public:
    // RAII Constructor
    Array(int cap) : capacity(cap), size(0) {
        arr = new T[capacity];
    }
    
    // RAII Destructor
    ~Array() {
        delete[] arr;
    }
    
    // Copy constructor (deep copy)
    Array(const Array& other) : capacity(other.capacity), size(other.size) {
        arr = new T[capacity];
        std::copy(other.arr, other.arr + size, arr);
    }
    
    // Move constructor
    Array(Array&& other) noexcept 
        : arr(other.arr), size(other.size), capacity(other.capacity) {
        other.arr = nullptr;
        other.size = 0;
    }
};
```

## S3 ⭐⭐
**Soru**: Array ADT'de linear search ve binary search arasındaki farklar nelerdir? Hangi durumlarda hangisi tercih edilmelidir?

**Cevap**: 

1. **Linear Search**:
```cpp
int linearSearch(const T& key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}
```
- Time Complexity: O(n)
- Sıralı olmayan array'lerde kullanılabilir
- Küçük veri setlerinde etkili
- Memory access pattern daha iyi (cache-friendly)

2. **Binary Search**:
```cpp
int binarySearch(const T& key) {
    if (!isSorted()) throw std::runtime_error("Array must be sorted");
    
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
```
- Time Complexity: O(log n)
- Sadece sıralı array'lerde kullanılabilir
- Büyük veri setlerinde daha etkili
- Memory access pattern daha kötü (cache misses)

## S4 ⭐⭐
**Soru**: Array ADT'de duplicate elemanları nasıl bulursunuz? En verimli çözümü açıklayın.

**Cevap**: Duplicate elemanları bulmanın birkaç yöntemi vardır:

1. **Naive Approach (O(n²)):**
```cpp
Array<T> findDuplicates() const {
    Array<T> duplicates(size);
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                duplicates.append(arr[i]);
                break;
            }
        }
    }
    return duplicates;
}
```

2. **Hash Table Approach (O(n)):**
```cpp
Array<T> findDuplicatesEfficient() const {
    std::unordered_map<T, int> freq;
    Array<T> duplicates(size);
    
    for (int i = 0; i < size; i++) {
        freq[arr[i]]++;
        if (freq[arr[i]] == 2) {
            duplicates.append(arr[i]);
        }
    }
    return duplicates;
}
```

## S5 ⭐⭐
**Soru**: Array ADT'de bir array'i in-place olarak nasıl reverse edersiniz? Ekstra bellek kullanmadan çözümü açıklayın.

**Cevap**: Two-pointer yaklaşımı kullanarak O(n) time ve O(1) space complexity ile çözülebilir:

```cpp
void reverse() {
    int start = 0;
    int end = size - 1;
    
    while (start < end) {
        // XOR swap
        arr[start] = arr[start] ^ arr[end];
        arr[end] = arr[start] ^ arr[end];
        arr[start] = arr[start] ^ arr[end];
        
        start++;
        end--;
    }
}

// Alternatif modern C++ çözümü:
void reverse() {
    for (int i = 0; i < size/2; i++) {
        std::swap(arr[i], arr[size-1-i]);
    }
}
```

## S6 ⭐⭐⭐
**Soru**: Array ADT'de set operasyonlarını (union, intersection, difference) nasıl implemente edersiniz? Kompleksiteleri nedir?

**Cevap**: Set operasyonları şu şekilde implemente edilebilir:

1. **Union (Birleşim):**
```cpp
Array<T> getUnion(const Array& other) const {
    Array<T> result(capacity + other.capacity);
    
    // İlk array'in elemanlarını ekle
    for (int i = 0; i < size; i++) {
        result.append(arr[i]);
    }
    
    // İkinci array'in elemanlarını ekle (tekrar etmeyenleri)
    for (int i = 0; i < other.size; i++) {
        if (result.linearSearch(other.arr[i]) == -1) {
            result.append(other.arr[i]);
        }
    }
    
    return result;
}
// Time Complexity: O(n*m) where n,m are array sizes
```

2. **Intersection (Kesişim):**
```cpp
Array<T> getIntersection(const Array& other) const {
    Array<T> result(std::min(capacity, other.capacity));
    
    for (int i = 0; i < size; i++) {
        if (other.linearSearch(arr[i]) != -1) {
            result.append(arr[i]);
        }
    }
    
    return result;
}
// Time Complexity: O(n*m)
```

3. **Difference (Fark):**
```cpp
Array<T> getDifference(const Array& other) const {
    Array<T> result(capacity);
    
    for (int i = 0; i < size; i++) {
        if (other.linearSearch(arr[i]) == -1) {
            result.append(arr[i]);
        }
    }
    
    return result;
}
// Time Complexity: O(n*m)
```
Daha verimli implementasyon için hash table kullanılabilir (O(n+m)).

## S9 ⭐
**Soru**: Bir array'de en çok tekrar eden elemanı nasıl bulursunuz?
1. Hash Map yaklaşımı (O(n)):
```cpp
int findMostFrequent(int arr[], int n) {
    unordered_map<int, int> freq;
    int maxFreq = 0, result = arr[0];
    
    for(int i = 0; i < n; i++) {
        freq[arr[i]]++;
        if(freq[arr[i]] > maxFreq) {
            maxFreq = freq[arr[i]];
            result = arr[i];
        }
    }
    return result;
}
```

## S10 ⭐
**Soru**: Bir array'i sıralamadan ikinci en büyük elemanı nasıl bulursunuz?
```cpp
int findSecondLargest(int arr[], int n) {
    if(n < 2) return -1;
    
    int largest = arr[0];
    int secondLargest = INT_MIN;
    
    for(int i = 1; i < n; i++) {
        if(arr[i] > largest) {
            secondLargest = largest;
            largest = arr[i];
        }
        else if(arr[i] < largest && arr[i] > secondLargest) {
            secondLargest = arr[i];
        }
    }
    return secondLargest;
}
```

## S11 ⭐⭐
**Soru**: Bir array'de ardışık elemanların en büyük toplamını nasıl bulursunuz? (Kadane's Algorithm)
```cpp
int maxSubArraySum(int arr[], int n) {
    int maxSoFar = arr[0];
    int currMax = arr[0];
    
    for(int i = 1; i < n; i++) {
        currMax = max(arr[i], currMax + arr[i]);
        maxSoFar = max(maxSoFar, currMax);
    }
    return maxSoFar;
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Dinamik programlama yaklaşımı kullanır
- Negatif sayıları da ele alabilir

## S12 ⭐⭐
**Soru**: Array'de sıfırları sona taşıma problemi nasıl çözülür? (Move Zeroes)
1. İki pointer yaklaşımı (O(n)):
```cpp
void moveZeroes(int arr[], int n) {
    int nonZero = 0;  // non-zero elemanların yazılacağı index
    
    // Sıfır olmayan elemanları başa taşı
    for(int i = 0; i < n; i++) {
        if(arr[i] != 0) {
            swap(arr[nonZero++], arr[i]);
        }
    }
}
```
2. Counting yaklaşımı (O(n)):
```cpp
void moveZeroes(int arr[], int n) {
    int count = 0;  // sıfır sayısı
    
    // Sıfır olmayanları başa yaz
    for(int i = 0; i < n; i++) {
        if(arr[i] != 0) {
            arr[count++] = arr[i];
        }
    }
    
    // Kalan yerleri sıfırla doldur
    while(count < n) {
        arr[count++] = 0;
    }
}
```

## S13 ⭐⭐
**Soru**: Sorted array'de target sayısının ilk ve son pozisyonunu nasıl bulursunuz?
1. Binary Search yaklaşımı (O(log n)):
```cpp
pair<int,int> findFirstAndLast(int arr[], int n, int target) {
    pair<int,int> result = {-1, -1};
    
    // İlk pozisyonu bul
    int left = 0, right = n-1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) {
            result.first = mid;
            right = mid - 1;  // Sol tarafta ara
        }
        else if(arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    // Son pozisyonu bul
    left = 0, right = n-1;
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] == target) {
            result.second = mid;
            left = mid + 1;  // Sağ tarafta ara
        }
        else if(arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    return result;
}
```
- Time Complexity: O(log n)
- Space Complexity: O(1)
- İki binary search kullanır
- Sıralı array'de çalışır

## S14 ⭐
**Soru**: Array'de tek sayıda tekrar eden elemanı nasıl bulursunuz? (Diğer tüm elemanlar çift sayıda tekrar ediyor)
```cpp
int findSingleNumber(int arr[], int n) {
    int result = 0;
    for(int i = 0; i < n; i++) {
        result ^= arr[i];  // XOR operatörü
    }
    return result;
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- XOR özelliklerini kullanır: a^a = 0 ve a^0 = a

## S15 ⭐
**Soru**: Array'i yerinde (in-place) olarak artan ve azalan şekilde sıralayın (Peak Array)
```cpp
void createPeakArray(int arr[], int n) {
    sort(arr, arr + n);  // Önce sırala
    
    // İkili gruplar halinde swap yap
    for(int i = 1; i < n-1; i += 2) {
        swap(arr[i], arr[i+1]);
    }
}
```
- Time Complexity: O(n log n)
- Space Complexity: O(1)
- Sonuç: arr[0] < arr[1] > arr[2] < arr[3] > arr[4] ...

## S16 ⭐⭐
**Soru**: Array'de verilen hedef sayıya en yakın üç sayının toplamını bulun
```cpp
int threeSumClosest(int arr[], int n, int target) {
    sort(arr, arr + n);
    int closestSum = arr[0] + arr[1] + arr[2];
    
    for(int i = 0; i < n-2; i++) {
        int left = i + 1, right = n - 1;
        
        while(left < right) {
            int currentSum = arr[i] + arr[left] + arr[right];
            
            if(currentSum == target) return currentSum;
            
            if(abs(currentSum - target) < abs(closestSum - target)) {
                closestSum = currentSum;
            }
            
            if(currentSum < target) left++;
            else right--;
        }
    }
    return closestSum;
}
```
- Time Complexity: O(n²)
- Space Complexity: O(1)
- Two pointer tekniği kullanır

## S17 ⭐⭐
**Soru**: Array'de majority element'i bulun (n/2'den fazla tekrar eden eleman)
1. Boyer-Moore Voting Algorithm (O(n)):
```cpp
int findMajorityElement(int arr[], int n) {
    int candidate = arr[0];
    int count = 1;
    
    // Aday seçimi
    for(int i = 1; i < n; i++) {
        if(count == 0) {
            candidate = arr[i];
            count = 1;
        }
        else if(arr[i] == candidate) {
            count++;
        }
        else {
            count--;
        }
    }
    
    // Doğrulama
    count = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] == candidate) count++;
    }
    
    return count > n/2 ? candidate : -1;
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- İki geçişli algoritma

## S18 ⭐⭐
**Soru**: Array'de kayıp pozitif sayıyı bulun (en küçük pozitif sayı)
```cpp
int findFirstMissingPositive(int arr[], int n) {
    // 1: Negatif ve n'den büyük sayıları 1 ile değiştir
    for(int i = 0; i < n; i++) {
        if(arr[i] <= 0 || arr[i] > n) {
            arr[i] = 1;
        }
    }
    
    // 2: İndex'leri işaretle
    for(int i = 0; i < n; i++) {
        int index = abs(arr[i]) - 1;
        if(index < n && arr[index] > 0) {
            arr[index] = -arr[index];
        }
    }
    
    // 3: İlk pozitif sayıyı bul
    for(int i = 0; i < n; i++) {
        if(arr[i] > 0) return i + 1;
    }
    
    return n + 1;
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Array'i hash table olarak kullanır

## S19 ⭐⭐
**Soru**: Array'de en uzun ardışık sayı dizisinin uzunluğunu bulun
```cpp
int longestConsecutive(int arr[], int n) {
    unordered_set<int> numSet;
    for(int i = 0; i < n; i++) {
        numSet.insert(arr[i]);
    }
    
    int longestStreak = 0;
    
    for(int num : numSet) {
        if(!numSet.count(num-1)) {  // Dizinin başlangıcı
            int currentNum = num;
            int currentStreak = 1;
            
            while(numSet.count(currentNum+1)) {
                currentNum++;
                currentStreak++;
            }
            
            longestStreak = max(longestStreak, currentStreak);
        }
    }
    
    return longestStreak;
}
```
- Time Complexity: O(n)
- Space Complexity: O(n)
- Hash set kullanarak optimizasyon

## S20 ⭐⭐
**Soru**: Array'de equilibrium index'i bulun (sol tarafın toplamı sağ tarafa eşit olan index)
```cpp
int findEquilibriumIndex(int arr[], int n) {
    int totalSum = 0;
    for(int i = 0; i < n; i++) {
        totalSum += arr[i];
    }
    
    int leftSum = 0;
    for(int i = 0; i < n; i++) {
        int rightSum = totalSum - leftSum - arr[i];
        
        if(leftSum == rightSum) {
            return i;
        }
        
        leftSum += arr[i];
    }
    
    return -1;
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Prefix sum tekniği kullanır

## S21 ⭐
**Soru**: Array'de kaç tane çift ve tek sayı olduğunu bulun
```cpp
pair<int,int> countEvenOdd(int arr[], int n) {
    int evenCount = 0, oddCount = 0;
    
    for(int i = 0; i < n; i++) {
        if(arr[i] % 2 == 0) evenCount++;
        else oddCount++;
    }
    
    return {evenCount, oddCount};
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Basit modulo operasyonu kullanır

## S22 ⭐
**Soru**: Array'de verilen bir sayının kaç kez tekrar ettiğini bulun
```cpp
int findFrequency(int arr[], int n, int x) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] == x) count++;
    }
    return count;
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Sıralı array'de binary search ile O(log n)'de bulunabilir

## S23 ⭐⭐
**Soru**: Array'de en küçük ve en büyük elemanı tek geçişte bulun
```cpp
pair<int,int> findMinMax(int arr[], int n) {
    if(n == 0) return {0, 0};
    
    int minVal = arr[0], maxVal = arr[0];
    
    // Çift sayıda eleman varsa ikili karşılaştır
    for(int i = 1; i < n-1; i += 2) {
        int smaller, larger;
        if(arr[i] < arr[i+1]) {
            smaller = arr[i];
            larger = arr[i+1];
        } else {
            smaller = arr[i+1];
            larger = arr[i];
        }
        
        minVal = min(minVal, smaller);
        maxVal = max(maxVal, larger);
    }
    
    // Tek sayıda eleman varsa son elemanı kontrol et
    if(n % 2) {
        minVal = min(minVal, arr[n-1]);
        maxVal = max(maxVal, arr[n-1]);
    }
    
    return {minVal, maxVal};
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Karşılaştırma sayısını minimize eder

## S24 ⭐⭐
**Soru**: Array'de verilen sayıdan küçük olan elemanları sola, büyük olanları sağa taşıyın (Dutch National Flag)
```cpp
void partition(int arr[], int n, int pivot) {
    int low = 0, high = n-1;
    
    while(low < high) {
        // Soldaki büyük elemanı bul
        while(low < n && arr[low] <= pivot) low++;
        
        // Sağdaki küçük elemanı bul
        while(high >= 0 && arr[high] > pivot) high--;
        
        // Swap yap
        if(low < high) {
            swap(arr[low], arr[high]);
        }
    }
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Partition algoritması kullanır

## S25 ⭐⭐
**Soru**: Array'de ardışık elemanların farkının en büyük olduğu değeri bulun
```cpp
int maxDifference(int arr[], int n) {
    if(n < 2) return 0;
    
    int maxDiff = arr[1] - arr[0];
    int minElement = arr[0];
    
    for(int i = 1; i < n; i++) {
        maxDiff = max(maxDiff, arr[i] - minElement);
        minElement = min(minElement, arr[i]);
    }
    
    return maxDiff;
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Tek geçişte çözüm

## S26 ⭐⭐
**Soru**: Array'de verilen sayıya en yakın elemanı bulun
```cpp
int findClosest(int arr[], int n, int target) {
    if(n == 0) return -1;
    
    if(n == 1) return arr[0];
    
    // Binary search kullan
    int left = 0, right = n-1;
    while(right - left > 1) {
        int mid = left + (right - left) / 2;
        
        if(arr[mid] == target) return arr[mid];
        
        if(arr[mid] < target) left = mid;
        else right = mid;
    }
    
    // En yakın elemanı bul
    if(abs(arr[left] - target) <= abs(arr[right] - target))
        return arr[left];
    return arr[right];
}
```
- Time Complexity: O(log n)
- Space Complexity: O(1)
- Binary search kullanır

## S27 ⭐⭐
**Soru**: Array'de her elemanın sağındaki ilk büyük elemanı bulun
```cpp
vector<int> nextGreaterElement(int arr[], int n) {
    vector<int> result(n, -1);
    stack<int> st;
    
    // Sağdan sola tara
    for(int i = n-1; i >= 0; i--) {
        // Stack'te daha küçük elemanları çıkar
        while(!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }
        
        // Sonraki büyük elemanı bul
        if(!st.empty()) {
            result[i] = st.top();
        }
        
        st.push(arr[i]);
    }
    
    return result;
}
```
- Time Complexity: O(n)
- Space Complexity: O(n)
- Stack kullanarak tek geçişte çözüm

## S28 ⭐⭐
**Soru**: Array'de her elemanın sol ve sağındaki elemanların toplamı eşit olan indeksi bulun
```cpp
int findSpecialIndex(int arr[], int n) {
    vector<int> prefixSum(n);
    prefixSum[0] = arr[0];
    
    // Prefix sum hesapla
    for(int i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i-1] + arr[i];
    }
    
    // Her indeks için kontrol et
    for(int i = 1; i < n-1; i++) {
        int leftSum = prefixSum[i-1];
        int rightSum = prefixSum[n-1] - prefixSum[i];
        
        if(leftSum == rightSum) return i;
    }
    
    return -1;
}
```
- Time Complexity: O(n)
- Space Complexity: O(n)
- Prefix sum array kullanır

## S29 ⭐⭐
**Soru**: Array'de verilen sayıya en yakın çift sayıyı bulun
```cpp
pair<int,int> findClosestPair(int arr[], int n, int target) {
    sort(arr, arr + n);
    
    int left = 0, right = n-1;
    int minDiff = INT_MAX;
    pair<int,int> result;
    
    while(left < right) {
        int sum = arr[left] + arr[right];
        int diff = abs(sum - target);
        
        if(diff < minDiff) {
            minDiff = diff;
            result = {arr[left], arr[right]};
        }
        
        if(sum < target) left++;
        else right--;
    }
    
    return result;
}
```
- Time Complexity: O(n log n)
- Space Complexity: O(1)
- Two pointer tekniği kullanır

## S31 ⭐⭐
**Soru**: İki sıralı array'i tek bir sıralı array'de birleştirin (Merge Sort'un merge işlemi)
```cpp
void mergeSortedArrays(int arr1[], int n1, int arr2[], int n2, int result[]) {
    int i = 0, j = 0, k = 0;
    
    // İki array'i karşılaştırarak birleştir
    while(i < n1 && j < n2) {
        if(arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    
    // Kalan elemanları ekle
    while(i < n1) {
        result[k++] = arr1[i++];
    }
    
    while(j < n2) {
        result[k++] = arr2[j++];
    }
}
```
- Time Complexity: O(n1 + n2)
- Space Complexity: O(1) (result array hariç)
- Merge Sort algoritmasının temel yapı taşı
- İki pointer tekniği kullanır
- Stable sorting özelliği vardır (eşit elemanların sırası korunur)

Alternatif yaklaşım (in-place merge):
```cpp
void mergeInPlace(int arr1[], int n1, int arr2[], int n2) {
    // Her eleman için
    for(int i = 0; i < n1; i++) {
        // arr1[i] arr2[0]'dan büyükse swap yap
        if(arr1[i] > arr2[0]) {
            swap(arr1[i], arr2[0]);
            
            // arr2'yi sıralı tut
            int first = arr2[0];
            int j;
            for(j = 1; j < n2 && arr2[j] < first; j++) {
                arr2[j-1] = arr2[j];
            }
            arr2[j-1] = first;
        }
    }
}
```
- Time Complexity: O(n1 * n2)
- Space Complexity: O(1)
- Ekstra alan kullanmadan birleştirme
- İlk çözüme göre daha yavaş ama memory-efficient

