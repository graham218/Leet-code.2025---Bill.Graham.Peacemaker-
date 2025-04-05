/**
 * 1. Arrays & Hashing >> Two Sum
 *
 * Given an array of integers, nums, and an integer target, return the indices of the two numbers
 * in the array that add up to the target.
 *
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 *
 * Example 1:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 * Example 2:
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 *
 * Example 3:
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 *
 * Constraints:
 * 2 <= nums.length <= 10^4
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= target <= 10^9
 */

/**
 * Approach 1: Brute Force
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * Description:
 * This is the most straightforward approach. We iterate through each element in the array
 * and check the sum of it with every other element. If the sum equals the target, we return the indices.
 *
 * Real-world application:
 * This approach can be used in a very basic data validation scenario where you need to check all possible
 * combinations of values to find a match.  For example, in a very simple, non-performance-critical
 * configuration check, you might use this to ensure no two settings conflict.  It's generally avoided
 * in production code due to its inefficiency.
 */
const twoSumBruteForce = (nums, target) => {
    for (let i = 0; i < nums.length; i++) {
        for (let j = i + 1; j < nums.length; j++) {
            if (nums[i] + nums[j] === target) {
                return [i, j];
            }
        }
    }
    // No solution found (though problem statement guarantees one)
    return [];
};

/**
 * Approach 2: Hash Map (Two-Pass)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Description:
 * In this approach, we use a hash map (JavaScript object) to store each number from the array and its index.
 * First, we iterate through the array and store each number and its index in the hash map.
 * Then, we iterate through the array again. For each number, we check if the difference
 * (target - number) exists in the hash map. If it does, and the index is different from the current index,
 * we have found our pair.
 *
 * Real-world application:
 * Hash maps are extremely common.  This two-pass approach could be used in a system that
 * processes user requests, where you need to quickly look up related data.  For example,
 * in an e-commerce system, you might store product IDs and their details in a hash map
 * for fast retrieval during the checkout process.  The first pass pre-loads the data,
 * and the second pass uses it for lookups.
 */
const twoSumHashMapTwoPass = (nums, target) => {
    const numMap = {};

    // Store numbers and their indices in the hash map
    for (let i = 0; i < nums.length; i++) {
        numMap[nums[i]] = i;
    }

    // Find the pair
    for (let i = 0; i < nums.length; i++) {
        const complement = target - nums[i];
        if (numMap[complement] !== undefined && numMap[complement] !== i) {
            return [i, numMap[complement]];
        }
    }

    return [];
};

/**
 * Approach 3: Hash Map (One-Pass)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Description:
 * This is an optimized version of the hash map approach. Instead of iterating through the array twice,
 * we do it in one pass. For each number, we check if its complement (target - number) is already
 * in the hash map. If it is, we found the pair. If not, we add the number and its index to the hash map.
 *
 * Real-world application:
 * This one-pass hash map is even more efficient.  Consider a real-time data processing
 * scenario, like processing a stream of sensor readings.  You might need to identify
 * pairs of readings that satisfy a certain condition (the 'target').  A one-pass hash map
 * allows you to do this very efficiently as the data arrives, without needing to store the
 * entire dataset first.
 */
const twoSumHashMapOnePass = (nums, target) => {
    const numMap = {};

    for (let i = 0; i < nums.length; i++) {
        const complement = target - nums[i];
        if (numMap[complement] !== undefined) {
            return [numMap[complement], i];
        } else {
            numMap[nums[i]] = i;
        }
    }

    return [];
};

/**
 * Approach 4: Sorting and Two Pointers
 *
 * Time Complexity: O(n log n)  (due to sorting)
 * Space Complexity: O(1) or O(n) depending on the sorting algorithm
 *
 * Description:
 * This approach first sorts the array. Then, we use two pointers, one at the beginning and one at the end
 * of the sorted array. We calculate the sum of the numbers at these two pointers.
 * If the sum is equal to the target, we found the pair. If the sum is less than the target, we move the left
 * pointer to the right. If the sum is greater than the target, we move the right pointer to the left.
 *
 * Real-world application:
 * This approach is useful when the input array needs to be sorted anyway for other purposes.
 * For example, imagine you're working on a system that analyzes financial transactions.  You might
 * sort the transactions by amount, and then use a two-pointer approach to find pairs of transactions
 * that meet a specific condition (e.g., sum to a particular fraud threshold).  The sorting step
 * might be a requirement of the overall financial analysis process.
 *
 * Note:  This approach modifies the original array, and it's more difficult to directly get the original indices.
 */
