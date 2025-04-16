/**
 * Binary Search: Find Minimum in Rotated Sorted Array
 *
 * Problem:
 *
 * Given a sorted array that has been rotated n number of times, find the minimum element in it.
 *
 * Example:
 *
 * Input: [3, 4, 5, 1, 2]
 * Output: 1
 *
 * Constraints:
 *
 * -   The array will not have duplicate elements.
 * -   The array is sorted but rotated.
 * -   The rotation is in the clockwise direction.
 *
 *
 * Approaches:
 *
 * 1.  **Linear Search:**
 * -   Iterate through the array and find the minimum element.
 * -   Time Complexity: O(n)
 * -   Space Complexity: O(1)
 *
 * 2.  **Binary Search (Optimized):**
 * -   Use binary search to find the minimum element.
 * -   The key idea is that the rotated array has two sorted parts.
 * -   We can use binary search to find the point where the two sorted parts meet, which is the minimum element.
 * -   Time Complexity: O(log n)
 * -   Space Complexity: O(1)
 *
 * 3.  **Recursive Binary Search:**
 * -   Implement the binary search approach using recursion.
 * -   Time Complexity: O(log n)
 * -   Space Complexity: O(log n) (due to the call stack)
 *
 * 4. **Binary Search with Duplicates Handling:**
 * - Handles cases where the rotated array contains duplicate elements.
 * - Time Complexity: O(log n) in the average case, O(n) in the worst case.
 * - Space Complexity: O(1)
 *
 * 5. **ES6 Optimized Binary Search**
 * - Uses modern ES6 syntax for a more concise implementation.
 * - Time Complexity: O(log n)
 * - Space Complexity: O(1)
 */

/**
 * 1. Linear Search Approach
 *
 * @param {number[]} nums The rotated sorted array.
 * @returns {number} The minimum element in the array.
 */
function findMinimumLinearSearch(nums) {
    if (!nums || nums.length === 0) {
        return undefined; // Handle empty array case
    }

    let min = nums[0];
    for (let i = 1; i < nums.length; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
    }
    return min;
}

/**
 * 2. Binary Search (Optimized) Approach
 *
 * @param {number[]} nums The rotated sorted array.
 * @returns {number} The minimum element in the array.
 */
function findMinimumBinarySearch(nums) {
    if (!nums || nums.length === 0) {
        return undefined; // Handle empty array case
    }

    let left = 0;
    let right = nums.length - 1;

    while (left < right) {
        const mid = Math.floor((left + right) / 2);

        // If the middle element is greater than the rightmost element,
        // the minimum element is in the right half of the array.
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else {
            // Otherwise, the minimum element is in the left half or is the middle element.
            right = mid;
        }
    }

    // At the end of the loop, left and right will be pointing to the minimum element.
    return nums[left];
}

/**
 * 3. Recursive Binary Search Approach
 *
 * @param {number[]} nums The rotated sorted array.
 * @param {number} left The left index of the search range.
 * @param {number} right The right index of the search range.
 * @returns {number} The minimum element in the array.
 */
function findMinimumRecursiveBinarySearch(nums, left, right) {
    if (!nums || nums.length === 0) {
        return undefined; // Handle empty array
    }
    if (left === right) {
        return nums[left];
    }

    const mid = Math.floor((left + right) / 2);

    if (nums[mid] > nums[right]) {
        return findMinimumRecursiveBinarySearch(nums, mid + 1, right);
    } else {
        return findMinimumRecursiveBinarySearch(nums, left, mid);
    }
}

/**
 * 4. Binary Search with Duplicates Handling
 *
 * @param {number[]} nums The rotated sorted array with possible duplicates.
 * @returns {number} The minimum element in the array.
 */
function findMinimumWithDuplicates(nums) {
    if (!nums || nums.length === 0) {
        return undefined;
    }

    let left = 0;
    let right = nums.length - 1;

    while (left < right) {
        const mid = Math.floor((left + right) / 2);

        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            // Handle the case with duplicates: if nums[mid] == nums[right], we can't
            // be sure which half contains the minimum, so we shrink the search space
            // by one.
            right--;
        }
    }
    return nums[left];
}

