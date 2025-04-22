/**
 * **Bit Manipulation: Checking if a Number is a Power of 2**
 *
 * A power of 2 is a number that can be expressed as 2 raised to some non-negative integer exponent.
 * For example, 2^0 = 1, 2^1 = 2, 2^2 = 4, 2^3 = 8, and so on.
 *
 * Here are five different approaches to check if a given number is a power of 2 using bit manipulation:
 */

(() => {
  /**
   * **Approach 1: Using `n & (n - 1)`**
   *
   * This is the most common and efficient method.
   * A power of 2 in binary representation has only one bit set (e.g., 1: 0001, 2: 0010, 4: 0100, 8: 1000).
   * Subtracting 1 from a power of 2 will result in a number where all the bits to the right of the set bit are also set (e.g., 7: 0111, 3: 0011).
   * The bitwise AND of `n` and `n - 1` will be 0 if `n` is a power of 2.
   *
   * **Example:**
   * n = 8 (1000 in binary)
   * n - 1 = 7 (0111 in binary)
   * n & (n - 1) = 1000 & 0111 = 0000 = 0
   *
   * **Edge Case:**
   * n = 0:  0 & -1 = 0.  We need to explicitly exclude 0.
   *
   * **Time Complexity:** O(1)
   * **Space Complexity:** O(1)
   */
  function isPowerOfTwo_approach1(n) {
    if (n <= 0) {
      return false;
    }
    return (n & (n - 1)) === 0;
  }

  /**
   * **Approach 2: Counting Set Bits**
   *
   * A power of 2 has only one bit set to 1 in its binary representation.
   * We can count the number of set bits and check if it is equal to 1.
   *
   * **Time Complexity:** O(log n) in the worst case (number of bits in n)
   * **Space Complexity:** O(1)
   */
  function isPowerOfTwo_approach2(n) {
    if (n <= 0) {
      return false;
    }
    let count = 0;
    while (n > 0) {
      count += (n & 1); // Check the least significant bit
      n >>= 1;         // Right shift n by 1
    }
    return count === 1;
  }

  /**
   * **Approach 3: Using Bitwise NOT**
   *
   * If `n` is a power of 2, then `n` will have only one bit set.
   * Let's say n is 8 (1000).
   * `~n` will be -9 (1...10111).
   * `~n + 1` will be -8 (1...1000).
   * `n & (~n + 1)` will give the least significant bit that is set.
   * If n is a power of 2, then `n & (~n + 1)` will be equal to n.
   *
   * **Time Complexity:** O(1)
   * **Space Complexity:** O(1)
   */
  function isPowerOfTwo_approach3(n) {
    if (n <= 0) {
      return false;
    }
    return (n & (~n + 1)) === n;
  }

  /**
   * **Approach 4:  Using Math.log2**
   *
   * The base-2 logarithm of a power of 2 is an integer.
   * We can use `Math.log2(n)` to find the logarithm base 2 of n.
   * If the result is an integer, then n is a power of 2.
   *
   * **Time Complexity:** O(1) - Math.log2 is generally considered constant time.
   * **Space Complexity:** O(1)
   */
  function isPowerOfTwo_approach4(n) {
    if (n <= 0) {
      return false;
    }
    const logResult = Math.log2(n);
    return Number.isInteger(logResult);
  }
  /**
   * **Approach 5: Iterative Division by 2**
   *
   * Keep dividing the number by 2. If the number is a power of 2,
   * it will eventually become 1. If at any point the remainder is not 0
   * and the number is not 1, then the number is not a power of 2.
   *
   * **Time Complexity:** O(log n)
   * **Space Complexity:** O(1)
   */
  function isPowerOfTwo_approach5(n) {
    if (n <= 0) return false;

    while (n % 2 === 0) {
      n /= 2;
    }
    return n === 1;
  }

  // Example Usage and Verification
  const numbers = [0, 1, 2, 3, 4, 5, 8, 16, 24, 32, 64, 128, -2, -8];
  console.log("Testing if numbers are powers of 2:");

  numbers.forEach(num => {
    console.log(`\nNumber: ${num}`);
    console.log(`Approach 1: ${isPowerOfTwo_approach1(num)}`);
    console.log(`Approach 2: ${isPowerOfTwo_approach2(num)}`);
    console.log(`Approach 3: ${isPowerOfTwo_approach3(num)}`);
    console.log(`Approach 4: ${isPowerOfTwo_approach4(num)}`);
    console.log(`Approach 5: ${isPowerOfTwo_approach5(num)}`);
  });
})();
