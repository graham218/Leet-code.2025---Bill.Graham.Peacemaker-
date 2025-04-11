/**
 * Sudoku Solver with 5 Different Backtracking Approaches
 *
 * This file contains a JavaScript implementation of a Sudoku solver using five different backtracking approaches.
 * It demonstrates various techniques to solve Sudoku puzzles, providing a comprehensive understanding of backtracking
 * and optimization strategies.  The output for each approach will be printed to the console.
 */

/**
 * 1. Basic Backtracking
 * - The most straightforward backtracking approach.
 * - It tries each number (1-9) in each empty cell until it finds a valid one.
 * - If no valid number is found, it backtracks to the previous empty cell.
 */
function solveSudokuBasic(board) {
    function isValid(board, row, col, num) {
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === num) return false;
            if (board[i][col] === num) return false;
            if (board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)] === num) return false;
        }
        return true;
    }

    function findEmpty(board) {
        for (let row = 0; row < 9; row++) {
            for (let col = 0; col < 9; col++) {
                if (board[row][col] === 0) return [row, col];
            }
        }
        return null;
    }

    function solve() {
        const emptyCell = findEmpty(board);
        if (!emptyCell) return true; // Puzzle solved

        const [row, col] = emptyCell;
        for (let num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num)) {
                board[row][col] = num;
                if (solve()) return true; // Recursively solve the rest
                board[row][col] = 0;    // Backtrack
            }
        }
        return false; // No solution found for this branch
    }

    // Make a copy to avoid modifying the original board
    const boardCopy = board.map(row => [...row]);
    if (solve()) {
        return boardCopy;
    } else {
        return null;
    }
}



/**
 * 2. Backtracking with Forward Checking
 * - Improves upon basic backtracking by adding a "forward checking" step.
 * - Before placing a number, it checks if that number will leave any empty cell
 * in its row, column, or block with no possible valid numbers.
 */
function solveSudokuForwardChecking(board) {
    function isValid(board, row, col, num) {
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === num) return false;
            if (board[i][col] === num) return false;
            if (board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)] === num) return false;
        }
        return true;
    }

    function findEmpty(board) {
        for (let row = 0; row < 9; row++) {
            for (let col = 0; col < 9; col++) {
                if (board[row][col] === 0) return [row, col];
            }
        }
        return null;
    }

    function canPlace(board, row, col, num) {
        if (!isValid(board, row, col, num)) {
            return false;
        }

        // Forward checking: Check for domains of future variables
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === 0 && countPossibleValues(board, row, i) === 1 && i !== col) return false; //check row
            if (board[i][col] === 0 && countPossibleValues(board, i, col) === 1 && i !== row) return false; //check col
        }

        const boxRowStart = 3 * Math.floor(row / 3);
        const boxColStart = 3 * Math.floor(col / 3);
        for (let i = boxRowStart; i < boxRowStart + 3; i++) {
            for (let j = boxColStart; j < boxColStart + 3; j++) {
                if (board[i][j] === 0 && countPossibleValues(board, i, j) === 1 && (i !== row || j !== col)) return false;
            }
        }
        return true;
    }

    function countPossibleValues(board, row, col) {
        let count = 0;
        for (let num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num)) {
                count++;
            }
        }
        return count;
    }

    function solve() {
        const emptyCell = findEmpty(board);
        if (!emptyCell) return true;

        const [row, col] = emptyCell;
        for (let num = 1; num <= 9; num++) {
            if (canPlace(board, row, col, num)) { // Use canPlace instead of isValid
                board[row][col] = num;
                if (solve()) return true;
                board[row][col] = 0;
            }
        }
        return false;
    }
    const boardCopy = board.map(row => [...row]);
    if(solve()){
        return boardCopy;
    }
    else{
        return null;
    }
}


/**
 * 3. Backtracking with Minimum Remaining Values (MRV) Heuristic
 * - Uses a heuristic to select the next empty cell to fill.
 * - MRV chooses the cell with the fewest possible valid values.
 * - This reduces the branching factor and improves efficiency.
 */
function solveSudokuMRV(board) {
    function isValid(board, row, col, num) {
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === num) return false;
            if (board[i][col] === num) return false;
            if (board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)] === num) return false;
        }
        return true;
    }

    function findEmptyMRV(board) {
        let minRemaining = 10; // Initialize with a value greater than 9
        let bestRow = -1, bestCol = -1;

        for (let row = 0; row < 9; row++) {
            for (let col = 0; col < 9; col++) {
                if (board[row][col] === 0) {
                    let remaining = 0;
                    for (let num = 1; num <= 9; num++) {
                        if (isValid(board, row, col, num)) {
                            remaining++;
                        }
                    }
                    if (remaining < minRemaining) {
                        minRemaining = remaining;
                        bestRow = row;
                        bestCol = col;
                    }
                }
            }
        }
        return bestRow === -1 ? null : [bestRow, bestCol];
    }

    function solve() {
        const emptyCell = findEmptyMRV(board);
        if (!emptyCell) return true;

        const [row, col] = emptyCell;
        for (let num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num)) {
                board[row][col] = num;
                if (solve()) return true;
                board[row][col] = 0;
            }
        }
        return false;
    }
    const boardCopy = board.map(row => [...row]);
    if(solve()){
        return boardCopy;
    }
    else{
        return null;
    }
}

/**
 * 4. Backtracking with Least Constraining Value (LCV) Heuristic
 * -  Improves the ordering of values to try within a cell.
 * -  LCV chooses the value that restricts the fewest choices for neighboring cells.
 */

