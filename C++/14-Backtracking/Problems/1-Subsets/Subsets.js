/*
 * Problem:
 *
 * Given a set of distinct integers, nums, return all possible subsets (the power set).
 *
 * Example:
 *
 * nums = [1, 2, 3]
 * Output:
 * [
 * [3],
 * [1],
 * [2],
 * [1,2,3],
 * [1,3],
 * [2,3],
 * [1,2],
 * []
 * ]
 *
 * Constraints:
 *
 * The solution set must not contain duplicate subsets.
 *
 */

/**
 * Approach 1: Iterative Approach
 *
 * Time Complexity: O(N * 2^N)
 * Space Complexity: O(2^N)
 */
function subsetsIterative(nums) {
  const subsets = [[]]; // Start with the empty subset
  for (const num of nums) {
    const n = subsets.length;
    for (let i = 0; i < n; i++) {
      const subset = subsets[i].slice(); // Create a copy to avoid modifying the original
      subset.push(num);
      subsets.push(subset);
    }
  }
  return subsets;
}

/**
 * Approach 2: Recursive Backtracking
 *
 * Time Complexity: O(N * 2^N)
 * Space Complexity: O(N) (due to recursion depth)
 */
function subsetsRecursive(nums) {
  const subsets = [];
  const currentSubset = [];

  function backtrack(index) {
    subsets.push([...currentSubset]); // Add a copy of the current subset
    if (index >= nums.length) {
      return;
    }
    currentSubset.push(nums[index]);
    backtrack(index + 1); // Include nums[index]
    currentSubset.pop();
    backtrack(index + 1); // Exclude nums[index]
  }

  backtrack(0);
  return subsets;
}

/**
 * Approach 3: Bit Manipulation
 *
 * Time Complexity: O(N * 2^N)
 * Space Complexity: O(2^N)
 */
function subsetsBitManipulation(nums) {
  const subsets = [];
  const n = nums.length;
  const totalSubsets = 1 << n; // 2^n

  for (let i = 0; i < totalSubsets; i++) {
    const subset = [];
    for (let j = 0; j < n; j++) {
      if ((i >> j) & 1) { // Check if the j-th bit is set
        subset.push(nums[j]);
      }
    }
    subsets.push(subset);
  }
  return subsets;
}

/**
 * Approach 4: Cascading Approach
 *
 * Time Complexity: O(N * 2^N)
 * Space Complexity: O(2^N)
 */
function subsetsCascading(nums) {
    let subsets = [[]];
    for (let num of nums) {
        const n = subsets.length;
        for (let i = 0; i < n; i++) {
            subsets.push([...subsets[i], num]);
        }
    }
    return subsets;
}

/**
 * Approach 5: Optimized Backtracking with Slice
 *
 * Time Complexity: O(N * 2^N)
 * Space Complexity: O(N)
 */
function subsetsOptimizedBacktracking(nums) {
    const result = [];
    const n = nums.length;

    function backtrack(start, currentSubset) {
        // Use slice() to create a copy of the current subset
        result.push(currentSubset.slice());

        for (let i = start; i < n; i++) {
            currentSubset.push(nums[i]);
            backtrack(i + 1, currentSubset);
            currentSubset.pop();
        }
    }

    backtrack(0, []);
    return result;
}

// Example usage and output
const nums = [1, 2, 3];

console.log("Input: ", nums);
console.log("\nApproach 1: Iterative Approach");
console.log(subsetsIterative(nums));

console.log("\nApproach 2: Recursive Backtracking");
console.log(subsetsRecursive(nums));

console.log("\nApproach 3: Bit Manipulation");
console.log(subsetsBitManipulation(nums));

console.log("\nApproach 4: Cascading Approach");
console.log(subsetsCascading(nums));

console.log("\nApproach 5: Optimized Backtracking with Slice");
console.log(subsetsOptimizedBacktracking(nums));
