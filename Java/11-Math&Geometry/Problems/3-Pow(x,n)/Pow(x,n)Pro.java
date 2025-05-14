import java.util.HashMap;
import java.util.Map;

public class PowerFunction {

    public static void main(String[] args) {
        double x = 2.0;
        int n = 10;

        // 1. Basic Iterative Approach
        System.out.println("1. Basic Iterative: " + powerIterative(x, n)); // Output: 1024.0

        // 2. Optimized Iterative Approach
        System.out.println("2. Optimized Iterative: " + powerOptimizedIterative(x, n)); // Output: 1024.0

        // 3. Recursive Approach
        System.out.println("3. Recursive: " + powerRecursive(x, n)); // Output: 1024.0

        // 4. Recursive Approach with Memoization
        System.out.println("4. Recursive with Memoization: " + powerRecursiveMemoization(x, n)); // Output: 1024.0

        // 5. Using Math.pow() (Real-world Library Function)
        System.out.println("5. Math.pow(): " + powerUsingMathPow(x, n));
    }

    /**
     * 1. Basic Iterative Approach:
     * - Calculates x^n using a simple loop.
     * - Multiplies x by itself n times.
     * - Handles positive and negative exponents.
     * - Time Complexity: O(n)
     * - Space Complexity: O(1)
     * - Real-world application: Simple calculations in calculators, scripting.
     */
    public static double powerIterative(double x, int n) {
        double result = 1.0;
        if (n == 0) {
            return 1.0;
        }
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }
        for (int i = 0; i < n; i++) {
            result *= x;
        }
        return result;
    }

    /**
     * 2. Optimized Iterative Approach:
     * - Uses the property x^n = x^(n/2) * x^(n/2) for even n, and x * x^(n-1) for odd n.
     * - Reduces the number of multiplications significantly.
     * - Handles positive and negative exponents.
     * - Time Complexity: O(log n)
     * - Space Complexity: O(1)
     * - Real-world application: Efficient computation in scientific computing, financial calculations.
     */
    public static double powerOptimizedIterative(double x, int n) {
        double result = 1.0;
        if (n == 0) {
            return 1.0;
        }
        if (n < 0) {
            x = 1 / x;
            n = -n;
        }
        while (n > 0) {
            if (n % 2 == 1) { // n is odd
                result *= x;
            }
            x *= x;
            n /= 2;
        }
        return result;
    }

    /**
     * 3. Recursive Approach:
     * - Implements the same logic as the optimized iterative approach, but recursively.
     * - Breaks down the problem into smaller subproblems.
     * - Can be less efficient than the iterative approach due to function call overhead.
     * - Time Complexity: O(log n)
     * - Space Complexity: O(log n) (due to the call stack)
     * - Real-world application: Demonstrating recursion, used in divide-and-conquer algorithms.
     */
    public static double powerRecursive(double x, int n) {
        if (n == 0) {
            return 1.0;
        }
        if (n < 0) {
            return powerRecursive(1 / x, -n);
        }
        if (n % 2 == 0) { // n is even
            double temp = powerRecursive(x, n / 2);
            return temp * temp;
        } else { // n is odd
            return x * powerRecursive(x, n - 1);
        }
    }

    /**
     * 4. Recursive Approach with Memoization:
     * - Optimizes the recursive approach by storing previously computed results.
     * - Uses a HashMap to store intermediate values.
     * - Avoids redundant calculations.
     * - Time Complexity: O(log n)
     * - Space Complexity: O(log n) (for the HashMap and call stack)
     * - Real-world application: Dynamic programming problems, caching results of expensive operations.
     */
    static Map<Integer, Double> memo = new HashMap<>();

    public static double powerRecursiveMemoization(double x, int n) {
        if (n == 0) {
            return 1.0;
        }
        if (n < 0) {
            return powerRecursiveMemoization(1 / x, -n);
        }
        if (memo.containsKey(n)) {
            return memo.get(n);
        }
        double result;
        if (n % 2 == 0) {
            double temp = powerRecursiveMemoization(x, n / 2);
            result = temp * temp;
        } else {
            result = x * powerRecursiveMemoization(x, n - 1);
        }
        memo.put(n, result);
        return result;
    }

    /**
     * 5. Using Math.pow() (Real-world Library Function):
     * - Utilizes the built-in Math.pow() function from the Java library.
     * - Highly optimized and efficient.
     * - Preferred method for most practical applications.
     * - Time Complexity: Implementation-dependent, typically very efficient (O(log n) or better).
     * - Space Complexity: O(1)
     * - Real-world application: Standard way to calculate powers in Java applications.
     */
    public static double powerUsingMathPow(double x, int n) {
        return Math.pow(x, n);
    }
}

