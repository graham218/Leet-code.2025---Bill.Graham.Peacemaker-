/**
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 *
 * https://leetcode.com/problems/climbing-stairs/
 */

/**
 * Solution for Climbing Stairs problem using 5 different approaches:
 * 1. Recursive Approach
 * 2. Memoization Approach (Top-Down DP)
 * 3. Tabulation Approach (Bottom-Up DP)
 * 4. Space Optimized Tabulation
 * 5. Fibonacci Approach
 */

(() => {
  /**
   * 1. Recursive Approach
   *
   * Time Complexity: O(2^n) - Exponential time complexity due to overlapping subproblems.
   * Space Complexity: O(n) -  Due to the depth of the recursion tree.
   */
  const climbStairsRecursive = (n) => {
    if (n <= 1) {
      return 1;
    }
    return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
  };

  /**
   * 2. Memoization Approach (Top-Down DP)
   *
   * Time Complexity: O(n) - Each subproblem is solved only once.
   * Space Complexity: O(n) -  O(n) for the memoization array and O(n) for the recursion stack.
   */
  const climbStairsMemoization = (n, memo = []) => {
    if (n <= 1) {
      return 1;
    }
    if (memo[n] !== undefined) {
      return memo[n];
    }
    memo[n] = climbStairsMemoization(n - 1, memo) + climbStairsMemoization(n - 2, memo);
    return memo[n];
  };

  /**
   * 3. Tabulation Approach (Bottom-Up DP)
   *
   * Time Complexity: O(n) - Iterates through the array once.
   * Space Complexity: O(n) - Uses an array of size n+1 to store the results.
   */
  const climbStairsTabulation = (n) => {
    if (n <= 1) {
      return 1;
    }
    const dp = new Array(n + 1);
    dp[0] = 1;
    dp[1] = 1;
    for (let i = 2; i <= n; i++) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
  };

  /**
   * 4. Space Optimized Tabulation
   *
   * Time Complexity: O(n) - Iterates n times.
   * Space Complexity: O(1) - Uses only a constant amount of extra space.
   */
  const climbStairsSpaceOptimized = (n) => {
    if (n <= 1) {
      return 1;
    }
    let prev1 = 1; // Represents dp[i-1]
    let prev2 = 1; // Represents dp[i-2]
    for (let i = 2; i <= n; i++) {
      const current = prev1 + prev2; // Calculate dp[i]
      prev2 = prev1; // Update dp[i-2]
      prev1 = current; // Update dp[i-1]
    }
    return prev1;
  };

  /**
   * 5. Fibonacci Approach
   *
   * Time Complexity: O(n) -  Similar to the iterative approach.
   * Space Complexity: O(1) - Uses constant extra space.
   *
   * This approach is based on the observation that the number of ways to climb n stairs
   * is equal to the nth Fibonacci number.
   */
  const climbStairsFibonacci = (n) => {
    if (n <= 1) return 1;
    let a = 1,
      b = 1;
    for (let i = 2; i <= n; i++) {
      [a, b] = [b, a + b];
    }
    return b;
  };

  // Example usage and output
  const n = 10;
  console.log(`Number of stairs: ${n}`);
  console.log(`1. Recursive Approach: ${climbStairsRecursive(n)}`);
  console.log(`2. Memoization Approach: ${climbStairsMemoization(n)}`);
  console.log(`3. Tabulation Approach: ${climbStairsTabulation(n)}`);
  console.log(`4. Space Optimized Tabulation: ${climbStairsSpaceOptimized(n)}`);
  console.log(`5. Fibonacci Approach: ${climbStairsFibonacci(n)}`);
})();
