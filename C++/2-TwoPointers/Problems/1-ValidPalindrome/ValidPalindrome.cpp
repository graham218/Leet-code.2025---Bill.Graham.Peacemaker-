#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype> // Include for std::isalnum, std::tolower

using namespace std;

// Helper function to check if a character is alphanumeric
bool isAlphanumeric(char c) {
    return std::isalnum(static_cast<unsigned char>(c));
}

// Helper function to convert a character to lowercase
char toLower(char c) {
    return std::tolower(static_cast<unsigned char>(c));
}

// Approach 1: Two Pointers (Optimized)
// - Time Complexity: O(n), where n is the length of the string
// - Space Complexity: O(1)
bool isPalindrome_twoPointers(const string& s) {
    int left = 0;
    int right = s.length() - 1;

    while (left < right) {
        // Skip non-alphanumeric characters from the left
        while (left < right && !isAlphanumeric(s[left])) {
            left++;
        }
        // Skip non-alphanumeric characters from the right
        while (left < right && !isAlphanumeric(s[right])) {
            right--;
        }
        // Compare characters (case-insensitive)
        if (toLower(s[left]) != toLower(s[right])) {
            return false;
        }
        // Move pointers
        left++;
        right--;
    }
    return true;
}

// Approach 2: Using STL reverse (Less Efficient)
// - Time Complexity: O(n), where n is the length of the filtered string.
// - Space Complexity: O(n), for the filtered string.
bool isPalindrome_stlReverse(const string& s) {
    string filtered_s;
    // Filter out non-alphanumeric characters and convert to lowercase
    for (char c : s) {
        if (isAlphanumeric(c)) {
            filtered_s += toLower(c);
        }
    }
    string reversed_s = filtered_s;
    reverse(reversed_s.begin(), reversed_s.end()); // Reverse the filtered string
    return filtered_s == reversed_s;
}

// Approach 3: Recursive Approach (Not Recommended for long strings - Stack Overflow Potential)
// - Time Complexity: O(n)
// - Space Complexity: O(n) due to recursive calls (stack space)
bool isPalindrome_recursive(const string& s, int left, int right) {
    if (left >= right) {
        return true; // Base case: empty or single character string is a palindrome
    }
    // Skip non-alphanumeric characters
    while (left < right && !isAlphanumeric(s[left])) {
        left++;
    }
    while (left < right && !isAlphanumeric(s[right])) {
        right--;
    }

    if (toLower(s[left]) != toLower(s[right])) {
        return false; // Characters don't match
    }
    return isPalindrome_recursive(s, left + 1, right - 1); // Recursive call
}

bool isPalindrome_recursive(const string& s) {
    return isPalindrome_recursive(s, 0, s.length() - 1);
}

// Approach 4: Using a Stack and a Queue (Illustrative, not optimal)
// - Time Complexity: O(n)
// - Space Complexity: O(n)
#include <stack>
#include <queue>
bool isPalindrome_stackQueue(const string& s) {
    stack<char> charStack;
    queue<char> charQueue;

    for (char c : s) {
        if (isAlphanumeric(c)) {
            char lower_c = toLower(c);
            charStack.push(lower_c);
            charQueue.push(lower_c);
        }
    }

    while (!charStack.empty() && !charQueue.empty()) {
        if (charStack.top() != charQueue.front()) {
            return false;
        }
        charStack.pop();
        charQueue.pop();
    }
    return true;
}

// Approach 5: Using std::copy_if and std::equal (Similar to STL reverse, but avoids explicit reverse)
// - Time Complexity: O(n)
// - Space Complexity: O(n)
#include <algorithm>
#include <iterator>
bool isPalindrome_copyEqual(const string& s) {
    string filtered_s;
    std::copy_if(s.begin(), s.end(), std::back_inserter(filtered_s), [](char c){ return isAlphanumeric(c); });
    std::transform(filtered_s.begin(), filtered_s.end(), filtered_s.begin(), ::tolower); // convert to lowercase
    return std::equal(filtered_s.begin(), filtered_s.end(), filtered_s.rbegin());
}

