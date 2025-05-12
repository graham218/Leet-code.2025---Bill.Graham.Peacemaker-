import java.util.Arrays;

public class HouseRobber {

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
     * Approach 1: Recursive Approach (Top-Down) - Basic Implementation
     * - This is the most basic approach, exploring all possible combinations of robbing or not robbing a house.
     * - It has exponential time complexity, making it inefficient for larger input sizes.
     * - Real-world context: Useful for understanding the problem's core logic, but not suitable for performance-critical applications.  Good for teaching the concept of recursion.
     *
     */
    public static int robRecursive(int[] nums) {
        return robRecursiveHelper(nums, nums.length - 1);
    }

    private static int robRecursiveHelper(int[] nums, int i) {
        if (i < 0) {
            return 0;
        }
        //Choice: rob current house or not rob it.
        int rob = nums[i] + (i - 2 >= 0 ? robRecursiveHelper(nums, i - 2) : 0); //Rob current house and add to the maximum of the houses before the previous
        int notRob = robRecursiveHelper(nums, i - 1); //Don't rob, so take the maximum from the previous house.

        return Math.max(rob, notRob);
    }

    /**
     * Approach 2: Memoization (Top-Down Dynamic Programming)
     * - This approach optimizes the recursive solution by storing the results of subproblems to avoid redundant calculations.
     * - It uses a memoization table (dp array) to store the maximum amount of money that can be robbed up to a certain house.
     * - Time Complexity: O(n), Space Complexity: O(n)
     * - Real-world context: A significant improvement over the basic recursion.  Useful when the input size is moderate.  A good example of how to optimize recursive solutions.
     */
    public static int robMemoization(int[] nums) {
        if (nums == null || nums.length == 0) {
            return 0;
        }
        int[] dp = new int[nums.length];
        Arrays.fill(dp, -1); // Initialize dp array with -1 to indicate that the subproblem has not been solved yet.
        return robMemoizationHelper(nums, nums.length - 1, dp);
    }

    private static int robMemoizationHelper(int[] nums, int i, int[] dp) {
        if (i < 0) {
            return 0;
        }
        if (dp[i] != -1) {
            return dp[i]; // Return the stored result if it's already calculated.
        }

        int rob = nums[i] + (i - 2 >= 0 ? robMemoizationHelper(nums, i - 2, dp) : 0);
        int notRob = robMemoizationHelper(nums, i - 1, dp);

        dp[i] = Math.max(rob, notRob); // Store the result in the dp array.
        return dp[i];
    }

    /**
     * Approach 3: Tabulation (Bottom-Up Dynamic Programming)
     * - This is a bottom-up approach where we iteratively calculate the maximum amount of money that can be robbed for each house.
     * - It builds a table (dp array) from the beginning, filling it in a specific order until the final result is obtained.
     * - Time Complexity: O(n), Space Complexity: O(n)
     * - Real-world context: Generally preferred over memoization due to its iterative nature, which can be more efficient in some cases.  Very common DP approach in production.
     */
    public static int robTabulation(int[] nums) {
        if (nums == null || nums.length == 0) {
            return 0;
        }
        int n = nums.length;
        int[] dp = new int[n];
        dp[0] = nums[0]; //Base case
        if (n > 1) {
            dp[1] = Math.max(nums[0], nums[1]); //Base case
        }

        for (int i = 2; i < n; i++) {
            dp[i] = Math.max(nums[i] + dp[i - 2], dp[i - 1]); //Transition function
        }
        return dp[n - 1];
    }

