import java.util.Arrays;

public class MatrixChainMultiplication {

    // Helper method to print the optimal parenthesization of the matrices.
    // This method is used by the memoized and bottom-up DP solutions.
    private static String printOptimalParenthesization(int[][] s, int i, int j) {
        if (i == j) {
            return "A" + i;
        } else {
            return "(" + printOptimalParenthesization(s, i, s[i][j]) +
                    printOptimalParenthesization(s, s[i][j] + 1, j) + ")";
        }
    }

    // 1. Recursive Solution
    // This is the most basic approach, where we recursively calculate the cost for
    // every possible split of the matrix chain.  It has exponential time complexity.
    public static int matrixChainMultiplicationRecursive(int[] p, int i, int j) {
        if (i == j) {
            return 0; // One matrix, no multiplication needed.
        }

        int minCost = Integer.MAX_VALUE;
        for (int k = i; k < j; k++) {
            // Calculate cost for each split (k)
            int cost = matrixChainMultiplicationRecursive(p, i, k) +
                    matrixChainMultiplicationRecursive(p, k + 1, j) +
                    p[i - 1] * p[k] * p[j]; // Cost of multiplying the two subchains
            minCost = Math.min(minCost, cost); // Update minCost if a lower cost is found
        }
        return minCost;
    }

    // 2. Memoized (Top-Down Dynamic Programming) Solution
    // This approach improves upon the recursive solution by storing the results of
    // subproblems in a table (memoization).  This avoids redundant calculations.
    public static int matrixChainMultiplicationMemoized(int[] p, int i, int j, int[][] memo) {
        if (i == j) {
            return 0;
        }

        if (memo[i][j] != -1) {
            return memo[i][j]; // Return stored value if already calculated
        }

        int minCost = Integer.MAX_VALUE;
        for (int k = i; k < j; k++) {
            int cost = matrixChainMultiplicationMemoized(p, i, k, memo) +
                    matrixChainMultiplicationMemoized(p, k + 1, j, memo) +
                    p[i - 1] * p[k] * p[j];
            minCost = Math.min(minCost, cost);
        }
        memo[i][j] = minCost; // Store the calculated cost
        return minCost;
    }

    public static int matrixChainMultiplicationMemoized(int[] p) {
        int n = p.length;
        int[][] memo = new int[n][n];
        for (int[] row : memo) {
            Arrays.fill(row, -1); // Initialize memo table with -1
        }
        return matrixChainMultiplicationMemoized(p, 1, n - 1, memo);
    }

