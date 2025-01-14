# Matrix İşlemleri Mülakat Soruları

## Temel Matrix Kavramları

### S1 ⭐: Sparse matrix nedir ve nasıl verimli bir şekilde depolanır?
Sparse matrix, çoğu elementi sıfır olan bir matrix'tir. Verimli storage için:
1. Coordinate List (COO): Sıfır olmayan elementler için (row, column, value) tuple'ları
2. Compressed Sparse Row (CSR): Non-zero value'lar, column index'leri ve row pointer'ları
3. Compressed Sparse Column (CSC): CSR'ye benzer ancak column-oriented

Örnek implementation:
```cpp
struct SparseElement {
    int row, col;
    double value;
};

class SparseMatrix {
    vector<SparseElement> elements;
    int rows, cols;
};
```

### S2 ⭐: Row-major ve column-major storage arasındaki farkı açıklayın.
Row-major: Aynı row'daki elementler contiguous olarak depolanır
- Index hesaplama: `index = i * cols + j`
- C/C++'da common

Column-major: Aynı column'daki elementler contiguous olarak depolanır
- Index hesaplama: `index = i + j * rows`
- Fortran, MATLAB'da common

### S3 ⭐⭐: Dense ve sparse storage'ı destekleyen bir matrix class'ını nasıl implemente edersiniz?
```cpp
template<typename T>
class Matrix {
protected:
    virtual T get(int i, int j) const = 0;
    virtual void set(int i, int j, const T& value) = 0;
};

class DenseMatrix : public Matrix<T> {
    vector<T> data;  // Continuous storage
};

class SparseMatrix : public Matrix<T> {
    map<pair<int,int>, T> data;  // Sadece non-zero elementler
};
```

### S4 ⭐⭐: Bir matrix'i in-place nasıl transpose edersiniz?
Square matrix için:
```cpp
void transposeInPlace(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}
```
Time complexity: O(n²)
Space complexity: O(1)

### S5 ⭐⭐: Matrix multiplication'ı nasıl efficient bir şekilde implemente edersiniz?
Basic implementation:
```cpp
Matrix multiply(const Matrix& A, const Matrix& B) {
    if(A.cols != B.rows) 
        throw invalid_argument("Invalid dimensions");
    
    Matrix C(A.rows, B.cols);
    for(int i = 0; i < A.rows; i++) {
        for(int j = 0; j < B.cols; j++) {
            for(int k = 0; k < A.cols; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
```
Optimizasyonlar:
1. Cache blocking (tiling)
2. SIMD instructions
3. Parallel processing
4. Strassen's algorithm (büyük matrix'ler için)

## İleri Matrix İşlemleri

### S6 ⭐⭐⭐: Operator overloading destekleyen bir matrix class'ını nasıl implemente edersiniz?
```cpp
template<typename T>
class Matrix {
public:
    // Addition operator
    Matrix operator+(const Matrix& other) const {
        if(rows != other.rows || cols != other.cols)
            throw invalid_argument("Incompatible dimensions");
        
        Matrix result(rows, cols);
        for(int i = 0; i < rows * cols; i++)
            result.data[i] = data[i] + other.data[i];
        return result;
    }
    
    // Scalar multiplication
    Matrix operator*(const T& scalar) const {
        Matrix result(rows, cols);
        for(int i = 0; i < rows * cols; i++)
            result.data[i] = data[i] * scalar;
        return result;
    }
    
    // Matrix multiplication
    Matrix operator*(const Matrix& other) const;
};
```

### S7 ⭐⭐⭐: Matrix determinant'ını efficient bir şekilde nasıl hesaplarsınız?
Yöntemler:
1. 2x2 matrix için: ad - bc
2. 3x3 matrix için: Sarrus' rule
3. Büyük matrix'ler için:
   - LU decomposition (O(n³))
   - Gaussian elimination with partial pivoting
```cpp
double determinant(const Matrix& A) {
    if(A.rows != A.cols) 
        throw invalid_argument("Matrix must be square");
    
    if(A.rows == 2) {
        return A[0][0] * A[1][1] - A[0][1] * A[1][0];
    }
    
    // Büyük matrix'ler için LU decomposition kullan
    Matrix L, U;
    luDecomposition(A, L, U);
    
    double det = 1.0;
    for(int i = 0; i < A.rows; i++)
        det *= U[i][i];
    return det;
}
```

