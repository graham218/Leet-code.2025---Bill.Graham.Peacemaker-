/*
N-Queens Problem:

The N-Queens problem is a classic puzzle where you need to place N queens on an N x N chessboard
such that no two queens attack each other. This means no two queens can be in the same row,
column, or diagonal.

This code provides five different JavaScript approaches to solve the N-Queens problem using backtracking:

1.  **Simple Backtracking:** The basic recursive backtracking approach.
2.  **Backtracking with Early Pruning:** Improves efficiency by checking for conflicts before placing a queen.
3.  **Backtracking with Optimized Conflict Check:** Further optimizes conflict detection using sets.
4.  **Iterative Backtracking:** Solves the problem using a stack instead of recursion.
5. **Backtracking with Bit Manipulation**: Uses bit manipulation to optimize the conflict checks.

Each approach will find all possible solutions to the N-Queens problem and log them to the console.
*/

/**
 * Helper function to print the chessboard configuration in a user-friendly format.
 *
 * @param {number[][]} board - A 2D array representing the chessboard.  A 1 indicates a queen, 0 is empty.
 * @returns {string[]} An array of strings, where each string represents a row of the board.
 */
function printBoard(board) {
    const n = board.length;
    const solution = [];
    for (let i = 0; i < n; i++) {
        let rowString = '';
        for (let j = 0; j < n; j++) {
            rowString += board[i][j] === 1 ? 'Q' : '.';
        }
        solution.push(rowString);
    }
    return solution;
}

// 1. Simple Backtracking
/**
 * Solves the N-Queens problem using simple backtracking.
 *
 * @param {number} n - The size of the chessboard.
 * @returns {string[][][]} An array of solutions, where each solution is a board configuration.
 */
function solveNQueensSimple(n) {
    const board = Array(n).fill(null).map(() => Array(n).fill(0));
    const solutions = [];

    function backtrack(row) {
        if (row === n) {
            solutions.push(printBoard(board));
            return;
        }

        for (let col = 0; col < n; col++) {
            board[row][col] = 1;
            if (isValid(board, row, col)) {
                backtrack(row + 1);
            }
            board[row][col] = 0; // Backtrack: Remove the queen
        }
    }

    /**
     * Checks if placing a queen at the given row and column is valid.
     *
     * @param {number[][]} board - The current board configuration.
     * @param {number} row - The row to check.
     * @param {number} col - The column to check.
     * @returns {boolean} True if the placement is valid, false otherwise.
     */
    function isValid(board, row, col) {
        for (let i = 0; i < row; i++) {
            if (board[i][col] === 1) {
                return false; // Check column
            }
            if (col - (row - i) >= 0 && board[i][col - (row - i)] === 1) {
                return false; // Check left diagonal
            }
            if (col + (row - i) < board.length && board[i][col + (row - i)] === 1) {
                return false; // Check right diagonal
            }
        }
        return true;
    }

    backtrack(0);
    return solutions;
}



// 2. Backtracking with Early Pruning
/**
 * Solves the N-Queens problem using backtracking with early pruning.
 * This version checks for conflicts *before* placing the queen.
 *
 * @param {number} n - The size of the chessboard.
 * @returns {string[][][]} An array of solutions.
 */
function solveNQueensEarlyPruning(n) {
    const board = Array(n).fill(null).map(() => Array(n).fill(0));
    const solutions = [];

    function backtrack(row) {
        if (row === n) {
            solutions.push(printBoard(board));
            return;
        }

        for (let col = 0; col < n; col++) {
            if (isValidEarlyPruning(board, row, col)) { // Check *before* placing
                board[row][col] = 1;
                backtrack(row + 1);
                board[row][col] = 0;
            }
        }
    }

    function isValidEarlyPruning(board, row, col) {
      for (let i = 0; i < row; i++) {
        if (board[i][col] === 1) {
          return false;
        }
        if (col - (row - i) >= 0 && board[i][col - (row - i)] === 1) {
          return false;
        }
        if (col + (row - i) < board.length && board[i][col + (row - i)] === 1) {
          return false;
        }
      }
      return true;
    }

    backtrack(0);
    return solutions;
}



// 3. Backtracking with Optimized Conflict Check
/**
 * Solves the N-Queens problem using backtracking with optimized conflict checks using Sets.
 *
 * @param {number} n - The size of the chessboard.
 * @returns {string[][][]} An array of solutions.
 */
