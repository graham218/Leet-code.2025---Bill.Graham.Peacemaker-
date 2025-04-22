/**
 * Dynamic Programming (DP) - Coin Change Problem
 *
 * Problem:
 * You are given an array of coin denominations and a target amount.
 * Find the minimum number of coins needed to make up that amount.
 * If that amount of money cannot be made up by any combination of the coins, return -1.
 *
 * Approaches:
 * 1. Recursive Solution
 * 2. Memoization (Top-Down DP)
 * 3. Tabulation (Bottom-Up DP)
 * 4. Tabulation with Space Optimization
 * 5. Iterative with Tabulation (Optimized)
 */

const coinChange = () => {
    const coins = [1, 2, 5];
    const amount = 11;

    // 1. Recursive Solution
    const recursiveSolution = (coins, amount) => {
        if (amount === 0) {
            return 0;
        }
        if (amount < 0) {
            return -1;
        }

        let minCoins = Infinity;
        for (const coin of coins) {
            const subResult = recursiveSolution(coins, amount - coin);
            if (subResult !== -1) {
                minCoins = Math.min(minCoins, subResult + 1);
            }
        }

        return minCoins === Infinity ? -1 : minCoins;
    };

    // 2. Memoization (Top-Down DP)
    const memoizationSolution = (coins, amount, memo = {}) => {
        if (amount === 0) {
            return 0;
        }
        if (amount < 0) {
            return -1;
        }
        if (memo[amount] !== undefined) {
            return memo[amount];
        }

        let minCoins = Infinity;
        for (const coin of coins) {
            const subResult = memoizationSolution(coins, amount - coin, memo);
            if (subResult !== -1) {
                minCoins = Math.min(minCoins, subResult + 1);
            }
        }

        memo[amount] = minCoins === Infinity ? -1 : minCoins;
        return memo[amount];
    };

    // 3. Tabulation (Bottom-Up DP)
    const tabulationSolution = (coins, amount) => {
        const dp = new Array(amount + 1).fill(Infinity);
        dp[0] = 0;

        for (let i = 1; i <= amount; i++) {
            for (const coin of coins) {
                if (i - coin >= 0) {
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }

        return dp[amount] === Infinity ? -1 : dp[amount];
    };

    // 4. Tabulation with Space Optimization (Not applicable for this problem, but showing general idea for completeness)
    //   In the coin change problem, we can't really optimize the space further than the standard tabulation,
    //   as we need to keep track of the minimum coins for each amount up to the target amount.
    //   Space optimization is more applicable to problems where you only need to keep track of the previous row or a few variables.
    const tabulationSpaceOptimized = (coins, amount) => {
          const dp = new Array(amount + 1).fill(Infinity);
          dp[0] = 0;

          for (let i = 1; i <= amount; i++) {
              for (const coin of coins) {
                  if (i - coin >= 0) {
                      dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                  }
              }
          }
          return dp[amount] === Infinity ? -1 : dp[amount];
    }


    // 5. Iterative with Tabulation (Optimized - same as 3, but with a slight variation in loop order)
    const iterativeTabulationSolution = (coins, amount) => {
        const dp = new Array(amount + 1).fill(Infinity);
        dp[0] = 0;

        for (const coin of coins) { // Iterate through coins first
            for (let i = coin; i <= amount; i++) { // Then iterate through amounts
                dp[i] = Math.min(dp[i], dp[i - coin] + 1);
            }
        }
        return dp[amount] === Infinity ? -1 : dp[amount];
    };

    // Example Usage and Output
    console.log("Coin Change Problem");
    console.log("Coins:", coins);
    console.log("Amount:", amount);
    console.log("\n--- Recursive Solution ---");
    console.log("Minimum coins needed:", recursiveSolution(coins, amount)); // Output: 3
    console.log("\n--- Memoization (Top-Down DP) Solution ---");
    console.log("Minimum coins needed:", memoizationSolution(coins, amount)); // Output: 3
    console.log("\n--- Tabulation (Bottom-Up DP) Solution ---");
    console.log("Minimum coins needed:", tabulationSolution(coins, amount)); // Output: 3
    console.log("\n--- Tabulation (Space Optimized) Solution ---");
    console.log("Minimum coins needed:", tabulationSpaceOptimized(coins, amount)); // Output: 3
    console.log("\n--- Iterative Tabulation (Optimized) Solution ---");
    console.log("Minimum coins needed:", iterativeTabulationSolution(coins, amount)); // Output: 3

    // Additional test cases
    const testCases = [
        { coins: [2], amount: 3, expected: -1 },
        { coins: [1, 2, 5], amount: 0, expected: 0 },
        { coins: [1, 2, 5], amount: 100, expected: 20 },
        { coins: [1, 2, 5, 10, 20, 50, 100, 200, 500, 1000], amount: 7486, expected: 8},
        { coins: [186,419,83,408], amount: 6249, expected: 20 }
    ];

    console.log("\n--- Additional Test Cases ---");
    testCases.forEach((testCase, index) => {
        const result = iterativeTabulationSolution(testCase.coins, testCase.amount);
        console.log(`Test Case ${index + 1}:`);
        console.log("Coins:", testCase.coins);
        console.log("Amount:", testCase.amount);
        console.log("Expected:", testCase.expected, "Result:", result, result === testCase.expected ? "✅" : "❌");
    });
};

coinChange();
