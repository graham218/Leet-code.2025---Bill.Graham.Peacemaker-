/*
Problem:
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Example 2:
Input: nums = [1]
Output: 1

Example 3:
Input: nums = [5,4,-1,7,8]
Output: 23

Constraints:
-   1 <= nums.length <= 10^5
-   -10^4 <= nums[i] <= 10^4

Real-world Applications:
1.  **Financial Analysis**: Identifying periods of maximum profit in stock prices.  `nums` represents daily stock price changes.
2.  **Image Processing**: Finding the brightest region in an image.  `nums` represents pixel intensities.
3.  **Signal Processing**: Detecting the strongest signal in a noisy data stream. `nums` represents signal amplitudes.
4.  **Bioinformatics**: Analyzing DNA sequences to find regions with the highest similarity score. `nums` represents similarity scores.
5.  **Weather Forecasting**: Finding periods with the highest temperature increase. `nums` represents daily temperature changes.
6.  **Sports Analytics**: Determining the best performance streak of a player or team. `nums` represents performance metrics.
*/

/**
 * Approach 1: Brute Force
 *
 * Description:
 * The most straightforward approach.  Iterate through all possible subarrays
 * and calculate the sum of each subarray. Keep track of the maximum sum found so far.
 *
 * Time Complexity: O(n^2) - Nested loops to generate all subarrays.
 * Space Complexity: O(1) - Only a few variables are used.
 */
function maxSubarray_bruteforce(nums) {
    let maxSum = -Infinity; // Initialize with negative infinity to handle negative numbers

    for (let i = 0; i < nums.length; i++) {
        let currentSum = 0;
        for (let j = i; j < nums.length; j++) {
            currentSum += nums[j];
            maxSum = Math.max(maxSum, currentSum);
        }
    }
    return maxSum;
}

/**
 * Approach 2: Dynamic Programming (Slightly Optimized Brute Force)
 *
 * Description:
 * A slight optimization over brute force. Instead of recalculating the sum of each
 * subarray from scratch, we use the sum of the previous subarray.
 *
 * Time Complexity: O(n^2) - Still nested loops, but with some optimization.
 * Space Complexity: O(1) - Only a few variables are used.
 */
function maxSubarray_dp_slow(nums) {
    let maxSum = -Infinity;

    for (let i = 0; i < nums.length; i++) {
        let currentSum = 0;
        for (let j = i; j < nums.length; j++) {
            currentSum += nums[j];
            maxSum = Math.max(maxSum, currentSum);
        }
    }
    return maxSum;
}


/**
 * Approach 3: Kadane's Algorithm
 *
 * Description:
 * Kadane's algorithm is the standard, efficient solution to the maximum subarray problem.
 * It iterates through the array, keeping track of the maximum sum ending at the current position
 * (`currentSum`) and the overall maximum sum (`maxSum`).  If `currentSum` becomes negative,
 * it's reset to 0 because a negative sum will never contribute to a larger maximum subarray.
 *
 * Time Complexity: O(n) - Single pass through the array.
 * Space Complexity: O(1) - Only a few variables are used.
 */
function maxSubarray_kadane(nums) {
    let maxSum = -Infinity;
    let currentSum = 0;

    for (let i = 0; i < nums.length; i++) {
        currentSum = Math.max(nums[i], currentSum + nums[i]); // 핵심
        maxSum = Math.max(maxSum, currentSum);
    }
    return maxSum;
}

/**
 * Approach 4: Kadane's Algorithm (with start and end index)
 *
 * Description:
 * Kadane's algorithm, but also keeps track of the start and end indices of the maximum subarray.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function maxSubarray_kadane_indices(nums) {
    let maxSum = -Infinity;
    let currentSum = 0;
    let maxStartIndex = 0;
    let maxEndIndex = 0;
    let currentStartIndex = 0;

    for (let i = 0; i < nums.length; i++) {
        if (nums[i] > currentSum + nums[i]) {
            currentSum = nums[i];
            currentStartIndex = i;
        } else {
            currentSum += nums[i];
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
            maxStartIndex = currentStartIndex;
            maxEndIndex = i;
        }
    }
    return {
        maxSum: maxSum,
        startIndex: maxStartIndex,
        endIndex: maxEndIndex,
    };
}

/**
 * Approach 5: Divide and Conquer
 *
 * Description:
 * A divide-and-conquer approach.  The array is recursively divided into two halves.
 * The maximum subarray can either be entirely in the left half, entirely in the right half,
 * or cross the middle.  The maximum subarray crossing the middle is found in linear time.
 *
 * Time Complexity: O(n log n) - Divide and conquer.
 * Space Complexity: O(log n) -  Due to the recursive call stack.
 */
