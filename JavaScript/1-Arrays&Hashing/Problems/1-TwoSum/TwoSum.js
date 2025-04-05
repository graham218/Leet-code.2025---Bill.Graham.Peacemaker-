/**
 * 1. Arrays & Hashing >> Two Sum
 *
 * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 *
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 *
 * You can return the answer in any order.
 *
 * Example 1:
 *
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 * Example 2:
 *
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 *
 * Example 3:
 *
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 *
 * Constraints:
 *
 * 2 <= nums.length <= 104
 * -109 <= nums[i] <= 109
 * -109 <= target <= 109
 * Only one valid answer exists.
 */

/**
 * Approach 1: Brute Force
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
const twoSumBruteForce = (nums, target) => {
  for (let i = 0; i < nums.length; i++) {
    for (let j = i + 1; j < nums.length; j++) {
      if (nums[i] + nums[j] === target) {
        return [i, j];
      }
    }
  }
  // No solution found (though the problem states there *is* one)
  return [];
};

/**
 * Approach 2: Hash Map (Two-Pass)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
const twoSumHashMapTwoPass = (nums, target) => {
  const map = new Map();

  // Store each number and its index in the map
  for (let i = 0; i < nums.length; i++) {
    map.set(nums[i], i);
  }

  // Iterate again to find the complement
  for (let i = 0; i < nums.length; i++) {
    const complement = target - nums[i];
    if (map.has(complement) && map.get(complement) !== i) {
      return [i, map.get(complement)];
    }
  }

  // No solution found
  return [];
};

/**
 * Approach 3: Hash Map (One-Pass)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
const twoSumHashMapOnePass = (nums, target) => {
  const map = new Map();

  for (let i = 0; i < nums.length; i++) {
    const complement = target - nums[i];
    if (map.has(complement)) {
      return [map.get(complement), i];
    }
    map.set(nums[i], i);
  }

  // No solution found
  return [];
};

/**
 * Approach 4:  Using Array.prototype.find() (Less Efficient)
 *
 * Time Complexity: O(n^2) in the worst case (find() iterates)
 * Space Complexity: O(1)
 *
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
const twoSumFind = (nums, target) => {
    for (let i = 0; i < nums.length; i++) {
        const complementIndex = nums.findIndex((num, index) => index !== i && num === target - nums[i]);
        if (complementIndex !== -1) {
            return [i, complementIndex];
        }
    }
    return [];
};


/**
 * Approach 5: Sorting and Two Pointers (Efficient for Sorted Arrays)
 * This approach modifies the original array, and doesn't return the original indices.
 * It's included for completeness, but the problem requires original indices.
 *
 * Time Complexity: O(n log n) for sorting, O(n) for two pointers, so O(n log n)
 * Space Complexity: O(n) for the copy, O(1) for two pointers
 *
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
const twoSumSortedPointers = (nums, target) => {
  // Create a copy to avoid modifying the original array
  const sortedNums = [...nums].sort((a, b) => a - b); // O(n log n)
  let left = 0;
  let right = sortedNums.length - 1;

  while (left < right) { // O(n)
    const sum = sortedNums[left] + sortedNums[right];
    if (sum === target) {
      // Need to find original indices, which is tricky since we sorted
      const originalIndex1 = nums.indexOf(sortedNums[left]);
      const originalIndex2 = nums.lastIndexOf(sortedNums[right]); // Use lastIndexOf in case of duplicates
      if(originalIndex1 === originalIndex2){
        //If both are same, we need to find the other index.
        for(let i=0; i<nums.length; i++){
            if(nums[i] === sortedNums[right] && i !== originalIndex1){
                return [originalIndex1, i];
            }
        }

      }
      return [originalIndex1, originalIndex2];

    } else if (sum < target) {
      left++;
    } else {
      right--;
    }
  }
  return [];
};



// Example Usage and Output
const nums1 = [2, 7, 11, 15];
const target1 = 9;
console.log(`Input: nums = [${nums1}], target = ${target1}`);
console.log(`Brute Force: ${twoSumBruteForce(nums1, target1)}`); // Output: [0, 1]
console.log(`Hash Map (Two-Pass): ${twoSumHashMapTwoPass(nums1, target1)}`); // Output: [0, 1]
console.log(`Hash Map (One-Pass): ${twoSumHashMapOnePass(nums1, target1)}`); // Output: [0, 1]
console.log(`Find: ${twoSumFind(nums1, target1)}`);       // Output: [0, 1]
console.log(`Sorted Pointers: ${twoSumSortedPointers(nums1, target1)}`); // Output: [0, 1] (May not be in original order)


const nums2 = [3, 2, 4];
const target2 = 6;
console.log(`\nInput: nums = [${nums2}], target = ${target2}`);
console.log(`Brute Force: ${twoSumBruteForce(nums2, target2)}`); // Output: [1, 2]
console.log(`Hash Map (Two-Pass): ${twoSumHashMapTwoPass(nums2, target2)}`); // Output: [1, 2]
console.log(`Hash Map (One-Pass): ${twoSumHashMapOnePass(nums2, target2)}`); // Output: [1, 2]
console.log(`Find: ${twoSumFind(nums2, target2)}`);       // Output: [1, 2]
console.log(`Sorted Pointers: ${twoSumSortedPointers(nums2, target2)}`); // Output: [1, 2]

const nums3 = [3, 3];
const target3 = 6;
console.log(`\nInput: nums = [${nums3}], target = ${target3}`);
console.log(`Brute Force: ${twoSumBruteForce(nums3, target3)}`);   // Output: [0, 1]
console.log(`Hash Map (Two-Pass): ${twoSumHashMapTwoPass(nums3, target3)}`);   // Output: [0, 1]
console.log(`Hash Map (One-Pass): ${twoSumHashMapOnePass(nums3, target3)}`);   // Output: [0, 1]
console.log(`Find: ${twoSumFind(nums3, target3)}`);         // Output: [0, 1]
console.log(`Sorted Pointers: ${twoSumSortedPointers(nums3, target3)}`);       // Output: [0, 1]

const nums4 = [2,5,5,11];
const target4 = 10;
console.log(`\nInput: nums = [${nums4}], target = ${target4}`);
console.log(`Brute Force: ${twoSumBruteForce(nums4, target4)}`);
console.log(`Hash Map (Two-Pass): ${twoSumHashMapTwoPass(nums4, target4)}`);
console.log(`Hash Map (One-Pass): ${twoSumHashMapOnePass(nums4, target4)}`);
console.log(`Find: ${twoSumFind(nums4, target4)}`);
console.log(`Sorted Pointers: ${twoSumSortedPointers(nums4, target4)}`);
