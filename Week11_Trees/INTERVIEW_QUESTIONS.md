# İkili Ağaç (Binary Tree) Mülakat Soruları

## S1 ⭐ İkili Ağacın Yüksekliğini Bulma
Verilen bir ikili ağacın yüksekliğini bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
int getHeight(Node* root) {
    if (!root) return -1;
    return 1 + std::max(getHeight(root->left), getHeight(root->right));
}
```

**Time Complexity:** O(n)

## S2 ⭐ İkili Ağaçta Yaprak Düğümleri Sayma
Verilen bir ikili ağaçtaki yaprak düğümlerin sayısını bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
int countLeaves(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}
```

**Time Complexity:** O(n)

## S3 ⭐⭐ İkili Ağacın Simetrik Olup Olmadığını Kontrol Etme
Verilen bir ikili ağacın simetrik olup olmadığını kontrol eden bir fonksiyon yazın.

**Örnek Kod:**
```cpp
bool isSymmetric(Node* root) {
    if (!root) return true;
    return isMirror(root->left, root->right);
}

bool isMirror(Node* left, Node* right) {
    if (!left && !right) return true;
    if (!left || !right) return false;
    
    return (left->data == right->data) &&
           isMirror(left->left, right->right) &&
           isMirror(left->right, right->left);
}
```

**Time Complexity:** O(n)

## S4 ⭐⭐ İki Ağacın Aynı Olup Olmadığını Kontrol Etme
Verilen iki ikili ağacın yapısal olarak aynı olup olmadığını ve aynı değerleri içerip içermediğini kontrol eden bir fonksiyon yazın.

**Örnek Kod:**
```cpp
bool isSameTree(Node* p, Node* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    
    return (p->data == q->data) &&
           isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}
```

**Time Complexity:** O(min(n,m)) where n and m are the sizes of the trees

## S5 ⭐⭐ İkili Ağacın Alt Ağaç Toplamlarını Bulma
Her düğümün değerini, o düğümün alt ağacındaki tüm değerlerin toplamıyla değiştiren bir fonksiyon yazın.

**Örnek Kod:**
```cpp
int updateSubtreeSum(Node* root) {
    if (!root) return 0;
    
    int oldVal = root->data;
    int leftSum = updateSubtreeSum(root->left);
    int rightSum = updateSubtreeSum(root->right);
    
    root->data = oldVal + leftSum + rightSum;
    return root->data;
}
```

**Time Complexity:** O(n)

## S6 ⭐⭐⭐ İkili Ağacın Dengeli Olup Olmadığını Kontrol Etme
Bir ikili ağacın dengeli olup olmadığını kontrol eden bir fonksiyon yazın. Dengeli ağaç, her düğüm için sol ve sağ alt ağaçların yükseklik farkının en fazla 1 olduğu ağaçtır.

**Örnek Kod:**
```cpp
bool isBalanced(Node* root) {
    return checkHeight(root) != -1;
}

int checkHeight(Node* root) {
    if (!root) return 0;
    
    int leftHeight = checkHeight(root->left);
    if (leftHeight == -1) return -1;
    
    int rightHeight = checkHeight(root->right);
    if (rightHeight == -1) return -1;
    
    if (std::abs(leftHeight - rightHeight) > 1) return -1;
    
    return 1 + std::max(leftHeight, rightHeight);
}
```

**Time Complexity:** O(n)

## S7 ⭐⭐ İkili Ağacın Çapını Bulma
Bir ikili ağacın çapını (herhangi iki düğüm arasındaki en uzun yol) bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
int diameterOfBinaryTree(Node* root) {
    int diameter = 0;
    calculateHeight(root, diameter);
    return diameter;
}

