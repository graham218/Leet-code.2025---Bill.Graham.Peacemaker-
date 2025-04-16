// 0/1 Knapsack Problem

/*
The 0/1 Knapsack problem is a classic optimization problem where, given a set of items, each with a weight and a value, the goal is to determine the most valuable combination of items to include in a knapsack without exceeding its weight capacity.  You either take the whole item or leave it (hence 0/1).

Real-world applications:
1.  **Resource Allocation:** A project manager has a limited budget and a set of tasks, each with a cost and a benefit.  The knapsack problem helps decide which tasks to fund to maximize the overall benefit without exceeding the budget.
2.  **Portfolio Optimization:** An investor has a limited amount of capital and a set of potential investments, each with a cost and an expected return.  The knapsack problem helps select the investments that maximize the return without exceeding the capital.
3.  **Cutting Stock:** A manufacturer has a limited supply of raw material (e.g., a roll of fabric) and a set of orders for pieces of specific sizes and values. The knapsack problem helps determine which orders to fulfill to maximize the value of the pieces cut from the raw material.
4.  **Cargo Loading:** A cargo plane or ship has a limited weight capacity and a set of items to transport, each with a weight and a value.  The knapsack problem helps decide which items to load to maximize the total value of the cargo.
5.  **Cryptocurrency Trading:** A trader has a limited amount of capital and a set of cryptocurrencies to trade, each with an expected profit and risk. The knapsack problem can help determine which cryptocurrencies to trade to maximize profit while staying within a certain risk tolerance.

*/

const knapsackProblem = {
    // 1. Recursive Approach
    recursive: function(weights, values, capacity, n) {
        if (n === 0 || capacity === 0) {
            return 0;
        }

        if (weights[n - 1] > capacity) {
            return this.recursive(weights, values, capacity, n - 1);
        } else {
            return Math.max(
                values[n - 1] + this.recursive(weights, values, capacity - weights[n - 1], n - 1),
                this.recursive(weights, values, capacity, n - 1)
            );
        }
    },

    // 2. Memoization (Top-Down Dynamic Programming)
    memoization: function(weights, values, capacity, n, memo) {
        if (n === 0 || capacity === 0) {
            return 0;
        }

        if (memo[n][capacity] !== undefined) {
            return memo[n][capacity];
        }

        if (weights[n - 1] > capacity) {
            memo[n][capacity] = this.memoization(weights, values, capacity, n - 1, memo);
            return memo[n][capacity];
        } else {
            memo[n][capacity] = Math.max(
                values[n - 1] + this.memoization(weights, values, capacity - weights[n - 1], n - 1, memo),
                this.memoization(weights, values, capacity, n - 1, memo)
            );
            return memo[n][capacity];
        }
    },

    // 3. Tabulation (Bottom-Up Dynamic Programming)
    tabulation: function(weights, values, capacity, n) {
        const dp = Array(n + 1).fill(null).map(() => Array(capacity + 1).fill(0));

        for (let i = 0; i <= n; i++) {
            for (let w = 0; w <= capacity; w++) {
                if (i === 0 || w === 0) {
                    dp[i][w] = 0;
                } else if (weights[i - 1] <= w) {
                    dp[i][w] = Math.max(
                        values[i - 1] + dp[i - 1][w - weights[i - 1]],
                        dp[i - 1][w]
                    );
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[n][capacity];
    },

      // 4. Space Optimized Tabulation
      spaceOptimized: function(weights, values, capacity, n) {
        let dp = Array(capacity + 1).fill(0);

        for (let i = 1; i <= n; i++) {
            for (let w = capacity; w >= 0; w--) {
                if (weights[i - 1] <= w) {
                    dp[w] = Math.max(dp[w], values[i - 1] + dp[w - weights[i - 1]]);
                }
            }
        }
        return dp[capacity];
    },

    // 5. Itemized Result with Tabulation
    tabulationWithItems: function(weights, values, capacity, n) {
        const dp = Array(n + 1).fill(null).map(() => Array(capacity + 1).fill(0));
        const selectedItems = [];

        for (let i = 0; i <= n; i++) {
            for (let w = 0; w <= capacity; w++) {
                if (i === 0 || w === 0) {
                    dp[i][w] = 0;
                } else if (weights[i - 1] <= w) {
                    dp[i][w] = Math.max(
                        values[i - 1] + dp[i - 1][w - weights[i - 1]],
                        dp[i - 1][w]
                    );
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        let totalValue = dp[n][capacity];
        let w = capacity;
        for (let i = n; i > 0 && totalValue > 0; i--) {
            if (totalValue === dp[i - 1][w]) {
                continue;
            } else {
                selectedItems.push({ weight: weights[i - 1], value: values[i - 1] });
                totalValue -= values[i - 1];
                w -= weights[i - 1];
            }
        }

        return { maxValue: dp[n][capacity], selectedItems: selectedItems };
    }
};

// Example Usage
const weights = [10, 20, 30];
const values = [60, 100, 120];
const capacity = 50;
const n = weights.length;

// 1. Recursive Approach
console.log("1. Recursive Approach:", knapsackProblem.recursive(weights, values, capacity, n)); // Output: 220

// 2. Memoization Approach
const memo = Array(n + 1).fill(null).map(() => Array(capacity + 1).fill(undefined));
console.log("2. Memoization Approach:", knapsackProblem.memoization(weights, values, capacity, n, memo)); // Output: 220

// 3. Tabulation Approach
console.log("3. Tabulation Approach:", knapsackProblem.tabulation(weights, values, capacity, n)); // Output: 220

// 4. Space Optimized Approach
console.log("4. Space Optimized Approach:", knapsackProblem.spaceOptimized(weights, values, capacity, n)); // Output: 220

// 5. Tabulation with Items
const resultWithItems = knapsackProblem.tabulationWithItems(weights, values, capacity, n);
console.log("5. Tabulation with Items:", resultWithItems);
/*
Output:
{
  maxValue: 220,
  selectedItems: [
    { weight: 30, value: 120 },
    { weight: 20, value: 100 }
  ]
}
*/
