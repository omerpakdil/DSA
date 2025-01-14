# Sparse Matrix ve Polynomial Mülakat Soruları

## Temel Sorular

### S1 ⭐: Sparse matrix nedir ve ne zaman kullanılmalıdır?
Sparse matrix, çoğu elementi sıfır olan matristir. Şu durumlarda kullanılmalıdır:
- Matrisin %70'inden fazlası sıfır ise
- Bellek kullanımı kritik ise
- Sıfır olmayan elementler üzerinde işlem yapılacaksa

Örnek kullanım alanları:
- Büyük sosyal ağ grafları
- Bilimsel hesaplamalar
- 3D grafik transformasyonları

### S2 ⭐: Sparse matrix'leri saklamak için hangi formatlar kullanılır?
Üç temel format vardır:
1. **Coordinate List (COO)**:
```cpp
struct Element {
    int row, col, value;
};
vector<Element> elements;  // Sadece sıfır olmayan elementler
```

2. **Compressed Sparse Row (CSR)**:
```cpp
vector<double> values;     // Sıfır olmayan değerler
vector<int> columns;       // Her değerin column index'i
vector<int> row_ptr;      // Her row'un başlangıç pozisyonu
```

3. **Compressed Sparse Column (CSC)**:
```cpp
vector<double> values;     // Sıfır olmayan değerler
vector<int> rows;         // Her değerin row index'i
vector<int> col_ptr;      // Her column'un başlangıç pozisyonu
```

### S3 ⭐: Bir polinomu bilgisayarda nasıl temsil edersiniz?
İki yaygın yaklaşım vardır:

1. **Array-based representation**:
```cpp
// Tüm katsayıları sakla (sıfırlar dahil)
vector<int> coefficients = {1, 2, 3};  // x² + 2x + 3
```

2. **Map-based representation** (Sparse):
```cpp
// Sadece sıfır olmayan katsayıları sakla
map<int, int> coefficients = {{2,1}, {1,2}, {0,3}};  // x² + 2x + 3
```

### S4 ⭐⭐: Sparse matrix çarpımını nasıl optimize edersiniz?
```cpp
SparseMatrix multiply(const SparseMatrix& A, const SparseMatrix& B) {
    SparseMatrix result(A.rows, B.cols);
    
    // Her sıfır olmayan A[i][k] için
    for(const auto& elemA : A.elements) {
        // Her sıfır olmayan B[k][j] için
        for(const auto& elemB : B.elements) {
            if(elemA.col == elemB.row) {
                // Sadece gerekli çarpımları yap
                result.addElement(elemA.row, elemB.col, 
                                elemA.value * elemB.value);
            }
        }
    }
    return result;
}
```

### S5 ⭐⭐: İki polinomun çarpımını efficient bir şekilde nasıl hesaplarsınız?
```cpp
Polynomial multiply(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result;
    
    // Sadece sıfır olmayan terimler için çarpım yap
    for(const auto& [exp1, coef1] : p1.terms) {
        for(const auto& [exp2, coef2] : p2.terms) {
            int newExp = exp1 + exp2;
            int newCoef = coef1 * coef2;
            result.addTerm(newExp, newCoef);
        }
    }
    return result;
}
```

## İleri Seviye Sorular

### S6 ⭐⭐: Sparse matrix'lerde memory usage nasıl hesaplanır?
Örnek analiz:
1. **Dense Matrix**: n × m × sizeof(T) bytes
2. **COO Format**: 3 × nnz × sizeof(T) bytes
   - nnz: sıfır olmayan element sayısı
   - Her element için (row, col, value) saklanır

```cpp
size_t getDenseSize(int rows, int cols) {
    return rows * cols * sizeof(double);
}

size_t getSparseSize(int nnz) {
    return nnz * (2 * sizeof(int) + sizeof(double));
}
```

### S7 ⭐⭐⭐: Sparse matrix'lerde hızlı element erişimi nasıl sağlanır?
Binary search tree kullanarak:

```cpp
class SparseMatrix {
    map<pair<int,int>, double> elements;
    
public:
    double get(int i, int j) {
        auto it = elements.find({i,j});
        return (it != elements.end()) ? it->second : 0.0;
    }
    
    void set(int i, int j, double value) {
        if(value != 0.0)
            elements[{i,j}] = value;
        else
            elements.erase({i,j});
    }
};
```

