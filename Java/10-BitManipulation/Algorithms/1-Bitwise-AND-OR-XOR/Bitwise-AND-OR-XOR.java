/*
 * Bit Manipulation: Bitwise AND, OR, XOR in Java
 *
 * This program demonstrates the fundamental bitwise operations in Java: AND, OR, and XOR.
 * It provides five different approaches to illustrate these operations with detailed explanations.
 */

public class BitManipulation {

    public static void main(String[] args) {
        // Example values
        int a = 12; // Binary: 1100
        int b = 25; // Binary: 11001

        System.out.println("Bitwise Operations on a = " + a + " and b = " + b);
        System.out.println("---------------------------------------------------");

        // Approach 1: Basic Bitwise AND
        System.out.println("\nApproach 1: Bitwise AND (&)");
        System.out.println("Performs a bit-by-bit AND operation.");
        System.out.println("Result: a & b = " + (a & b) + " (Binary: " + Integer.toBinaryString(a & b) + ")");
        // Explanation:
        //   1100
        // & 11001
        // --------
        //   0100  (Decimal 4)
        // The AND operation returns 1 only if both corresponding bits are 1.

        // Approach 2: Basic Bitwise OR
        System.out.println("\nApproach 2: Bitwise OR (|)");
        System.out.println("Performs a bit-by-bit OR operation.");
        System.out.println("Result: a | b = " + (a | b) + " (Binary: " + Integer.toBinaryString(a | b) + ")");
        // Explanation:
        //   1100
        // | 11001
        // --------
        //   11101 (Decimal 29)
        // The OR operation returns 1 if at least one of the corresponding bits is 1.

        // Approach 3: Basic Bitwise XOR
        System.out.println("\nApproach 3: Bitwise XOR (^)");
        System.out.println("Performs a bit-by-bit XOR (exclusive OR) operation.");
        System.out.println("Result: a ^ b = " + (a ^ b) + " (Binary: " + Integer.toBinaryString(a ^ b) + ")");
        // Explanation:
        //   1100
        // ^ 11001
        // --------
        //   11101 (Decimal 21)
        // The XOR operation returns 1 if the corresponding bits are different.

        // Approach 4: Using Bitwise AND to check if a number is even or odd
        System.out.println("\nApproach 4: Check if a number is even or odd using Bitwise AND");
        int num = 7;
        System.out.println("Number: " + num);
        if ((num & 1) == 0) {
            System.out.println(num + " is even.");
        } else {
            System.out.println(num + " is odd.");
        }
        // Explanation:
        // The least significant bit of an odd number is always 1, and for an even number, it's 0.
        //  7 in binary is 0111. 0111 & 0001 = 0001 (1), which is non-zero (true), hence odd.
        //  6 in binary is 0110. 0110 & 0001 = 0000 (0), which is zero (false), hence even.

        // Approach 5: Using Bitwise OR to set a specific bit
        System.out.println("\nApproach 5: Set a specific bit using Bitwise OR");
        int number = 10; // Binary: 1010
        int position = 1; // Let's set the bit at position 1 (from the right, 0-indexed)
        int mask = 1 << position; // Create a mask: 0010
        int result = number | mask; // Perform the OR operation
        System.out.println("Number: " + number + " (Binary: " + Integer.toBinaryString(number) + ")");
        System.out.println("Set bit at position " + position + " using mask " + mask + " (Binary: " + Integer.toBinaryString(mask) + ")");
        System.out.println("Result: " + result + " (Binary: " + Integer.toBinaryString(result) + ")");
        // Explanation:
        //  1010 (10)
        // |0010 (2)
        // ------
        //  1010 (10)  Incorrect.  The bit at position 1 is already set.
        // Let's try with number = 8 (1000 in binary) and position 1.
        //  1000 (8)
        // |0010 (2)
        // ------
        //  1010 (10) The bit at position 1 is set.

        // Approach 6: Using Bitwise XOR to toggle a specific bit.
        System.out.println("\nApproach 6: Toggle a specific bit using Bitwise XOR");
        int numToToggle = 10; // Binary 1010
        int posToToggle = 1;
        int toggleMask = 1 << posToToggle; // 0010
        int toggledResult = numToToggle ^ toggleMask;
        System.out.println("Number: " + numToToggle + " (Binary: " + Integer.toBinaryString(numToToggle) + ")");
        System.out.println("Toggling bit at position: " + posToToggle);
        System.out.println("Result: " + toggledResult + " (Binary: " + Integer.toBinaryString(toggledResult) + ")");
        // Explanation:
        // 1010
        // 0010 ^
        // ----
        // 1000
        // If the bit is 1, XORing with 1 makes it 0. If the bit is 0, XORing with 1 makes it 1.
    }
}
