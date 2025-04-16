/**
 * **Bit Manipulation: Number of 1 Bits**
 *
 * **Problem:**
 *
 * Write a JavaScript function to count the number of set bits (1s) in the binary representation of a given unsigned integer.  Provide at least 5 different approaches, explain their application with real-world project examples, and display the output of each approach using `console.log`.
 *
 * **Explanation and Approaches:**
 *
 * Here's a breakdown of several methods to count the number of 1 bits, along with explanations, real-world use cases, and example code:
 *
 * 1.  **Brian Kernighan's Algorithm (Clearing the Least Significant Bit):**
 * * **Concept:** This is the most efficient approach.  It works by repeatedly clearing the least significant set bit of the number until the number becomes 0.  In each iteration, it subtracts 1 from the number and performs a bitwise AND with the original number.  This operation clears the rightmost 1-bit.
 * * **Real-World Application:**
 * * **Embedded Systems:** Counting set bits is crucial in low-power systems for tasks like determining the number of active components, power consumption analysis, and optimizing resource allocation.  For example, in a microcontroller, you might count the number of active interrupt flags.
 * * **Example:**
 */
function countSetBitsKernighan(n) {
  let count = 0;
  while (n !== 0) {
    n &= (n - 1); // Clear the least significant bit
    count++;
  }
  return count;
}

/**
 * 2.  **Right Shift and Check (Iterative):**
 * * **Concept:** This method iteratively right-shifts the number by one position and checks the least significant bit in each iteration.  If the least significant bit is 1, it increments the count.
 * * **Real-World Application:**
 * * **Network Protocols:** Counting set bits is used in network protocols for calculating checksums, determining the number of active connections, or analyzing packet headers.  For instance, you might count the number of set bits in a status flag field.
 * * **Example:**
 */
function countSetBitsRightShift(n) {
  let count = 0;
  while (n !== 0) {
    if ((n & 1) === 1) { // Check if the last bit is 1
      count++;
    }
    n >>>= 1; // Unsigned right shift (important in JavaScript)
  }
  return count;
}

/**
 * 3.  **Using `toString(2)` and Counting:**
 * * **Concept:** This approach converts the number to its binary string representation and then counts the number of '1' characters in the string.
 * * **Real-World Application:**
 * * **Data Analysis:** In data analysis, you might use this to count occurrences of specific bit patterns in binary data, such as counting the number of active features in a bitmask representation.
 * * **Example:**
 */
function countSetBitsToString(n) {
  const binaryString = n.toString(2);
  let count = 0;
  for (let i = 0; i < binaryString.length; i++) {
    if (binaryString[i] === '1') {
      count++;
    }
  }
  return count;
}

/**
 * 4. **Lookup Table (for smaller numbers or repeated calls):**
 * * **Concept**: This method pre-computes the number of set bits for all possible values of a smaller range (e.g., for each byte).  Then, for a larger number, it breaks it down into smaller chunks and uses the lookup table to get the count for each chunk.  This is a space-time tradeoff: it uses more memory but is faster for repeated calculations.
 * * **Real-world application:**
 * * **Image Processing:** Counting set bits in pixel masks or feature descriptors.  For example, counting the number of 'on' pixels in a binary image segment.
 * * **Example:**
 */
const BYTE_LOOKUP = [];
for (let i = 0; i < 256; i++) {
  let count = 0;
  let num = i;
  while (num > 0) {
    count += (num & 1);
    num >>>= 1;
  }
  BYTE_LOOKUP[i] = count;
}

function countSetBitsLookupTable(n) {
  let count = 0;
  count += BYTE_LOOKUP[n & 0xFF];
  count += BYTE_LOOKUP[(n >>> 8) & 0xFF];
  count += BYTE_LOOKUP[(n >>> 16) & 0xFF];
  count += BYTE_LOOKUP[(n >>> 24) & 0xFF];
  return count;
}

/**
 * 5. **Using Reduce with Binary Conversion**
 * * **Concept**: This method converts the number to its binary representation, splits the string into an array of characters, and then uses the `reduce` method to sum up the '1's.
 * * **Real-world application:**
 * * **Data Serialization/Deserialization**: When working with binary data formats, you might need to count set bits to validate data integrity or determine the size of certain fields.
 * * **Example:**
 */
function countSetBitsReduce(n) {
  return n.toString(2).split('').reduce((count, bit) => count + parseInt(bit, 10), 0);
}
// Example Usage and Output:
const number = 255; // Example number (11111111 in binary)

console.log(`Number: ${number}`);
console.log(`Kernighan's Algorithm: ${countSetBitsKernighan(number)}`);        // Output: 8
console.log(`Right Shift and Check: ${countSetBitsRightShift(number)}`);      // Output: 8
console.log(`toString(2) and Counting: ${countSetBitsToString(number)}`);    // Output: 8
console.log(`Lookup Table: ${countSetBitsLookupTable(number)}`);            // Output: 8
console.log(`Reduce with Binary Conversion: ${countSetBitsReduce(number)}`); // Output: 8

const number2 = 10; // Example number (1010 in binary)
console.log(`\nNumber: ${number2}`);
console.log(`Kernighan's Algorithm: ${countSetBitsKernighan(number2)}`);
console.log(`Right Shift and Check: ${countSetBitsRightShift(number2)}`);
console.log(`toString(2) and Counting: ${countSetBitsToString(number2)}`);
console.log(`Lookup Table: ${countSetBitsLookupTable(number2)}`);
console.log(`Reduce with Binary Conversion: ${countSetBitsReduce(number2)}`);
