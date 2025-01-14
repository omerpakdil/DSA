#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <functional>
#include <memory>
#include <optional>
#include <variant>

// Container örnekleri
void containerExamples() {
    std::cout << "\n=== Container Örnekleri ===\n";
    
    // Sequence container'lar
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vec.push_back(6);
    std::cout << "Vector: ";
    for(int x : vec) std::cout << x << " ";
    std::cout << "\n";
    
    std::list<int> lst = {1, 2, 3};
    lst.push_front(0);
    lst.push_back(4);
    std::cout << "List: ";
    for(int x : lst) std::cout << x << " ";
    std::cout << "\n";
    
    std::deque<int> dq = {1, 2, 3};
    dq.push_front(0);
    dq.push_back(4);
    std::cout << "Deque: ";
    for(int x : dq) std::cout << x << " ";
    std::cout << "\n";
    
    // Associative container'lar
    std::set<int> s = {3, 1, 4, 1, 5};
    std::cout << "Set: ";
    for(int x : s) std::cout << x << " ";
    std::cout << "\n";
    
    std::map<std::string, int> m;
    m["one"] = 1;
    m["two"] = 2;
    m["three"] = 3;
    std::cout << "Map: ";
    for(const auto& [key, value] : m) {
        std::cout << key << "=" << value << " ";
    }
    std::cout << "\n";
    
    // Hash tabanlı container'lar
    std::unordered_map<std::string, int> um;
    um["apple"] = 1;
    um["banana"] = 2;
    std::cout << "Unordered Map: ";
    for(const auto& [key, value] : um) {
        std::cout << key << "=" << value << " ";
    }
    std::cout << "\n";
}

// Iterator örnekleri
void iteratorExamples() {
    std::cout << "\n=== Iterator Örnekleri ===\n";
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // İleri yönde iterasyon
    std::cout << "İleri yönde: ";
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Geri yönde iterasyon
    std::cout << "Geri yönde: ";
    for(auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // Random erişim
    auto it = vec.begin();
    it += 2;  // Üçüncü elemana git
    std::cout << "Random erişim: " << *it << "\n";
}

// Algorithm örnekleri
void algorithmExamples() {
    std::cout << "\n=== Algorithm Örnekleri ===\n";
    
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    
    // Sıralama
    std::sort(vec.begin(), vec.end());
    std::cout << "Sıralı: ";
    for(int x : vec) std::cout << x << " ";
    std::cout << "\n";
    
    // Eleman bulma
    auto it = std::find(vec.begin(), vec.end(), 4);
    if(it != vec.end()) {
        std::cout << "4 sayısının pozisyonu: " << (it - vec.begin()) << "\n";
    }
    
    // Eleman sayma
    int count = std::count(vec.begin(), vec.end(), 5);
    std::cout << "5 sayısının adedi: " << count << "\n";
    
    // Dönüştürme
    std::vector<int> squared(vec.size());
    std::transform(vec.begin(), vec.end(), squared.begin(),
        [](int x) { return x * x; });
    std::cout << "Kareleri: ";
    for(int x : squared) std::cout << x << " ";
    std::cout << "\n";
}

// Function object örnekleri
void functionObjectExamples() {
    std::cout << "\n=== Function Object Örnekleri ===\n";
    
    std::vector<int> vec = {3, 1, 4, 1, 5};
    
    // Özel karşılaştırıcı
    struct Compare {
        bool operator()(int a, int b) { return a > b; }
    };
    
    std::sort(vec.begin(), vec.end(), Compare());
    std::cout << "Sıralı (büyükten küçüğe): ";
    for(int x : vec) std::cout << x << " ";
    std::cout << "\n";
    
    // Lambda ifadesi
    auto square = [](int x) { return x * x; };
    std::cout << "5'in karesi: " << square(5) << "\n";
    
    // Değer yakalama
    int multiplier = 10;
    auto multiply = [multiplier](int x) { return x * multiplier; };
    std::cout << "5 * 10: " << multiply(5) << "\n";
}

// Utility bileşenleri örnekleri
void utilityExamples() {
    std::cout << "\n=== Utility Örnekleri ===\n";
    
    // Pair kullanımı
    std::pair<std::string, int> p = {"one", 1};
    std::cout << "Pair: " << p.first << "=" << p.second << "\n";
    
    // Smart pointer kullanımı
    auto sp = std::make_shared<int>(42);
    std::weak_ptr<int> wp = sp;
    std::cout << "Shared ptr değeri: " << *sp << "\n";
    std::cout << "Weak ptr expired mi? " << wp.expired() << "\n";
    
    // Optional kullanımı
    std::optional<int> opt = 42;
    if(opt) {
        std::cout << "Optional değeri: " << *opt << "\n";
    }
    
    // Variant kullanımı
    std::variant<int, std::string> var = "hello";
    std::cout << "Variant string tutuyor: " << std::get<std::string>(var) << "\n";
    var = 42;
    std::cout << "Variant artık int tutuyor: " << std::get<int>(var) << "\n";
}

int main() {
    containerExamples();
    iteratorExamples();
    algorithmExamples();
    functionObjectExamples();
    utilityExamples();
    return 0;
} 