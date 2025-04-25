#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Function to check if two character frequency maps are equal
bool areMapsEqual(const vector<int>& s1Map, const vector<int>& s2Map) {
    for (int i = 0; i < 26; ++i) {
        if (s1Map[i] != s2Map[i]) {
            return false;
        }
    }
    return true;
}

// Approach 1: Brute Force (Naive)
// Generate all permutations of s1 and check if any of them is a substring of s2.
// This approach is very inefficient due to the factorial time complexity of generating permutations.
bool checkInclusion_BruteForce(string s1, string s2) {
    if (s1.length() > s2.length()) {
        return false;
    }

    sort(s1.begin(), s1.end()); // Sort s1 to use next_permutation

    do {
        if (s2.find(s1) != string::npos) {
            return true;
        }
    } while (next_permutation(s1.begin(), s1.end()));

    return false;
}

// Approach 2: Using Sorting (Less Efficient Sliding Window)
//  1. Create a window of size s1.length() in s2.
//  2. Sort the characters within the window.
//  3. Compare the sorted window with the sorted s1.
//  4. Slide the window and repeat.
bool checkInclusion_Sorting(string s1, string s2) {
    if (s1.length() > s2.length()) {
        return false;
    }

    sort(s1.begin(), s1.end()); // Sort s1 for comparison

    for (int i = 0; i <= s2.length() - s1.length(); ++i) {
        string window = s2.substr(i, s1.length());
        sort(window.begin(), window.end()); // Sort the window

        if (window == s1) {
            return true;
        }
    }
    return false;
}

// Approach 3: Character Frequency Counting (Sliding Window - Efficient)
// 1. Calculate the frequency of each character in s1.
// 2. Create a sliding window of size s1.length() in s2.
// 3. Maintain a character frequency count for the current window in s2.
// 4. Compare the character frequency counts of s1 and the current window.
// 5. Slide the window, updating the character frequency count.
bool checkInclusion_FrequencyCounting(string s1, string s2) {
    if (s1.length() > s2.length()) {
        return false;
    }

    vector<int> s1Map(26, 0); // Frequency map for s1
    vector<int> s2Map(26, 0); // Frequency map for the current window in s2

    // Calculate frequency of characters in s1
    for (char c : s1) {
        s1Map[c - 'a']++;
    }

    // Initialize the first window in s2
    for (int i = 0; i < s1.length(); ++i) {
        s2Map[s2[i] - 'a']++;
    }

    // Slide the window through s2
    for (int i = 0; i <= s2.length() - s1.length(); ++i) {
        if (areMapsEqual(s1Map, s2Map)) {
            return true;
        }
        if (i < s2.length() - s1.length()) {
            // Remove the character going out of the window
            s2Map[s2[i] - 'a']--;
            // Add the character entering the window
            s2Map[s2[i + s1.length()] - 'a']++;
        }
    }
    return false;
}

// Approach 4: Optimized Frequency Counting (Sliding Window - Most Efficient)
// Same as Approach 3, but optimizes the comparison.  Instead of comparing the entire frequency maps,
// it maintains a count of matched characters.
bool checkInclusion_OptimizedFrequencyCounting(string s1, string s2) {
    if (s1.length() > s2.length()) {
        return false;
    }

    vector<int> s1Map(26, 0); // Frequency map for s1
    vector<int> s2Map(26, 0); // Frequency map for the current window in s2
    int matchedCount = 0;     // Count of characters matched between s1Map and s2Map

    // Calculate frequency of characters in s1
    for (char c : s1) {
        s1Map[c - 'a']++;
    }

    // Initialize the first window in s2 and calculate initial matchedCount
    for (int i = 0; i < s1.length(); ++i) {
        s2Map[s2[i] - 'a']++;
        if (s2Map[s2[i] - 'a'] <= s1Map[s2[i] - 'a']) {
            matchedCount++;
        }
    }

    // Slide the window through s2
    for (int i = 0; i <= s2.length() - s1.length(); ++i) {
        if (matchedCount == s1.length()) {
            return true;
        }

        if (i < s2.length() - s1.length()) {
            // Remove the character going out of the window
            char charToRemove = s2[i];
            s2Map[charToRemove - 'a']--;
            if (s2Map[charToRemove - 'a'] < s1Map[charToRemove - 'a']) {
                matchedCount--;
            }

            // Add the character entering the window
            char charToAdd = s2[i + s1.length()];
            s2Map[charToAdd - 'a']++;
            if (s2Map[charToAdd - 'a'] <= s1Map[charToAdd - 'a']) {
                matchedCount++;
            }
        }
    }
    return false;
}

// Approach 5: Using Unordered Map
bool checkInclusion_UnorderedMap(string s1, string s2) {
    if (s1.length() > s2.length()) {
        return false;
    }

    unordered_map<char, int> s1Map;
    unordered_map<char, int> s2Map;

    // Calculate frequency of characters in s1
    for (char c : s1) {
        s1Map[c]++;
    }

    // Initialize the first window in s2
    for (int i = 0; i < s1.length(); ++i) {
        s2Map[s2[i]]++;
    }

    // Function to compare unordered maps
    auto compareMaps = [&](const unordered_map<char, int>& map1, const unordered_map<char, int>& map2) {
        for (const auto& pair : map1) {
            if (map2.find(pair.first) == map2.end() || map2.at(pair.first) != pair.second) {
                return false;
            }
        }
        for (const auto& pair : map2) {
             if (map1.find(pair.first) == map1.end() || map1.at(pair.first) != pair.second) {
                return false;
            }
        }
        return true;
    };

    // Slide the window
    for (int i = 0; i <= s2.length() - s1.length(); ++i) {
        if (compareMaps(s1Map, s2Map)) {
            return true;
        }

        if (i < s2.length() - s1.length()) {
            // Remove the character going out of the window
            s2Map[s2[i]]--;
            if (s2Map[s2[i]] == 0) {
                s2Map.erase(s2[i]);
            }
            // Add the character entering the window
            s2Map[s2[i + s1.length()]]++;
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
    cout << "Optimized Frequency Counting: " << (checkInclusion_OptimizedFrequencyCounting(s1, s2) ? "true" : "false") << endl;
    cout << "Unordered Map: " << (checkInclusion_UnorderedMap(s1, s2) ? "true" : "false") << endl;

    return 0;
}
