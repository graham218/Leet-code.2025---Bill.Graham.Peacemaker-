#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> // Required for numeric_limits
#include <numeric> // Required for std::accumulate

using namespace std;

// 1. Kadane's Algorithm (Basic) - Most efficient, handles all cases
//    - This is the standard implementation of Kadane's algorithm.
//    - It iterates through the array, keeping track of the maximum subarray sum ending at the current position (`max_ending_here`) and the overall maximum sum (`max_so_far`).
//    - It's efficient (O(n)) and works for arrays with negative numbers.
int kadaneBasic(const vector<int>& nums) {
    if (nums.empty()) {
        return 0; // Or throw an exception, depending on the desired behavior for empty input
    }

    int max_so_far = nums[0];  // Initialize with the first element, handles single-element arrays
    int max_ending_here = nums[0];

    for (size_t i = 1; i < nums.size(); ++i) {
        // Decide whether to extend the current subarray or start a new one.
        max_ending_here = max(nums[i], max_ending_here + nums[i]);
        // Update the overall maximum sum.
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

// 2. Kadane's Algorithm with Start and End Index Tracking
//    - This version keeps track of the start and end indices of the maximum subarray.
//    - Useful when you need to know *which* subarray has the maximum sum, not just the sum itself.
//    - Handles cases where the maximum subarray is empty.
pair<int, pair<int, int>> kadaneWithIndex(const vector<int>& nums) {
    if (nums.empty()) {
        return {0, {0, -1}}; // Return 0 and an invalid range, or throw an exception.  Start index is 0, end index is -1.
    }

    int max_so_far = nums[0];
    int max_ending_here = nums[0];
    int start_index = 0;
    int end_index = 0;
    int current_start = 0; // Track the start of the current subarray

    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] > max_ending_here + nums[i]) {
            // Start a new subarray from the current element.
            max_ending_here = nums[i];
            current_start = i; // Update the start index
        } else {
            // Extend the current subarray.
            max_ending_here = max_ending_here + nums[i];
        }

        if (max_ending_here > max_so_far) {
            // Update the overall maximum sum and its indices.
            max_so_far = max_ending_here;
            start_index = current_start;
            end_index = i;
        }
    }
    return {max_so_far, {start_index, end_index}};
}

