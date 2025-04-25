#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits
#include <string>
#include <numeric> // Required for std::accumulate

// ------------------------------------------------------------------------------------------------
// 1. Maximum Sum Subarray of Fixed Size K
//
// Problem: Given an array of integers and a positive integer K, find the maximum sum of any
// subarray of size K.
//
// Application: This is a fundamental problem with applications in financial analysis (e.g.,
// finding the most profitable K-day trading period), signal processing (e.g., smoothing
// a noisy signal by averaging over a fixed window), and image processing (e.g., calculating
// the average color of a K x K pixel region).
// ------------------------------------------------------------------------------------------------
int maxSubarraySum(const std::vector<int>& arr, int k) {
    if (arr.size() < k || k <= 0) {
        return 0; // Handle invalid input
    }

    int max_sum = std::numeric_limits<int>::min(); // Initialize to the smallest possible integer
    int window_sum = 0;

    // Calculate the sum of the first window
    for (int i = 0; i < k; ++i) {
        window_sum += arr[i];
    }
    max_sum = window_sum; //initialize max_sum

    // Slide the window through the array
    for (int i = k; i < arr.size(); ++i) {
        window_sum += arr[i] - arr[i - k]; // Subtract the outgoing element, add the incoming
        max_sum = std::max(max_sum, window_sum); // Update max_sum if the current window sum is larger
    }

    return max_sum;
}

// ------------------------------------------------------------------------------------------------
// 2. Minimum Subarray Length with Sum >= Target
//
// Problem: Given an array of positive integers and a target sum, find the minimum length of a
// contiguous subarray whose sum is greater than or equal to the target.
//
// Application: This problem is relevant to resource allocation (e.g., finding the smallest
// contiguous block of memory that satisfies a minimum size requirement), logistics
// (e.g., finding the shortest route segment with a minimum delivery volume), and data
// compression (e.g., finding the smallest buffer that can hold a minimum amount of data).
// ------------------------------------------------------------------------------------------------
int minSubarrayLength(const std::vector<int>& arr, int target) {
    if (arr.empty() || target <= 0) {
        return 0; // Handle invalid input
    }

    int min_length = std::numeric_limits<int>::max(); // Initialize to the largest possible integer
    int window_sum = 0;
    int window_start = 0;

    for (int window_end = 0; window_end < arr.size(); ++window_end) {
        window_sum += arr[window_end]; // Add the next element to the window

        // Shrink the window while the sum is >= target
        while (window_sum >= target) {
            min_length = std::min(min_length, window_end - window_start + 1); //update minLength
            window_sum -= arr[window_start]; // Subtract the element going out of the window
            ++window_start; // Slide the window's start
        }
    }

    return (min_length == std::numeric_limits<int>::max()) ? 0 : min_length; // Return 0 if no such subarray exists
}

// ------------------------------------------------------------------------------------------------
// 3. Longest Substring Without Repeating Characters
//
// Problem: Given a string, find the length of the longest substring without repeating characters.
//
// Application: This problem is important in text processing, bioinformatics (e.g., finding the
// longest non-repeating sequence of DNA), and data validation (e.g., checking for unique
// character sequences in identifiers).
// ------------------------------------------------------------------------------------------------
int longestUniqueSubstringLength(const std::string& str) {
    if (str.empty()) {
        return 0;
    }

    int max_length = 0;
    int window_start = 0;
    std::vector<int> char_index(256, -1); // Store the last seen index of each character (ASCII)

    for (int window_end = 0; window_end < str.length(); ++window_end) {
        char current_char = str[window_end];
        // If the character has been seen before and it's within the current window
        if (char_index[current_char] >= window_start) {
            window_start = char_index[current_char] + 1; // Move the window start to after the previous occurrence
        }
        char_index[current_char] = window_end; // Update the last seen index of the character
        max_length = std::max(max_length, window_end - window_start + 1); //update maxLength
    }

    return max_length;
}

