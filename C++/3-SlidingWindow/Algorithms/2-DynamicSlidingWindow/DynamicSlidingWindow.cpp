#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <unordered_map>
#include <deque>

using namespace std;

// Function to find the maximum sum of a subarray of size k (Fixed Size Window)
int maxSubarraySumFixedSize(const vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) {
        return -1; // Invalid input: k is larger than array size
    }

    int max_sum = numeric_limits<int>::min(); // Initialize max_sum to the smallest possible integer
    int window_sum = 0;

    // Calculate the sum of the first window
    for (int i = 0; i < k; ++i) {
        window_sum += arr[i];
    }
    max_sum = window_sum; //initialize max_sum

    // Slide the window through the rest of the array
    for (int i = k; i < n; ++i) {
        window_sum += arr[i] - arr[i - k]; // Add the new element and subtract the oldest
        max_sum = max(max_sum, window_sum); // Update max_sum if the current window sum is larger
    }

    return max_sum;
}

// Function to find the minimum size subarray with a sum greater than or equal to a target (Dynamic Size Window - 1)
int minSubarrayLenGreaterThanTarget(const vector<int>& arr, int target) {
    int n = arr.size();
    int min_len = numeric_limits<int>::max(); // Initialize min_len to the largest possible integer
    int window_sum = 0;
    int window_start = 0;

    for (int window_end = 0; window_end < n; ++window_end) {
        window_sum += arr[window_end]; // Expand the window

        while (window_sum >= target) { // Shrink the window while the condition is met
            min_len = min(min_len, window_end - window_start + 1); // Update min_len
            window_sum -= arr[window_start]; // Remove the element at the start of the window
            ++window_start; // Move the start of the window forward
        }
    }

    return (min_len == numeric_limits<int>::max()) ? 0 : min_len; // Return 0 if no such subarray exists
}

// Function to find the longest substring without repeating characters (Dynamic Size Window - 2)
int lengthOfLongestSubstring(const string& s) {
    int n = s.length();
    int max_len = 0;
    int window_start = 0;
    unordered_map<char, int> char_index_map; // Map to store the index of each character

    for (int window_end = 0; window_end < n; ++window_end) {
        char current_char = s[window_end];
        // If the character is already in the map and its index is within the current window
        if (char_index_map.find(current_char) != char_index_map.end() && char_index_map[current_char] >= window_start) {
            window_start = char_index_map[current_char] + 1; // Move the start of the window to the next character after the previous occurrence
        }
        char_index_map[current_char] = window_end; // Update the index of the current character
        max_len = max(max_len, window_end - window_start + 1); // Update max_len
    }
    return max_len;
}

// Function to find the maximum sum of a subarray of size k, handling negative numbers (Fixed Size Window with negative numbers)
int maxSubarraySumFixedSizeNegative(const vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) {
        return -1; // Invalid input: k is larger than array size
    }

    int max_sum = numeric_limits<int>::min();
    int window_sum = 0;

    // Calculate the sum of the first window
    for (int i = 0; i < k; ++i) {
        window_sum += arr[i];
    }
    max_sum = window_sum;

    // Slide the window through the rest of the array
    for (int i = k; i < n; ++i) {
        window_sum += arr[i] - arr[i - k];
        max_sum = max(max_sum, window_sum);
    }

    return max_sum;
}

// Function to find the maximum of all subarrays of size k using a deque (Fixed Size Window - Deque)
vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> result;
    deque<int> dq; // Use a deque to store indices

    if (n < k || k <= 0) {
        return result; // Handle edge cases
    }

    for (int i = 0; i < n; ++i) {
        // Remove elements out of the window
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        // Remove smaller elements from the back
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i); // Add current element's index
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]); // The front of the deque is the index of the largest element in the window
        }
    }
    return result;
}

int main() {
    // Example usage of the functions
    vector<int> arr1 = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int k1 = 4;
    cout << "Maximum subarray sum of size " << k1 << ": " << maxSubarraySumFixedSize(arr1, k1) << endl; // Output: 39

    vector<int> arr2 = {2, 3, 1, 2, 4, 3};
    int target2 = 7;
    cout << "Minimum subarray length with sum >= " << target2 << ": " << minSubarrayLenGreaterThanTarget(arr2, target2) << endl; // Output: 2

    string s3 = "abcabcbb";
    cout << "Length of longest substring without repeating characters: " << lengthOfLongestSubstring(s3) << endl; // Output: 3

    vector<int> arr4 = {-2, -3, 4, -1, -2, 1, 5, -3};
    int k4 = 3;
    cout << "Maximum subarray sum of size " << k4 << " (with negative numbers): " << maxSubarraySumFixedSizeNegative(arr4, k4) << endl; // Output: 6

    vector<int> nums5 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k5 = 3;
    vector<int> result5 = maxSlidingWindow(nums5, k5);
    cout << "Maximums of sliding windows of size " << k5 << ": ";
    for (int num : result5) {
        cout << num << " ";
    }
    cout << endl; // Output: 3 3 5 5 6 7

    return 0;
}
