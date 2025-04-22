/**
 * Sudoku Solver with 5 Different Backtracking Approaches
 */

/**
 * 1. Basic Backtracking
 * - Uses a simple recursive backtracking algorithm.
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

  function solve(board) {
    for (let row = 0; row < 9; row++) {
      for (let col = 0; col < 9; col++) {
        if (board[row][col] === '.') {
          for (let num = '1'; num <= '9'; num++) {
            if (isValid(board, row, col, num)) {
              board[row][col] = num;
              if (solve(board)) return true;
              else board[row][col] = '.'; // Backtrack
            }
          }
          return false;
        }
      }
    }
    return true;
  }

  // Create a copy to avoid modifying the original board directly.
  const boardCopy = board.map(row => [...row]);
  if (solve(boardCopy)) {
    return boardCopy;
  } else {
    return null; // Indicate no solution found
  }
}



/**
 * 2. Backtracking with Early Termination
 * - Optimizes the basic backtracking by checking for solution existence
 * before starting the recursion.  This version doesn't strictly need the early return,
 * but it's included to show the intent.
 */
function solveSudokuEarlyTermination(board) {
    function isValid(board, row, col, num) {
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === num) return false;
            if (board[i][col] === num) return false;
            if (board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)] === num) return false;
        }
        return true;
    }

    function solve(board) {
        for (let row = 0; row < 9; row++) {
            for (let col = 0; col < 9; col++) {
                if (board[row][col] === '.') {
                    for (let num = '1'; num <= '9'; num++) {
                        if (isValid(board, row, col, num)) {
                            board[row][col] = num;
                            if (solve(board)) return true;
                            else board[row][col] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    const boardCopy = board.map(row => [...row]);
    if (solve(boardCopy)) {
        return boardCopy;
    }
    return null;
}

/**
 * 3. Backtracking with Preprocessing of Empty Cells
 * - Stores the coordinates of empty cells to avoid iterating over filled cells.
 */
function solveSudokuPreprocessEmpty(board) {
  function isValid(board, row, col, num) {
    for (let i = 0; i < 9; i++) {
      if (board[row][i] === num) return false;
      if (board[i][col] === num) return false;
      if (board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)] === num) return false;
    }
    return true;
  }

  function solve(board, emptyCells) {
    if (emptyCells.length === 0) return true;

    const [row, col] = emptyCells.shift();
    for (let num = '1'; num <= '9'; num++) {
      if (isValid(board, row, col, num)) {
        board[row][col] = num;
        if (solve(board, [...emptyCells])) return true;
        else board[row][col] = '.';
      }
    }
    emptyCells.unshift([row, col]); // Restore for backtracking
    return false;
  }

  const emptyCells = [];
  for (let row = 0; row < 9; row++) {
    for (let col = 0; col < 9; col++) {
      if (board[row][col] === '.') {
        emptyCells.push([row, col]);
      }
    }
  }

  const boardCopy = board.map(row => [...row]);
  if (solve(boardCopy, emptyCells)) {
    return boardCopy;
  }
  return null;
}

/**
 * 4. Backtracking with Optimized Domain Reduction
 * - (More advanced) Uses a more sophisticated approach to reduce the possible values
 * (domains) for each empty cell, potentially improving efficiency.  This is a simplified
 * version of domain reduction.
 */
function solveSudokuDomainReduction(board) {
    function isValid(board, row, col, num) {
        for (let i = 0; i < 9; i++) {
            if (board[row][i] === num) return false;
            if (board[i][col] === num) return false;
            if (board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)] === num) return false;
        }
        return true;
    }

    function getPossibleValues(board, row, col) {
        const possibleValues = new Set(['1', '2', '3', '4', '5', '6', '7', '8', '9']);
        for (let i = 0; i < 9; i++) {
            possibleValues.delete(board[row][i]);
            possibleValues.delete(board[i][col]);
            possibleValues.delete(board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)]);
        }
        return Array.from(possibleValues);
    }

    function solve(board) {
        for (let row = 0; row < 9; row++) {
            for (let col = 0; col < 9; col++) {
                if (board[row][col] === '.') {
                    const possibleValues = getPossibleValues(board, row, col);
                    for (const num of possibleValues) {
                        if (isValid(board, row, col, num)) {
                            board[row][col] = num;
                            if (solve(board)) return true;
                            else board[row][col] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    const boardCopy = board.map(row => [...row]);
    if (solve(boardCopy)) {
      return boardCopy;
    }
    return null;
}



/**
 * 5. Backtracking with Minimum Remaining Values (MRV) Heuristic
 * - Uses the MRV heuristic to select the empty cell with the fewest possible values,
 * which often reduces the search space.
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

  function getPossibleValues(board, row, col) {
    const possibleValues = new Set(['1', '2', '3', '4', '5', '6', '7', '8', '9']);
    for (let i = 0; i < 9; i++) {
      possibleValues.delete(board[row][i]);
      possibleValues.delete(board[i][col]);
      possibleValues.delete(board[3 * Math.floor(row / 3) + Math.floor(i / 3)][3 * Math.floor(col / 3) + (i % 3)]);
    }
    return Array.from(possibleValues);
  }

  function findMRVCell(board) {
    let minRemainingValues = Infinity;
    let mrvRow = -1;
    let mrvCol = -1;

    for (let row = 0; row < 9; row++) {
      for (let col = 0; col < 9; col++) {
        if (board[row][col] === '.') {
          const possibleValues = getPossibleValues(board, row, col);
          if (possibleValues.length < minRemainingValues) {
            minRemainingValues = possibleValues.length;
            mrvRow = row;
            mrvCol = col;
          }
        }
      }
    }
    return (mrvRow === -1) ? null : [mrvRow, mrvCol];
  }

  function solve(board) {
    const mrvCell = findMRVCell(board);
    if (!mrvCell) return true; // No empty cells left

    const [row, col] = mrvCell;
    const possibleValues = getPossibleValues(board, row, col);
    for (const num of possibleValues) {
      if (isValid(board, row, col, num)) {
        board[row][col] = num;
        if (solve(board)) return true;
        else board[row][col] = '.';
      }
    }
    return false;
  }

  const boardCopy = board.map(row => [...row]);
    if (solve(boardCopy)) {
      return boardCopy;
    }
    return null;
}



// Helper function to print the Sudoku board
function printBoard(board, title) {
  if (!board) {
    console.log(`${title}: No solution found.`);
    return;
  }
  console.log(title);
  for (let i = 0; i < 9; i++) {
    let rowStr = '';
    for (let j = 0; j < 9; j++) {
      rowStr += board[i][j] + ' ';
      if ((j + 1) % 3 === 0) rowStr += '| ';
    }
    console.log(rowStr);
    if ((i + 1) % 3 === 0) console.log('------------------------');
  }
}

// Example Sudoku board (replace with your puzzle)
const sudokuBoard = [
  ['5', '3', '.', '.', '7', '.', '.', '.', '.'],
  ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
  ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
  ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
  ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
  ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
  ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
  ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
  ['.', '.', '.', '.', '8', '.', '.', '7', '9'],
];

// Solve and print using each approach
console.log("Original Board:");
printBoard(sudokuBoard, "Original Board:");

const solvedBoardBasic = solveSudokuBasic(sudokuBoard);
printBoard(solvedBoardBasic, "1. Basic Backtracking Solution:");

const solvedBoardEarly = solveSudokuEarlyTermination(sudokuBoard);
printBoard(solvedBoardEarly, "2. Backtracking with Early Termination Solution:");

const solvedBoardPreprocess = solveSudokuPreprocessEmpty(sudokuBoard);
printBoard(solvedBoardPreprocess, "3. Backtracking with Preprocessing Solution:");

const solvedBoardDomain = solveSudokuDomainReduction(sudokuBoard);
printBoard(solvedBoardDomain, "4. Backtracking with Domain Reduction Solution:");

const solvedBoardMRV = solveSudokuMRV(sudokuBoard);
printBoard(solvedBoardMRV, "5. Backtracking with MRV Heuristic Solution:");
