import java.util.Arrays;

public class KnapsackProblem {

    /**
     * 0/1 Knapsack Problem
     *
     * You are given a knapsack with a maximum weight capacity W, and a set of items, each with a weight wi and a value vi.
     * The goal is to determine the maximum total value of items that can be included in the knapsack, without exceeding its capacity.
     * You cannot break an item; you either take it entirely or leave it behind (0/1 choice).
     */

    // 1. Recursive Approach (Basic)
    //    - Time Complexity: O(2^n) - Exponential, where n is the number of items
    //    - Space Complexity: O(n) - Due to the call stack in recursion
    //    - Explanation: Explores all possible combinations of items (include or exclude) to find the optimal solution.
    //                   It's very inefficient for larger input sets due to its exponential nature.
    public static int knapsackRecursive(int W, int[] weights, int[] values, int n) {
        // Base case: If there are no items or the knapsack has no capacity, the maximum value is 0.
        if (n == 0 || W == 0) {
            return 0;
        }

        // If the weight of the current item is greater than the remaining capacity,
        // we can't include it, so we move on to the next item.
        if (weights[n - 1] > W) {
            return knapsackRecursive(W, weights, values, n - 1);
        } else {
            // Otherwise, we have two choices:
            // 1. Include the current item:  Subtract its weight from the capacity and add its value.
            // 2. Exclude the current item: Move on to the next item without changing the capacity.
            // We take the maximum of these two choices.
            int includeItem = values[n - 1] + knapsackRecursive(W - weights[n - 1], weights, values, n - 1);
            int excludeItem = knapsackRecursive(W, weights, values, n - 1);
            return Math.max(includeItem, excludeItem);
        }
    }



    // 2. Memoization (Top-Down Dynamic Programming)
    //    - Time Complexity: O(n * W) - Pseudo-polynomial, where n is the number of items and W is the knapsack capacity
    //    - Space Complexity: O(n * W) -  for the memoization table (dp array) + O(n) for recursion stack.
    //    - Explanation:  Improves upon the recursive approach by storing the results of solved subproblems
    //                    in a table (dp array).  This prevents redundant calculations, significantly
    //                    reducing the time complexity.  It's still recursive but much more efficient.
    public static int knapsackMemoization(int W, int[] weights, int[] values, int n, int[][] dp) {
        if (n == 0 || W == 0) {
            return 0;
        }

        // Check if the result for this subproblem is already stored in the dp table.
        if (dp[n][W] != -1) {
            return dp[n][W];
        }

        if (weights[n - 1] > W) {
            // Store the result in the dp table before returning.
            dp[n][W] = knapsackMemoization(W, weights, values, n - 1, dp);
            return dp[n][W];
        } else {
            int includeItem = values[n - 1] + knapsackMemoization(W - weights[n - 1], weights, values, n - 1, dp);
            int excludeItem = knapsackMemoization(W, weights, values, n - 1, dp);
            // Store the result in the dp table before returning.
            dp[n][W] = Math.max(includeItem, excludeItem);
            return dp[n][W];
        }
    }

    public static int knapsackMemoization(int W, int[] weights, int[] values) {
        int n = weights.length;
        // Create a 2D array to store the results of subproblems.  Initialize all values to -1 (indicating not calculated).
        int[][] dp = new int[n + 1][W + 1];
        for (int[] row : dp) {
            Arrays.fill(row, -1);
        }
        return knapsackMemoization(W, weights, values, n, dp);
    }


    // 3. Tabulation (Bottom-Up Dynamic Programming)
    //    - Time Complexity: O(n * W) - Pseudo-polynomial
    //    - Space Complexity: O(n * W) - for the dp table
    //    - Explanation:  A non-recursive, iterative approach to dynamic programming.  It builds the dp table
    //                    from the bottom up, starting with the base cases and systematically filling it in.
    //                    Often slightly more efficient than memoization due to the absence of recursive overhead.
    public static int knapsackTabulation(int W, int[] weights, int[] values) {
        int n = weights.length;
        // Create a 2D array to store the results of subproblems.
        int[][] dp = new int[n + 1][W + 1];

        // Initialize the first row and column of the dp table to 0 (base cases).
        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }
        for (int j = 0; j <= W; j++) {
            dp[0][j] = 0;
        }

