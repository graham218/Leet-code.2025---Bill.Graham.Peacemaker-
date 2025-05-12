import java.util.HashMap;
import java.util.Map;

public class ClimbingStairs {

    /**
     * **1. Recursive Approach (Basic)**
     *
     * * Concept:* The most straightforward way to solve this problem is by using recursion.
     * We define a function `climbStairsRecursive(n)` that calculates the number of ways to reach the nth step.
     * The base cases are when n is 0 (1 way to be at the "ground" before starting) or 1 (1 way to reach the first step).
     * For any n > 1, the number of ways is the sum of the ways to reach the (n-1)th step and the (n-2)th step.
     * * Real-World Analogy:* Imagine you're planning a very short presentation.  You can choose to prepare either one slide at a time or two slides at a time. This recursive function calculates all the possible ways you can prepare your presentation.
     * * Time Complexity:* O(2^n) - Exponential (very slow for larger n)
     * * Space Complexity:* O(n) - Due to the recursion depth
     */
    public static int climbStairsRecursive(int n) {
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return 1;
        }
        return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
    }

    /**
     * **2. Memoization (Top-Down DP)**
     *
     * * Concept:* Memoization is an optimization technique where we store the results of expensive function calls
     * and reuse them when the same inputs occur again.  In this case, we use a `HashMap` (or an array) to store
     * the number of ways to reach each step.  Before calculating the number of ways for a step, we check if
     * it's already stored in the `memo`.  If it is, we return the stored value; otherwise, we calculate it,
     * store it, and return it.
     * * Real-World Analogy:* Think of preparing a project report. Instead of re-calculating the same metrics
     * multiple times, you store them in a "cache" (the memo). When you need the metric again, you just look it up
     * in the cache instead of recalculating.
     * * Time Complexity:* O(n) - Each step's result is calculated only once.
     * * Space Complexity:* O(n) - For the memoization table (HashMap) and the recursion stack.
     */
    public static int climbStairsMemoization(int n, Map<Integer, Integer> memo) {
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return 1;
        }
        if (memo.containsKey(n)) {
            return memo.get(n);
        }
        int result = climbStairsMemoization(n - 1, memo) + climbStairsMemoization(n - 2, memo);
        memo.put(n, result);
        return result;
    }

    public static int climbStairsMemoization(int n) {
        return climbStairsMemoization(n, new HashMap<>());
    }

    /**
     * **3. Tabulation (Bottom-Up DP)**
     *
     * * Concept:* Tabulation is another DP technique where we build a table (array) of results from the bottom up.
     * We start with the base cases and iteratively calculate the results for larger inputs.  In this problem,
     * `dp[i]` stores the number of ways to reach the ith step.  We initialize `dp[0]` and `dp[1]` and then
     * calculate the rest of the values using the formula `dp[i] = dp[i-1] + dp[i-2]`.
     * * Real-World Analogy:* Imagine you're building a project timeline. You start with the initial tasks,
     * estimate their durations, and then use those estimates to calculate the completion dates of subsequent tasks.
     * You're building up the timeline step by step.
     * * Time Complexity:* O(n) - We iterate through the array once.
     * * Space Complexity:* O(n) - For the DP table (array).
     */
    public static int climbStairsTabulation(int n) {
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return 1;
        }
        int[] dp = new int[n + 1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    /**
     * **4. Optimized Tabulation (Bottom-Up with Constant Space)**
     *
     * * Concept:* We can optimize the tabulation approach to use only constant space.  Notice that in the previous
     * approach, we only need the values of `dp[i-1]` and `dp[i-2]` to calculate `dp[i]`.  So, we can keep track of
     * just these two values instead of the entire array.
     * * Real-World Analogy:* Consider a very memory-constrained embedded system, like a simple sensor, that needs
     * to calculate a running total.  Instead of storing all the individual measurements, you only keep the
     * previous total and the current measurement to calculate the new total.
     * * Time Complexity:* O(n) - We still iterate n times.
     * * Space Complexity:* O(1) -  We use only a constant amount of extra space (two variables).
     */
    public static int climbStairsOptimized(int n) {
        if (n == 0) {
            return 1;
        }
        if (n == 1) {
            return 1;
        }
        int prev1 = 1; // Represents dp[i-1]
        int prev2 = 1; // Represents dp[i-2]
        for (int i = 2; i <= n; i++) {
            int current = prev1 + prev2; // Calculate dp[i]
            prev2 = prev1;             // Update dp[i-2]
            prev1 = current;           // Update dp[i-1]
        }
        return prev1;
    }

    /**
     * **5. Fibonacci Formula (Direct Solution)**
     *
     * * Concept: The number of ways to climb n stairs is actually the (n+1)th Fibonacci number.  We can use the
     * closed-form formula (Binet's formula) to calculate the Fibonacci number directly.  This avoids iteration
     * or recursion.
     * * Real-World Analogy: In financial modeling, if you have a scenario where a value increases following the
     * Fibonacci sequence (which is rare, but illustrative), you could use this formula to project the value
     * for a future period directly, without simulating each intermediate step.
     * * Time Complexity: O(1) - Constant time for the calculation.
     * * Space Complexity: O(1) - Constant space.
     */
    public static int climbStairsFibonacci(int n) {
        double sqrt5 = Math.sqrt(5);
        double fibN = Math.pow((1 + sqrt5) / 2, n + 1) - Math.pow((1 - sqrt5) / 2, n + 1);
        return (int) Math.round(fibN / sqrt5);
    }

    public static void main(String[] args) {
        int n = 10; // Example: Calculate for 10 stairs

        System.out.println("Climbing Stairs Problem - n = " + n);
        System.out.println("1. Recursive Approach: " + climbStairsRecursive(n));
        System.out.println("2. Memoization Approach: " + climbStairsMemoization(n));
        System.out.println("3. Tabulation Approach: " + climbStairsTabulation(n));
        System.out.println("4. Optimized Tabulation Approach: " + climbStairsOptimized(n));
        System.out.println("5. Fibonacci Formula Approach: " + climbStairsFibonacci(n));
    }
}

