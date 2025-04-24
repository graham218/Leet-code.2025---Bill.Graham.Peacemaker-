#include <iostream>
#include <vector>
#include <climits>
#include <numeric> // for std::accumulate
#include <algorithm> // for std::max

// 1. Basic Kadane's Algorithm
//   - This is the standard implementation for finding the maximum subarray sum.
//   - It's the foundation for the other approaches.
//   - Real-world application: Analyzing stock prices to find the maximum profit over a period.
int kadaneBasic(const std::vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;

    for (int num : nums) {
        maxEndingHere = std::max(num, maxEndingHere + num);
        maxSoFar = std::max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

// 2. Kadane's Algorithm with Start and End Indices
//   - This version keeps track of the start and end indices of the maximum subarray.
//   - Useful when you need to know the subarray that yields the maximum sum.
//   - Real-world application: Identifying the most profitable trading period in stock market data.
std::pair<int, std::pair<int, int>> kadaneWithIndices(const std::vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    int start = 0;
    int end = 0;
    int tempStart = 0;

    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > maxEndingHere + nums[i]) {
            maxEndingHere = nums[i];
            tempStart = i; // Start a new subarray
        } else {
            maxEndingHere += nums[i];
        }

        if (maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
            start = tempStart;
            end = i;
        }
    }
    return {maxSoFar, {start, end}};
}

// 3. Kadane's Algorithm for Circular Subarrays
//   - Handles the case where the maximum subarray can wrap around the end of the array.
//   - This is a variation of Kadane's algorithm.
//   - Real-world application: Analyzing data from a circular buffer, such as daily temperature fluctuations where the last day connects to the first.
int maxSubarraySumCircular(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    // Case 1: Max subarray is non-wrapping (use standard Kadane)
    int maxNonWrapping = kadaneBasic(nums);

    // Case 2: Max subarray is wrapping
    int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
    // Invert the array elements to find the minimum subarray sum.
    std::vector<int> invertedNums(n);
    for (int i = 0; i < n; ++i) {
        invertedNums[i] = -nums[i];
    }
    int minSubarraySum = kadaneBasic(invertedNums);
    int maxWrapping = totalSum + minSubarraySum; // Add the minimum subarray

    // Handle the case where all elements are negative
    if (maxWrapping == 0) {
        return maxNonWrapping;
    }

    return std::max(maxNonWrapping, maxWrapping);
}

// 4. Kadane's Algorithm with Negative Numbers Only Check
//   -  Handles arrays where all numbers are negative.
//   -  A variation to address a specific edge case.
//   - Real-world application:  Analyzing a series of financial losses to minimize the largest loss.
int kadaneWithNegativeCheck(const std::vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    bool allNegative = true;

    for (int num : nums) {
        if (num > 0) {
            allNegative = false;
        }
        maxEndingHere = std::max(num, maxEndingHere + num);
        maxSoFar = std::max(maxSoFar, maxEndingHere);
    }
    if (allNegative)
    {
        int maxVal = INT_MIN;
         for(int num: nums){
            maxVal = std::max(maxVal, num);
         }
         return maxVal;
    }
    return maxSoFar;
}

// 5. Kadane's Algorithm for 2D Arrays (Maximum Submatrix Sum)
//   -  Extends Kadane's algorithm to find the maximum sum submatrix in a 2D array.
//   -  A more complex application of the core idea.
//   - Real-world application: Image processing, finding the brightest region in an image represented as a 2D array of pixel intensities.
int maxSubmatrixSum(const std::vector<std::vector<int>>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return 0;
    int cols = matrix[0].size();
    int maxSum = INT_MIN;

    for (int left = 0; left < cols; ++left) {
        std::vector<int> temp(rows, 0); // Temporary array to store column sums

        for (int right = left; right < cols; ++right) {
            // Calculate the sum of elements for each row between 'left' and 'right' columns.
            for (int i = 0; i < rows; ++i) {
                temp[i] += matrix[i][right];
            }

            // Apply 1D Kadane's algorithm to the temporary array 'temp'.
            int currentMax = kadaneBasic(temp);
            maxSum = std::max(maxSum, currentMax);
        }
    }
    return maxSum;
}

int main() {
    // Example Usage
    std::vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "1. Basic Kadane's Algorithm: " << kadaneBasic(nums1) << std::endl; // Output: 6

    std::vector<int> nums2 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::pair<int, std::pair<int, int>> result2 = kadaneWithIndices(nums2);
    std::cout << "2. Kadane's Algorithm with Indices: Sum = " << result2.first
              << ", Start = " << result2.second.first << ", End = " << result2.second.second << std::endl; // Output: Sum = 6, Start = 3, End = 6

    std::vector<int> nums3 = {5, -3, 5};
    std::cout << "3. Kadane's Algorithm for Circular Subarrays: " << maxSubarraySumCircular(nums3) << std::endl; // Output: 7

    std::vector<int> nums4 = {-2, -3, -4, -1, -5};
    std::cout << "4. Kadane's Algorithm with Negative Numbers Only Check: " << kadaneWithNegativeCheck(nums4) << std::endl; // Output: -1

    std::vector<std::vector<int>> matrix = {
        {1, 2, -1, -4, -20},
        {-8, -3, 4, 2, 1},
        {3, 8, 10, 1, 3},
        {-4, -1, 1, 7, -6}
    };
    std::cout << "5. Kadane's Algorithm for 2D Arrays: " << maxSubmatrixSum(matrix) << std::endl; // Output: 29

    return 0;
}