    // 3. Bottom-Up Dynamic Programming Solution
    // This approach calculates the optimal costs in a bottom-up manner, filling a table
    // iteratively.  It's generally more efficient than the memoized approach.
    public static int matrixChainMultiplicationBottomUp(int[] p) {
        int n = p.length;
        int[][] dp = new int[n][n]; // dp[i][j] stores min cost to multiply matrices Ai to Aj
        int[][] s = new int[n][n]; // s[i][j] stores the optimal split point for Ai to Aj

        // Base case: cost of multiplying a single matrix is 0
        for (int i = 1; i < n; i++) {
            dp[i][i] = 0;
        }

        // l is chain length.  We start with chains of length 2 and go up to length n-1
        for (int l = 2; l < n; l++) {
            for (int i = 1; i < n - l + 1; i++) {
                int j = i + l - 1;
                dp[i][j] = Integer.MAX_VALUE;
                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost; // Update min cost
                        s[i][j] = k;     // Store the optimal split point
                    }
                }
            }
        }
        // Print the optimal parenthesization
        System.out.println("Optimal Parenthesization: " + printOptimalParenthesization(s, 1, n - 1));
        return dp[1][n - 1]; // Result is stored in dp[1][n-1]
    }

    // 4. Space Optimized Bottom-Up DP
    // This approach reduces the space complexity of the bottom-up DP from O(n^2) to O(n).
    // It iterates through the subproblem sizes, updating a 1D array to store the minimum costs.
    public static int matrixChainMultiplicationSpaceOptimized(int[] p) {
        int n = p.length;
        int[] dp = new int[n]; // dp[i] stores the minimum cost to multiply matrices A1 to Ai
        // Initialize dp array.  dp[i] represents the cost of multiplying A1...Ai.
        for (int i = 1; i < n; i++) {
            dp[i] = 0; // Cost of multiplying a single matrix is 0
        }

        for (int len = 2; len < n; len++) { // Length of the chain being considered
            for (int i = 1; i <= n - len; i++) {
                int j = i + len - 1;
                int minCost = Integer.MAX_VALUE;
                for (int k = i; k < j; k++) {
                    // Calculate the cost of multiplying the subchains and the final multiplication.
                    int cost = dp[i] + dp[k+1] + p[i - 1] * p[k] * p[j];
                    minCost = Math.min(minCost, cost);
                }
                dp[j] = minCost; // Store the minimum cost for the chain A1...Aj
            }
        }
        return dp[n - 1];
    }

    // 5. Recursive Solution with Memoization and Parenthesis Printing
    // This combines the memoization technique with the ability to print the optimal
    // parenthesization of the matrices.
    public static int matrixChainMultiplicationMemoizedWithParenthesis(int[] p, int i, int j, int[][] memo, int[][] s) {
        if (i == j) {
            return 0;
        }

        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        int minCost = Integer.MAX_VALUE;
        for (int k = i; k < j; k++) {
            int cost = matrixChainMultiplicationMemoizedWithParenthesis(p, i, k, memo, s) +
                    matrixChainMultiplicationMemoizedWithParenthesis(p, k + 1, j, memo, s) +
                    p[i - 1] * p[k] * p[j];
            if (cost < minCost) {
                minCost = cost;
                s[i][j] = k; // Store the split point
            }
        }
        memo[i][j] = minCost;
        return minCost;
    }

    public static int matrixChainMultiplicationMemoizedWithParenthesis(int[] p) {
        int n = p.length;
        int[][] memo = new int[n][n];
        int[][] s = new int[n][n]; // To store split points for optimal parenthesization
        for (int[] row : memo) {
            Arrays.fill(row, -1);
        }
        int minCost = matrixChainMultiplicationMemoizedWithParenthesis(p, 1, n - 1, memo, s);
        System.out.println("Optimal Parenthesization: " + printOptimalParenthesization(s, 1, n - 1));
        return minCost;
    }

    public static void main(String[] args) {
        int[] p = {10, 30, 5, 60, 5}; // Dimensions of matrices: A1(10x30), A2(30x5), A3(5x60), A4(60x5)
        int n = p.length;

        System.out.println("Matrix Chain Multiplication");
        System.out.println("-----------------------------");

        // 1. Recursive Solution
        long start = System.nanoTime();
        int costRecursive = matrixChainMultiplicationRecursive(p, 1, n - 1);
        long end = System.nanoTime();
        System.out.println("1. Recursive Solution: Minimum cost is " + costRecursive + ". Time: " + (end - start) / 1e6 + " ms");

        // 2. Memoized Solution
        start = System.nanoTime();
        int costMemoized = matrixChainMultiplicationMemoized(p);
        end = System.nanoTime();
        System.out.println("2. Memoized Solution: Minimum cost is " + costMemoized + ". Time: " + (end - start) / 1e6 + " ms");

        // 3. Bottom-Up DP Solution
        start = System.nanoTime();
        int costBottomUp = matrixChainMultiplicationBottomUp(p);
        end = System.nanoTime();
        System.out.println("3. Bottom-Up DP Solution: Minimum cost is " + costBottomUp + ". Time: " + (end - start) / 1e6 + " ms");

        // 4. Space Optimized Bottom-Up DP
        start = System.nanoTime();
        int costSpaceOptimized = matrixChainMultiplicationSpaceOptimized(p);
        end = System.nanoTime();
        System.out.println("4. Space Optimized Bottom-Up DP Solution: Minimum cost is " + costSpaceOptimized + ". Time: " + (end - start) / 1e6 + " ms");

        // 5. Memoized Solution with Parenthesis Printing
        start = System.nanoTime();
        int costMemoizedWithParenthesis = matrixChainMultiplicationMemoizedWithParenthesis(p);
        end = System.nanoTime();
        System.out.println("5. Memoized Solution with Parenthesis Printing: Minimum cost is " + costMemoizedWithParenthesis + ". Time: " + (end - start) / 1e6 + " ms");
    }
}

