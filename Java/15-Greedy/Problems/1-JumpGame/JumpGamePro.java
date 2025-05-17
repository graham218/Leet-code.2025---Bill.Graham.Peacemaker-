import java.util.Arrays;

public class JumpGame {

    public static void main(String[] args) {
        int[] nums1 = {2, 3, 1, 1, 4};
        int[] nums2 = {3, 2, 1, 0, 4};
        int[] nums3 = {0};
        int[] nums4 = {2, 0, 0};
        int[] nums5 = {2, 5, 0, 0};

        // Example Usage and Explanation of Approaches
        System.out.println("Jump Game Solutions:");

        // Approach 1: Greedy (Most Efficient)
        System.out.println("\nApproach 1: Greedy (Most Efficient)");
        System.out.println("Can reach the end? " + canJumpGreedy(nums1)); // true
        System.out.println("Can reach the end? " + canJumpGreedy(nums2)); // false
        System.out.println("Can reach the end? " + canJumpGreedy(nums3)); // true
        System.out.println("Can reach the end? " + canJumpGreedy(nums4)); // true
        System.out.println("Can reach the end? " + canJumpGreedy(nums5)); // true
        //Real-world application: Optimizing resource allocation.

        // Approach 2: Dynamic Programming (Top-Down with Memoization)
        System.out.println("\nApproach 2: Dynamic Programming (Top-Down with Memoization)");
        System.out.println("Can reach the end? " + canJumpDP(nums1)); // true
        System.out.println("Can reach the end? " + canJumpDP(nums2)); // false
        System.out.println("Can reach the end? " + canJumpDP(nums3)); // true
        System.out.println("Can reach the end? " + canJumpDP(nums4)); // true
        System.out.println("Can reach the end? " + canJumpDP(nums5)); // true
        //Real-world application: Solving complex decision-making problems.

        // Approach 3: Dynamic Programming (Bottom-Up)
        System.out.println("\nApproach 3: Dynamic Programming (Bottom-Up)");
        System.out.println("Can reach the end? " + canJumpDPBottomUp(nums1)); // true
        System.out.println("Can reach the end? " + canJumpDPBottomUp(nums2)); // false
        System.out.println("Can reach the end? " + canJumpDPBottomUp(nums3)); // true
        System.out.println("Can reach the end? " + canJumpDPBottomUp(nums4)); // true
        System.out.println("Can reach the end? " + canJumpDPBottomUp(nums5)); // true
        //Real-world application: Route planning and navigation.

        // Approach 4: Backtracking
        System.out.println("\nApproach 4: Backtracking");
        System.out.println("Can reach the end? " + canJumpBacktracking(nums1));
        System.out.println("Can reach the end? " + canJumpBacktracking(nums2));
        System.out.println("Can reach the end? " + canJumpBacktracking(nums3));
        System.out.println("Can reach the end? " + canJumpBacktracking(nums4));
        System.out.println("Can reach the end? " + canJumpBacktracking(nums5));
        //Real-world application: Game playing and AI.

        // Approach 5: Recursive
        System.out.println("\nApproach 5: Recursive");
        System.out.println("Can reach the end? " + canJumpRecursive(nums1, 0));
        System.out.println("Can reach the end? " + canJumpRecursive(nums2, 0));
        System.out.println("Can reach the end? " + canJumpRecursive(nums3, 0));
        System.out.println("Can reach the end? " + canJumpRecursive(nums4, 0));
        System.out.println("Can reach the end? " + canJumpRecursive(nums5, 0));
        //Real-world application: Parsing and evaluating expressions.
    }

    /**
     * Approach 1: Greedy Algorithm (Most Efficient)
     *
     * - Time Complexity: O(n), where n is the length of the array.
     * - Space Complexity: O(1), constant extra space.
     * - Explanation:
     * - The greedy approach iterates through the array, keeping track of the
     * farthest reachable index.
     * - At each step, it updates the farthest reachable index and checks if
     * the current position is beyond the farthest reach.
     * - This is the most efficient solution because it only requires a single pass
     * through the array.
     * - Real-world application:
     * - Optimizing resource allocation: Imagine you have a set of tasks with
     * varying durations and deadlines. You can use a greedy approach to
     * schedule the tasks to maximize the number of completed tasks or
     * minimize the overall completion time.
     *
     * @param nums The input array representing jump lengths at each position.
     * @return True if it's possible to reach the end of the array, false otherwise.
     */
    public static boolean canJumpGreedy(int[] nums) {
        int maxReach = 0; // Initialize the farthest reachable index.
        for (int i = 0; i < nums.length; i++) {
            if (i > maxReach) { // If the current index is beyond reach, we can't reach the end.
                return false;
            }
            maxReach = Math.max(maxReach, i + nums[i]); // Update the farthest reachable index.
        }
        return true; // If the loop finishes, we can reach the end.
    }

