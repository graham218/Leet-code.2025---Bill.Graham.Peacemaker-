import java.util.HashMap;
import java.util.Map;

public class ReverseBits {

    /**
     * **Approach 1: Iterative Bitwise Swap**
     *
     * * **Concept:** Iterates through the bits of the number, swapping the leftmost bit with the rightmost bit, the second leftmost with the second rightmost, and so on.
     * * **Real-world application:** This is a fundamental bit manipulation technique.  It's often used in low-level systems programming, such as:
     * * **Network protocols:** Reversing bit order for specific data formats.
     * * **Cryptographic algorithms:** Some encryption/decryption algorithms involve bit reversal.
     * * **Image processing:** Certain image transformations might require reversing the bit representation of pixel data.
     * * **Time Complexity:** O(log n), where n is the number.  In practice, O(32) for a 32-bit integer.
     * **Space Complexity:** O(1) - constant space.
     */
    public int reverseBitsIterative(int n) {
        int reversed = 0;
        for (int i = 0; i < 32; i++) {
            // Get the rightmost bit of n
            int rightBit = (n >> i) & 1;
            // Place the rightmost bit of n to the leftmost position of reversed
            reversed = reversed | (rightBit << (31 - i));
        }
        return reversed;
    }

    /**
     * **Approach 2: Using Built-in Integer.reverse()**
     *
     * * **Concept:** Utilizes the `Integer.reverse()` method provided by Java, which directly reverses the bits of an integer.
     * * **Real-world application:** This is the most straightforward and efficient way to reverse bits in Java.  It's suitable for any application where performance is critical and you need a quick, reliable way to reverse bits.  Examples:
     * * **General utility functions:** Part of a library or toolkit for bit manipulation.
     * * **Competitive programming:** Where speed and conciseness are highly valued.
     * * Any application where you want to avoid manual bit manipulation.
     * * **Time Complexity:** O(1) - constant time (highly optimized in the JVM).
     * * **Space Complexity:** O(1) - constant space.
     */
    public int reverseBitsBuiltin(int n) {
        return Integer.reverse(n);
    }

    /**
     * **Approach 3: Bit Manipulation with Divide and Conquer**
     *
     * * **Concept:** This approach uses a divide-and-conquer strategy to reverse the bits. It involves a series of bitwise operations to swap adjacent bits, then groups of 2 bits, then groups of 4, and so on.
     * * **Real-world application:** While `Integer.reverse()` is usually preferred, this approach demonstrates an interesting bit manipulation technique.  It can be adapted for:
     * * **Hardware implementations:** The bitwise operations can be efficiently implemented in hardware.
     * * **Optimized libraries:** This approach can be a basis for highly optimized bit reversal routines in specialized libraries.
     * * Understanding how bit reversal can be done very efficiently.
     * * **Time Complexity:** O(log n), where n is the number of bits. In practice, O(32)
     * * **Space Complexity:** O(1) - constant space.
     */
    public int reverseBitsDivideAndConquer(int n) {
        n = (n & 0x55555555) << 1 | (n & 0xAAAAAAAA) >>> 1; // Swap adjacent bits
        n = (n & 0x33333333) << 2 | (n & 0xCCCCCCCC) >>> 2; // Swap pairs of bits
        n = (n & 0x0F0F0F0F) << 4 | (n & 0xF0F0F0F0) >>> 4; // Swap groups of 4
        n = (n & 0x00FF00FF) << 8 | (n & 0xFF00FF00) >>> 8; // Swap groups of 8
        n = (n & 0x0000FFFF) << 16 | (n & 0xFFFF0000) >>> 16; // Swap groups of 16
        return n;
    }

    /**
     * **Approach 4: Using a Lookup Table**
     *
     * * **Concept:** Pre-computes the reversed values for all possible 8-bit combinations and stores them in a lookup table.  Then, it processes the input integer byte by byte, using the lookup table to reverse each byte.
     * * **Real-world application:** This approach is very efficient when you need to reverse bits many times, especially for large amounts of data.  It's used in:
     * * **High-performance networking:** Reversing bits in network packets.
     * * **Data processing:** Reversing bits in large data sets.
     * * Any situation where you can trade space for speed.
     * * **Time Complexity:** O(1) - constant time (4 table lookups for a 32-bit integer).
     * * **Space Complexity:** O(1) - constant space (256-entry table).
     */
    private static final int[] reverseTable = new int[256];

    static {
        // Initialize the lookup table
        for (int i = 0; i < 256; i++) {
            reverseTable[i] = reverseByte(i);
        }
    }

    private static int reverseByte(int b) {
        int reversed = 0;
        for (int i = 0; i < 8; i++) {
            reversed = reversed | ((b >> i) & 1) << (7 - i);
        }
        return reversed;
    }

    public int reverseBitsLookupTable(int n) {
        return (reverseTable[(n & 0xFF)] << 24)
                | (reverseTable[((n >> 8) & 0xFF)] << 16)
                | (reverseTable[((n >> 16) & 0xFF)] << 8)
                | (reverseTable[((n >> 24) & 0xFF)]);
    }

    /**
     * **Approach 5: Using HashMap for Caching**
     * * **Concept:** This approach uses a HashMap to cache the reversed bits of previously seen integers. If the reversed bits of an integer are already in the map, it returns the cached value, otherwise, it calculates the reversed bits and stores them in the map.
     * * **Real-world application:**
     * * This approach is useful when the input integer `n` has many repeated values.
     * * It can be used in scenarios where reversing bits is a common operation, and you want to optimize performance by avoiding redundant calculations.
     * * **Time Complexity:**
     * * Average case: O(1) -  for repeated integers, it's a constant time lookup.
     * * Worst case: O(log n) - for unique integers, the first call will take O(log n) to reverse.
     * * **Space Complexity:** O(k) - where k is the number of unique integers encountered.
     */
    private final Map<Integer, Integer> cache = new HashMap<>();

    public int reverseBitsWithCache(int n) {
        if (cache.containsKey(n)) {
            return cache.get(n);
        }
        int reversed = 0;
        for (int i = 0; i < 32; i++) {
            reversed |= ((n >> i) & 1) << (31 - i);
        }
        cache.put(n, reversed);
        return reversed;
    }

    public static void main(String[] args) {
        ReverseBits solution = new ReverseBits();

        int num = 43261596; // Example input

        System.out.println("Input: " + num);
        System.out.println("Iterative: " + solution.reverseBitsIterative(num));
        System.out.println("Built-in: " + solution.reverseBitsBuiltin(num));
        System.out.println("Divide and Conquer: " + solution.reverseBitsDivideAndConquer(num));
        System.out.println("Lookup Table: " + solution.reverseBitsLookupTable(num));
        System.out.println("HashMap Cache: " + solution.reverseBitsWithCache(num));

        // Example with repeated input to demonstrate caching
        System.out.println("\nTesting with repeated input:");
        int repeatedNum = 1024;
        System.out.println("Input: " + repeatedNum);
        System.out.println("HashMap Cache: " + solution.reverseBitsWithCache(repeatedNum)); // First call - calculate and cache
        System.out.println("HashMap Cache: " + solution.reverseBitsWithCache(repeatedNum)); // Second call - retrieve from cache
    }
}
