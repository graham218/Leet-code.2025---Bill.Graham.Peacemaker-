/**
 * Jump Game Problem:
 *
 * You are given an array of non-negative integers. Each element represents the maximum jump length at that position.
 * Determine if you are able to reach the last index.
 *
 * For example:
 * A = [2,3,1,1,4], return true.
 * A = [3,2,1,0,4], return false.
 */

/**
 * Approach 1: Greedy Approach (Optimized)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function canJumpGreedy(nums) {
  let maxReach = 0;
  for (let i = 0; i < nums.length; i++) {
    if (i > maxReach) {
      return false; // Cannot reach current position
    }
    maxReach = Math.max(maxReach, i + nums[i]);
  }
  return true;
}

/**
 * Approach 2: Dynamic Programming (Top-Down with Memoization)
 *
 * Time Complexity: O(n) - due to memoization
 * Space Complexity: O(n) - for the memoization array and call stack
 */
function canJumpMemoization(nums) {
  const memo = new Array(nums.length).fill(null); // Use null for unvisited
  memo[nums.length - 1] = true; // Last position is reachable

  function canReach(index) {
    if (memo[index] !== null) {
      return memo[index]; // Return memoized result
    }

    const maxJump = nums[index];
    for (let nextJump = 1; nextJump <= maxJump; nextJump++) {
      if (index + nextJump >= nums.length - 1) {
        memo[index] = true;
        return true;
      }
      if (canReach(index + nextJump)) {
        memo[index] = true;
        return true;
      }
    }

    memo[index] = false;
    return false;
  }

  return canReach(0);
}



/**
 * Approach 3: Dynamic Programming (Bottom-Up)
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
function canJumpBottomUp(nums) {
  const reachable = new Array(nums.length).fill(false);
  reachable[nums.length - 1] = true; // Last index is always reachable

  for (let i = nums.length - 2; i >= 0; i--) {
    const maxJump = nums[i];
    for (let j = 1; j <= maxJump; j++) {
      if (i + j < nums.length && reachable[i + j]) {
        reachable[i] = true;
        break; // Important: Once reachable, no need to check further
      }
    }
  }
  return reachable[0];
}

/**
 * Approach 4: Recursive Approach (Basic - Exceeds Time Limit for Larger Inputs)
 *
 * Time Complexity: O(2^n) -  Exponential time complexity.
 * Space Complexity: O(n) -  Due to the depth of the recursion.
 */
function canJumpRecursive(nums) {
  function canReach(index) {
    if (index >= nums.length - 1) {
      return true;
    }

    const maxJump = nums[index];
    for (let nextJump = 1; nextJump <= maxJump; nextJump++) {
      if (canReach(index + nextJump)) {
        return true;
      }
    }
    return false;
  }

  return canReach(0);
}

/**
 * Approach 5: Greedy Backtracking (Less Efficient than Optimized Greedy)
 *
 * Time Complexity: O(n^2) in the worst case
 * Space Complexity: O(1)
 */
function canJumpGreedyBacktracking(nums) {
    let lastReachable = nums.length - 1;
    for (let i = nums.length - 2; i >= 0; i--) {
        if (i + nums[i] >= lastReachable) {
            lastReachable = i;
        }
    }
    return lastReachable === 0;
}



// Example Usage:
const nums1 = [2, 3, 1, 1, 4];
const nums2 = [3, 2, 1, 0, 4];
const nums3 = [0];
const nums4 = [2, 0, 0];
const nums5 = [2, 5, 0, 0];

console.log("Example 1:");
console.log("Input: [2,3,1,1,4]");
console.log("Greedy Approach:", canJumpGreedy(nums1)); // true
console.log("Memoization Approach:", canJumpMemoization(nums1)); // true
console.log("Bottom-Up DP Approach:", canJumpBottomUp(nums1)); // true
console.log("Recursive Approach:", canJumpRecursive(nums1)); // true
console.log("Greedy Backtracking Approach:", canJumpGreedyBacktracking(nums1)); // true


console.log("\nExample 2:");
console.log("Input: [3,2,1,0,4]");
console.log("Greedy Approach:", canJumpGreedy(nums2)); // false
console.log("Memoization Approach:", canJumpMemoization(nums2)); // false
console.log("Bottom-Up DP Approach:", canJumpBottomUp(nums2)); // false
console.log("Recursive Approach:", canJumpRecursive(nums2)); // false
console.log("Greedy Backtracking Approach:", canJumpGreedyBacktracking(nums2)); // false

console.log("\nExample 3: Single Element Array");
console.log("Input: [0]");
console.log("Greedy Approach:", canJumpGreedy(nums3)); // true
console.log("Memoization Approach:", canJumpMemoization(nums3)); // true
console.log("Bottom-Up DP Approach:", canJumpBottomUp(nums3)); // true
console.log("Recursive Approach:", canJumpRecursive(nums3)); // true
console.log("Greedy Backtracking Approach:", canJumpGreedyBacktracking(nums3)); // true

console.log("\nExample 4: Reachable with Zeros");
console.log("Input: [2, 0, 0]");
console.log("Greedy Approach:", canJumpGreedy(nums4)); // true
console.log("Memoization Approach:", canJumpMemoization(nums4)); // true
console.log("Bottom-Up DP Approach:", canJumpBottomUp(nums4)); // true
console.log("Recursive Approach:", canJumpRecursive(nums4)); // true
console.log("Greedy Backtracking Approach:", canJumpGreedyBacktracking(nums4)); // true

console.log("\nExample 5: Larger Jumps");
console.log("Input: [2, 5, 0, 0]");
console.log("Greedy Approach:", canJumpGreedy(nums5)); // true
console.log("Memoization Approach:", canJumpMemoization(nums5)); // true
console.log("Bottom-Up DP Approach:", canJumpBottomUp(nums5));   // true
console.log("Recursive Approach:", canJumpRecursive(nums5));   // true
console.log("Greedy Backtracking Approach:", canJumpGreedyBacktracking(nums5));
