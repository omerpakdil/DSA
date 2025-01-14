#ifndef STRING_OPS_H
#define STRING_OPS_H

#include <string>
#include <cctype>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <algorithm>

class StringOps {
private:
    std::string str;

public:
    // Constructors
    explicit StringOps(const std::string& s = "") : str(s) {}
    
    // Basic Operations
    size_t length() const { return str.length(); }
    bool isEmpty() const { return str.empty(); }
    
    // Case Operations
    void toUpperCase() {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    }
    
    void toLowerCase() {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }
    
    // Counting Operations
    size_t countWords() const;
    size_t countVowels() const;
    size_t countConsonants() const;
    
    // Validation Operations
    bool isValidString() const;  // Checks if string contains valid characters
    bool isPalindrome() const;   // Checks if string is palindrome
    bool isAnagram(const std::string& other) const;
    
    // Modification Operations
    void reverse();
    void removeSpaces();
    void removeDuplicates();
    
    // Finding Operations
    std::vector<std::pair<char, int>> findDuplicates() const;
    std::vector<std::string> findPermutations() const;
    
    // Bitwise Operations
    std::vector<char> findDuplicatesUsingBits() const;
    
    // Utility Operations
    std::string toString() const { return str; }
    void setString(const std::string& s) { str = s; }
    char at(size_t index) const {
        if (index >= str.length()) throw std::out_of_range("Index out of range");
        return str[index];
    }
    
    // Operator Overloading
    bool operator==(const StringOps& other) const { return str == other.str; }
    bool operator!=(const StringOps& other) const { return !(*this == other); }
    char operator[](size_t index) const { return at(index); }
};

#endif // STRING_OPS_H 