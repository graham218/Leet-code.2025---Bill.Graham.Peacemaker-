/**
 * House Robber Problem:
 *
 * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed,
 * the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected
 * and it will automatically contact the police if two adjacent houses were robbed on the same night.
 *
 * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
 *
 *
 * Approach 1: Top-Down Recursion with Memoization (Real-world application: Optimizing resource allocation in a network)
 */
function robTopDown(nums, i, memo) {
  if (i < 0) {
    return 0;
  }
  if (i === 0) {
    return nums[0];
  }
  if (memo[i] !== -1) {
    return memo[i];
  }

  // Rob the current house or skip it
  const robCurrent = nums[i] + robTopDown(nums, i - 2, memo);
  const skipCurrent = robTopDown(nums, i - 1, memo);

  memo[i] = Math.max(robCurrent, skipCurrent);
  return memo[i];
}

function robTopDownMemoization(nums) {
  const memo = new Array(nums.length).fill(-1);
  return robTopDown(nums, nums.length - 1, memo);
}

/**
 * Approach 2: Bottom-Up Dynamic Programming (Real-world application: Calculating maximum profit in stock trading)
 */
function robBottomUp(nums) {
  if (!nums || nums.length === 0) return 0;
  if (nums.length === 1) return nums[0];

  const dp = new Array(nums.length);
  dp[0] = nums[0];
  dp[1] = Math.max(nums[0], nums[1]);

  for (let i = 2; i < nums.length; i++) {
    // Rob current house or skip it
    dp[i] = Math.max(nums[i] + dp[i - 2], dp[i - 1]);
  }
  return dp[nums.length - 1];
}

/**
 * Approach 3: Optimized Bottom-Up DP (Constant Space) (Real-world application:  Finding the optimal path in a simplified embedded system with limited memory)
 */
function robOptimized(nums) {
  if (!nums || nums.length === 0) return 0;
  if (nums.length === 1) return nums[0];

  let prev2 = 0; // Represents dp[i-2]
  let prev1 = Math.max(nums[0], nums[1]); // Represents dp[i-1]
  let current;

  for (let i = 2; i < nums.length; i++) {
    current = Math.max(nums[i] + prev2, prev1);
    prev2 = prev1;
    prev1 = current;
  }
  return prev1;
}

/**
 * Approach 4: Divide and Conquer (Less efficient, but demonstrates a different paradigm. Real-world: Could be adapted for parallel processing of independent sub-problems, like in a distributed computing environment for analyzing financial data in segments)
 */
function robDivideConquer(nums, low, high) {
  if (low > high) return 0;
  if (low === high) return nums[low];

  let includeLow = nums[low] + robDivideConquer(nums, low + 2, high);
  let excludeLow = robDivideConquer(nums, low + 1, high);

  return Math.max(includeLow, excludeLow);
}

function robDivideConquerStart(nums) {
  if (!nums || nums.length === 0) return 0;
  return robDivideConquer(nums, 0, nums.length - 1);
}

/**
 * Approach 5: Iterative with Explicit State Tracking (Real-world: Useful in scenarios where you need to track the *state* of which houses were robbed, not just the maximum amount, such as in a security system simulation or audit trail analysis.)
 */
function robIterativeWithState(nums) {
  if (!nums || nums.length === 0) return { maxAmount: 0, robbedHouses: [] };
  if (nums.length === 1) return { maxAmount: nums[0], robbedHouses: [0] };

  const dp = new Array(nums.length);
  const robbedHouses = new Array(nums.length).fill(null).map(() => []); // Array to store which houses are robbed

  dp[0] = nums[0];
  robbedHouses[0] = [0];

  dp[1] = Math.max(nums[0], nums[1]);
  robbedHouses[1] = (nums[0] > nums[1]) ? [0] : [1];


  for (let i = 2; i < nums.length; i++) {
    const robCurrent = nums[i] + dp[i - 2];
    const skipCurrent = dp[i - 1];

    if (robCurrent > skipCurrent) {
      dp[i] = robCurrent;
      robbedHouses[i] = [...robbedHouses[i - 2], i]; // Spread operator to create a new array
    } else {
      dp[i] = skipCurrent;
      robbedHouses[i] = [...robbedHouses[i - 1]];
    }
  }

  return { maxAmount: dp[nums.length - 1], robbedHouses: robbedHouses[nums.length - 1] };
}



// Example usage and output
const houses = [2, 7, 9, 3, 1];

console.log("Input Houses:", houses);
console.log("--------------------------------------------------");

// Approach 1: Top-Down Recursion with Memoization
console.log("Approach 1: Top-Down Recursion with Memoization");
const maxAmount1 = robTopDownMemoization(houses);
console.log("Maximum amount robbed:", maxAmount1); // Output: 12
console.log("--------------------------------------------------");

// Approach 2: Bottom-Up Dynamic Programming
console.log("Approach 2: Bottom-Up Dynamic Programming");
const maxAmount2 = robBottomUp(houses);
console.log("Maximum amount robbed:", maxAmount2); // Output: 12
console.log("--------------------------------------------------");

// Approach 3: Optimized Bottom-Up DP (Constant Space)
console.log("Approach 3: Optimized Bottom-Up DP (Constant Space)");
const maxAmount3 = robOptimized(houses);
console.log("Maximum amount robbed:", maxAmount3); // Output: 12
console.log("--------------------------------------------------");

// Approach 4: Divide and Conquer
console.log("Approach 4: Divide and Conquer");
const maxAmount4 = robDivideConquerStart(houses);
console.log("Maximum amount robbed:", maxAmount4); // Output: 12
console.log("--------------------------------------------------");

// Approach 5: Iterative with Explicit State Tracking
console.log("Approach 5: Iterative with Explicit State Tracking");
const result5 = robIterativeWithState(houses);
console.log("Maximum amount robbed:", result5.maxAmount); // Output: 12
console.log("Robbed houses (indices):", result5.robbedHouses); // Output: [ 0, 2, 4 ]
console.log("--------------------------------------------------");
