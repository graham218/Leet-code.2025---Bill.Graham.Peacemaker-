import java.util.Arrays;

public class MatrixChainMultiplication {

    // Approach 1: Recursive Solution
    // This is the most basic approach, directly implementing the recursive definition.
    // It has exponential time complexity and is very inefficient for larger problems.
    //
    // Real-world application: This approach is rarely used directly in real-world projects
    // due to its inefficiency.  It's primarily a pedagogical tool to understand the problem.
    // However, it can be used for very small problem instances where performance is not critical,
    // such as in some embedded systems with limited matrix sizes or in educational software
    // demonstrating the basic concept.
    public static int matrixChainMultiplicationRecursive(int[] p, int i, int j) {
        if (i == j) {
            return 0; // Base case: only one matrix, no multiplication cost
        }

        int minCost = Integer.MAX_VALUE;
        for (int k = i; k < j; k++) {
            // Calculate cost for each possible split
            int cost = matrixChainMultiplicationRecursive(p, i, k) +
                    matrixChainMultiplicationRecursive(p, k + 1, j) +
                    p[i - 1] * p[k] * p[j]; // Cost of multiplying the two subchains
            minCost = Math.min(minCost, cost); // Update minimum cost
        }
        return minCost;
    }

    // Approach 2: Memoization (Top-Down Dynamic Programming)
    // This approach improves upon the recursive solution by storing the results of
    // subproblems in a table (memoization).  This avoids redundant calculations.
    //
    // Real-world application: Memoization is a valuable technique in many real-world
    // applications.  For example, in a compiler, it can be used to optimize the evaluation
    // of expression trees.  In financial modeling, it can be used to speed up the calculation
    // of complex derivative prices.  In game development, it can be used to cache the results
    // of expensive calculations, such as pathfinding or AI decisions.  It's often used when
    // the problem has overlapping subproblems and a recursive structure.
    public static int matrixChainMultiplicationMemoized(int[] p, int i, int j, int[][] memo) {
        if (i == j) {
            return 0;
        }

        if (memo[i][j] != -1) {
            return memo[i][j]; // Return stored result if available
        }

        int minCost = Integer.MAX_VALUE;
        for (int k = i; k < j; k++) {
            int cost = matrixChainMultiplicationMemoized(p, i, k, memo) +
                    matrixChainMultiplicationMemoized(p, k + 1, j, memo) +
                    p[i - 1] * p[k] * p[j];
            minCost = Math.min(minCost, cost);
        }
        memo[i][j] = minCost; // Store the result
        return minCost;
    }

