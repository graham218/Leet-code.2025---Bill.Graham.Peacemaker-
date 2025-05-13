import java.util.Arrays;

public class Knapsack {

    /**
     * 0/1 Knapsack Problem
     *
     * Given a set of items, each with a weight and a value, determine the maximum value of items
     * you can include in a knapsack with a given capacity.  Each item can either be included
     * or excluded (0/1).
     */

    // 1. Recursive Approach (Basic)
    // Time Complexity: O(2^n) - Exponential
    // Space Complexity: O(n) - Depth of the recursion tree
    public static int knapsackRecursive(int capacity, int[] weights, int[] values, int n) {
        // Base case: If no items or capacity is 0, the maximum value is 0
        if (n == 0 || capacity == 0) {
            return 0;
        }

        // If the weight of the current item is more than the capacity,
        // exclude it and solve for the remaining items
        if (weights[n - 1] > capacity) {
            return knapsackRecursive(capacity, weights, values, n - 1);
        } else {
            // Otherwise, we have two choices:
            // 1. Include the current item and reduce the capacity
            // 2. Exclude the current item
            // Return the maximum of these two choices
            int includeItem = values[n - 1] + knapsackRecursive(capacity - weights[n - 1], weights, values, n - 1);
            int excludeItem = knapsackRecursive(capacity, weights, values, n - 1);
            return Math.max(includeItem, excludeItem);
        }
    }

    // 2. Memoization (Top-Down Dynamic Programming)
    // Time Complexity: O(n * capacity)
    // Space Complexity: O(n * capacity) + O(n) for recursion stack
    public static int knapsackMemoization(int capacity, int[] weights, int[] values, int n, int[][] memo) {
        // Base case: If no items or capacity is 0, the maximum value is 0
        if (n == 0 || capacity == 0) {
            return 0;
        }

        // If the result is already memoized, return it
        if (memo[n][capacity] != -1) {
            return memo[n][capacity];
        }

        // If the weight of the current item is more than the capacity,
        // exclude it and solve for the remaining items
        if (weights[n - 1] > capacity) {
            memo[n][capacity] = knapsackMemoization(capacity, weights, values, n - 1, memo);
            return memo[n][capacity];
        } else {
            // Otherwise, we have two choices:
            // 1. Include the current item and reduce the capacity
            // 2. Exclude the current item
            // Store the result in the memo table and return it
            int includeItem = values[n - 1] + knapsackMemoization(capacity - weights[n - 1], weights, values, n - 1, memo);
            int excludeItem = knapsackMemoization(capacity, weights, values, n - 1, memo);
            memo[n][capacity] = Math.max(includeItem, excludeItem);
            return memo[n][capacity];
        }
    }

    // 3. Tabulation (Bottom-Up Dynamic Programming)
    // Time Complexity: O(n * capacity)
    // Space Complexity: O(n * capacity)
    public static int knapsackTabulation(int capacity, int[] weights, int[] values, int n) {
        // Create a table to store the results of subproblems
        int[][] dp = new int[n + 1][capacity + 1];

        // Initialize the first row and column to 0 (base case)
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }
        for (int j = 0; j <= capacity; j++) {
            dp[0][j] = 0;
        }

        // Fill the table in a bottom-up manner
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= capacity; j++) {
                if (weights[i - 1] > j) {
                    // If the weight of the current item is more than the current capacity,
                    // take the value from the previous row
                    dp[i][j] = dp[i - 1][j];
                } else {
                    // Otherwise, we have two choices:
                    // 1. Include the current item
                    // 2. Exclude the current item
                    // Take the maximum of these two choices
                    int includeItem = values[i - 1] + dp[i - 1][j - weights[i - 1]];
                    int excludeItem = dp[i - 1][j];
                    dp[i][j] = Math.max(includeItem, excludeItem);
                }
            }
        }

        // The result is at the bottom-right corner of the table
        return dp[n][capacity];
    }

    // 4. Space Optimized Tabulation (Bottom-Up Dynamic Programming)
    // Time Complexity: O(n * capacity)
    // Space Complexity: O(capacity) - Optimized space
    public static int knapsackSpaceOptimized(int capacity, int[] weights, int[] values, int n) {
        // Create a 1D array to store the results of subproblems
        int[] dp = new int[capacity + 1];

        // Initialize the array to 0
        Arrays.fill(dp, 0);

        // Iterate over the items
        for (int i = 0; i < n; i++) {
            // Iterate over the capacity in reverse order
            // This is important to avoid overwriting previous results needed for the calculation
            for (int j = capacity; j >= weights[i]; j--) {
                // Update the dp array with the maximum value
                // between including and excluding the current item
                dp[j] = Math.max(dp[j], values[i] + dp[j - weights[i]]);
            }
        }

        // The result is at the last index of the array
        return dp[capacity];
    }

    // 5.  Recursive Approach with Memoization and Explicit Table
    // Time Complexity: O(n * capacity)
    // Space Complexity: O(n * capacity)
    public static int knapsackRecursiveMemo(int capacity, int[] weights, int[] values, int n) {
        int[][] memo = new int[n + 1][capacity + 1];
        for (int[] row : memo) {
            Arrays.fill(row, -1);
        }
        return knapsackMemoization(capacity, weights, values, n, memo);
    }

    public static void main(String[] args) {
        int[] values = {60, 100, 120};
        int[] weights = {10, 20, 30};
        int capacity = 50;
        int n = values.length;

        System.out.println("0/1 Knapsack Problem");
        System.out.println("Values: " + Arrays.toString(values));
        System.out.println("Weights: " + Arrays.toString(weights));
        System.out.println("Capacity: " + capacity);

        // 1. Recursive Approach
        long startTime = System.nanoTime();
        int maxValueRecursive = knapsackRecursive(capacity, weights, values, n);
        long endTime = System.nanoTime();
        System.out.println("\n1. Recursive Approach: Maximum Value = " + maxValueRecursive);
        System.out.println("   Time taken: " + (endTime - startTime) + " ns");

        // 2. Memoization Approach
        int[][] memo = new int[n + 1][capacity + 1];
        for (int[] row : memo) {
            Arrays.fill(row, -1);
        }
        startTime = System.nanoTime();
        int maxValueMemoization = knapsackMemoization(capacity, weights, values, n, memo);
        endTime = System.nanoTime();
        System.out.println("2. Memoization Approach: Maximum Value = " + maxValueMemoization);
        System.out.println("   Time taken: " + (endTime - startTime) + " ns");

        // 3. Tabulation Approach
        startTime = System.nanoTime();
        int maxValueTabulation = knapsackTabulation(capacity, weights, values, n);
        endTime = System.nanoTime();
        System.out.println("3. Tabulation Approach: Maximum Value = " + maxValueTabulation);
        System.out.println("   Time taken: " + (endTime - startTime) + " ns");

        // 4. Space Optimized Tabulation Approach
        startTime = System.nanoTime();
        int maxValueSpaceOptimized = knapsackSpaceOptimized(capacity, weights, values, n);
        endTime = System.nanoTime();
        System.out.println("4. Space Optimized Approach: Maximum Value = " + maxValueSpaceOptimized);
        System.out.println("   Time taken: " + (endTime - startTime) + " ns");

        // 5. Recursive with Memoization (using helper function)
        startTime = System.nanoTime();
        int maxValueRecursiveMemo = knapsackRecursiveMemo(capacity, weights, values, n);
        endTime = System.nanoTime();
        System.out.println("5. Recursive + Memoization Approach: Maximum Value = " + maxValueRecursiveMemo);
        System.out.println("   Time taken: " + (endTime - startTime) + " ns");
    }
}