### S8 ⭐⭐⭐: Büyük sparse matrix'lerde paralel işlem nasıl yapılır?
1. **Data Partitioning**:
```cpp
void parallelMultiply(const SparseMatrix& A, const SparseMatrix& B) {
    vector<thread> threads;
    int numThreads = thread::hardware_concurrency();
    
    // Matrix'i row'lara böl
    for(int t = 0; t < numThreads; t++) {
        threads.emplace_back([&, t]() {
            int startRow = t * (A.rows / numThreads);
            int endRow = (t + 1) * (A.rows / numThreads);
            multiplyRows(A, B, startRow, endRow);
        });
    }
    
    for(auto& thread : threads) thread.join();
}
```

### S9 ⭐⭐⭐: Polynomial interpolation nasıl implemente edilir?
Lagrange interpolation örneği:
```cpp
Polynomial interpolate(const vector<Point>& points) {
    Polynomial result;
    
    for(size_t i = 0; i < points.size(); i++) {
        Polynomial term({points[i].y});  // Başlangıç değeri
        
        for(size_t j = 0; j < points.size(); j++) {
            if(i != j) {
                // Li(x) = Π (x - xj)/(xi - xj)
                double denom = points[i].x - points[j].x;
                Polynomial factor({-points[j].x/denom, 1.0/denom});
                term = term * factor;
            }
        }
        result = result + term;
    }
    return result;
}
```

### S10 ⭐⭐⭐: Sparse matrix'lerde eigenvalue ve eigenvector hesaplama
Power method implementasyonu:
```cpp
pair<double, vector<double>> powerMethod(const SparseMatrix& A, 
                                       int maxIter = 1000,
                                       double tol = 1e-10) {
    int n = A.getRows();
    vector<double> v(n, 1.0);  // Initial guess
    double eigenvalue = 0.0;
    
    for(int iter = 0; iter < maxIter; iter++) {
        // v = Av
        vector<double> Av = A.multiply(v);
        
        // Normalize
        double norm = 0.0;
        for(double x : Av) norm += x * x;
        norm = sqrt(norm);
        
        // Update eigenvalue estimate
        eigenvalue = norm;
        
        // Update eigenvector
        for(double& x : Av) x /= norm;
        
        // Check convergence
        double diff = 0.0;
        for(int i = 0; i < n; i++) {
            diff += abs(v[i] - Av[i]);
        }
        if(diff < tol) break;
        
        v = Av;
    }
    
    return {eigenvalue, v};
}
```

### S11 ⭐: Sparse matrix'te bir row'un tüm elementlerini nasıl sıfırlarsınız?
```cpp
void clearRow(SparseMatrix& matrix, int row) {
    auto it = matrix.elements.begin();
    while(it != matrix.elements.end()) {
        if(it->row == row)
            it = matrix.elements.erase(it);
        else
            ++it;
    }
}

// Alternatif implementasyon (map-based)
void clearRow(SparseMatrix& matrix, int row) {
    for(int j = 0; j < matrix.getCols(); j++) {
        matrix.set(row, j, 0);
    }
}
```
Time Complexity: O(k) veya O(n), implementasyona bağlı
Space Complexity: O(1)

### S12 ⭐: Sparse matrix'i nasıl transpose edersiniz?
```cpp
SparseMatrix transpose(const SparseMatrix& matrix) {
    SparseMatrix result(matrix.getCols(), matrix.getRows());
    
    for(const auto& elem : matrix.elements) {
        result.addElement(elem.col, elem.row, elem.value);
    }
    return result;
}
```
Time Complexity: O(k), k = sıfır olmayan element sayısı
Space Complexity: O(k)

### S13 ⭐: Bir polinomun belirli bir x değeri için değerini nasıl hesaplarsınız? (Horner's method)
```cpp
template<typename T>
T evaluatePolynomial(const Polynomial<T>& poly, T x) {
    T result = 0;
    for(auto it = poly.coefficients.rbegin(); 
        it != poly.coefficients.rend(); ++it) {
        result = result * x + it->second;
    }
    return result;
}
```
Time Complexity: O(n), n = polinom derecesi
Space Complexity: O(1)

### S14 ⭐⭐: İki sparse matrix'in toplamını nasıl hesaplarsınız?
```cpp
SparseMatrix add(const SparseMatrix& A, const SparseMatrix& B) {
    if(A.rows != B.rows || A.cols != B.cols)
        throw std::invalid_argument("Matrix boyutları uyumsuz");
        
    SparseMatrix result(A.rows, A.cols);
    
    // A'nın elementlerini ekle
    for(const auto& elem : A.elements) {
        result.addElement(elem.row, elem.col, elem.value);
    }
    
    // B'nin elementlerini ekle/güncelle
    for(const auto& elem : B.elements) {
        T currentValue = result.get(elem.row, elem.col);
        result.set(elem.row, elem.col, currentValue + elem.value);
    }
    
    return result;
}
```
Time Complexity: O(k1 + k2), k1 ve k2 = input matrix'lerdeki sıfır olmayan element sayıları
Space Complexity: O(k1 + k2)

