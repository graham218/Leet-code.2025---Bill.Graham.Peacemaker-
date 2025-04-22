/**
 * Happy Number Problem:
 *
 * A happy number is defined by the following process:
 *
 * 1.  Starting with any positive integer, replace the number by the sum of the squares of its digits.
 * 2.  Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
 * 3.  Those numbers for which this process ends in 1 are happy numbers.
 *
 * For example, 19 is a happy number:
 *
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1
 *
 * Determine if a number is a happy number.
 */

/**
 * Helper function to calculate the sum of the squares of the digits of a number.
 *
 * @param {number} n The number.
 * @returns {number} The sum of the squares of the digits.
 */
const sumOfSquaredDigits = (n) => {
  let sum = 0;
  while (n > 0) {
    const digit = n % 10;
    sum += digit * digit;
    n = Math.floor(n / 10);
  }
  return sum;
};

// ----------------------------------------------------------------------------
// 1.  Basic Iterative Approach
//
// Project:  Simple Number Utility
//
// Description:  This is the most straightforward implementation, suitable for a
// simple utility function in a small project or script.  It directly
// implements the happy number algorithm using a while loop and a set to
// detect cycles.
// ----------------------------------------------------------------------------
const isHappyBasic = (n) => {
  const seen = new Set();
  while (n !== 1 && !seen.has(n)) {
    seen.add(n);
    n = sumOfSquaredDigits(n);
  }
  return n === 1;
};

// ----------------------------------------------------------------------------
// 2.  Iterative Approach with Maximum Iterations
//
// Project:  Data Analysis Tool
//
// Description:  In a data analysis tool, you might want to process a large
// number of inputs.  To prevent infinite loops in case of erroneous data,
// we add a maximum iteration count.
// ----------------------------------------------------------------------------
const isHappyWithMaxIterations = (n, maxIterations = 1000) => {
  const seen = new Set();
  let iterations = 0;
  while (n !== 1 && !seen.has(n) && iterations < maxIterations) {
    seen.add(n);
    n = sumOfSquaredDigits(n);
    iterations++;
  }
  return n === 1;
};

// ----------------------------------------------------------------------------
// 3.  Floyd's Cycle Detection (Tortoise and Hare)
//
// Project:  Performance-Critical Library
//
// Description:  For a performance-critical library, especially when dealing
// with very large numbers, Floyd's cycle detection algorithm is more
// efficient in detecting loops than using a set.
// ----------------------------------------------------------------------------
const isHappyFloyd = (n) => {
  let slow = n;
  let fast = n;
  do {
    slow = sumOfSquaredDigits(slow);
    fast = sumOfSquaredDigits(sumOfSquaredDigits(fast));
  } while (slow !== fast);
  return slow === 1;
};

// ----------------------------------------------------------------------------
// 4.  Precomputed Unhappy Numbers
//
// Project:  Real-time System
//
// Description:  In a real-time system where performance is paramount, we can
// precompute the set of unhappy numbers that lead to a cycle.  This avoids
// redundant calculations.  The key idea is that all unhappy numbers eventually
// reach the same cycle: 4, 16, 37, 58, 89, 145, 42, 20.
// ----------------------------------------------------------------------------
const unhappyNumbers = new Set([4, 16, 37, 58, 89, 145, 42, 20]);

const isHappyPrecomputed = (n) => {
  while (n !== 1 && !unhappyNumbers.has(n)) {
    n = sumOfSquaredDigits(n);
  }
  return n === 1;
};

// ----------------------------------------------------------------------------
// 5.  Recursive Approach with Memoization
//
// Project:  Functional Programming Application
//
// Description:  For a functional programming application, a recursive
// approach with memoization can be used.  This avoids recalculating the
// sum of squared digits for the same number multiple times.
// ----------------------------------------------------------------------------
const isHappyRecursive = (n, memo = new Map()) => {
  if (n === 1) return true;
  if (memo.has(n)) return false; // Cycle detected
  memo.set(n, true); // Mark as visited
  const nextNumber = sumOfSquaredDigits(n);
  return isHappyRecursive(nextNumber, memo);
};

// ----------------------------------------------------------------------------
// Main function to demonstrate the different approaches.
// ----------------------------------------------------------------------------
const main = () => {
  const testNumbers = [1, 19, 2, 7, 28, 145, 100, 2147483647]; // Added more diverse test cases

  console.log("--- Happy Number Results ---");

  console.log("\n1. Basic Iterative Approach:");
  testNumbers.forEach((num) => {
    console.log(`${num} is ${isHappyBasic(num) ? "happy" : "unhappy"}`);
  });

  console.log("\n2. Iterative Approach with Maximum Iterations:");
  testNumbers.forEach((num) => {
    console.log(`${num} is ${isHappyWithMaxIterations(num) ? "happy" : "unhappy"}`);
  });

  console.log("\n3. Floyd's Cycle Detection:");
  testNumbers.forEach((num) => {
    console.log(`${num} is ${isHappyFloyd(num) ? "happy" : "unhappy"}`);
  });

  console.log("\n4. Precomputed Unhappy Numbers:");
  testNumbers.forEach((num) => {
    console.log(`${num} is ${isHappyPrecomputed(num) ? "happy" : "unhappy"}`);
  });

  console.log("\n5. Recursive Approach with Memoization:");
  testNumbers.forEach((num) => {
    console.log(`${num} is ${isHappyRecursive(num) ? "happy" : "unhappy"}`);
  });
};

// Run the main function to display the results.
main();
