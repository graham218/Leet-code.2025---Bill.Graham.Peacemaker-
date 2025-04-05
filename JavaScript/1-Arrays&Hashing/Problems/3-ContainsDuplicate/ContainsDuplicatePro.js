/**
 * 1. Arrays & Hashing >> Contains Duplicate
 *
 * Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
 *
 * Example 1:
 * Input: nums = [1,2,3,1]
 * Output: true
 *
 * Example 2:
 * Input: nums = [1,2,3,4]
 * Output: false
 *
 * Example 3:
 * Input: nums = [1,1,1,3,3,4,3,2,4,2]
 * Output: true
 *
 * Constraints:
 * 1 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 */

/**
 * Approach 1: Brute Force
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * Description:
 * The brute force approach iterates through each element of the array and compares it with every other element.
 * If any two elements are found to be equal, it returns true. Otherwise, it returns false after checking all pairs.
 *
 * Real-world application:
 * This approach is generally inefficient and not suitable for large datasets.  However, it could be used in very
 * simple data validation scenarios or in small-scale data analysis where performance is not a critical concern.
 * For example, you might use it to check for duplicate entries in a small configuration file.
 */
const containsDuplicateBruteForce = (nums) => {
    for (let i = 0; i < nums.length; i++) {
        for (let j = i + 1; j < nums.length; j++) {
            if (nums[i] === nums[j]) {
                return true;
            }
        }
    }
    return false;
};

/**
 * Approach 2: Using a Set
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Description:
 * This approach uses a Set to keep track of the elements encountered so far.  It iterates through the array,
 * and for each element, it checks if the element is already in the Set. If it is, it means a duplicate has been found,
 * and the function returns true. If the loop finishes without finding any duplicates, it returns false.
 *
 * Real-world application:
 * This is a very common and efficient approach for detecting duplicates.  It can be used in many scenarios,
 * such as validating the uniqueness of user IDs, email addresses, or other identifiers in a system.  It's also
 * useful in data cleaning to remove duplicate records from a dataset.
 */
const containsDuplicateSet = (nums) => {
    const numSet = new Set();
    for (const num of nums) {
        if (numSet.has(num)) {
            return true;
        }
        numSet.add(num);
    }
    return false;
};

/**
 * Approach 3: Using an Object (Hash Map)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Description:
 * This approach uses a JavaScript object (hash map) to store the frequency of each element.  As it iterates
 * through the array, it checks if the element already exists as a key in the object.  If it does, a duplicate
 * is found.  If not, it adds the element as a key with a value of 1.
 *
 * Real-world application:
 * Similar to using a Set, this approach is efficient for detecting duplicates.  It can be used in scenarios where
 * you need to count the occurrences of each element, in addition to detecting duplicates. For example, you could
 * use it to analyze website traffic data to identify frequently visited pages.
 */
const containsDuplicateObject = (nums) => {
    const numCounts = {};
    for (const num of nums) {
        if (numCounts[num]) {
            return true;
        }
        numCounts[num] = 1;
    }
    return false;
};

/**
 * Approach 4: Sorting
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(1) or O(n) depending on the sorting algorithm
 *
 * Description:
 * This approach sorts the array first. After sorting, duplicate elements will be adjacent to each other.
 * The function then iterates through the sorted array, checking if any two adjacent elements are equal.
 *
 * Real-world application:
 * This approach is useful if the array needs to be sorted for other purposes as well. For example, if you
 * are processing a list of customer orders and need to both check for duplicate order IDs and sort the orders
 * by date, you could use this approach.
 */
const containsDuplicateSort = (nums) => {
    const sortedNums = [...nums].sort((a, b) => a - b); //avoid mutating original array
    for (let i = 0; i < sortedNums.length - 1; i++) {
        if (sortedNums[i] === sortedNums[i + 1]) {
            return true;
        }
    }
    return false;
};

/**
 * Approach 5: Using Array.prototype.indexOf()
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * Description:
 * This approach iterates through the array and for each element, checks if its first occurrence
 * (found using indexOf()) is at a different index. If it is, it means the element appears more than once.
 *
 * Real-world application:
 * This approach is less efficient than using a Set or a hash map, but it demonstrates an alternative
 * way to find duplicates using built-in array methods.  It might be used in situations where you want to
 * avoid using extra data structures and are working with relatively small arrays.
 */
const containsDuplicateIndexOf = (nums) => {
    for (let i = 0; i < nums.length; i++) {
        if (nums.indexOf(nums[i]) !== i) {
            return true;
        }
    }
    return false;
};

/**
 * Approach 6: Using Array.prototype.reduce()
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Description:
 * This approach uses the reduce method to build a Set of unique elements.  The reduce function
 * iterates through the array, adding each element to the Set.  At the end, it checks if the size of the Set
 * is less than the length of the original array. If it is, it means there were duplicates.
 *
 * Real-world application:
 * This approach demonstrates a functional way to solve the problem.  It can be useful in codebases that
 * emphasize functional programming paradigms.  It's also a good example of how to use reduce()
 * to accumulate a value (in this case, a Set) over an array.
 */
const containsDuplicateReduce = (nums) => {
    const uniqueSet = nums.reduce((set, num) => {
        set.add(num);
        return set;
    }, new Set());
    return uniqueSet.size !== nums.length;
};

// Example Usage
const nums1 = [1, 2, 3, 1];
const nums2 = [1, 2, 3, 4];
const nums3 = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2];

console.log("Example 1:");
console.log("Brute Force:", containsDuplicateBruteForce(nums1));    // Output: true
console.log("Set:", containsDuplicateSet(nums1));                // Output: true
console.log("Object:", containsDuplicateObject(nums1));            // Output: true
console.log("Sort:", containsDuplicateSort(nums1));                // Output: true
console.log("indexOf:", containsDuplicateIndexOf(nums1));          // Output: true
console.log("Reduce:", containsDuplicateReduce(nums1));            // Output: true

console.log("\nExample 2:");
console.log("Brute Force:", containsDuplicateBruteForce(nums2));    // Output: false
console.log("Set:", containsDuplicateSet(nums2));                // Output: false
console.log("Object:", containsDuplicateObject(nums2));            // Output: false
console.log("Sort:", containsDuplicateSort(nums2));                // Output: false
console.log("indexOf:", containsDuplicateIndexOf(nums2));          // Output: false
console.log("Reduce:", containsDuplicateReduce(nums2));            // Output: false

console.log("\nExample 3:");
console.log("Brute Force:", containsDuplicateBruteForce(nums3));    // Output: true
console.log("Set:", containsDuplicateSet(nums3));                // Output: true
console.log("Object:", containsDuplicateObject(nums3));            // Output: true
console.log("Sort:", containsDuplicateSort(nums3));                // Output: true
console.log("indexOf:", containsDuplicateIndexOf(nums3));          // Output: true
console.log("Reduce:", containsDuplicateReduce(nums3));            // Output: true