### S8 ⭐⭐⭐: Matrix inverse'ünü nasıl implemente edersiniz?
Yöntemler:
1. Gauss-Jordan elimination
2. LU decomposition
3. Adjoint method
```cpp
Matrix inverse(const Matrix& A) {
    if(A.rows != A.cols)
        throw invalid_argument("Matrix must be square");
    
    int n = A.rows;
    Matrix augmented(n, 2*n);
    
    // Augmented matrix oluştur [A|I]
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            augmented[i][j] = A[i][j];
            augmented[i][j+n] = (i == j) ? 1 : 0;
        }
    }
    
    // Gauss-Jordan elimination uygula
    // Augmented matrix'in sağ yarısını return et
}
```

### S9 ⭐⭐⭐: Linear equation system'lerini efficient bir şekilde nasıl çözersiniz?
Yöntemler:
1. Gaussian elimination
2. LU decomposition
3. Iterative methods (Jacobi, Gauss-Seidel)
```cpp
vector<double> solveSystem(const Matrix& A, const vector<double>& b) {
    // Ax = b
    Matrix L, U;
    vector<double> y, x;
    
    // 1. LU decomposition: A = LU
    luDecomposition(A, L, U);
    
    // 2. Ly = b çöz (forward substitution)
    y = forwardSubstitution(L, b);
    
    // 3. Ux = y çöz (backward substitution)
    x = backwardSubstitution(U, y);
    
    return x;
}
```

