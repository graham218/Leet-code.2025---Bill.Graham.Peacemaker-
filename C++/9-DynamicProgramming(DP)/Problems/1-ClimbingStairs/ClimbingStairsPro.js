/**
 * Climbing Stairs:
 *
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 *
 * This problem can be solved using dynamic programming. Here are five different approaches:
 *
 * 1.  Recursive Approach (Basic)
 * 2.  Memoization Approach (Top-Down DP)
 * 3.  Tabulation Approach (Bottom-Up DP)
 * 4.  Space-Optimized Tabulation (Constant Space)
 * 5.  Matrix Exponentiation (Advanced - for very large n)
 */

console.log("Climbing Stairs Problem - 5 Approaches");

// 1. Recursive Approach (Basic)
// This is the most intuitive way to solve the problem, but it's also the least efficient.
// It involves a lot of redundant calculations.
//
// Real-world Analogy: Imagine you are planning a small, fixed number of tasks. You explore every possible sequence of task completion
//                     without remembering the effort of repeated sub-sequences.  This is like a naive, inefficient project manager.
function climbStairsRecursive(n) {
    if (n <= 1) {
        return 1;
    }
    return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
}

console.log("\n1. Recursive Approach:");
console.log(`climbStairsRecursive(2) = ${climbStairsRecursive(2)}`); // Output: 2
console.log(`climbStairsRecursive(3) = ${climbStairsRecursive(3)}`); // Output: 3
console.log(`climbStairsRecursive(4) = ${climbStairsRecursive(4)}`); // Output: 5
console.log(`climbStairsRecursive(5) = ${climbStairsRecursive(5)}`); // Output: 8
// console.log(`climbStairsRecursive(30) = ${climbStairsRecursive(30)}`); // This will be very slow!  Avoid for large n

// 2. Memoization Approach (Top-Down DP)
// This approach is an improvement over the recursive approach. It stores the results of subproblems
// in a cache (memo) to avoid redundant calculations.
//
// Real-world Analogy:  A project manager uses a "scratchpad" (the memo object) to record the effort of sub-tasks.
//                      If the same sub-task comes up again, they just look up the effort instead of recalculating.
function climbStairsMemoization(n, memo = {}) {
    if (n <= 1) {
        return 1;
    }
    if (memo[n] !== undefined) {
        return memo[n];
    }
    memo[n] = climbStairsMemoization(n - 1, memo) + climbStairsMemoization(n - 2, memo);
    return memo[n];
}

console.log("\n2. Memoization Approach:");
console.log(`climbStairsMemoization(2) = ${climbStairsMemoization(2)}`); // Output: 2
console.log(`climbStairsMemoization(3) = ${climbStairsMemoization(3)}`); // Output: 3
console.log(`climbStairsMemoization(4) = ${climbStairsMemoization(4)}`); // Output: 5
console.log(`climbStairsMemoization(5) = ${climbStairsMemoization(5)}`); // Output: 8
console.log(`climbStairsMemoization(30) = ${climbStairsMemoization(30)}`); // Output: 1346269.  Much faster!

// 3. Tabulation Approach (Bottom-Up DP)
// This approach is another way to avoid redundant calculations. It builds a table of results
// from the bottom up, starting with the base cases.
//
// Real-world Analogy: A project manager creates a detailed work breakdown structure (the dp array), filling in the effort
//                     for each sub-task in order.  The effort for a task is calculated *after* the effort of its
//                     sub-tasks are known.
function climbStairsTabulation(n) {
    if (n <= 1) {
        return 1;
    }
    const dp = [1, 1]; // dp[0] = 1, dp[1] = 1
    for (let i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

console.log("\n3. Tabulation Approach:");
console.log(`climbStairsTabulation(2) = ${climbStairsTabulation(2)}`); // Output: 2
console.log(`climbStairsTabulation(3) = ${climbStairsTabulation(3)}`); // Output: 3
console.log(`climbStairsTabulation(4) = ${climbStairsTabulation(4)}`); // Output: 5
console.log(`climbStairsTabulation(5) = ${climbStairsTabulation(5)}`); // Output: 8
console.log(`climbStairsTabulation(30) = ${climbStairsTabulation(30)}`); // Output: 1346269

// 4. Space-Optimized Tabulation (Constant Space)
// This approach is a further optimization of the tabulation approach. It reduces the space complexity
// from O(n) to O(1) by only storing the previous two results, which are needed to calculate the next result.
//
// Real-world Analogy: The project manager realizes they only need the *last two* sub-task efforts to calculate the current task's effort.
//                     They discard older effort data, keeping only the essential information in their head or a very small note.
function climbStairsSpaceOptimized(n) {
    if (n <= 1) {
        return 1;
    }
    let prev1 = 1; // Represents dp[i-1]
    let prev2 = 1; // Represents dp[i-2]
    for (let i = 2; i <= n; i++) {
        const current = prev1 + prev2; // Calculate dp[i]
        prev2 = prev1;             // Update for the next iteration
        prev1 = current;
    }
    return prev1;
}

console.log("\n4. Space-Optimized Tabulation:");
console.log(`climbStairsSpaceOptimized(2) = ${climbStairsSpaceOptimized(2)}`); // Output: 2
console.log(`climbStairsSpaceOptimized(3) = ${climbStairsSpaceOptimized(3)}`); // Output: 3
console.log(`climbStairsSpaceOptimized(4) = ${climbStairsSpaceOptimized(4)}`); // Output: 5
console.log(`climbStairsSpaceOptimized(5) = ${climbStairsSpaceOptimized(5)}`); // Output: 8
console.log(`climbStairsSpaceOptimized(30) = ${climbStairsSpaceOptimized(30)}`); // Output: 1346269

// 5. Matrix Exponentiation (Advanced - for very large n)
// This approach uses matrix exponentiation to calculate the nth Fibonacci number (which is related to this problem)
// in O(log n) time.  This is significantly faster for very large values of n.
//
// Real-world Analogy:  For extremely large projects with a very specific, repetitive structure, an advanced project management
//                       technique (like using a mathematical model of project dependencies) can provide a very efficient way to
//                       calculate the overall effort.  This is like using a highly optimized algorithm for a very specific scenario.
function climbStairsMatrix(n) {
    if (n <= 1) return 1;

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

    function powerMatrix(M, p) {
        if (p === 1) return M;
        if (p % 2 === 0) {
            const X = powerMatrix(M, p / 2);
            return multiplyMatrices(X, X);
        } else {
            const X = powerMatrix(M, (p - 1) / 2);
            return multiplyMatrices(multiplyMatrices(X, X), M);
        }
    }

    const finalMatrix = powerMatrix(matrix, n - 1);
    return finalMatrix[0][0];
}

console.log("\n5. Matrix Exponentiation Approach:");
console.log(`climbStairsMatrix(2) = ${climbStairsMatrix(2)}`);
console.log(`climbStairsMatrix(3) = ${climbStairsMatrix(3)}`);
console.log(`climbStairsMatrix(4) = ${climbStairsMatrix(4)}`);
console.log(`climbStairsMatrix(5) = ${climbStairsMatrix(5)}`);
console.log(`climbStairsMatrix(30) = ${climbStairsMatrix(30)}`);  // Fast, even for larger n
console.log(`climbStairsMatrix(100) = ${climbStairsMatrix(100)}`); // Handles larger n efficiently
