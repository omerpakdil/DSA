# String İşlemleri Mülakat Soruları

**S1 ⭐**: String'lerde immutability nedir? C++'ta string'lerin bellek yönetimi nasıl yapılır?
- String immutability, bir string'in oluşturulduktan sonra değiştirilemez olması demektir
- C++'ta std::string sınıfı mutable'dır (değiştirilebilir)
- Bellek yönetimi:
```cpp
std::string str = "Hello";  // Stack'te string objesi, heap'te data
str += " World";           // Yeni bellek alokasyonu ve kopyalama
```
- Copy-on-write optimizasyonu
- Small string optimization (SSO)

**S2 ⭐**: String'de bir karakterin tekrar sayısını en verimli şekilde nasıl bulursunuz?
```cpp
int findCharFrequency(const string& str, char target) {
    // 1. Hash Map yaklaşımı - O(n)
    unordered_map<char, int> freq;
    for(char c : str) freq[c]++;
    return freq[target];
    
    // 2. Count yaklaşımı - O(n)
    return count(str.begin(), str.end(), target);
    
    // 3. Manuel sayma - O(n)
    int count = 0;
    for(char c : str) 
        if(c == target) count++;
    return count;
}
```

**S3 ⭐⭐**: String'de tekrar eden ilk karakteri nasıl bulursunuz?
```cpp
char findFirstRepeating(const string& str) {
    // 1. Hash Set yaklaşımı - O(n)
    unordered_set<char> seen;
    for(char c : str) {
        if(seen.count(c)) return c;
        seen.insert(c);
    }
    return '\0';
    
    // 2. Bit Vector yaklaşımı (ASCII) - O(n)
    bitset<256> seen;
    for(char c : str) {
        if(seen[c]) return c;
        seen[c] = 1;
    }
    return '\0';
}
```

**S4 ⭐⭐**: String'de tekrar etmeyen ilk karakteri bulun
```cpp
char findFirstNonRepeating(const string& str) {
    // Hash Map yaklaşımı - O(n)
    vector<int> freq(256, 0);
    
    // İlk geçiş: Frekansları say
    for(char c : str) {
        freq[c]++;
    }
    
    // İkinci geçiş: İlk tekrar etmeyeni bul
    for(char c : str) {
        if(freq[c] == 1) return c;
    }
    
    return '\0';
}
```

**S5 ⭐⭐**: String'de tüm permütasyonları nasıl bulursunuz?
```cpp
void findPermutations(string str, int left, int right) {
    // Base case
    if(left == right) {
        cout << str << endl;
        return;
    }
    
    // Her karakter için permütasyon oluştur
    for(int i = left; i <= right; i++) {
        // Karakterleri değiştir
        swap(str[left], str[i]);
        
        // Recursive olarak alt permütasyonları bul
        findPermutations(str, left + 1, right);
        
        // Geri al (backtrack)
        swap(str[left], str[i]);
    }
}
```
- Time Complexity: O(n!)
- Space Complexity: O(n) - recursion stack

**S6 ⭐⭐**: İki string'in rotasyon olup olmadığını kontrol edin (örn: "waterbottle" "erbottlewat" birbirinin rotasyonudur)
```cpp
bool isRotation(const string& s1, const string& s2) {
    if(s1.length() != s2.length()) return false;
    
    // s1+s1 içinde s2'yi ara
    string temp = s1 + s1;
    return temp.find(s2) != string::npos;
}
```
- Time Complexity: O(n)
- KMP algoritması kullanılabilir

**S7 ⭐⭐**: String sıkıştırma: Tekrar eden karakterleri sayılarıyla değiştirin
```cpp
string compressString(const string& str) {
    if(str.empty()) return str;
    
    string result;
    char current = str[0];
    int count = 1;
    
    for(size_t i = 1; i <= str.length(); i++) {
        if(i < str.length() && str[i] == current) {
            count++;
        } else {
            result += current + to_string(count);
            if(i < str.length()) {
                current = str[i];
                count = 1;
            }
        }
    }
    
    return result.length() < str.length() ? result : str;
}
```
- Input: "aabbbcccc" → Output: "a2b3c4"
- Eğer sıkıştırılmış hali daha uzunsa orijinali döndür

