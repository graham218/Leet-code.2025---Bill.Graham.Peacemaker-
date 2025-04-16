/*
 * Matrix Chain Multiplication (MCM) Problem:
 *
 * Given a sequence of matrices, find the most efficient way to multiply these matrices together.
 * The problem is not actually to perform the multiplications, but merely to decide the sequence
 * of the matrix multiplications involved.
 *
 * Different ways of parenthesizing a chain of matrices result in different numbers of total operations.
 *
 * For example:
 *
 * Consider four matrices A1, A2, A3, and A4 with dimensions 10x20, 20x50, 50x10, and 10x30 respectively.
 * There are several ways to multiply these matrices:
 *
 * 1. (A1 * A2) * (A3 * A4)
 * 2. ((A1 * A2) * A3) * A4
 * 3. A1 * ((A2 * A3) * A4)
 * 4. (A1 * (A2 * A3)) * A4
 * 5. A1 * (A2 * (A3 * A4))
 *
 * Each of these parenthesizations requires a different number of multiplications. The goal is to
 * find the parenthesization that minimizes the total number of scalar multiplications.
 */

// Helper function to print the optimal parenthesization
function printOptimalParenthesization(s, i, j) {
    if (i === j) {
        return "A" + i;
    } else {
        const k = s[i][j];
        return "(" + printOptimalParenthesization(s, i, k) + printOptimalParenthesization(s, k + 1, j) + ")";
    }
}

