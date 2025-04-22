/**
 * Bit Manipulation - Power of Two
 *
 * Problem:
 * Given an integer, determine if it is a power of two.
 *
 * A number is a power of two if it can be expressed as 2^n, where n is a non-negative integer.
 *
 * Examples:
 * Input: 1  Output: true (2^0)
 * Input: 16 Output: true (2^4)
 * Input: 3  Output: false
 * Input: 0  Output: false (Special case, typically not considered a power of 2)
 * Input: -1 Output: false (Negative numbers are not powers of 2)
 *
 * Approaches:
 * 1.  Iterative Division: Repeatedly divide the number by 2. If it eventually becomes 1, it's a power of two.
 * 2.  Bitwise AND: A power of two has only one bit set to 1.  n & (n-1) will be 0 for powers of 2.
 * 3.  Counting Set Bits: Count the number of set bits. A power of two has exactly one set bit.
 * 4.  Using Math.log2:  Check if the base-2 logarithm is an integer.
 * 5.  Check if n is a power of 2 using the Number.isInteger and Math.log2
 *
 * Real-world applications:
 * 1.  Memory Allocation: Determining block sizes in memory management.
 * 2.  Image Processing: Checking texture dimensions for power-of-two requirements.
 * 3.  Game Development: Optimizing calculations and data structures.
 * 4.  Network Routing: Identifying network masks and subnets.
 * 5.  Data Compression:  Algorithms may use power-of-two sizes for efficient processing.
 */

/**
 * Approach 1: Iterative Division
 *
 * Concept:
 * Repeatedly divides the input number by 2. If the number eventually becomes 1,
 * it is a power of two.  Handles edge cases like 0 and negative numbers.
 *
 * Time Complexity: O(log n) - Number of divisions is proportional to log2(n).
 * Space Complexity: O(1) - Constant space.
 */
function isPowerOfTwo_iterative(n) {
    if (n <= 0) {
        return false; // 0 and negative numbers are not powers of two
    }
    while (n % 2 === 0) {
        n /= 2;
    }
    return n === 1;
}

/**
 * Approach 2: Bitwise AND
 *
 * Concept:
 * A power of two in binary representation has only one bit set to 1
 * (e.g., 2 = 10, 4 = 100, 8 = 1000).
 * Subtracting 1 from a power of two results in a number where all the bits
 * after the leading 1 are set to 1 (e.g., 4 - 1 = 3,  100 - 011).
 * The bitwise AND of these two numbers will be 0.
 * n & (n - 1) clears the least significant bit.
 *
 * Time Complexity: O(1) - Constant time for bitwise operations.
 * Space Complexity: O(1) - Constant space.
 */
function isPowerOfTwo_bitwise(n) {
    if (n <= 0) {
        return false; // 0 and negative numbers are not powers of two
    }
    return (n & (n - 1)) === 0;
}

/**
 * Approach 3: Counting Set Bits
 *
 * Concept:
 * A power of two has exactly one bit set to 1 in its binary representation.
 * This approach counts the number of set bits.
 *
 * Time Complexity: O(log n) -  Worst case, iterates through the bits of n.
 * Space Complexity: O(1) - Constant space.
 */
function isPowerOfTwo_countBits(n) {
    if (n <= 0) {
        return false; // 0 and negative numbers are not powers of two
    }
    let count = 0;
    while (n > 0) {
        count += (n & 1); // Check the least significant bit
        n >>= 1;         // Right shift to check the next bit
    }
    return count === 1;
}

/**
 * Approach 4: Using Math.log2
 *
 * Concept:
 * The base-2 logarithm of a power of two is an integer.  We can use Math.log2
 * to calculate the logarithm and check if it's an integer.
 *
 * Time Complexity: O(1) -  Constant time for Math.log2 and Number.isInteger.
 * Space Complexity: O(1) - Constant space.
 */
function isPowerOfTwo_log2(n) {
    if (n <= 0) {
        return false;
    }
    const logValue = Math.log2(n);
    return Number.isInteger(logValue);
}

/**
 * Approach 5: Using Math.log2 and Integer Check (alternative)
 *
 * Concept:
 * Calculates the base-2 logarithm of the number and checks if the result
 * is an integer.  This is a variation of approach 4.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
function isPowerOfTwo_log2_alt(n) {
  if (n <= 0) return false;
  return Number.isInteger(Math.log2(n));
}

// --- Test Cases and Output ---
console.log("--- Power of Two Tests ---");

function runTests(funcName, func) {
    console.log(`\nTesting: ${funcName}`);
    console.log(`1: ${func(1)}`);       // true
    console.log(`2: ${func(2)}`);       // true
    console.log(`4: ${func(4)}`);       // true
    console.log(`8: ${func(8)}`);       // true
    console.log(`16: ${func(16)}`);     // true
    console.log(`3: ${func(3)}`);       // false
    console.log(`5: ${func(5)}`);       // false
    console.log(`6: ${func(6)}`);       // false
    console.log(`7: ${func(7)}`);       // false
    console.log(`0: ${func(0)}`);       // false
    console.log(`-1: ${func(-1)}`);     // false
    console.log(`-2: ${func(-2)}`);     // false
    console.log(`256: ${func(256)}`);   // true
    console.log(`1024: ${func(1024)}`); // true
}

runTests("isPowerOfTwo_iterative", isPowerOfTwo_iterative);
runTests("isPowerOfTwo_bitwise", isPowerOfTwo_bitwise);
runTests("isPowerOfTwo_countBits", isPowerOfTwo_countBits);
runTests("isPowerOfTwo_log2", isPowerOfTwo_log2);
runTests("isPowerOfTwo_log2_alt", isPowerOfTwo_log2_alt);
