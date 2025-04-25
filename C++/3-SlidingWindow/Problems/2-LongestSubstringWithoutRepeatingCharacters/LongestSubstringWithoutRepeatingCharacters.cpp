#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <unordered_set> // Include the header for unordered_set

using namespace std;

// Function to find the length of the longest substring without repeating characters using the Brute Force approach.
// Time Complexity: O(n^3), Space Complexity: O(min(n, m)) where n is the length of the string and m is the size of the character set.
int longestUniqueSubstrBruteForce(const string& str) {
    int n = str.length();
    int longestLength = 0;

    // Iterate through all possible starting positions of substrings.
    for (int i = 0; i < n; i++) {
        // Iterate through all possible ending positions of substrings.
        for (int j = i; j < n; j++) {
            // Check if the substring from i to j has all unique characters.
            vector<bool> visited(256, false); // Assume ASCII character set

            bool unique = true;
            for (int k = i; k <= j; k++) {
                if (visited[str[k]]) {
                    unique = false;
                    break;
                }
                visited[str[k]] = true;
            }

            // If the substring has all unique characters, update the longest length.
            if (unique) {
                longestLength = max(longestLength, j - i + 1);
            }
        }
    }
    return longestLength;
}

// Function to find the length of the longest substring without repeating characters using the Sliding Window approach with a set.
// Time Complexity: O(n), Space Complexity: O(min(n, m))
int longestUniqueSubstrSlidingWindowSet(const string& str) {
    int n = str.length();
    int longestLength = 0;
    int left = 0, right = 0;
    unordered_set<char> charSet;

    while (right < n) {
        if (charSet.find(str[right]) == charSet.end()) {
            // If the character is not in the set, add it and move the right pointer.
            charSet.insert(str[right]);
            right++;
            longestLength = max(longestLength, (int)charSet.size());
        } else {
            // If the character is already in the set, remove the leftmost character and move the left pointer.
            charSet.erase(str[left]);
            left++;
        }
    }
    return longestLength;
}

// Function to find the length of the longest substring without repeating characters using the Sliding Window approach with a map.
// Time Complexity: O(n), Space Complexity: O(min(n, m))
int longestUniqueSubstrSlidingWindowMap(const string& str) {
    int n = str.length();
    int longestLength = 0;
    int left = 0, right = 0;
    unordered_map<char, int> charMap; // Stores character and its last seen index

    while (right < n) {
        if (charMap.find(str[right]) == charMap.end() || charMap[str[right]] < left) {
            // If the character is not in the map or its last seen index is before the current window,
            // add it to the map with its current index and move the right pointer.
            charMap[str[right]] = right;
            right++;
            longestLength = max(longestLength, right - left);
        } else {
            // If the character is in the map and its last seen index is within the current window,
            // move the left pointer to just after the last seen index of the repeating character.
            left = charMap[str[right]] + 1;
            charMap[str[right]] = right; // Update the last seen index
            right++;
        }
    }
    return longestLength;
}

// Function to find the length of the longest substring without repeating characters using the Optimized Sliding Window approach with a vector.
// Time Complexity: O(n), Space Complexity: O(m) where m is the size of the character set (e.g., 256 for ASCII).
int longestUniqueSubstrOptimized(const string& str) {
    int n = str.length();
    int longestLength = 0;
    int left = 0, right = 0;
    vector<int> charIndex(256, -1); // Stores the last seen index of each character, initialized to -1

    while (right < n) {
        if (charIndex[str[right]] == -1 || charIndex[str[right]] < left) {
            // If the character has not been seen or its last seen index is outside the current window
            charIndex[str[right]] = right; // Update last seen index
            right++; // Expand window
            longestLength = max(longestLength, right - left); // Calculate and store max length
        } else {
            // If the character is repeated within the window
            left = charIndex[str[right]] + 1; // Shrink window to exclude the repeated char
            charIndex[str[right]] = right;    // Update last seen index
            right++;
        }
    }
    return longestLength;
}