function solveSudokuLCV(board) {
    function isValid(board, row, col, num) {
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === num) return false;
            if (board[i][col] === num) return false;
            if (board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)] === num) return false;
        }
        return true;
    }

    function findEmpty(board) {
        for (let row = 0; row < 9; row++) {
            for (let col = 0; col < 9; col++) {
                if (board[row][col] === 0) return [row, col];
            }
        }
        return null;
    }

    function countAffectedValues(board, row, col, num) {
        let count = 0;
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === 0 && isValid(board, row, i, num)) count++;
            if (board[i][col] === 0 && isValid(board, i, col, num)) count++;
        }
        const boxRowStart = 3 * Math.floor(row / 3);
        const boxColStart = 3 * Math.floor(col / 3);
        for (let i = boxRowStart; i < boxRowStart + 3; i++) {
            for (let j = boxColStart; j < boxColStart + 3; j++) {
                if (board[i][j] === 0 && isValid(board, i, j, num)) count++;
            }
        }
        return count;
    }

    function getPossibleValuesLCV(board, row, col) {
        const values = [];
        for (let num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num)) {
                values.push({ num, count: countAffectedValues(board, row, col, num) });
            }
        }
        // Sort in ascending order of constraining value (least constraining value first)
        values.sort((a, b) => a.count - b.count);
        return values.map(v => v.num);
    }

    function solve() {
        const emptyCell = findEmpty(board);
        if (!emptyCell) return true;

        const [row, col] = emptyCell;
        const possibleValues = getPossibleValuesLCV(board, row, col); // Get LCV ordered values
        for (const num of possibleValues) {
            board[row][col] = num;
            if (solve()) return true;
            board[row][col] = 0;
        }
        return false;
    }
    const boardCopy = board.map(row => [...row]);
      if (solve()) {
        return boardCopy;
    } else {
        return null;
    }
}



/**
 * 5. Optimized Backtracking (Combining MRV and LCV)
 * - Combines the MRV and LCV heuristics for maximum efficiency.
 * - Selects the cell with the fewest remaining values (MRV) and
 * tries the least constraining value (LCV) in that cell.
 */
function solveSudokuOptimized(board) {
    function isValid(board, row, col, num) {
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === num) return false;
            if (board[i][col] === num) return false;
            if (board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)] === num) return false;
        }
        return true;
    }

    function findEmptyMRV(board) {
        let minRemaining = 10;
        let bestRow = -1, bestCol = -1;

        for (let row = 0; row < 9; row++) {
            for (let col = 0; col < 9; col++) {
                if (board[row][col] === 0) {
                    let remaining = 0;
                    for (let num = 1; num <= 9; num++) {
                        if (isValid(board, row, col, num)) {
                            remaining++;
                        }
                    }
                    if (remaining < minRemaining) {
                        minRemaining = remaining;
                        bestRow = row;
                        bestCol = col;
                    }
                }
            }
        }
        return bestRow === -1 ? null : [bestRow, bestCol];
    }

    function countAffectedValues(board, row, col, num) {
        let count = 0;
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === 0 && isValid(board, row, i, num)) count++;
            if (board[i][col] === 0 && isValid(board, i, col, num)) count++;
        }
        const boxRowStart = 3 * Math.floor(row / 3);
        const boxColStart = 3 * Math.floor(col / 3);
        for (let i = boxRowStart; i < boxRowStart + 3; i++) {
            for (let j = boxColStart; j < boxColStart + 3; j++) {
                if (board[i][j] === 0 && isValid(board, i, j, num)) count++;
            }
        }
        return count;
    }

    function getPossibleValuesLCV(board, row, col) {
        const values = [];
        for (let num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num)) {
                values.push({ num, count: countAffectedValues(board, row, col, num) });
            }
        }
        values.sort((a, b) => a.count - b.count);
        return values.map(v => v.num);
    }

    function solve() {
        const emptyCell = findEmptyMRV(board);
        if (!emptyCell) return true;

        const [row, col] = emptyCell;
        const possibleValues = getPossibleValuesLCV(board, row, col);
        for (const num of possibleValues) {
            board[row][col] = num;
            if (solve()) return true;
            board[row][col] = 0;
        }
        return false;
    }
    const boardCopy = board.map(row => [...row]);
    if (solve()) {
        return boardCopy;
    } else {
        return null;
    }
}



// Example Sudoku Board (0 represents empty cells)
const sudokuBoard = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
];

// Function to print the Sudoku board
function printBoard(board, title) {
    if (!board) {
        console.log(`${title}: No solution found.`);
        return;
    }
    console.log(title);
    for (let row = 0; row < 9; row++) {
        let rowString = '';
        for (let col = 0; col < 9; col++) {
            rowString += board[row][col] + ' ';
            if ((col + 1) % 3 === 0) rowString += '| ';
        }
        console.log(rowString);
        if ((row + 1) % 3 === 0) console.log('------------------------');
    }
}

// Solve and print using each approach
console.log("Original Board:");
printBoard(sudokuBoard, "Original Board:");

const solvedBoardBasic = solveSudokuBasic(sudokuBoard);
printBoard(solvedBoardBasic, "1. Basic Backtracking Solution:");

const solvedBoardForwardChecking = solveSudokuForwardChecking(sudokuBoard);
printBoard(solvedBoardForwardChecking, "2. Backtracking with Forward Checking Solution:");

const solvedBoardMRV = solveSudokuMRV(sudokuBoard);
printBoard(solvedBoardMRV, "3. Backtracking with MRV Heuristic Solution:");

const solvedBoardLCV = solveSudokuLCV(sudokuBoard);
printBoard(solvedBoardLCV, "4. Backtracking with LCV Heuristic Solution:");

const solvedBoardOptimized = solveSudokuOptimized(sudokuBoard);
printBoard(solvedBoardOptimized, "5. Optimized Backtracking (MRV + LCV) Solution:");
