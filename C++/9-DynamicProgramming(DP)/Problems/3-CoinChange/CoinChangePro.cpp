/**
 * Dynamic Programming: Coin Change Problem
 *
 * Problem:
 * Given an array of coin denominations and a target amount, find the minimum number of coins
 * needed to make up that amount. If the amount cannot be made up by any combination of the coins,
 * return -1.
 *
 * Approaches:
 * 1. Top-Down (Memoization)
 * 2. Bottom-Up (Tabulation)
 * 3. Bottom-Up (Tabulation) - Space Optimized
 * 4. Variation: Counting the Number of Combinations
 * 5. Variation: Coin Change with Limited Supply
 *
 * Real-world applications:
 * - **E-commerce:** Calculating optimal change in online transactions.
 * - **Point of Sale (POS) Systems:** Determining the fewest coins/bills for customer change.
 * - **Inventory Management:** Optimizing the combination of item quantities to meet a target.
 * - **Financial Systems:** Calculating optimal portfolio allocations.
 */

// 1. Top-Down (Memoization)
/**
 * Solves the Coin Change problem using a top-down dynamic programming approach with memoization.
 *
 * @param {number[]} coins An array of coin denominations.
 * @param {number} amount The target amount.
 * @returns {number} The minimum number of coins needed, or -1 if the amount cannot be made.
 */
function coinChangeTopDown(coins, amount) {
  if (amount === 0) {
    return 0;
  }

  const memo = new Array(amount + 1).fill(Infinity); // Initialize memoization table
  memo[0] = 0; // Base case: 0 coins needed for amount 0

  /**
   * Recursive helper function to calculate the minimum coins needed for a given amount.
   *
   * @param {number} remaining The remaining amount.
   * @returns {number} The minimum number of coins needed for the remaining amount.
   */
  function dp(remaining) {
    if (remaining < 0) {
      return Infinity; // Invalid amount
    }
    if (memo[remaining] !== Infinity) {
      return memo[remaining]; // Return memoized result if available
    }

    for (const coin of coins) {
      const subResult = dp(remaining - coin);
      if (subResult !== Infinity) {
        memo[remaining] = Math.min(memo[remaining], subResult + 1);
      }
    }
    return memo[remaining];
  }

  const result = dp(amount);
  return result === Infinity ? -1 : result;
}

// 2. Bottom-Up (Tabulation)
/**
 * Solves the Coin Change problem using a bottom-up dynamic programming approach with tabulation.
 *
 * @param {number[]} coins An array of coin denominations.
 * @param {number} amount The target amount.
 * @returns {number} The minimum number of coins needed, or -1 if the amount cannot be made.
 */
function coinChangeBottomUp(coins, amount) {
  if (amount === 0) {
    return 0;
  }

  const dp = new Array(amount + 1).fill(Infinity); // Initialize DP table
  dp[0] = 0; // Base case: 0 coins needed for amount 0

  for (let i = 1; i <= amount; i++) {
    for (const coin of coins) {
      if (i - coin >= 0) {
        dp[i] = Math.min(dp[i], dp[i - coin] + 1);
      }
    }
  }

  return dp[amount] === Infinity ? -1 : dp[amount];
}

// 3. Bottom-Up (Tabulation) - Space Optimized
/**
 * Solves the Coin Change problem using a space-optimized bottom-up dynamic programming approach.
 *
 * @param {number[]} coins An array of coin denominations.
 * @param {number} amount The target amount.
 * @returns {number} The minimum number of coins needed, or -1 if the amount cannot be made.
 */
function coinChangeBottomUpSpaceOptimized(coins, amount) {
  if (amount === 0) {
    return 0;
  }

  let dp = new Array(amount + 1).fill(Infinity);
  dp[0] = 0;

  for (const coin of coins) {
    for (let i = coin; i <= amount; i++) {
      dp[i] = Math.min(dp[i], dp[i - coin] + 1);
    }
  }
  return dp[amount] === Infinity ? -1 : dp[amount];
}

// 4. Variation: Counting the Number of Combinations
/**
 * Counts the number of distinct combinations of coins that can make up the target amount.
 *
 * @param {number[]} coins An array of coin denominations.
 * @param {number} amount The target amount.
 * @returns {number} The number of combinations.
 */
function coinChangeCombinations(coins, amount) {
  if (amount === 0) {
    return 1; // There is one way to make 0 amount: using no coins
  }

  const dp = new Array(amount + 1).fill(0);
  dp[0] = 1; // Base case: one way to make amount 0

  for (const coin of coins) {
    for (let i = coin; i <= amount; i++) {
      dp[i] += dp[i - coin];
    }
  }
  return dp[amount];
}

// 5. Variation: Coin Change with Limited Supply
/**
 * Solves the Coin Change problem with a limited supply of each coin denomination.
 *
 * @param {number[]} coins An array of coin denominations.
 * @param {number[]} quantities An array representing the quantity of each coin available.
 * @param {number} amount The target amount.
 * @returns {number} The minimum number of coins needed, or -1 if the amount cannot be made.
 */
function coinChangeLimitedSupply(coins, quantities, amount) {
  if (amount === 0) {
    return 0;
  }

  const dp = new Array(amount + 1).fill(Infinity);
  dp[0] = 0;

  for (let i = 0; i < coins.length; i++) {
    const coin = coins[i];
    const quantity = quantities[i];
    for (let j = amount; j >= coin; j--) {
      for (let k = 1; k <= quantity && k * coin <= j; k++) {
        dp[j] = Math.min(dp[j], dp[j - k * coin] + k);
      }
    }
  }
  return dp[amount] === Infinity ? -1 : dp[amount];
}

// Example Usage and Console Logs
const coins = [1, 2, 5];
const amount = 11;

console.log("Coin Change Problem:");
console.log("Coins:", coins);
console.log("Amount:", amount);
console.log("\n---");

// 1. Top-Down (Memoization)
const resultTopDown = coinChangeTopDown(coins, amount);
console.log("1. Top-Down (Memoization):", resultTopDown); // Output: 3

// 2. Bottom-Up (Tabulation)
const resultBottomUp = coinChangeBottomUp(coins, amount);
console.log("2. Bottom-Up (Tabulation):", resultBottomUp); // Output: 3

// 3. Bottom-Up (Tabulation) - Space Optimized
const resultBottomUpSpaceOptimized = coinChangeBottomUpSpaceOptimized(coins, amount);
console.log("3. Bottom-Up (Space Optimized):", resultBottomUpSpaceOptimized); // Output: 3

// 4. Variation: Counting the Number of Combinations
const combinations = coinChangeCombinations(coins, amount);
console.log("4. Number of Combinations:", combinations); // Output: 7

// 5. Variation: Coin Change with Limited Supply
const limitedCoins = [1, 2, 5];
const quantities = [2, 1, 2]; // Example: 2x1, 1x2, 2x5
const amountLimited = 11;
const resultLimitedSupply = coinChangeLimitedSupply(limitedCoins, quantities, amountLimited);
console.log("\n---");
console.log("5. Coin Change with Limited Supply:");
console.log("Coins:", limitedCoins);
console.log("Quantities:", quantities);
console.log("Amount:", amountLimited);
console.log("Result (Limited Supply):", resultLimitedSupply); // Output: 3