    /**
     * Approach 2: Dynamic Programming (Top-Down with Memoization)
     *
     * - Time Complexity: O(n^2), where n is the length of the array in the worst case.
     * - Space Complexity: O(n), for the memoization array and recursion stack.
     * - Explanation:
     * - This approach uses dynamic programming with memoization (top-down).
     * - It creates a memoization array to store the results of subproblems.
     * - The `canJumpFromPosition` function recursively checks if it's possible
     * to reach the end from a given position.
     * - Memoization avoids redundant calculations by storing the results of
     * already solved subproblems.
     * - Real-world application:
     * - Solving complex decision-making problems: Consider a scenario where you
     * need to make a series of decisions, and each decision affects the
     * outcome of subsequent decisions. Dynamic programming can help you
     * find the optimal sequence of decisions by breaking down the problem
     * into smaller, overlapping subproblems and storing the solutions to
     * these subproblems.
     *
     * @param nums The input array.
     * @return True if it's possible to reach the end, false otherwise.
     */
    public static boolean canJumpDP(int[] nums) {
        int[] memo = new int[nums.length];
        Arrays.fill(memo, -1); // Initialize memo array with -1 (unvisited).
        memo[nums.length - 1] = 1; // Base case: last position is reachable.
        return canJumpFromPosition(0, nums, memo) == 1;
    }

    private static int canJumpFromPosition(int position, int[] nums, int[] memo) {
        if (memo[position] != -1) { // If the result is already memoized, return it.
            return memo[position];
        }

        int maxJump = Math.min(position + nums[position], nums.length - 1);
        for (int nextPosition = position + 1; nextPosition <= maxJump; nextPosition++) {
            if (canJumpFromPosition(nextPosition, nums, memo) == 1) {
                memo[position] = 1; // Mark the current position as reachable.
                return 1;
            }
        }

        memo[position] = 0; // Mark the current position as unreachable.
        return 0;
    }

    /**
     * Approach 3: Dynamic Programming (Bottom-Up)
     *
     * - Time Complexity: O(n^2), where n is the length of the array.
     * - Space Complexity: O(n), for the dp array.
     * - Explanation:
     * - This approach uses dynamic programming (bottom-up).
     * - It creates a dp array where dp[i] indicates whether position i is reachable.
     * - It starts from the end of the array and works backward, determining
     * reachability based on the reachability of subsequent positions.
     * - Real-world application:
     * - Route planning and navigation: Imagine you're developing a navigation
     * system that needs to find the shortest path between two points. You
     * can use dynamic programming to break down the problem into smaller
     * subproblems, such as finding the shortest path to intermediate
     * destinations, and then combine the solutions to these subproblems
     * to find the overall shortest path.
     *
     * @param nums The input array.
     * @return True if it's possible to reach the end, false otherwise.
     */
    public static boolean canJumpDPBottomUp(int[] nums) {
        boolean[] dp = new boolean[nums.length];
        dp[nums.length - 1] = true; // Last position is reachable.

        for (int i = nums.length - 2; i >= 0; i--) {
            int maxJump = Math.min(i + nums[i], nums.length - 1);
            for (int j = i + 1; j <= maxJump; j++) {
                if (dp[j]) {
                    dp[i] = true; // If any subsequent position is reachable, the current is too.
                    break;
                }
            }
        }
        return dp[0]; // Check if the first position is reachable.
    }

    /**
     * Approach 4: Backtracking
     *
     * - Time Complexity: O(2^n), where n is the length of the array (exponential).
     * - Space Complexity: O(n), for the recursion stack.
     * - Explanation:
     * - This approach uses backtracking to explore all possible paths.
     * - The `canJumpFromPositionBacktracking` function recursively tries all
     * possible jumps from the current position.
     * - It's very inefficient for larger arrays as it explores many redundant paths.
     * - Real-world application:
     * - Game playing and AI: In games like chess or Go, a computer AI can use
     * backtracking to explore all possible moves and counter-moves to find
     * the best strategy.  While more advanced techniques exist, backtracking
     * provides a foundational approach to decision-making in complex scenarios.
     *
     * @param nums The input array.
     * @return True if it's possible to reach the end, false otherwise.
     */
    public static boolean canJumpBacktracking(int[] nums) {
        return canJumpFromPositionBacktracking(0, nums);
    }

    private static boolean canJumpFromPositionBacktracking(int position, int[] nums) {
        if (position == nums.length - 1) {
            return true; // Reached the end.
        }

        int maxJump = Math.min(position + nums[position], nums.length - 1);
        for (int nextPosition = position + 1; nextPosition <= maxJump; nextPosition++) {
            if (canJumpFromPositionBacktracking(nextPosition, nums)) {
                return true; // Found a path to the end.
            }
        }
        return false; // No path to the end from this position.
    }

    /**
     * Approach 5: Recursive
     *
     * - Time Complexity: O(2^n), where n is the length of the array (exponential).
     * - Space Complexity: O(n), for the recursion stack.
     * - Explanation:
     * - This is a basic recursive solution.
     * - It checks if the end of the array can be reached from the current position
     * - It has the same exponential time complexity as the backtracking approach
     * - Real-world application:
     * - Parsing and evaluating expressions: Recursive functions are often used
     * to parse and evaluate mathematical or logical expressions. For example,
     * a recursive function can be used to break down a complex expression
     * into smaller sub-expressions and then evaluate each sub-expression
     * recursively.
     *
     * @param nums The input array
     * @param position The current position
     * @return boolean
     */
    public static boolean canJumpRecursive(int[] nums, int position) {
        if (position >= nums.length - 1) {
            return true;
        }

        int maxJump = Math.min(position + nums[position], nums.length - 1);
        for (int i = 1; i <= maxJump; i++) {
            if (canJumpRecursive(nums, position + i)) {
                return true;
            }
        }
        return false;
    }
}

