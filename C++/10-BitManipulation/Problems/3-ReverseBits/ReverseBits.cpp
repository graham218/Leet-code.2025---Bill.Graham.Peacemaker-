/*
Bit Manipulation: Reverse Bits

Given an unsigned 32-bit integer n, return its bitwise reversed version.

Example 1:
Input: n = 00000010100101000001111010011100
Output:    11001011110000010010100101000000

Example 2:
Input: n = 11111110000000000000000000000001
Output:    10000000000000000000000001111111

Constraints:
The input integer n is guaranteed to be a positive integer represented using 32 bits.
*/

/**
 * Approach 1: Iterative Bit Manipulation
 * - Iterate through the bits of the input integer.
 * - Extract the least significant bit (LSB).
 * - Shift the reversed integer to the left and add the extracted LSB.
 * - Shift the input integer to the right.
 *
 * @param {number} n - The unsigned 32-bit integer to reverse.
 * @return {number} - The bitwise reversed integer.
 */
const reverseBits1 = (n) => {
  let reversed = 0;
  for (let i = 0; i < 32; i++) {
    // Get the rightmost bit of n
    const bit = (n >> i) & 1;
    // Shift the reversed number to the left by 1 and add the bit
    reversed = (reversed << 1) | bit;
  }
  return reversed >>> 0; // Use >>> to ensure unsigned 32-bit integer
};

/**
 * Approach 2: Using String Conversion
 * - Convert the integer to its 32-bit binary string representation.
 * - Reverse the string.
 * - Parse the reversed string as an unsigned 32-bit integer.
 *
 * @param {number} n - The unsigned 32-bit integer to reverse.
 * @return {number} - The bitwise reversed integer.
 */
const reverseBits2 = (n) => {
  let binaryString = n.toString(2).padStart(32, '0'); // Pad with 0s to ensure 32 bits
  const reversedString = binaryString.split('').reverse().join('');
  return parseInt(reversedString, 2) >>> 0;
};

/**
 * Approach 3: Bit Manipulation with Masking
 * - Iterate through the first 16 bits.
 * - Swap the i-th bit with the (31-i)-th bit.
 *
 * @param {number} n - The unsigned 32-bit integer to reverse.
 * @return {number} - The bitwise reversed integer.
 */
const reverseBits3 = (n) => {
    for (let i = 0; i < 16; i++) {
        // Get the i-th bit
        const bitI = (n >> i) & 1;
        // Get the (31-i)-th bit
        const bitJ = (n >> (31 - i)) & 1;

        // If the bits are different, swap them
        if (bitI !== bitJ) {
            // Clear the i-th and (31-i)-th bits
            n = n & ~(1 << i);
            n = n & ~(1 << (31 - i));
            // Set the i-th bit to bitJ and the (31-i)-th bit to bitI
            n = n | (bitJ << i);
            n = n | (bitI << (31 - i));
        }
    }
    return n >>> 0;
};

/**
 * Approach 4: Optimized Bit Manipulation
 * Uses a divide and conquer approach to minimize operations.
 *
 * @param {number} n - The unsigned 32-bit integer to reverse.
 * @return {number} - The bitwise reversed integer.
 */
const reverseBits4 = (n) => {
    n = (n >>> 0); // Ensure n is treated as unsigned

    // Step 1: Reverse each byte
    n = ((n & 0x000000FF) << 24) |
        ((n & 0x0000FF00) << 8)  |
        ((n & 0x00FF0000) >>> 8) |
        ((n & 0xFF000000) >>> 24);

    // Step 2: Swap bits within each byte
    n = ((n & 0x00000F0F) << 12) | ((n & 0x0000F0F0) >>> 12) |
        ((n & 0x00F000F0) << 4)  | ((n & 0x000F000F) >>> 4)  |
        ((n & 0x0A0A0A0A) << 2)  | ((n & 0x05050505) >>> 2);

    return n >>> 0;
};


/**
 * Approach 5: Using a Lookup Table
 * - Create a lookup table to store the reversed values of all possible bytes (0-255).
 * - Split the input integer into bytes.
 * - Use the lookup table to get the reversed value of each byte.
 * - Combine the reversed bytes to get the final reversed integer.
 *
 * @param {number} n - The unsigned 32-bit integer to reverse.
 * @return {number} - The bitwise reversed integer.
 */
const reverseBits5 = (n) => {
    const reversedByte = new Array(256);
    // Precompute reversed bytes
    for (let i = 0; i < 256; i++) {
        let reversed = 0;
        for (let j = 0; j < 8; j++) {
            reversed = (reversed << 1) | ((i >> j) & 1);
        }
        reversedByte[i] = reversed;
    }

    // Split the integer into 4 bytes
    const byte1 = (n >>> 24) & 0xFF;
    const byte2 = (n >>> 16) & 0xFF;
    const byte3 = (n >>> 8) & 0xFF;
    const byte4 = n & 0xFF;

    // Use the lookup table to reverse each byte and combine them
    return (reversedByte[byte4] << 24) |
           (reversedByte[byte3] << 16) |
           (reversedByte[byte2] << 8)  |
           reversedByte[byte1];
};

// Example usage and output
const n = 43261596; // 00000010100101000001111010011100
console.log(`Input: ${n.toString(2).padStart(32, '0')}`); // 00000010100101000001111010011100

console.log("Approach 1: Iterative Bit Manipulation");
const reversed1 = reverseBits1(n);
console.log(`Reversed (Decimal): ${reversed1}`);
console.log(`Reversed (Binary): ${reversed1.toString(2).padStart(32, '0')}`); // 11001011110000010010100101000000

console.log("\nApproach 2: Using String Conversion");
const reversed2 = reverseBits2(n);
console.log(`Reversed (Decimal): ${reversed2}`);
console.log(`Reversed (Binary): ${reversed2.toString(2).padStart(32, '0')}`); // 11001011110000010010100101000000

console.log("\nApproach 3: Bit Manipulation with Masking");
const reversed3 = reverseBits3(n);
console.log(`Reversed (Decimal): ${reversed3}`);
console.log(`Reversed (Binary): ${reversed3.toString(2).padStart(32, '0')}`); // 11001011110000010010100101000000

console.log("\nApproach 4: Optimized Bit Manipulation");
const reversed4 = reverseBits4(n);
console.log(`Reversed (Decimal): ${reversed4}`);
console.log(`Reversed (Binary): ${reversed4.toString(2).padStart(32, '0')}`); // 11001011110000010010100101000000

console.log("\nApproach 5: Using a Lookup Table");
const reversed5 = reverseBits5(n);
console.log(`Reversed (Decimal): ${reversed5}`);
console.log(`Reversed (Binary): ${reversed5.toString(2).padStart(32, '0')}`); // 11001011110000010010100101000000
