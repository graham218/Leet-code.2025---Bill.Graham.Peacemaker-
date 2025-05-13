public class NumberOf1Bits {

    /**
     * **Approach 1: Iterating through bits and checking each one**
     *
     * This is the most straightforward approach.  We iterate through the 32 bits of the integer `n`.
     * In each iteration, we check if the least significant bit is 1 by using the bitwise AND operator `&` with 1.
     * If it's 1, we increment our count. Then, we right-shift `n` by 1 bit to check the next bit.
     *
     * **Time Complexity:** O(32), which is effectively O(1) since we're dealing with a 32-bit integer.
     * **Space Complexity:** O(1), as we only use a constant amount of extra space.
     *
     * @param n The integer whose 1 bits we want to count
     * @return The number of 1 bits in n
     */
    public int hammingWeightApproach1(int n) {
        int count = 0;
        for (int i = 0; i < 32; i++) {
            if ((n & 1) == 1) {
                count++;
            }
            n >>>= 1; // Use unsigned right shift to avoid issues with negative numbers
        }
        return count;
    }

    /**
     * **Approach 2: Optimized Iteration using n & (n - 1)**
     *
     * This approach is more efficient than the first one. The key idea is that the expression `n & (n - 1)`
     * clears the least significant 1 bit of `n`.  For example:
     * n = 10110 (binary)
     * n - 1 = 10101 (binary)
     * n & (n - 1) = 10100 (binary)
     *
     * We repeat this process until `n` becomes 0. In each step, we increment the count, effectively counting
     * the number of 1 bits. This approach avoids unnecessary iterations for leading zeros.
     *
     * **Time Complexity:** O(k), where k is the number of 1 bits in n.  This is better than O(32) if n has few 1s.
     * **Space Complexity:** O(1), as we use only a constant amount of extra space.
     *
     * @param n The integer
     * @return The number of 1 bits in n
     */
    public int hammingWeightApproach2(int n) {
        int count = 0;
        while (n != 0) {
            n &= (n - 1);
            count++;
        }
        return count;
    }

    /**
     * **Approach 3: Using the built-in Integer.bitCount() method**
     *
     * Java provides a built-in method `Integer.bitCount(n)` that directly returns the number of 1 bits
     * in an integer. This is the most concise and often the most efficient way to achieve this.
     * It's generally implemented using optimized native code.
     *
     * **Time Complexity:** O(1) in practice, as it's a highly optimized native implementation.
     * **Space Complexity:** O(1)
     *
     * @param n The integer
     * @return The number of 1 bits in n
     */
    public int hammingWeightApproach3(int n) {
        return Integer.bitCount(n);
    }

    /**
     * **Approach 4: Bitwise AND with a mask, similar to approach 1, but slightly different order**
     * This approach uses a mask that starts at 1 and is left shifted.
     * @param n The integer
     * @return The number of 1 bits
     */
    public int hammingWeightApproach4(int n) {
        int count = 0;
        int mask = 1;
        for (int i = 0; i < 32; i++) {
            if ((n & mask) != 0) {
                count++;
            }
            mask <<= 1;
        }
        return count;
    }

    /**
     * **Approach 5: Using String conversion (Less Efficient, for demonstration)**
     *
     * This approach converts the integer to its binary string representation and then counts the number of '1' characters.
     * While this works, it's generally less efficient than the bitwise operations in the other approaches,
     * especially for large integers, due to the overhead of string conversion.  It's included here primarily for
     * illustrative purposes, to show a different way of thinking about the problem.
     *
     * **Time Complexity:** O(log n), where n is the integer.  Converting to a binary string takes logarithmic time.
     * **Space Complexity:** O(log n), to store the binary string.
     *
     * @param n The integer
     * @return The number of 1 bits in n
     */
    public int hammingWeightApproach5(int n) {
        String binaryString = Integer.toBinaryString(n);
        int count = 0;
        for (char c : binaryString.toCharArray()) {
            if (c == '1') {
                count++;
            }
        }
        return count;
    }

    public static void main(String[] args) {
        NumberOf1Bits solution = new NumberOf1Bits();

        // Test cases
        int n1 = 11; // Binary: 1011
        int n2 = 0;
        int n3 = -1; // All bits are 1 in two's complement representation
        int n4 = 2147483647; //Max positive 32 bit int
        int n5 = -2147483648; //Min negative 32 bit int

        System.out.println("Number of 1 bits in " + n1 + ":");
        System.out.println("Approach 1: " + solution.hammingWeightApproach1(n1));
        System.out.println("Approach 2: " + solution.hammingWeightApproach2(n1));
        System.out.println("Approach 3: " + solution.hammingWeightApproach3(n1));
        System.out.println("Approach 4: " + solution.hammingWeightApproach4(n1));
        System.out.println("Approach 5: " + solution.hammingWeightApproach5(n1));
        System.out.println();

        System.out.println("Number of 1 bits in " + n2 + ":");
        System.out.println("Approach 1: " + solution.hammingWeightApproach1(n2));
        System.out.println("Approach 2: " + solution.hammingWeightApproach2(n2));
        System.out.println("Approach 3: " + solution.hammingWeightApproach3(n2));
        System.out.println("Approach 4: " + solution.hammingWeightApproach4(n2));
        System.out.println("Approach 5: " + solution.hammingWeightApproach5(n2));
        System.out.println();

        System.out.println("Number of 1 bits in " + n3 + ":");
        System.out.println("Approach 1: " + solution.hammingWeightApproach1(n3));
        System.out.println("Approach 2: " + solution.hammingWeightApproach2(n3));
        System.out.println("Approach 3: " + solution.hammingWeightApproach3(n3));
        System.out.println("Approach 4: " + solution.hammingWeightApproach4(n3));
        System.out.println("Approach 5: " + solution.hammingWeightApproach5(n3));
        System.out.println();

        System.out.println("Number of 1 bits in " + n4 + ":");
        System.out.println("Approach 1: " + solution.hammingWeightApproach1(n4));
        System.out.println("Approach 2: " + solution.hammingWeightApproach2(n4));
        System.out.println("Approach 3: " + solution.hammingWeightApproach3(n4));
        System.out.println("Approach 4: " + solution.hammingWeightApproach4(n4));
        System.out.println("Approach 5: " + solution.hammingWeightApproach5(n4));
        System.out.println();

        System.out.println("Number of 1 bits in " + n5 + ":");
        System.out.println("Approach 1: " + solution.hammingWeightApproach1(n5));
        System.out.println("Approach 2: " + solution.hammingWeightApproach2(n5));
        System.out.println("Approach 3: " + solution.hammingWeightApproach3(n5));
        System.out.println("Approach 4: " + solution.hammingWeightApproach4(n5));
        System.out.println("Approach 5: " + solution.hammingWeightApproach5(n5));
        System.out.println();
    }
}
