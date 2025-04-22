/**
 * Bit Manipulation: Checking if a Number is a Power of 2
 *
 * Problem:
 * Given an integer, determine if it is a power of 2.
 *
 * A number is a power of 2 if it can be expressed as 2^n, where n is a non-negative integer.
 *
 * We will explore several approaches, including bit manipulation techniques that are
 * highly efficient.  We'll also provide real-world examples of where these techniques
 * are applied.
 */

{
  console.log("\n--- Bit Manipulation: Checking if a Number is a Power of 2 ---\n");

  /**
   * Approach 1: Iterative Division by 2
   *
   * Concept:
   * Repeatedly divide the number by 2. If the number is a power of 2,
   * the remainder will always be 0, and the final result will be 1.
   *
   * Example:
   * n = 8 (2^3)
   * 8 / 2 = 4, remainder 0
   * 4 / 2 = 2, remainder 0
   * 2 / 2 = 1, remainder 0
   *
   * Real-world application:
   * -  Calculating the number of times a task can be divided in a scheduling algorithm.
   */
  function isPowerOfTwo_Division(n) {
    if (n <= 0) {
      return false;
    }
    while (n % 2 === 0) {
      n /= 2;
    }
    return n === 1;
  }

  // Example usage
  console.log("Approach 1: Iterative Division by 2");
  console.log(`isPowerOfTwo_Division(8): ${isPowerOfTwo_Division(8)}`); // true
  console.log(`isPowerOfTwo_Division(12): ${isPowerOfTwo_Division(12)}`); // false
  console.log(`isPowerOfTwo_Division(0): ${isPowerOfTwo_Division(0)}`);   // false
  console.log(`isPowerOfTwo_Division(1): ${isPowerOfTwo_Division(1)}`);   // true
  console.log(`isPowerOfTwo_Division(1024): ${isPowerOfTwo_Division(1024)}`); // true


  /**
   * Approach 2: Using Math.log2
   *
   * Concept:
   * The logarithm base 2 of a power of 2 is an integer. We can use Math.log2()
   * to calculate the base 2 logarithm and check if the result is an integer.
   *
   * Example:
   * log2(8) = 3, which is an integer.
   * log2(12) ≈ 3.58, which is not an integer.
   *
   * Real-world application:
   * -   Determining the number of bits needed to represent a number (e.g., in data storage).
   */
  function isPowerOfTwo_Log2(n) {
    if (n <= 0) {
      return false;
    }
    const logResult = Math.log2(n);
    return Number.isInteger(logResult);
  }

  // Example usage
  console.log("\nApproach 2: Using Math.log2");
  console.log(`isPowerOfTwo_Log2(8): ${isPowerOfTwo_Log2(8)}`); // true
  console.log(`isPowerOfTwo_Log2(12): ${isPowerOfTwo_Log2(12)}`); // false
  console.log(`isPowerOfTwo_Log2(0): ${isPowerOfTwo_Log2(0)}`);   // false
  console.log(`isPowerOfTwo_Log2(1): ${isPowerOfTwo_Log2(1)}`);   // true
  console.log(`isPowerOfTwo_Log2(1024): ${isPowerOfTwo_Log2(1024)}`); // true

  /**
   * Approach 3: Bitwise AND with n-1
   *
   * Concept:
   * A power of 2 in binary has only one bit set to 1 (e.g., 8 is 1000).
   * Subtracting 1 from a power of 2 will result in a number where all the bits
   * after the leading 1 are set to 1 (e.g., 8 - 1 = 7, which is 0111).
   * The bitwise AND of these two numbers will be 0.
   *
   * Example:
   * n = 8 (1000 in binary)
   * n - 1 = 7 (0111 in binary)
   * 1000 & 0111 = 0000 = 0
   *
   * Real-world application:
   * -   Efficiently checking if a number is a power of 2 in performance-critical
   * systems, such as embedded systems or high-frequency trading platforms.
   */
  function isPowerOfTwo_Bitwise(n) {
    if (n <= 0) {
      return false;
    }
    return (n & (n - 1)) === 0;
  }

  // Example usage
  console.log("\nApproach 3: Bitwise AND with n-1");
  console.log(`isPowerOfTwo_Bitwise(8): ${isPowerOfTwo_Bitwise(8)}`); // true
  console.log(`isPowerOfTwo_Bitwise(12): ${isPowerOfTwo_Bitwise(12)}`); // false
  console.log(`isPowerOfTwo_Bitwise(0): ${isPowerOfTwo_Bitwise(0)}`);   // false
  console.log(`isPowerOfTwo_Bitwise(1): ${isPowerOfTwo_Bitwise(1)}`);   // true
  console.log(`isPowerOfTwo_Bitwise(1024): ${isPowerOfTwo_Bitwise(1024)}`); // true

  /**
   * Approach 4: Counting Set Bits
   *
   * Concept:
   * A power of 2 has only one bit set to 1 in its binary representation.
   * We can count the number of set bits and check if it is equal to 1.
   *
   * Example:
   * 8 (1000 in binary) has one set bit.
   * 12 (1100 in binary) has two set bits.
   *
   * Real-world application:
   * -   Error detection and correction in data transmission, where the number of set
   * bits can be used to calculate parity.
   */
  function isPowerOfTwo_BitCount(n) {
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

  // Example usage
  console.log("\nApproach 4: Counting Set Bits");
  console.log(`isPowerOfTwo_BitCount(8): ${isPowerOfTwo_BitCount(8)}`); // true
  console.log(`isPowerOfTwo_BitCount(12): ${isPowerOfTwo_BitCount(12)}`); // false
  console.log(`isPowerOfTwo_BitCount(0): ${isPowerOfTwo_BitCount(0)}`);   // false
  console.log(`isPowerOfTwo_BitCount(1): ${isPowerOfTwo_BitCount(1)}`);   // true
  console.log(`isPowerOfTwo_BitCount(1024): ${isPowerOfTwo_BitCount(1024)}`); // true


  /**
   * Approach 5:  Using the ~ Operator
   *
   * Concept:
   * The ~ operator flips all the bits of a number.  For a power of two, n,
   * ~n will have all bits set to 1 except for the position of the original '1'
   * bit in n.  Adding 1 to ~n results in a number that, when ANDed with n,
   * will be zero (except for the case of n = 0).
   *
   * Example:
   * n = 8 (1000 in binary)
   * ~n = -9 (1...10111 in binary, two's complement)
   * ~n + 1 = -8 (1...11000 in binary)
   * n & (~n + 1) = 1000 & 11000 = 1000
   *
   * For power of 2, n & (~n + 1) == n
   *
   * Real-world application:
   * - This method is sometimes used in low-level optimizations or specific
   * hardware interactions.
   */
    function isPowerOfTwo_TwosComplement(n) {
        if (n <= 0) return false;
        return (n & (~n + 1)) === n;
    }

    console.log("\nApproach 5: Using the ~ Operator");
    console.log(`isPowerOfTwo_TwosComplement(8): ${isPowerOfTwo_TwosComplement(8)}`);
    console.log(`isPowerOfTwo_TwosComplement(12): ${isPowerOfTwo_TwosComplement(12)}`);
    console.log(`isPowerOfTwo_TwosComplement(0): ${isPowerOfTwo_TwosComplement(0)}`);
    console.log(`isPowerOfTwo_TwosComplement(1): ${isPowerOfTwo_TwosComplement(1)}`);
    console.log(`isPowerOfTwo_TwosComplement(1024): ${isPowerOfTwo_TwosComplement(1024)}`);
}
