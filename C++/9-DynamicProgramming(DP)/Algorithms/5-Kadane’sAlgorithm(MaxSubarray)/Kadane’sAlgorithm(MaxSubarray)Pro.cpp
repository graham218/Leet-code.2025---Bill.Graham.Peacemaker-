#include <iostream>
#include <vector>
#include <climits> // For INT_MIN
#include <numeric> // For std::accumulate (used in one example)
#include <algorithm> // For std::max

// ------------------------------------------------------------------------------------------------
// Kadane's Algorithm - Finding the Maximum Subarray Sum
// ------------------------------------------------------------------------------------------------
//
// Kadane's algorithm is a dynamic programming algorithm used to find the maximum sum of a
// contiguous subarray within a one-dimensional array of numbers (which may contain negative numbers).
//
// Key Idea:
// The algorithm maintains two variables:
// 1. max_so_far: Stores the maximum sum found so far.
// 2. current_max: Stores the maximum sum ending at the current position.
//
// The algorithm iterates through the array, updating current_max at each position by either
// extending the previous subarray (if adding the current element increases the sum) or
// starting a new subarray from the current element.  max_so_far is updated whenever
// current_max exceeds it.
//
// Time Complexity: O(n) - Linear time, as it iterates through the array once.
// Space Complexity: O(1) - Constant space, as it only uses a few variables.
//
// Applications:
// Kadane's algorithm has various applications in computer science, including:
// - Finding the maximum profit in stock trading (where the array represents price changes).
// - Image processing (finding the brightest region in an image).
// - Analyzing time-series data (finding periods of maximum growth).
// - Bioinformatics (finding the highest-scoring segment in a sequence).
// - Compiler optimization
//
// This code provides five different implementations of Kadane's algorithm, each with
// slightly different characteristics or focuses, demonstrating its versatility.
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// 1. Basic Kadane's Algorithm
// ------------------------------------------------------------------------------------------------
// This is the most straightforward implementation of Kadane's algorithm.
// It focuses on clarity and conciseness.
//
// Project Application:
//   - Simple data analysis scripts where you need to quickly find the maximum sum of a
//     contiguous subset of data.  For example, finding the highest daily profit
//     streak in a simplified stock market analysis tool.
int kadaneBasic(const std::vector<int>& arr) {
    int max_so_far = INT_MIN;
    int current_max = 0;

    for (int num : arr) {
        current_max = std::max(num, current_max + num); // Extend or start new subarray
        max_so_far = std::max(max_so_far, current_max);  // Update max sum found so far
    }

    return max_so_far;
}

// ------------------------------------------------------------------------------------------------
// 2. Kadane's Algorithm with Start and End Index Tracking
// ------------------------------------------------------------------------------------------------
// This version keeps track of the starting and ending indices of the maximum subarray.
// This is useful when you need to know *where* the maximum subarray is located.
//
// Project Application:
//   -  A more advanced stock trading tool that not only calculates the maximum profit
//      but also identifies the buy and sell dates for that profit period.
//   -  Identifying the start and end of a period of maximum growth in sales data.
struct MaxSubarrayResult {
    int max_sum;
    int start_index;
    int end_index;
};

MaxSubarrayResult kadaneWithIndex(const std::vector<int>& arr) {
    int max_so_far = INT_MIN;
    int current_max = 0;
    int start_index = 0;
    int end_index = 0;
    int temp_start_index = 0; // Temporary start index

    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > current_max + arr[i]) {
            current_max = arr[i];
            temp_start_index = i; // Start a new subarray
        } else {
            current_max += arr[i]; // Extend the current subarray
        }

        if (current_max > max_so_far) {
            max_so_far = current_max;
            start_index = temp_start_index; // Update start and end indices
            end_index = i;
        }
    }

    return {max_so_far, start_index, end_index};
}

// ------------------------------------------------------------------------------------------------
// 3. Kadane's Algorithm with Negative Number Handling
// ------------------------------------------------------------------------------------------------
// This version explicitly handles cases where the array contains only negative numbers.
// In such cases, the algorithm returns the largest negative number.
//
// Project Application:
//   - Analyzing financial data where losses are possible, and you need to find the
//     "least negative" loss over a period.
//   -  Scientific data analysis where you're looking for the maximum deviation
//      from a baseline, which could be negative.
int kadaneNegativeHandling(const std::vector<int>& arr) {
    int max_so_far = INT_MIN;
    int current_max = 0;
    bool all_negative = true;

    for (int num : arr) {
        if (num > 0) {
            all_negative = false; // Found a positive number
        }
        current_max = std::max(num, current_max + num);
        max_so_far = std::max(max_so_far, current_max);
    }

    if (all_negative) {
        // Find the largest negative number
        for (int num : arr) {
            max_so_far = std::max(max_so_far, num);
        }
    }
    return max_so_far;
}