**S8 ⭐⭐**: String'de tüm palindromik alt stringleri bulun
```cpp
vector<string> findPalindromicSubstrings(const string& str) {
    vector<string> result;
    
    // Her karakteri merkez alarak genişlet
    for(int i = 0; i < str.length(); i++) {
        // Tek uzunluklu palindromlar
        expandAroundCenter(str, i, i, result);
        
        // Çift uzunluklu palindromlar
        expandAroundCenter(str, i, i+1, result);
    }
    
    return result;
}

void expandAroundCenter(const string& str, int left, int right, 
                       vector<string>& result) {
    while(left >= 0 && right < str.length() && 
          str[left] == str[right]) {
        result.push_back(str.substr(left, right-left+1));
        left--;
        right++;
    }
}
```
- Time Complexity: O(n²)
- Manacher's Algorithm ile O(n)'de çözülebilir

**S9 ⭐⭐⭐**: String'de en uzun palindromik alt stringi bulun
```cpp
string longestPalindromicSubstring(const string& str) {
    if(str.length() < 2) return str;
    
    int start = 0, maxLength = 1;
    int n = str.length();
    
    // dp[i][j]: str[i..j] palindrom mu?
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    
    // Tek karakterli palindromlar
    for(int i = 0; i < n; i++) 
        dp[i][i] = true;
    
    // İki karakterli palindromlar
    for(int i = 0; i < n-1; i++) {
        if(str[i] == str[i+1]) {
            dp[i][i+1] = true;
            start = i;
            maxLength = 2;
        }
    }
    
    // Üç ve daha uzun palindromlar
    for(int len = 3; len <= n; len++) {
        for(int i = 0; i < n-len+1; i++) {
            int j = i + len - 1;
            
            if(str[i] == str[j] && dp[i+1][j-1]) {
                dp[i][j] = true;
                if(len > maxLength) {
                    start = i;
                    maxLength = len;
                }
            }
        }
    }
    
    return str.substr(start, maxLength);
}
```
- Time Complexity: O(n²)
- Space Complexity: O(n²)
- Manacher's Algorithm ile O(n)'de çözülebilir

**S10 ⭐⭐⭐**: String'de en uzun ortak alt stringi bulun (LCS)
```cpp
string longestCommonSubstring(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    
    // dp[i][j]: str1[0..i] ve str2[0..j] için LCS uzunluğu
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    int maxLength = 0;
    int endIndex = 0;
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                
                if(dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;
                }
            }
        }
    }
    
    return str1.substr(endIndex - maxLength + 1, maxLength);
}
```
- Time Complexity: O(m*n)
- Space Complexity: O(m*n)
- Suffix Tree ile O(m+n)'de çözülebilir 

**S11 ⭐**: String'i kelimelerine ayırın (string tokenization)
```cpp
vector<string> splitString(const string& str, char delimiter = ' ') {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    
    while(getline(ss, token, delimiter)) {
        if(!token.empty()) {  // Boş token'ları atla
            tokens.push_back(token);
        }
    }
    return tokens;
}
```
- Time Complexity: O(n)
- Space Complexity: O(n)
- std::stringstream kullanımı
- Farklı delimiter'lar için uyarlanabilir

**S12 ⭐**: String'deki kelimeleri ters çevirin ("Hello World" → "olleH dlroW")
```cpp
string reverseWords(string str) {
    stringstream ss(str);
    string word, result;
    
    while(ss >> word) {
        reverse(word.begin(), word.end());
        result += word + " ";
    }
    
    // Son boşluğu kaldır
    if(!result.empty()) {
        result.pop_back();
    }
    
    return result;
}
```
- Time Complexity: O(n)
- Her kelimeyi ayrı ayrı ters çevirir
- Kelime sırası korunur

**S13 ⭐**: String'de parantezlerin dengeli olup olmadığını kontrol edin
```cpp
bool isBalancedParentheses(const string& str) {
    stack<char> st;
    
    for(char c : str) {
        if(c == '(' || c == '{' || c == '[') {
            st.push(c);
        }
        else if(c == ')' || c == '}' || c == ']') {
            if(st.empty()) return false;
            
            char top = st.top();
            if((c == ')' && top != '(') ||
               (c == '}' && top != '{') ||
               (c == ']' && top != '[')) {
                return false;
            }
            st.pop();
        }
    }
    
    return st.empty();
}
```
- Time Complexity: O(n)
- Stack kullanarak çözüm
- Farklı parantez tipleri için genişletilebilir

**S14 ⭐⭐**: String'de ardışık tekrar eden karakterleri kaldırın ("aabbcc" → "abc")
```cpp
string removeConsecutiveDuplicates(string str) {
    if(str.empty()) return str;
    
    string result;
    result += str[0];  // İlk karakteri ekle
    
    for(size_t i = 1; i < str.length(); i++) {
        if(str[i] != str[i-1]) {
            result += str[i];
        }
    }
    
    return result;
}
```
- Time Complexity: O(n)
- Space Complexity: O(n)
- In-place çözüm de mümkün