// 1. Standard Dynamic Programming Approach (Tabulation)
function matrixChainMultiplicationDP(p) {
    const n = p.length - 1; // Number of matrices
    const m = Array(n + 1).fill(null).map(() => Array(n + 1).fill(0)); // m[i][j] = min cost of multiplying Ai to Aj
    const s = Array(n + 1).fill(null).map(() => Array(n + 1).fill(0)); // s[i][j] = k at which we split Ai to Aj

    for (let len = 2; len <= n; len++) { // len is length of chain
        for (let i = 1; i <= n - len + 1; i++) {
            const j = i + len - 1;
            m[i][j] = Infinity;
            for (let k = i; k < j; k++) {
                const cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    const optimalParens = printOptimalParenthesization(s, 1, n);
    return {
        minCost: m[1][n],
        optimalParenthesization: optimalParens,
    };
}

// 2. Memoization (Top-Down Dynamic Programming)
function matrixChainMultiplicationMemo(p) {
    const n = p.length - 1;
    const m = Array(n + 1).fill(null).map(() => Array(n + 1).fill(null)); // Use null to indicate not computed
    const s = Array(n + 1).fill(null).map(() => Array(n + 1).fill(0));

    function matrixChainMemo(i, j) {
        if (i === j) {
            m[i][j] = 0;
            return 0;
        }
        if (m[i][j] !== null) {
            return m[i][j];
        }
        m[i][j] = Infinity;
        for (let k = i; k < j; k++) {
            const cost = matrixChainMemo(i, k) + matrixChainMemo(k + 1, j) + p[i - 1] * p[k] * p[j];
            if (cost < m[i][j]) {
                m[i][j] = cost;
                s[i][j] = k;
            }
        }
        return m[i][j];
    }

    const minCost = matrixChainMemo(1, n);
    const optimalParens = printOptimalParenthesization(s, 1, n);
    return { minCost, optimalParenthesization: optimalParens };
}

// 3. Divide and Conquer (Recursive, Naive)
function matrixChainMultiplicationRecursive(p, i, j) {
    if (i === j) {
        return 0;
    }
    let minCost = Infinity;
    for (let k = i; k < j; k++) {
        const cost = matrixChainMultiplicationRecursive(p, i, k) +
            matrixChainMultiplicationRecursive(p, k + 1, j) +
            p[i - 1] * p[k] * p[j];
        if (cost < minCost) {
            minCost = cost;
        }
    }
    return minCost;
}

// 4.  Optimized DP with Space Optimization (Not applicable for MCM in the strictest sense, but showing the concept)
// Space optimization for DP problems often involves reducing the dimensions of the DP table.
//  MCM doesn't lend itself to this *typical* space optimization because the dependencies
//  in the table are more complex than just the previous row or column.  However, the concept
//  is important in DP, so I'll illustrate it with a simpler example (which is NOT MCM).
//
//  Example:  Finding the nth Fibonacci number using DP with space optimization
function fibonacciDPSpaceOptimized(n) {
    if (n <= 1) return n;
    let a = 0, b = 1;
    for (let i = 2; i <= n; i++) {
        const temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

// 5. Hybrid Approach: Memoization with Iterative Base Case Initialization
function matrixChainMultiplicationHybrid(p) {
    const n = p.length - 1;
    const m = Array(n + 1).fill(null).map(() => Array(n + 1).fill(null));
    const s = Array(n + 1).fill(null).map(() => Array(n + 1).fill(0));

    // Initialize base cases (i == j)
    for (let i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    function matrixChainMemoHybrid(i, j) {
        if (m[i][j] !== null) {
            return m[i][j];
        }

        m[i][j] = Infinity;
        for (let k = i; k < j; k++) {
            const cost = matrixChainMemoHybrid(i, k) + matrixChainMemoHybrid(k + 1, j) + p[i - 1] * p[k] * p[j];
            if (cost < m[i][j]) {
                m[i][j] = cost;
                s[i][j] = k;
            }
        }
        return m[i][j];
    }

    const minCost = matrixChainMemoHybrid(1, n);
    const optimalParens = printOptimalParenthesization(s, 1, n);
    return { minCost, optimalParenthesization: optimalParens };
}



// Example usage:
const dimensions = [10, 20, 50, 10, 30]; // Dimensions of matrices: A1(10x20), A2(20x50), A3(50x10), A4(10x30)

// 1. Standard Dynamic Programming
console.log("1. Standard Dynamic Programming (Tabulation):");
const resultDP = matrixChainMultiplicationDP(dimensions);
console.log("Minimum cost:", resultDP.minCost);
console.log("Optimal parenthesization:", resultDP.optimalParenthesization);
console.log("-" .repeat(40));

// 2. Memoization
console.log("2. Memoization (Top-Down):");
const resultMemo = matrixChainMultiplicationMemo(dimensions);
console.log("Minimum cost:", resultMemo.minCost);
console.log("Optimal parenthesization:", resultMemo.optimalParenthesization);
console.log("-" .repeat(40));

// 3. Divide and Conquer
console.log("3. Divide and Conquer (Recursive):");
const resultRecursive = matrixChainMultiplicationRecursive(dimensions, 1, dimensions.length - 1);
console.log("Minimum cost:", resultRecursive);
console.log("-" .repeat(40));

// 4. Space Optimized DP (Fibonacci Example - Concept Illustration):
console.log("4. Space Optimized DP (Fibonacci Example):");
const fibResult = fibonacciDPSpaceOptimized(10); // Calculate 10th Fibonacci number
console.log("10th Fibonacci number:", fibResult);
console.log("-" .repeat(40));

// 5. Hybrid Approach: Memoization with Iterative Base Case
console.log("5. Hybrid Approach (Memoization + Iterative Base Case):");
const resultHybrid = matrixChainMultiplicationHybrid(dimensions);
console.log("Minimum cost:", resultHybrid.minCost);
console.log("Optimal parenthesization:", resultHybrid.optimalParenthesization);
console.log("-" .repeat(40));

/*
 * Real-world Applications of Matrix Chain Multiplication:
 *
 * 1. Compiler Optimization:
 * - In optimizing compilers, matrix chain multiplication can be used to determine the optimal order
 * for evaluating a sequence of expressions involving matrix multiplications.  This minimizes
 * the number of operations and improves the efficiency of the generated code.
 * - Example:  A compiler might need to generate code to multiply several matrices.  MCM helps the
 * compiler decide the best order to perform these multiplications.
 *
 * 2.  Image Processing:
 * -  Certain image processing operations, such as transformations and compositing, can be
 * represented as matrix multiplications.  MCM can be employed to optimize the sequence of
 * these operations to reduce computational cost.
 * - Example:  Combining multiple image layers using matrix transformations.  MCM optimizes the order
 * of applying these transformations.
 *
 * 3.  Robotics:
 * -  In robotics, transformations representing robot movements and object positions can be
 * represented as matrices.  MCM can be used to optimize the sequence of transformations
 * involved in complex robotic tasks.
 * - Example:  Calculating the final position of a robot arm after a series of joint rotations.  MCM
 * optimizes the order of matrix multiplications representing these rotations.
 *
 * 4.  Financial Modeling:
 * -  Some financial models involve complex calculations with sequences of matrix operations.
 * MCM can be applied to optimize the order of these operations for better performance.
 * - Example:  Portfolio optimization calculations involving multiple asset correlations and weightings.
 *
 * 5.  Scientific Computing:
 * -  Various scientific computations, such as those in physics, engineering, and data analysis,
 * involve matrix operations.  MCM can be used to optimize the efficiency of these computations.
 * - Example:  Solving systems of equations or performing simulations with multiple matrix operations.
 */