### S10 ⭐⭐⭐: Eigenvalue computation'ı nasıl implemente edersiniz?
Yöntemler:
1. Power method (dominant eigenvalue için)
2. QR algorithm
3. Jacobi method (symmetric matrix'ler için)
```cpp
double powerMethod(const Matrix& A, vector<double>& eigenvector, 
                  double tolerance = 1e-10, int maxIter = 1000) {
    vector<double> v(A.rows, 1.0);
    double eigenvalue = 0.0;
    
    for(int iter = 0; iter < maxIter; iter++) {
        // 1. Matrix-vector multiplication: w = Av
        vector<double> w = A * v;
        
        // 2. Find largest component
        double max = *max_element(w.begin(), w.end());
        
        // 3. Normalize
        for(double& wi : w) wi /= max;
        
        // 4. Check convergence
        if(convergence(v, w, tolerance)) {
            eigenvalue = max;
            eigenvector = w;
            break;
        }
        
        v = w;
    }
    
    return eigenvalue;
}
```

## Sık Sorulan Matrix Soruları

### S11 ⭐: Matrix'te sıfır olan row ve column'ları nasıl bulursunuz?
```cpp
pair<vector<int>, vector<int>> findZeroRowsAndCols(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<int> zeroRows, zeroCols;
    
    // Row'ları kontrol et
    for(int i = 0; i < rows; i++) {
        bool isZeroRow = true;
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] != 0) {
                isZeroRow = false;
                break;
            }
        }
        if(isZeroRow) zeroRows.push_back(i);
    }
    
    // Column'ları kontrol et
    for(int j = 0; j < cols; j++) {
        bool isZeroCol = true;
        for(int i = 0; i < rows; i++) {
            if(matrix[i][j] != 0) {
                isZeroCol = false;
                break;
            }
        }
        if(isZeroCol) zeroCols.push_back(j);
    }
    
    return {zeroRows, zeroCols};
}
```
Time Complexity: O(rows × cols)
Space Complexity: O(rows + cols)

### S12 ⭐: Matrix'i 90 derece saat yönünde nasıl döndürürsünüz?
```cpp
void rotateMatrix90(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    // Step 1: Transpose matrix
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    // Step 2: Her row'u reverse et
    for(int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}
```
Time Complexity: O(n²)
Space Complexity: O(1)

### S13 ⭐: Matrix'te bir elementi nasıl ararsınız? Matrix sıralı ise nasıl optimize edersiniz?
```cpp
// Sıralı olmayan matrix için linear search
bool findElement(const vector<vector<int>>& matrix, int target) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] == target) return true;
        }
    }
    return false;
}

// Sıralı matrix için binary search (her row sıralı)
bool findElementSorted(const vector<vector<int>>& matrix, int target) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    // Sağ üst köşeden başla
    int i = 0, j = cols - 1;
    
    while(i < rows && j >= 0) {
        if(matrix[i][j] == target) return true;
        if(matrix[i][j] > target) j--;
        else i++;
    }
    return false;
}
```

### S14 ⭐⭐: Matrix'te en büyük kare alt matrix'i nasıl bulursunuz?
```cpp
int maximalSquare(vector<vector<int>>& matrix) {
    if(matrix.empty()) return 0;
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0));
    int maxSize = 0;
    
    for(int i = 1; i <= rows; i++) {
        for(int j = 1; j <= cols; j++) {
            if(matrix[i-1][j-1] == 1) {
                dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                maxSize = max(maxSize, dp[i][j]);
            }
        }
    }
    
    return maxSize * maxSize;  // Kare alanını return et
}
```

### S15 ⭐⭐: Matrix'te bir elementi update ettiğinizde row ve column toplamlarını nasıl efficient tutarsınız?
```cpp
class MatrixWithSums {
    vector<vector<int>> matrix;
    vector<int> rowSums;
    vector<int> colSums;
    
public:
    MatrixWithSums(int rows, int cols) : 
        matrix(rows, vector<int>(cols)),
        rowSums(rows),
        colSums(cols) {}
    
    void update(int i, int j, int newValue) {
        int oldValue = matrix[i][j];
        matrix[i][j] = newValue;
        
        // Update sums
        rowSums[i] += (newValue - oldValue);
        colSums[j] += (newValue - oldValue);
    }
    
    int getRowSum(int row) { return rowSums[row]; }
    int getColSum(int col) { return colSums[col]; }
};
```

### S16 ⭐⭐: Matrix'te spiral order traversal nasıl yaparsınız?
```cpp
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> result;
    if(matrix.empty()) return result;
    
    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;
    
    while(top <= bottom && left <= right) {
        // Sağa git
        for(int j = left; j <= right; j++)
            result.push_back(matrix[top][j]);
        top++;
        
        // Aşağı git
        for(int i = top; i <= bottom; i++)
            result.push_back(matrix[i][right]);
        right--;
        
        if(top <= bottom) {
            // Sola git
            for(int j = right; j >= left; j--)
                result.push_back(matrix[bottom][j]);
            bottom--;
        }
        
        if(left <= right) {
            // Yukarı git
            for(int i = bottom; i >= top; i--)
                result.push_back(matrix[i][left]);
            left++;
        }
    }
    
    return result;
}
```

### S17 ⭐⭐: Matrix'te bir path'in minimum maliyetini nasıl bulursunuz?
```cpp
int minPathSum(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    // İlk row'u doldur
    for(int j = 1; j < cols; j++)
        grid[0][j] += grid[0][j-1];
    
    // İlk column'u doldur
    for(int i = 1; i < rows; i++)
        grid[i][0] += grid[i-1][0];
    
    // Diğer hücreleri doldur
    for(int i = 1; i < rows; i++) {
        for(int j = 1; j < cols; j++) {
            grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
        }
    }
    
    return grid[rows-1][cols-1];
}
```

### S18 ⭐⭐: Matrix multiplication için Strassen algoritmasını açıklayın.
Strassen algoritması, matrix çarpımını O(n³)'ten O(n^2.807)'ye düşürür:

1. Matrix'leri 4 alt matrix'e böl
2. 7 çarpma işlemi yap (klasik methodda 8)
3. Alt matrix'leri birleştir

Avantajları:
- Büyük matrix'ler için daha hızlı
- Teorik olarak daha düşük complexity

Dezavantajları:
- Küçük matrix'ler için overhead
- Numerik stabilite sorunları
- Implementasyonu kompleks

### S19 ⭐⭐: Matrix'te connected component'leri nasıl bulursunuz?
```cpp
void dfs(vector<vector<int>>& matrix, int i, int j, int rows, int cols) {
    if(i < 0 || i >= rows || j < 0 || j >= cols || matrix[i][j] != 1)
        return;
        
    // Visit current cell
    matrix[i][j] = 2;  // Mark as visited
    
    // Visit neighbors
    dfs(matrix, i+1, j, rows, cols);
    dfs(matrix, i-1, j, rows, cols);
    dfs(matrix, i, j+1, rows, cols);
    dfs(matrix, i, j-1, rows, cols);
}

int countComponents(vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int components = 0;
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(matrix[i][j] == 1) {
                dfs(matrix, i, j, rows, cols);
                components++;
            }
        }
    }
    
    return components;
}
```

### S20 ⭐⭐: Matrix'te bir kelimeyi nasıl ararsınız? (Word Search problemi)
```cpp
bool exist(vector<vector<char>>& board, string word) {
    int rows = board.size();
    int cols = board[0].size();
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(dfs(board, i, j, word, 0))
                return true;
        }
    }
    return false;
}

bool dfs(vector<vector<char>>& board, int i, int j, string& word, int pos) {
    if(pos == word.length()) return true;
    
    if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || 
       board[i][j] != word[pos])
        return false;
    
    char temp = board[i][j];
    board[i][j] = '#';  // Mark as visited
    
    bool found = dfs(board, i+1, j, word, pos+1) ||
                 dfs(board, i-1, j, word, pos+1) ||
                 dfs(board, i, j+1, word, pos+1) ||
                 dfs(board, i, j-1, word, pos+1);
                 
    board[i][j] = temp;  // Restore
    return found;
}
``` 