import java.util.Arrays;

public class HouseRobber {

    /**
     * House Robber Problem:
     * You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed,
     * the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected
     * and it will automatically contact the police if two adjacent houses were robbed on the same night.
     *
     * Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
     *
     * Example 1:
     * Input: nums = [1,2,3,1]
     * Output: 4
     * Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
     * Total amount you can rob = 1 + 3 = 4.
     *
     * Example 2:
     * Input: nums = [2,7,9,3,1]
     * Output: 12
     * Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
     * Total amount you can rob = 2 + 9 + 1 = 12.
     *
     * Constraints:
     * 1 <= nums.length <= 100
     * 0 <= nums[i] <= 400
     */

    // Approach 1: Recursive Approach (Top-Down)
    // Time Complexity: O(2^n) - Exponential, due to overlapping subproblems.
    // Space Complexity: O(n) -  Due to the recursion call stack.
    public static int robRecursive(int[] nums, int i) {
        if (i < 0) {
            return 0;
        }
        //Choice to rob current house or not to rob
        return Math.max(robRecursive(nums, i - 2) + nums[i], robRecursive(nums, i - 1));
    }

    // Approach 2: Memoization (Top-Down Dynamic Programming)
    // Time Complexity: O(n) - Each subproblem is solved only once.
    // Space Complexity: O(n) -  O(n) for memoization array + O(n) for recursion stack.
    public static int robMemo(int[] nums, int i, int[] memo) {
        if (i < 0) {
            return 0;
        }
        if (memo[i] != -1) {
            return memo[i];
        }
        //Choice to rob current house or not to rob
        memo[i] = Math.max(robMemo(nums, i - 2, memo) + nums[i], robMemo(nums, i - 1, memo));
        return memo[i];
    }

    // Approach 3: Tabulation (Bottom-Up Dynamic Programming)
    // Time Complexity: O(n) - Iterating through the array once.
    // Space Complexity: O(n) - Using a DP table of size n.
    public static int robTabulation(int[] nums) {
        if (nums == null || nums.length == 0) {
            return 0;
        }
        int n = nums.length;
        if (n == 1) return nums[0];

        int[] dp = new int[n];
        dp[0] = nums[0];
        dp[1] = Math.max(nums[0], nums[1]);

        for (int i = 2; i < n; i++) {
            //Choice to rob current house or not to rob
            dp[i] = Math.max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[n - 1];
    }

    // Approach 4: Optimized Tabulation (Bottom-Up Dynamic Programming with Constant Space)
    // Time Complexity: O(n) - Iterating through the array once.
    // Space Complexity: O(1) - Using only two variables.
    public static int robOptimized(int[] nums) {
        if (nums == null || nums.length == 0) {
            return 0;
        }
        int n = nums.length;
        if (n == 1) return nums[0];

        int prev2 = 0;  // Represents dp[i-2]
        int prev1 = 0;  // Represents dp[i-1]
        int current = 0;

        for (int i = 0; i < n; i++) {
            //Choice to rob current house or not to rob
            current = Math.max(prev2 + nums[i], prev1);
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }

    // Approach 5: Iterative with only relevant variables
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    public static int robIterative(int[] nums) {
        if (nums == null || nums.length == 0) return 0;
        int rob = 0; // max money robbed including the current house
        int notRob = 0; // max money robbed excluding the current house

        for (int num : nums) {
            int newRob = Math.max(notRob + num, rob);
            notRob = Math.max(notRob, rob);
            rob = newRob;
        }
        return rob;
    }

    public static void main(String[] args) {
        int[] nums = {2, 7, 9, 3, 1};

        // Approach 1: Recursive
        System.out.println("Recursive Approach: " + robRecursive(nums, nums.length - 1)); // Output: 12

        // Approach 2: Memoization
        int[] memo = new int[nums.length];
        Arrays.fill(memo, -1);
        System.out.println("Memoization Approach: " + robMemo(nums, nums.length - 1, memo)); // Output: 12

        // Approach 3: Tabulation
        System.out.println("Tabulation Approach: " + robTabulation(nums)); // Output: 12

        // Approach 4: Optimized Tabulation
        System.out.println("Optimized Tabulation Approach: " + robOptimized(nums)); // Output: 12

        // Approach 5: Iterative with only relevant variables
        System.out.println("Iterative Approach: " + robIterative(nums));
    }
}