function maxSubarray_divideAndConquer(nums) {
    if (nums.length === 0) {
        return -Infinity;
    }

    function findMaxCrossingSubarray(arr, low, mid, high) {
        let leftSum = -Infinity;
        let currentSum = 0;
        for (let i = mid; i >= low; i--) {
            currentSum += arr[i];
            leftSum = Math.max(leftSum, currentSum);
        }

        let rightSum = -Infinity;
        currentSum = 0;
        for (let i = mid + 1; i <= high; i++) {
            currentSum += arr[i];
            rightSum = Math.max(rightSum, currentSum);
        }
        return leftSum + rightSum;
    }

    function findMaxSubarray(arr, low, high) {
        if (low === high) {
            return arr[low];
        }
        const mid = Math.floor((low + high) / 2);
        const leftSum = findMaxSubarray(arr, low, mid);
        const rightSum = findMaxSubarray(arr, mid + 1, high);
        const crossSum = findMaxCrossingSubarray(arr, low, mid, high);
        return Math.max(leftSum, rightSum, crossSum);
    }

    return findMaxSubarray(nums, 0, nums.length - 1);
}

/**
 * Approach 6: Dynamic Programming (Explicit Array)
 *
 * Description:
 * Classic dynamic programming approach, similar to Kadane's, but uses an explicit
 * DP array `dp`.  `dp[i]` stores the maximum sum of a subarray ending at index `i`.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n) -  Uses a DP array of size n.
 */
function maxSubarray_dp_array(nums) {
    const n = nums.length;
    const dp = new Array(n);
    dp[0] = nums[0];  // Base case: max subarray ending at index 0 is just nums[0]
    let maxSum = nums[0];

    for (let i = 1; i < n; i++) {
        dp[i] = Math.max(nums[i], dp[i - 1] + nums[i]); // 핵심 DP transition
        maxSum = Math.max(maxSum, dp[i]);
    }
    return maxSum;
}



// Example Usage and Output
const nums1 = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
const nums2 = [1];
const nums3 = [5, 4, -1, 7, 8];

console.log("Input: [-2, 1, -3, 4, -1, 2, 1, -5, 4]");
console.log("Brute Force:", maxSubarray_bruteforce(nums1));          // Output: 6
console.log("DP (Slow):", maxSubarray_dp_slow(nums1));              // Output: 6
console.log("Kadane's:", maxSubarray_kadane(nums1));                // Output: 6
console.log("Kadane's with Indices:", maxSubarray_kadane_indices(nums1)); // Output: { maxSum: 6, startIndex: 3, endIndex: 6 }
console.log("Divide and Conquer:", maxSubarray_divideAndConquer(nums1));  // Output: 6
console.log("DP Array:", maxSubarray_dp_array(nums1));                // Output: 6

console.log("\nInput: [1]");
console.log("Brute Force:", maxSubarray_bruteforce(nums2));          // Output: 1
console.log("DP (Slow):", maxSubarray_dp_slow(nums2));              // Output: 1
console.log("Kadane's:", maxSubarray_kadane(nums2));                // Output: 1
console.log("Kadane's with Indices:", maxSubarray_kadane_indices(nums2)); // Output: { maxSum: 1, startIndex: 0, endIndex: 0 }
console.log("Divide and Conquer:", maxSubarray_divideAndConquer(nums2));  // Output: 1
console.log("DP Array:", maxSubarray_dp_array(nums2));                // Output: 1

console.log("\nInput: [5, 4, -1, 7, 8]");
console.log("Brute Force:", maxSubarray_bruteforce(nums3));          // Output: 23
console.log("DP (Slow):", maxSubarray_dp_slow(nums3));              // Output: 23
console.log("Kadane's:", maxSubarray_kadane(nums3));                // Output: 23
console.log("Kadane's with Indices:", maxSubarray_kadane_indices(nums3)); // Output: { maxSum: 23, startIndex: 0, endIndex: 4 }
console.log("Divide and Conquer:", maxSubarray_divideAndConquer(nums3));  // Output: 23
console.log("DP Array:", maxSubarray_dp_array(nums3));                // Output: 23