int main() {
    string testString1 = "A man, a plan, a canal: Panama";
    string testString2 = "race a car";
    string testString3 = " ";
    string testString4 = "121";
    string testString5 = "hello";
    string testString6 = "Was it a car or a cat I saw?";

    cout << "Test String 1: " << testString1 << endl;
    cout << "Two Pointers: " << (isPalindrome_twoPointers(testString1) ? "true" : "false") << endl;
    cout << "STL Reverse: " << (isPalindrome_stlReverse(testString1) ? "true" : "false") << endl;
    cout << "Recursive: " << (isPalindrome_recursive(testString1) ? "true" : "false") << endl;
    cout << "Stack and Queue: " << (isPalindrome_stackQueue(testString1) ? "true" : "false") << endl;
    cout << "Copy and Equal: " << (isPalindrome_copyEqual(testString1) ? "true" : "false") << endl;


    cout << "\nTest String 2: " << testString2 << endl;
    cout << "Two Pointers: " << (isPalindrome_twoPointers(testString2) ? "true" : "false") << endl;
    cout << "STL Reverse: " << (isPalindrome_stlReverse(testString2) ? "true" : "false") << endl;
    cout << "Recursive: " << (isPalindrome_recursive(testString2) ? "true" : "false") << endl;
    cout << "Stack and Queue: " << (isPalindrome_stackQueue(testString2) ? "true" : "false") << endl;
    cout << "Copy and Equal: " << (isPalindrome_copyEqual(testString2) ? "true" : "false") << endl;

    cout << "\nTest String 3: " << testString3 << endl;
    cout << "Two Pointers: " << (isPalindrome_twoPointers(testString3) ? "true" : "false") << endl;
    cout << "STL Reverse: " << (isPalindrome_stlReverse(testString3) ? "true" : "false") << endl;
    cout << "Recursive: " << (isPalindrome_recursive(testString3) ? "true" : "false") << endl;
    cout << "Stack and Queue: " << (isPalindrome_stackQueue(testString3) ? "true" : "false") << endl;
    cout << "Copy and Equal: " << (isPalindrome_copyEqual(testString3) ? "true" : "false") << endl;

    cout << "\nTest String 4: " << testString4 << endl;
    cout << "Two Pointers: " << (isPalindrome_twoPointers(testString4) ? "true" : "false") << endl;
    cout << "STL Reverse: " << (isPalindrome_stlReverse(testString4) ? "true" : "false") << endl;
    cout << "Recursive: " << (isPalindrome_recursive(testString4) ? "true" : "false") << endl;
    cout << "Stack and Queue: " << (isPalindrome_stackQueue(testString4) ? "true" : "false") << endl;
    cout << "Copy and Equal: " << (isPalindrome_copyEqual(testString4) ? "true" : "false") << endl;

    cout << "\nTest String 5: " << testString5 << endl;
    cout << "Two Pointers: " << (isPalindrome_twoPointers(testString5) ? "true" : "false") << endl;
    cout << "STL Reverse: " << (isPalindrome_stlReverse(testString5) ? "true" : "false") << endl;
    cout << "Recursive: " << (isPalindrome_recursive(testString5) ? "true" : "false") << endl;
    cout << "Stack and Queue: " << (isPalindrome_stackQueue(testString5) ? "true" : "false") << endl;
    cout << "Copy and Equal: " << (isPalindrome_copyEqual(testString5) ? "true" : "false") << endl;

    cout << "\nTest String 6: " << testString6 << endl;
    cout << "Two Pointers: " << (isPalindrome_twoPointers(testString6) ? "true" : "false") << endl;
    cout << "STL Reverse: " << (isPalindrome_stlReverse(testString6) ? "true" : "false") << endl;
    cout << "Recursive: " << (isPalindrome_recursive(testString6) ? "true" : "false") << endl;
    cout << "Stack and Queue: " << (isPalindrome_stackQueue(testString6) ? "true" : "false") << endl;
    cout << "Copy and Equal: " << (isPalindrome_copyEqual(testString6) ? "true" : "false") << endl;

    return 0;
}

