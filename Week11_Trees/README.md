## Ağaç (Tree) Veri Yapısı

Bu bölümde, ağaç veri yapısının temel kavramları, özellikleri ve implementasyonu ele alınacaktır.

### İçerik

1. **Temel Kavramlar**
   - Terminoloji (Root, Node, Leaf, Parent, Child, Siblings)
   - N düğümlü ikili ağaçların sayısı
   - Yükseklik ve düğüm ilişkileri
   - İç ve dış düğümler
   - Strict (Tam) ikili ağaçlar
   - n-li ağaçlar

2. **Ağaç Temsili**
   - Dizi temsili
   - Bağlı liste temsili
   - Tam ve eksiksiz ikili ağaçlar
   - Strict vs Complete ikili ağaçlar

3. **Ağaç Gezinme (Traversal)**
   - Preorder gezinme
   - Inorder gezinme
   - Postorder gezinme
   - Level-order gezinme
   - İteratif vs özyinelemeli yaklaşımlar
   - Gezinme yöntemlerinden ağaç oluşturma

4. **Temel Operasyonlar**
   - Ağaç oluşturma
   - Yükseklik hesaplama
   - Düğüm sayma
   - Yaprak düğümleri sayma
   - Derinlik hesaplama

### Klasör Yapısı
```
Week8_Trees/
├── include/         # Header dosyaları
├── src/            # Kaynak dosyalar
├── test/           # Test dosyaları
└── examples/       # Örnek kullanımlar
```

### Gereksinimler
- C++17 veya üzeri
- CMake 3.15 veya üzeri
- Google Test (testler için) 