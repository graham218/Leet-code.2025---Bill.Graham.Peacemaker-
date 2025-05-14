import java.util.*;
import java.io.*;

class PowerOfTwo {

    // Approach 1: Using division by 2
    // Keep dividing the number by 2. If it is a power of 2, it will eventually become 1.
    // This approach handles edge cases like 0 correctly.
    public static boolean isPowerOfTwo_Approach1(int n) {
        if (n <= 0) {
            return false; // 0 and negative numbers are not powers of 2
        }
        while (n % 2 == 0) {
            n /= 2;
        }
        return n == 1;
    }

    // Approach 2: Using bitwise AND operator
    // A power of 2 in binary representation has only one bit set (e.g., 10, 100, 1000).
    // n & (n-1) will clear the least significant bit.  For a power of 2, this result will be 0.
    public static boolean isPowerOfTwo_Approach2(int n) {
        if (n <= 0) {
            return false; // 0 and negative numbers are not powers of 2
        }
        return (n & (n - 1)) == 0;
    }

    // Approach 3: Counting set bits
    // A power of two has only one bit set in its binary representation.
    // We can count the number of set bits and check if it is equal to 1.
    public static boolean isPowerOfTwo_Approach3(int n) {
        if (n <= 0) {
            return false; // 0 and negative numbers are not powers of 2.
        }
        int count = 0;
        while (n > 0) {
            count += (n & 1); // Check the last bit and add it to the count
            n >>= 1;         // Right shift the number (divide by 2)
        }
        return count == 1;
    }

    // Approach 4: Using Math.log()
    // The logarithm base 2 of a power of 2 is an integer.
    // We can use Math.log() to calculate the logarithm and check if it is an integer.
    public static boolean isPowerOfTwo_Approach4(int n) {
        if (n <= 0) {
            return false; // 0 and negative numbers are not powers of 2
        }
        // Math.log(n) / Math.log(2) is equivalent to log2(n)
        double logResult = Math.log(n) / Math.log(2);
        // Check if the result is an integer.  We use a small epsilon to handle
        // potential precision issues with floating-point numbers.
        final double EPSILON = 1e-10;
        return Math.abs(logResult - Math.round(logResult)) < EPSILON;
    }

    // Approach 5: Optimized bitwise AND (Handles Integer.MIN_VALUE)
    //  n & -n isolates the least significant bit of n.
    //  For powers of two, this will be equal to the number itself, except for Integer.MIN_VALUE
    public static boolean isPowerOfTwo_Approach5(int n) {
        if (n <= 0) {
            return false;
        }
        if (n == Integer.MIN_VALUE) {
            return false; // Integer.MIN_VALUE is not a power of 2
        }
        return (n & -n) == n;
    }
    public static void main(String[] args) {
        // Test cases
        int[] testNumbers = {0, 1, 2, 3, 4, 5, 8, 16, 24, 32, -4, Integer.MIN_VALUE, Integer.MAX_VALUE};

        // Test all the methods
        for (int num : testNumbers) {
            System.out.println("Number: " + num);
            System.out.println("Approach 1: " + isPowerOfTwo_Approach1(num));
            System.out.println("Approach 2: " + isPowerOfTwo_Approach2(num));
            System.out.println("Approach 3: " + isPowerOfTwo_Approach3(num));
            System.out.println("Approach 4: " + isPowerOfTwo_Approach4(num));
            System.out.println("Approach 5: " + isPowerOfTwo_Approach5(num));
            System.out.println("--------------------");
        }

        // Additional test cases
        System.out.println("Testing edge cases:");
        System.out.println("isPowerOfTwo_Approach1(0): " + isPowerOfTwo_Approach1(0));
        System.out.println("isPowerOfTwo_Approach1(1): " + isPowerOfTwo_Approach1(1));
        System.out.println("isPowerOfTwo_Approach1(2): " + isPowerOfTwo_Approach1(2));
        System.out.println("isPowerOfTwo_Approach1(3): " + isPowerOfTwo_Approach1(3));
        System.out.println("isPowerOfTwo_Approach1(4): " + isPowerOfTwo_Approach1(4));
        System.out.println("isPowerOfTwo_Approach1(5): " + isPowerOfTwo_Approach1(5));
        System.out.println("isPowerOfTwo_Approach1(16): " + isPowerOfTwo_Approach1(16));
        System.out.println("isPowerOfTwo_Approach1(24): " + isPowerOfTwo_Approach1(24));

    }
}
