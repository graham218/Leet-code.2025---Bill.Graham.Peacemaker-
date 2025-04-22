/**
 * Given an unsigned integer, return the number of '1' bits it has (i.e., the number of set bits).
 *
 * For example, the 32-bit integer '11' has binary representation 00000000000000000000000000001011, so the function should return 3.
 */

/**
 * Approach 1: Using the right shift operator (>>>) and checking the least significant bit.
 *
 * Time Complexity: O(log n), where n is the number.  In the worst case, we iterate through all bits of n.
 * Space Complexity: O(1), constant space is used.
 */
const hammingWeight1 = (n) => {
  let count = 0;
  while (n !== 0) {
    // Check if the least significant bit is 1 using the modulo operator.
    if (n % 2 === 1) {
      count++;
    }
    // Use unsigned right shift to move to the next bit.
    n >>>= 1;
  }
  return count;
};

/**
 * Approach 2: Optimized approach using bit manipulation (n & (n - 1)).
 *
 * Time Complexity: O(k), where k is the number of set bits in n. This is because the loop iterates once for each set bit.
 * Space Complexity: O(1), constant space is used.
 */
const hammingWeight2 = (n) => {
  let count = 0;
  while (n !== 0) {
    // This operation clears the least significant 1 bit of n.
    n &= (n - 1);
    count++;
  }
  return count;
};

/**
 * Approach 3: Using the built-in JavaScript method (toString(2)).  This is NOT ideal for very large numbers.
 *
 * Time Complexity: O(log n) in the average case, where n is the number.  Converting to a string of base 2.
 * Space Complexity: O(log n), to store the binary string representation of n.
 */
const hammingWeight3 = (n) => {
  // Convert the number to its binary string representation.
  const binaryString = n.toString(2);
  let count = 0;
  // Iterate through the string and count the '1's.
  for (let i = 0; i < binaryString.length; i++) {
    if (binaryString[i] === '1') {
      count++;
    }
  }
  return count;
};

/**
 * Approach 4:  Bitwise AND with 1 and right shift (>>).  Similar to approach 1, but uses >>
 *
 * Time Complexity: O(log n), where n is the number.
 * Space Complexity: O(1)
 */
const hammingWeight4 = (n) => {
    let count = 0;

    while (n !== 0) {
        if ((n & 1) === 1) {
            count++;
        }
        n = n >> 1; // Right shift (signed),  Use >>> for consistency.
    }
    return count;
};

/**
 * Approach 5: Using Array.from and toString(2) and filtering.
 *
 * Time Complexity: O(log n), where n is the number.
 * Space Complexity: O(log n)
 */
const hammingWeight5 = (n) => {
    const binaryString = n.toString(2);
    const bitsArray = Array.from(binaryString); // Convert string to array of characters
    const ones = bitsArray.filter(bit => bit === '1');
    return ones.length;
};



// Example usage:
const number = 11; // Binary representation: 1011
console.log(`Number: ${number}`);
console.log(`Hamming Weight (Approach 1): ${hammingWeight1(number)}`); // Output: 3
console.log(`Hamming Weight (Approach 2): ${hammingWeight2(number)}`); // Output: 3
console.log(`Hamming Weight (Approach 3): ${hammingWeight3(number)}`); // Output: 3
console.log(`Hamming Weight (Approach 4): ${hammingWeight4(number)}`); // Output: 3
console.log(`Hamming Weight (Approach 5): ${hammingWeight5(number)}`); // Output: 3

const largeNumber = 2147483647; // Max 32-bit signed integer (all bits are 1 except the sign bit in some representations)
console.log(`\nNumber: ${largeNumber}`);
console.log(`Hamming Weight (Approach 1) for large number: ${hammingWeight1(largeNumber)}`);
console.log(`Hamming Weight (Approach 2) for large number: ${hammingWeight2(largeNumber)}`);
console.log(`Hamming Weight (Approach 3) for large number: ${hammingWeight3(largeNumber)}`);
console.log(`Hamming Weight (Approach 4) for large number: ${hammingWeight4(largeNumber)}`);
console.log(`Hamming Weight (Approach 5) for large number: ${hammingWeight5(largeNumber)}`);

const zeroNumber = 0;
console.log(`\nNumber: ${zeroNumber}`);
console.log(`Hamming Weight (Approach 1) for zero: ${hammingWeight1(zeroNumber)}`);
console.log(`Hamming Weight (Approach 2) for zero: ${hammingWeight2(zeroNumber)}`);
console.log(`Hamming Weight (Approach 3) for zero: ${hammingWeight3(zeroNumber)}`);
console.log(`Hamming Weight (Approach 4) for zero: ${hammingWeight4(zeroNumber)}`);
console.log(`Hamming Weight (Approach 5) for zero: ${hammingWeight5(zeroNumber)}`);