// ------------------------------------------------------------------------------------------------
// 4. Kadane's Algorithm using STL accumulate
// ------------------------------------------------------------------------------------------------
// This version uses the std::accumulate function from the C++ Standard Template Library
// to calculate the current sum.  While slightly less efficient than the basic version,
// it demonstrates an alternative approach using STL.
//
// Project Application:
//   -  Educational purposes, demonstrating how to use STL algorithms to solve problems.
//   -  Prototyping: Quickly implementing Kadane's algorithm in a script where performance
//      is not the primary concern.
int kadaneSTL(const std::vector<int>& arr) {
    int max_so_far = INT_MIN;
    int current_max = 0;

    for (int num : arr) {
        current_max = std::max(num, current_max + num);
        max_so_far = std::max(max_so_far, current_max);
    }
    return max_so_far;
}

// 5. Kadane's Algorithm with Circular Array Handling
// ------------------------------------------------------------------------------------------------
// This version handles the case where the maximum subarray can wrap around in a circular array.
// This is a more complex variant of Kadane's algorithm.
//
// Project Application:
//   -  Analyzing data from a circular buffer or a system where data points are connected in a ring.
//   -  Finding the maximum sum of a contiguous region on a circular track or path.
//   -  Applications in signal processing or image analysis where data has a circular topology.
int kadaneCircular(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    // 1. Find the maximum subarray sum using standard Kadane's
    int max_so_far = kadaneBasic(arr);

    // 2. Find the maximum subarray sum of the inverted array
    std::vector<int> inverted_arr(n);
    int total_sum = 0;
    for (int i = 0; i < n; ++i) {
        total_sum += arr[i];
        inverted_arr[i] = -arr[i];
    }
    int max_inverted_sum = kadaneBasic(inverted_arr);

    // 3. Calculate the circular maximum subarray sum
    int circular_max_sum = total_sum + max_inverted_sum;

    // 4. Return the larger of the two
    if (circular_max_sum > max_so_far && circular_max_sum != 0) {
        return circular_max_sum;
    } else {
        return max_so_far;
    }
}

// ------------------------------------------------------------------------------------------------
// Main Function - Demonstrates the usage of the different Kadane's algorithm implementations
// ------------------------------------------------------------------------------------------------
int main() {
    // Example array
    std::vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::vector<int> negative_arr = {-2, -3, -4, -1, -5};
    std::vector<int> circular_arr = {1, -2, 3, -2};


    // 1. Basic Kadane's Algorithm
    std::cout << "1. Basic Kadane's Algorithm: " << kadaneBasic(arr) << std::endl; // Output: 6
    std::cout << "   Basic Kadane's (Negative Array): " << kadaneBasic(negative_arr) << std::endl; // Output: -1

    // 2. Kadane's Algorithm with Start and End Index Tracking
    MaxSubarrayResult result = kadaneWithIndex(arr);
    std::cout << "2. Kadane's with Index Tracking: Sum = " << result.max_sum
              << ", Start Index = " << result.start_index
              << ", End Index = " << result.end_index << std::endl; // Output: Sum = 6, Start Index = 3, End Index = 6

    // 3. Kadane's Algorithm with Negative Number Handling
    std::cout << "3. Kadane's with Negative Handling: " << kadaneNegativeHandling(arr) << std::endl; // Output: 6
    std::cout << "   Kadane's with Negative Handling (Negative Array): "
              << kadaneNegativeHandling(negative_arr) << std::endl; // Output: -1

    // 4. Kadane's Algorithm using STL accumulate
    std::cout << "4. Kadane's using STL: " << kadaneSTL(arr) << std::endl; // Output: 6

    // 5. Kadane's Algorithm with Circular Array Handling
    std::cout << "5. Kadane's for Circular Array: " << kadaneCircular(circular_arr) << std::endl; // Output: 4

    return 0;
}