    // Approach 3: Tabulation (Bottom-Up Dynamic Programming)
    // This approach systematically fills a table of subproblem solutions in a bottom-up
    // manner.  It avoids recursion and is generally more efficient than memoization.
    //
    // Real-world application: Tabulation is very common in real-world applications.  For example,
    // in bioinformatics, it's used for sequence alignment (e.g., the Needleman-Wunsch algorithm).
    // In operations research, it's used for solving optimization problems like the knapsack problem.
    // In computer graphics, it can be used for tasks like texture mapping and rendering.  It's
    // preferred when the subproblem dependencies are well-defined and can be ordered.
    public static int matrixChainMultiplicationTabulated(int[] p) {
        int n = p.length;
        int[][] dp = new int[n][n];

        // Initialize the diagonal elements (cost of multiplying a single matrix is 0)
        for (int i = 1; i < n; i++) {
            dp[i][i] = 0;
        }

        // Fill the table in a bottom-up manner
        for (int L = 2; L < n; L++) { // L is the chain length
            for (int i = 1; i < n - L + 1; i++) {
                int j = i + L - 1;
                dp[i][j] = Integer.MAX_VALUE;
                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                    dp[i][j] = Math.min(dp[i][j], cost);
                }
            }
        }
        return dp[1][n - 1]; // The result is stored in dp[1][n-1]
    }

    // Approach 4: Optimized Tabulation with Reduced Space Complexity
    // This approach optimizes the tabulation method by reducing the space complexity.
    // In the standard tabulation method, we use a 2D array of size n x n.
    // However, we only need two rows at a time to calculate the next row.
    // This optimized approach uses only two 1D arrays to store the intermediate results,
    // reducing the space complexity from O(n^2) to O(n).
    //
    // Real-world application: This space-optimized tabulation is crucial when dealing with
    // very large input sizes where memory is a constraint.  For example, in large-scale
    // data processing or in embedded systems with limited RAM, this optimization can make
    // the difference between a feasible and an infeasible solution.  It's often used in
    // high-performance computing and in applications where memory efficiency is paramount.
    public static int matrixChainMultiplicationOptimized(int[] p) {
        int n = p.length;
        int[] prev = new int[n]; // Stores results from the previous row
        int[] curr = new int[n]; // Stores results for the current row

        // Initialize base case (L = 1) - no need to explicitly initialize in Java, defaults to 0.

        for (int L = 2; L < n; L++) {
            for (int i = 1; i < n - L + 1; i++) {
                int j = i + L - 1;
                curr[i] = Integer.MAX_VALUE;
                for (int k = i; k < j; k++) {
                    int cost = prev[i] + prev[k + 1] + p[i - 1] * p[k] * p[j];
                    curr[i] = Math.min(curr[i], cost);
                }
            }
            // Swap prev and curr for the next iteration
            int[] temp = prev;
            prev = curr;
            curr = temp;
        }
        return prev[1]; // The result is in prev[1] after the loop finishes
    }

    // Approach 5:  Iterative Approach with Explicit Parenthesis Tracking
    // This approach is similar to tabulation, but it also keeps track of the
    // optimal parenthesization.  This is useful if you need to know not only the
    // minimum cost but also the optimal way to multiply the matrices.
    //
    // Real-world application: This is useful in applications where the actual
    // multiplication order matters.  For example, in compiler design, this information
    // can be used to generate optimized code for matrix multiplication.  In robotics,
    // it can be used to plan the optimal sequence of matrix transformations.  In
    // scientific computing, it can be used to optimize the evaluation of complex
    // matrix expressions.  Any application where the *order* of operations affects
    // numerical stability or performance would benefit from this approach.
    public static int matrixChainMultiplicationWithParenthesis(int[] p) {
        int n = p.length;
        int[][] dp = new int[n][n];
        int[][] split = new int[n][n]; // Stores the optimal split point

        for (int i = 1; i < n; i++) {
            dp[i][i] = 0;
        }

        for (int L = 2; L < n; L++) {
            for (int i = 1; i < n - L + 1; i++) {
                int j = i + L - 1;
                dp[i][j] = Integer.MAX_VALUE;
                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                        split[i][j] = k; // Store the split point
                    }
                }
            }
        }
        printOptimalParenthesization(split, 1, n - 1);
        System.out.println();
        return dp[1][n - 1];
    }

    // Helper function to print the optimal parenthesization
    public static void printOptimalParenthesization(int[][] s, int i, int j) {
        if (i == j) {
            System.out.print("A" + i);
        } else {
            System.out.print("(");
            printOptimalParenthesization(s, i, s[i][j]);
            printOptimalParenthesization(s, s[i][j] + 1, j);
            System.out.print(")");
        }
    }

    public static void main(String[] args) {
        int[] p = {10, 30, 5, 60, 5}; // Dimensions of matrices: A1(10x30), A2(30x5), A3(5x60), A4(60x5)
        int n = p.length;

        // Approach 1: Recursive
        System.out.println("Approach 1: Recursive Solution");
        long startTime = System.nanoTime();
        int result1 = matrixChainMultiplicationRecursive(p, 1, n - 1);
        long endTime = System.nanoTime();
        System.out.println("Minimum cost: " + result1);
        System.out.println("Time taken: " + (endTime - startTime) + " ns");
        System.out.println("----------------------------------------");

        // Approach 2: Memoization
        System.out.println("Approach 2: Memoization");
        int[][] memo = new int[n][n];
        for (int[] row : memo) {
            Arrays.fill(row, -1);
        }
        startTime = System.nanoTime();
        int result2 = matrixChainMultiplicationMemoized(p, 1, n - 1, memo);
        endTime = System.nanoTime();
        System.out.println("Minimum cost: " + result2);
        System.out.println("Time taken: " + (endTime - startTime) + " ns");
        System.out.println("----------------------------------------");

        // Approach 3: Tabulation
        System.out.println("Approach 3: Tabulation");
        startTime = System.nanoTime();
        int result3 = matrixChainMultiplicationTabulated(p);
        endTime = System.nanoTime();
        System.out.println("Minimum cost: " + result3);
        System.out.println("Time taken: " + (endTime - startTime) + " ns");
        System.out.println("----------------------------------------");

        // Approach 4: Optimized Tabulation
        System.out.println("Approach 4: Optimized Tabulation");
        startTime = System.nanoTime();
        int result4 = matrixChainMultiplicationOptimized(p);
        endTime = System.nanoTime();
        System.out.println("Minimum cost: " + result4);
        System.out.println("Time taken: " + (endTime - startTime) + " ns");
        System.out.println("----------------------------------------");

        // Approach 5: Iterative with Parenthesis
        System.out.println("Approach 5: Iterative with Parenthesis");
        startTime = System.nanoTime();
        int result5 = matrixChainMultiplicationWithParenthesis(p);
        endTime = System.nanoTime();
        System.out.println("Minimum cost: " + result5);
        System.out.println("Time taken: " + (endTime - startTime) + " ns");
        System.out.println("----------------------------------------");
    }
}

