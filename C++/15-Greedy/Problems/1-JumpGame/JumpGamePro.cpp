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
 * Approach 1: Greedy Approach (Optimized - Real-World: Route Optimization)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * Real-world application: Route optimization in logistics or robotics.  Instead of array indices,
 * think of locations, and the values as maximum travel distances.  This approach finds if a destination is reachable.
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
 * Approach 2: Dynamic Programming (Top-Down with Memoization - Real-World: Game Development)
 *
 * Time Complexity: O(n) - due to memoization
 * Space Complexity: O(n) - for the memoization array and call stack
 *
 * Real-world application:  Game development, where you have a character moving through levels.  Memoization helps
 * determine if a certain point in the level is reachable, avoiding redundant calculations in complex level designs.
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
 * Approach 3: Dynamic Programming (Bottom-Up - Real-World:  Resource Allocation)
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 *
 * Real-world application:  Resource allocation.  Imagine you have a series of projects (represented by the array),
 * and each project has a certain amount of resource that can be allocated (the value).  This approach determines
 * if you can reach the final project with the given resources.  Less efficient than Greedy, but shows the DP concept.
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
 * Approach 4: Recursive Approach (Basic - Real-World: Simulation - Conceptual)
 *
 * Time Complexity: O(2^n) -  Exponential time complexity.
 * Space Complexity: O(n) -  Due to the depth of the recursion.
 *
 * Real-world application:  Basic simulation of a system with branching possibilities.  For example, a very simplified model
 * of decision-making, where each step has multiple choices.  In reality, this approach is too inefficient for complex simulations.
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
 * Approach 5: Greedy Backtracking (Real-World:  Step-by-Step Validation)
 *
 * Time Complexity: O(n^2) in the worst case
 * Space Complexity: O(1)
 *
 * Real-world application:  Step-by-step validation of a process.  Imagine validating a series of user inputs,
 * where each input determines the next possible input.  This approach checks if the final step can be reached
 * by backtracking from the end.
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

console.log("Example 1: Route Optimization");
console.log("Input: [2,3,1,1,4] (Locations and Travel Distances)");
console.log("Reachable:", canJumpGreedy(nums1)); // true

console.log("\nExample 2: Game Development");
console.log("Input: [3,2,1,0,4] (Level Design - Reachability)");
console.log("Reachable:", canJumpMemoization(nums2)); // false

console.log("\nExample 3: Resource Allocation");
console.log("Input: [0] (Single Project)");
console.log("Reachable:", canJumpBottomUp(nums3)); // true

console.log("\nExample 4: Simulation (Conceptual)");
console.log("Input: [2, 0, 0] (Simplified Decision Tree)");
console.log("Reachable:", canJumpRecursive(nums4)); // true

console.log("\nExample 5: Step-by-Step Validation");
console.log("Input: [2, 5, 0, 0] (Input Validation Sequence)");
console.log("Reachable:", canJumpGreedyBacktracking(nums5)); // true
