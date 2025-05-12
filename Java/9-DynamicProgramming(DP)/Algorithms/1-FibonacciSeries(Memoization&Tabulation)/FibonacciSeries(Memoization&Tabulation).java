import java.util.HashMap;
import java.util.Map;

public class Fibonacci {

    public static void main(String[] args) {
        int n = 10; // Calculate the 10th Fibonacci number

        System.out.println("Fibonacci(" + n + ") using Recursion: " + fibonacciRecursion(n));
        System.out.println("Fibonacci(" + n + ") using Memoization (Top-Down): " + fibonacciMemoization(n, new HashMap<>()));
        System.out.println("Fibonacci(" + n + ") using Tabulation (Bottom-Up): " + fibonacciTabulation(n));
        System.out.println("Fibonacci(" + n + ") using Space Optimized Tabulation: " + fibonacciSpaceOptimized(n));
        System.out.println("Fibonacci(" + n + ") using Matrix Multiplication: " + fibonacciMatrix(n));
    }

    // 1. Recursive Approach (Basic, but inefficient)
    // This is the simplest approach, but it has exponential time complexity.
    // It repeatedly calculates the same Fibonacci numbers, leading to a lot of redundant work.
    public static int fibonacciRecursion(int n) {
        if (n <= 1) {
            return n;
        }
        return fibonacciRecursion(n - 1) + fibonacciRecursion(n - 2);
    }

    // 2. Memoization (Top-Down Dynamic Programming)
    // Memoization optimizes the recursive approach by storing the results of previously
    // calculated Fibonacci numbers in a HashMap.  This avoids redundant calculations.
    // It's called "top-down" because it starts from the top (n) and goes down to the base cases.
    public static int fibonacciMemoization(int n, Map<Integer, Integer> memo) {
        if (n <= 1) {
            return n;
        }
        // Check if the result is already in the memo
        if (memo.containsKey(n)) {
            return memo.get(n);
        }
        // Calculate the Fibonacci number and store it in the memo
        int result = fibonacciMemoization(n - 1, memo) + fibonacciMemoization(n - 2, memo);
        memo.put(n, result);
        return result;
    }

    // 3. Tabulation (Bottom-Up Dynamic Programming)
    // Tabulation calculates Fibonacci numbers iteratively, starting from the base cases
    // and building up to the desired number (n).  It stores the results in an array.
    // It's called "bottom-up" because it starts from the base cases and goes up to the final result.
    public static int fibonacciTabulation(int n) {
        if (n <= 1) {
            return n;
        }
        int[] table = new int[n + 1]; // Array to store Fibonacci numbers
        table[0] = 0; // Base case: F(0) = 0
        table[1] = 1; // Base case: F(1) = 1
        // Iterate from 2 to n, calculating each Fibonacci number
        for (int i = 2; i <= n; i++) {
            table[i] = table[i - 1] + table[i - 2];
        }
        return table[n]; // The nth Fibonacci number is at table[n]
    }

    // 4. Space Optimized Tabulation
    // This approach is a further optimization of the tabulation method.  Instead of
    // using an entire array to store the Fibonacci numbers, it only uses three variables
    // to store the previous two numbers and the current number.  This reduces the space complexity
    // from O(n) to O(1).
    public static int fibonacciSpaceOptimized(int n) {
        if (n <= 1) {
            return n;
        }
        int a = 0; // Represents F(n-2)
        int b = 1; // Represents F(n-1)
        int c;     // Represents F(n)
        // Iterate from 2 to n, calculating each Fibonacci number
        for (int i = 2; i <= n; i++) {
            c = a + b; // Calculate the current Fibonacci number
            a = b;     // Update a to be the previous F(n-1)
            b = c;     // Update b to be the current F(n)
        }
        return b; // After the loop, b holds the nth Fibonacci number
    }

    // 5. Matrix Multiplication
    // This is an efficient way to calculate Fibonacci numbers using matrix exponentiation.
    // It leverages the property that the nth Fibonacci number can be found using matrix exponentiation.
    // The time complexity of this method is O(log n).
    public static int fibonacciMatrix(int n) {
        if (n <= 1) return n;
        int[][] baseMatrix = {{1, 1}, {1, 0}};
        int[][] resultMatrix = matrixPower(baseMatrix, n - 1);
        return resultMatrix[0][0];
    }

    // Helper function to multiply two 2x2 matrices
    private static int[][] matrixMultiply(int[][] a, int[][] b) {
        int[][] result = new int[2][2];
        result[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
        result[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
        result[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
        result[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
        return result;
    }

    // Helper function to calculate the power of a 2x2 matrix
    private static int[][] matrixPower(int[][] matrix, int n) {
        if (n == 1) return matrix;
        if (n % 2 == 0) {
            int[][] halfPower = matrixPower(matrix, n / 2);
            return matrixMultiply(halfPower, halfPower);
        } else {
            int[][] halfPower = matrixPower(matrix, (n - 1) / 2);
            int[][] temp = matrixMultiply(halfPower, halfPower);
            return matrixMultiply(temp, matrix);
        }
    }
}