function solveNQueensOptimized(n) {
    const board = Array(n).fill(null).map(() => Array(n).fill(0));
    const solutions = [];
    const cols = new Set();
    const diagonals1 = new Set(); // row - col
    const diagonals2 = new Set(); // row + col

    function backtrack(row) {
        if (row === n) {
            solutions.push(printBoard(board));
            return;
        }

        for (let col = 0; col < n; col++) {
            const diag1 = row - col;
            const diag2 = row + col;

            if (!cols.has(col) && !diagonals1.has(diag1) && !diagonals2.has(diag2)) {
                board[row][col] = 1;
                cols.add(col);
                diagonals1.add(diag1);
                diagonals2.add(diag2);
                backtrack(row + 1);
                board[row][col] = 0; // Backtrack
                cols.delete(col);
                diagonals1.delete(diag1);
                diagonals2.delete(diag2);
            }
        }
    }

    backtrack(0);
    return solutions;
}

// 4. Iterative Backtracking
/**
 * Solves the N-Queens problem using iterative backtracking with a stack.
 *
 * @param {number} n - The size of the chessboard.
 * @returns {string[][][]} An array of solutions.
 */
function solveNQueensIterative(n) {
    const solutions = [];
    const stack = []; // Stack to store row and column positions
    const board = Array(n).fill(null).map(() => Array(n).fill(0));

    let row = 0;
    while (row < n) {
        let col = 0;
        if (stack.length > 0) {
          col = stack[stack.length-1].col + 1;
        }
        while (col < n) {
            if (row < n && isValidIterative(board, row, col)) {
                board[row][col] = 1;
                stack.push({ row, col });
                row++;
                col = 0; // Reset column for the next row
                break;
            }
            col++;
        }
        if (col === n) {
            // Backtrack: If no valid column found in current row, pop from stack
            if (stack.length === 0) {
                return solutions; // No more solutions
            }
            const { row: prevRow, col: prevCol } = stack.pop();
            board[prevRow][prevCol] = 0; // Clear the queen
            row = prevRow;          // Go back to the previous row
        }
    }
    if (stack.length === n){
      solutions.push(printBoard(board));
      return solutions;
    }
}

/**
 * Checks if a position is valid for the iterative approach.
 */
function isValidIterative(board, row, col) {
    for (let i = 0; i < row; i++) {
        if (board[i][col] === 1) return false;
        if (col - (row - i) >= 0 && board[i][col - (row - i)] === 1) return false;
        if (col + (row - i) < board.length && board[i][col + (row - i)] === 1) return false;
    }
    return true;
}

// 5. Backtracking with Bit Manipulation
/**
 * Solves the N-Queens problem using backtracking with bit manipulation for optimized conflict checks.
 *
 * @param {number} n - The size of the chessboard.
 * @returns {string[][][]} An array of solutions.
 */
function solveNQueensBits(n) {
    const solutions = [];
    const board = Array(n).fill(null).map(() => Array(n).fill(0));

    let cols = 0;          // Bitmask for occupied columns
    let diagonals1 = 0;    // Bitmask for occupied left diagonals (row - col + n - 1)
    let diagonals2 = 0;    // Bitmask for occupied right diagonals (row + col)

    function backtrack(row) {
        if (row === n) {
            solutions.push(printBoard(board));
            return;
        }

        for (let col = 0; col < n; col++) {
            const colBit = 1 << col;
            const diag1Bit = 1 << (row - col + n - 1);
            const diag2Bit = 1 << (row + col);

            if (!(cols & colBit) && !(diagonals1 & diag1Bit) && !(diagonals2 & diag2Bit)) {
                board[row][col] = 1;
                cols |= colBit;
                diagonals1 |= diag1Bit;
                diagonals2 |= diag2Bit;
                backtrack(row + 1);
                board[row][col] = 0;
                cols &= ~colBit;             // Clear the bit
                diagonals1 &= ~diag1Bit;
                diagonals2 &= ~diag2Bit;
            }
        }
    }

    backtrack(0);
    return solutions;
}



// Example usage for N = 8:
const n = 8;

console.log(`\nN-Queens Solutions for N = ${n}:`);

console.log("\n1. Simple Backtracking:");
const solutionsSimple = solveNQueensSimple(n);
console.log("Number of solutions:", solutionsSimple.length);
// console.log(solutionsSimple); // Print all solutions (can be large for N > 4)

console.log("\n2. Backtracking with Early Pruning:");
const solutionsEarlyPruning = solveNQueensEarlyPruning(n);
console.log("Number of solutions:", solutionsEarlyPruning.length);
// console.log(solutionsEarlyPruning);

console.log("\n3. Backtracking with Optimized Conflict Check (Sets):");
const solutionsOptimized = solveNQueensOptimized(n);
console.log("Number of solutions:", solutionsOptimized.length);
// console.log(solutionsOptimized);

console.log("\n4. Iterative Backtracking:");
const solutionsIterative = solveNQueensIterative(n);
console.log("Number of solutions:", solutionsIterative.length);
// console.log(solutionsIterative);

console.log("\n5. Backtracking with Bit Manipulation:");
const solutionsBits = solveNQueensBits(n);
console.log("Number of solutions:", solutionsBits.length);
// console.log(solutionsBits);
