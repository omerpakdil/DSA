# Array ADT (Soyut Veri Tipi)

## İçerik
1. [Array ADT Nedir?](#array-adt-nedir)
2. [Temel Operasyonlar](#temel-operasyonlar)
3. [Arama Operasyonları](#arama-operasyonları)
4. [Yardımcı Operasyonlar](#yardımcı-operasyonlar)
5. [Array Manipülasyonu](#array-manipülasyonu)
6. [Set Operasyonları](#set-operasyonları)
7. [Kompleksite Analizi](#kompleksite-analizi)

## Array ADT Nedir?
Array ADT (Abstract Data Type), array veri yapısı üzerinde gerçekleştirilebilecek tüm operasyonları tanımlayan soyut bir veri tipidir. Bu yapı:
- Veriyi saklamak için bir array
- Array'in boyutu
- Array'in kapasitesi
- Array üzerinde gerçekleştirilebilecek operasyonlar

gibi bileşenleri içerir.

## Temel Operasyonlar
1. **Display**: Array'i görüntüleme
2. **Add/Append**: Sona eleman ekleme
3. **Insert**: Belirli bir indekse eleman ekleme
4. **Delete**: Belirli bir indeksten eleman silme
5. **Search**: Eleman arama
6. **Get**: İndeksteki elemanı getirme
7. **Set**: İndeksteki elemanı güncelleme

## Arama Operasyonları
1. **Linear Search**: O(n)
   - Basit linear search
   - İyileştirilmiş linear search (Transposition/Move-to-Front)
2. **Binary Search**: O(log n)
   - Iterative implementation
   - Recursive implementation

## Yardımcı Operasyonlar
1. **Get**: İndeksteki elemanı getirme
2. **Set**: İndeksteki elemanı güncelleme
3. **Max/Min**: En büyük/küçük elemanı bulma
4. **Average**: Ortalama hesaplama
5. **Reverse**: Array'i ters çevirme
6. **Shift/Rotate**: Kaydırma ve döndürme işlemleri

## Array Manipülasyonu
1. **Reverse**: Array'i ters çevirme
2. **Shift Operations**:
   - Left Shift
   - Right Shift
3. **Rotate Operations**:
   - Left Rotate
   - Right Rotate

## Set Operasyonları
1. **Union**: İki array'in birleşimi
2. **Intersection**: İki array'in kesişimi
3. **Difference**: İki array'in farkı
4. **Membership**: Eleman kontrolü

## Kompleksite Analizi

| Operasyon | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Display | O(n) | O(1) |
| Add/Append | O(1) | O(1) |
| Insert | O(n) | O(1) |
| Delete | O(n) | O(1) |
| Linear Search | O(n) | O(1) |
| Binary Search | O(log n) | O(1) |
| Get/Set | O(1) | O(1) |
| Max/Min | O(n) | O(1) |
| Reverse | O(n) | O(1) |
| Shift/Rotate | O(n) | O(1) |
| Union/Intersection | O(m+n) | O(m+n) |

## Modern C++ Özellikleri
1. **RAII** prensipleri
2. **Move Semantics** desteği
3. **Template** kullanımı
4. **Exception Safety** garantisi
5. **Const Correctness**
6. **Smart Pointer** kullanımı (isteğe bağlı)
