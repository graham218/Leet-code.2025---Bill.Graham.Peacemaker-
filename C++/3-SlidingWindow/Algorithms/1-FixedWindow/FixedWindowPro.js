/*
Sliding Window to Fixed Window Problem:

This problem involves using a sliding window technique, but with a twist.  Instead of the window size being variable, it's fixed.  The goal is to efficiently compute some function over all fixed-size subarrays (windows) of a given array.

Here's the breakdown:

* Input: An array (arr) and a window size (k).
* Output:  Depends on the specific problem (e.g., max sum of each window, average of each window).
* Constraint: The window size (k) is fixed.

Why Sliding Window?

The sliding window technique optimizes solutions by avoiding redundant calculations.  Instead of recalculating the function for each window from scratch, it reuses the computation from the previous window.

5 Different Approaches (with real-world-ish examples):

1.  Maximum Sum of Subarray of Size K (Basic Sliding Window)
2.  Minimum Average of Subarray of Size K (Slight Variation)
3.  Maximum Product of Subarray of Size K (Handles Negatives)
4.  Counting Occurrences of a Value in Each Subarray of Size K
5.  Checking for Subarray with Sum Equal to Target (with Fixed Size K)
*/

console.log("Sliding Window to Fixed Window - 5 Approaches");

// 1. Maximum Sum of Subarray of Size K
//    Real-world application: Finding the maximum revenue in a fixed period (e.g., weekly sales).
function maxSumSubarray(arr, k) {
    if (k > arr.length) {
        console.log("1. Max Sum Subarray: Window size exceeds array length.");
        return null; // Or throw an error: throw new Error("...");
    }

    let max_sum = 0;
    let current_sum = 0;

    // Calculate the sum of the first window
    for (let i = 0; i < k; i++) {
        current_sum += arr[i];
    }
    max_sum = current_sum;

    // Slide the window through the rest of the array
    for (let i = k; i < arr.length; i++) {
        current_sum = current_sum - arr[i - k] + arr[i]; // Subtract the first element of the previous window and add the last element of the current window.
        max_sum = Math.max(max_sum, current_sum);
    }

    console.log(`1. Max Sum Subarray: Max sum of subarray of size ${k} is ${max_sum}`);
    return max_sum;
}

// Example usage:
const array1 = [1, 4, 2, 10, 23, 3, 1, 0, 20];
const k1 = 4;
maxSumSubarray(array1, k1); // Output: 39 (10 + 23 + 3 + 1)

const array1_negative = [-1, -4, -2, -10, -23, -3, -1, -0, -20];
maxSumSubarray(array1_negative, k1); // Output: -7


// 2. Minimum Average of Subarray of Size K
//    Real-world application: Finding the minimum average daily temperature over a fixed number of days.
function minAvgSubarray(arr, k) {
    if (k > arr.length) {
        console.log("2. Min Avg Subarray: Window size exceeds array length.");
        return null;
    }

    let min_sum = Infinity;
    let current_sum = 0;

    for (let i = 0; i < k; i++) {
        current_sum += arr[i];
    }
    min_sum = current_sum;

    for (let i = k; i < arr.length; i++) {
        current_sum = current_sum - arr[i - k] + arr[i];
        min_sum = Math.min(min_sum, current_sum);
    }

    const min_average = min_sum / k;
    console.log(`2. Min Avg Subarray: Minimum average of subarray of size ${k} is ${min_average}`);
    return min_average;
}

// Example usage:
const array2 = [1, 12, -5, -6, 50, 3];
const k2 = 4;
minAvgSubarray(array2, k2); // Output: -2.5  ((-5 + -6 + 50 + 3) / 4)


// 3. Maximum Product of Subarray of Size K
//   Real-world application: Finding the maximum profit over a fixed number of trading days.  Handles negative stock prices.
function maxProductSubarray(arr, k) {
    if (k > arr.length) {
        console.log("3. Max Product Subarray: Window size exceeds array length.");
        return null;
    }

    let max_product = -Infinity; // Initialize to negative infinity to handle arrays with negative numbers
    let current_product = 1;

    for (let i = 0; i < k; i++) {
        current_product *= arr[i];
    }
    max_product = current_product;

    for (let i = k; i < arr.length; i++) {
        current_product = (current_product / arr[i - k]) * arr[i];
        max_product = Math.max(max_product, current_product);
    }
    console.log(`3. Max Product Subarray: Maximum product of subarray of size ${k} is ${max_product}`);
    return max_product;
}

// Example usage:
const array3 = [1, -4, 2, -10, 23, 3, 1, 0, 20];
const k3 = 4;
maxProductSubarray(array3, k3); // Output: 60 (2 * -10 * 23 * 3)

const array3_with_zeros = [1, -4, 2, 0, 23, 3, 1, 0, 20];
maxProductSubarray(array3_with_zeros, k3); // Output: 0

const array3_all_negative = [-1, -2, -3, -4];
const k3_all_negative = 2;
maxProductSubarray(array3_all_negative, k3_all_negative); // Output: 6


// 4. Counting Occurrences of a Value in Each Subarray of Size K
//    Real-world application: Counting how many times a specific event occurs in a fixed time window (e.g., website visits in consecutive hours).
function countOccurrences(arr, k, targetValue) {
    if (k > arr.length) {
        console.log("4. Count Occurrences: Window size exceeds array length.");
        return [];
    }

    const counts = [];
    let current_count = 0;

    for (let i = 0; i < k; i++) {
        if (arr[i] === targetValue) {
            current_count++;
        }
    }
    counts.push(current_count);

    for (let i = k; i < arr.length; i++) {
        if (arr[i - k] === targetValue) {
            current_count--;
        }
        if (arr[i] === targetValue) {
            current_count++;
        }
        counts.push(current_count);
    }
    console.log(`4. Count Occurrences: Occurrences of ${targetValue} in each subarray of size ${k} are: ${counts.join(', ')}`);
    return counts;
}

// Example usage:
const array4 = [1, 2, 3, 2, 1, 4, 2, 5, 2];
const k4 = 3;
const targetValue4 = 2;
countOccurrences(array4, k4, targetValue4); // Output: [ 1, 1, 2, 1, 1, 1, 2 ]


// 5. Checking for Subarray with Sum Equal to Target (with Fixed Size K)
//   Real-world application: Detecting if there's a fixed-length period where a certain financial target is met (e.g., daily sales reaching a goal).
function hasSubarrayWithSum(arr, k, targetSum) {
    if (k > arr.length) {
        console.log("5. Subarray with Sum: Window size exceeds array length.");
        return false;
    }

    let current_sum = 0;
    for (let i = 0; i < k; i++) {
        current_sum += arr[i];
    }

    if (current_sum === targetSum) {
        console.log(`5. Subarray with Sum: Found subarray with sum ${targetSum}: [${arr.slice(0,k).join(', ')}]`);
        return true;
    }

    for (let i = k; i < arr.length; i++) {
        current_sum = current_sum - arr[i - k] + arr[i];
        if (current_sum === targetSum) {
            console.log(`5. Subarray with Sum: Found subarray with sum ${targetSum}: [${arr.slice(i-k+1,i+1).join(', ')}]`);
            return true;
        }
    }

    console.log(`5. Subarray with Sum: No subarray with sum ${targetSum} found.`);
    return false;
}

// Example usage:
const array5 = [2, 3, 4, 1, 5, 6];
const k5 = 3;
const targetSum5 = 10;
hasSubarrayWithSum(array5, k5, targetSum5); // Output: true ([3, 4, 1])

const targetSum5_not_found = 15;
hasSubarrayWithSum(array5, k5, targetSum5_not_found); // Output: false
