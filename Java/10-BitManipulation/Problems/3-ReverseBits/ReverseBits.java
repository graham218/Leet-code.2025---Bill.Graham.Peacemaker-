public class ReverseBits {

    /**
     * **Approach 1: Iterative Bitwise Swap**
     *
     * This method iterates through the 32 bits of the integer. In each iteration,
     * it swaps the i-th bit from the left with the (31-i)-th bit from the right.
     * It uses bitwise AND to check if a bit is set, and bitwise OR to set a bit
     * in the result.  It's generally efficient as it only iterates 16 times.
     *
     * @param n The integer whose bits are to be reversed
     * @return The integer with reversed bits
     */
    public int reverseBits1(int n) {
        int result = 0;
        for (int i = 0; i < 16; i++) {
            // Get the i-th bit from the right
            int rightBit = (n >> i) & 1;
            // Get the i-th bit from the left
            int leftBit = (n >> (31 - i)) & 1;

            // Set the i-th bit from the right in the result
            result |= (leftBit << i);
            // Set the i-th bit from the left in the result
            result |= (rightBit << (31 - i));
        }
        return result;
    }

    /**
     * **Approach 2: Bitwise Operations and Shifting**
     *
     * This approach is optimized for speed.  It processes the bits one by one,
     * taking the least significant bit of the input, and placing it in the
     * most significant bit of the result.  It shifts the result to the left
     * and the input to the right in each step.
     *
     * @param n The integer to reverse
     * @return The reversed integer
     */
    public int reverseBits2(int n) {
        int result = 0;
        for (int i = 0; i < 32; i++) {
            // Get the rightmost bit of n
            int rightBit = n & 1;
            // Shift the current result to the left, making space for the new bit.
            result <<= 1;
            // Place the rightmost bit of n into the least significant bit of result
            result |= rightBit;
            // Discard the rightmost bit of n
            n >>>= 1; // Use unsigned right shift to avoid sign extension
        }
        return result;
    }

    /**
     * **Approach 3: Using Integer.reverse()**
     *
     * This is the simplest and most efficient approach in Java.  The
     * `Integer.reverse()` method is a built-in function that does exactly
     * what we need.  It's highly optimized at the JVM level.
     *
     * @param n The integer to reverse
     * @return The reversed integer
     */
    public int reverseBits3(int n) {
        return Integer.reverse(n);
    }

    /**
     * **Approach 4:  Lookup Table (for repeated calls)**
     *
     * If the reverseBits function is called many times, a lookup table can
     * improve performance.  This approach pre-computes the reversed values
     * for all possible byte values (0-255) and stores them in an array.  Then,
     * the input integer is processed byte by byte, and the reversed value for
     * each byte is retrieved from the table.  This trades space for time.
     *
     * @param n The integer to reverse
     * @return The reversed integer
     */
    private static final int[] reverseTable = new int[256];

    // Static initializer to pre-compute the reversed bits for each byte
    static {
        for (int i = 0; i < 256; i++) {
            reverseTable[i] = reverseByte(i);
        }
    }

    private static int reverseByte(int b) {
        int result = 0;
        for (int i = 0; i < 8; i++) {
            result |= ((b >> i) & 1) << (7 - i);
        }
        return result;
    }

    public int reverseBits4(int n) {
        int result = 0;
        // Process the integer in 4 bytes.
        result |= reverseTable[(n & 0xFF)] << 24;
        result |= reverseTable[((n >> 8) & 0xFF)] << 16;
        result |= reverseTable[((n >> 16) & 0xFF)] << 8;
        result |= reverseTable[((n >> 24) & 0xFF)];
        return result;
    }

    /**
     * **Approach 5: Divide and Conquer**
     *
     * This approach uses a divide-and-conquer strategy to reverse the bits. It performs a series of bitwise swaps
     * to reverse the bits in pairs, then groups of 4, then groups of 8, 16
     * @param n the integer to be reversed
     * @return the reversed integer
     */
    public int reverseBits5(int n) {
        // Swap adjacent bits
        n = (n & 0x55555555) << 1 | (n >>> 1) & 0x55555555;
        // Swap pairs of bits
        n = (n & 0x33333333) << 2 | (n >>> 2) & 0x33333333;
        // Swap groups of 4 bits
        n = (n & 0x0F0F0F0F) << 4 | (n >>> 4) & 0x0F0F0F0F;
        // Swap groups of 8 bits
        n = (n & 0x00FF00FF) << 8 | (n >>> 8) & 0x00FF00FF;
        // Swap groups of 16 bits
        n = (n << 16) | (n >>> 16);
        return n;
    }

    public static void main(String[] args) {
        ReverseBits solution = new ReverseBits();
        int num = 43261596; // Example input

        System.out.println("Original Number: " + num);
        System.out.println("Reversed Bits (Approach 1): " + solution.reverseBits1(num));
        System.out.println("Reversed Bits (Approach 2): " + solution.reverseBits2(num));
        System.out.println("Reversed Bits (Approach 3): " + solution.reverseBits3(num));
        System.out.println("Reversed Bits (Approach 4): " + solution.reverseBits4(num));
        System.out.println("Reversed Bits (Approach 5): " + solution.reverseBits5(num));
    }
}