**S15 ⭐⭐**: İki string arasındaki edit distance'ı bulun (Levenshtein Distance)
```cpp
int minEditDistance(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    
    // dp[i][j]: str1[0..i] ve str2[0..j] arası min edit distance
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    // Base cases
    for(int i = 0; i <= m; i++) dp[i][0] = i;
    for(int j = 0; j <= n; j++) dp[0][j] = j;
    
    // Fill dp table
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min({dp[i-1][j],     // deletion
                                  dp[i][j-1],     // insertion
                                  dp[i-1][j-1]}); // replacement
            }
        }
    }
    
    return dp[m][n];
}
```
- Time Complexity: O(m*n)
- Space Complexity: O(m*n)
- Dinamik programlama çözümü

**S16 ⭐⭐**: String'de en uzun tekrar eden substring'i bulun
```cpp
string longestRepeatingSubstring(const string& str) {
    int n = str.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    
    int maxLength = 0;
    int endIndex = 0;
    
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(str[i-1] == str[j-1] && dp[i-1][j-1] < j - i) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if(dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;
                }
            }
        }
    }
    
    return maxLength > 0 ? str.substr(endIndex - maxLength + 1, maxLength) : "";
}
```
- Time Complexity: O(n²)
- Space Complexity: O(n²)
- Suffix Array ile O(n log n)'de çözülebilir

**S17 ⭐⭐**: String'de verilen pattern'i bulun (KMP Algorithm)
```cpp
vector<int> computeLPS(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    
    int len = 0;
    int i = 1;
    
    while(i < m) {
        if(pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if(len != 0) {
                len = lps[len-1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

vector<int> KMPSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.length();
    int m = pattern.length();
    
    vector<int> lps = computeLPS(pattern);
    
    int i = 0, j = 0;
    while(i < n) {
        if(pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if(j == m) {
            result.push_back(i-j);
            j = lps[j-1];
        } else if(i < n && pattern[j] != text[i]) {
            if(j != 0) {
                j = lps[j-1];
            } else {
                i++;
            }
        }
    }
    
    return result;
}
```
- Time Complexity: O(n+m)
- Space Complexity: O(m)
- Pattern matching için optimal algoritma

