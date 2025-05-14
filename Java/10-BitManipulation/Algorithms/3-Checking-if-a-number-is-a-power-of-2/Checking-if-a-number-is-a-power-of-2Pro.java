import java.util.InputMismatchException;
import java.util.Scanner;

public class PowerOfTwoChecker {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = 0; // Initialize number

        // Input validation loop
        while (true) {
            System.out.print("Enter an integer to check if it's a power of 2: ");
            try {
                number = scanner.nextInt();
                if (number < 0) {
                    System.out.println("Please enter a non-negative integer.");
                } else {
                    break; // Exit loop if input is valid
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter an integer.");
                scanner.next(); // Consume the invalid input to prevent an infinite loop
            }
        }
        scanner.close();


        // 1. Using the Trick: n & (n-1) == 0
        System.out.println("\nMethod 1: Using n & (n-1) == 0");
        if (isPowerOfTwo_Bitwise(number)) {
            System.out.println(number + " is a power of 2.");
            // Example Usage: Configuration Flags in a System
            System.out.println("Example Application: Checking configuration flags in a system where powers of 2 represent individual features.");
        } else {
            System.out.println(number + " is not a power of 2.");
        }

        // 2. Repeated Division by 2
        System.out.println("\nMethod 2: Repeated Division by 2");
        if (isPowerOfTwo_Division(number)) {
            System.out.println(number + " is a power of 2.");
            // Example Usage: Image resizing
            System.out.println("Example Application: Useful in image processing for checking if dimensions are powers of 2.");
        } else {
            System.out.println(number + " is not a power of 2.");
        }

        // 3. Counting Set Bits
        System.out.println("\nMethod 3: Counting Set Bits");
        if (isPowerOfTwo_BitCount(number)) {
            System.out.println(number + " is a power of 2.");
            // Example Usage: Checking states
            System.out.println("Example Application: Determining if a system is in a unique state, represented by a single bit.");
        } else {
            System.out.println(number + " is not a power of 2.");
        }

        // 4. Using Math.log()
        System.out.println("\nMethod 4: Using Math.log()");
        if (isPowerOfTwo_Logarithm(number)) {
            System.out.println(number + " is a power of 2.");
            // Example Usage: Memory allocation
            System.out.println("Example Application: Determining optimal memory allocation sizes that are powers of 2.");
        } else {
            System.out.println(number + " is not a power of 2.");
        }

        // 5. Check against known powers of 2 (for a limited range)
        System.out.println("\nMethod 5: Check against known powers of 2");
        if (isPowerOfTwo_Precomputed(number)) {
            System.out.println(number + " is a power of 2.");
            System.out.println("Example Application: Efficiently validating input against a limited set of allowed sizes or values.");
        } else {
            System.out.println(number + " is not a power of 2.");
        }
    }

    // 1. Bitwise AND with (n-1)
    /**
     * Checks if a number is a power of 2 using the bitwise AND trick.
     * A power of 2 has only one bit set to 1.  Subtracting 1 from it will
     * result in a number where all bits up to that set bit are flipped.
     * The bitwise AND of the two will be 0.
     *
     * @param n The number to check.
     * @return true if n is a power of 2, false otherwise.
     */
    public static boolean isPowerOfTwo_Bitwise(int n) {
        if (n <= 0) {
            return false; // 0 and negative numbers are not powers of 2
        }
        return (n & (n - 1)) == 0;
    }

    // 2. Repeated Division by 2
    /**
     * Checks if a number is a power of 2 by repeatedly dividing it by 2.
     * If the number is a power of 2, it will eventually become 1.
     *
     * @param n The number to check.
     * @return true if n is a power of 2, false otherwise.
     */
    public static boolean isPowerOfTwo_Division(int n) {
        if (n <= 0) {
            return false; // 0 and negative numbers are not powers of 2
        }
        while (n % 2 == 0) {
            n /= 2;
        }
        return n == 1;
    }

    // 3. Counting Set Bits
    /**
     * Checks if a number is a power of 2 by counting the number of set bits.
     * A power of 2 has only one bit set to 1.
     *
     * @param n The number to check.
     * @return true if n is a power of 2, false otherwise.
     */
    public static boolean isPowerOfTwo_BitCount(int n) {
        if (n <= 0) {
            return false; // 0 and negative numbers are not powers of 2
        }
        int count = 0;
        while (n > 0) {
            count += (n & 1); // Check the least significant bit
            n >>= 1;         // Right shift n by 1
        }
        return count == 1;
    }

    // 4. Using Logarithm (Base 2)
    /**
     * Checks if a number is a power of 2 using logarithms.
     * If n is a power of 2, then log2(n) will be an integer.  We check
     * if the result is close to an integer to account for potential
     * floating-point inaccuracies.
     *
     * @param n The number to check.
     * @return true if n is a power of 2, false otherwise.
     */
    public static boolean isPowerOfTwo_Logarithm(int n) {
        if (n <= 0) {
            return false; // 0 and negative numbers are not powers of 2
        }
        double log2 = Math.log(n) / Math.log(2);
        // Check if log2 is very close to an integer
        return Math.abs(log2 - Math.round(log2)) < 1e-10; // Using a small tolerance
    }

    // 5. Check against known powers of 2 (for a limited range - int)
    /**
     * Checks if a number is a power of 2 by comparing it to precomputed powers of 2.
     * This is efficient for a limited range of inputs (e.g., within the range of an integer).
     *
     * @param n The number to check.
     * @return true if n is a power of 2, false otherwise.
     */
    public static boolean isPowerOfTwo_Precomputed(int n) {
        if (n <= 0) {
            return false; // 0 and negative numbers are not powers of 2
        }
        // Array of powers of 2 up to the largest power of 2 that an int can hold.
        int[] powersOfTwo = {
                1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384,
                32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304,
                8388608, 16777216, 33554432, 67108864, 134217728, 268435456,
                536870912, 1073741824
        };
        for (int powerOfTwo : powersOfTwo) {
            if (n == powerOfTwo) {
                return true;
            }
        }
        return false;
    }
}

