#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <unordered_map>
#include <unordered_set> // Include the unordered_set header

using namespace std;

// Function to find the maximum sum of a subarray of size k (Fixed Sliding Window)
// Approach 1: Fixed Sliding Window
int maxSubarraySum(const vector<int>& arr, int k) {
    if (arr.size() < k) {
        return -1; // Invalid input
    }

    int max_sum = 0;
    int current_sum = 0;

    // Calculate the sum of the first k elements
    for (int i = 0; i < k; ++i) {
        current_sum += arr[i];
    }
    max_sum = current_sum;

    // Slide the window through the rest of the array
    for (int i = k; i < arr.size(); ++i) {
        current_sum += (arr[i] - arr[i - k]); // Add the new element, subtract the oldest
        max_sum = max(max_sum, current_sum);   // Update the maximum sum
    }

    return max_sum;
}

// Function to find the length of the longest substring without repeating characters
// Approach 2: Dynamic Sliding Window with a Set
int longestUniqueSubstr(const string& str) {
    int max_len = 0;
    int start = 0;
    int end = 0;
    unordered_set<char> seen; // Use a set to track seen characters

    while (end < str.length()) {
        if (seen.find(str[end]) == seen.end()) { // If the character is not in the set
            seen.insert(str[end]);             // Add it to the set
            end++;                             // Expand the window
            max_len = max(max_len, end - start); // Update max length
        } else {
            seen.erase(str[start]);           // Remove the leftmost character
            start++;                           // Shrink the window
        }
    }
    return max_len;
}

// Function to find the minimum size subarray sum greater than or equal to a target
// Approach 3: Dynamic Sliding Window to find min subarray
int minSubarraySum(const vector<int>& nums, int target) {
    int min_len = INT_MAX;
    int start = 0;
    int end = 0;
    int current_sum = 0;

    while (end < nums.size()) {
        current_sum += nums[end]; // Expand the window
        end++;

        while (current_sum >= target) {
            min_len = min(min_len, end - start); // Update min length
            current_sum -= nums[start];         // Shrink the window
            start++;
        }
    }
    return (min_len == INT_MAX) ? 0 : min_len; // Return 0 if no such subarray exists
}

// Function to count the number of subarrays with sum equal to k
// Approach 4: Using a Hash Map to store prefix sums
int subarraySumK(const vector<int>& nums, int k) {
    int count = 0;
    int current_sum = 0;
    unordered_map<int, int> sum_map; // Map to store prefix sums and their frequencies
    sum_map[0] = 1; // Initialize with sum 0 occurring once (empty subarray)

    for (int num : nums) {
        current_sum += num;
        // If there's a prefix sum (current_sum - k), then there's a subarray ending at the current index with sum k
        if (sum_map.find(current_sum - k) != sum_map.end()) {
            count += sum_map[current_sum - k];
        }
        sum_map[current_sum]++; // Update frequency of the current prefix sum
    }
    return count;
}

// Function to find the longest substring with at most K distinct characters
// Approach 5: Dynamic Sliding Window with Character Frequency Map
int longestSubstringWithKDistinct(const string& s, int k) {
    int start = 0, end = 0, max_len = 0;
    unordered_map<char, int> freq_map; // Map to store character frequencies

    while (end < s.length()) {
        freq_map[s[end]]++; // Add the character to the frequency map
        end++;

        while (freq_map.size() > k) { // If the number of distinct characters exceeds k
            freq_map[s[start]]--;     // Decrease the frequency of the leftmost character
            if (freq_map[s[start]] == 0) {
                freq_map.erase(s[start]); // Remove the character if its frequency becomes 0
            }
            start++; // Shrink the window
        }
        max_len = max(max_len, end - start); // Update max length
    }
    return max_len;
}

int main() {
    // Example usage of the functions
    vector<int> arr = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int k = 4;
    cout << "Maximum subarray sum of size " << k << ": " << maxSubarraySum(arr, k) << endl;

    string str = "abcabcbb";
    cout << "Length of longest unique substring: " << longestUniqueSubstr(str) << endl;

    vector<int> nums = {2, 3, 1, 2, 4, 3};
    int target = 7;
    cout << "Minimum subarray length with sum >= " << target << ": " << minSubarraySum(nums, target) << endl;

    vector<int> nums2 = {1, 1, 1};
    int target2 = 2;
    cout << "Subarray count with sum  = " << target2 << ": " << subarraySumK(nums2, target2) << endl;

    string s = "eceba";
    int kDistinct = 2;
    cout << "Longest substring with at most " << kDistinct << " distinct characters: " << longestSubstringWithKDistinct(s, kDistinct) << endl;

    return 0;
}
