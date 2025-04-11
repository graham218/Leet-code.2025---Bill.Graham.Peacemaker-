/**
 * Happy Number Problem:
 *
 * A happy number is defined by the following process:
 *
 * 1.  Starting with any positive integer, replace the number by the sum of the squares of its digits.
 * 2.  Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not contain 1.
 * 3.  Those numbers for which this process ends in 1 are happy numbers.
 *
 * For example, 19 is a happy number:
 *
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1
 *
 * Implement a function to determine if a number is a happy number.
 */

/**
 * Approach 1: Using a Set to detect cycles
 */
function isHappy1(n) {
  const seen = new Set();
  while (n !== 1 && !seen.has(n)) {
    seen.add(n);
    n = sumOfSquaredDigits(n);
  }
  return n === 1;
}

/**
 * Approach 2: Using Floyd's Cycle Detection (Fast and Slow pointers)
 * This approach is more efficient as it avoids storing the entire history of numbers.
 */
function isHappy2(n) {
  let slow = n;
  let fast = n;
  do {
    slow = sumOfSquaredDigits(slow);
    fast = sumOfSquaredDigits(sumOfSquaredDigits(fast));
  } while (slow !== fast);
  return slow === 1;
}

/**
 * Helper function to calculate the sum of the squares of the digits of a number.
 */
function sumOfSquaredDigits(num) {
  let sum = 0;
  while (num > 0) {
    const digit = num % 10;
    sum += digit * digit;
    num = Math.floor(num / 10);
  }
  return sum;
}

/**
 * Approach 3: Using a Lookup Table of Unhappy Numbers
 * Numbers that are not happy eventually reach a cycle.  We can check if the number reaches any of the numbers in the cycle.
 * The most common cycle starts at 4.
 */
function isHappy3(n) {
  const unhappyNumbers = [4, 16, 37, 58, 89, 145, 42, 20]; // Common cycle numbers
  while (n !== 1 && !unhappyNumbers.includes(n)) {
    n = sumOfSquaredDigits(n);
  }
  return n === 1;
}

/**
 * Approach 4: Iterative Approach with Maximum Iterations
 * This approach limits the number of iterations to prevent infinite loops.
 */
function isHappy4(n) {
  let count = 0;
  const maxIterations = 1000; // Set a maximum limit
  while (n !== 1 && count < maxIterations) {
    n = sumOfSquaredDigits(n);
    count++;
  }
  return n === 1;
}

/**
 * Approach 5: Recursive Approach with Memoization
 * This approach uses recursion with a cache (memoization) to store previously seen numbers
 */
function isHappy5(n, cache = new Set()) {
  if (n === 1) {
    return true;
  }
  if (cache.has(n)) {
    return false; // Cycle detected
  }
  cache.add(n);
  return isHappy5(sumOfSquaredDigits(n), cache);
}

// Example usage and output using console.log:
const numbers = [19, 20, 7, 28, 4];

console.log("Approach 1 (Set):");
numbers.forEach(num => console.log(`${num} is happy: ${isHappy1(num)}`));

console.log("\nApproach 2 (Floyd's Cycle Detection):");
numbers.forEach(num => console.log(`${num} is happy: ${isHappy2(num)}`));

console.log("\nApproach 3 (Unhappy Numbers Lookup):");
numbers.forEach(num => console.log(`${num} is happy: ${isHappy3(num)}`));

console.log("\nApproach 4 (Max Iterations):");
numbers.forEach(num => console.log(`${num} is happy: ${isHappy4(num)}`));

console.log("\nApproach 5 (Recursion with Memoization):");
numbers.forEach(num => console.log(`${num} is happy: ${isHappy5(num)}`));
