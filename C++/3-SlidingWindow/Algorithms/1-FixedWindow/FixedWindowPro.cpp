#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <unordered_map>
#include <queue>

using namespace std;

// 1. Maximum Sum Subarray of Fixed Size K
// Real-world application: Analyzing stock prices for a specific period (e.g., finding the highest average stock price over a 7-day window).
int maxSumSubarray(const vector<int>& arr, int k) {
    if (arr.size() < k) {
        return -1; // Handle invalid input: window size larger than array size
    }

    int max_sum = 0;
    int window_sum = 0;

    // Calculate the sum of the first window
    for (int i = 0; i < k; ++i) {
        window_sum += arr[i];
    }
    max_sum = window_sum; // Initialize max_sum

    // Slide the window through the rest of the array
    for (int i = k; i < arr.size(); ++i) {
        window_sum += arr[i] - arr[i - k]; // Subtract the outgoing element, add the incoming
        max_sum = max(max_sum, window_sum); // Update max_sum if necessary
    }

    return max_sum;
}

// 2. Minimum Window Substring
// Real-world application: Text processing, finding the smallest snippet of text containing all keywords.
string minWindowSubstring(const string& s, const string& t) {
    if (t.empty() || s.empty() || t.size() > s.size()) {
        return ""; // Handle edge cases
    }

    unordered_map<char, int> target_freq; // Frequency of characters in t
    for (char c : t) {
        target_freq[c]++;
    }

    int required_chars = target_freq.size(); // Number of unique characters in t
    int formed_chars = 0; // Number of unique characters in s that meet the required frequency
    unordered_map<char, int> window_freq; // Frequency of characters in the current window

    int min_length = numeric_limits<int>::max();
    int start = 0;
    int min_start = 0;

    int left = 0;
    for (int right = 0; right < s.size(); ++right) {
        char current_char = s[right];
        window_freq[current_char]++;

        if (target_freq.find(current_char) != target_freq.end() &&
            window_freq[current_char] == target_freq[current_char]) {
            formed_chars++;
        }

        while (left <= right && formed_chars == required_chars) {
            if (right - left + 1 < min_length) {
                min_length = right - left + 1;
                min_start = left;
            }

            char left_char = s[left];
            window_freq[left_char]--;

            if (target_freq.find(left_char) != target_freq.end() &&
                window_freq[left_char] < target_freq[left_char]) {
                formed_chars--;
            }
            left++;
        }
    }

    return min_length == numeric_limits<int>::max() ? "" : s.substr(min_start, min_length);
}

// 3. Longest Substring Without Repeating Characters
// Real-world application: Data compression, finding the longest non-repeating sequence for efficient encoding.
int longestSubstringWithoutRepeatingChars(const string& s) {
    if (s.empty()) return 0;

    int max_length = 0;
    unordered_map<char, int> char_index; // Stores the last seen index of each character
    int start = 0;

    for (int end = 0; end < s.size(); ++end) {
        char current_char = s[end];
        if (char_index.find(current_char) != char_index.end() && char_index[current_char] >= start) {
            start = char_index[current_char] + 1; // Move start to the next position after the repeated char
        }
        char_index[current_char] = end; // Update the last seen index
        max_length = max(max_length, end - start + 1);
    }
    return max_length;
}

// 4. Counting Anagrams
// Real-world application: Bioinformatics, finding occurrences of a specific gene sequence (anagram) within a larger DNA strand.
int countAnagrams(const string& text, const string& pattern) {
    if (pattern.size() > text.size()) {
        return 0; // Pattern cannot be an anagram if it's longer than the text
    }

    unordered_map<char, int> pattern_freq;
    for (char c : pattern) {
        pattern_freq[c]++;
    }

    int required_chars = pattern_freq.size();
    int formed_chars = 0;
    unordered_map<char, int> window_freq;
    int count = 0;

    int left = 0;
    for (int right = 0; right < text.size(); ++right) {
        char current_char = text[right];
        window_freq[current_char]++;

        if (pattern_freq.find(current_char) != pattern_freq.end() &&
            window_freq[current_char] == pattern_freq[current_char]) {
            formed_chars++;
        }

        if (right - left + 1 == pattern.size()) { // Window size equals pattern size
            if (formed_chars == required_chars) {
                count++;
            }
            char left_char = text[left];
            window_freq[left_char]--;
             if (pattern_freq.find(left_char) != pattern_freq.end() &&
                window_freq[left_char] < pattern_freq[left_char]) {
                formed_chars--;
            }
            left++;
        }
    }
    return count;
}

// 5.  Sliding Window Maximum
// Real-world application: Real-time data analysis, finding the maximum value in a stream of data within a fixed time window.
vector<int> slidingWindowMaximum(const vector<int>& nums, int k) {
    vector<int> result;
    if (nums.empty() || k <= 0) return result;

    deque<int> dq; // Stores indices, not values
    for (int i = 0; i < nums.size(); ++i) {
        // Remove elements out of the current window
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        // Remove smaller elements from the back
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i); // Add the current element's index
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]); // The front of dq is always the maximum
        }
    }
    return result;
}

int main() {
    // 1. Maximum Sum Subarray
    vector<int> arr1 = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int k1 = 4;
    cout << "Maximum sum of subarray of size " << k1 << ": " << maxSumSubarray(arr1, k1) << endl; // Expected: 39

    // 2. Minimum Window Substring
    string s2 = "ADOBECODEBANC";
    string t2 = "ABC";
    cout << "Minimum window substring: " << minWindowSubstring(s2, t2) << endl; // Expected: "BANC"

    // 3. Longest Substring Without Repeating Characters
    string s3 = "abcabcbb";
    cout << "Longest substring without repeating characters: " << longestSubstringWithoutRepeatingChars(s3) << endl; // Expected: 3

     // 4. Counting Anagrams
    string text4 = "BACDGABCDAABCD";
    string pattern4 = "ABCD";
    cout << "Number of anagrams of '" << pattern4 << "' in '" << text4 << "': " << countAnagrams(text4, pattern4) << endl; //expected 3

    // 5. Sliding Window Maximum
    vector<int> nums5 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k5 = 3;
    vector<int> result5 = slidingWindowMaximum(nums5, k5);
    cout << "Sliding window maximum (k=" << k5 << "): ";
    for (int num : result5) {
        cout << num << " "; // Expected: 3 3 5 5 6 7
    }
    cout << endl;

    return 0;
}
