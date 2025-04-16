/*
Bit Manipulation: Reverse Bits

Given a 32-bit unsigned integer, reverse its bits.

For example, if you are given the number 13 (00000000000000000000000000001101 in binary),
return 2147483648 (10000000000000000000000000000000 in binary).

Different Approaches:

1.  **Iterative Approach:**
    * Iterate through the bits of the input number.
    * Extract the least significant bit.
    * Shift the result to the left and add the extracted bit.
    * Shift the input number to the right.

2.  **Using String Manipulation:**
    * Convert the number to its binary string representation.
    * Pad the string with leading zeros to ensure it has 32 bits.
    * Reverse the string.
    * Convert the reversed string back to an unsigned integer.

3.  **Bitwise Swap Approach:**
    * Use a loop to swap the bits at the opposite ends of the number.
    * This approach minimizes the number of operations.

4.  **Lookup Table Approach:**
     * Create a lookup table to store the reversed values of all possible 8-bit sequences.
     * Split the 32-bit integer into 4 bytes.
     * Use the lookup table to reverse each byte, and then combine the reversed bytes.
     * This approach is faster, especially for multiple reversals.

5.  **Optimized Bitwise Swap:**
    * Similar to bitwise swap, but optimized for performance.
    * Uses a divide-and-conquer strategy to minimize swaps.

*/

/**
 * Reverses the bits of a 32-bit unsigned integer using iterative approach.
 *
 * @param {number} n - The 32-bit unsigned integer to reverse.
 * @returns {number} The integer with reversed bits.
 */
function reverseBitsIterative(n) {
    let result = 0;
    for (let i = 0; i < 32; i++) {
        // Get the least significant bit of n
        const lsb = n & 1;
        // Shift the result to the left, making space for the new bit
        result <<= 1;
        // Set the least significant bit of result to the extracted lsb
        result |= lsb;
        // Shift n to the right, discarding the least significant bit
        n >>>= 1;
    }
    return result >>> 0; // Ensure unsigned 32-bit integer
}

/**
 * Reverses the bits of a 32-bit unsigned integer using string manipulation.
 *
 * @param {number} n - The 32-bit unsigned integer to reverse.
 * @returns {number} The integer with reversed bits.
 */
function reverseBitsString(n) {
    let binaryString = (n >>> 0).toString(2); // Convert to unsigned binary string
    binaryString = binaryString.padStart(32, '0'); // Pad with zeros to 32 bits
    const reversedString = binaryString.split('').reverse().join(''); // Reverse the string
    return parseInt(reversedString, 2) >>> 0; // Convert back to unsigned integer
}

/**
 * Reverses the bits of a 32-bit unsigned integer using bitwise swap.
 *
 * @param {number} n - The 32-bit unsigned integer to reverse.
 * @returns {number} The integer with reversed bits.
 */
function reverseBitsBitwiseSwap(n) {
    for (let i = 0; i < 16; i++) {
        // Get the i-th bit from the left
        const leftBit = (n >>> i) & 1;
        // Get the i-th bit from the right
        const rightBit = (n >>> (31 - i)) & 1;

        // If the bits are different, swap them
        if (leftBit !== rightBit) {
            // Clear the i-th bit from the left and right
            n = n & ~(1 << i);
            n = n & ~(1 << (31 - i));

            // Set the i-th bit from the left and right to the correct value.
            n = n | (rightBit << i);
            n = n | (leftBit << (31 - i));
        }
    }
    return n >>> 0;
}

/**
 * Reverses the bits of a 32-bit unsigned integer using lookup table.
 *
 * @param {number} n - The 32-bit unsigned integer to reverse.
 * @returns {number} The integer with reversed bits.
 */
function reverseBitsLookupTable(n) {
    const lookupTable = new Array(256);
    // Pre-compute the reversed bits for each byte (0-255)
    for (let i = 0; i < 256; i++) {
        let reversedByte = 0;
        for (let j = 0; j < 8; j++) {
            reversedByte |= ((i >>> j) & 1) << (7 - j);
        }
        lookupTable[i] = reversedByte;
    }

    // Split the 32-bit integer into 4 bytes
    const byte1 = (n >>> 24) & 0xFF;
    const byte2 = (n >>> 16) & 0xFF;
    const byte3 = (n >>> 8) & 0xFF;
    const byte4 = n & 0xFF;

    // Use the lookup table to reverse each byte and combine
    return (
        (lookupTable[byte4] << 24) |
        (lookupTable[byte3] << 16) |
        (lookupTable[byte2] << 8) |
        lookupTable[byte1]
    ) >>> 0;
}

/**
 * Reverses the bits of a 32-bit unsigned integer using optimized bitwise swap.
 *
 * @param {number} n - The 32-bit unsigned integer to reverse.
 * @returns {number} The integer with reversed bits.
 */
function reverseBitsOptimized(n) {
      n = (n >>> 0); // convert to unsigned.
      n = ((n & 0x55555555) << 1) | ((n & 0xAAAAAAAA) >>> 1); // Swap odd and even bits
      n = ((n & 0x33333333) << 2) | ((n & 0xCCCCCCCC) >>> 2); // Swap consecutive pairs
      n = ((n & 0x0F0F0F0F) << 4) | ((n & 0xF0F0F0F0) >>> 4); // Swap nibbles
      n = ((n & 0x00FF00FF) << 8) | ((n & 0xFF00FF00) >>> 8); // Swap bytes
      n = ((n & 0x0000FFFF) << 16) | ((n & 0xFFFF0000) >>> 16); // Swap 16-bit halves
      return n >>> 0;
}

// Example Usage and output using console.log
const num = 43261596; // Example input: 00000010100101000001111010011100
console.log(`Input: ${num}`);

// Iterative Approach
const reversedIterative = reverseBitsIterative(num);
console.log(`Reversed (Iterative): ${reversedIterative} (Binary: ${reversedIterative.toString(2).padStart(32, '0')})`);

// String Manipulation Approach
const reversedString = reverseBitsString(num);
console.log(`Reversed (String): ${reversedString} (Binary: ${reversedString.toString(2).padStart(32, '0')})`);

// Bitwise Swap Approach
const reversedBitwiseSwap = reverseBitsBitwiseSwap(num);
console.log(`Reversed (Bitwise Swap): ${reversedBitwiseSwap} (Binary: ${reversedBitwiseSwap.toString(2).padStart(32, '0')})`);

// Lookup Table Approach
const reversedLookupTable = reverseBitsLookupTable(num);
console.log(`Reversed (Lookup Table): ${reversedLookupTable} (Binary: ${reversedLookupTable.toString(2).padStart(32, '0')})`);

// Optimized Bitwise Swap Approach
const reversedOptimized = reverseBitsOptimized(num);
console.log(`Reversed (Optimized): ${reversedOptimized} (Binary: ${reversedOptimized.toString(2).padStart(32, '0')})`);
