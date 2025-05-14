import java.util.*;
import java.io.*;

public class BitManipulationExamples {

    public static void main(String[] args) {
        // 1. Checking if a number is a power of 2
        System.out.println("1. Checking if a number is a power of 2:");
        int num1 = 16;
        int num2 = 25;
        System.out.println(num1 + " is a power of 2: " + isPowerOfTwo(num1)); // true
        System.out.println(num2 + " is a power of 2: " + isPowerOfTwo(num2)); // false

        // 2. Counting set bits in an integer
        System.out.println("\n2. Counting set bits in an integer:");
        int num3 = 13; // Binary: 1101, Set bits: 3
        System.out.println("Set bits in " + num3 + ": " + countSetBits(num3)); // 3

        // 3. Setting a specific bit in a number
        System.out.println("\n3. Setting a specific bit in a number:");
        int num4 = 10; // Binary: 1010
        int positionToSet = 1; // Set the bit at index 1 (from right, 0-indexed)
        System.out.println("Number after setting bit at position " + positionToSet + " in " + num4 + ": " + setBit(num4, positionToSet)); // 11 (Binary: 1011)

        // 4. Clearing a specific bit in a number
        System.out.println("\n4. Clearing a specific bit in a number:");
        int num5 = 11; // Binary: 1011
        int positionToClear = 1; // Clear the bit at index 1 (from right, 0-indexed)
        System.out.println("Number after clearing bit at position " + positionToClear + " in " + num5 + ": " + clearBit(num5, positionToClear)); // 9 (Binary: 1001)

        // 5. Toggling a specific bit in a number
        System.out.println("\n5. Toggling a specific bit in a number:");
        int num6 = 10; // Binary: 1010
        int positionToToggle = 2;
        System.out.println("Number after toggling bit at position " + positionToToggle + " in " + num6 + ": " + toggleBit(num6, positionToToggle)); // 14 (Binary 1110)

        // 6. Checking if the number is even or odd
        System.out.println("\n6. Checking if the number is even or odd:");
        int num7 = 7;
        int num8 = 12;
        System.out.println(num7 + " is odd: " + isOdd(num7));
        System.out.println(num8 + " is odd: " + isOdd(num8));

        // 7. Find the unique number in an array where every number occurs twice
        System.out.println("\n7. Find the unique number in an array where every number occurs twice:");
        int[] arr1 = {2, 3, 4, 2, 4};
        System.out.println("Unique number in arr1: " + findUniqueNumber(arr1)); // Output: 3

        // 8. Calculate the number of bits needed to flip to convert one number to another
        System.out.println("\n8. Calculate the number of bits needed to flip to convert one number to another:");
        int a = 10; // Binary: 1010
        int b = 7;  // Binary: 0111
        System.out.println("Bits to flip from " + a + " to " + b + ": " + bitsToFlip(a, b)); // Output: 2

        // 9.  Find two non-repeating numbers in an array where every other number repeats twice
        System.out.println("\n9. Find two non-repeating numbers in an array where every other number repeats twice:");
        int[] arr2 = {1, 2, 3, 1, 2, 4};
        int[] uniqueNumbers = findTwoUniqueNumbers(arr2);
        System.out.println("Two unique numbers are: " + uniqueNumbers[0] + " and " + uniqueNumbers[1]); // Output: 3 and 4

        // 10. Check if the given number is power of 2 using Brian Kernighan’s Algorithm
        System.out.println("\n10. Check if the given number is power of 2 using Brian Kernighan’s Algorithm:");
        int n1 = 8;
        int n2 = 10;
        System.out.println(n1 + " is a power of 2: " + isPowerOfTwoBrianKernighan(n1));
        System.out.println(n2 + " is a power of 2: " + isPowerOfTwoBrianKernighan(n2));
    }

    // 1. Function to check if a number is a power of 2 using bit manipulation
    // A number n is a power of 2 if and only if n is positive and n & (n-1) is 0.
    public static boolean isPowerOfTwo(int n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    }

    // 2. Function to count the number of set bits (1s) in an integer using bit manipulation
    // Uses the Brian Kernighan's algorithm to clear the least significant set bit in each iteration.
    public static int countSetBits(int n) {
        int count = 0;
        while (n != 0) {
            n &= (n - 1); // Clear the least significant set bit
            count++;
        }
        return count;
    }

