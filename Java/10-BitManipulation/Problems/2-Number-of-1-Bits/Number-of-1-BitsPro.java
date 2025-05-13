import java.util.InputMismatchException;
import java.util.Scanner;

public class NumberOf1Bits {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = 0; // Initialize number

        // Input validation loop
        while (true) {
            System.out.print("Enter a non-negative integer: ");
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
        scanner.close(); // Close the scanner to prevent resource leaks.

        // Call each method and print the result
        System.out.println("Number: " + number);
        System.out.println("Approach 1: Using Integer.bitCount(): " + countSetBits1(number));
        System.out.println("Approach 2: Bitwise AND with (n-1): " + countSetBits2(number));
        System.out.println("Approach 3: Right Shift and Check: " + countSetBits3(number));
        System.out.println("Approach 4: Using Unsigned Right Shift: " + countSetBits4(number));
        System.out.println("Approach 5: Lookup Table Method: " + countSetBits5(number));
    }

    /**
     * Approach 1: Using Integer.bitCount()
     * This is the simplest and most efficient way to count the number of set bits in an integer in Java.
     * It leverages the built-in Integer.bitCount() method, which is highly optimized.
     *
     * Real-world application:
     * -   **Network routing:** Counting the number of set bits in an IP address for subnet calculations.
     * -   **Data compression:** Determining the number of non-zero bytes in a data block.
     * -   **Cryptography:** Used in some cryptographic algorithms.
     *
     * @param n The integer.
     * @return The number of set bits in n.
     */
    public static int countSetBits1(int n) {
        return Integer.bitCount(n);
    }

    /**
     * Approach 2: Bitwise AND with (n-1)
     * This method repeatedly clears the least significant set bit of the number until it becomes 0.
     * The number of iterations is equal to the number of set bits.
     *
     * Explanation:
     * n & (n-1)  clears the rightmost 1-bit of n.
     * For example:
     * n = 10 (binary 1010)
     * n-1 = 9 (binary 1001)
     * n & (n-1) = 1000 (8 in decimal)
     *
     * Real-world application:
     * -   **Calculating Hamming weight:** Used in information theory and coding theory.
     * -   **Checking if a number is a power of 2:** A number is a power of 2 if and only if n & (n-1) is 0 (except for 0 itself).
     * -   **Graphics processing:** Counting the number of active pixels in a mask.
     *
     * @param n The integer.
     * @return The number of set bits in n.
     */
    public static int countSetBits2(int n) {
        int count = 0;
        while (n != 0) {
            n &= (n - 1); // Clear the least significant set bit
            count++;
        }
        return count;
    }

    /**
     * Approach 3: Right Shift and Check
     * This method iterates through the bits of the number, checking the least significant bit in each iteration.
     * It right-shifts the number in each step until it becomes 0.
     *
     * Real-world application:
     * -   **Embedded systems:** Analyzing individual bits in a register.
     * -   **Digital signal processing:** Extracting bit-level information from a signal.
     * -   **Protocol implementation:** Parsing bit fields in a network packet.
     *
     * @param n The integer.
     * @return The number of set bits in n.
     */
    public static int countSetBits3(int n) {
        int count = 0;
        while (n != 0) {
            if ((n & 1) == 1) { // Check if the least significant bit is set
                count++;
            }
            n >>= 1; // Right shift n by 1 bit.  Sign extension occurs.
        }
        return count;
    }

    /**
     * Approach 4: Using Unsigned Right Shift (>>>)
     * Similar to approach 3, but uses the unsigned right shift operator (>>>) to avoid sign extension.
     * This is important for negative numbers, where the sign bit is shifted in with the regular right shift (>>).
     *
     * Real-world application:
     * -   **Low-level systems programming:** When you need to treat the number as an unsigned value.
     * -   **Implementing cryptographic algorithms:** Some algorithms require unsigned right shifts.
     * -  **Image processing:** Processing pixel data where values are often treated as unsigned.
     *
     * @param n The integer.
     * @return The number of set bits in n.
     */
    public static int countSetBits4(int n) {
        int count = 0;
        while (n != 0) {
            if ((n & 1) == 1) {
                count++;
            }
            n >>>= 1; // Unsigned right shift
        }
        return count;
    }

    /**
     * Approach 5: Lookup Table Method
     * This method pre-computes the number of set bits for all possible byte values (0-255) and stores them in a lookup table.
     * It then breaks the integer into bytes and uses the lookup table to count the set bits in each byte.
     * This approach is very efficient for large numbers, as it reduces the number of operations.
     *
     * Real-world application:
     * -   **High-performance computing:** When counting set bits is a bottleneck and needs to be optimized.
     * -  **Large data processing:** Counting set bits in large datasets.
     * -  **Memory-constrained systems:** If memory for the lookup table is available, this can be faster than bitwise operations.
     *
     * @param n The integer.
     * @return The number of set bits in n.
     */
    public static int countSetBits5(int n) {
        int[] lookup = new int[256];
        // Initialize the lookup table
        for (int i = 0; i < 256; i++) {
            lookup[i] = Integer.bitCount(i); // Pre-compute set bits for each byte value
        }

        int count = 0;
        // Break the integer into 4 bytes and use the lookup table.  Handles negative numbers correctly.
        count += lookup[n & 0xFF];
        count += lookup[(n >> 8) & 0xFF];
        count += lookup[(n >> 16) & 0xFF];
        count += lookup[(n >> 24) & 0xFF];
        return count;
    }
}
