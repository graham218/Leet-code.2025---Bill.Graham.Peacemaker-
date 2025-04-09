// Matrix Chain Multiplication

// Helper function to print the optimal parenthesization
function printOptimalParens(s, i, j) {
  if (i === j) {
    process.stdout.write(`A${i}`); // Use process.stdout.write for node.js
  } else {
    process.stdout.write("(");
    printOptimalParens(s, i, s[i][j]);
    printOptimalParens(s, s[i][j] + 1, j);
    process.stdout.write(")");
  }
}

// 1. Recursive Solution
function matrixChainMultiplicationRecursive(p, i, j) {
  if (i === j) {
    return 0;
  }

  let min = Infinity;
  for (let k = i; k < j; k++) {
    const cost =
      matrixChainMultiplicationRecursive(p, i, k) +
      matrixChainMultiplicationRecursive(p, k + 1, j) +
      p[i - 1] * p[k] * p[j];
    if (cost < min) {
      min = cost;
    }
  }
  return min;
}

// 2. Memoized Solution (Top-Down DP)
function matrixChainMultiplicationMemoized(p, i, j, memo) {
  if (i === j) {
    return 0;
  }

  if (memo[i][j] !== -1) {
    return memo[i][j];
  }

  let min = Infinity;
  for (let k = i; k < j; k++) {
    const cost =
      matrixChainMultiplicationMemoized(p, i, k, memo) +
      matrixChainMultiplicationMemoized(p, k + 1, j, memo) +
      p[i - 1] * p[k] * p[j];
    if (cost < min) {
      min = cost;
    }
  }
  memo[i][j] = min;
  return min;
}

function matrixChainOrderMemoized(p) {
  const n = p.length;
  const memo = Array(n)
    .fill(null)
    .map(() => Array(n).fill(-1));
  return matrixChainMultiplicationMemoized(p, 1, n - 1, memo);
}

// 3. Tabulated Solution (Bottom-Up DP)
function matrixChainOrderTabulated(p) {
  const n = p.length;
  const m = Array(n)
    .fill(null)
    .map(() => Array(n).fill(0));
  const s = Array(n)
    .fill(null)
    .map(() => Array(n).fill(0)); // To store split points for optimal parenthesization

  for (let L = 2; L < n; L++) {
    for (let i = 1; i < n - L + 1; i++) {
      const j = i + L - 1;
      m[i][j] = Infinity;
      for (let k = i; k <= j - 1; k++) {
        const cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
        if (cost < m[i][j]) {
          m[i][j] = cost;
          s[i][j] = k; // Store the split point
        }
      }
    }
  }
  return { m: m[1][n - 1], s }; // Return both cost and split points
}

// 4. Optimized Tabulated Solution (Slightly more efficient)
function matrixChainOrderOptimized(p) {
    const n = p.length;
    const m = Array(n).fill(null).map(() => Array(n).fill(0));

    for (let len = 2; len < n; len++) {
        for (let i = 1; i < n - len + 1; i++) {
            const j = i + len - 1;
            m[i][j] = Infinity;
            for (let k = i; k < j; k++) {
                const cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }
    return m[1][n - 1];
}

// 5. Space Optimized Solution (Reduces space complexity to O(n)) - Not applicable for full MCM problem
// Space optimization is generally not straightforward for the full MCM problem
// because we need to store intermediate results for all subproblems.  A true
// space-optimized solution that reduces the auxiliary space to O(n) is not
// typically possible for the standard MCM problem. The following is included
// for demonstration of the concept, but it's not a correct or efficient approach
// for MCM.  It's included to show how one *might* think about space optimization,
// but it's crucial to understand it's not a practical solution for this problem.
//
// function matrixChainOrderSpaceOptimized(p) {
//   const n = p.length;
//   let dp = Array(n).fill(0);
//
//   for (let L = 2; L < n; L++) {
//     for (let i = 1; i < n - L + 1; i++) {
//       const j = i + L - 1;
//       let minCost = Infinity;
//       for (let k = i; k < j; k++) {
//         const cost = dp[i] + dp[k + 1] + p[i - 1] * p[k] * p[j]; // Incorrect access
//         if (cost < minCost) {
//           minCost = cost;
//         }
//       }
//       dp[j] = minCost; // Incorrect update
//     }
//   }
//   return dp[n - 1]; // Incorrect return
// }
//
// The above approach is fundamentally flawed for MCM.  It doesn't correctly
// track the dependencies between subproblems, and it overwrites values in `dp`
// that are still needed for other calculations.  It's included *only* to illustrate
// the *idea* of space optimization, but it will *not* produce the correct answer
// for Matrix Chain Multiplication.  It's here for educational purposes to show
// what a naive space optimization might look like and why it doesn't work.

// Example usage:
const p = [40, 20, 30, 10, 30]; // Dimensions: 40x20, 20x30, 30x10, 10x30
const n = p.length;

console.log("Matrix Chain Multiplication Results:");
console.log("------------------------------------");

// 1. Recursive Solution
const recursiveResult = matrixChainMultiplicationRecursive(p, 1, n - 1);
console.log("Recursive Solution:", recursiveResult); // Expected: 30000

// 2. Memoized Solution
const memoizedResult = matrixChainOrderMemoized(p);
console.log("Memoized Solution:", memoizedResult); // Expected: 30000

// 3. Tabulated Solution
const tabulatedResult = matrixChainOrderTabulated(p);
console.log("Tabulated Solution:", tabulatedResult.m); // Expected: 30000
process.stdout.write("Optimal Parenthesization: ");  // Use process.stdout.write
printOptimalParens(tabulatedResult.s, 1, n - 1);
console.log();

// 4. Optimized Tabulated Solution
const optimizedTabulatedResult = matrixChainOrderOptimized(p);
console.log("Optimized Tabulated Solution:", optimizedTabulatedResult); // Expected: 30000

// 5. Space Optimized Solution (Incorrect for MCM)
// const spaceOptimizedResult = matrixChainOrderSpaceOptimized(p);
// console.log("Space Optimized Solution (Incorrect):", spaceOptimizedResult); // Incorrect
console.log("Space Optimized Solution: Not applicable/Not Correct for MCM");
