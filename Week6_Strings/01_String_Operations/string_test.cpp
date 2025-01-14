#include "string_ops.h"
#include <iostream>
#include <cassert>

void testBasicOperations() {
    std::cout << "\n=== Testing Basic Operations ===\n";
    
    StringOps str("Hello World");
    std::cout << "String: " << str.toString() << "\n";
    std::cout << "Length: " << str.length() << "\n";
    std::cout << "Is Empty: " << (str.isEmpty() ? "Yes" : "No") << "\n";
    
    // Test empty string
    StringOps empty;
    assert(empty.isEmpty());
    assert(empty.length() == 0);
}

void testCaseOperations() {
    std::cout << "\n=== Testing Case Operations ===\n";
    
    StringOps str("Hello World 123");
    std::cout << "Original: " << str.toString() << "\n";
    
    str.toUpperCase();
    std::cout << "Uppercase: " << str.toString() << "\n";
    assert(str.toString() == "HELLO WORLD 123");
    
    str.toLowerCase();
    std::cout << "Lowercase: " << str.toString() << "\n";
    assert(str.toString() == "hello world 123");
}

void testCountingOperations() {
    std::cout << "\n=== Testing Counting Operations ===\n";
    
    StringOps str("Hello World! How are you?");
    std::cout << "String: " << str.toString() << "\n";
    std::cout << "Word Count: " << str.countWords() << "\n";
    std::cout << "Vowel Count: " << str.countVowels() << "\n";
    std::cout << "Consonant Count: " << str.countConsonants() << "\n";
    
    assert(str.countWords() == 5);
    assert(str.countVowels() == 8);
    assert(str.countConsonants() == 11);
}

void testValidationOperations() {
    std::cout << "\n=== Testing Validation Operations ===\n";
    
    StringOps str1("A man, a plan, a canal: Panama");
    StringOps str2("race a car");
    StringOps str3("Was it a car or a cat I saw?");
    
    std::cout << "Testing Palindromes:\n";
    std::cout << str1.toString() << " is " << (str1.isPalindrome() ? "" : "not ") << "a palindrome\n";
    std::cout << str2.toString() << " is " << (str2.isPalindrome() ? "" : "not ") << "a palindrome\n";
    std::cout << str3.toString() << " is " << (str3.isPalindrome() ? "" : "not ") << "a palindrome\n";
    
    assert(str1.isPalindrome());
    assert(!str2.isPalindrome());
    assert(str3.isPalindrome());
    
    // Test anagrams
    StringOps anagram1("listen");
    assert(anagram1.isAnagram("silent"));
    assert(!anagram1.isAnagram("hello"));
}

void testModificationOperations() {
    std::cout << "\n=== Testing Modification Operations ===\n";
    
    StringOps str("Hello World!");
    std::cout << "Original: " << str.toString() << "\n";
    
    str.reverse();
    std::cout << "Reversed: " << str.toString() << "\n";
    assert(str.toString() == "!dlroW olleH");
    
    str.removeSpaces();
    std::cout << "After removing spaces: " << str.toString() << "\n";
    assert(str.toString() == "!dlroWolleH");
    
    StringOps dupStr("programming");
    dupStr.removeDuplicates();
    std::cout << "After removing duplicates from 'programming': " << dupStr.toString() << "\n";
    assert(dupStr.toString() == "progamin");
}

void testFindingOperations() {
    std::cout << "\n=== Testing Finding Operations ===\n";
    
    StringOps str("programming");
    
    // Test finding duplicates
    auto duplicates = str.findDuplicates();
    std::cout << "Duplicates in 'programming':\n";
    for (const auto& pair : duplicates) {
        std::cout << "'" << pair.first << "' appears " << pair.second << " times\n";
    }
    
    // Test finding duplicates using bits
    auto bitDuplicates = str.findDuplicatesUsingBits();
    std::cout << "Duplicates (using bits):\n";
    for (char c : bitDuplicates) {
        std::cout << "'" << c << "' is duplicate\n";
    }
    
    // Test permutations
    StringOps permStr("abc");
    auto perms = permStr.findPermutations();
    std::cout << "Permutations of 'abc':\n";
    for (const auto& p : perms) {
        std::cout << p << " ";
    }
    std::cout << "\n";
}

int main() {
    try {
        testBasicOperations();
        testCaseOperations();
        testCountingOperations();
        testValidationOperations();
        testModificationOperations();
        testFindingOperations();
        
        std::cout << "\nAll tests completed successfully!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
} 