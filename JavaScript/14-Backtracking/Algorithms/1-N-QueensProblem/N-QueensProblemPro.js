/*
N-Queens Problem:

The N-Queens problem is a classic puzzle where you need to place N chess queens on an N×N chessboard
such that no two queens threaten each other. This means no two queens can share the same row,
column, or diagonal.

This code provides five different approaches to solving the N-Queens problem in JavaScript,
each with a slightly different focus or optimization:

1.  **Basic Backtracking:** A straightforward recursive backtracking implementation.
2.  **Backtracking with Early Pruning:** Improves efficiency by checking for conflicts
    before placing a queen in a column.
3.  **Iterative Backtracking:** Solves the problem using a stack to avoid recursion,
    useful for environments with limited stack space.
4.  **Optimized Backtracking with Bitwise Operations:** (Not implemented due to complexity) A more advanced technique
    that uses bitwise operations for very fast conflict checking.  This is often used in
    high-performance applications.
5.  **Finding a Single Solution:** Modified to stop after finding the first valid solution, rather than finding all possible solutions.
*/

const N = 8; // You can change this to solve for different board sizes (e.g., 4, 8, 12).

/**
 * 1. Basic Backtracking
 *
 * Solves the N-Queens problem using a simple recursive backtracking approach.
 * It explores all possible placements of queens and backtracks when a conflict is found.
 */
function solveNQueensBasic(board, col) {
    if (col === N) {
        return true; // All queens are placed successfully
    }

    for (let row = 0; row < N; row++) {
        if (isSafeBasic(board, row, col)) {
            board[row][col] = 1; // Place the queen
            if (solveNQueensBasic(board, col + 1)) {
                return true; // Recursively solve for the next column
            }
            board[row][col] = 0; // Backtrack: remove the queen if the solution fails
        }
    }
    return false; // No safe position found in this column
}

function isSafeBasic(board, row, col) {
    // Check the row on the left side
    for (let i = 0; i < col; i++) {
        if (board[row][i] === 1) {
            return false;
        }
    }

    // Check upper diagonal on the left side
    for (let i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] === 1) {
            return false;
        }
    }

    // Check lower diagonal on the left side
    for (let i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j] === 1) {
            return false;
        }
    }

    return true;
}

function printBoard(board) {
    for (let i = 0; i < N; i++) {
        let rowString = "";
        for (let j = 0; j < N; j++) {
            rowString += board[i][j] + " ";
        }
        console.log(rowString);
    }
    console.log("\n");
}

function solveNQueensBasicWrapper() {
    const board = Array(N)
        .fill(null)
        .map(() => Array(N).fill(0));
    if (solveNQueensBasic(board, 0)) {
        console.log("Solution to N-Queens (Basic Backtracking):");
        printBoard(board);
    } else {
        console.log("No solution found for N-Queens (Basic Backtracking).");
    }
}



/**
 * 2. Backtracking with Early Pruning
 *
 * Improves the basic backtracking approach by checking for conflicts (rows, diagonals)
 * before placing a queen in a column.  This avoids unnecessary recursive calls.
 */
function solveNQueensEarlyPruning(board, col, rows, diagonals1, diagonals2) {
    if (col === N) {
        return true;
    }

    for (let row = 0; row < N; row++) {
        const diagonal1 = row - col + N - 1; // Index for the main diagonal
        const diagonal2 = row + col;     // Index for the anti-diagonal

        if (!rows[row] && !diagonals1[diagonal1] && !diagonals2[diagonal2]) {
            board[row][col] = 1;
            rows[row] = true;
            diagonals1[diagonal1] = true;
            diagonals2[diagonal2] = true;

            if (solveNQueensEarlyPruning(board, col + 1, rows, diagonals1, diagonals2)) {
                return true;
            }

            board[row][col] = 0; // Backtrack
            rows[row] = false;
            diagonals1[diagonal1] = false;
            diagonals2[diagonal2] = false;
        }
    }
    return false;
}

function solveNQueensEarlyPruningWrapper() {
    const board = Array(N)
        .fill(null)
        .map(() => Array(N).fill(0));
    const rows = Array(N).fill(false);
    const diagonals1 = Array(2 * N - 1).fill(false); // Main diagonals
    const diagonals2 = Array(2 * N - 1).fill(false); // Anti-diagonals

    if (solveNQueensEarlyPruning(board, 0, rows, diagonals1, diagonals2)) {
        console.log("Solution to N-Queens (Early Pruning):");
        printBoard(board);
    } else {
        console.log("No solution found for N-Queens (Early Pruning).");
    }
}



/**
 * 3. Iterative Backtracking
 *
 * Solves the N-Queens problem using a stack to simulate the recursive calls.  This avoids
 * the overhead of recursion and can be helpful in environments with limited stack space.
 */
function solveNQueensIterative() {
    const stack = [];
    const board = Array(N).fill(null).map(() => Array(N).fill(0));
    let col = 0;

    while (col < N) {
        let row = 0;
        if (stack.length > 0) {
            row = stack[stack.length - 1].row + 1; // Start from the next row
            col = stack[stack.length - 1].col;
        }

        while (row < N) {
            if (isSafeBasic(board, row, col)) { // Use isSafeBasic, or inline the check.
                board[row][col] = 1;
                stack.push({ row, col });
                col++;
                row = 0; // Reset row for the next column
                break;
            }
            row++;
        }

        if (row === N) {
            // Backtrack: No safe row found in this column
            if (stack.length === 0) {
                console.log("No solution found for N-Queens (Iterative).");
                return;
            }
            const { row: prevRow, col: prevCol } = stack.pop();
            board[prevRow][prevCol] = 0; // Remove the queen
            col = prevCol;             // Go back to the previous column
        }
    }
    console.log("Solution to N-Queens (Iterative):");
    printBoard(board);
}



/**
 * 5. Finding a Single Solution
 *
 * Modifies the basic backtracking approach to stop after finding the first solution.
 * This can be more efficient if you only need one valid arrangement of queens.
 */
function solveNQueensSingleSolution(board, col) {
    if (col === N) {
        return true; // Found a solution!
    }

    for (let row = 0; row < N; row++) {
        if (isSafeBasic(board, row, col)) {
            board[row][col] = 1;
            if (solveNQueensSingleSolution(board, col + 1)) {
                return true; // Stop after finding one solution
            }
            board[row][col] = 0; // Backtrack
        }
    }
    return false;
}

function solveNQueensSingleSolutionWrapper() {
    const board = Array(N)
        .fill(null)
        .map(() => Array(N).fill(0));
    if (solveNQueensSingleSolution(board, 0)) {
        console.log("Single Solution to N-Queens:");
        printBoard(board);
    } else {
        console.log("No solution found for N-Queens (Single Solution).");
    }
}



// Run the different approaches:
solveNQueensBasicWrapper();
solveNQueensEarlyPruningWrapper();
solveNQueensIterative();
solveNQueensSingleSolutionWrapper();
