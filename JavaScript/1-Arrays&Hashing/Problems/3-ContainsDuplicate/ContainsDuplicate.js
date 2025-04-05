/**
 * 217. Arrays & Hashing >> Contains Duplicate
 *
 * Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
 *
 * Example 1:
 *
 * Input: nums = [1,2,3,1]
 * Output: true
 *
 * Example 2:
 *
 * Input: nums = [1,2,3,4]
 * Output: false
 *
 * Example 3:
 *
 * Input: nums = [1,1,1,3,3,4,3,2,4,2]
 * Output: true
 *
 * Constraints:
 *
 * 1 <= nums.length <= 105
 * -109 <= nums[i] <= 109
 */

/**
 * Approach 1: Brute Force
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * @param {number[]} nums
 * @return {boolean}
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
 * Approach 2: Sorting
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(1) -  O(n) depending on the sorting algorithm
 *
 * @param {number[]} nums
 * @return {boolean}
 */
const containsDuplicateSort = (nums) => {
  const sortedNums = [...nums].sort((a, b) => a - b); // create a copy and sort
  for (let i = 0; i < sortedNums.length - 1; i++) {
    if (sortedNums[i] === sortedNums[i + 1]) {
      return true;
    }
  }
  return false;
};

/**
 * Approach 3: Hash Set
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * @param {number[]} nums
 * @return {boolean}
 */
const containsDuplicateSet = (nums) => {
  const set = new Set();
  for (const num of nums) {
    if (set.has(num)) {
      return true;
    }
    set.add(num);
  }
  return false;
};

/**
 * Approach 4: Hash Map (Frequency Counting)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * @param {number[]} nums
 * @return {boolean}
 */
const containsDuplicateMap = (nums) => {
  const map = new Map();
  for (const num of nums) {
    map.set(num, (map.get(num) || 0) + 1);
    if (map.get(num) >= 2) {
      return true;
    }
  }
  return false;
};

/**
 * Approach 5: Using Array.prototype.indexOf (Less Efficient)
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * @param {number[]} nums
 * @return {boolean}
 */
const containsDuplicateIndexOf = (nums) => {
  for (let i = 0; i < nums.length; i++) {
    if (nums.indexOf(nums[i]) !== i) {
      return true;
    }
  }
  return false;
};

// Example Usage and Output
const nums1 = [1, 2, 3, 1];
console.log(`Input: nums = [${nums1}]`);
console.log(`Brute Force: ${containsDuplicateBruteForce(nums1)}`); // Output: true
console.log(`Sorting: ${containsDuplicateSort(nums1)}`); // Output: true
console.log(`Set: ${containsDuplicateSet(nums1)}`); // Output: true
console.log(`Map: ${containsDuplicateMap(nums1)}`); // Output: true
console.log(`IndexOf: ${containsDuplicateIndexOf(nums1)}`); // Output: true

const nums2 = [1, 2, 3, 4];
console.log(`\nInput: nums = [${nums2}]`);
console.log(`Brute Force: ${containsDuplicateBruteForce(nums2)}`); // Output: false
console.log(`Sorting: ${containsDuplicateSort(nums2)}`); // Output: false
console.log(`Set: ${containsDuplicateSet(nums2)}`); // Output: false
console.log(`Map: ${containsDuplicateMap(nums2)}`); // Output: false
console.log(`IndexOf: ${containsDuplicateIndexOf(nums2)}`); // Output: false

const nums3 = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2];
console.log(`\nInput: nums = [${nums3}]`);
console.log(`Brute Force: ${containsDuplicateBruteForce(nums3)}`); // Output: true
console.log(`Sorting: ${containsDuplicateSort(nums3)}`); // Output: true
console.log(`Set: ${containsDuplicateSet(nums3)}`); // Output: true
console.log(`Map: ${containsDuplicateMap(nums3)}`); // Output: true
console.log(`IndexOf: ${containsDuplicateIndexOf(nums3)}`); // Output: true
