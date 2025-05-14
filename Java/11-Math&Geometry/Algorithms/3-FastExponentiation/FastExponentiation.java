import java.util.*;
import java.io.*;

class FastExponentiation {

    // 1. Recursive Approach
    //   - Time Complexity: O(log n)
    //   - Space Complexity: O(log n) due to recursion depth
    //   - Explanation:
    //     - Base case: If the exponent is 0, return 1.
    //     - Recursive step:
    //       - Calculate the result for n/2 recursively.
    //       - If the exponent is even, return the square of the result.
    //       - If the exponent is odd, return the base times the square of the result.
    public static long recursiveExponentiation(long base, long exponent) {
        if (exponent == 0) {
            return 1;
        }
        long temp = recursiveExponentiation(base, exponent / 2);
        if (exponent % 2 == 0) {
            return temp * temp;
        } else {
            return base * temp * temp;
        }
    }

    // 2. Iterative Approach
    //   - Time Complexity: O(log n)
    //   - Space Complexity: O(1)
    //   - Explanation:
    //     - Initialize the result to 1.
    //     - Iterate while the exponent is greater than 0.
    //     - If the exponent is odd, multiply the result by the base.
    //     - Square the base and divide the exponent by 2 in each iteration.
    public static long iterativeExponentiation(long base, long exponent) {
        long result = 1;
        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result *= base;
            }
            base *= base;
            exponent /= 2;
        }
        return result;
    }

    // 3. Optimized Iterative Approach (Bit Manipulation)
    //   - Time Complexity: O(log n)
    //   - Space Complexity: O(1)
    //   - Explanation:
    //     - Uses bit manipulation to check if the exponent is odd or even.
    //     - `exponent & 1` is equivalent to `exponent % 2`.
    //     - `exponent >>= 1` is equivalent to `exponent /= 2`.
    //     - This approach is often faster in practice due to the efficiency of bitwise operations.
    public static long optimizedIterativeExponentiation(long base, long exponent) {
        long result = 1;
        while (exponent > 0) {
            if ((exponent & 1) == 1) { // Check if exponent is odd
                result *= base;
            }
            base *= base;
            exponent >>= 1; // Divide exponent by 2
        }
        return result;
    }

    // 4. Recursive Approach with Memoization
    //   - Time Complexity: O(log n)
    //   - Space Complexity: O(log n) for memoization map + O(log n) for recursion stack = O(log n)
    //   - Explanation:
    //     - Uses a HashMap to store the results of subproblems.
    //     - This avoids redundant calculations and improves performance, especially for larger exponents.
    public static long memoizationExponentiation(long base, long exponent, Map<Long, Long> memo) {
        if (exponent == 0) {
            return 1;
        }
        if (memo.containsKey(exponent)) {
            return memo.get(exponent);
        }
        long temp = memoizationExponentiation(base, exponent / 2, memo);
        long result;
        if (exponent % 2 == 0) {
            result = temp * temp;
        } else {
            result = base * temp * temp;
        }
        memo.put(exponent, result);
        return result;
    }

    // 5. Using Java's Math.pow() method
    //   - Time Complexity:  O(1) in most implementations, but can vary.
    //   - Space Complexity: O(1)
    //   - Explanation:
    //     -  Java's Math.pow() method is a built-in function to calculate the power of a number.
    //     -  It's generally highly optimized and often implemented using native code.
    //     -  Note: It uses double, so we need to cast to long.  Use with caution for very large numbers
    public static long javaPowExponentiation(long base, long exponent) {
        return (long) Math.pow(base, exponent);
    }

    public static void main(String[] args) {
        long base = 2;
        long exponent = 30;

        System.out.println("Base: " + base + ", Exponent: " + exponent);
        System.out.println("Recursive Exponentiation: " + recursiveExponentiation(base, exponent));
        System.out.println("Iterative Exponentiation: " + iterativeExponentiation(base, exponent));
        System.out.println("Optimized Iterative Exponentiation: " + optimizedIterativeExponentiation(base, exponent));
        System.out.println("Memoization Exponentiation: " + memoizationExponentiation(base, exponent, new HashMap<>()));
        System.out.println("Java Math.pow(): " + javaPowExponentiation(base, exponent));
    }
}

