import java.util.ArrayList;
import java.util.List;

public class BitManipulation {

    public static void main(String[] args) {
        // Example Usage of the bit manipulation techniques
        int number = 7; // Binary: 111
        int position = 2; // 0-based index

        System.out.println("Original Number: " + number);

        // 1. Check if the bit is set
        System.out.println("1. Is bit set at position " + position + "?: " + isBitSet(number, position));

        // 2. Set the bit
        int numberAfterSettingBit = setBit(number, position);
        System.out.println("2. Number after setting bit " + position + ": " + numberAfterSettingBit + " (Binary: " + Integer.toBinaryString(numberAfterSettingBit) + ")");

        // 3. Clear the bit
        int numberAfterClearingBit = clearBit(number, position);
        System.out.println("3. Number after clearing bit " + position + ": " + numberAfterClearingBit + " (Binary: " + Integer.toBinaryString(numberAfterClearingBit) + ")");

        // 4. Toggle the bit
        int numberAfterTogglingBit = toggleBit(number, position);
        System.out.println("4. Number after toggling bit " + position + ": " + numberAfterTogglingBit + " (Binary: " + Integer.toBinaryString(numberAfterTogglingBit) + ")");

        // 5. Find the rightmost set bit
        int rightmostSetBit = findRightmostSetBit(number);
        System.out.println("5. Rightmost set bit of " + number + ": " + rightmostSetBit);

        // Example of generating all subsets using bitmasking
        int[] set = {1, 2, 3};
        System.out.println("\nSubsets of {1, 2, 3}:");
        List<List<Integer>> subsets = generateAllSubsets(set);
        for (List<Integer> subset : subsets) {
            System.out.println(subset);
        }

        // Example: Counting set bits using different methods
        int num = 10; // Binary 1010
        System.out.println("\nNumber of set bits in " + num + " (Binary: " + Integer.toBinaryString(num) + ")");
        System.out.println("Approach 1: Using Integer.bitCount(): " + countSetBitsUsingBitCount(num));
        System.out.println("Approach 2: Iterating through bits: " + countSetBitsIterative(num));
        System.out.println("Approach 3: Brian Kernighan's Algorithm: " + countSetBitsKernighan(num));
    }

    // 1. Check if the bit at a given position is set (1)
    //    - Uses the left shift operator (<<) and bitwise AND (&)
    //    - Time Complexity: O(1)
    //    - Space Complexity: O(1)
    public static boolean isBitSet(int number, int position) {
        // Create a mask with a 1 at the specified position.
        int mask = 1 << position;
        // Perform bitwise AND with the number. If the result is non-zero, the bit is set.
        return (number & mask) != 0;
    }

    // 2. Set the bit at a given position (change to 1)
    //    - Uses the left shift operator (<<) and bitwise OR (|)
    //    - Time Complexity: O(1)
    //    - Space Complexity: O(1)
    public static int setBit(int number, int position) {
        // Create a mask with a 1 at the specified position
        int mask = 1 << position;
        // Perform bitwise OR to set the bit.
        return number | mask;
    }

    // 3. Clear the bit at a given position (change to 0)
    //    - Uses the left shift operator (<<), bitwise NOT (~), and bitwise AND (&)
    //    - Time Complexity: O(1)
    //    - Space Complexity: O(1)
    public static int clearBit(int number, int position) {
        // Create a mask with a 1 at the specified position
        int mask = 1 << position;
        // Invert the mask using bitwise NOT.  Now the mask has a 0 at 'position'
        int invertedMask = ~mask;
        // Perform bitwise AND to clear the bit.
        return number & invertedMask;
    }

    // 4. Toggle the bit at a given position (change 0 to 1 and 1 to 0)
    //    - Uses the left shift operator (<<) and bitwise XOR (^)
    //    - Time Complexity: O(1)
    //    - Space Complexity: O(1)
    public static int toggleBit(int number, int position) {
        // Create a mask with a 1 at the specified position
        int mask = 1 << position;
        // Perform bitwise XOR to toggle the bit.
        return number ^ mask;
    }

    // 5. Find the position of the rightmost set bit
    //    - Uses a clever bit manipulation trick: number & -number
    //    - This isolates the rightmost set bit.  Then, find the log base 2
    //    - Time Complexity: O(1) - assuming Math.log2 is constant time
    //    - Space Complexity: O(1)
    public static int findRightmostSetBit(int number) {
        if (number == 0) {
            return -1; // Or throw an exception, depending on the desired behavior for 0
        }
        // Isolate the rightmost set bit
        int rightmostBit = number & -number;
        // Find the position (0-indexed) using log base 2.
        return (int) (Math.log(rightmostBit) / Math.log(2));
    }

    // 6. Generate all subsets of a set using bitmasking
    //    - Iterates through all possible bitmasks from 0 to 2^n - 1, where n is the size of the set.
    //    - Each bitmask represents a subset: if the j-th bit is set, the j-th element is included in the subset.
    //    - Time Complexity: O(n * 2^n), where n is the size of the input set.
    //    - Space Complexity: O(2^n), to store all the subsets.
    public static List<List<Integer>> generateAllSubsets(int[] set) {
        int n = set.length;
        List<List<Integer>> subsets = new ArrayList<>();

        // Iterate through all possible bitmasks (subsets)
        for (int i = 0; i < (1 << n); i++) {
            List<Integer> subset = new ArrayList<>();
            // Check each bit of the current mask
            for (int j = 0; j < n; j++) {
                // If the j-th bit is set, add the j-th element to the subset
                if ((i & (1 << j)) != 0) {
                    subset.add(set[j]);
                }
            }
            subsets.add(subset);
        }
        return subsets;
    }

    // 7. Count the number of set bits in an integer (Approach 1: Using Integer.bitCount())
    //    - Uses the built-in Integer.bitCount() method.
    //    - Time Complexity: O(1) in most implementations
    //    - Space Complexity: O(1)
    public static int countSetBitsUsingBitCount(int n) {
        return Integer.bitCount(n);
    }

    // 8. Count the number of set bits in an integer (Approach 2: Iterating through bits)
    //   - Right shifts the number until it becomes 0.
    //   - Checks the least significant bit in each iteration.
    //   - Time Complexity: O(log n), where n is the number.
    //   - Space Complexity: O(1)
    public static int countSetBitsIterative(int n) {
        int count = 0;
        while (n != 0) {
            if ((n & 1) == 1) {
                count++;
            }
            n >>>= 1; // Unsigned right shift (important for negative numbers)
        }
        return count;
    }

    // 9. Count the number of set bits in an integer (Approach 3: Brian Kernighan's Algorithm)
    //    - Efficiently clears the rightmost set bit in each iteration.
    //    - The loop continues until the number becomes 0.
    //    - Time Complexity: O(k), where k is the number of set bits in n.
    //    - Space Complexity: O(1)
    public static int countSetBitsKernighan(int n) {
        int count = 0;
        while (n != 0) {
            n &= (n - 1); // Clear the rightmost set bit
            count++;
        }
        return count;
    }
}

