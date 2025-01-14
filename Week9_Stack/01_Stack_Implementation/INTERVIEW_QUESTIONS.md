# Stack Mülakat Soruları

## Temel Stack Soruları

### S1 ⭐ Stack nedir ve hangi prensiple çalışır? Array ve Linked List implementasyonlarının avantaj ve dezavantajları nelerdir?

Stack, LIFO (Last In First Out) prensibiyle çalışan bir veri yapısıdır. İki temel implementasyonu vardır:

Array Implementasyonu:
- Avantajlar:
  - Sabit zamanlı erişim
  - Bellek kullanımı daha verimli
  - Cache dostu
- Dezavantajlar:
  - Sabit boyut
  - Boyut değiştirme maliyetli
  - Overflow riski

Linked List Implementasyonu:
- Avantajlar:
  - Dinamik boyut
  - Kolay genişleme
  - Overflow riski yok
- Dezavantajlar:
  - Her node için ekstra bellek
  - Cache performansı düşük
  - Pointer yönetimi gerekli

### S2 ⭐ Stack'in temel operasyonlarını ve karmaşıklıklarını açıklayın.

Temel operasyonlar:
```cpp
void push(T value);    // O(1)
T pop();              // O(1)
T peek();             // O(1)
bool isEmpty();       // O(1)
size_t size();        // O(1)
```

### S3 ⭐⭐ Stack kullanarak bir string'in palindrom olup olmadığını nasıl kontrol edersiniz?

```cpp
bool isPalindrome(const std::string& str) {
    Stack<char> stack;
    int mid = str.length() / 2;
    
    // İlk yarıyı stack'e ekle
    for (int i = 0; i < mid; i++) {
        stack.push(str[i]);
    }
    
    // Tek uzunlukta ise ortadaki karakteri atla
    int startIndex = (str.length() % 2 == 0) ? mid : mid + 1;
    
    // İkinci yarı ile karşılaştır
    for (int i = startIndex; i < str.length(); i++) {
        if (stack.isEmpty() || stack.pop() != str[i]) {
            return false;
        }
    }
    
    return stack.isEmpty();
}
```

Karmaşıklık: O(n) zaman, O(n/2) alan

### S4 ⭐⭐ Stack kullanarak parantezlerin dengeli olup olmadığını nasıl kontrol edersiniz?

```cpp
bool isBalanced(const std::string& expr) {
    Stack<char> stack;
    
    for (char c : expr) {
        if (c == '(' || c == '{' || c == '[') {
            stack.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (stack.isEmpty()) return false;
            
            char top = stack.pop();
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return stack.isEmpty();
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S5 ⭐⭐ Stack kullanarak infix ifadeyi postfix'e nasıl dönüştürürsünüz?

```cpp
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infixToPostfix(const std::string& infix) {
    Stack<char> stack;
    std::string postfix;
    
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        }
        else if (c == '(') {
            stack.push(c);
        }
        else if (c == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                postfix += stack.pop();
            }
            if (!stack.isEmpty()) stack.pop(); // '(' karakterini çıkar
        }
        else { // Operatör
            while (!stack.isEmpty() && stack.peek() != '(' && 
                   precedence(stack.peek()) >= precedence(c)) {
                postfix += stack.pop();
            }
            stack.push(c);
        }
    }
    
    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }
    
    return postfix;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S6 ⭐⭐ Stack kullanarak postfix ifadeyi nasıl değerlendirirsiniz?

