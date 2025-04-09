/**
 * Fibonacci Series Implementation in JavaScript - 5 Approaches
 */

console.log("Fibonacci Series in JavaScript - 5 Approaches");

/**
 * 1. Recursive Approach (Basic)
 * - Purely recursive implementation.
 * - Inefficient due to repeated calculations.
 */
function fibonacciRecursive(n) {
  if (n <= 1) return n;
  return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

console.log("\n1. Recursive Approach:");
console.time("Recursive");
console.log("fibonacciRecursive(10):", fibonacciRecursive(10)); // 55
console.timeEnd("Recursive"); // ~1ms for fib(10), ~45ms for fib(20), very slow for fib(30+)

/**
 * 2. Memoization Approach (Top-Down DP)
 * - Uses an object (memo) to store previously calculated Fibonacci numbers.
 * - Avoids redundant calculations by looking up stored values.
 */
function fibonacciMemoization(n, memo = {}) {
  if (n <= 1) return n;
  if (memo[n] !== undefined) return memo[n]; // Check if result is memoized
  memo[n] = fibonacciMemoization(n - 1, memo) + fibonacciMemoization(n - 2, memo);
  return memo[n];
}

console.log("\n2. Memoization Approach:");
console.time("Memoization");
console.log("fibonacciMemoization(10):", fibonacciMemoization(10)); // 55
console.log("fibonacciMemoization(100):", fibonacciMemoization(100)); // 354224848179262000000
console.timeEnd("Memoization"); // ~0.1ms for fib(10), ~0.2ms for fib(100) - HUGE improvement

/**
 * 3. Tabulation Approach (Bottom-Up DP)
 * - Builds a table (dp) of Fibonacci numbers from the bottom up.
 * - Iteratively calculates Fibonacci numbers and stores them in the table.
 */
function fibonacciTabulation(n) {
  if (n <= 1) return n;
  const dp = [0, 1]; // Initialize base cases
  for (let i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2]; // Build the table
  }
  return dp[n];
}

console.log("\n3. Tabulation Approach:");
console.time("Tabulation");
console.log("fibonacciTabulation(10):", fibonacciTabulation(10)); // 55
console.log("fibonacciTabulation(100):", fibonacciTabulation(100)); // 354224848179262000000
console.timeEnd("Tabulation"); // ~0.1ms for fib(10), ~0.1ms for fib(100) - Very efficient

/**
 * 4. Tabulation Approach with Space Optimization
 * - Similar to tabulation, but uses only two variables to store the previous two Fibonacci numbers.
 * - Reduces space complexity from O(n) to O(1).
 */
function fibonacciOptimized(n) {
  if (n <= 1) return n;
  let a = 0, b = 1; // Initialize first two Fibonacci numbers
  for (let i = 2; i <= n; i++) {
    const temp = a + b; // Calculate next Fibonacci number
    a = b;             // Update a
    b = temp;            // Update b
  }
  return b;
}

console.log("\n4. Tabulation Approach (Space Optimized):");
console.time("Optimized Tabulation");
console.log("fibonacciOptimized(10):", fibonacciOptimized(10)); // 55
console.log("fibonacciOptimized(100):", fibonacciOptimized(100)); // 354224848179262000000
console.timeEnd("Optimized Tabulation"); // ~0.1ms for fib(10), ~0.1ms for fib(100) - Best space efficiency

/**
 * 5. Matrix Exponentiation (Advanced - For very large n)
 * - Uses matrix exponentiation to calculate the nth Fibonacci number in O(log n) time.
 * - More complex but very efficient for large values of n.
 */
function fibonacciMatrix(n) {
  if (n <= 1) return n;

  const matrix = [
    [1, 1],
    [1, 0],
  ];

  function multiplyMatrices(A, B) {
    const C = [
      [0, 0],
      [0, 0],
    ];
    for (let i = 0; i < 2; i++) {
      for (let j = 0; j < 2; j++) {
        for (let k = 0; k < 2; k++) {
          C[i][j] = (C[i][j] + A[i][k] * B[k][j]);
        }
      }
    }
    return C;
  }

  function powerMatrix(M, n) {
    if (n === 0 || n === 1) return M; // Corrected base case
    let result = [[1,0],[0,1]]; //identity matrix
    let A = M;

    while (n > 0) {
      if (n % 2 === 1) {
        result = multiplyMatrices(result, A);
      }
      A = multiplyMatrices(A, A);
      n = Math.floor(n / 2);
    }
    return result;
  }

  const finalMatrix = powerMatrix(matrix, n - 1);
  return finalMatrix[0][0];
}

console.log("\n5. Matrix Exponentiation Approach:");
console.time("Matrix Exponentiation");
console.log("fibonacciMatrix(10):", fibonacciMatrix(10)); // 55
console.log("fibonacciMatrix(100):", fibonacciMatrix(100)); // 354224848179262000000
console.log("fibonacciMatrix(1000):", fibonacciMatrix(1000));
console.timeEnd("Matrix Exponentiation");
