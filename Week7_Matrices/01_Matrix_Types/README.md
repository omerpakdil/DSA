# Matrix Türleri ve İşlemleri

Bu modül, matematiksel ve hesaplamalı uygulamalarda yaygın olarak kullanılan çeşitli matrix türlerini uygular. Her matrix türü, kendine özgü özelliklerine göre depolama ve işlemler için optimize edilmiştir.

## İçindekiler
1. [Matrix Türleri](#matrix-türleri)
2. [Uygulama Detayları](#uygulama-detayları)
3. [Zaman Karmaşıklıkları](#zaman-karmaşıklıkları)
4. [Kullanım Örnekleri](#kullanım-örnekleri)
5. [Derleme ve Test](#derleme-ve-test)

## Matrix Türleri

### 1. Diagonal Matrix
- Sadece köşegen elemanlar sıfırdan farklı olabilir
- Storage: n×n matrix için O(n)
- Örnek:
```
1 0 0
0 2 0
0 0 3
```

### 2. Lower Triangular Matrix
- Ana köşegenin üstündeki elemanlar sıfırdır
- Storage: n×n matrix için O(n(n+1)/2)
- Örnek:
```
1 0 0
2 3 0
4 5 6
```

### 3. Upper Triangular Matrix
- Ana köşegenin altındaki elemanlar sıfırdır
- Storage: n×n matrix için O(n(n+1)/2)
- Örnek:
```
1 2 3
0 4 5
0 0 6
```

### 4. Symmetric Matrix
- Matrix transpozuna eşittir (aij = aji)
- Storage: n×n matrix için O(n(n+1)/2)
- Örnek:
```
1 2 3
2 4 5
3 5 6
```

### 5. Tridiagonal Matrix
- Ana köşegen ve onun üstündeki ve altındaki köşegenlerde sıfırdan farklı elemanlar
- Storage: n×n matrix için O(3n-2)
- Örnek:
```
1 5 0 0
8 2 6 0
0 9 3 7
0 0 10 4
```

### 6. Toeplitz Matrix
- Her köşegen boyunca sabit elemanlar
- Storage: n×n matrix için O(2n-1)
- Örnek:
```
1 2 3
4 1 2
5 4 1
```

## Uygulama Detayları

Tüm matrix türleri, temel bir Matrix class'ından inheritance alan template class'lar olarak uygulanmıştır. Temel özellikler:
- Farklı data type'lar için template desteği
- Boundary checking ve error handling
- Matrix özelliklerine göre memory-efficient storage
- Tüm türler için consistent ve clean interface

## Zaman Karmaşıklıkları

| Operation | Complexity | Not |
|-----------|------------|-----|
| Constructor | O(1) | Sadece memory allocation |
| get(i,j) | O(1) | Index hesaplaması ile constant time access |
| set(i,j) | O(1) | Matrix property validation içerir |
| Display | O(n²) | Tüm elementleri yazdırır |

## Kullanım Örnekleri

```cpp
// 3x3 diagonal matrix oluşturma
DiagonalMatrix<int> dm(3);
dm.set(0, 0, 1);
dm.set(1, 1, 2);
dm.set(2, 2, 3);

// 3x3 symmetric matrix oluşturma
SymmetricMatrix<double> sm(3);
sm.set(0, 0, 1.0);
sm.set(0, 1, 2.0);  // Otomatik olarak (1,0)'a da 2.0 atar
sm.set(1, 1, 4.0);
```

## Derleme ve Test

```bash
# Build directory oluştur
mkdir build && cd build

# CMake configuration
cmake ..

# Build
make

# Test execution
./matrix_test
```

Test programı tüm matrix türleri için comprehensive testler içerir ve şunları verify eder:
- Doğru element storage ve access
- Matrix property enforcement
- Error handling
- Display functionality 