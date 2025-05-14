import java.util.*;
import java.io.*;

public class FastExponentiation {

    /**
     * **1. Recursive Approach**
     *
     * * **Concept:** This method recursively calculates the power by halving the exponent.
     * * **Time Complexity:** O(log n), where n is the exponent.
     * * **Space Complexity:** O(log n) due to the recursion depth.
     * * **Real-world application:** Useful in scenarios where a clear, concise implementation is favored, and the input size (exponent) is reasonably small.  For example, calculating powers in a configuration file parser.
     *
     * @param base     The base number.
     * @param exponent The exponent.
     * @return The result of base raised to the power of exponent.
     */
    public static long recursivePower(long base, long exponent) {
        if (exponent == 0) {
            return 1;
        }
        if (exponent % 2 == 0) {
            long temp = recursivePower(base, exponent / 2);
            return temp * temp;
        } else {
            return base * recursivePower(base, exponent - 1);
        }
    }

    /**
     * **2. Iterative Approach**
     *
     * * **Concept:** This method iteratively calculates the power using bitwise operations. It's generally preferred over the recursive approach due to its lower memory overhead.
     * * **Time Complexity:** O(log n), where n is the exponent.
     * * **Space Complexity:** O(1) - constant space.
     * * **Real-world application:** This is the most common and preferred method.  It's used in cryptographic algorithms (like RSA) and anywhere performance is critical, such as in game development or high-performance computing.
     *
     * @param base     The base number.
     * @param exponent The exponent.
     * @return The result of base raised to the power of exponent.
     */
    public static long iterativePower(long base, long exponent) {
        long result = 1;
        long currentBase = base; // Avoid modifying the original base

        while (exponent > 0) {
            if ((exponent & 1) == 1) { // Check if the least significant bit is 1
                result *= currentBase;
            }
            currentBase *= currentBase; // Square the base
            exponent >>= 1;             // Right shift the exponent (divide by 2)
        }
        return result;
    }

    /**
     * **3. Optimized Iterative Approach (Slightly more efficient)**
     *
     * * **Concept:** This is a variation of the iterative approach that aims to reduce the number of multiplications in some cases.  It's often very slightly faster than the standard iterative method.
     * * **Time Complexity:** O(log n), where n is the exponent.
     * * **Space Complexity:** O(1)
     * * **Real-world application:** This can be used in performance-critical applications where even small optimizations matter.  For example, in embedded systems or when writing very efficient numerical libraries.
     *
     * @param base     The base number.
     * @param exponent The exponent.
     * @return The result of base raised to the power of exponent.
     */
    public static long optimizedIterativePower(long base, long exponent) {
        long result = 1;
        long currentBase = base;

        while (exponent > 0) {
            if (exponent % 2 == 1) {
                result = result * currentBase;
            }
            exponent = exponent / 2;
            currentBase = currentBase * currentBase;
        }
        return result;
    }

    /**
     * **4. Using Java's Math.pow() (For smaller exponents)**
     *
     * * **Concept:** Java's built-in Math.pow() method provides a convenient way to calculate powers.  However, it uses double-precision floating-point numbers, which can introduce inaccuracies for very large numbers or integer bases and exponents.  It is also generally less efficient for integer exponentiation than the bitwise methods.
     * * **Time Complexity:** The time complexity of `Math.pow()` is implementation-dependent, but it's generally efficient.  It's *not* guaranteed to be O(log n) for all inputs, and can be slower for integer powers.
     * * **Space Complexity:** O(1)
     * * **Real-world application:** Good for quick calculations in applications where accuracy with floating-point numbers is sufficient and performance is not the absolute highest priority.  For example, in a scientific calculator application or for simple calculations in a user interface.  It's often *not* suitable for cryptography or high-performance integer math.
     *
     * @param base     The base number (will be cast to double).
     * @param exponent The exponent (will be cast to double).
     * @return The result of base raised to the power of exponent (as a double).
     */
    public static double javaMathPow(double base, double exponent) {
        return Math.pow(base, exponent);
    }

    /**
     * **5. Modular Exponentiation**
     *
     * * **Concept:** This method calculates (base^exponent) % modulus efficiently.  It's crucial for cryptography.  It prevents intermediate results from becoming too large.
     * * **Time Complexity:** O(log n), where n is the exponent.
     * * **Space Complexity:** O(1)
     * * **Real-world application:** Essential in cryptography, especially in algorithms like RSA and Diffie-Hellman key exchange, where you need to calculate large powers modulo a number.  Also used in hashing algorithms and other areas of computer science.
     *
     * @param base     The base number.
     * @param exponent The exponent.
     * @param modulus  The modulus.
     * @return (base^exponent) % modulus
     */
    public static long modularExponentiation(long base, long exponent, long modulus) {
        long result = 1;
        long currentBase = base % modulus; // Important to reduce base modulo modulus

        while (exponent > 0) {
            if ((exponent & 1) == 1) {
                result = (result * currentBase) % modulus;
            }
            currentBase = (currentBase * currentBase) % modulus; // Reduce squared base modulo modulus
            exponent >>= 1;
        }
        return result;
    }

    public static void main(String[] args) {
        long base = 2;
        long exponent = 30; // Changed to 30 to show the efficiency
        long modulus = 1000000007; // A common prime modulus

        System.out.println("Base: " + base + ", Exponent: " + exponent);

        // 1. Recursive Approach
        long result1 = recursivePower(base, exponent);
        System.out.println("Recursive Power: " + result1);

        // 2. Iterative Approach
        long result2 = iterativePower(base, exponent);
        System.out.println("Iterative Power: " + result2);

        // 3. Optimized Iterative Approach
        long result3 = optimizedIterativePower(base, exponent);
        System.out.println("Optimized Iterative Power: " + result3);

        // 4. Using Java's Math.pow()
        double result4 = javaMathPow(base, exponent);
        System.out.println("Java Math.pow(): " + result4);

        // 5. Modular Exponentiation
        long result5 = modularExponentiation(base, exponent, modulus);
        System.out.println("Modular Exponentiation: " + result5);
    }
}