/**
 * 5. ES6 Optimized Binary Search
 *
 * @param {number[]} nums The rotated sorted array.
 * @returns {number} The minimum element.
 */
function findMinimumES6(nums) {
    if (!nums || nums.length === 0) return undefined;

    let [left, right] = [0, nums.length - 1];

    while (left < right) {
        const mid = (left + right) >>> 1; // Use bitwise for slightly faster division
        if (nums[mid] > nums[right]) left = mid + 1;
        else right = mid;
    }
    return nums[left];
}

// Example usage and console logs
const rotatedArray1 = [3, 4, 5, 1, 2];
const rotatedArray2 = [4, 5, 6, 7, 0, 1, 2];
const rotatedArray3 = [11, 13, 15, 17, 10];
const rotatedArray4 = [2, 2, 2, 0, 2]; // Example with duplicates
const rotatedArray5 = [10, 1, 10, 10, 10]; // Example with duplicates

console.log("Test Case 1:");
console.log("Input:", rotatedArray1);
console.log("Linear Search:", findMinimumLinearSearch(rotatedArray1)); // Output: 1
console.log("Binary Search:", findMinimumBinarySearch(rotatedArray1)); // Output: 1
console.log("Recursive Binary Search:", findMinimumRecursiveBinarySearch(rotatedArray1, 0, rotatedArray1.length - 1)); // Output: 1
console.log("Binary Search with Duplicates:", findMinimumWithDuplicates(rotatedArray1)); // Output: 1
console.log("ES6 Optimized Binary Search:", findMinimumES6(rotatedArray1)); // Output: 1

console.log("\nTest Case 2:");
console.log("Input:", rotatedArray2);
console.log("Linear Search:", findMinimumLinearSearch(rotatedArray2)); // Output: 0
console.log("Binary Search:", findMinimumBinarySearch(rotatedArray2)); // Output: 0
console.log("Recursive Binary Search:", findMinimumRecursiveBinarySearch(rotatedArray2, 0, rotatedArray2.length - 1)); // Output: 0
console.log("Binary Search with Duplicates:", findMinimumWithDuplicates(rotatedArray2)); // Output: 0
console.log("ES6 Optimized Binary Search:", findMinimumES6(rotatedArray2)); // Output: 0

console.log("\nTest Case 3:");
console.log("Input:", rotatedArray3);
console.log("Linear Search:", findMinimumLinearSearch(rotatedArray3)); // Output: 10
console.log("Binary Search:", findMinimumBinarySearch(rotatedArray3)); // Output: 10
console.log("Recursive Binary Search:", findMinimumRecursiveBinarySearch(rotatedArray3, 0, rotatedArray3.length - 1)); // Output: 10
console.log("Binary Search with Duplicates:", findMinimumWithDuplicates(rotatedArray3)); // Output: 10
console.log("ES6 Optimized Binary Search:", findMinimumES6(rotatedArray3)); // Output: 10

console.log("\nTest Case 4 (Duplicates):");
console.log("Input:", rotatedArray4);
console.log("Linear Search:", findMinimumLinearSearch(rotatedArray4)); // Output: 0
console.log("Binary Search:", findMinimumBinarySearch(rotatedArray4)); // Output: 0
console.log("Recursive Binary Search:", findMinimumRecursiveBinarySearch(rotatedArray4, 0, rotatedArray4.length - 1)); // Output: 0
console.log("Binary Search with Duplicates:", findMinimumWithDuplicates(rotatedArray4)); // Output: 0
console.log("ES6 Optimized Binary Search:", findMinimumES6(rotatedArray4)); // Output: 0

console.log("\nTest Case 5 (Duplicates):");
console.log("Input:", rotatedArray5);
console.log("Linear Search:", findMinimumLinearSearch(rotatedArray5));
console.log("Binary Search:", findMinimumBinarySearch(rotatedArray5));
console.log("Recursive Binary Search:", findMinimumRecursiveBinarySearch(rotatedArray5, 0, rotatedArray5.length - 1));
console.log("Binary Search with Duplicates:", findMinimumWithDuplicates(rotatedArray5));
console.log("ES6 Optimized Binary Search:", findMinimumES6(rotatedArray5));
