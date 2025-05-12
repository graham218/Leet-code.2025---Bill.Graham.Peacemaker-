import java.util.HashMap;
import java.util.Map;

public class Fibonacci {

    // 1. Recursive Approach (Basic, but inefficient)
    //    - Concept: Directly implements the mathematical definition of the Fibonacci sequence.
    //    - Use Case: Simple demonstration of the Fibonacci concept, not suitable for large numbers due to performance.
    //    - Time Complexity: O(2^n) - Exponential (very slow)
    //    - Space Complexity: O(n) - Due to the call stack
    public static int fibonacciRecursive(int n) {
        if (n <= 1) {
            return n;
        }
        return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
    }

    // 2. Memoization (Top-Down Dynamic Programming)
    //    - Concept: Stores the results of expensive function calls and reuses them when needed.  Uses a HashMap for storage.
    //    - Use Case: Optimizing recursive functions where the same inputs occur repeatedly.  Good for problems where you can easily define the problem recursively.
    //    - Time Complexity: O(n) - Linear
    //    - Space Complexity: O(n) - Due to the HashMap and call stack
    public static int fibonacciMemoization(int n, Map<Integer, Integer> memo) {
        if (n <= 1) {
            return n;
        }
        if (memo.containsKey(n)) {
            return memo.get(n);
        }
        int result = fibonacciMemoization(n - 1, memo) + fibonacciMemoization(n - 2, memo);
        memo.put(n, result);
        return result;
    }

    public static int fibonacciMemoization(int n) {
        return fibonacciMemoization(n, new HashMap<>());
    }

    // 3. Tabulation (Bottom-Up Dynamic Programming)
    //    - Concept: Builds a table of results from the bottom up, solving smaller subproblems first. Uses an array for storage.
    //    - Use Case:  More efficient than memoization as it avoids recursion.  Ideal when you need to calculate all Fibonacci numbers up to n.
    //    - Time Complexity: O(n) - Linear
    //    - Space Complexity: O(n) - Due to the table (array)
    public static int fibonacciTabulation(int n) {
        if (n <= 1) {
            return n;
        }
        int[] table = new int[n + 1];
        table[0] = 0;
        table[1] = 1;
        for (int i = 2; i <= n; i++) {
            table[i] = table[i - 1] + table[i - 2];
        }
        return table[n];
    }

    // 4. Space-Optimized Tabulation
    //    - Concept:  Improves upon tabulation by only storing the two previous Fibonacci numbers, reducing space usage.
    //    - Use Case: When memory is a concern, and you only need the nth Fibonacci number.
    //    - Time Complexity: O(n) - Linear
    //    - Space Complexity: O(1) - Constant (only two variables are used)
    public static int fibonacciSpaceOptimized(int n) {
        if (n <= 1) {
            return n;
        }
        int a = 0;
        int b = 1;
        for (int i = 2; i <= n; i++) {
            int next = a + b;
            a = b;
            b = next;
        }
        return b;
    }

    // 5. Matrix Method (Advanced - for very large n)
    //    - Concept: Uses matrix exponentiation to calculate the nth Fibonacci number.  Based on the matrix identity:
    //      | F(n+1)  F(n)  |   =   | 1  1 | ^n
    //      | F(n)    F(n-1)|       | 1  0 |
    //    - Use Case:  Most efficient for extremely large values of n.  Used in cryptography and advanced algorithms.
    //    - Time Complexity: O(log n) - Logarithmic (very fast)
    //    - Space Complexity: O(1) - Constant
    public static int fibonacciMatrix(int n) {
        if (n <= 1)
            return n;
        int[][] matrix = {{1, 1}, {1, 0}};
        power(matrix, n - 1);
        return matrix[0][0];
    }

    // Helper function to multiply two 2x2 matrices
    private static void multiply(int[][] a, int[][] b) {
        int x = a[0][0] * b[0][0] + a[0][1] * b[1][0];
        int y = a[0][0] * b[0][1] + a[0][1] * b[1][1];
        int z = a[1][0] * b[0][0] + a[1][1] * b[1][0];
        int w = a[1][0] * b[0][1] + a[1][1] * b[1][1];
        a[0][0] = x;
        a[0][1] = y;
        a[1][0] = z;
        a[1][1] = w;
    }

    // Helper function to calculate the power of a matrix
    private static void power(int[][] matrix, int n) {
        if (n == 0 || n == 1)
            return;
        int[][] temp = {{1, 1}, {1, 0}}; // Identity Matrix
        power(matrix, n / 2);
        multiply(matrix, matrix);
        if (n % 2 != 0)
            multiply(matrix, temp);
    }

    public static void main(String[] args) {
        int n = 10; // Example: Calculate the 10th Fibonacci number

        System.out.println("Fibonacci Series for n = " + n + ":");
        System.out.println("1. Recursive: " + fibonacciRecursive(n));
        System.out.println("2. Memoization: " + fibonacciMemoization(n));
        System.out.println("3. Tabulation: " + fibonacciTabulation(n));
        System.out.println("4. Space-Optimized Tabulation: " + fibonacciSpaceOptimized(n));
        System.out.println("5. Matrix Method: " + fibonacciMatrix(n));

        // Real-world examples (Illustrative)
        System.out.println("\nReal-world Examples (Illustrative):");

        // 1. Recursive: Not typically used directly in projects due to inefficiency.  Good for teaching recursion.
        System.out.println("1. Recursive: (Conceptual) Demonstrating recursion in a simple example.");

        // 2. Memoization:  Caching results of expensive calculations.
        System.out.println("2. Memoization: Optimizing API calls that return the same data for the same input.");

        // 3. Tabulation:  Generating a sequence of values for a report or visualization.
        System.out.println("3. Tabulation: Generating a table of financial growth projections over several years.");

        // 4. Space-Optimized Tabulation:  Calculating a specific value with limited memory resources, like in embedded systems.
        System.out.println("4. Space-Optimized Tabulation: Calculating a specific metric in a memory-constrained IoT device.");

        // 5. Matrix Method:  High-performance computing, cryptography, and advanced algorithms.
        System.out.println("5. Matrix Method:  Used in cryptographic algorithms for key generation or encryption/decryption.");
    }
}