**S18 ⭐⭐**: String'de en küçük pencere boyutunu bulun (tüm karakterleri içeren)
```cpp
string minWindow(const string& str) {
    vector<int> freq(256, 0);
    int distinct = 0;
    
    // Farklı karakter sayısını bul
    for(char c : str) {
        if(freq[c] == 0) distinct++;
        freq[c]++;
    }
    
    int start = 0, minLen = str.length();
    int startIndex = 0;
    vector<int> currFreq(256, 0);
    int count = 0;
    
    for(int i = 0; i < str.length(); i++) {
        currFreq[str[i]]++;
        if(currFreq[str[i]] == 1) count++;
        
        if(count == distinct) {
            while(currFreq[str[start]] > 1) {
                currFreq[str[start]]--;
                start++;
            }
            
            if(i - start + 1 < minLen) {
                minLen = i - start + 1;
                startIndex = start;
            }
        }
    }
    
    return str.substr(startIndex, minLen);
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Sliding window tekniği

**S19 ⭐⭐**: String'de tüm alt dizileri bulun
```cpp
vector<string> findAllSubstrings(const string& str) {
    vector<string> result;
    int n = str.length();
    
    // Her başlangıç noktası için
    for(int len = 1; len <= n; len++) {
        // Her uzunluk için
        for(int start = 0; start <= n - len; start++) {
            result.push_back(str.substr(start, len));
        }
    }
    
    return result;
}
```
- Time Complexity: O(n³)
- Space Complexity: O(n³)
- Tüm olası alt dizileri listeler

**S20 ⭐⭐**: String'de en uzun prefix'i bulun (birden çok string arasında)
```cpp
string longestCommonPrefix(const vector<string>& strs) {
    if(strs.empty()) return "";
    
    // İlk string'i referans al
    string prefix = strs[0];
    
    for(size_t i = 1; i < strs.size(); i++) {
        // Prefix'i kısalt
        while(strs[i].find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.length()-1);
            if(prefix.empty()) return "";
        }
    }
    
    return prefix;
}
```
- Time Complexity: O(S), S = tüm karakterlerin toplamı
- Space Complexity: O(1)
- Binary search ile optimize edilebilir 

**S21 ⭐**: String'i sayıya çevirin (atoi implementasyonu)
```cpp
int stringToInteger(const string& str) {
    int result = 0;
    int sign = 1;
    int i = 0;
    
    // Boşlukları atla
    while(i < str.length() && str[i] == ' ') i++;
    
    // İşareti kontrol et
    if(i < str.length() && (str[i] == '+' || str[i] == '-')) {
        sign = (str[i] == '+') ? 1 : -1;
        i++;
    }
    
    // Sayıyı oluştur
    while(i < str.length() && isdigit(str[i])) {
        // Taşma kontrolü
        if(result > INT_MAX/10 || (result == INT_MAX/10 && str[i]-'0' > INT_MAX%10)) {
            return sign == 1 ? INT_MAX : INT_MIN;
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return sign * result;
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Taşma kontrolü önemli
- Whitespace ve işaret kontrolü

**S22 ⭐**: String'de ilk tekrar etmeyen karakteri bulun
```cpp
char firstNonRepeatingChar(const string& str) {
    vector<int> count(256, 0);
    vector<int> index(256, -1);
    
    // Frekans ve ilk indeksleri bul
    for(int i = 0; i < str.length(); i++) {
        count[str[i]]++;
        if(index[str[i]] == -1) {
            index[str[i]] = i;
        }
    }
    
    // İlk tekrar etmeyen karakteri bul
    int minIndex = INT_MAX;
    for(int i = 0; i < 256; i++) {
        if(count[i] == 1 && index[i] < minIndex) {
            minIndex = index[i];
        }
    }
    
    return minIndex == INT_MAX ? '\0' : str[minIndex];
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Tek geçişte çözüm mümkün
- ASCII karakterler için sabit alan

**S23 ⭐**: String'i integer'a çevirmeden sayı olup olmadığını kontrol edin
```cpp
bool isValidNumber(const string& str) {
    int i = 0;
    bool hasDigit = false;
    
    // Başlangıç boşlukları
    while(i < str.length() && str[i] == ' ') i++;
    
    // İşaret kontrolü
    if(i < str.length() && (str[i] == '+' || str[i] == '-')) i++;
    
    // Sayı kısmı
    while(i < str.length() && isdigit(str[i])) {
        hasDigit = true;
        i++;
    }
    
    // Ondalık kısım
    if(i < str.length() && str[i] == '.') {
        i++;
        while(i < str.length() && isdigit(str[i])) {
            hasDigit = true;
            i++;
        }
    }
    
    // Son boşluklar
    while(i < str.length() && str[i] == ' ') i++;
    
    return hasDigit && i == str.length();
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Ondalık sayıları da kontrol eder
- Boşluk ve işaret kontrolü yapar

**S24 ⭐⭐**: String'de kelime frekanslarını bulun
```cpp
unordered_map<string, int> wordFrequency(const string& text) {
    unordered_map<string, int> freq;
    stringstream ss(text);
    string word;
    
    // Kelimeleri ayır ve say
    while(ss >> word) {
        // Noktalama işaretlerini kaldır
        word.erase(remove_if(word.begin(), word.end(), 
                           [](char c) { return !isalnum(c); }), 
                  word.end());
        
        // Küçük harfe çevir
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        
        if(!word.empty()) {
            freq[word]++;
        }
    }
    
    return freq;
}
```
- Time Complexity: O(n)
- Space Complexity: O(k), k = unique kelime sayısı
- Case-insensitive sayım
- Noktalama işaretlerini temizler

**S25 ⭐⭐**: String'de verilen kelimenin tüm anagramlarını bulun
```cpp
vector<int> findAnagrams(const string& str, const string& pattern) {
    vector<int> result;
    if(str.length() < pattern.length()) return result;
    
    vector<int> patternFreq(26, 0);
    vector<int> windowFreq(26, 0);
    
    // Pattern frekanslarını hesapla
    for(char c : pattern) {
        patternFreq[c - 'a']++;
    }
    
    // İlk pencereyi oluştur
    for(int i = 0; i < pattern.length(); i++) {
        windowFreq[str[i] - 'a']++;
    }
    
    // Frekanslar eşitse ilk indeksi ekle
    if(patternFreq == windowFreq) {
        result.push_back(0);
    }
    
    // Sliding window
    for(int i = pattern.length(); i < str.length(); i++) {
        windowFreq[str[i-pattern.length()] - 'a']--;
        windowFreq[str[i] - 'a']++;
        
        if(patternFreq == windowFreq) {
            result.push_back(i - pattern.length() + 1);
        }
    }
    
    return result;
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Sliding window tekniği
- Sadece küçük harfler için

**S26 ⭐⭐**: String'de en uzun palindromik subsequence'ı bulun
```cpp
int longestPalindromicSubsequence(const string& str) {
    int n = str.length();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // Tek karakterli palindromlar
    for(int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    // İki ve daha uzun palindromlar
    for(int len = 2; len <= n; len++) {
        for(int i = 0; i < n-len+1; i++) {
            int j = i + len - 1;
            
            if(str[i] == str[j] && len == 2) {
                dp[i][j] = 2;
            }
            else if(str[i] == str[j]) {
                dp[i][j] = dp[i+1][j-1] + 2;
            }
            else {
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[0][n-1];
}
```
- Time Complexity: O(n²)
- Space Complexity: O(n²)
- Dinamik programlama çözümü
- Alt problemleri kullanır

**S27 ⭐⭐**: String'de tüm palindromik dekompozisyonları bulun
```cpp
void palindromicDecompositions(const string& str, int start, 
                             vector<string>& current,
                             vector<vector<string>>& result) {
    if(start >= str.length()) {
        result.push_back(current);
        return;
    }
    
    for(int end = start; end < str.length(); end++) {
        if(isPalindrome(str, start, end)) {
            current.push_back(str.substr(start, end-start+1));
            palindromicDecompositions(str, end+1, current, result);
            current.pop_back();
        }
    }
}

bool isPalindrome(const string& str, int start, int end) {
    while(start < end) {
        if(str[start++] != str[end--]) return false;
    }
    return true;
}
```
- Time Complexity: O(n * 2^n)
- Space Complexity: O(n)
- Backtracking çözümü
- Tüm olası bölünmeleri dener

**S28 ⭐⭐**: String'de en uzun unique substring'i bulun
```cpp
string longestUniqueSubstring(const string& str) {
    vector<int> lastSeen(256, -1);
    int start = 0;
    int maxLength = 0;
    int maxStart = 0;
    
    for(int i = 0; i < str.length(); i++) {
        if(lastSeen[str[i]] >= start) {
            start = lastSeen[str[i]] + 1;
        }
        
        lastSeen[str[i]] = i;
        
        if(i - start + 1 > maxLength) {
            maxLength = i - start + 1;
            maxStart = start;
        }
    }
    
    return str.substr(maxStart, maxLength);
}
```
- Time Complexity: O(n)
- Space Complexity: O(1)
- Sliding window tekniği
- Son görülen pozisyonları takip eder

**S29 ⭐⭐**: String'de wildcard pattern matching yapın
```cpp
bool wildcardMatching(const string& str, const string& pattern) {
    int m = str.length();
    int n = pattern.length();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    
    // Boş string ve pattern eşleşir
    dp[0][0] = true;
    
    // Pattern'deki başlangıç yıldızları
    for(int j = 1; j <= n; j++) {
        if(pattern[j-1] == '*') {
            dp[0][j] = dp[0][j-1];
        }
    }
    
    // DP tablosunu doldur
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(pattern[j-1] == '*') {
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
            else if(pattern[j-1] == '?' || str[i-1] == pattern[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            }
        }
    }
    
    return dp[m][n];
}
```
- Time Complexity: O(m*n)
- Space Complexity: O(m*n)
- '*' ve '?' karakterlerini destekler
- Dinamik programlama çözümü

**S30 ⭐⭐**: String'de regex pattern matching yapın
```cpp
bool isMatch(const string& str, const string& pattern) {
    int m = str.length();
    int n = pattern.length();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    
    // Boş string ve pattern eşleşir
    dp[0][0] = true;
    
    // Pattern'deki başlangıç yıldızları
    for(int j = 1; j <= n; j++) {
        if(pattern[j-1] == '*') {
            dp[0][j] = dp[0][j-2];
        }
    }
    
    // DP tablosunu doldur
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(pattern[j-1] == '.') {
                dp[i][j] = dp[i-1][j-1];
            }
            else if(pattern[j-1] == '*') {
                dp[i][j] = dp[i][j-2];  // 0 occurrence
                if(pattern[j-2] == '.' || pattern[j-2] == str[i-1]) {
                    dp[i][j] = dp[i][j] || dp[i-1][j];
                }
            }
            else {
                dp[i][j] = dp[i-1][j-1] && str[i-1] == pattern[j-1];
            }
        }
    }
    
    return dp[m][n];
}
```
- Time Complexity: O(m*n)
- Space Complexity: O(m*n)
- '.' ve '*' karakterlerini destekler
- Dinamik programlama çözümü 