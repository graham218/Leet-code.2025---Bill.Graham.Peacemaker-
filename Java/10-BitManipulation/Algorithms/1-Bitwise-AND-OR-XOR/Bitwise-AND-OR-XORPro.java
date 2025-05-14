import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class BitwiseOperations {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int num1, num2;

        System.out.println("Enter two integers:");
        num1 = scanner.nextInt();
        num2 = scanner.nextInt();

        System.out.println("\nBitwise Operations:");
        System.out.println("-------------------");

        // 1. Basic Bitwise AND, OR, XOR
        System.out.println("\n1. Basic Operations:");
        basicOperations(num1, num2);

        // 2. Using Bitwise AND for Checking Even/Odd
        System.out.println("\n2. Checking Even/Odd:");
        checkEvenOdd(num1);

        // 3. Using Bitwise OR for Setting a Bit
        System.out.println("\n3. Setting a Bit:");
        int bitToSet = 2; // Set the 2nd bit (0-based index)
        int resultOr = setBit(num1, bitToSet);
        System.out.println("Original number: " + num1 + ", After setting bit " + bitToSet + ": " + resultOr);

        // 4. Using Bitwise XOR for Toggling a Bit
        System.out.println("\n4. Toggling a Bit:");
        int bitToToggle = 1; // Toggle the 1st bit (0-based index)
        int resultXor = toggleBit(num1, bitToToggle);
        System.out.println("Original number: " + num1 + ", After toggling bit " + bitToToggle + ": " + resultXor);

        // 5. Using Bitwise AND to check if a number is power of 2
        System.out.println("\n5. Check if Power of 2:");
        checkPowerOfTwo(num1);

        scanner.close();
    }

    // 1. Basic Bitwise AND, OR, XOR Operations
    // Demonstrates the basic usage of bitwise operators.
    public static void basicOperations(int num1, int num2) {
        System.out.println("Number 1: " + num1 + " (" + Integer.toBinaryString(num1) + ")");
        System.out.println("Number 2: " + num2 + " (" + Integer.toBinaryString(num2) + ")");
        System.out.println("-------------------");
        System.out.println("Bitwise AND (&): " + (num1 & num2) + " (" + Integer.toBinaryString(num1 & num2) + ")");
        System.out.println("Bitwise OR  (|): " + (num1 | num2) + " (" + Integer.toBinaryString(num1 | num2) + ")");
        System.out.println("Bitwise XOR (^): " + (num1 ^ num2) + " (" + Integer.toBinaryString(num1 ^ num2) + ")");
    }

    // 2. Using Bitwise AND for Checking Even/Odd
    // A common application of bitwise AND is to efficiently check if a number is even or odd.
    // If the least significant bit is 0, the number is even; otherwise, it's odd.
    public static void checkEvenOdd(int num) {
        if ((num & 1) == 0) {
            System.out.println(num + " is even.");
        } else {
            System.out.println(num + " is odd.");
        }
    }

    // 3. Using Bitwise OR for Setting a Bit
    // Bitwise OR can be used to set a specific bit in a number to 1.
    public static int setBit(int num, int bitPosition) {
        // Create a mask with a 1 at the desired bit position.
        int mask = 1 << bitPosition;
        return num | mask; // ORing with the mask sets the bit.
    }


    // 4. Using Bitwise XOR for Toggling a Bit
    // Bitwise XOR can be used to toggle a specific bit in a number (change 0 to 1 and vice-versa).
    public static int toggleBit(int num, int bitPosition) {
        // Create a mask with a 1 at the desired bit position.
        int mask = 1 << bitPosition;
        return num ^ mask; // XORing with the mask toggles the bit.
    }

    // 5. Using Bitwise AND to check if a number is power of 2
    public static void checkPowerOfTwo(int num) {
        if (num <= 0) {
            System.out.println(num + " is not a power of 2.");
            return;
        }
        // A power of 2 has only one bit set to 1.  Subtracting 1 will make that bit 0, and all lower bits 1.
        // ANDing the number with its predecessor will result in 0 if it's a power of 2.
        if ((num & (num - 1)) == 0) {
            System.out.println(num + " is a power of 2.");
        } else {
            System.out.println(num + " is not a power of 2.");
        }
    }
}

/*
Explanation:

1. Basic Bitwise Operations:
   - Demonstrates the fundamental use of &, |, and ^.
   - Example:
     - num1 = 5 (0101 in binary)
     - num2 = 3 (0011 in binary)
     - AND (&):  0101 & 0011 = 0001 (1 in decimal)
     - OR  (|):  0101 | 0011 = 0111 (7 in decimal)
     - XOR (^):  0101 ^ 0011 = 0110 (6 in decimal)

2. Checking Even/Odd:
   - Uses (num & 1) to check the least significant bit.
   - If the LSB is 0, the number is even.
   - If the LSB is 1, the number is odd.
   - This is more efficient than using the modulo operator (%)

3. Setting a Bit:
   - Uses the bitwise OR operator (|) to set a specific bit to 1.
   - A mask is created with a 1 at the desired position.
   - ORing the number with the mask sets that bit without affecting others.

4. Toggling a Bit:
   - Uses the bitwise XOR operator (^) to toggle a specific bit.
   - A mask is created with a 1 at the desired position.
   - XORing with the mask flips the bit (0 becomes 1, 1 becomes 0).

5. Check if Power of 2:
   - Uses the property that powers of 2 have only one bit set to 1.
   - num & (num - 1) clears the least significant 1-bit.
   - If the result is 0, the number is a power of 2.
   - Handles the edge case where num is 0.

Real-World Applications:

- Embedded Systems: Bitwise operations are crucial for low-level hardware manipulation, setting registers, and controlling devices.
- Network Programming: Used for manipulating IP addresses, subnet masks, and protocol flags.
- Graphics Programming:  Working with pixel colors, masking, and other graphical operations.
- Cryptography:  Used in encryption algorithms and hash functions.
- Data Compression:  Bitwise operations can be used to efficiently pack and unpack data.
- Game Development:  Used for collision detection, setting game states, and optimizing performance.
*/
