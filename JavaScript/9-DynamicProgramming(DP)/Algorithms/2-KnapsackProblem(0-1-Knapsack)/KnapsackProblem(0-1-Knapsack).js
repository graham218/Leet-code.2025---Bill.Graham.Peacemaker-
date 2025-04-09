/*
Knapsack Problem (0/1 Knapsack)

Given a set of items, each with a weight and a value, determine the maximum value of items you can include in a knapsack with a given weight capacity.  You can either include the whole item or exclude it (hence 0/1).

Problem Variations Implemented:
1.  Recursive Solution
2.  Memoized (Top-Down) DP Solution
3.  Tabulated (Bottom-Up) DP Solution
4.  Space-Optimized DP Solution
5.  Item Tracking (Backtracking) with Tabulated DP
*/

const knapsackProblem = {

    /**
     * 1. Recursive Solution
     *
     * Solves the 0/1 knapsack problem using a recursive approach.  This is the most basic
     * solution, but it has exponential time complexity and is very inefficient for
     * larger input sets due to redundant calculations.
     *
     * @param {number[]} weights - Array of item weights.
     * @param {number[]} values - Array of item values.
     * @param {number} capacity - Maximum weight capacity of the knapsack.
     * @param {number} n - Number of items.
     * @returns {number} The maximum value that can be carried in the knapsack.
     */
    recursive(weights, values, capacity, n) {
        // Base case: If there are no items or the knapsack has no capacity, the maximum value is 0.
        if (n === 0 || capacity === 0) {
            return 0;
        }

        // If the weight of the current item exceeds the remaining capacity, skip it.
        if (weights[n - 1] > capacity) {
            return this.recursive(weights, values, capacity, n - 1);
        }

        // Return the maximum of two cases:
        // 1. Include the current item and reduce the capacity.
        // 2. Exclude the current item.
        return Math.max(
            values[n - 1] + this.recursive(weights, values, capacity - weights[n - 1], n - 1),
            this.recursive(weights, values, capacity, n - 1)
        );
    },


    /**
     * 2. Memoized (Top-Down) DP Solution
     *
     * Solves the 0/1 knapsack problem using a top-down dynamic programming approach
     * with memoization.  It stores the results of subproblems in a table to avoid
     * redundant calculations, significantly improving performance over the pure
     * recursive solution.
     *
     * @param {number[]} weights - Array of item weights.
     * @param {number[]} values - Array of item values.
     * @param {number} capacity - Maximum weight capacity of the knapsack.
     * @param {number} n - Number of items.
     * @param {number[][]} memo - A 2D array to store the results of subproblems.
     * Initialized with -1 to indicate that a subproblem
     * has not been solved yet.
     * @returns {number} The maximum value that can be carried in the knapsack.
     */
    memoized(weights, values, capacity, n, memo) {
        // Base case: If there are no items or the knapsack has no capacity, the maximum value is 0.
        if (n === 0 || capacity === 0) {
            return 0;
        }

        // If the result for this subproblem is already memoized, return it.
        if (memo[n][capacity] !== -1) {
            return memo[n][capacity];
        }

        // If the weight of the current item exceeds the remaining capacity, skip it.
        if (weights[n - 1] > capacity) {
            memo[n][capacity] = this.memoized(weights, values, capacity, n - 1, memo);
            return memo[n][capacity];
        }

        // Calculate the maximum value and store it in the memo table.
        memo[n][capacity] = Math.max(
            values[n - 1] + this.memoized(weights, values, capacity - weights[n - 1], n - 1, memo),
            this.memoized(weights, values, capacity, n - 1, memo)
        );
        return memo[n][capacity];
    },


    /**
     * 3. Tabulated (Bottom-Up) DP Solution
     *
     * Solves the 0/1 knapsack problem using a bottom-up dynamic programming approach.
     * It iteratively fills a table of subproblem solutions, building up to the final
     * solution.  This approach is generally more efficient than the memoized approach
     * as it avoids the overhead of recursive function calls.
     *
     * @param {number[]} weights - Array of item weights.
     * @param {number[]} values - Array of item values.
     * @param {number} capacity - Maximum weight capacity of the knapsack.
     * @param {number} n - Number of items.
     * @returns {number} The maximum value that can be carried in the knapsack.
     */
    tabulated(weights, values, capacity, n) {
        // Create a table to store the results of subproblems.
        // dp[i][w] stores the maximum value achievable with items up to index i-1
        // and a maximum weight of w.
        const dp = Array(n + 1).fill(null).map(() => Array(capacity + 1).fill(0));

        // Build the table in a bottom-up manner.
        for (let i = 0; i <= n; i++) {
            for (let w = 0; w <= capacity; w++) {
                if (i === 0 || w === 0) {
                    dp[i][w] = 0; // Base case: 0 value with no items or no capacity
                } else if (weights[i - 1] <= w) {
                    // If the current item's weight is within the capacity, decide
                    // whether to include it or not.
                    dp[i][w] = Math.max(
                        values[i - 1] + dp[i - 1][w - weights[i - 1]], // Include the item
                        dp[i - 1][w]                                 // Exclude the item
                    );
                } else {
                    // If the current item's weight exceeds the capacity, exclude it.
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        // The final result is at the bottom-right corner of the table.
        return dp[n][capacity];
    },


    /**
     * 4. Space-Optimized DP Solution
     *
     * Solves the 0/1 knapsack problem using a space-optimized version of the
     * tabulated dynamic programming approach.  It reduces the space complexity
     * from O(n * capacity) to O(capacity) by using only a single 1D array to
     * store the intermediate results.
     *
     * @param {number[]} weights - Array of item weights.
     * @param {number[]} values - Array of item values.
     * @param {number} capacity - Maximum weight capacity of the knapsack.
     * @param {number} n - Number of items.
     * @returns {number} The maximum value that can be carried in the knapsack.
     */
    spaceOptimized(weights, values, capacity, n) {
        // Create a 1D array to store the results of subproblems.
        // dp[w] stores the maximum value achievable with a maximum weight of w.
        const dp = Array(capacity + 1).fill(0);

        // Iterate over the items.
        for (let i = 0; i < n; i++) {
            // Iterate over the capacities in *reverse* order.  This is crucial to avoid
            // overwriting previous subproblem solutions before they are needed.
            for (let w = capacity; w >= 0; w--) {
                if (weights[i] <= w) {
                    // If the current item's weight is within the capacity, decide
                    // whether to include it or not.
                    dp[w] = Math.max(
                        values[i] + dp[w - weights[i]], // Include the item
                        dp[w]                         // Exclude the item
                    );
                }
                // If the current item's weight exceeds the capacity, dp[w] remains unchanged.
            }
        }

        // The final result is at the end of the array.
        return dp[capacity];
    },

    /**
     * 5. Item Tracking (Backtracking) with Tabulated DP
     *
     * Solves the 0/1 knapsack problem using the tabulated dynamic programming approach,
     * and also determines *which* items are included in the optimal solution.  It uses
     * backtracking to trace back through the DP table and identify the items that
     * contributed to the maximum value.
     *
     * @param {number[]} weights - Array of item weights.
     * @param {number[]} values - Array of item values.
     * @param {number} capacity - Maximum weight capacity of the knapsack.
     * @param {number} n - Number of items.
     * @returns {{maxValue: number, items: number[]}}
     * An object containing the maximum value and an array of the *indices* of the
     * items included in the optimal solution (indices are 1-based). Returns empty array if no items are selected.
     */
    tabulatedWithItemTracking(weights, values, capacity, n) {
        // Create a table to store the results of subproblems.
        const dp = Array(n + 1).fill(null).map(() => Array(capacity + 1).fill(0));

        // Build the table in a bottom-up manner.
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

        // The maximum value is at the bottom-right corner of the table.
        const maxValue = dp[n][capacity];

        // Backtrack to find the items included in the optimal solution.
        let w = capacity;
        let i = n;
        const includedItems = [];
        while (i > 0 && w > 0) {
            if (dp[i][w] !== dp[i - 1][w]) {
                // If the value is different, it means the current item was included.
                includedItems.push(i); // Store the item index (1-based)
                w -= weights[i - 1];     // Reduce the capacity
                i--;                 // Move to the previous item
            } else {
                // If the value is the same, the current item was not included.
                i--;
            }
        }

        return { maxValue, items: includedItems };
    },
};



// Example usage:
const weights = [10, 20, 30];
const values = [60, 100, 120];
const capacity = 50;
const n = weights.length;

console.log("Knapsack Problem (0/1 Knapsack)");
console.log("Weights:", weights);
console.log("Values:", values);
console.log("Capacity:", capacity);
console.log("Number of items:", n);
console.log("----------------------------------------");

// 1. Recursive Solution
console.log("1. Recursive Solution:");
const maxValueRecursive = knapsackProblem.recursive(weights, values, capacity, n);
console.log("Maximum value:", maxValueRecursive);  // Output: 220
console.log("----------------------------------------");

// 2. Memoized (Top-Down) DP Solution
console.log("2. Memoized (Top-Down) DP Solution:");
const memo = Array(n + 1).fill(null).map(() => Array(capacity + 1).fill(-1));
const maxValueMemoized = knapsackProblem.memoized(weights, values, capacity, n, memo);
console.log("Maximum value:", maxValueMemoized);  // Output: 220
console.log("Memo Table:", memo);
console.log("----------------------------------------");

// 3. Tabulated (Bottom-Up) DP Solution
console.log("3. Tabulated (Bottom-Up) DP Solution:");
const maxValueTabulated = knapsackProblem.tabulated(weights, values, capacity, n);
console.log("Maximum value:", maxValueTabulated);  // Output: 220
console.log("----------------------------------------");

// 4. Space-Optimized DP Solution
console.log("4. Space-Optimized DP Solution:");
const maxValueSpaceOptimized = knapsackProblem.spaceOptimized(weights, values, capacity, n);
console.log("Maximum value:", maxValueSpaceOptimized);  // Output: 220
console.log("----------------------------------------");

// 5. Item Tracking (Backtracking) with Tabulated DP
console.log("5. Item Tracking (Backtracking) with Tabulated DP:");
const resultWithItems = knapsackProblem.tabulatedWithItemTracking(weights, values, capacity, n);
console.log("Maximum value:", resultWithItems.maxValue);
console.log("Included items (indices):", resultWithItems.items); // Output: [ 3, 2 ]  (items with indices 2 and 3, i.e., 20 and 30 weights)
console.log("----------------------------------------");