    /**
     * Approach 4: Optimized Tabulation (Constant Space)
     * - This approach further optimizes the tabulation method by reducing the space complexity to O(1).
     * - It observes that to calculate dp[i], we only need dp[i-1] and dp[i-2]. Therefore, we can store these two values in variables and update them iteratively.
     * - Time Complexity: O(n), Space Complexity: O(1)
     * - Real-world context: The most efficient solution in terms of space complexity.  Ideal for resource-constrained environments like embedded systems or mobile devices.  A very practical optimization.
     */
    public static int robOptimized(int[] nums) {
        if (nums == null || nums.length == 0) {
            return 0;
        }
        int n = nums.length;
        if (n == 1) return nums[0];
        if (n == 2) return Math.max(nums[0], nums[1]);

        int prev2 = nums[0]; // Represents dp[i-2]
        int prev1 = Math.max(nums[0], nums[1]); // Represents dp[i-1]
        int current = 0;

        for (int i = 2; i < n; i++) {
            current = Math.max(nums[i] + prev2, prev1);
            prev2 = prev1; //update
            prev1 = current; //update
        }
        return prev1;
    }

    /**
     * Approach 5: Divide and Conquer (for very large arrays - conceptual)
     * - This approach is more conceptual and suitable for *extremely* large arrays that might exceed memory limits in a single pass.
     * - The idea is to divide the array into smaller subproblems, solve each subproblem independently (using tabulation or optimized tabulation),
     * and then combine the results.  This can be parallelized.
     * -  It adds overhead for dividing and combining, so it's only beneficial for *very* large `n`.
     * - Real-world context: Useful in distributed computing scenarios where the data is spread across multiple machines.  Applicable to very large datasets, such as processing financial transactions or analyzing data from numerous sensors.
     *
     * - Note: This is NOT a standard DP approach for the House Robber problem.  It's included to show how the problem could be adapted for a divide-and-conquer strategy in specific large-scale scenarios.
     */
    public static int robDivideConquer(int[] nums) {
        if (nums == null || nums.length == 0) {
            return 0;
        }
        int n = nums.length;
        if (n <= 4) { // Base case: use a standard DP approach for small arrays
            return robOptimized(nums);
        }

        // Divide the array into two halves (or more, for deeper division)
        int mid = n / 2;
        int[] leftHalf = Arrays.copyOfRange(nums, 0, mid);
        int[] rightHalf = Arrays.copyOfRange(nums, mid, n);

        // Recursively solve for each half (can be done in parallel)
        int maxLeft = robDivideConquer(leftHalf);
        int maxRight = robDivideConquer(rightHalf);

        // Need to consider the overlap: the last house of the left half and the first house of the right half.
        // We can't simply add maxLeft + maxRight, as they might be adjacent.
        // We need to consider cases where we rob either, both, or none of the boundary houses.

        // Calculate the maximum for the combined array, considering the boundary houses.
        int combinedMax = Math.max(maxLeft + robOptimized(Arrays.copyOfRange(nums, mid+2, n)),  //Rob left side, and right side starting from 2 houses after the mid
                robOptimized(Arrays.copyOfRange(nums, 0, mid-1)) + maxRight); //Rob right side and left side until 2 houses before the mid

        return Math.max(combinedMax, maxLeft + maxRight); // Consider the simple sum of the two halves
    }

    public static void main(String[] args) {
        int[] houses = {2, 7, 9, 3, 1};
        System.out.println("Input: " + Arrays.toString(houses));

        System.out.println("Recursive Approach: " + robRecursive(houses)); //12
        System.out.println("Memoization Approach: " + robMemoization(houses)); //12
        System.out.println("Tabulation Approach: " + robTabulation(houses)); //12
        System.out.println("Optimized Tabulation Approach: " + robOptimized(houses)); //12
        System.out.println("Divide and Conquer Approach: " + robDivideConquer(houses)); //12

        int[] largeHouses = new int[1000];
        Arrays.fill(largeHouses, 1);
        System.out.println("Optimized Tabulation for large array: " + robOptimized(largeHouses)); //500.  This will be fast.

        int[] veryLargeHouses = new int[1000000]; // Example of a very large array
        Arrays.fill(veryLargeHouses, 1);
        System.out.println("Divide and Conquer for very large array: " + robDivideConquer(veryLargeHouses)); //500000.  This is where divide and conquer *might* start to show benefits, especially if parallelized, though the overhead is significant.
    }
}