// Another optimized approach using only a vector
int longestUniqueSubstrVector(const string& str) {
    int n = str.length();
    if (n <= 1) return n;

    vector<int> lastIndex(256, -1); // Initialize a vector to store the last seen index of each character
    int maxLength = 0;
    int start = 0;

    for (int i = 0; i < n; ++i) {
        unsigned char currentChar = str[i]; // Use unsigned char to handle ASCII values correctly
        if (lastIndex[currentChar] != -1 && lastIndex[currentChar] >= start) {
            start = lastIndex[currentChar] + 1; // Move the start of the window
        }
        lastIndex[currentChar] = i; // Update the last seen index
        maxLength = max(maxLength, i - start + 1); // Calculate the maximum length
    }
    return maxLength;
}

int main() {
    string str = "abcabcbb";
    cout << "String: " << str << endl;

    cout << "\nBrute Force Approach: Length of longest unique substring: " << longestUniqueSubstrBruteForce(str) << endl;
    cout << "Sliding Window with Set: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowSet(str) << endl;
    cout << "Sliding Window with Map: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowMap(str) << endl;
    cout << "Optimized Sliding Window: Length of longest unique substring: " << longestUniqueSubstrOptimized(str) << endl;
    cout << "Optimized Sliding Window with Vector: Length of longest unique substring: " << longestUniqueSubstrVector(str) << endl;

    string str2 = "bbbbb";
    cout << "\nString: " << str2 << endl;
    cout << "\nBrute Force Approach: Length of longest unique substring: " << longestUniqueSubstrBruteForce(str2) << endl;
    cout << "Sliding Window with Set: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowSet(str2) << endl;
    cout << "Sliding Window with Map: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowMap(str2) << endl;
    cout << "Optimized Sliding Window: Length of longest unique substring: " << longestUniqueSubstrOptimized(str2) << endl;
    cout << "Optimized Sliding Window with Vector: Length of longest unique substring: " << longestUniqueSubstrVector(str2) << endl;

    string str3 = "pwwkew";
    cout << "\nString: " << str3 << endl;
    cout << "\nBrute Force Approach: Length of longest unique substring: " << longestUniqueSubstrBruteForce(str3) << endl;
    cout << "Sliding Window with Set: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowSet(str3) << endl;
    cout << "Sliding Window with Map: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowMap(str3) << endl;
    cout << "Optimized Sliding Window: Length of longest unique substring: " << longestUniqueSubstrOptimized(str3) << endl;
    cout << "Optimized Sliding Window with Vector: Length of longest unique substring: " << longestUniqueSubstrVector(str3) << endl;

    string str4 = "";
    cout << "\nString: " << str4 << endl;
    cout << "\nBrute Force Approach: Length of longest unique substring: " << longestUniqueSubstrBruteForce(str4) << endl;
    cout << "Sliding Window with Set: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowSet(str4) << endl;
    cout << "Sliding Window with Map: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowMap(str4) << endl;
    cout << "Optimized Sliding Window: Length of longest unique substring: " << longestUniqueSubstrOptimized(str4) << endl;
    cout << "Optimized Sliding Window with Vector: Length of longest unique substring: " << longestUniqueSubstrVector(str4) << endl;

    string str5 = "abcdefg";
    cout << "\nString: " << str5 << endl;
    cout << "\nBrute Force Approach: Length of longest unique substring: " << longestUniqueSubstrBruteForce(str5) << endl;
    cout << "Sliding Window with Set: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowSet(str5) << endl;
    cout << "Sliding Window with Map: Length of longest unique substring: " << longestUniqueSubstrSlidingWindowMap(str5) << endl;
    cout << "Optimized Sliding Window: Length of longest unique substring: " << longestUniqueSubstrOptimized(str5) << endl;
    cout << "Optimized Sliding Window with Vector: Length of longest unique substring: " << longestUniqueSubstrVector(str5) << endl;

    return 0;
}

