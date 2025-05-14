import java.util.InputMismatchException;
import java.util.Scanner;

public class PowerOfTwo {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = 0; // Initialize number

        // Input Handling
        System.out.println("Enter an integer to check if it's a power of two:");
        try {
            number = scanner.nextInt();
        } catch (InputMismatchException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            scanner.close();
            return; // Exit the program
        } finally {
            // Ensure scanner is closed to prevent resource leaks
            scanner.close();
        }


        // Input Validation: Handles negative numbers and zero.
        if (number <= 0) {
            System.out.println("Number must be greater than zero to be a power of two.");
            return;
        }

        // 1. Bitwise AND Approach
        System.out.println("\n1. Bitwise AND Approach:");
        boolean isPowerOfTwoBitwise = isPowerOfTwoBitwise(number);
        System.out.println(number + " is a power of two: " + isPowerOfTwoBitwise);

        // 2. Division by 2 Approach
        System.out.println("\n2. Division by 2 Approach:");
        boolean isPowerOfTwoDivision = isPowerOfTwoDivision(number);
        System.out.println(number + " is a power of two: " + isPowerOfTwoDivision);

        // 3. Using Math.log() Approach
        System.out.println("\n3. Using Math.log() Approach:");
        boolean isPowerOfTwoLog = isPowerOfTwoLog(number);
        System.out.println(number + " is a power of two: " + isPowerOfTwoLog);

        // 4. Counting Set Bits Approach
        System.out.println("\n4. Counting Set Bits Approach:");
        boolean isPowerOfTwoCountBits = isPowerOfTwoCountSetBits(number);
        System.out.println(number + " is a power of two: " + isPowerOfTwoCountBits);

        // 5. Optimized Bitwise AND
        System.out.println("\n5. Optimized Bitwise AND Approach:");
        boolean isPowerOfTwoOptimized = isPowerOfTwoOptimized(number);
        System.out.println(number + " is a power of two: " + isPowerOfTwoOptimized);
    }

    /**
     * 1. Bitwise AND Approach:
     * A power of two in binary has only one bit set (e.g., 10, 100, 1000).
     * Subtracting 1 from a power of two results in a number with all bits
     * set up to the position of the original set bit (e.g., 10 - 1 = 01, 100 - 1 = 011).
     * The bitwise AND of these two numbers will be 0.
     *
     * @param n The number to check.
     * @return True if n is a power of two, false otherwise.
     */
    public static boolean isPowerOfTwoBitwise(int n) {
        // Handle edge case of 0.  A power of two must be greater than 0.
        if (n <= 0) {
            return false;
        }
        return (n & (n - 1)) == 0;
    }

    /**
     * 2. Division by 2 Approach:
     * Repeatedly divides the number by 2. If the number is a power of two,
     * it will eventually become 1. If at any point the remainder is not 0
     * (except for the last division), the number is not a power of two.
     *
     * @param n The number to check.
     * @return True if n is a power of two, false otherwise.
     */
    public static boolean isPowerOfTwoDivision(int n) {
        if (n <= 0) {
            return false;
        }
        while (n % 2 == 0) {
            n /= 2;
        }
        return n == 1;
    }

    /**
     * 3. Using Math.log() Approach:
     * The logarithm base 2 of a power of two is an integer.
     * We can use Math.log() to calculate the logarithm and check if it's an integer.
     *
     * @param n The number to check.
     * @return True if n is a power of two, false otherwise.
     */
    public static boolean isPowerOfTwoLog(int n) {
        if (n <= 0) {
            return false;
        }
        double logValue = Math.log(n) / Math.log(2);
        // Check if the logValue is very close to an integer
        return Math.abs(logValue - Math.round(logValue)) < 1e-10; // Use a small tolerance
    }

    /**
     * 4. Counting Set Bits Approach:
     * A power of two has only one bit set to 1.  We can count the number of set bits.
     *
     * @param n The number to check.
     * @return True if n is a power of two, false otherwise.
     */
    public static boolean isPowerOfTwoCountSetBits(int n) {
        if (n <= 0) {
            return false;
        }
        int count = 0;
        while (n > 0) {
            count += (n & 1); // Check the least significant bit
            n >>= 1;         // Right shift n by 1
        }
        return count == 1;
    }

    /**
     * 5. Optimized Bitwise AND Approach
     * This is a slightly optimized version of the first approach.  It avoids the subtraction.
     *
     * @param n The number to check
     * @return True if n is a power of 2, false otherwise
     */
    public static boolean isPowerOfTwoOptimized(int n) {
        if (n <= 0) return false;
        return (n & -n) == n;
    }
}
