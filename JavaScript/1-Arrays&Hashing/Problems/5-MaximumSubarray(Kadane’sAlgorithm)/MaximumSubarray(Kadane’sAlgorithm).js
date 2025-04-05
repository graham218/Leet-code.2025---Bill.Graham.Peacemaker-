/*
Problem:
Given an integer array nums, find the contiguous subarray (containing at least one number)
which has the largest sum and return its sum.

Example 1:
Input: [−2,1,−3,4,−1,2,1,−5,4]
Output: 6
Explanation: [4,−1,2,1] has the largest sum = 6.

Example 2:
Input: [1]
Output: 1

Example 3:
Input: [5,4,-1,7,8]
Output: 23
*/

/**
 * Approach 1: Brute Force
 *
 * Generate all possible subarrays and calculate the sum of each subarray.
 * Keep track of the maximum sum encountered.  This is the most straightforward
 * approach, but it's also the least efficient due to its triple nested loop.
 *
 * Time Complexity: O(n^3), where n is the length of the input array `nums`.
 * Space Complexity: O(1), constant extra space.
 */
function maxSubarrayBruteForce(nums) {
    let maxSum = -Infinity; // Initialize with negative infinity to handle arrays with all negative numbers

    for (let i = 0; i < nums.length; i++) {
        for (let j = i; j < nums.length; j++) {
            let currentSum = 0;
            for (let k = i; k <= j; k++) {
                currentSum += nums[k];
            }
            maxSum = Math.max(maxSum, currentSum);
        }
    }
    return maxSum;
}

/**
 * Approach 2: Slightly Optimized Brute Force
 *
 * This approach is similar to the brute force approach, but it eliminates one loop.
 * Instead of recalculating the sum of the subarray in the innermost loop, it
 * incrementally adds elements.
 *
 * Time Complexity: O(n^2), where n is the length of the input array `nums`.
 * Space Complexity: O(1), constant extra space.
 */
function maxSubarrayOptimizedBruteForce(nums) {
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
 * Approach 3: Divide and Conquer
 *
 * Recursively divide the array into two halves and find the maximum subarray sum in each half.
 * The maximum subarray sum can either be entirely in the left half, entirely in the right half,
 * or cross the midpoint.  The crossing subarray requires a separate calculation.
 *
 * Time Complexity: O(n log n), where n is the length of the input array `nums`.
 * Space Complexity: O(log n), due to the recursive call stack.
 */
function maxSubarrayDivideAndConquer(nums, left = 0, right = nums.length - 1) {
    if (left === right) {
        return nums[left];
    }

    const mid = Math.floor((left + right) / 2);
    const leftSum = maxSubarrayDivideAndConquer(nums, left, mid);
    const rightSum = maxSubarrayDivideAndConquer(nums, mid + 1, right);
    const crossSum = maxCrossingSum(nums, left, mid, right);

    return Math.max(leftSum, rightSum, crossSum);
}

function maxCrossingSum(nums, left, mid, right) {
    let leftSum = -Infinity;
    let currentSum = 0;
    for (let i = mid; i >= left; i--) {
        currentSum += nums[i];
        leftSum = Math.max(leftSum, currentSum);
    }

    let rightSum = -Infinity;
    currentSum = 0;
    for (let i = mid + 1; i <= right; i++) {
        currentSum += nums[i];
        rightSum = Math.max(rightSum, currentSum);
    }

    return leftSum + rightSum;
}

/**
 * Approach 4: Kadane's Algorithm (Dynamic Programming)
 *
 * Kadane's algorithm is the most efficient way to solve the maximum subarray problem.
 * It uses dynamic programming to keep track of the maximum subarray sum ending at each position.
 * The core idea is that if the current subarray sum becomes negative, it's better to start a new
 * subarray from the next element.
 *
 * Time Complexity: O(n), where n is the length of the input array `nums`.
 * Space Complexity: O(1), constant extra space.
 */
function maxSubarrayKadane(nums) {
    let maxSoFar = -Infinity;
    let maxEndingHere = 0;

    for (let i = 0; i < nums.length; i++) {
        maxEndingHere = Math.max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = Math.max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

/**
 * Approach 5: Kadane's Algorithm (with start and end index)
 *
 * This is a variation of Kadane's Algorithm that also tracks the start and end indices
 * of the maximum subarray.
 *
 * Time Complexity: O(n), where n is the length of the input array `nums`.
 * Space Complexity: O(1), constant extra space.
 */
function maxSubarrayKadaneWithIndex(nums) {
    let maxSoFar = -Infinity;
    let maxEndingHere = 0;
    let start = 0;
    let end = 0;
    let tempStart = 0;

    for (let i = 0; i < nums.length; i++) {
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
    return { maxSum: maxSoFar, startIndex: start, endIndex: end };
}


// Example Usage and Output
const nums1 = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
const nums2 = [1];
const nums3 = [5, 4, -1, 7, 8];
const nums4 = [-2, -3, -4, -5];
const nums5 = [-2, 1, -3, 4, -1, 2, 1, -5, 4];


console.log("Input: [-2, 1, -3, 4, -1, 2, 1, -5, 4]");
console.log("Brute Force:", maxSubarrayBruteForce(nums1));             // Output: 6
console.log("Optimized Brute Force:", maxSubarrayOptimizedBruteForce(nums1));  // Output: 6
console.log("Divide and Conquer:", maxSubarrayDivideAndConquer(nums1));       // Output: 6
console.log("Kadane's Algorithm:", maxSubarrayKadane(nums1));           // Output: 6
console.log("Kadane's with Index:", maxSubarrayKadaneWithIndex(nums1)); // Output: { maxSum: 6, startIndex: 3, endIndex: 6 }

console.log("\nInput: [1]");
console.log("Brute Force:", maxSubarrayBruteForce(nums2));             // Output: 1
console.log("Optimized Brute Force:", maxSubarrayOptimizedBruteForce(nums2));  // Output: 1
console.log("Divide and Conquer:", maxSubarrayDivideAndConquer(nums2));       // Output: 1
console.log("Kadane's Algorithm:", maxSubarrayKadane(nums2));           // Output: 1
console.log("Kadane's with Index:", maxSubarrayKadaneWithIndex(nums2)); // Output: { maxSum: 1, startIndex: 0, endIndex: 0 }

console.log("\nInput: [5, 4, -1, 7, 8]");
console.log("Brute Force:", maxSubarrayBruteForce(nums3));             // Output: 23
console.log("Optimized Brute Force:", maxSubarrayOptimizedBruteForce(nums3));  // Output: 23
console.log("Divide and Conquer:", maxSubarrayDivideAndConquer(nums3));       // Output: 23
console.log("Kadane's Algorithm:", maxSubarrayKadane(nums3));           // Output: 23
console.log("Kadane's with Index:", maxSubarrayKadaneWithIndex(nums3)); // Output: { maxSum: 23, startIndex: 0, endIndex: 4 }

console.log("\nInput: [-2, -3, -4, -5]");
console.log("Brute Force:", maxSubarrayBruteForce(nums4));             // Output: -2
console.log("Optimized Brute Force:", maxSubarrayOptimizedBruteForce(nums4));  // Output: -2
console.log("Divide and Conquer:", maxSubarrayDivideAndConquer(nums4));       // Output: -2
console.log("Kadane's Algorithm:", maxSubarrayKadane(nums4));           // Output: -2
console.log("Kadane's with Index:", maxSubarrayKadaneWithIndex(nums4)); // Output: { maxSum: -2, startIndex: 0, endIndex: 0 }
