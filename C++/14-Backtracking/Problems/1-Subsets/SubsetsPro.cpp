/*
 * Backtracking: Subsets
 *
 * Problem:
 *
 * Given a set of distinct integers, nums, return all possible subsets (the power set).
 *
 * Example:
 *
 * Input: nums = [1, 2, 3]
 * Output:
 * [
 * [],
 * [1],
 * [2],
 * [1, 2],
 * [3],
 * [1, 3],
 * [2, 3],
 * [1, 2, 3]
 * ]
 *
 * Constraints:
 *
 * 0 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 * All numbers in nums are unique.
 *
 *
 * Approach 1: Iterative Approach
 *
 * Real-world application:
 * - Feature toggles: In a web application, you might have a set of features that can be enabled or disabled.
 * Generating all subsets of features allows you to test all possible combinations.
 *
 * Explanation:
 * - Start with an empty subset.
 * - For each number in the input array, iterate through the existing subsets and create new subsets by adding the current number to them.
 * - This effectively builds up all possible combinations.
 *
 */
function subsetsIterative(nums) {
  const subsets = [[]]; // Start with an empty set
  for (const num of nums) {
    const n = subsets.length;
    for (let i = 0; i < n; i++) {
      const subset = subsets[i].slice(); // Important: Create a copy!
      subset.push(num);
      subsets.push(subset);
    }
  }
  return subsets;
}

/*
 * Approach 2: Recursive Approach
 *
 * Real-world application:
 * - Configuration management:  Imagine a system where you have various configuration options (e.g., logging levels, database settings).
 * A recursive approach can help generate all possible configuration combinations for testing or deployment.
 *
 * Explanation:
 * - The recursive function `generateSubsets` builds subsets by making a choice at each step:
 * either include the current number or exclude it.
 * - The base case is when all numbers have been processed.
 *
 */
function subsetsRecursive(nums) {
  const subsets = [];
  const currentSubset = [];

  function generateSubsets(index) {
    if (index === nums.length) {
      subsets.push([...currentSubset]); // Add a copy of the current subset
      return;
    }

    // Include the current number
    currentSubset.push(nums[index]);
    generateSubsets(index + 1);

    // Exclude the current number (backtrack)
    currentSubset.pop();
    generateSubsets(index + 1);
  }

  generateSubsets(0);
  return subsets;
}

/*
 * Approach 3: Backtracking Approach
 *
 * Real-world application:
 * - Permission management: In a system with various roles and permissions, you can use backtracking to generate all possible combinations of permissions for a user.
 *
 * Explanation:
 * - Backtracking is a general technique for finding all solutions by exploring all possible candidates.
 * - The `backtrack` function explores adding or not adding each element.
 * - It maintains a `currentSubset` and adds it to the result when a complete subset is formed.
 */
function subsetsBacktracking(nums) {
  const subsets = [];
  const currentSubset = [];

  function backtrack(index) {
    subsets.push([...currentSubset]); // Add the current subset (including empty)

    for (let i = index; i < nums.length; i++) {
      currentSubset.push(nums[i]); // Include nums[i]
      backtrack(i + 1);       // Explore further with this included
      currentSubset.pop();     // Backtrack: remove nums[i] to exclude it
    }
  }

  backtrack(0);
  return subsets;
}

/*
 * Approach 4: Bit Manipulation Approach
 *
 * Real-world application:
 * -  Combinatorial optimization:  If you're working on a problem where you need to try different combinations
 * (e.g., selecting items for a knapsack, or choosing which servers to allocate resources to),
 * bit manipulation can efficiently represent and iterate through these combinations.
 *
 * Explanation:
 * - Each subset can be represented by a binary string of length n, where n is the number of elements in `nums`.
 * - The i-th bit being 1 means the i-th element is included in the subset, and 0 means it's excluded.
 * - Iterate through all possible binary strings (from 0 to 2^n - 1) and construct the corresponding subsets.
 */
function subsetsBitManipulation(nums) {
  const n = nums.length;
  const subsets = [];
  const totalSubsets = 1 << n; // 2^n

  for (let i = 0; i < totalSubsets; i++) {
    const subset = [];
    for (let j = 0; j < n; j++) {
      // Check if the j-th bit is set in i
      if ((i >> j) & 1) {
        subset.push(nums[j]);
      }
    }
    subsets.push(subset);
  }
  return subsets;
}

/*
 * Approach 5: Using Reduce (Functional Approach)
 *
 * Real-world application:
 * - Data analysis: When you need to create rolling aggregations or cumulative combinations of data,
 * reduce can be a concise way to express the logic.  For example, if you're analyzing user activity
 * and want to see all possible combinations of actions a user has taken up to a certain point.
 *
 * Explanation:
 * -  The `reduce` function iterates through the `nums` array.
 * -  For each number, it maps over the existing subsets and adds the current number to create new subsets.
 * -  It then concatenates the original subsets with the new subsets, accumulating all combinations.
 */
function subsetsReduce(nums) {
    return nums.reduce((subsets, num) => {
        const newSubsets = subsets.map(subset => [...subset, num]);
        return subsets.concat(newSubsets);
    }, [[]]);
}

// Example usage and output
const nums = [1, 2, 3];

console.log("Approach 1: Iterative Approach");
console.log(subsetsIterative(nums));
// Expected Output: [ [], [ 1 ], [ 2 ], [ 1, 2 ], [ 3 ], [ 1, 3 ], [ 2, 3 ], [ 1, 2, 3 ] ]

console.log("\nApproach 2: Recursive Approach");
console.log(subsetsRecursive(nums));
// Expected Output: [ [], [ 1 ], [ 2 ], [ 1, 2 ], [ 3 ], [ 1, 3 ], [ 2, 3 ], [ 1, 2, 3 ] ]

console.log("\nApproach 3: Backtracking Approach");
console.log(subsetsBacktracking(nums));
// Expected Output: [ [], [ 1 ], [ 2 ], [ 1, 2 ], [ 3 ], [ 1, 3 ], [ 2, 3 ], [ 1, 2, 3 ] ]

console.log("\nApproach 4: Bit Manipulation Approach");
console.log(subsetsBitManipulation(nums));
// Expected Output: [ [], [ 1 ], [ 2 ], [ 1, 2 ], [ 3 ], [ 1, 3 ], [ 2, 3 ], [ 1, 2, 3 ] ]

console.log("\nApproach 5: Using Reduce");
console.log(subsetsReduce(nums));
// Expected Output: [ [], [ 1 ], [ 2 ], [ 1, 2 ], [ 3 ], [ 1, 3 ], [ 2, 3 ], [ 1, 2, 3 ] ]
