import java.util.Arrays;

public class JumpGame {

    /**
     * Approach 1: Greedy Approach (Most Efficient)
     *
     * Time Complexity: O(n), where n is the length of the array.
     * Space Complexity: O(1).
     *
     * Explanation:
     * The greedy approach works by iterating through the array and keeping track of the
     * farthest reachable index. At each step, we update the farthest reachable index
     * and check if we can reach the end of the array.
     */
    public boolean canJumpGreedy(int[] nums) {
        if (nums == null || nums.length == 0) {
            return false; // Handle null or empty input
        }
        int maxReach = 0; // The farthest index that can be reached
        for (int i = 0; i < nums.length; i++) {
            if (i > maxReach) {
                return false; // If the current index is beyond the maximum reach, we can't reach it.
            }
            maxReach = Math.max(maxReach, i + nums[i]); // Update the maximum reach
            if (maxReach >= nums.length - 1) {
                return true; // If the maximum reach is greater than or equal to the last index, we can reach the end.
            }
        }
        return false; // If the loop finishes without reaching the end, we can't jump to the end.
    }

    /**
     * Approach 2: Dynamic Programming (Top-Down with Memoization)
     *
     * Time Complexity: O(n), where n is the length of the array.
     * Space Complexity: O(n) for the memoization array.
     *
     * Explanation:
     * This approach uses recursion with memoization to avoid redundant calculations.
     * We start from the beginning of the array and recursively check if we can reach
     * the end. The memoization array stores the result for each index to avoid
     * recomputing it.
     */
    public boolean canJumpDPTopDown(int[] nums) {
        if (nums == null || nums.length == 0) {
            return false;
        }
        int[] memo = new int[nums.length];
        Arrays.fill(memo, -1); // -1: unknown, 0: false, 1: true
        memo[nums.length - 1] = 1; // The last index is reachable

        return canJumpFrom(0, nums, memo);
    }

    private boolean canJumpFrom(int position, int[] nums, int[] memo) {
        if (memo[position] != -1) {
            return memo[position] == 1; // Return the memoized result
        }

        int maxJump = Math.min(position + nums[position], nums.length - 1); // Max distance we can jump
        for (int i = maxJump; i > position; i--) {
            if (canJumpFrom(i, nums, memo)) {
                memo[position] = 1; // Mark the current position as reachable
                return true;
            }
        }

        memo[position] = 0; // Mark the current position as unreachable
        return false;
    }

    /**
     * Approach 3: Dynamic Programming (Bottom-Up)
     *
     * Time Complexity: O(n^2), where n is the length of the array.
     * Space Complexity: O(n) for the dp array.
     *
     * Explanation:
     * This approach uses a bottom-up dynamic programming approach. We create a dp array
     * where dp[i] indicates whether we can reach index i. We start from the end of the
     * array and work our way back to the beginning.
     * This approach is less efficient than the greedy approach due to the nested loop.
     */
    public boolean canJumpDPBottomUp(int[] nums) {
        if (nums == null || nums.length == 0) {
            return false;
        }
        boolean[] dp = new boolean[nums.length];
        dp[nums.length - 1] = true; // The last index is reachable

        for (int i = nums.length - 2; i >= 0; i--) {
            int maxJump = Math.min(i + nums[i], nums.length - 1);
            for (int j = i + 1; j <= maxJump; j++) {
                if (dp[j]) {
                    dp[i] = true; // If we can reach any of the next reachable indices, we can reach the current index.
                    break;
                }
            }
        }
        return dp[0]; // Check if we can reach the first index.
    }

    /**
     * Approach 4: Backtracking (Brute Force - Time Limit Exceeded for larger inputs)
     *
     * Time Complexity: O(2^n) in the worst case, where n is the length of the array.
     * Space Complexity: O(n) for the recursion stack.
     *
     * Explanation:
     * This is a brute-force approach that tries all possible paths. It recursively
     * explores all possible jumps from each position. This approach is very inefficient
     * and will result in a time limit exceeded error for larger input arrays.
     */
    public boolean canJumpBacktracking(int[] nums) {
        if (nums == null || nums.length == 0) {
            return false;
        }
        return canJumpFromBacktracking(0, nums);
    }

