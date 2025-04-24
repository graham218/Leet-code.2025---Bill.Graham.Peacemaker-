#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <locale> // For std::tolower

// Function to check if a character is alphanumeric
bool isAlphaNumeric(char c) {
    return std::isalnum(c);
}

// 1. Two Pointers - Basic
//   - Project Use Case: Simple input validation in a small utility or script.
//   - Justification: Demonstrates the core two-pointer technique.  Easy to understand.
bool isPalindrome_TwoPointersBasic(const std::string& s) {
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// 2. Two Pointers - Alphanumeric Check
//   - Project Use Case: Validating user input in a form, filtering out special characters.
//   - Justification: More robust; handles real-world input with non-alphanumeric characters.
bool isPalindrome_TwoPointersAlphaNum(const std::string& s) {
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        // Skip non-alphanumeric characters
        while (left < right && !isAlphaNumeric(s[left])) {
            left++;
        }
        while (left < right && !isAlphaNumeric(s[right])) {
            right--;
        }
        // Case-insensitive comparison
        if (std::tolower(s[left]) != std::tolower(s[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

// 3. Using STL - remove_if and equal
//   - Project Use Case:  Part of a text processing pipeline in a larger application.
//   - Justification: Leverages the standard library for efficiency and conciseness.
bool isPalindrome_STL(const std::string& s) {
    std::string filtered_s;
    // Copy only alphanumeric characters, converting to lowercase
    for (char c : s) {
        if (std::isalnum(c)) {
            filtered_s += std::tolower(c);
        }
    }
    // Create a reversed copy for comparison
    std::string reversed_s = filtered_s;
    std::reverse(reversed_s.begin(), reversed_s.end());

    return filtered_s == reversed_s;
}

// 4. Recursive Approach
//    - Project Use Case:  Could be used in a functional programming style context, or for a problem
//      where the palindrome check is a sub-routine in a recursive algorithm.  Less common for
//      this specific problem, but demonstrates recursion.
//    - Justification: Demonstrates a different problem-solving paradigm (recursion).
bool isPalindrome_Recursive(const std::string& s, int left, int right) {
    if (left >= right) {
        return true; // Base case: empty or single char is a palindrome
    }
    // Skip non-alphanumeric characters
    while (left < right && !isAlphaNumeric(s[left])) {
        left++;
    }
    while (left < right && !isAlphaNumeric(s[right])) {
        right--;
    }

    if (std::tolower(s[left]) != std::tolower(s[right])) {
        return false; // Mismatch
    }
    return isPalindrome_Recursive(s, left + 1, right - 1); // Recursive call
}

bool isPalindrome_Recursive(const std::string& s) {
    return isPalindrome_Recursive(s, 0, s.length() - 1);
}

// 5. Using std::transform and std::equal
//    - Project Use Case: High-performance text processing, where efficiency is critical.
//    - Justification:  More optimized and modern C++; avoids explicit loops for filtering and comparison.
bool isPalindrome_TransformEqual(const std::string& s) {
    std::string filtered_s;
    // Transform and copy only alphanumeric characters, converting to lowercase
    std::transform(s.begin(), s.end(), std::back_inserter(filtered_s), [](unsigned char c){
        return std::isalnum(c) ? std::tolower(c) : 0; // 0 will be skipped
    });

    std::string reversed_s = filtered_s;
    std::reverse(reversed_s.begin(), reversed_s.end());
    return filtered_s == reversed_s;
}

int main() {
    std::string testString1 = "A man, a plan, a canal: Panama";
    std::string testString2 = "race a car";
    std::string testString3 = "Madam, I'm Adam!";
    std::string testString4 = "121";
    std::string testString5 = "hello";
    std::string testString6 = " "; // Empty string test case
    std::string testString7 = ".,";   //Punctuation test case

    std::cout << "Test String 1: " << testString1 << std::endl;
    std::cout << "Two Pointers Basic: " << isPalindrome_TwoPointersBasic(testString1) << std::endl;
    std::cout << "Two Pointers AlphaNum: " << isPalindrome_TwoPointersAlphaNum(testString1) << std::endl;
    std::cout << "STL: " << isPalindrome_STL(testString1) << std::endl;
    std::cout << "Recursive: " << isPalindrome_Recursive(testString1) << std::endl;
    std::cout << "Transform/Equal: " << isPalindrome_TransformEqual(testString1) << std::endl;

    std::cout << "\nTest String 2: " << testString2 << std::endl;
    std::cout << "Two Pointers Basic: " << isPalindrome_TwoPointersBasic(testString2) << std::endl;
    std::cout << "Two Pointers AlphaNum: " << isPalindrome_TwoPointersAlphaNum(testString2) << std::endl;
    std::cout << "STL: " << isPalindrome_STL(testString2) << std::endl;
    std::cout << "Recursive: " << isPalindrome_Recursive(testString2) << std::endl;
    std::cout << "Transform/Equal: " << isPalindrome_TransformEqual(testString2) << std::endl;

    std::cout << "\nTest String 3: " << testString3 << std::endl;
    std::cout << "Two Pointers Basic: " << isPalindrome_TwoPointersBasic(testString3) << std::endl;
    std::cout << "Two Pointers AlphaNum: " << isPalindrome_TwoPointersAlphaNum(testString3) << std::endl;
    std::cout << "STL: " << isPalindrome_STL(testString3) << std::endl;
    std::cout << "Recursive: " << isPalindrome_Recursive(testString3) << std::endl;
    std::cout << "Transform/Equal: " << isPalindrome_TransformEqual(testString3) << std::endl;

    std::cout << "\nTest String 4: " << testString4 << std::endl;
    std::cout << "Two Pointers Basic: " << isPalindrome_TwoPointersBasic(testString4) << std::endl;
    std::cout << "Two Pointers AlphaNum: " << isPalindrome_TwoPointersAlphaNum(testString4) << std::endl;
    std::cout << "STL: " << isPalindrome_STL(testString4) << std::endl;
    std::cout << "Recursive: " << isPalindrome_Recursive(testString4) << std::endl;
    std::cout << "Transform/Equal: " << isPalindrome_TransformEqual(testString4) << std::endl;

    std::cout << "\nTest String 5: " << testString5 << std::endl;
    std::cout << "Two Pointers Basic: " << isPalindrome_TwoPointersBasic(testString5) << std::endl;
    std::cout << "Two Pointers AlphaNum: " << isPalindrome_TwoPointersAlphaNum(testString5) << std::endl;
    std::cout << "STL: " << isPalindrome_STL(testString5) << std::endl;
    std::cout << "Recursive: " << isPalindrome_Recursive(testString5) << std::endl;
    std::cout << "Transform/Equal: " << isPalindrome_TransformEqual(testString5) << std::endl;

    std::cout << "\nTest String 6 (Empty): " << testString6 << std::endl;
    std::cout << "Two Pointers Basic: " << isPalindrome_TwoPointersBasic(testString6) << std::endl;
    std::cout << "Two Pointers AlphaNum: " << isPalindrome_TwoPointersAlphaNum(testString6) << std::endl;
    std::cout << "STL: " << isPalindrome_STL(testString6) << std::endl;
    std::cout << "Recursive: " << isPalindrome_Recursive(testString6) << std::endl;
    std::cout << "Transform/Equal: " << isPalindrome_TransformEqual(testString6) << std::endl;

    std::cout << "\nTest String 7 (Punctuation): " << testString7 << std::endl;
    std::cout << "Two Pointers Basic: " << isPalindrome_TwoPointersBasic(testString7) << std::endl;
    std::cout << "Two Pointers AlphaNum: " << isPalindrome_TwoPointersAlphaNum(testString7) << std::endl;
    std::cout << "STL: " << isPalindrome_STL(testString7) << std::endl;
    std::cout << "Recursive: " << isPalindrome_Recursive(testString7) << std::endl;
    std::cout << "Transform/Equal: " << isPalindrome_TransformEqual(testString7) << std::endl;

    return 0;
}
