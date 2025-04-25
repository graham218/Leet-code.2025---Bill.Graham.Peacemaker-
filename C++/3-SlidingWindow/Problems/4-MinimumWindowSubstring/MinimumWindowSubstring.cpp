#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Function to check if windowCount has all the characters of t with their required frequencies
bool hasAllChars(const unordered_map<char, int>& windowCount, const unordered_map<char, int>& tCount) {
    for (const auto& pair : tCount) {
        if (windowCount.find(pair.first) == windowCount.end() || windowCount.at(pair.first) < pair.second) {
            return false;
        }
    }
    return true;
}

// Approach 1: Brute Force
// Generate all possible substrings of s and check if they contain t.
// Time Complexity: O(n^3), where n is the length of s.
// Space Complexity: O(m), where m is the length of t.
string minWindow_BruteForce(string s, string t) {
    if (s.empty() || t.empty() || t.length() > s.length()) {
        return "";
    }

    int minLength = INT_MAX;
    string minWindow = "";
    unordered_map<char, int> tCount;

    // Count frequency of characters in t
    for (char c : t) {
        tCount[c]++;
    }

    // Generate all substrings of s
    for (int i = 0; i < s.length(); i++) {
        for (int j = i; j < s.length(); j++) {
            string sub = s.substr(i, j - i + 1);
            unordered_map<char, int> subCount;

            // Count frequency of characters in the substring
            for (char c : sub) {
                subCount[c]++;
            }

            // Check if the substring contains all characters of t
            if (hasAllChars(subCount, tCount)) {
                if (sub.length() < minLength) {
                    minLength = sub.length();
                    minWindow = sub;
                }
            }
        }
    }
    return minWindow;
}

// Approach 2: Optimized Brute Force
// Slightly optimized version of brute force, avoiding redundant substring creation.
// Time Complexity: O(n^2 * m), where n is the length of s, and m is the length of t.
// Space Complexity: O(m)
string minWindow_OptimizedBruteForce(string s, string t) {
    if (s.empty() || t.empty() || t.length() > s.length()) {
        return "";
    }

    int minLength = INT_MAX;
    string minWindow = "";
    unordered_map<char, int> tCount;

    for (char c : t) {
        tCount[c]++;
    }

    for (int i = 0; i < s.length(); ++i) {
        unordered_map<char, int> windowCount;
        for (int j = i; j < s.length(); ++j) {
            windowCount[s[j]]++;
            if (hasAllChars(windowCount, tCount)) {
                string sub = s.substr(i, j - i + 1);
                if (sub.length() < minLength) {
                    minLength = sub.length();
                    minWindow = sub;
                }
                break; // Important optimization: Once a valid window is found, no need to check further
            }
        }
    }
    return minWindow;
}

// Approach 3: Sliding Window with Hash Map
// Uses a sliding window and a hash map to efficiently track character frequencies.
// Time Complexity: O(n), where n is the length of s.
// Space Complexity: O(m), where m is the length of t.
string minWindow_SlidingWindow(string s, string t) {
    if (s.empty() || t.empty() || t.length() > s.length()) {
        return "";
    }

    unordered_map<char, int> tCount;
    unordered_map<char, int> windowCount;
    int minLength = INT_MAX;
    string minWindow = "";
    int left = 0;
    int right = 0;
    int matched = 0; // Count of characters matched

    // Count frequency of characters in t
    for (char c : t) {
        tCount[c]++;
    }

    // Expand the window
    while (right < s.length()) {
        char c = s[right];
        if (tCount.find(c) != tCount.end()) {
            windowCount[c]++;
            if (windowCount[c] == tCount[c]) {
                matched++;
            }
        }
        right++;

        // Shrink the window
        while (matched == tCount.size()) {
            if (right - left < minLength) {
                minLength = right - left;
                minWindow = s.substr(left, right - left);
            }
            char leftChar = s[left];
            if (tCount.find(leftChar) != tCount.end()) {
                windowCount[leftChar]--;
                if (windowCount[leftChar] < tCount[leftChar]) {
                    matched--;
                }
            }
            left++;
        }
    }
    return minWindow;
}

// Approach 4: Sliding Window with Optimized Hash Map
// Further optimization of the sliding window approach.
// Time Complexity: O(n), where n is the length of s.
// Space Complexity: O(m), where m is the length of t.
string minWindow_OptimizedSlidingWindow(string s, string t) {
    if (s.empty() || t.empty() || t.length() > s.length()) {
        return "";
    }

    vector<int> tFreq(128, 0); // Assuming ASCII characters
    vector<int> windowFreq(128, 0);
    int requiredChars = 0;
    int matchedChars = 0;
    int minLength = INT_MAX;
    int minStart = 0;

    for (char c : t) {
        tFreq[c]++;
        if (tFreq[c] == 1) { // Count distinct characters in t
            requiredChars++;
        }
    }

    int left = 0;
    for (int right = 0; right < s.length(); ++right) {
        char c = s[right];
        windowFreq[c]++;
        if (windowFreq[c] == tFreq[c]) {
            matchedChars++;
        }

        while (matchedChars == requiredChars) {
            if (right - left + 1 < minLength) {
                minLength = right - left + 1;
                minStart = left;
            }
            char leftChar = s[left];
            windowFreq[leftChar]--;
            if (windowFreq[leftChar] < tFreq[leftChar]) {
                matchedChars--;
            }
            left++;
        }
    }
    return (minLength == INT_MAX) ? "" : s.substr(minStart, minLength);
}

// Approach 5: Using two pointers and a counter
// Time Complexity: O(n)
// Space Complexity: O(m)
string minWindow_TwoPointers(string s, string t) {
    if (s.empty() || t.empty() || t.length() > s.length()) return "";

    vector<int> tFreq(128, 0);
    int requiredChars = 0;
    for (char c : t) {
        tFreq[c]++;
        requiredChars++;
    }

    int left = 0, right = 0, formedChars = 0, minLength = INT_MAX, minLeft = 0;
    vector<int> windowFreq(128, 0);

    while (right < s.length()) {
        char c = s[right];
        if (tFreq[c] > 0) {
            windowFreq[c]++;
            if (windowFreq[c] <= tFreq[c]) {
                formedChars++;
            }
        }

        while (left <= right && formedChars == requiredChars) {
            if (right - left + 1 < minLength) {
                minLength = right - left + 1;
                minLeft = left;
            }

            char leftChar = s[left];
            if (tFreq[leftChar] > 0) {
                windowFreq[leftChar]--;
                if (windowFreq[leftChar] < tFreq[leftChar]) {
                    formedChars--;
                }
            }
            left++;
        }
        right++;
    }
    return (minLength == INT_MAX) ? "" : s.substr(minLeft, minLength);
}

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";

    cout << "String s: " << s << endl;
    cout << "String t: " << t << endl << endl;

    cout << "Minimum Window (Brute Force): " << minWindow_BruteForce(s, t) << endl;
    cout << "Minimum Window (Optimized Brute Force): " << minWindow_OptimizedBruteForce(s, t) << endl;
    cout << "Minimum Window (Sliding Window): " << minWindow_SlidingWindow(s, t) << endl;
    cout << "Minimum Window (Optimized Sliding Window): " << minWindow_OptimizedSlidingWindow(s, t) << endl;
    cout << "Minimum Window (Two Pointers): " << minWindow_TwoPointers(s, t) << endl;

    return 0;
}