    private boolean canJumpFromBacktracking(int position, int[] nums) {
        if (position == nums.length - 1) {
            return true; // Base case: If we reach the last index, we are done.
        }

        int maxJump = Math.min(position + nums[position], nums.length - 1);
        for (int i = maxJump; i > position; i--) {
            if (canJumpFromBacktracking(i, nums)) {
                return true; // If we can reach the end from any of the next positions, return true.
            }
        }
        return false; // If we can't reach the end from any of the next positions, return false.
    }

    /**
     * Approach 5: Iterative Greedy (Similar to Approach 1, but with slight variation)
     *
     * Time Complexity: O(n), where n is the length of the array.
     * Space Complexity: O(1).
     *
     * Explanation:
     * This is another greedy approach, similar to the first one, but it iterates backwards.
     * It starts from the end and checks if any previous position can reach the current position.
     */
    public boolean canJumpIterativeGreedy(int[] nums) {
        if (nums == null || nums.length == 0) {
            return false;
        }
        int lastReachable = nums.length - 1; // Initialize the last reachable position to the end.
        for (int i = nums.length - 2; i >= 0; i--) {
            if (i + nums[i] >= lastReachable) {
                lastReachable = i; // Update the last reachable position if the current position can reach it.
            }
        }
        return lastReachable == 0; // If the first position can reach the end, return true.
    }

    public static void main(String[] args) {
        JumpGame solution = new JumpGame();

        // Test cases
        int[] nums1 = {2, 3, 1, 1, 4};
        System.out.println("Can jump to the end (Greedy): " + solution.canJumpGreedy(nums1)); // Output: true
        System.out.println("Can jump to the end (DP Top-Down): " + solution.canJumpDPTopDown(nums1)); // Output: true
        System.out.println("Can jump to the end (DP Bottom-Up): " + solution.canJumpDPBottomUp(nums1)); // Output: true
        System.out.println("Can jump to the end (Backtracking): " + solution.canJumpBacktracking(nums1)); // Output: true
        System.out.println("Can jump to the end (Iterative Greedy): " + solution.canJumpIterativeGreedy(nums1)); // Output: true


        int[] nums2 = {3, 2, 1, 0, 4};
        System.out.println("Can jump to the end (Greedy): " + solution.canJumpGreedy(nums2)); // Output: false
        System.out.println("Can jump to the end (DP Top-Down): " + solution.canJumpDPTopDown(nums2)); // Output: false
        System.out.println("Can jump to the end (DP Bottom-Up): " + solution.canJumpDPBottomUp(nums2)); // Output: false
        System.out.println("Can jump to the end (Backtracking): " + solution.canJumpBacktracking(nums2)); // Output: false
        System.out.println("Can jump to the end (Iterative Greedy): " + solution.canJumpIterativeGreedy(nums2)); // Output: false

        int[] nums3 = {0};
        System.out.println("Can jump to the end (Greedy): " + solution.canJumpGreedy(nums3)); // Output: true
        System.out.println("Can jump to the end (DP Top-Down): " + solution.canJumpDPTopDown(nums3)); // Output: true
        System.out.println("Can jump to the end (DP Bottom-Up): " + solution.canJumpDPBottomUp(nums3)); // Output: true
        System.out.println("Can jump to the end (Backtracking): " + solution.canJumpBacktracking(nums3)); // Output: true
        System.out.println("Can jump to the end (Iterative Greedy): " + solution.canJumpIterativeGreedy(nums3)); // Output: true

        int[] nums4 = {2,0,0};
        System.out.println("Can jump to the end (Greedy): " + solution.canJumpGreedy(nums4)); // Output: true
        System.out.println("Can jump to the end (DP Top-Down): " + solution.canJumpDPTopDown(nums4)); // Output: true
        System.out.println("Can jump to the end (DP Bottom-Up): " + solution.canJumpDPBottomUp(nums4)); // Output: true
        System.out.println("Can jump to the end (Backtracking): " + solution.canJumpBacktracking(nums4)); // Output: true
        System.out.println("Can jump to the end (Iterative Greedy): " + solution.canJumpIterativeGreedy(nums4)); // Output: true
    }
}

