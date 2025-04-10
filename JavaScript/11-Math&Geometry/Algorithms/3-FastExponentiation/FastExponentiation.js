/*
Math & Geometry: Fast Exponentiation in JavaScript

This code demonstrates five different approaches to calculate the exponentiation of a number (x^n) efficiently.  Standard Math.pow() can be inefficient for very large exponents.  These methods reduce the number of multiplications needed.

1.  Recursive Approach
    * 原理 (Principle):
        * If n is even: x^n = (x^(n/2))^2
        * If n is odd:  x^n = x * (x^((n-1)/2))^2
        * Base case: n == 0, return 1
    * 优点 (Advantages):  Conceptually simple, easy to understand.
    * 缺点 (Disadvantages): Can be stack-overflow-prone for very large exponents due to recursive calls.
    * 时间复杂度 (Time Complexity): O(log n)
    * 空间复杂度 (Space Complexity): O(log n) due to recursion depth

2.  Iterative Approach
    * 原理 (Principle):
        * Same principle as the recursive approach, but implemented iteratively.
        * Uses bitwise operations to check if the exponent is even or odd.
    * 优点 (Advantages):  Avoids recursion, more efficient in terms of memory.
    * 缺点 (Disadvantages): Slightly more complex to understand than the recursive version.
    * 时间复杂度 (Time Complexity): O(log n)
    * 空间复杂度 (Space Complexity): O(1)

3.  Right-to-Left Binary Method
    * 原理 (Principle):
        * Scans the bits of the exponent from right to left.
        * If the current bit is 1, multiply the result by the current power of x.
        * Square x in each iteration.
    * 优点 (Advantages):  Efficient and widely used.
    * 缺点 (Disadvantages):  Less intuitive than the basic recursive approach.
    * 时间复杂度 (Time Complexity): O(log n)
    * 空间复杂度 (Space Complexity): O(1)

4.  Left-to-Right Binary Method
     * 原理 (Principle):
        * Scans the bits of the exponent from left to right.
        * Squares the result in each step.
        * If the current bit is 1, multiply the result by x.
     * 优点 (Advantages): Efficient and can be slightly more intuitive for some.
     * 缺点 (Disadvantages): Requires knowing the exponent in binary form.
     * 时间复杂度 (Time Complexity): O(log n)
     * 空间复杂度 (Space Complexity): O(1)

5.  Using JavaScript's Math.pow()
    * 原理 (Principle):  Utilizes the built-in Math.pow() function.
    * 优点 (Advantages):  Simplest and most concise.
    * 缺点 (Disadvantages):  May not be as performant for extremely large exponents in all JavaScript engines, and doesn't illustrate the algorithm.
    * 时间复杂度 (Time Complexity): Implementation-dependent (often considered O(1) in practice, but can be O(log n) in some implementations)
    * 空间复杂度 (Space Complexity): O(1)
*/

/**
 * 1. Recursive Approach for Fast Exponentiation
 * Calculates x^n using recursion.
 *
 * @param {number} x The base number.
 * @param {number} n The exponent (non-negative integer).
 * @returns {number} The result of x^n.
 */
function fastExponentiationRecursive(x, n) {
    if (n === 0) {
        return 1;
    }

    if (n % 2 === 0) { // n is even
        const temp = fastExponentiationRecursive(x, n / 2);
        return temp * temp;
    } else { // n is odd
        const temp = fastExponentiationRecursive(x, (n - 1) / 2);
        return x * temp * temp;
    }
}

/**
 * 2. Iterative Approach for Fast Exponentiation
 * Calculates x^n using iteration and bitwise operations.
 *
 * @param {number} x The base number.
 * @param {number} n The exponent (non-negative integer).
 * @returns {number} The result of x^n.
 */
function fastExponentiationIterative(x, n) {
    let result = 1;
    let base = x;
    let exp = n;

    while (exp > 0) {
        if (exp % 2 === 1) { // Check if the last bit is 1 (odd exponent)
            result *= base;
        }
        base *= base; // Square the base
        exp = Math.floor(exp / 2); // Right shift the exponent (integer division by 2)
    }
    return result;
}

/**
 * 3. Right-to-Left Binary Method for Fast Exponentiation
 * Calculates x^n by scanning the bits of n from right to left.
 *
 * @param {number} x The base number.
 * @param {number} n The exponent (non-negative integer).
 * @returns {number} The result of x^n.
 */
