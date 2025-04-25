#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Function to check if two frequency vectors are equal
bool areFrequenciesEqual(const vector<int>& freq1, const vector<int>& freq2) {
    for (int i = 0; i < 26; ++i) {
        if (freq1[i] != freq2[i]) {
            return false;
        }
    }
    return true;
}

// Approach 1: Brute Force (Naive)
// Generate all permutations of s1 and check if any of them is a substring of s2.
// This approach is extremely inefficient, especially for larger strings.
bool checkInclusion_BruteForce(string s1, string s2) {
    if (s1.length() > s2.length()) {
        return false;
    }

    sort(s1.begin(), s1.end()); // Sort s1 once.

    do {
        if (s2.find(s1) != string::npos) {
            return true;
        }
    } while (next_permutation(s1.begin(), s1.end())); // Iterate through permutations.
    return false;
}

// Approach 2: Using Sorting (Optimized Sliding Window)
// A more optimized sliding window approach.  It maintains a window of size s1.length() in s2,
// sorts the characters in the window, and compares the sorted window with the sorted s1.
bool checkInclusion_Sorting(string s1, string s2) {
    if (s1.length() > s2.length()) {
        return false;
    }

    string sortedS1 = s1;
    sort(sortedS1.begin(), sortedS1.end()); // Sort s1

    for (int i = 0; i <= s2.length() - s1.length(); ++i) {
        string sub = s2.substr(i, s1.length()); // Extract substring.
        sort(sub.begin(), sub.end());           // Sort the substring.
        if (sub == sortedS1) {
            return true;
        }
    }
    return false;
}

// Approach 3: Character Frequency Counting (Sliding Window - Efficient)
// This is the most efficient sliding window approach.  It uses frequency arrays
// to track the character counts in s1 and the current window of s2.
bool checkInclusion_FrequencyCounting(string s1, string s2) {
    if (s1.length() > s2.length()) {
        return false;
    }

    vector<int> s1Freq(26, 0); // Frequency of characters in s1
    vector<int> s2Freq(26, 0); // Frequency of characters in the current window of s2

    // Calculate frequency of characters in s1
    for (char c : s1) {
        s1Freq[c - 'a']++;
    }

    // Initial frequency count for the first window in s2
    for (int i = 0; i < s1.length(); ++i) {
        s2Freq[s2[i] - 'a']++;
    }

    // Slide the window through s2
    for (int i = 0; i <= s2.length() - s1.length(); ++i) {
        if (areFrequenciesEqual(s1Freq, s2Freq)) {
            return true;
        }
        if (i < s2.length() - s1.length()) { // Important boundary check
            s2Freq[s2[i] - 'a']--;             // Remove the leftmost character
            s2Freq[s2[i + s1.length()] - 'a']++; // Add the rightmost character
        }
    }
    return false;
}

// Approach 4: Using unordered_map (Sliding Window)
// Uses a hash map to store the frequencies of characters.  Slightly less efficient
// than the vector approach in C++, but more flexible for larger character sets.
bool checkInclusion_HashMap(string s1, string s2) {
    if (s1.length() > s2.length()) return false;

    unordered_map<char, int> s1Map;
    unordered_map<char, int> s2Map;

    // Build frequency map for s1
    for (char c : s1) {
        s1Map[c]++;
    }

    // Initial frequency map for the first window in s2
    for (int i = 0; i < s1.length(); i++) {
        s2Map[s2[i]]++;
    }

    for (int i = 0; i <= s2.length() - s1.length(); i++) {
        if (s1Map == s2Map) return true;
        if (i < s2.length() - s1.length()) {
            s2Map[s2[i]]--;
            if (s2Map[s2[i]] == 0) {
                s2Map.erase(s2[i]); // Clean up the map.
            }
            s2Map[s2[i + s1.length()]]++;
        }
    }
    return false;
}

// Approach 5: Optimized Frequency Counting with Early Exit
// Further optimization of approach 3. Instead of comparing the entire frequency arrays,
// it maintains a 'count' of matched characters. If 'count' equals s1.length(), a permutation is found.
bool checkInclusion_OptimizedCounting(string s1, string s2) {
    if (s1.length() > s2.length()) return false;

    vector<int> s1Freq(26, 0);
    vector<int> s2Freq(26, 0);
    int matchedCount = 0; // Count of matched characters

    for (char c : s1) s1Freq[c - 'a']++;

    for (int i = 0; i < s1.length(); i++) {
        s2Freq[s2[i] - 'a']++;
        if (s2Freq[s2[i] - 'a'] <= s1Freq[s2[i] - 'a']) {
            matchedCount++;
        }
    }

    for (int i = 0; i <= s2.length() - s1.length(); i++) {
        if (matchedCount == s1.length()) return true;

        if (i < s2.length() - s1.length()) {
            int leftChar = s2[i] - 'a';
            int rightChar = s2[i + s1.length()] - 'a';

            s2Freq[leftChar]--;
            if (s2Freq[leftChar] < s1Freq[leftChar]) {
                matchedCount--;
            }

            s2Freq[rightChar]++;
            if (s2Freq[rightChar] <= s1Freq[rightChar]) {
                matchedCount++;
            }
        }
    }
    return false;
}

int main() {
    string s1 = "ab";
    string s2 = "eidbaooo";

    cout << "String s1: " << s1 << ", String s2: " << s2 << endl;

    cout << "Brute Force: " << (checkInclusion_BruteForce(s1, s2) ? "true" : "false") << endl;
    cout << "Sorting: " << (checkInclusion_Sorting(s1, s2) ? "true" : "false") << endl;
    cout << "Frequency Counting: " << (checkInclusion_FrequencyCounting(s1, s2) ? "true" : "false") << endl;
    cout << "Hash Map: " << (checkInclusion_HashMap(s1, s2) ? "true" : "false") << endl;
    cout << "Optimized Counting: " << (checkInclusion_OptimizedCounting(s1, s2) ? "true" : "false") << endl;

    return 0;
}
