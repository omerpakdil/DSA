#include "string_ops.h"
#include <sstream>
#include <bitset>

// Counting Operations
size_t StringOps::countWords() const {
    if (isEmpty()) return 0;
    
    std::istringstream iss(str);
    size_t count = 0;
    std::string word;
    
    while (iss >> word) {
        count++;
    }
    
    return count;
}

size_t StringOps::countVowels() const {
    size_t count = 0;
    for (char c : str) {
        char lower = std::tolower(c);
        if (lower == 'a' || lower == 'e' || lower == 'i' || 
            lower == 'o' || lower == 'u') {
            count++;
        }
    }
    return count;
}

size_t StringOps::countConsonants() const {
    size_t count = 0;
    for (char c : str) {
        char lower = std::tolower(c);
        if (std::isalpha(c) && !(lower == 'a' || lower == 'e' || lower == 'i' || 
            lower == 'o' || lower == 'u')) {
            count++;
        }
    }
    return count;
}

// Validation Operations
bool StringOps::isValidString() const {
    for (char c : str) {
        if (!std::isprint(c)) return false;
    }
    return true;
}

bool StringOps::isPalindrome() const {
    if (isEmpty()) return true;
    
    std::string temp;
    // Remove non-alphanumeric characters and convert to lowercase
    for (char c : str) {
        if (std::isalnum(c)) {
            temp += std::tolower(c);
        }
    }
    
    size_t left = 0;
    size_t right = temp.length() - 1;
    
    while (left < right) {
        if (temp[left] != temp[right]) {
            return false;
        }
        left++;
        right--;
    }
    
    return true;
}

bool StringOps::isAnagram(const std::string& other) const {
    if (str.length() != other.length()) return false;
    
    std::unordered_map<char, int> freq;
    
    // Count frequency of characters in first string
    for (char c : str) {
        freq[std::tolower(c)]++;
    }
    
    // Decrease frequency for characters in second string
    for (char c : other) {
        char lower = std::tolower(c);
        if (freq.find(lower) == freq.end() || freq[lower] == 0) {
            return false;
        }
        freq[lower]--;
    }
    
    return true;
}

// Modification Operations
void StringOps::reverse() {
    size_t left = 0;
    size_t right = str.length() - 1;
    
    while (left < right) {
        std::swap(str[left], str[right]);
        left++;
        right--;
    }
}

void StringOps::removeSpaces() {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
}

void StringOps::removeDuplicates() {
    if (str.length() <= 1) return;
    
    std::string result;
    std::unordered_map<char, bool> seen;
    
    for (char c : str) {
        if (!seen[c]) {
            result += c;
            seen[c] = true;
        }
    }
    
    str = result;
}

// Finding Operations
std::vector<std::pair<char, int>> StringOps::findDuplicates() const {
    std::unordered_map<char, int> freq;
    std::vector<std::pair<char, int>> duplicates;
    
    // Count frequency of each character
    for (char c : str) {
        freq[c]++;
    }
    
    // Add characters with frequency > 1 to result
    for (const auto& pair : freq) {
        if (pair.second > 1) {
            duplicates.emplace_back(pair.first, pair.second);
        }
    }
    
    return duplicates;
}

std::vector<std::string> StringOps::findPermutations() const {
    std::vector<std::string> result;
    std::string temp = str;
    
    // Sort the string to get permutations in order
    std::sort(temp.begin(), temp.end());
    result.push_back(temp);
    
    while (std::next_permutation(temp.begin(), temp.end())) {
        result.push_back(temp);
    }
    
    return result;
}

// Bitwise Operations
std::vector<char> StringOps::findDuplicatesUsingBits() const {
    std::vector<char> duplicates;
    std::bitset<128> seen;     // For ASCII characters
    std::bitset<128> duplicate;
    
    for (char c : str) {
        if (seen[c]) {
            duplicate[c] = 1;
        } else {
            seen[c] = 1;
        }
    }
    
    // Collect duplicates
    for (size_t i = 0; i < 128; i++) {
        if (duplicate[i]) {
            duplicates.push_back(static_cast<char>(i));
        }
    }
    
    return duplicates;
} 