int calculateHeight(Node* root, int& diameter) {
    if (!root) return 0;
    
    int leftHeight = calculateHeight(root->left, diameter);
    int rightHeight = calculateHeight(root->right, diameter);
    
    diameter = std::max(diameter, leftHeight + rightHeight);
    
    return 1 + std::max(leftHeight, rightHeight);
}
```

**Time Complexity:** O(n)

## S8 ⭐⭐ İkili Ağacın Ayna Görüntüsünü Oluşturma
Verilen bir ikili ağacın ayna görüntüsünü oluşturan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
void mirror(Node* root) {
    if (!root) return;
    
    // Alt ağaçları ayna görüntüsüne çevir
    mirror(root->left);
    mirror(root->right);
    
    // Düğümün sol ve sağ çocuklarını değiştir
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
}
```

**Time Complexity:** O(n)

## S9 ⭐⭐⭐ İkili Ağaçta En Yakın Ortak Atayı Bulma
Verilen iki düğümün en yakın ortak atasını bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
    if (!root || root == p || root == q) return root;
    
    Node* left = lowestCommonAncestor(root->left, p, q);
    Node* right = lowestCommonAncestor(root->right, p, q);
    
    if (!left) return right;
    if (!right) return left;
    return root;
}
```

**Time Complexity:** O(n)

## S10 ⭐⭐ İkili Ağacı Dikey Olarak Yazdırma
İkili ağacı dikey olarak yazdıran bir fonksiyon yazın.

**Örnek Kod:**
```cpp
void verticalOrder(Node* root) {
    if (!root) return;
    
    map<int, vector<int>> m;
    queue<pair<Node*, int>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        Node* node = q.front().first;
        int hd = q.front().second;
        q.pop();
        
        m[hd].push_back(node->data);
        
        if (node->left) q.push({node->left, hd-1});
        if (node->right) q.push({node->right, hd+1});
    }
    
    for (auto p : m) {
        for (int x : p.second) {
            cout << x << " ";
        }
        cout << endl;
    }
}
```

**Time Complexity:** O(n log n)

## S11 ⭐ İkili Ağacın Genişliğini Bulma
Verilen bir ikili ağacın maksimum genişliğini (herhangi bir seviyedeki düğüm sayısı) bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
int getMaxWidth(Node* root) {
    if (!root) return 0;
    
    int maxWidth = 0;
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        maxWidth = max(maxWidth, size);
        
        for (int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }
    
    return maxWidth;
}
```

**Time Complexity:** O(n)

## S12 ⭐ İkili Ağacın Sağ Görünümünü Bulma
İkili ağaca sağdan bakıldığında görünen düğümleri (her seviyenin en sağdaki düğümü) bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
vector<int> rightView(Node* root) {
    vector<int> result;
    if (!root) return result;
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();
            
            if (i == size - 1) {  // Her seviyenin son düğümü
                result.push_back(current->data);
            }
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }
    
    return result;
}
```

**Time Complexity:** O(n)

## S13 ⭐ İkili Ağacın Sol Görünümünü Bulma
İkili ağaca soldan bakıldığında görünen düğümleri bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
vector<int> leftView(Node* root) {
    vector<int> result;
    if (!root) return result;
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();
            
            if (i == 0) {  // Her seviyenin ilk düğümü
                result.push_back(current->data);
            }
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }
    
    return result;
}
```

**Time Complexity:** O(n)

## S14 ⭐⭐ İkili Ağacın Zigzag Traversal'ı
İkili ağacı zigzag sırasında (bir seviye soldan sağa, diğer seviye sağdan sola) gezen bir fonksiyon yazın.

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
        vector<int> currentLevel(size);
        
        for (int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();
            
            int index = leftToRight ? i : size - 1 - i;
            currentLevel[index] = current->data;
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        
        leftToRight = !leftToRight;
        result.push_back(currentLevel);
    }
    
    return result;
}
```

**Time Complexity:** O(n)

## S15 ⭐ İkili Ağacın Derinliğini Bulma
Verilen bir düğümün kök düğümden olan uzaklığını (derinliğini) bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
int findDepth(Node* root, Node* target, int depth = 0) {
    if (!root) return -1;
    if (root == target) return depth;
    
    int leftDepth = findDepth(root->left, target, depth + 1);
    if (leftDepth != -1) return leftDepth;
    
    return findDepth(root->right, target, depth + 1);
}
```

