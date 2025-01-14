# Sparse Matrix ve Polynomial Representation

Bu modül, seyrek (sparse) matrislerin ve polinomların verimli temsilini ve işlenmesini sağlayan implementasyonları içerir.

## İçindekiler
1. [Sparse Matrix](#sparse-matrix)
2. [Polynomial Representation](#polynomial-representation)
3. [Implementasyon Detayları](#implementasyon-detayları)
4. [Kullanım Örnekleri](#kullanım-örnekleri)
5. [Performans Analizi](#performans-analizi)

## Sparse Matrix

Sparse matrix, çoğu elementi sıfır olan matrisler için özel bir veri yapısıdır. Bu implementasyon:

- Coordinate List (COO) formatını kullanır
- Sadece sıfır olmayan elementleri saklar
- O(1) element ekleme
- O(k) element arama (k: sıfır olmayan element sayısı)

Örnek:
```
Dense Format:    Sparse Format:
1 0 0 2         (0,0,1)
0 0 0 0         (0,3,2)
0 3 0 0         (2,1,3)
0 0 0 4         (3,3,4)
```

## Polynomial Representation

Polinomlar sparse vector olarak temsil edilir:

- Map kullanarak {üs: katsayı} şeklinde storage
- Sıfır katsayılı terimler saklanmaz
- Toplama ve çarpma operasyonları desteklenir

Örnek:
```
3x² + 2x + 1  ->  {2:3, 1:2, 0:1}
2x² + x       ->  {2:2, 1:1}
```

## Implementasyon Detayları

### Sparse Matrix
- Template class ile generic type desteği
- Exception handling ile güvenli operasyonlar
- Memory-efficient storage
- Display fonksiyonu ile kolay görüntüleme

### Polynomial
- Map-based storage ile efficient operasyonlar
- Operator overloading ile doğal syntax
- Toplama: O(n+m) complexity
- Çarpma: O(nm) complexity

## Kullanım Örnekleri

```cpp
// Sparse Matrix örneği
SparseMatrix<int> matrix(4, 4);
matrix.addElement(0, 0, 1);
matrix.addElement(0, 3, 2);
matrix.display();

// Polynomial örneği
Polynomial<int> p1;
p1.addTerm(2, 3);  // 3x²
p1.addTerm(1, 2);  // 2x
p1.addTerm(0, 1);  // 1
p1.display();
```

## Performans Analizi

### Sparse Matrix
| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Add Element | O(1) | O(1) |
| Get Element | O(k) | O(1) |
| Display | O(n×m) | O(k) |

### Polynomial
| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Add Term | O(log n) | O(1) |
| Get Coefficient | O(log n) | O(1) |
| Addition | O(n+m) | O(n+m) |
| Multiplication | O(nm) | O(n+m) |

Burada:
- n, m: Polinomlardaki terim sayıları
- k: Sparse matrix'teki sıfır olmayan element sayısı 