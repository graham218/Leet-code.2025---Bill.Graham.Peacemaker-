/**
 * Given an integer n, determine if it is a power of two.
 *
 * A number is a power of two if it can be written as 2^x for some integer x.
 *
 * Example 1:
 * Input: n = 1
 * Output: true (2^0 = 1)
 *
 * Example 2:
 * Input: n = 16
 * Output: true (2^4 = 16)
 *
 * Example 3:
 * Input: n = 3
 * Output: false
 *
 * Constraints:
 * -2^31 <= n <= 2^31 - 1
 */

/**
 * Approach 1: Iterative Division by 2
 * Keep dividing the number by 2 until it becomes 1. If at any point the remainder is not 0,
 * the number is not a power of two.  Handles edge case of n <= 0.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
function isPowerOfTwo_iterative(n) {
  if (n <= 0) {
    return false;
  }
  while (n % 2 === 0) {
    n /= 2;
  }
  return n === 1;
}

/**
 * Approach 2: Using Math.log2
 * If n is a power of 2, then log2(n) will be an integer.  We can check if the result
 * is an integer using Math.floor. Handles edge case of n <= 0.
 *
 * Time Complexity: O(1) - Math.log2 is typically implemented with a fast algorithm.
 * Space Complexity: O(1)
 */
function isPowerOfTwo_log2(n) {
  if (n <= 0) {
    return false;
  }
  const logResult = Math.log2(n);
  return Math.floor(logResult) === logResult;
}

/**
 * Approach 3: Bitwise AND with n-1
 * A power of two in binary representation has only one bit set (e.g., 1, 10, 100, 1000).
 * Subtracting 1 from a power of two will result in a number where all the bits
 * after the set bit are also set (e.g., 0, 01, 011, 0111).
 * The bitwise AND of these two numbers will be 0.
 * This approach is the most efficient. It correctly handles positive powers of 2.
 * It does not handle n <= 0 correctly.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
function isPowerOfTwo_bitwise(n) {
  if (n <= 0) {
      return false; // handles the edge case of n being 0 or negative
  }
  return (n & (n - 1)) === 0;
}

/**
 * Approach 4: Counting Set Bits
 * A power of two has only one bit set to 1 in its binary representation.
 * We can count the number of set bits and check if it is equal to 1.
 *
 * Time Complexity: O(log n) in the worst case (number of bits in n)
 * Space Complexity: O(1)
 */
function isPowerOfTwo_countBits(n) {
  if (n <= 0) {
    return false;
  }
  let count = 0;
  while (n > 0) {
    count += (n & 1); // Check the last bit
    n >>= 1;         // Right shift
  }
  return count === 1;
}