```cpp
int evaluatePostfix(const std::string& postfix) {
    Stack<int> stack;
    
    for (char c : postfix) {
        if (isdigit(c)) {
            stack.push(c - '0');
        }
        else {
            int val2 = stack.pop();
            int val1 = stack.pop();
            
            switch(c) {
                case '+': stack.push(val1 + val2); break;
                case '-': stack.push(val1 - val2); break;
                case '*': stack.push(val1 * val2); break;
                case '/': stack.push(val1 / val2); break;
            }
        }
    }
    
    return stack.pop();
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S7 ⭐⭐ Stack kullanarak bir array'in next greater element'lerini nasıl bulursunuz?

```cpp
std::vector<int> nextGreaterElements(const std::vector<int>& arr) {
    Stack<int> stack;
    std::vector<int> result(arr.size(), -1);
    
    for (int i = 0; i < arr.size(); i++) {
        while (!stack.isEmpty() && arr[stack.peek()] < arr[i]) {
            result[stack.pop()] = arr[i];
        }
        stack.push(i);
    }
    
    return result;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S8 ⭐⭐⭐ Minimum elemanı O(1) zamanda bulan bir stack nasıl implementersiniz?

```cpp
template<typename T>
class MinStack {
private:
    Stack<T> mainStack;
    Stack<T> minStack;
    
public:
    void push(T value) {
        mainStack.push(value);
        if (minStack.isEmpty() || value <= minStack.peek()) {
            minStack.push(value);
        }
    }
    
    T pop() {
        if (mainStack.isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        
        T value = mainStack.pop();
        if (value == minStack.peek()) {
            minStack.pop();
        }
        return value;
    }
    
    T getMin() {
        if (minStack.isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return minStack.peek();
    }
};
```

Karmaşıklık: 
- push: O(1) zaman
- pop: O(1) zaman
- getMin: O(1) zaman
Alan karmaşıklığı: O(n)

### S9 ⭐⭐⭐ İki stack kullanarak bir queue nasıl implementersiniz?

```cpp
template<typename T>
class QueueUsingStacks {
private:
    Stack<T> stack1; // Push için
    Stack<T> stack2; // Pop için
    
    void transferElements() {
        while (!stack1.isEmpty()) {
            stack2.push(stack1.pop());
        }
    }
    
public:
    void enqueue(T value) {
        stack1.push(value);
    }
    
    T dequeue() {
        if (stack2.isEmpty()) {
            if (stack1.isEmpty()) {
                throw std::underflow_error("Queue is empty");
            }
            transferElements();
        }
        return stack2.pop();
    }
    
    T front() {
        if (stack2.isEmpty()) {
            if (stack1.isEmpty()) {
                throw std::underflow_error("Queue is empty");
            }
            transferElements();
        }
        return stack2.peek();
    }
};
```

Karmaşıklık:
- enqueue: O(1) zaman
- dequeue: Amortized O(1) zaman
Alan karmaşıklığı: O(n)

### S10 ⭐⭐⭐ Stack kullanarak bir string'deki tüm ardışık tekrarları nasıl kaldırırsınız?

```cpp
std::string removeConsecutiveDuplicates(const std::string& str) {
    Stack<char> stack;
    
    for (char c : str) {
        if (!stack.isEmpty() && stack.peek() == c) {
            stack.pop();
        } else {
            stack.push(c);
        }
    }
    
    // Stack'teki karakterleri string'e dönüştür
    std::string result;
    Stack<char> tempStack;
    
    while (!stack.isEmpty()) {
        tempStack.push(stack.pop());
    }
    
    while (!tempStack.isEmpty()) {
        result += tempStack.pop();
    }
    
    return result;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S11 ⭐ Stack kullanarak bir string'i kelimelerine nasıl ayırırsınız?

```cpp
std::vector<std::string> splitWords(const std::string& str) {
    Stack<char> stack;
    std::vector<std::string> words;
    std::string currentWord;
    
    for (char c : str) {
        if (c == ' ') {
            // Stack'teki karakterleri kelimeye dönüştür
            while (!stack.isEmpty()) {
                currentWord = stack.pop() + currentWord;
            }
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        } else {
            stack.push(c);
        }
    }
    
    // Son kelimeyi ekle
    while (!stack.isEmpty()) {
        currentWord = stack.pop() + currentWord;
    }
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }
    
    return words;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S12 ⭐ Stack kullanarak bir string'deki kelimeleri nasıl tersine çevirirsiniz?

```cpp
std::string reverseWords(const std::string& str) {
    Stack<std::string> wordStack;
    std::string currentWord;
    
    for (char c : str) {
        if (c == ' ') {
            if (!currentWord.empty()) {
                wordStack.push(currentWord);
                currentWord.clear();
            }
        } else {
            currentWord += c;
        }
    }
    
    // Son kelimeyi ekle
    if (!currentWord.empty()) {
        wordStack.push(currentWord);
    }
    
    // Kelimeleri tersine çevir
    std::string result;
    while (!wordStack.isEmpty()) {
        result += wordStack.pop();
        if (!wordStack.isEmpty()) {
            result += " ";
        }
    }
    
    return result;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S13 ⭐⭐ Stack kullanarak bir string'deki nested parantezlerin derinliğini nasıl bulursunuz?

```cpp
int findMaxNesting(const std::string& str) {
    Stack<char> stack;
    int maxDepth = 0;
    int currentDepth = 0;
    
    for (char c : str) {
        if (c == '(') {
            currentDepth++;
            maxDepth = std::max(maxDepth, currentDepth);
            stack.push(c);
        } else if (c == ')') {
            if (stack.isEmpty() || stack.peek() != '(') {
                return -1; // Geçersiz parantez dizisi
            }
            stack.pop();
            currentDepth--;
        }
    }
    
    return stack.isEmpty() ? maxDepth : -1;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S14 ⭐ Stack kullanarak bir string'deki HTML tag'lerinin dengeli olup olmadığını nasıl kontrol edersiniz?

```cpp
bool isValidHTML(const std::string& html) {
    Stack<std::string> stack;
    size_t pos = 0;
    
    while (pos < html.length()) {
        if (html[pos] == '<') {
            size_t endPos = html.find('>', pos);
            if (endPos == std::string::npos) return false;
            
            std::string tag = html.substr(pos + 1, endPos - pos - 1);
            if (tag[0] != '/') {
                stack.push(tag);
            } else {
                if (stack.isEmpty()) return false;
                if (stack.pop() != tag.substr(1)) return false;
            }
            pos = endPos + 1;
        } else {
            pos++;
        }
    }
    
    return stack.isEmpty();
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S15 ⭐⭐ Stack kullanarak bir string'deki ardışık sayıları nasıl hesaplarsınız?

```cpp
int evaluateExpression(const std::string& expr) {
    Stack<int> numbers;
    Stack<char> operators;
    
    for (char c : expr) {
        if (isdigit(c)) {
            numbers.push(c - '0');
        } else if (c == '+' || c == '-') {
            while (!operators.isEmpty()) {
                int b = numbers.pop();
                int a = numbers.pop();
                char op = operators.pop();
                numbers.push(op == '+' ? a + b : a - b);
            }
            operators.push(c);
        }
    }
    
    while (!operators.isEmpty()) {
        int b = numbers.pop();
        int a = numbers.pop();
        char op = operators.pop();
        numbers.push(op == '+' ? a + b : a - b);
    }
    
    return numbers.pop();
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S16 ⭐ Stack kullanarak bir array'i nasıl tersine çevirirsiniz?

```cpp
template<typename T>
void reverseArray(T arr[], int size) {
    Stack<T> stack;
    
    // Array'i stack'e pushla
    for (int i = 0; i < size; i++) {
        stack.push(arr[i]);
    }
    
    // Stack'ten geri array'e popla
    for (int i = 0; i < size; i++) {
        arr[i] = stack.pop();
    }
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S17 ⭐⭐ Stack kullanarak bir string'deki nested function call'ları nasıl parse edersiniz?

```cpp
struct FunctionCall {
    std::string name;
    std::vector<std::string> args;
};

FunctionCall parseFunctionCall(const std::string& str) {
    Stack<char> stack;
    FunctionCall result;
    std::string currentArg;
    
    size_t nameEnd = str.find('(');
    result.name = str.substr(0, nameEnd);
    
    for (size_t i = nameEnd; i < str.length(); i++) {
        if (str[i] == '(') {
            stack.push(str[i]);
        } else if (str[i] == ')') {
            stack.pop();
            if (!currentArg.empty()) {
                result.args.push_back(currentArg);
                currentArg.clear();
            }
        } else if (str[i] == ',' && stack.size() == 1) {
            result.args.push_back(currentArg);
            currentArg.clear();
        } else if (str[i] != ' ') {
            currentArg += str[i];
        }
    }
    
    return result;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S18 ⭐ Stack kullanarak bir string'deki karakterlerin frekansını nasıl bulursunuz?

```cpp
std::map<char, int> findFrequency(const std::string& str) {
    Stack<char> stack;
    std::map<char, int> freq;
    
    // Karakterleri stack'e pushla
    for (char c : str) {
        stack.push(c);
    }
    
    // Stack'ten popla ve frekansları say
    while (!stack.isEmpty()) {
        freq[stack.pop()]++;
    }
    
    return freq;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S19 ⭐⭐ Stack kullanarak bir string'deki en uzun geçerli parantez alt dizisini nasıl bulursunuz?

```cpp
int longestValidParentheses(const std::string& str) {
    Stack<int> stack;
    stack.push(-1);
    int maxLen = 0;
    
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            stack.push(i);
        } else {
            stack.pop();
            if (stack.isEmpty()) {
                stack.push(i);
            } else {
                maxLen = std::max(maxLen, i - stack.peek());
            }
        }
    }
    
    return maxLen;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S20 ⭐ Stack kullanarak bir string'deki karakterleri sıralı bir şekilde nasıl yazdırırsınız?

```cpp
std::string sortString(const std::string& str) {
    Stack<char> stack;
    Stack<char> tempStack;
    
    // İlk karakteri stack'e pushla
    for (char c : str) {
        // Mevcut karakteri doğru pozisyona yerleştir
        while (!stack.isEmpty() && stack.peek() > c) {
            tempStack.push(stack.pop());
        }
        stack.push(c);
        while (!tempStack.isEmpty()) {
            stack.push(tempStack.pop());
        }
    }
    
    // Stack'ten sıralı string oluştur
    std::string result;
    while (!stack.isEmpty()) {
        result = stack.pop() + result;
    }
    
    return result;
}
```

Karmaşıklık: O(n²) zaman, O(n) alan

### S21 ⭐ Stack kullanarak bir string'deki sayıları nasıl toplayabilirsiniz?

```cpp
int sumNumbersInString(const std::string& str) {
    Stack<int> stack;
    int currentNum = 0;
    int sum = 0;
    
    for (char c : str) {
        if (isdigit(c)) {
            currentNum = currentNum * 10 + (c - '0');
        } else if (currentNum > 0) {
            stack.push(currentNum);
            currentNum = 0;
        }
    }
    
    if (currentNum > 0) {
        stack.push(currentNum);
    }
    
    while (!stack.isEmpty()) {
        sum += stack.pop();
    }
    
    return sum;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S22 ⭐ Stack kullanarak bir string'deki özel karakterleri nasıl kaldırırsınız?

```cpp
std::string removeSpecialCharacters(const std::string& str) {
    Stack<char> stack;
    
    for (char c : str) {
        if (isalnum(c)) {
            stack.push(c);
        }
    }
    
    std::string result;
    Stack<char> tempStack;
    
    while (!stack.isEmpty()) {
        tempStack.push(stack.pop());
    }
    
    while (!tempStack.isEmpty()) {
        result += tempStack.pop();
    }
    
    return result;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S23 ⭐⭐ Stack kullanarak bir string'deki nested parantezleri nasıl genişletirsiniz?

```cpp
std::string expandNestedParentheses(const std::string& str) {
    Stack<std::string> stack;
    std::string current;
    int repeat = 0;
    
    for (char c : str) {
        if (isdigit(c)) {
            repeat = repeat * 10 + (c - '0');
        } else if (c == '(') {
            if (!current.empty()) {
                stack.push(current);
            }
            stack.push(std::to_string(repeat));
            current.clear();
            repeat = 0;
        } else if (c == ')') {
            std::string temp = current;
            int count = std::stoi(stack.pop());
            
            current = stack.isEmpty() ? "" : stack.pop();
            while (count--) {
                current += temp;
            }
        } else {
            current += c;
        }
    }
    
    return current;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S24 ⭐⭐ Stack kullanarak bir string'deki palindrom alt dizileri nasıl bulursunuz?

```cpp
std::vector<std::string> findPalindromicSubstrings(const std::string& str) {
    Stack<std::string> stack;
    std::vector<std::string> palindromes;
    
    for (int i = 0; i < str.length(); i++) {
        // Tek uzunluklu palindromlar
        std::string odd = std::string(1, str[i]);
        int left = i - 1, right = i + 1;
        
        while (left >= 0 && right < str.length() && str[left] == str[right]) {
            odd = str[left] + odd + str[right];
            left--;
            right++;
        }
        stack.push(odd);
        
        // Çift uzunluklu palindromlar
        if (i < str.length() - 1 && str[i] == str[i + 1]) {
            std::string even = str.substr(i, 2);
            left = i - 1;
            right = i + 2;
            
            while (left >= 0 && right < str.length() && str[left] == str[right]) {
                even = str[left] + even + str[right];
                left--;
                right++;
            }
            stack.push(even);
        }
    }
    
    while (!stack.isEmpty()) {
        palindromes.push_back(stack.pop());
    }
    
    return palindromes;
}
```

Karmaşıklık: O(n²) zaman, O(n) alan

### S25 ⭐ Stack kullanarak bir string'deki kelime sayısını nasıl bulursunuz?

```cpp
int countWords(const std::string& str) {
    Stack<char> stack;
    int wordCount = 0;
    bool inWord = false;
    
    for (char c : str) {
        if (isspace(c)) {
            if (inWord) {
                wordCount++;
                inWord = false;
            }
            while (!stack.isEmpty()) {
                stack.pop();
            }
        } else {
            stack.push(c);
            inWord = true;
        }
    }
    
    if (inWord) {
        wordCount++;
    }
    
    return wordCount;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S26 ⭐⭐ Stack kullanarak bir string'deki nested function call'ların derinliğini nasıl bulursunuz?

```cpp
int findMaxFunctionNesting(const std::string& str) {
    Stack<char> stack;
    int maxDepth = 0;
    int currentDepth = 0;
    bool inFunction = false;
    
    for (char c : str) {
        if (c == '(') {
            if (inFunction) {
                currentDepth++;
                maxDepth = std::max(maxDepth, currentDepth);
            }
            stack.push(c);
        } else if (c == ')') {
            if (stack.isEmpty()) {
                return -1; // Geçersiz parantez dizisi
            }
            if (inFunction) {
                currentDepth--;
            }
            stack.pop();
        } else if (isalpha(c)) {
            inFunction = true;
        }
    }
    
    return stack.isEmpty() ? maxDepth : -1;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S27 ⭐ Stack kullanarak bir string'deki en uzun kelimeyi nasıl bulursunuz?

```cpp
std::string findLongestWord(const std::string& str) {
    Stack<char> stack;
    std::string longestWord;
    std::string currentWord;
    
    for (char c : str) {
        if (isspace(c)) {
            while (!stack.isEmpty()) {
                currentWord = stack.pop() + currentWord;
            }
            if (currentWord.length() > longestWord.length()) {
                longestWord = currentWord;
            }
            currentWord.clear();
        } else {
            stack.push(c);
        }
    }
    
    // Son kelimeyi kontrol et
    while (!stack.isEmpty()) {
        currentWord = stack.pop() + currentWord;
    }
    if (currentWord.length() > longestWord.length()) {
        longestWord = currentWord;
    }
    
    return longestWord;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S28 ⭐⭐ Stack kullanarak bir string'deki nested XML tag'lerini nasıl validate edersiniz?

```cpp
bool validateXML(const std::string& xml) {
    Stack<std::string> stack;
    size_t pos = 0;
    
    while (pos < xml.length()) {
        if (xml[pos] == '<') {
            if (pos + 1 < xml.length() && xml[pos + 1] == '/') {
                // Kapanış tag'i
                size_t endPos = xml.find('>', pos);
                if (endPos == std::string::npos) return false;
                
                std::string closeTag = xml.substr(pos + 2, endPos - pos - 2);
                if (stack.isEmpty() || stack.pop() != closeTag) {
                    return false;
                }
                pos = endPos + 1;
            } else {
                // Açılış tag'i
                size_t endPos = xml.find('>', pos);
                if (endPos == std::string::npos) return false;
                
                std::string openTag = xml.substr(pos + 1, endPos - pos - 1);
                stack.push(openTag);
                pos = endPos + 1;
            }
        } else {
            pos++;
        }
    }
    
    return stack.isEmpty();
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S29 ⭐ Stack kullanarak bir string'deki rakamları nasıl ayırırsınız?

```cpp
std::vector<int> extractNumbers(const std::string& str) {
    Stack<int> stack;
    int currentNum = 0;
    
    for (char c : str) {
        if (isdigit(c)) {
            currentNum = currentNum * 10 + (c - '0');
        } else if (currentNum > 0) {
            stack.push(currentNum);
            currentNum = 0;
        }
    }
    
    if (currentNum > 0) {
        stack.push(currentNum);
    }
    
    std::vector<int> numbers;
    while (!stack.isEmpty()) {
        numbers.push_back(stack.pop());
    }
    std::reverse(numbers.begin(), numbers.end());
    
    return numbers;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

### S30 ⭐⭐ Stack kullanarak bir string'deki nested JSON yapısını nasıl validate edersiniz?

```cpp
bool validateJSON(const std::string& json) {
    Stack<char> stack;
    bool inString = false;
    char lastChar = '\0';
    
    for (char c : json) {
        if (c == '"' && lastChar != '\\') {
            inString = !inString;
        } else if (!inString) {
            if (c == '{' || c == '[') {
                stack.push(c);
            } else if (c == '}') {
                if (stack.isEmpty() || stack.pop() != '{') {
                    return false;
                }
            } else if (c == ']') {
                if (stack.isEmpty() || stack.pop() != '[') {
                    return false;
                }
            }
        }
        lastChar = c;
    }
    
    return stack.isEmpty() && !inString;
}
```

Karmaşıklık: O(n) zaman, O(n) alan

Bu sorular, stack veri yapısının çeşitli kullanım senaryolarını kapsar. Her soru için verilen çözümler, optimal yaklaşımları ve yaygın edge case'leri ele alır.