// ------------------------------------------------------------------------------------------------
// 4.  Minimum Window Substring
//
// Problem: Given a string S and a string T, find the minimum window in S which will contain
// all the characters in T in complexity O(n).
//
// Application: This problem is useful in text search and replacement, bioinformatics (finding
// the shortest DNA sequence containing a given set of genes), and data mining (finding the
// smallest subset of data containing a specific set of attributes).
// ------------------------------------------------------------------------------------------------
std::string minWindowSubstring(const std::string& s, const std::string& t) {
    if (s.empty() || t.empty() || t.length() > s.length()) {
        return ""; // Handle invalid input
    }

    std::vector<int> target_freq(256, 0); // Frequency of characters in T
    std::vector<int> window_freq(256, 0); // Frequency of characters in the current window
    int required_chars = 0; // Count of distinct characters needed from T
    int formed_chars = 0;    // Count of distinct characters from T found in the current window

    // Calculate frequency of characters in T
    for (char c : t) {
        if (target_freq[c] == 0) {
            required_chars++;
        }
        target_freq[c]++;
    }

    int window_start = 0;
    int min_window_length = std::numeric_limits<int>::max();
    int min_window_start = 0;

    for (int window_end = 0; window_end < s.length(); ++window_end) {
        char current_char = s[window_end];
        window_freq[current_char]++; // Add the current character to the window

        // If the frequency of the current character in the window matches the required frequency in T
        if (target_freq[current_char] != 0 && window_freq[current_char] == target_freq[current_char]) {
            formed_chars++; // Increment the count of formed characters
        }

        // Try to minimize the window size
        while (formed_chars == required_chars) {
            // Update minimum window length and start index
            if (window_end - window_start + 1 < min_window_length) {
                min_window_length = window_end - window_start + 1;
                min_window_start = window_start;
            }

            char start_char = s[window_start];
            window_freq[start_char]--; // Remove the character at the start of the window

            // If removing the character makes the window no longer satisfy the condition
            if (target_freq[start_char] != 0 && window_freq[start_char] < target_freq[start_char]) {
                formed_chars--; // Decrement the count of formed characters
            }
            window_start++; // Shrink the window
        }
    }

    return (min_window_length == std::numeric_limits<int>::max()) ? "" : s.substr(min_window_start, min_window_length);
}

// ------------------------------------------------------------------------------------------------
// 5.  Longest Subarray with Sum at Most K
//
// Problem: Given an array of positive integers and a target sum K, find the length of the
// longest subarray whose sum is at most K.
//
// Application: Useful in resource allocation (e.g., finding the longest time interval within
// a budget constraint), network traffic analysis (e.g., finding the longest period with
// bandwidth usage below a threshold), and financial analysis (e.g., finding the longest
// period where cumulative losses are within a limit).
// ------------------------------------------------------------------------------------------------

int longestSubarrayWithSumAtMostK(const std::vector<int>& arr, int k) {
    if (arr.empty() || k < 0) {
        return 0;
    }

    int max_length = 0;
    int window_start = 0;
    int window_sum = 0;

    for (int window_end = 0; window_end < arr.size(); ++window_end) {
        window_sum += arr[window_end]; // Add the next element to the window

        // Shrink the window while the sum is greater than K
        while (window_sum > k) {
            window_sum -= arr[window_start]; // Subtract the element going out of the window
            ++window_start; // Slide the window's start
        }

        max_length = std::max(max_length, window_end - window_start + 1); //update the maxLen
    }

    return max_length;
}

int main() {
    // Example usage of the functions
    std::vector<int> arr1 = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int k1 = 4;
    std::cout << "1. Maximum Subarray Sum of size " << k1 << ": " << maxSubarraySum(arr1, k1) << std::endl; // Expected: 39

    std::vector<int> arr2 = {2, 3, 1, 2, 4, 3};
    int target2 = 7;
    std::cout << "2. Minimum Subarray Length with Sum >= " << target2 << ": " << minSubarrayLength(arr2, target2) << std::endl; // Expected: 2

    std::string str3 = "abcabcbb";
    std::cout << "3. Longest Unique Substring Length: " << longestUniqueSubstringLength(str3) << std::endl; // Expected: 3

    std::string s4 = "ADOBECODEBANC";
    std::string t4 = "ABC";
    std::cout << "4. Minimum Window Substring containing \"" << t4 << "\": \"" << minWindowSubstring(s4, t4) << "\"" << std::endl; // Expected: "BANC"

    std::vector<int> arr5 = {1, 2, 3, 4, 1, 2, 3, 1, 1, 4};
    int k5 = 8;
    std::cout << "5. Longest Subarray with Sum at Most " << k5 << ": " << longestSubarrayWithSumAtMostK(arr5, k5) << std::endl; // Expected: 4

    return 0;
}
