#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <numeric>
#include <unordered_map>
#include <queue>

using namespace std;

// 1. Fixed Size Sliding Window - Maximum Sum Subarray
// Real-world application: Analyzing fixed-length time series data (e.g., stock prices over a 5-day period) to find the maximum average.
int maxSumSubarray(const vector<int>& arr, int k) {
    if (arr.size() < k) {
        return -1; // Handle invalid input
    }

    int maxSum = 0;
    int currentSum = 0;

    // Calculate the sum of the first window
    for (int i = 0; i < k; ++i) {
        currentSum += arr[i];
    }
    maxSum = currentSum;

    // Slide the window through the rest of the array
    for (int i = k; i < arr.size(); ++i) {
        currentSum += arr[i] - arr[i - k]; // Add the new element, subtract the oldest
        maxSum = max(maxSum, currentSum);   // Update the maximum sum
    }
    return maxSum;
}

// 2. Dynamic Sliding Window - Minimum Window Substring
// Real-world application: Text processing, finding the smallest substring containing a set of characters (e.g., finding the shortest DNA sequence containing a specific gene pattern).
string minWindowSubstring(const string& s, const string& t) {
    if (s.empty() || t.empty() || t.size() > s.size()) {
        return ""; // Handle invalid input
    }

    unordered_map<char, int> targetFreq; // Frequency of characters in t
    for (char c : t) {
        targetFreq[c]++;
    }

    int left = 0, right = 0;
    int minLeft = 0, minLength = numeric_limits<int>::max();
    int formed = 0; // Count of characters matched
    unordered_map<char, int> windowFreq; // Frequency of characters in the current window

    while (right < s.size()) {
        char currentChar = s[right];
        windowFreq[currentChar]++;

        if (targetFreq.find(currentChar) != targetFreq.end() &&
            windowFreq[currentChar] <= targetFreq[currentChar]) {
            formed++;
        }

        // Try to contract the window
        while (left <= right && formed == t.size()) {
            if (right - left + 1 < minLength) {
                minLength = right - left + 1;
                minLeft = left;
            }

            char leftChar = s[left];
            windowFreq[leftChar]--;

            if (targetFreq.find(leftChar) != targetFreq.end() &&
                windowFreq[leftChar] < targetFreq[leftChar]) {
                formed--;
            }
            left++; // Move the left boundary
        }
        right++; // Expand the window
    }
    return minLength == numeric_limits<int>::max() ? "" : s.substr(minLeft, minLength);
}

// 3. Sliding Window with Hashing - Find All Anagrams in a String
// Real-world application:  Bioinformatics, finding occurrences of a specific DNA sequence (anagram) within a larger sequence.
vector<int> findAnagrams(const string& s, const string& p) {
    vector<int> result;
    if (p.size() > s.size()) {
        return result; // Handle invalid input
    }

    unordered_map<char, int> targetFreq; // Frequency of characters in p
    for (char c : p) {
        targetFreq[c]++;
    }

    unordered_map<char, int> windowFreq; // Frequency of characters in the current window
    int left = 0, right = 0;
    int count = 0; // Count of matched characters

    while (right < s.size()) {
        char currentChar = s[right];
        windowFreq[currentChar]++;

        if (targetFreq.find(currentChar) != targetFreq.end() &&
            windowFreq[currentChar] <= targetFreq[currentChar]) {
            count++;
        }

        if (right - left + 1 == p.size()) {
            if (count == p.size()) {
                result.push_back(left);
            }

            char leftChar = s[left];
            windowFreq[leftChar]--;
            if (targetFreq.find(leftChar) != targetFreq.end() &&
                windowFreq[leftChar] < targetFreq[leftChar]) {
                count--;
            }
            left++;
        }
        right++;
    }
    return result;
}

// 4. Sliding Window with Queue - Maximum of all subarrays of size k
// Real-world application: Real-time data processing, finding the maximum value in a stream of data within a fixed-size window (e.g., monitoring the peak value of network traffic in a 5-second interval).
vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    vector<int> result;
    if (nums.empty() || k <= 0) return result;
    if (k > nums.size()) k = nums.size(); // handle edge case.

    deque<int> q; // Store indices, not values
    for (int i = 0; i < nums.size(); ++i) {
        // Remove elements out of the current window
        while (!q.empty() && q.front() < i - k + 1) {
            q.pop_front();
        }

        // Remove smaller elements from the back
        while (!q.empty() && nums[q.back()] < nums[i]) {
            q.pop_back();
        }

        q.push_back(i); // Add the current element's index

        if (i >= k - 1) {
            result.push_back(nums[q.front()]); // The front is always the maximum
        }
    }
    return result;
}

// 5. Sliding Window for String Matching - Longest Substring Without Repeating Characters
// Real-world application: Data compression, finding the longest substring without repeating characters can help in identifying patterns for efficient encoding.
int lengthOfLongestSubstring(const string& s) {
    int maxLength = 0;
    int left = 0, right = 0;
    unordered_map<char, int> charIndexMap; // Store character and its last seen index

    while (right < s.size()) {
        char currentChar = s[right];
        if (charIndexMap.find(currentChar) != charIndexMap.end() &&
            charIndexMap[currentChar] >= left) {
            left = charIndexMap[currentChar] + 1; // Move left pointer
        }
        charIndexMap[currentChar] = right; // Update last seen index
        maxLength = max(maxLength, right - left + 1);
        right++;
    }
    return maxLength;
}

int main() {
    // 1. Fixed Size Sliding Window
    vector<int> arr1 = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int k1 = 4;
    cout << "Maximum sum of subarray of size " << k1 << ": " << maxSumSubarray(arr1, k1) << endl; // Output: 39

    // 2. Dynamic Sliding Window
    string s2 = "ADOBECODEBANC";
    string t2 = "ABC";
    cout << "Minimum window substring: " << minWindowSubstring(s2, t2) << endl; // Output: BANC

    // 3. Sliding Window with Hashing
    string s3 = "cbaebabacd";
    string p3 = "abc";
    vector<int> anagramIndices = findAnagrams(s3, p3);
    cout << "Anagram indices: "; // Output: 0 6
    for (int index : anagramIndices) {
        cout << index << " ";
    }
    cout << endl;

    // 4. Sliding Window with Queue
    vector<int> nums4 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k4 = 3;
    vector<int> maxValues = maxSlidingWindow(nums4, k4);
    cout << "Maximum values in sliding window: "; // Output: 3 3 5 5 6 7
    for (int value : maxValues) {
        cout << value << " ";
    }
    cout << endl;

    // 5. Sliding Window for String Matching
    string s5 = "abcabcbb";
    cout << "Length of longest substring without repeating characters: " << lengthOfLongestSubstring(s5) << endl; // Output: 3

    string s6 = "bbbbb";
    cout << "Length of longest substring without repeating characters: " << lengthOfLongestSubstring(s6) << endl; // Output: 1

    string s7 = "pwwkew";
    cout << "Length of longest substring without repeating characters: " << lengthOfLongestSubstring(s7) << endl; // Output: 3

    return 0;
}
