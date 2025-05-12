import java.util.HashMap;
import java.util.Map;

public class ClimbingStairs {

    /**
     * **1. Recursive Approach**
     *
     * * Time Complexity: O(2^n) - Exponential, due to overlapping subproblems.
     * * Space Complexity: O(n) -  Due to the recursion depth.
     *
     * *Explanation:*
     * The most straightforward approach.  To reach the nth step, you can either
     * come from the (n-1)th step or the (n-2)th step.  This leads to a recursive
     * solution. However, it's very inefficient as it recalculates the same
     * values multiple times.
     */
    public int climbStairsRecursive(int n) {
        if (n <= 1) {
            return 1;
        }
        return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
    }

    /**
     * **2. Memoization (Top-Down DP)**
     *
     * * Time Complexity: O(n) - Each subproblem is solved only once.
     * * Space Complexity: O(n) -  O(n) for the memoization table (dp array) + O(n) for recursion depth.
     *
     * *Explanation:*
     * This approach improves upon the recursive solution by storing the results of
     * already solved subproblems.  We use a `dp` array (or a HashMap) to store
     * the number of ways to reach each step.  Before calculating the number of ways
     * to reach a step, we check if it's already stored. If it is, we return the stored
     * value; otherwise, we calculate it and store it.
     */
    public int climbStairsMemoization(int n) {
        int[] dp = new int[n + 1];
        return climbStairsMemoizationHelper(n, dp);
    }

    private int climbStairsMemoizationHelper(int n, int[] dp) {
        if (n <= 1) {
            return 1;
        }
        if (dp[n] != 0) { // Changed from -1 to 0, because 0 is not a possible value.
            return dp[n];
        }
        dp[n] = climbStairsMemoizationHelper(n - 1, dp) + climbStairsMemoizationHelper(n - 2, dp);
        return dp[n];
    }

    /**
     * **3. Tabulation (Bottom-Up DP)**
     *
     * * Time Complexity: O(n) - We iterate through the array once.
     * * Space Complexity: O(n) -  For the dp array.
     *
     * *Explanation:*
     * This is another dynamic programming approach, but instead of using recursion,
     * we build the solution from the bottom up.  We create a `dp` array where `dp[i]`
     * represents the number of ways to reach the ith step.  We initialize the base cases
     * (dp[0] and dp[1]) and then iterate from 2 to n, calculating the number of ways
     * to reach each step based on the previous two steps.
     */
    public int climbStairsTabulation(int n) {
        if (n <= 1) {
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
     * **4. Optimized Tabulation (Bottom-Up DP with Constant Space)**
     *
     * * Time Complexity: O(n) - We iterate through the loop n times.
     * * Space Complexity: O(1) -  We only use three variables.
     *
     * *Explanation:*
     * This approach is an optimized version of the tabulation method.  We observe that
     * to calculate the number of ways to reach the ith step, we only need the number of
     * ways to reach the (i-1)th and (i-2)th steps.  Therefore, we don't need to store
     * the entire `dp` array; we can just keep track of the previous two values.
     */
    public int climbStairsOptimized(int n) {
        if (n <= 1) {
            return 1;
        }
        int prev1 = 1; // Represents dp[i-1]
        int prev2 = 1; // Represents dp[i-2]
        for (int i = 2; i <= n; i++) {
            int current = prev1 + prev2; // Calculate dp[i]
            prev2 = prev1;             // Update for the next iteration
            prev1 = current;
        }
        return prev1;
    }

    /**
     * **5. Matrix Method**
     *
     * * Time Complexity: O(log n) - due to the matrix exponentiation.
     * * Space Complexity: O(1) - constant space.
     *
     * *Explanation:*
     * This approach uses matrix exponentiation, which is based on the observation that
     * the Fibonacci sequence (which is related to this problem) can be represented
     * by the matrix:
     *
     * [F(n+1)  F(n)  ]   =  [1  1]^n [F(1) F(0)]
     * [F(n)    F(n-1)]      [1  0]
     *
     * We can calculate the nth power of the matrix [[1, 1], [1, 0]] efficiently
     * using binary exponentiation.  This method is more complex to understand
     * but provides a very efficient solution for large values of n.
     */
    public int climbStairsMatrix(int n) {
        if (n <= 1) {
            return 1;
        }
        int[][] matrix = {{1, 1}, {1, 0}};
        int[][] result = matrixPower(matrix, n);
        return result[0][0];
    }

    private int[][] matrixPower(int[][] matrix, int n) {
        int[][] result = {{1, 0}, {0, 1}}; // Identity matrix
        while (n > 0) {
            if (n % 2 == 1) {
                result = matrixMultiply(result, matrix);
            }
            matrix = matrixMultiply(matrix, matrix);
            n /= 2;
        }
        return result;
    }

    private int[][] matrixMultiply(int[][] a, int[][] b) {
        int[][] result = new int[2][2];
        result[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
        result[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
        result[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
        result[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
        return result;
    }

    public static void main(String[] args) {
        ClimbingStairs solution = new ClimbingStairs();
        int n = 10;

        System.out.println("Climbing Stairs Problem: n = " + n);
        System.out.println("\n1. Recursive Approach:");
        System.out.println("Number of ways: " + solution.climbStairsRecursive(n));

        System.out.println("\n2. Memoization Approach:");
        System.out.println("Number of ways: " + solution.climbStairsMemoization(n));

        System.out.println("\n3. Tabulation Approach:");
        System.out.println("Number of ways: " + solution.climbStairsTabulation(n));

        System.out.println("\n4. Optimized Tabulation Approach:");
        System.out.println("Number of ways: " + solution.climbStairsOptimized(n));

        System.out.println("\n5. Matrix Approach:");
        System.out.println("Number of ways: " + solution.climbStairsMatrix(n));
    }
}