        // Fill the dp table in a bottom-up manner.
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= W; j++) {
                if (weights[i - 1] > j) {
                    // If the current item's weight is greater than the current capacity, exclude it.
                    dp[i][j] = dp[i - 1][j];
                } else {
                    // Otherwise, take the maximum of including or excluding the item.
                    dp[i][j] = Math.max(values[i - 1] + dp[i - 1][j - weights[i - 1]], dp[i - 1][j]);
                }
            }
        }
        // The final result is stored in the bottom-right corner of the dp table.
        return dp[n][W];
    }

    // 4. Space-Optimized Tabulation
    //    - Time Complexity: O(n * W) - Pseudo-polynomial
    //    - Space Complexity: O(W)     -  Uses only a 1D array of size W+1.
    //    - Explanation:  A further optimization of the tabulation method.  It reduces the space complexity
    //                    from O(n * W) to O(W) by realizing that to calculate dp[i][j], we only need
    //                    the values from the previous row (dp[i-1]).  Therefore, we can use a single 1D array
    //                    and update it in place.
    public static int knapsackSpaceOptimized(int W, int[] weights, int[] values) {
        int n = weights.length;
        // Create a 1D array to store the results.
        int[] dp = new int[W + 1];

        // Iterate through each item.
        for (int i = 0; i < n; i++) {
            // Iterate through the capacity in *reverse* order.  This is crucial to avoid overwriting
            // values that are needed for subsequent calculations in the same iteration.
            for (int j = W; j >= weights[i]; j--) {
                // Calculate the maximum value by either including or excluding the current item.
                dp[j] = Math.max(dp[j], values[i] + dp[j - weights[i]]);
            }
        }
        // The final result is at the end of the dp array.
        return dp[W];
    }



    // 5. Greedy Approach (Incorrect for 0/1 Knapsack)
    //    - Time Complexity: O(n log n) -  due to sorting.
    //    - Space Complexity: O(1)       -  excluding the space used for sorting (which might be O(n) depending on the algorithm)
    //    - Explanation:  This approach is *incorrect* for the 0/1 Knapsack problem, but it's included here for comparison.
    //                    It calculates the value-to-weight ratio for each item, sorts the items in descending order
    //                    of this ratio, and then greedily adds items to the knapsack until it's full.
    //                    This works for the Fractional Knapsack problem (where you can take fractions of items)
    //                    but not for the 0/1 Knapsack problem, where you must take an item entirely or not at all.
    //                    Greedy approach does NOT guarantee optimal solution for 0/1 Knapsack.
    public static int knapsackGreedy(int W, int[] weights, int[] values) {
        int n = weights.length;
        // Create an array to store the value-to-weight ratios.
        double[] ratios = new double[n];
        for (int i = 0; i < n; i++) {
            ratios[i] = (double) values[i] / weights[i];
        }

        // Create an array of indices to keep track of the original item order.
        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }

        // Sort the indices array based on the ratios in descending order.  Use a stable sort.
        Arrays.sort(indices, (i, j) -> Double.compare(ratios[j], ratios[i]));

        int totalValue = 0;
        int remainingCapacity = W;
        // Greedily add items based on the sorted ratios.
        for (int i = 0; i < n; i++) {
            int index = indices[i];
            if (weights[index] <= remainingCapacity) {
                totalValue += values[index];
                remainingCapacity -= weights[index];
            }
            // In 0/1 knapsack, we either take the whole item or leave it.  There is no else condition.
        }
        return totalValue;
    }


    public static void main(String[] args) {
        // Example usage:
        int knapsackCapacity = 10;
        int[] itemWeights = {2, 4, 6, 3, 8};
        int[] itemValues = {6, 10, 12, 7, 15};
        int numberOfItems = itemWeights.length;

        System.out.println("0/1 Knapsack Problem:");
        System.out.println("Knapsack Capacity: " + knapsackCapacity);
        System.out.println("Item Weights: " + Arrays.toString(itemWeights));
        System.out.println("Item Values: " + Arrays.toString(itemValues));
        System.out.println();

        // 1. Recursive Approach
        long startTimeRecursive = System.nanoTime();
        int maxValueRecursive = knapsackRecursive(knapsackCapacity, itemWeights, itemValues, numberOfItems);
        long endTimeRecursive = System.nanoTime();
        long durationRecursive = endTimeRecursive - startTimeRecursive;
        System.out.println("1. Recursive Approach:");
        System.out.println("   Maximum Value: " + maxValueRecursive);
        System.out.println("   Time Taken: " + durationRecursive + " nanoseconds");

        // 2. Memoization Approach
        long startTimeMemoization = System.nanoTime();
        int maxValueMemoization = knapsackMemoization(knapsackCapacity, itemWeights, itemValues);
        long endTimeMemoization = System.nanoTime();
        long durationMemoization = endTimeMemoization - startTimeMemoization;
        System.out.println("\n2. Memoization Approach:");
        System.out.println("   Maximum Value: " + maxValueMemoization);
        System.out.println("   Time Taken: " + durationMemoization + " nanoseconds");

        // 3. Tabulation Approach
        long startTimeTabulation = System.nanoTime();
        int maxValueTabulation = knapsackTabulation(knapsackCapacity, itemWeights, itemValues);
        long endTimeTabulation = System.nanoTime();
        long durationTabulation = endTimeTabulation - startTimeTabulation;
        System.out.println("\n3. Tabulation Approach:");
        System.out.println("   Maximum Value: " + maxValueTabulation);
        System.out.println("   Time Taken: " + durationTabulation + " nanoseconds");

        // 4. Space-Optimized Tabulation Approach
        long startTimeSpaceOptimized = System.nanoTime();
        int maxValueSpaceOptimized = knapsackSpaceOptimized(knapsackCapacity, itemWeights, itemValues);
        long endTimeSpaceOptimized = System.nanoTime();
        long durationSpaceOptimized = endTimeSpaceOptimized - startTimeSpaceOptimized;
        System.out.println("\n4. Space-Optimized Tabulation Approach:");
        System.out.println("   Maximum Value: " + maxValueSpaceOptimized);
        System.out.println("   Time Taken: " + durationSpaceOptimized + " nanoseconds");

        // 5. Greedy Approach (Incorrect for 0/1 Knapsack)
        long startTimeGreedy = System.nanoTime();
        int maxValueGreedy = knapsackGreedy(knapsackCapacity, itemWeights, itemValues);
        long endTimeGreedy = System.nanoTime();
        long durationGreedy = endTimeGreedy - startTimeGreedy;
        System.out.println("\n5. Greedy Approach (Incorrect for 0/1 Knapsack):");
        System.out.println("   Maximum Value: " + maxValueGreedy);
        System.out.println("   Time Taken: " + durationGreedy + " nanoseconds");


        System.out.println("\n\nReal-World Applications of the 0/1 Knapsack Problem:");
        System.out.println("1. **Resource Allocation:** A project manager has a limited budget and a set of tasks, each with a cost and a benefit.  The problem is to choose the tasks that maximize the total benefit without exceeding the budget.");
        System.out.println("2. **Investment Decisions:** A venture capitalist has a limited amount of capital and several investment opportunities, each with a cost and a potential return.  The problem is to select the investments that maximize the total return without exceeding the capital.");
        System.out.println("3. **Cargo Loading:** A cargo ship has a maximum weight capacity and a set of containers, each with a weight and a value.  The problem is to choose the containers to load onto the ship to maximize the total value without exceeding the weight capacity.");
        System.out.println("4. **Theft Scenario:** A thief breaks into a vault with a knapsack of limited capacity.  There are various items, each with a weight and a value.  The thief wants to maximize the value of the loot without exceeding the knapsack's capacity. (This is the classic, albeit unethical, example)");
        System.out.println("5. **Portfolio Optimization:** A financial advisor wants to select a portfolio of assets. Each asset has an expected return and a cost. The advisor aims to maximize the expected return while staying within a budget.");
    }
}