**Time Complexity:** O(n)

## S16 ⭐⭐ İkili Ağacın Yatay Mesafesini Bulma
Her düğümün kökten yatay mesafesini bulan (sol çocuk -1, sağ çocuk +1) bir fonksiyon yazın.

**Örnek Kod:**
```cpp
void findHorizontalDistance(Node* root, int hd, map<int, vector<int>>& m) {
    if (!root) return;
    
    m[hd].push_back(root->data);
    
    findHorizontalDistance(root->left, hd - 1, m);
    findHorizontalDistance(root->right, hd + 1, m);
}

map<int, vector<int>> getHorizontalDistance(Node* root) {
    map<int, vector<int>> m;
    findHorizontalDistance(root, 0, m);
    return m;
}
```

**Time Complexity:** O(n)

## S17 ⭐ İkili Ağacın Alt Ağaçlarını Bulma
Verilen bir ikili ağacın tüm alt ağaçlarını bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
vector<Node*> findSubtrees(Node* root) {
    vector<Node*> subtrees;
    if (!root) return subtrees;
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        
        subtrees.push_back(current);
        
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    
    return subtrees;
}
```

**Time Complexity:** O(n)

## S18 ⭐⭐ İkili Ağacın Sınır Düğümlerini Bulma
İkili ağacın sınır düğümlerini (sol sınır, yapraklar ve sağ sınır) bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
void addLeaves(Node* root, vector<int>& res) {
    if (!root) return;
    if (!root->left && !root->right) {
        res.push_back(root->data);
        return;
    }
    addLeaves(root->left, res);
    addLeaves(root->right, res);
}

vector<int> boundaryTraversal(Node* root) {
    vector<int> res;
    if (!root) return res;
    
    res.push_back(root->data);
    
    // Sol sınır
    Node* cur = root->left;
    while (cur && (cur->left || cur->right)) {
        res.push_back(cur->data);
        cur = cur->left ? cur->left : cur->right;
    }
    
    // Yapraklar
    addLeaves(root->left, res);
    addLeaves(root->right, res);
    
    // Sağ sınır (tersten)
    vector<int> rightBoundary;
    cur = root->right;
    while (cur && (cur->left || cur->right)) {
        rightBoundary.push_back(cur->data);
        cur = cur->right ? cur->right : cur->left;
    }
    for (int i = rightBoundary.size() - 1; i >= 0; --i) {
        res.push_back(rightBoundary[i]);
    }
    
    return res;
}
```

**Time Complexity:** O(n)

## S19 ⭐ İkili Ağacın Seviye Toplamlarını Bulma
Her seviyedeki düğümlerin toplamını bulan bir fonksiyon yazın.

**Örnek Kod:**
```cpp
vector<int> levelSum(Node* root) {
    vector<int> result;
    if (!root) return result;
    
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        int sum = 0;
        
        for (int i = 0; i < size; i++) {
            Node* current = q.front();
            q.pop();
            
            sum += current->data;
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        
        result.push_back(sum);
    }
    
    return result;
}
```

**Time Complexity:** O(n)

## S20 ⭐⭐ İkili Ağacın Köşegen Traversal'ı
İkili ağacı köşegen sırasında (aynı köşegen üzerindeki düğümler) gezen bir fonksiyon yazın.

**Örnek Kod:**
```cpp
vector<vector<int>> diagonalTraversal(Node* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    map<int, vector<int>> diagonalMap;  // <köşegen seviyesi, düğümler>
    queue<pair<Node*, int>> q;  // <düğüm, köşegen seviyesi>
    q.push({root, 0});
    
    while (!q.empty()) {
        Node* current = q.front().first;
        int level = q.front().second;
        q.pop();
        
        diagonalMap[level].push_back(current->data);
        
        if (current->left) q.push({current->left, level + 1});
        if (current->right) q.push({current->right, level});
    }
    
    for (auto& pair : diagonalMap) {
        result.push_back(pair.second);
    }
    
    return result;
}
```

**Time Complexity:** O(n)