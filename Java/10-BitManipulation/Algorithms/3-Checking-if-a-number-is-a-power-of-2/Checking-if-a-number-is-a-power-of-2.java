import java.util.Scanner;

public class PowerOfTwoChecker {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int number = scanner.nextInt();

        // Check if the number is a power of 2 using different methods and print the results.
        System.out.println(number + " is a power of 2 (Method 1: Using Logarithm): " + isPowerOfTwoLogarithm(number));
        System.out.println(number + " is a power of 2 (Method 2: Iterative Division): " + isPowerOfTwoDivision(number));
        System.out.println(number + " is a power of 2 (Method 3: Bitwise AND): " + isPowerOfTwoBitwise(number));
        System.out.println(number + " is a power of 2 (Method 4: Bitwise AND with (n-1)): " + isPowerOfTwoBitwiseMinusOne(number));
        System.out.println(number + " is a power of 2 (Method 5: Using Integer.bitCount()): " + isPowerOfTwoBitCount(number));
        scanner.close();
    }

    // Method 1: Using Logarithm
    // Check if a number is a power of 2 by calculating the base-2 logarithm.
    // If the logarithm is an integer, the number is a power of 2.
    //
    // Time Complexity: O(log n) - due to Math.log, but often considered near-constant time for practical purposes.
    // Space Complexity: O(1)
    public static boolean isPowerOfTwoLogarithm(int n) {
        if (n <= 0) {
            return false; // Handle negative numbers and zero
        }
        double logResult = Math.log(n) / Math.log(2);
        return (logResult == Math.floor(logResult)); // Check if the logarithm is an integer
    }

    // Method 2: Iterative Division
    // Repeatedly divide the number by 2. If the remainder is ever not 0
    // and the number is not 1, then it's not a power of 2.
    //
    // Time Complexity: O(log n) - number is divided by 2 in each iteration.
    // Space Complexity: O(1)
    public static boolean isPowerOfTwoDivision(int n) {
        if (n <= 0) {
            return false; // Handle negative numbers and zero
        }
        while (n % 2 == 0) {
            n /= 2;
        }
        return n == 1;
    }

    // Method 3: Bitwise AND
    // A power of 2 has only one bit set to 1 (e.g., 2 = 10, 4 = 100, 8 = 1000).
    // Subtracting 1 from a power of 2 will result in a number with all bits
    // less significant than the original '1' bit set to 1 (e.g., 3 = 011, 7 = 0111).
    // The bitwise AND of these two numbers will be 0.
    // This method handles only positive numbers.
    //
    // Time Complexity: O(1) - constant time bitwise operations.
    // Space Complexity: O(1)
    public static boolean isPowerOfTwoBitwise(int n) {
        if (n <= 0) {
            return false; // Handle negative numbers and zero.  Important to exclude negatives.
        }
        return (n & (n - 1)) == 0;
    }

    // Method 4: Bitwise AND with (n-1) - Optimized version of Method 3
    public static boolean isPowerOfTwoBitwiseMinusOne(int n) {
        if (n <= 0) return false;
        return (n & (n - 1)) == 0;
    }


    // Method 5: Using Integer.bitCount()
    //  The Integer.bitCount() method returns the number of one-bits in the binary representation of an integer.
    //  A power of two has only one bit set to 1.
    //
    // Time Complexity: O(1) -  Integer.bitCount() is generally considered a constant-time operation.
    // Space Complexity: O(1)
    public static boolean isPowerOfTwoBitCount(int n) {
        if (n <= 0) {
            return false;
        }
        return Integer.bitCount(n) == 1;
    }
}