### S15 ⭐⭐: Bir polinomun türevini nasıl hesaplarsınız?
```cpp
template<typename T>
Polynomial<T> derivative(const Polynomial<T>& poly) {
    Polynomial<T> result;
    
    for(const auto& [power, coeff] : poly.coefficients) {
        if(power > 0) {  // x⁰'ın türevi 0
            result.addTerm(power - 1, coeff * power);
        }
    }
    return result;
}
```
Time Complexity: O(n), n = terim sayısı
Space Complexity: O(n)

### S16 ⭐⭐: Sparse matrix'te belirli bir değeri nasıl ararsınız?
```cpp
vector<pair<int,int>> findValue(const SparseMatrix& matrix, const T& value) {
    vector<pair<int,int>> positions;
    
    if(value == T()) {  // Sıfır değeri aranıyorsa
        // Sıfır olmayan elementlerin complement'ini bul
        set<pair<int,int>> nonZeros;
        for(const auto& elem : matrix.elements) {
            nonZeros.insert({elem.row, elem.col});
        }
        
        for(int i = 0; i < matrix.rows; i++) {
            for(int j = 0; j < matrix.cols; j++) {
                if(nonZeros.find({i,j}) == nonZeros.end()) {
                    positions.push_back({i,j});
                }
            }
        }
    } else {  // Sıfır olmayan değer aranıyorsa
        for(const auto& elem : matrix.elements) {
            if(elem.value == value) {
                positions.push_back({elem.row, elem.col});
            }
        }
    }
    return positions;
}
```

### S17 ⭐⭐: Bir polinomun köklerini nasıl bulursunuz? (Newton's method)
```cpp
double findRoot(const Polynomial<double>& poly, 
               double x0,           // Initial guess
               double tol = 1e-10,  // Tolerance
               int maxIter = 100) { // Maximum iterations
    Polynomial<double> deriv = derivative(poly);
    double x = x0;
    
    for(int i = 0; i < maxIter; i++) {
        double fx = evaluatePolynomial(poly, x);
        double dfx = evaluatePolynomial(deriv, x);
        
        if(abs(dfx) < tol)  // Avoid division by zero
            throw std::runtime_error("Derivative too close to zero");
            
        double dx = fx / dfx;
        x = x - dx;
        
        if(abs(dx) < tol)
            return x;
    }
    throw std::runtime_error("Maximum iterations reached");
}
```

### S18 ⭐⭐: Sparse matrix'te bir row veya column'un toplamını nasıl hesaplarsınız?
```cpp
T getRowSum(const SparseMatrix& matrix, int row) {
    T sum = T();
    for(const auto& elem : matrix.elements) {
        if(elem.row == row) {
            sum += elem.value;
        }
    }
    return sum;
}

T getColSum(const SparseMatrix& matrix, int col) {
    T sum = T();
    for(const auto& elem : matrix.elements) {
        if(elem.col == col) {
            sum += elem.value;
        }
    }
    return sum;
}
```
Time Complexity: O(k), k = sıfır olmayan element sayısı
Space Complexity: O(1)

### S19 ⭐: İki polinomun eşit olup olmadığını nasıl kontrol edersiniz?
```cpp
template<typename T>
bool areEqual(const Polynomial<T>& p1, const Polynomial<T>& p2) {
    if(p1.getDegree() != p2.getDegree())
        return false;
        
    // Tüm katsayıları karşılaştır
    for(size_t i = 0; i <= p1.getDegree(); i++) {
        if(p1.getCoefficient(i) != p2.getCoefficient(i))
            return false;
    }
    return true;
}
```
Time Complexity: O(n), n = max(derece1, derece2)
Space Complexity: O(1)

### S20 ⭐: Sparse matrix'in sıfır olmayan element yüzdesini nasıl hesaplarsınız?
```cpp
double getNonZeroPercentage(const SparseMatrix& matrix) {
    size_t totalElements = matrix.getRows() * matrix.getCols();
    size_t nonZeroElements = matrix.getNonZeroCount();
    
    return (nonZeroElements * 100.0) / totalElements;
}

bool isSparseMatrix(const SparseMatrix& matrix, double threshold = 70.0) {
    return (100.0 - getNonZeroPercentage(matrix)) >= threshold;
}
```
Time Complexity: O(1)
Space Complexity: O(1) 