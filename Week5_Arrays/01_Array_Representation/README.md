# Array Representation (Dizi Gösterimi)

## İçerik
1. [Array Temelleri](#array-temelleri)
2. [Array Tanımlama Yöntemleri](#array-tanımlama-yöntemleri)
3. [Static vs Dynamic Arrays](#static-vs-dynamic-arrays)
4. [Array Boyutunu Artırma](#array-boyutunu-artırma)
5. [2D Arrays](#2d-arrays)
6. [Compiler'da Array Gösterimi](#compilerda-array-gösterimi)
7. [Row Major ve Column Major Formüller](#row-major-ve-column-major-formüller)
8. [nD Arrays](#nd-arrays)

## Array Temelleri
- Array (Dizi), aynı türden elemanların ardışık bellek konumlarında saklandığı bir veri yapısıdır
- Her eleman bir index ile erişilebilir (0'dan başlar)
- Bellek adresleri ardışıktır
- Random access (doğrudan erişim) desteklenir: O(1)

### Memory'de Array Gösterimi
```
Index:     0   1   2   3   4
Data:     [10][20][30][40][50]
Address:  100 104 108 112 116  (int: 4 byte)
```

## Array Tanımlama Yöntemleri
1. **Stack'te Statik Array**
   ```cpp
   int A[5];                // Uninitialized
   int B[5] = {1,2,3,4,5};  // Initialized
   int C[] = {1,2,3,4,5};   // Size automatically determined
   ```

2. **Heap'te Dinamik Array**
   ```cpp
   int* arr = new int[5];     // C++
   int* arr = (int*)malloc(5 * sizeof(int));  // C style
   ```

## Static vs Dynamic Arrays
### Static Arrays
- Boyut compile-time'da belirlenir
- Stack'te oluşturulur
- Boyut değiştirilemez
- Hızlı erişim
- Scope bitince otomatik temizlenir

### Dynamic Arrays
- Boyut runtime'da belirlenir
- Heap'te oluşturulur
- Boyut değiştirilebilir (reallocation)
- Manuel memory management gerektirir
- `delete[]` veya `free()` ile temizlenmeli

## Array Boyutunu Artırma
1. **Yeni Array Oluşturma Yöntemi**
   ```cpp
   // 1. Yeni ve daha büyük array oluştur
   int* newArr = new int[newSize];
   
   // 2. Eski elemanları kopyala
   for(int i = 0; i < oldSize; i++)
       newArr[i] = oldArr[i];
   
   // 3. Eski array'i temizle
   delete[] oldArr;
   
   // 4. Pointer'ı güncelle
   oldArr = newArr;
   ```

2. **realloc Kullanımı (C-style)**
   ```cpp
   int* arr = (int*)realloc(arr, newSize * sizeof(int));
   ```

## 2D Arrays
### Tanımlama Yöntemleri
1. **Stack'te 2D Array**
   ```cpp
   int A[3][4];  // 3 row, 4 column
   ```

2. **Heap'te 2D Array**
   ```cpp
   // Method 1: Single block
   int* arr = new int[rows * cols];
   
   // Method 2: Array of pointers
   int** arr = new int*[rows];
   for(int i = 0; i < rows; i++)
       arr[i] = new int[cols];
   ```

## Compiler'da Array Gösterimi
### Memory Layout
1. **1D Array**
   ```
   A[i] = Base + i * size
   ```

2. **2D Array (Row Major)**
   ```
   A[i][j] = Base + (i * cols + j) * size
   ```

3. **2D Array (Column Major)**
   ```
   A[i][j] = Base + (j * rows + i) * size
   ```

## Row Major ve Column Major Formüller
### Row Major (C/C++)
- Satır öncelikli depolama
- Formül: `Address = Base + (i * cols + j) * size`
- Örnek:
  ```
  2D Array [3][4]:
  [1  2  3  4]
  [5  6  7  8]
  [9 10 11 12]
  
  Memory: 1,2,3,4,5,6,7,8,9,10,11,12
  ```

### Column Major (Fortran)
- Sütun öncelikli depolama
- Formül: `Address = Base + (j * rows + i) * size`
- Örnek:
  ```
  2D Array [3][4]:
  [1  2  3  4]
  [5  6  7  8]
  [9 10 11 12]
  
  Memory: 1,5,9,2,6,10,3,7,11,4,8,12
  ```

## nD Arrays
### 3D Array Formülleri
1. **Row Major**
   ```
   Address = Base + (i * d2 * d3 + j * d3 + k) * size
   ```
   - i, j, k: indeksler
   - d2, d3: 2. ve 3. boyut uzunlukları
   
2. **Column Major**
   ```
   Address = Base + (k * d1 * d2 + j * d1 + i) * size
   ```
   - d1, d2: 1. ve 2. boyut uzunlukları

### Genel nD Array Formülü
1. **Row Major**
   ```
   Address = Base + (i1*d2*d3*...*dn + i2*d3*...*dn + ... + in-1*dn + in) * size
   ```

2. **Column Major**
   ```
   Address = Base + (in*d1*d2*...*dn-1 + in-1*d1*...*dn-2 + ... + i2*d1 + i1) * size
   ```

## Best Practices
1. Array boyutunu kontrol edin
2. Boundary check yapın
3. Memory leak'leri önleyin
4. Mümkünse smart pointers kullanın
5. Multi-dimensional array'lerde doğru formülü kullanın

## Common Pitfalls
1. Array bounds aşımı
2. Memory leak
3. Dangling pointers
4. Wrong dimension calculations
5. Row/Column major karışıklığı 