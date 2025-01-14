# String Operations (String İşlemleri)

Bu bölümde, string (karakter dizisi) veri yapısı üzerinde gerçekleştirilebilecek temel ve ileri düzey işlemlerin implementasyonu yer almaktadır.

## İçerik

1. **Temel String İşlemleri**
   - String uzunluğunu bulma
   - Boş string kontrolü
   - Karakter erişimi ve değiştirme

2. **Case İşlemleri**
   - Büyük harfe çevirme (toUpperCase)
   - Küçük harfe çevirme (toLowerCase)

3. **Sayma İşlemleri**
   - Kelime sayısı (countWords)
   - Sesli harf sayısı (countVowels)
   - Sessiz harf sayısı (countConsonants)

4. **Doğrulama İşlemleri**
   - String geçerliliği kontrolü (isValidString)
   - Palindrom kontrolü (isPalindrome)
   - Anagram kontrolü (isAnagram)

5. **Değiştirme İşlemleri**
   - String'i ters çevirme (reverse)
   - Boşlukları kaldırma (removeSpaces)
   - Tekrar eden karakterleri kaldırma (removeDuplicates)

6. **Bulma İşlemleri**
   - Tekrar eden karakterleri bulma (findDuplicates)
   - Permütasyonları bulma (findPermutations)
   - Bit işlemleri ile tekrar eden karakterleri bulma (findDuplicatesUsingBits)

## Kullanım

```cpp
#include "string_ops.h"

int main() {
    // String oluşturma
    StringOps str("Hello World");
    
    // Temel işlemler
    size_t len = str.length();
    bool isEmpty = str.isEmpty();
    
    // Case işlemleri
    str.toUpperCase();  // "HELLO WORLD"
    str.toLowerCase();  // "hello world"
    
    // Sayma işlemleri
    size_t wordCount = str.countWords();     // 2
    size_t vowelCount = str.countVowels();   // 3
    
    // Doğrulama işlemleri
    bool isPal = str.isPalindrome();
    bool isAna = str.isAnagram("World Hello");
    
    // Değiştirme işlemleri
    str.reverse();          // "dlrow olleh"
    str.removeSpaces();     // "dlrowolleh"
    str.removeDuplicates(); // "dlroweh"
    
    return 0;
}
```

## Zaman Karmaşıklıkları

| İşlem | Karmaşıklık | Açıklama |
|-------|-------------|-----------|
| length | O(1) | String uzunluğunu döndürür |
| isEmpty | O(1) | Boş string kontrolü |
| toUpperCase/toLowerCase | O(n) | Her karakteri dönüştürür |
| countWords | O(n) | String'i tarayarak kelime sayar |
| countVowels/Consonants | O(n) | Her karakteri kontrol eder |
| isPalindrome | O(n) | String'i iki uçtan karşılaştırır |
| isAnagram | O(n) | Karakter frekanslarını karşılaştırır |
| reverse | O(n) | String'i ters çevirir |
| removeSpaces | O(n) | Boşlukları kaldırır |
| removeDuplicates | O(n) | Hash table kullanarak tekrarları kaldırır |
| findDuplicates | O(n) | Hash table ile tekrarları bulur |
| findPermutations | O(n!) | Tüm permütasyonları üretir |
| findDuplicatesUsingBits | O(n) | Bit manipülasyonu ile tekrarları bulur |

## Derleme ve Test

```bash
# Build klasörü oluştur
mkdir build && cd build

# CMake ile proje dosyalarını oluştur
cmake ..

# Projeyi derle
make

# Testleri çalıştır
./string_test
``` 