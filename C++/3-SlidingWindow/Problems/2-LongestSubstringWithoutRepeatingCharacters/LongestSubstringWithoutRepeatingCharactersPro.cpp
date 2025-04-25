#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <unordered_set> // Include the unordered_set header

using namespace std;

// Function to find the length of the longest substring without repeating characters using the Sliding Window approach.
// This is the most common and efficient approach.
int longestUniqueSubstring_SlidingWindow(const string& s) {
    if (s.empty()) {
        return 0;
    }

    int maxLength = 0;
    int start = 0;
    unordered_map<char, int> charIndexMap; // Map to store the most recent index of each character

    for (int end = 0; end < s.length(); ++end) {
        char currentChar = s[end];
        // If the character is already in the map and its last seen index is greater than or equal to the start index,
        // move the start pointer to the next position after the last occurrence of the character.
        if (charIndexMap.find(currentChar) != charIndexMap.end() && charIndexMap[currentChar] >= start) {
            start = charIndexMap[currentChar] + 1;
        }
        charIndexMap[currentChar] = end; // Update the last seen index of the character.
        maxLength = max(maxLength, end - start + 1); // Calculate the current substring length and update maxLength.
    }
    return maxLength;
}

// Function to find the length of the longest substring without repeating characters using a Brute Force approach.
// This approach has a time complexity of O(n^3), which is less efficient for large strings.
int longestUniqueSubstring_BruteForce(const string& s) {
    if (s.empty()) {
        return 0;
    }

    int maxLength = 0;
    for (int i = 0; i < s.length(); ++i) {
        for (int j = i; j < s.length(); ++j) {
            // Check if the substring from i to j has repeating characters.
            bool hasRepeatingChars = false;
            unordered_map<char, bool> charSet;
            for (int k = i; k <= j; ++k) {
                if (charSet[s[k]]) {
                    hasRepeatingChars = true;
                    break;
                }
                charSet[s[k]] = true;
            }
            if (!hasRepeatingChars) {
                maxLength = max(maxLength, j - i + 1);
            }
        }
    }
    return maxLength;
}

// Function to find the length of the longest substring without repeating characters using a Modified Brute Force approach.
// This approach optimizes the Brute Force approach by checking for repeating characters as we go.
int longestUniqueSubstring_ModifiedBruteForce(const string& s) {
    if (s.empty()) {
        return 0;
    }

    int maxLength = 0;
    for (int i = 0; i < s.length(); ++i) {
        unordered_map<char, bool> charSet;
        int currentLength = 0;
        for (int j = i; j < s.length(); ++j) {
            if (charSet[s[j]]) {
                break; // Exit inner loop if a repeating character is found
            }
            charSet[s[j]] = true;
            currentLength++;
            maxLength = max(maxLength, currentLength);
        }
    }
    return maxLength;
}

// Function to find the length of the longest substring without repeating characters using a Sliding Window with a Set.
// This approach uses a set to keep track of characters in the current window.
int longestUniqueSubstring_SlidingWindowSet(const string& s) {
    if (s.empty()) {
        return 0;
    }

    int maxLength = 0;
    int start = 0;
    unordered_set<char> charSet; // Set to store characters in the current window

    for (int end = 0; end < s.length(); ++end) {
        char currentChar = s[end];
        while (charSet.find(currentChar) != charSet.end()) {
            // If the character is already in the set, remove characters from the start of the window
            // until the repeating character is removed.
            charSet.erase(s[start]);
            start++;
        }
        charSet.insert(currentChar); // Add the current character to the set
        maxLength = max(maxLength, end - start + 1); // Update the maximum length
    }
    return maxLength;
}