const twoSumSortedTwoPointers = (nums, target) => {
    // Create a copy of the array to avoid modifying the original input
    const sortedNums = [...nums];
    sortedNums.sort((a, b) => a - b); // Sort the copied array

    let left = 0;
    let right = sortedNums.length - 1;

    while (left < right) {
        const sum = sortedNums[left] + sortedNums[right];
        if (sum === target) {
             // Need to find original indices.
             let index1 = -1;
             let index2 = -1;
             for (let i = 0; i < nums.length; i++){
                if (nums[i] === sortedNums[left]){
                    index1 = i;
                    break; // Important:  Find only the *first* occurrence
                }
             }
             for (let i = 0; i < nums.length; i++){
                if (nums[i] === sortedNums[right] && i !== index1){
                    index2 = i;
                    break;
                }
             }
            return [index1, index2];
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return [];
};


/**
 * Approach 5: Using Map.prototype.forEach()
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Description:
 * This approach uses the forEach method of the Map object.  It's similar to the one-pass hash map,
 * but uses the Map data structure.
 *
 * Real-world application:
 * Useful in scenarios where you're already working with Map objects, or prefer the explicit
 * forEach iteration.  For example, you might be processing data from an API that returns
 * key-value pairs, and you've stored some of that data in a Map.  This approach integrates
 * well with that data structure.
 */
const twoSumUsingMapForEach = (nums, target) => {
    const numMap = new Map();
    let result = [];

    nums.forEach((num, index) => {
        const complement = target - num;
        if (numMap.has(complement)) {
            result = [numMap.get(complement), index];
        } else {
            numMap.set(num, index);
        }
    });
    return result;
};

/**
 * Approach 6: Using Array.prototype.reduce()
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Description:
 * This approach uses the reduce method of the Array object.  It's a more functional approach.
 *
 * Real-world application:
 * This approach demonstrates a functional programming style.  It could be used in a data
 * transformation pipeline where you're processing data using functional methods.  For example,
 * in a data analysis script, you might use reduce to accumulate information about the data
 * as you process it.
 */
const twoSumUsingReduce = (nums, target) => {
    const numMap = {};
    let result = [];

    nums.reduce((_, num, index) => { // Use _ to indicate unused accumulator
        const complement = target - num;
        if (numMap[complement] !== undefined) {
            result = [numMap[complement], index];
        } else {
            numMap[num] = index;
        }
        return _; // Not used, but required for reduce
    }, null); // Initial value (not needed here)
    return result;
};



// Example Usage
const nums1 = [2, 7, 11, 15];
const target1 = 9;

const nums2 = [3, 2, 4];
const target2 = 6;

const nums3 = [3, 3];
const target3 = 6;

console.log("Example 1:");
console.log("Brute Force:", twoSumBruteForce(nums1, target1));       // Output: [0, 1]
console.log("Hash Map (Two-Pass):", twoSumHashMapTwoPass(nums1, target1));  // Output: [0, 1]
console.log("Hash Map (One-Pass):", twoSumHashMapOnePass(nums1, target1));  // Output: [0, 1]
console.log("Sorted Two Pointers:", twoSumSortedTwoPointers(nums1, target1));  // Output: [0, 1]
console.log("Using Map.forEach():", twoSumUsingMapForEach(nums1, target1));    // Output: [0, 1]
console.log("Using Array.reduce():", twoSumUsingReduce(nums1, target1));      // Output: [0, 1]

console.log("\nExample 2:");
console.log("Brute Force:", twoSumBruteForce(nums2, target2));       // Output: [1, 2]
console.log("Hash Map (Two-Pass):", twoSumHashMapTwoPass(nums2, target2));  // Output: [1, 2]
console.log("Hash Map (One-Pass):", twoSumHashMapOnePass(nums2, target2));  // Output: [1, 2]
console.log("Sorted Two Pointers:", twoSumSortedTwoPointers(nums2, target2));  // Output: [1, 2]
console.log("Using Map.forEach():", twoSumUsingMapForEach(nums2, target2));    // Output: [1, 2]
console.log("Using Array.reduce():", twoSumUsingReduce(nums2, target2));      // Output: [1, 2]

console.log("\nExample 3:");
console.log("Brute Force:", twoSumBruteForce(nums3, target3));       // Output: [0, 1]
console.log("Hash Map (Two-Pass):", twoSumHashMapTwoPass(nums3, target3));  // Output: [0, 1]
console.log("Hash Map (One-Pass):", twoSumHashMapOnePass(nums3, target3));  // Output: [0, 1]
console.log("Sorted Two Pointers:", twoSumSortedTwoPointers(nums3, target3));  // Output: [0, 1]
console.log("Using Map.forEach():", twoSumUsingMapForEach(nums3, target3));    // Output: [0, 1]
console.log("Using Array.reduce():", twoSumUsingReduce(nums3, target3));      // Output: [0, 1]
