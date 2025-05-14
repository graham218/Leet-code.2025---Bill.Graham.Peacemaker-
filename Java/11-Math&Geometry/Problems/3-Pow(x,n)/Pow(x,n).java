import java.lang.Math; // Import for the Math.pow() method

public class PowerOfNumber {

    public static void main(String[] args) {
        double x = 2.0;
        int n = 10;

        // Approach 1: Iterative Method
        System.out.println("Approach 1: Iterative Power: " + iterativePower(x, n)); // Output: 1024.0

        // Approach 2: Recursive Method
        System.out.println("Approach 2: Recursive Power: " + recursivePower(x, n)); // Output: 1024.0

        // Approach 3: Optimized Recursive Method (Binary Exponentiation)
        System.out.println("Approach 3: Optimized Recursive Power: " + optimizedRecursivePower(x, n)); // Output: 1024.0

        // Approach 4: Using Math.pow()
        System.out.println("Approach 4: Using Math.pow(): " + powerUsingMathPow(x, n)); // Output: 1024.0

        // Approach 5: Iterative Bitwise
        System.out.println("Approach 5: Iterative Bitwise: " + iterativeBitwise(x, n));
    }

    /**
     * Approach 1: Iterative Method
     * Calculates x^n using a simple iterative loop.
     * Handles positive and negative exponents.
     *
     * @param x The base number.
     * @param n The exponent.
     * @return The result of x raised to the power of n.
     */
    public static double iterativePower(double x, int n) {
        double result = 1.0;
        long absN = Math.abs((long)n); // Use long to handle Integer.MIN_VALUE

        for (int i = 0; i < absN; i++) {
            result *= x;
        }

        if (n < 0) {
            result = 1.0 / result;
        }
        return result;
    }

    /**
     * Approach 2: Recursive Method
     * Calculates x^n using a recursive approach.
     * Handles positive and negative exponents.
     *
     * @param x The base number.
     * @param n The exponent.
     * @return The result of x raised to the power of n.
     */
    public static double recursivePower(double x, int n) {
        if (n == 0) {
            return 1.0;
        }

        double result;
        if (n > 0) {
            result = x * recursivePower(x, n - 1);
        } else { // n < 0
            result = (1.0 / x) * recursivePower(x, n + 1);
        }
        return result;
    }

    /**
     * Approach 3: Optimized Recursive Method (Binary Exponentiation)
     * Calculates x^n using a more efficient recursive approach based on binary exponentiation.
     * It significantly reduces the number of multiplications.
     * Handles positive and negative exponents.
     *
     * @param x The base number.
     * @param n The exponent.
     * @return The result of x raised to the power of n.
     */
    public static double optimizedRecursivePower(double x, int n) {
        if (n == 0) {
            return 1.0;
        }
        double result;
        long absN = Math.abs((long)n);
        if (absN % 2 == 0) { // n is even
            double temp = optimizedRecursivePower(x, (int)(absN / 2));
            result = temp * temp;
        } else { // n is odd
            double temp = optimizedRecursivePower(x, (int)(absN / 2));
            result = x * temp * temp;
        }

        if (n < 0)
        {
            result = 1.0/result;
        }
        return result;
    }

    /**
     * Approach 4: Using Math.pow()
     * Calculates x^n using the built-in Math.pow() method from the Java library.
     *
     * @param x The base number.
     * @param n The exponent.
     * @return The result of x raised to the power of n.
     */
    public static double powerUsingMathPow(double x, int n) {
        return Math.pow(x, n);
    }

    /**
     * Approach 5: Iterative Bitwise
     * Computes x^n using bitwise operations.  This is a very efficient
     * method, particularly for integer exponents.
     *
     * @param x The base
     * @param n The exponent
     * @return x raised to the power n
     */
    public static double iterativeBitwise(double x, int n) {
        double result = 1.0;
        long absN = Math.abs((long)n); // Use long for absolute value

        while (absN > 0) {
            if ((absN & 1) == 1) { // Check if the least significant bit is 1
                result *= x;
            }
            x *= x; // Square x
            absN >>= 1; // Right shift n (divide by 2)
        }
        if (n < 0) {
            result = 1.0 / result;
        }
        return result;
    }
}