    // 3. Function to set a specific bit (make it 1) in a number using bit manipulation
    // Creates a mask with a 1 at the desired position and performs a bitwise OR operation.
    public static int setBit(int n, int position) {
        int mask = 1 << position;
        return n | mask;
    }

    // 4. Function to clear a specific bit (make it 0) in a number using bit manipulation
    // Creates a mask with a 0 at the desired position and performs a bitwise AND operation.
    public static int clearBit(int n, int position) {
        int mask = ~(1 << position); // Create a mask with 0 at 'position' and 1 elsewhere.
        return n & mask;
    }

    // 5. Function to toggle (flip) a specific bit in a number using bit manipulation
    // Creates a mask with a 1 at the desired position and performs a bitwise XOR operation.
    public static int toggleBit(int n, int position) {
        int mask = 1 << position;
        return n ^ mask;
    }

    // 6. Function to check if a number is odd using bit manipulation
    public static boolean isOdd(int n) {
        return (n & 1) == 1; // Check if the least significant bit is 1
    }

    // 7. Function to find the unique number in an array where every number occurs twice
    public static int findUniqueNumber(int[] arr) {
        int result = 0;
        for (int num : arr) {
            result ^= num; // XORing a number with itself results in 0, unique number remains.
        }
        return result;
    }

    // 8. Function to calculate the number of bits needed to flip to convert one number to another
    public static int bitsToFlip(int a, int b) {
        int xorResult = a ^ b; // XOR gives 1 for differing bits and 0 for same bits
        return countSetBits(xorResult); // Count the set bits in the XOR result
    }

    // 9. Function to find two non-repeating numbers in an array where every other number repeats twice
    public static int[] findTwoUniqueNumbers(int[] arr) {
        int xorSum = 0;
        for (int num : arr) {
            xorSum ^= num;
        }

        // Find the rightmost set bit in xorSum
        int rightmostSetBit = xorSum & -xorSum;

        int num1 = 0;
        int num2 = 0;

        for (int num : arr) {
            if ((num & rightmostSetBit) == 0) {
                num1 ^= num;
            } else {
                num2 ^= num;
            }
        }

        return new int[]{num1, num2};
    }

    // 10. Function to check if a number is a power of 2 using Brian Kernighan’s Algorithm
    public static boolean isPowerOfTwoBrianKernighan(int n) {
        if (n <= 0) {
            return false;
        }
        return (n & (n - 1)) == 0;
    }
}

/*
Explanation:

1. Checking if a number is a power of 2:
   - Uses the property that a power of 2 has only one bit set (e.g., 16 = 10000).
   - n & (n-1) clears the least significant bit. For powers of 2, this result is 0.

2. Counting set bits in an integer:
   - Brian Kernighan's Algorithm:  Repeatedly clears the least significant set bit until the number becomes 0.
   - The loop count equals the number of set bits.

3. Setting a specific bit in a number:
   - Creates a mask with '1' at the position to set.
   - Uses bitwise OR (|) to set the bit without affecting others.

4. Clearing a specific bit in a number:
   - Creates a mask with '0' at the position to clear (using complement ~).
   - Uses bitwise AND (&) to clear the bit.

5. Toggling a specific bit in a number:
   - Creates a mask with '1' at the position to toggle.
   - Uses bitwise XOR (^) to flip the bit (0 becomes 1, 1 becomes 0).

6. Checking if the number is even or odd:
   - Checks the least significant bit. If it's 1, the number is odd.

7. Find the unique number in an array where every number occurs twice:
   - Uses XOR. XORing a number with itself results in 0. The unique number remains after XORing all elements.

8. Calculate the number of bits needed to flip to convert one number to another:
   - XOR the two numbers. The set bits in the result represent the differing bits.
   - Count the set bits.

9. Find two non-repeating numbers in an array where every other number repeats twice:
   - XOR all numbers. The result is the XOR of the two unique numbers.
   - Find the rightmost set bit in the XOR result. This bit is different between the two unique numbers.
   - Divide the array into two groups based on whether this bit is set.
   - XOR the numbers in each group to get the two unique numbers.

10. Check if the given number is power of 2 using Brian Kernighan’s Algorithm:
    - It checks if the number is greater than 0 and if n & (n-1) is 0.
*/