function fastExponentiationRightToLeft(x, n) {
    let result = 1;
    let base = x;
    let exp = n;

    while (exp > 0) {
        if (exp & 1) { // Check if the least significant bit is 1
            result *= base;
        }
        base *= base;
        exp >>= 1; // Right shift the exponent by 1 (equivalent to dividing by 2 and discarding the remainder)
    }
    return result;
}

/**
 * 4. Left-to-Right Binary Method for Fast Exponentiation
 * Calculates x^n by scanning the bits of n from left to right.
 *
 * @param {number} x The base number.
 * @param {number} n The exponent (non-negative integer).
 * @returns {number} The result of x^n.
 */
function fastExponentiationLeftToRight(x, n) {
  let result = 1;
  let base = x;
  let exp = n;

  // Find the most significant bit
  let msb = 0;
  let temp = exp;
  while (temp > 0) {
    temp >>= 1;
    msb++;
  }

  // Iterate through the bits from left to right
  for (let i = msb - 1; i >= 0; i--) {
    result *= result; // Square the result
    if ((exp >> i) & 1) { // Check if the i-th bit is 1
      result *= base;
    }
  }
  return result;
}

/**
 * 5. Using JavaScript's Math.pow() for Exponentiation
 * Calculates x^n using the built-in Math.pow() function.
 *
 * @param {number} x The base number.
 * @param {number} n The exponent (non-negative integer).
 * @returns {number} The result of x^n.
 */
function fastExponentiationMathPow(x, n) {
    return Math.pow(x, n);
}



// Example usage and output
const base = 2;
const exponent = 10;

console.log(`Base: ${base}, Exponent: ${exponent}`);
console.log("---------------------------------------");

// 1. Recursive Approach
const resultRecursive = fastExponentiationRecursive(base, exponent);
console.log(`1. Recursive Approach: ${base}^${exponent} = ${resultRecursive}`);

// 2. Iterative Approach
const resultIterative = fastExponentiationIterative(base, exponent);
console.log(`2. Iterative Approach: ${base}^${exponent} = ${resultIterative}`);

// 3. Right-to-Left Binary Method
const resultRightToLeft = fastExponentiationRightToLeft(base, exponent);
console.log(`3. Right-to-Left Binary: ${base}^${exponent} = ${resultRightToLeft}`);

// 4. Left-to-Right Binary Method
const resultLeftToRight = fastExponentiationLeftToRight(base, exponent);
console.log(`4. Left-to-Right Binary: ${base}^${exponent} = ${resultLeftToRight}`);

// 5. Using Math.pow()
const resultMathPow = fastExponentiationMathPow(base, exponent);
console.log(`5. Using Math.pow(): ${base}^${exponent} = ${resultMathPow}`);

// Example with a larger exponent to demonstrate efficiency
const largeExponent = 1000000;
console.log("\nTesting with a large exponent:");
console.log(`Base: ${base}, Exponent: ${largeExponent}`);
console.log("---------------------------------------");

const startRecursive = performance.now();
const resultRecursiveLarge = fastExponentiationRecursive(base, largeExponent);
const endRecursive = performance.now();
console.log(`1. Recursive Approach: ${base}^${largeExponent} = ${resultRecursiveLarge.toPrecision(5)} (Time: ${endRecursive - startRecursive} ms)`); // Limit precision for display

const startIterative = performance.now();
const resultIterativeLarge = fastExponentiationIterative(base, largeExponent);
const endIterative = performance.now();
console.log(`2. Iterative Approach: ${base}^${largeExponent} = ${resultIterativeLarge.toPrecision(5)} (Time: ${endIterative - startIterative} ms)`);

const startRightToLeft = performance.now();
const resultRightToLeftLarge = fastExponentiationRightToLeft(base, largeExponent);
const endRightToLeft = performance.now();
console.log(`3. Right-to-Left Binary: ${base}^${largeExponent} = ${resultRightToLeftLarge.toPrecision(5)} (Time: ${endRightToLeft - startRightToLeft} ms)`);

const startLeftToRight = performance.now();
const resultLeftToRightLarge = fastExponentiationLeftToRight(base, largeExponent);
const endLeftToRight = performance.now();
console.log(`4. Left-to-Right Binary: ${base}^${largeExponent} = ${resultLeftToRightLarge.toPrecision(5)} (Time: ${endLeftToRight - startLeftToRight} ms)`);

const startMathPow = performance.now();
const resultMathPowLarge = fastExponentiationMathPow(base, largeExponent);
const endMathPow = performance.now();
console.log(`5. Using Math.pow(): ${base}^${largeExponent} = ${resultMathPowLarge.toPrecision(5)} (Time: ${endMathPow - startMathPow} ms)`);
