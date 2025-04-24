#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

// Function to check if two strings are anagrams of each other.
// An anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
// typically using all the original letters exactly once.

// Approach 1: Sorting
// Time Complexity: O(n log n), where n is the length of the strings.
// Space Complexity: O(1) or O(n), depending on the sorting algorithm implementation.  In-place sort may be O(1), but often a copy is made.
bool isAnagram_sorting(const string& s, const string& t) {
    // If the lengths of the strings are different, they cannot be anagrams.
    if (s.length() != t.length()) {
        return false;
    }

    // Create mutable copies of the input strings because sort() modifies the string in place.
    string sorted_s = s;
    string sorted_t = t;

    // Sort the characters in both strings.
    sort(sorted_s.begin(), sorted_s.end());
    sort(sorted_t.begin(), sorted_t.end());

    // If the sorted strings are equal, then the original strings are anagrams.
    return sorted_s == sorted_t;
}

// Approach 2: Using a vector as a frequency counter (assuming ASCII characters)
// Time Complexity: O(n), where n is the length of the strings.
// Space Complexity: O(1), because the size of the vector is fixed (256 for ASCII).
bool isAnagram_vector(const string& s, const string& t) {
    // If the lengths of the strings are different, they cannot be anagrams.
    if (s.length() != t.length()) {
        return false;
    }

    // Create a vector to store the frequency of each character (assuming ASCII characters).
    vector<int> char_counts(256, 0); // Initialize all counts to 0.

    // Iterate through the first string and increment the count for each character.
    for (char c : s) {
        char_counts[c]++;
    }

    // Iterate through the second string and decrement the count for each character.
    for (char c : t) {
        char_counts[c]--;
        if (char_counts[c] < 0) { // If a count goes negative, t has a char not in s, or too many of one char.
            return false;
        }
    }

    // If all counts are zero, the strings are anagrams.
    for (int count : char_counts) {
        if (count != 0) {
            return false;
        }
    }
    return true;
}

// Approach 3: Using an unordered_map as a frequency counter (handles Unicode)
// Time Complexity: O(n), where n is the length of the strings.
// Space Complexity: O(n), in the worst case, if all characters are distinct.
bool isAnagram_unordered_map(const string& s, const string& t) {
    // If the lengths of the strings are different, they cannot be anagrams.
    if (s.length() != t.length()) {
        return false;
    }

    // Create an unordered_map to store the frequency of each character.
    unordered_map<char, int> char_counts;

    // Iterate through the first string and increment the count for each character.
    for (char c : s) {
        char_counts[c]++;
    }

    // Iterate through the second string and decrement the count for each character.
    for (char c : t) {
        char_counts[c]--;
        if (char_counts[c] < 0) {
            return false;
        }
    }

    // If all counts are zero, the strings are anagrams.  Check that all values in the map are 0.
    for (const auto& pair : char_counts) {
        if (pair.second != 0) {
            return false;
        }
    }
    return true;
}

// Approach 4: Using a map as a frequency counter (handles Unicode, and is ordered)
// Time Complexity: O(n log n), where n is the length of the strings.  The log n factor comes from the map operations.
// Space Complexity: O(n), in the worst case.
bool isAnagram_map(const string& s, const string& t) {
    if (s.length() != t.length()) {
        return false;
    }

    map<char, int> s_char_counts;
    map<char, int> t_char_counts;

    for (char c : s) {
        s_char_counts[c]++;
    }
    for (char c : t) {
        t_char_counts[c]++;
    }

    return s_char_counts == t_char_counts;
}

// Approach 5: Optimized vector approach (more concise)
// Time Complexity: O(n)
// Space Complexity: O(1)
bool isAnagram_optimized_vector(const string& s, const string& t) {
    if (s.length() != t.length()) return false;
    vector<int> counts(26, 0); // Assuming lowercase English letters
    for (int i = 0; i < s.length(); ++i) {
        counts[s[i] - 'a']++;
        counts[t[i] - 'a']--;
    }
    for (int count : counts) {
        if (count != 0) return false;
    }
    return true;
}

int main() {
    string s1 = "listen";
    string t1 = "silent";

    string s2 = "hello";
    string t2 = "world";

    cout << "Approach 1 (Sorting):" << endl;
    cout << "s1 and t1: " << (isAnagram_sorting(s1, t1) ? "Anagrams" : "Not Anagrams") << endl; // Anagrams
    cout << "s2 and t2: " << (isAnagram_sorting(s2, t2) ? "Anagrams" : "Not Anagrams") << endl; // Not Anagrams

    cout << "\nApproach 2 (Vector):" << endl;
    cout << "s1 and t1: " << (isAnagram_vector(s1, t1) ? "Anagrams" : "Not Anagrams") << endl; // Anagrams
    cout << "s2 and t2: " << (isAnagram_vector(s2, t2) ? "Anagrams" : "Not Anagrams") << endl; // Not Anagrams

    cout << "\nApproach 3 (Unordered Map):" << endl;
    cout << "s1 and t1: " << (isAnagram_unordered_map(s1, t1) ? "Anagrams" : "Not Anagrams") << endl; // Anagrams
    cout << "s2 and t2: " << (isAnagram_unordered_map(s2, t2) ? "Anagrams" : "Not Anagrams") << endl; // Not Anagrams

    cout << "\nApproach 4 (Map):" << endl;
    cout << "s1 and t1: " << (isAnagram_map(s1, t1) ? "Anagrams" : "Not Anagrams") << endl;     // Anagrams
    cout << "s2 and t2: " << (isAnagram_map(s2, t2) ? "Anagrams" : "Not Anagrams") << endl;     // Not Anagrams

    cout << "\nApproach 5 (Optimized Vector):" << endl;
    cout << "s1 and t1: " << (isAnagram_optimized_vector(s1, t1) ? "Anagrams" : "Not Anagrams") << endl; // Anagrams
    cout << "s2 and t2: " << (isAnagram_optimized_vector(s2, t2) ? "Anagrams" : "Not Anagrams") << endl; // Not Anagrams

    return 0;
}