/**
 * Approach 5:  Using the Number 32 (for 32-bit integers)
 * The largest power of 2 that can be represented as a 32-bit signed integer is 2^30.
 * We can check if n is a power of 2 by checking if (2^30) is divisible by n.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
function isPowerOfTwo_division(n) {
  if (n <= 0) {
    return false;
  }
  const maxPowerOfTwo = 1073741824; // 2^30
  return maxPowerOfTwo % n === 0;
}

// Example usage and output
console.log("Example Cases:");
console.log(`Input: 1, Iterative: ${isPowerOfTwo_iterative(1)}, Log2: ${isPowerOfTwo_log2(1)}, Bitwise: ${isPowerOfTwo_bitwise(1)}, Count Bits: ${isPowerOfTwo_countBits(1)}, Division: ${isPowerOfTwo_division(1)}`); // true
console.log(`Input: 16, Iterative: ${isPowerOfTwo_iterative(16)}, Log2: ${isPowerOfTwo_log2(16)}, Bitwise: ${isPowerOfTwo_bitwise(16)}, Count Bits: ${isPowerOfTwo_countBits(16)}, Division: ${isPowerOfTwo_division(16)}`); // true
console.log(`Input: 3, Iterative: ${isPowerOfTwo_iterative(3)}, Log2: ${isPowerOfTwo_log2(3)}, Bitwise: ${isPowerOfTwo_bitwise(3)}, Count Bits: ${isPowerOfTwo_countBits(3)}, Division: ${isPowerOfTwo_division(3)}`); // false
console.log(`Input: 0, Iterative: ${isPowerOfTwo_iterative(0)}, Log2: ${isPowerOfTwo_log2(0)}, Bitwise: ${isPowerOfTwo_bitwise(0)}, Count Bits: ${isPowerOfTwo_countBits(0)}, Division: ${isPowerOfTwo_division(0)}`); // false
console.log(`Input: -16, Iterative: ${isPowerOfTwo_iterative(-16)}, Log2: ${isPowerOfTwo_log2(-16)}, Bitwise: ${isPowerOfTwo_bitwise(-16)}, Count Bits: ${isPowerOfTwo_countBits(-16)}, Division: ${isPowerOfTwo_division(-16)}`); // false
console.log(`Input: 2147483648, Iterative: ${isPowerOfTwo_iterative(2147483648)}, Log2: ${isPowerOfTwo_log2(2147483648)}, Bitwise: ${isPowerOfTwo_bitwise(2147483648)}, Count Bits: ${isPowerOfTwo_countBits(2147483648)}, Division: ${isPowerOfTwo_division(2147483648)}`); //true

// Additional test cases
console.log("\nAdditional Test Cases:");
function runTestCases() {
  const testCases = [
    { input: 1, expected: true },
    { input: 2, expected: true },
    { input: 4, expected: true },
    { input: 8, expected: true },
    { input: 16, expected: true },
    { input: 32, expected: true },
    { input: 64, expected: true },
    { input: 128, expected: true },
    { input: 256, expected: true },
    { input: 512, expected: true },
    { input: 1024, expected: true },
    { input: 2048, expected: true },
    { input: 4096, expected: true },
    { input: 8192, expected: true },
    { input: 16384, expected: true },
    { input: 32768, expected: true },
    { input: 65536, expected: true },
    { input: 131072, expected: true },
    { input: 262144, expected: true },
    { input: 524288, expected: true },
    { input: 1048576, expected: true },
    { input: 2097152, expected: true },
    { input: 4194304, expected: true },
    { input: 8388608, expected: true },
    { input: 16777216, expected: true },
    { input: 33554432, expected: true },
    { input: 67108864, expected: true },
    { input: 134217728, expected: true },
    { input: 268435456, expected: true },
    { input: 536870912, expected: true },
    { input: 1073741824, expected: true },
    { input: 2147483648, expected: true },
    { input: 0, expected: false },
    { input: 3, expected: false },
    { input: 5, expected: false },
    { input: 6, expected: false },
    { input: 7, expected: false },
    { input: 9, expected: false },
    { input: 10, expected: false },
    { input: 11, expected: false },
    { input: 12, expected: false },
    { input: 13, expected: false },
    { input: 14, expected: false },
    { input: 15, expected: false },
    { input: 17, expected: false },
    { input: 18, expected: false },
    { input: 19, expected: false },
    { input: 20, expected: false },
    { input: -1, expected: false },
    { input: -2, expected: false },
    { input: -4, expected: false },
    { input: -8, expected: false },
    { input: -16, expected: false },
  ];

  console.log("\nRunning Test Cases:");
  testCases.forEach((testCase, index) => {
    const { input, expected } = testCase;
    const results = [
      isPowerOfTwo_iterative(input),
      isPowerOfTwo_log2(input),
      isPowerOfTwo_bitwise(input),
      isPowerOfTwo_countBits(input),
      isPowerOfTwo_division(input),
    ];
    const passed = results.every(result => result === expected);
    const resultString = passed ? "PASS" : "FAIL";
    console.log(
      `Test Case ${index + 1}: Input = ${input}, Expected = ${expected}, Results = [${results.join(
        ", "
      )}] - ${resultString}`
    );
  });
}

runTestCases();