// Function to find the length of the longest substring without repeating characters using a Vector as a character map.
//  This approach assumes ASCII characters and uses a vector as a more space-efficient character map.
int longestUniqueSubstring_SlidingWindowVector(const string& s) {
    if (s.empty()) {
        return 0;
    }

    int maxLength = 0;
    int start = 0;
    vector<int> charIndexMap(256, -1); // Vector to store the last seen index of each character (assuming ASCII)

    for (int end = 0; end < s.length(); ++end) {
        char currentChar = s[end];
        if (charIndexMap[currentChar] != -1 && charIndexMap[currentChar] >= start) {
            start = charIndexMap[currentChar] + 1;
        }
        charIndexMap[currentChar] = end;
        maxLength = max(maxLength, end - start + 1);
    }
    return maxLength;
}

int main() {
    string testString = "abcabcbb";
    cout << "String: " << testString << endl;

    cout << "Longest Substring (Sliding Window): " << longestUniqueSubstring_SlidingWindow(testString) << endl;
    cout << "Longest Substring (Brute Force): " << longestUniqueSubstring_BruteForce(testString) << endl;
    cout << "Longest Substring (Modified Brute Force): " << longestUniqueSubstring_ModifiedBruteForce(testString) << endl;
    cout << "Longest Substring (Sliding Window with Set): " << longestUniqueSubstring_SlidingWindowSet(testString) << endl;
    cout << "Longest Substring (Sliding Window with Vector): " << longestUniqueSubstring_SlidingWindowVector(testString) << endl;

    testString = "bbbbb";
    cout << "\nString: " << testString << endl;
    cout << "Longest Substring (Sliding Window): " << longestUniqueSubstring_SlidingWindow(testString) << endl;
    cout << "Longest Substring (Brute Force): " << longestUniqueSubstring_BruteForce(testString) << endl;
    cout << "Longest Substring (Modified Brute Force): " << longestUniqueSubstring_ModifiedBruteForce(testString) << endl;
    cout << "Longest Substring (Sliding Window with Set): " << longestUniqueSubstring_SlidingWindowSet(testString) << endl;
    cout << "Longest Substring (Sliding Window with Vector): " << longestUniqueSubstring_SlidingWindowVector(testString) << endl;

    testString = "pwwkew";
    cout << "\nString: " << testString << endl;
    cout << "Longest Substring (Sliding Window): " << longestUniqueSubstring_SlidingWindow(testString) << endl;
    cout << "Longest Substring (Brute Force): " << longestUniqueSubstring_BruteForce(testString) << endl;
    cout << "Longest Substring (Modified Brute Force): " << longestUniqueSubstring_ModifiedBruteForce(testString) << endl;
    cout << "Longest Substring (Sliding Window with Set): " << longestUniqueSubstring_SlidingWindowSet(testString) << endl;
    cout << "Longest Substring (Sliding Window with Vector): " << longestUniqueSubstring_SlidingWindowVector(testString) << endl;

    testString = "";
    cout << "\nString: " << testString << endl;
    cout << "Longest Substring (Sliding Window): " << longestUniqueSubstring_SlidingWindow(testString) << endl;
    cout << "Longest Substring (Brute Force): " << longestUniqueSubstring_BruteForce(testString) << endl;
    cout << "Longest Substring (Modified Brute Force): " << longestUniqueSubstring_ModifiedBruteForce(testString) << endl;
    cout << "Longest Substring (Sliding Window with Set): " << longestUniqueSubstring_SlidingWindowSet(testString) << endl;
    cout << "Longest Substring (Sliding Window with Vector): " << longestUniqueSubstring_SlidingWindowVector(testString) << endl;

    testString = "dvdf";
    cout << "\nString: " << testString << endl;
    cout << "Longest Substring (Sliding Window): " << longestUniqueSubstring_SlidingWindow(testString) << endl;
    cout << "Longest Substring (Brute Force): " << longestUniqueSubstring_BruteForce(testString) << endl;
    cout << "Longest Substring (Modified Brute Force): " << longestUniqueSubstring_ModifiedBruteForce(testString) << endl;
    cout << "Longest Substring (Sliding Window with Set): " << longestUniqueSubstring_SlidingWindowSet(testString) << endl;
    cout << "Longest Substring (Sliding Window with Vector): " << longestUniqueSubstring_SlidingWindowVector(testString) << endl;

    return 0;
}

