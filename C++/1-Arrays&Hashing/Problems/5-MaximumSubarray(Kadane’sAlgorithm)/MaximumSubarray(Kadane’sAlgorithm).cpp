#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // For INT_MIN

using namespace std;

// Approach 1: Basic Kadane's Algorithm
// - Iterates through the array, keeping track of the current maximum sum
//   ending at the current position, and the overall maximum sum.
// - Time Complexity: O(n), Space Complexity: O(1)
int maxSubarrayKadane(const vector<int>& nums) {
    int maxSoFar = INT_MIN; // Initialize with the smallest possible integer
    int currentMax = 0;

    for (int num : nums) {
        currentMax = max(num, currentMax + num); // Decide to start a new subarray or extend the current one
        maxSoFar = max(maxSoFar, currentMax);    // Update the overall maximum sum
    }

    return maxSoFar;
}

// Approach 2: Kadane's Algorithm with Start and End Indices
// - Tracks the start and end indices of the maximum subarray.
// - Time Complexity: O(n), Space Complexity: O(1)
pair<int, pair<int, int>> maxSubarrayKadaneWithIndices(const vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int currentMax = 0;
    int start = 0;
    int end = 0;
    int tempStart = 0; // Temporary start index

    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > currentMax + nums[i]) {
            currentMax = nums[i];
            tempStart = i; // Start a new subarray
        } else {
            currentMax += nums[i]; // Extend the current subarray
        }

        if (currentMax > maxSoFar) {
            maxSoFar = currentMax;
            start = tempStart; // Update start and end indices
            end = i;
        }
    }
    return {maxSoFar, {start, end}};
}

// Approach 3: Kadane's Algorithm with Negative Number Handling
// - Handles arrays where all numbers might be negative.
// - Time Complexity: O(n), Space Complexity: O(1)
int maxSubarrayKadaneHandleNegative(const vector<int>& nums) {
    int maxSoFar = nums[0]; // Important: Initialize with the first element
    int currentMax = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        currentMax = max(nums[i], currentMax + nums[i]);
        maxSoFar = max(maxSoFar, currentMax);
    }
    return maxSoFar;
}

// Approach 4: Divide and Conquer (Recursive)
// - Recursively divides the array into two halves, finds the maximum subarray
//   in each half, and then finds the maximum subarray that crosses the midpoint.
// - Time Complexity: O(n log n), Space Complexity: O(log n) (due to recursion)
int maxCrossingSubarray(const vector<int>& nums, int low, int mid, int high) {
    int sum = 0;
    int leftSum = INT_MIN;
    for (int i = mid; i >= low; --i) {
        sum += nums[i];
        leftSum = max(leftSum, sum);
    }

    sum = 0;
    int rightSum = INT_MIN;
    for (int i = mid + 1; i <= high; ++i) {
        sum += nums[i];
        rightSum = max(rightSum, sum);
    }

    return leftSum + rightSum;
}

int maxSubarrayDivideConquer(const vector<int>& nums, int low, int high) {
    if (low == high) {
        return nums[low];
    }

    int mid = (low + high) / 2;
    int leftSum = maxSubarrayDivideConquer(nums, low, mid);
    int rightSum = maxSubarrayDivideConquer(nums, mid + 1, high);
    int crossSum = maxCrossingSubarray(nums, low, mid, high);

    return max(max(leftSum, rightSum), crossSum);
}

// Wrapper function for the divide and conquer approach
int maxSubarrayDivideConquerWrapper(const vector<int>& nums) {
    if (nums.empty()) return 0;
    return maxSubarrayDivideConquer(nums, 0, nums.size() - 1);
}

// Approach 5: Dynamic Programming (Less Efficient)
// - Uses a DP table (vector) to store the maximum subarray sum ending at each index.
// - This approach is less efficient than Kadane's but illustrates dynamic programming.
// - Time Complexity: O(n), Space Complexity: O(n)
int maxSubarrayDP(const vector<int>& nums) {
    if (nums.empty()) return 0;

    vector<int> dp(nums.size());
    dp[0] = nums[0]; // Base case: max subarray sum ending at index 0 is nums[0]
    int maxSoFar = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        dp[i] = max(nums[i], dp[i - 1] + nums[i]); // Recurrence relation
        maxSoFar = max(maxSoFar, dp[i]);
    }
    return maxSoFar;
}

int main() {
    // Test case
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    // Test all 5 approaches
    cout << "Maximum Subarray Sum (Kadane's): " << maxSubarrayKadane(nums) << endl;

    pair<int, pair<int, int>> kadaneResult = maxSubarrayKadaneWithIndices(nums);
    cout << "Maximum Subarray Sum (Kadane's with Indices): " << kadaneResult.first
              << ", Start Index: " << kadaneResult.second.first
              << ", End Index: " << kadaneResult.second.second << endl;

    cout << "Maximum Subarray Sum (Kadane's with Negative Handling): " << maxSubarrayKadaneHandleNegative(nums) << endl;

    cout << "Maximum Subarray Sum (Divide and Conquer): " << maxSubarrayDivideConquerWrapper(nums) << endl;

    cout << "Maximum Subarray Sum (Dynamic Programming): " << maxSubarrayDP(nums) << endl;

    // Test case with all negative numbers
    vector<int> negativeNums = {-1, -2, -3, -4, -5};
    cout << "\nMaximum Subarray Sum with all negative numbers:\n";
    cout << "Maximum Subarray Sum (Kadane's): " << maxSubarrayKadane(negativeNums) << endl;
    cout << "Maximum Subarray Sum (Kadane's with Negative Handling): " << maxSubarrayKadaneHandleNegative(negativeNums) << endl;
    cout << "Maximum Subarray Sum (Divide and Conquer): " << maxSubarrayDivideConquerWrapper(negativeNums) << endl;
    cout << "Maximum Subarray Sum (Dynamic Programming): " << maxSubarrayDP(negativeNums) << endl;

    return 0;
}
