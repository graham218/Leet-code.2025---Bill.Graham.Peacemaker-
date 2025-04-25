#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

// Approach 1: Basic Sliding Window (Conceptual, not always most efficient)
//   -  Good for understanding the core idea.
//   -  Not optimized for performance, may have redundant checks.
//   -  Illustrates the fundamental sliding window technique.
string minWindow_Basic(string s, string t) {
    if (s.empty() || t.empty()) return "";

    unordered_map<char, int> target_freq;
    for (char c : t) {
        target_freq[c]++;
    }

    int min_len = INT_MAX;
    int start_index = 0;
    int left = 0, right = 0;
    int matched = 0; // Count of characters matched

    unordered_map<char, int> window_freq;

    while (right < s.size()) {
        char char_right = s[right];
        window_freq[char_right]++;

        if (target_freq.find(char_right) != target_freq.end() &&
            window_freq[char_right] <= target_freq[char_right]) {
            matched++;
        }

        while (left <= right && matched == t.size()) {
            if (right - left + 1 < min_len) {
                min_len = right - left + 1;
                start_index = left;
            }

            char char_left = s[left];
            window_freq[char_left]--;

            if (target_freq.find(char_left) != target_freq.end() &&
                window_freq[char_left] < target_freq[char_left]) {
                matched--;
            }
            left++;
        }
        right++;
    }
    return (min_len == INT_MAX) ? "" : s.substr(start_index, min_len);
}

// Approach 2: Optimized Sliding Window with Early Exit
//   - Improves upon the basic approach by adding an early exit condition.
//   - If the target string 't' is longer than the source string 's', no possible window exists.
//   - Avoids unnecessary iterations, enhancing performance.
string minWindow_Optimized(string s, string t) {
    if (s.empty() || t.empty() || t.size() > s.size()) return ""; // Early exit

    unordered_map<char, int> target_freq;
    for (char c : t) target_freq[c]++;

    int min_len = INT_MAX, start_index = 0, left = 0, right = 0, matched = 0;
    unordered_map<char, int> window_freq;

    while (right < s.size()) {
        char char_right = s[right++];
        window_freq[char_right]++;

        if (target_freq.count(char_right) && window_freq[char_right] <= target_freq[char_right])
            matched++;

        while (left < right && matched == t.size()) {
            if (right - left < min_len) {
                min_len = right - left;
                start_index = left;
            }
            char char_left = s[left++];
            window_freq[char_left]--;
            if (target_freq.count(char_left) && window_freq[char_left] < target_freq[char_left])
                matched--;
        }
    }
    return min_len == INT_MAX ? "" : s.substr(start_index, min_len);
}

// Approach 3: Sliding Window with Frequency Difference Tracking
//   - Tracks the *difference* between required and found character frequencies.
//   - Uses a `diff` variable, which can be more intuitive for some.
//   - Avoids redundant checks within the inner loop.
string minWindow_FreqDiff(string s, string t) {
    if (s.empty() || t.empty()) return "";

    vector<int> freq_map(128, 0); // Assuming ASCII characters
    for (char c : t) freq_map[c]++;

    int left = 0, right = 0, min_len = INT_MAX, start_index = 0, diff = t.size();

    while (right < s.size()) {
        if (freq_map[s[right++]]-- > 0) diff--; // Important: decrement first

        while (diff == 0) {
            if (right - left < min_len) {
                min_len = right - left;
                start_index = left;
            }
            if (++freq_map[s[left++]] > 0) diff++; // Increment and check
        }
    }
    return min_len == INT_MAX ? "" : s.substr(start_index, min_len);
}

// Approach 4: Template-Based Sliding Window
//   - Encapsulates the sliding window logic into a template function.
//   - Makes the code more reusable and adaptable to similar problems.
//   - Demonstrates generic programming principles.
template <typename F>
string minWindow_Template(string s, string t, F condition) {
    if (s.empty() || t.empty()) return "";

    unordered_map<char, int> target_freq;
    for (char c : t) target_freq[c]++;

    int left = 0, right = 0, min_len = INT_MAX, start_index = 0;
    unordered_map<char, int> window_freq;
    int matched = 0;

    while (right < s.size()) {
        char char_right = s[right];
        window_freq[char_right]++;

        if (target_freq.find(char_right) != target_freq.end() &&
            window_freq[char_right] <= target_freq[char_right]) {
            matched++;
        }

        while (left <= right && condition(matched, t.size(), window_freq, target_freq)) {
            if (right - left + 1 < min_len) {
                min_len = right - left + 1;
                start_index = left;
            }
            char char_left = s[left];
            window_freq[char_left]--;
            if (target_freq.find(char_left) != target_freq.end() &&
                window_freq[char_left] < target_freq[char_left]) {
                matched--;
            }
            left++;
        }
        right++;
    }
    return (min_len == INT_MAX) ? "" : s.substr(start_index, min_len);
}

// Approach 5: Sliding Window with Optimized Map Operations
//   - Uses a more efficient approach to update the window frequency map.
//   - Reduces the number of map operations, leading to better performance.
//   - Suitable for very large input strings.
string minWindow_OptimizedMap(string s, string t) {
    if (s.empty() || t.empty()) return "";

    unordered_map<char, int> target_freq;
    for (char c : t) target_freq[c]++;

    int left = 0, right = 0, min_len = INT_MAX, start_index = 0, matched = 0;
    unordered_map<char, int> window_freq;

    while (right < s.size()) {
        char c = s[right++];
        if (target_freq.find(c) != target_freq.end()) {
            window_freq[c]++;
            if (window_freq[c] == target_freq[c]) { // Key optimization: Check for equality
                matched++;
            }
        }

        while (left < right && matched == target_freq.size()) {
            if (right - left < min_len) {
                min_len = right - left;
                start_index = left;
            }
            char d = s[left++];
            if (target_freq.find(d) != target_freq.end()) {
                window_freq[d]--;
                if (window_freq[d] < target_freq[d]) { // Key optimization: Check against target
                    matched--;
                }
            }
        }
    }
    return min_len == INT_MAX ? "" : s.substr(start_index, min_len);
}

int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";

    cout << "String s: " << s << endl;
    cout << "String t: " << t << endl << endl;

    cout << "Minimum Window (Basic): " << minWindow_Basic(s, t) << endl;
    cout << "Minimum Window (Optimized): " << minWindow_Optimized(s, t) << endl;
    cout << "Minimum Window (Freq Diff): " << minWindow_FreqDiff(s, t) << endl;

    // Using the template function:
    auto condition = [&](int matched, int target_size, const unordered_map<char, int>& window_freq, const unordered_map<char, int>& target_freq) {
        return matched == target_size;
    };
    cout << "Minimum Window (Template): " << minWindow_Template(s, t, condition) << endl;

    cout << "Minimum Window (Optimized Map): " << minWindow_OptimizedMap(s, t) << endl;

    return 0;
}