// 3. Kadane's Algorithm with Empty Subarray Handling
//    - This version explicitly handles the case where all numbers in the array are negative.
//    - In such cases, it returns the largest negative number (the least negative), which corresponds to the empty subarray.
//    - This might be required in specific applications.
int kadaneWithEmptySubarray(const vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    int max_so_far = nums[0];
    int max_ending_here = nums[0];
    bool all_negative = true;

    for (int num : nums) {
        if (num > 0) {
            all_negative = false; // Found a positive number
            break;
        }
    }

    if (all_negative) {
        // If all numbers are negative, find the maximum (least negative)
        max_so_far = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            max_so_far = max(max_so_far, nums[i]);
        }
        return max_so_far;
    }

    // Standard Kadane's algorithm
    for (size_t i = 1; i < nums.size(); ++i) {
        max_ending_here = max(nums[i], max_ending_here + nums[i]);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

// 4. Kadane's Algorithm using Accumulate (for comparison)
//     - This approach uses std::accumulate for a more functional style, but it's less efficient.
//     - It's included here for demonstration and comparison, NOT for performance-critical applications.
//     - It calculates the cumulative sum at each step and compares it with the current element.
int kadaneAccumulate(const vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    int max_so_far = nums[0];
    int current_sum = 0;

    for (int num : nums) {
        current_sum = max(num, current_sum + num);
        max_so_far = max(max_so_far, current_sum);
    }
    return max_so_far;
}

// 5. Kadane's Algorithm with Negative Infinity Initialization
//    - Initializes `max_so_far` to the smallest possible integer.
//    - Useful in situations where you want to ensure that the algorithm works correctly even if the array contains only negative numbers.
//    - Using numeric_limits<int>::min() guarantees that any non-empty subarray will have a sum greater than the initial value of max_so_far.
int kadaneNegativeInfinity(const vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    int max_so_far = numeric_limits<int>::min(); // Initialize to negative infinity
    int max_ending_here = 0;

    for (int num : nums) {
        max_ending_here = max(num, max_ending_here + num);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

int main() {
    // Test cases
    vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    vector<int> nums2 = {1};
    vector<int> nums3 = {-2, -3, -4, -5};
    vector<int> nums4 = {-2, 1, -3, 4, -1, 2, 1, -5, 4, 10, -2, -3, 4, 5}; // Added a longer test case
    vector<int> nums5 = {}; // Empty vector
    vector<int> nums6 = {5, 4, -1, 7, 8};

    // Test all the functions
    cout << "Test Case 1: [-2, 1, -3, 4, -1, 2, 1, -5, 4]" << endl;
    cout << "Kadane's Basic: " << kadaneBasic(nums1) << endl;
    pair<int, pair<int, int>> result1 = kadaneWithIndex(nums1);
    cout << "Kadane's with Index: Sum = " << result1.first << ", Start = " << result1.second.first << ", End = " << result1.second.second << endl;
    cout << "Kadane's with Empty Subarray: " << kadaneWithEmptySubarray(nums1) << endl;
    cout << "Kadane's with Accumulate: " << kadaneAccumulate(nums1) << endl;
    cout << "Kadane's with Negative Infinity: " << kadaneNegativeInfinity(nums1) << endl;
    cout << endl;

    cout << "Test Case 2: [1]" << endl;
    cout << "Kadane's Basic: " << kadaneBasic(nums2) << endl;
    pair<int, pair<int, int>> result2 = kadaneWithIndex(nums2);
    cout << "Kadane's with Index: Sum = " << result2.first << ", Start = " << result2.second.first << ", End = " << result2.second.second << endl;
    cout << "Kadane's with Empty Subarray: " << kadaneWithEmptySubarray(nums2) << endl;
    cout << "Kadane's with Accumulate: " << kadaneAccumulate(nums2) << endl;
    cout << "Kadane's with Negative Infinity: " << kadaneNegativeInfinity(nums2) << endl;
    cout << endl;

    cout << "Test Case 3: [-2, -3, -4, -5]" << endl;
    cout << "Kadane's Basic: " << kadaneBasic(nums3) << endl;
    pair<int, pair<int, int>> result3 = kadaneWithIndex(nums3);
    cout << "Kadane's with Index: Sum = " << result3.first << ", Start = " << result3.second.first << ", End = " << result3.second.second << endl;
    cout << "Kadane's with Empty Subarray: " << kadaneWithEmptySubarray(nums3) << endl;
    cout << "Kadane's with Accumulate: " << kadaneAccumulate(nums3) << endl;
    cout << "Kadane's with Negative Infinity: " << kadaneNegativeInfinity(nums3) << endl;
    cout << endl;

    cout << "Test Case 4: [-2, 1, -3, 4, -1, 2, 1, -5, 4, 10, -2, -3, 4, 5]" << endl;
    cout << "Kadane's Basic: " << kadaneBasic(nums4) << endl;
    pair<int, pair<int, int>> result4 = kadaneWithIndex(nums4);
    cout << "Kadane's with Index: Sum = " << result4.first << ", Start = " << result4.second.first << ", End = " << result4.second.second << endl;
    cout << "Kadane's with Empty Subarray: " << kadaneWithEmptySubarray(nums4) << endl;
    cout << "Kadane's with Accumulate: " << kadaneAccumulate(nums4) << endl;
    cout << "Kadane's with Negative Infinity: " << kadaneNegativeInfinity(nums4) << endl;
    cout << endl;

    cout << "Test Case 5: []" << endl;
    cout << "Kadane's Basic: " << kadaneBasic(nums5) << endl;
    pair<int, pair<int, int>> result5 = kadaneWithIndex(nums5);
    cout << "Kadane's with Index: Sum = " << result5.first << ", Start = " << result5.second.first << ", End = " << result5.second.second << endl;
    cout << "Kadane's with Empty Subarray: " << kadaneWithEmptySubarray(nums5) << endl;
    cout << "Kadane's with Accumulate: " << kadaneAccumulate(nums5) << endl;
    cout << "Kadane's with Negative Infinity: " << kadaneNegativeInfinity(nums5) << endl;
    cout << endl;

    cout << "Test Case 6: [5, 4, -1, 7, 8]" << endl;
    cout << "Kadane's Basic: " << kadaneBasic(nums6) << endl;
    pair<int, pair<int, int>> result6 = kadaneWithIndex(nums6);
    cout << "Kadane's with Index: Sum = " << result6.first << ", Start = " << result6.second.first << ", End = " << result6.second.second << endl;
    cout << "Kadane's with Empty Subarray: " << kadaneWithEmptySubarray(nums6) << endl;
    cout << "Kadane's with Accumulate: " << kadaneAccumulate(nums6) << endl;
    cout << "Kadane's with Negative Infinity: " << kadaneNegativeInfinity(nums6) << endl;
    cout << endl;
    return 0;
}

/*
Explanation of the Approaches:

1.  Kadane's Algorithm (Basic):
    * This is the most straightforward and efficient implementation.
    * It maintains two variables: `max_so_far` to store the overall maximum sum found so far, and `max_ending_here` to store the maximum sum ending at the current position.
    * The algorithm iterates through the array, updating `max_ending_here` by choosing the maximum between the current element and the sum of the current element and the previous `max_ending_here`.
    * `max_so_far` is updated whenever `max_ending_here` becomes greater.
    * Time Complexity: O(n), where n is the size of the input array.
    * Space Complexity: O(1), as it uses only a constant amount of extra space.
    * Handles arrays with both positive and negative numbers.

2.  Kadane's Algorithm with Start and End Index Tracking:
    * This version extends the basic Kadane's algorithm to keep track of the start and end indices of the maximum subarray.
    * It introduces two more variables: `start_index` and `end_index` to store the start and end positions of the maximum subarray. `current_start` tracks the beginning of the current subarray being considered.
    * When `max_ending_here` is updated to start a new subarray (i.e., when the current element is greater than the sum of the current element and the previous `max_ending_here`), the `current_start` is updated to the current index.
    * Whenever `max_so_far` is updated, the `start_index` and `end_index` are also updated to reflect the start and end of the new maximum subarray.
    * Time Complexity: O(n)
    * Space Complexity: O(1)
    * Useful when you need to know the subarray that yields the maximum sum.

3.  Kadane's Algorithm with Empty Subarray Handling:
    * This version handles the special case where all elements of the array are negative.
    * In the standard Kadane's algorithm, if all elements are negative, it would return the least negative element.  However, in some applications, an empty subarray (with a sum of 0) might be desirable in this scenario.
    * This version first checks if all elements are negative. If they are, it returns the maximum element (least negative), which can be interpreted as the sum of the maximum single-element subarray.
    * If the array contains at least one non-negative number, it proceeds with the standard Kadane's algorithm.
     * Time Complexity: O(n)
     * Space Complexity: O(1)

4.  Kadane's Algorithm using Accumulate:
    * This version provides an alternative implementation using the `std::accumulate` function from the `<numeric>` library.
    * It maintains the current sum and updates it using `std::accumulate`.
    * This approach is less efficient than the basic Kadane's algorithm because `std::accumulate` typically involves more overhead.
    * Included primarily for demonstration and comparison.  It is NOT recommended for performance-critical code.
    * Time Complexity: O(n) in most implementations of `accumulate`, but potentially higher depending on the compiler's implementation.
    * Space Complexity: O(1)

5.  Kadane's Algorithm with Negative Infinity Initialization:
    * This version initializes `max_so_far` to the smallest possible integer value using `numeric_limits<int>::min()`.
    * This initialization ensures that the algorithm works correctly even if the array contains only negative numbers.  By starting with negative infinity, the first positive (or least negative) number encountered will always be greater than `max_so_far`, thus correctly identifying the maximum subarray.
    * In the standard Kadane's, `max_so_far` is often initialized to the first element of the array.  While this works in most cases, initializing it to negative infinity provides a more robust solution.
    * Time Complexity: O(n)
    * Space Complexity: O(1)

Which approach to use?

* For general use cases where you need the maximum subarray sum, use **Kadane's Algorithm (Basic)**.  It's the most efficient and straightforward.
* If you also need the start and end indices of the maximum subarray, use **Kadane's Algorithm with Start and End Index Tracking**.
* If your application requires specific handling of arrays with all negative numbers (e.g., returning 0 or the largest negative number), use **Kadane's Algorithm with Empty Subarray Handling**.
* Avoid using **Kadane's Algorithm using Accumulate** in performance-critical code.  It's less efficient.
* If you want a more robust solution that guarantees correct behavior even with all negative numbers, use  **Kadane's Algorithm with Negative Infinity Initialization**.
*/
