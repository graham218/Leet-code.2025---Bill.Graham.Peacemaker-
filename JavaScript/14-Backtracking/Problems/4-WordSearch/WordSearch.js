/*
Word Search Problem:

Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example 1:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Example 2:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Example 3:
Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false

Constraints:
m == board.length
n == board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board consists of only uppercase and lowercase English letters.
word consists of only uppercase and lowercase English letters.
*/

/**
 * Approach 1: Basic Backtracking
 * - Uses a recursive helper function to explore possible paths in the board.
 * - Marks visited cells to avoid revisiting them in the same path.
 */
function exist1(board, word) {
  const rows = board.length;
  const cols = board[0].length;

  function backtrack(row, col, index) {
    if (index === word.length) {
      return true;
    }

    if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] !== word[index]) {
      return false;
    }

    const temp = board[row][col];
    board[row][col] = '#'; // Mark as visited
    const found = backtrack(row + 1, col, index + 1) ||
                  backtrack(row - 1, col, index + 1) ||
                  backtrack(row, col + 1, index + 1) ||
                  backtrack(row, col - 1, index + 1);
    board[row][col] = temp; // Restore the original character
    return found;
  }

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (backtrack(i, j, 0)) {
        return true;
      }
    }
  }
  return false;
}

/**
 * Approach 2: Backtracking with Early Termination
 * - Optimizes the basic backtracking by adding a check for early termination.
 * - If a path is found, it immediately returns true without exploring other paths.
 */
function exist2(board, word) {
  const rows = board.length;
  const cols = board[0].length;

  function backtrack(row, col, index) {
    if (index === word.length) {
      return true;
    }

    if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] !== word[index]) {
      return false;
    }

    const temp = board[row][col];
    board[row][col] = '#';
    const found = backtrack(row + 1, col, index + 1) ||
                  backtrack(row - 1, col, index + 1) ||
                  backtrack(row, col + 1, index + 1) ||
                  backtrack(row, col - 1, index + 1);
    board[row][col] = temp;
    return found;
  }

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (backtrack(i, j, 0)) {
        return true;
      }
    }
  }
  return false;
}

/**
 * Approach 3: Backtracking with Visited Array
 * - Uses a separate 2D array to keep track of visited cells.
 * - Avoids modifying the original board, preserving its content.
 */
function exist3(board, word) {
  const rows = board.length;
  const cols = board[0].length;
  const visited = Array(rows).fill(null).map(() => Array(cols).fill(false));

  function backtrack(row, col, index) {
    if (index === word.length) {
      return true;
    }

    if (row < 0 || row >= rows || col < 0 || col >= cols || visited[row][col] || board[row][col] !== word[index]) {
      return false;
    }

    visited[row][col] = true;
    const found = backtrack(row + 1, col, index + 1) ||
                  backtrack(row - 1, col, index + 1) ||
                  backtrack(row, col + 1, index + 1) ||
                  backtrack(row, col - 1, index + 1);
    visited[row][col] = false;
    return found;
  }

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (backtrack(i, j, 0)) {
        return true;
      }
    }
  }
  return false;
}

/**
 * Approach 4: Iterative Backtracking with Stack
 * - Uses a stack to simulate the recursive calls in backtracking.
 * - Stores the current row, column, and word index in the stack.
 */
function exist4(board, word) {
  const rows = board.length;
  const cols = board[0].length;
  const stack = [];

  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < cols; j++) {
      if (board[i][j] === word[0]) {
        stack.push([i, j, 0, new Set([i * cols + j])]); // Store row, col, index, visited set
        while (stack.length > 0) {
          const [row, col, index, visited] = stack.pop();

          if (index === word.length - 1) {
            return true;
          }

          const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];
          for (const [dr, dc] of directions) {
            const newRow = row + dr;
            const newCol = col + dc;
            const newIndex = index + 1;
            const cellKey = newRow * cols + newCol;

            if (newRow >= 0 && newRow < rows && newCol < cols && newCol >= 0 &&
                board[newRow][newCol] === word[newIndex] && !visited.has(cellKey)) {
              const newVisited = new Set(visited); // Create a copy!
              newVisited.add(cellKey);
              stack.push([newRow, newCol, newIndex, newVisited]);
            }
          }
        }
      }
    }
  }
  return false;
}

/**
 * Approach 5: Optimized Iterative Backtracking
 * - Combines the iterative approach with the visited array optimization.
 * - Uses a stack and a visited array to avoid modifying the board and improve efficiency.
 */
function exist5(board, word) {
    const rows = board.length;
    const cols = board[0].length;
    const stack = [];
    const visited = Array(rows).fill(null).map(() => Array(cols).fill(false));

    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (board[i][j] === word[0]) {
                stack.push([i, j, 0]);
                visited[i][j] = true; // Mark the starting cell as visited
                while (stack.length > 0) {
                    const [row, col, index] = stack.pop();

                    if (index === word.length - 1) {
                        return true;
                    }

                    const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];
                    for (const [dr, dc] of directions) {
                        const newRow = row + dr;
                        const newCol = col + dc;
                        const nextIndex = index + 1;

                        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                            !visited[newRow][newCol] && board[newRow][newCol] === word[nextIndex]) {
                            stack.push([newRow, newCol, nextIndex]);
                            visited[newRow][newCol] = true; // Mark the next cell as visited
                        }
                    }
                }
                // Reset visited array for the next search
                for (let r = 0; r < rows; r++) {
                  for (let c = 0; c < cols; c++) {
                    visited[r][c] = false;
                  }
                }
            }
        }
    }
    return false;
}



// Example Usage and Output
const board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]];
const word1 = "ABCCED";
const word2 = "SEE";
const word3 = "ABCB";

console.log("Approach 1 (Basic Backtracking):");
console.log("Word 1:", exist1(board, word1)); // Output: true
console.log("Word 2:", exist1(board, word2)); // Output: true
console.log("Word 3:", exist1(board, word3)); // Output: false

console.log("\nApproach 2 (Backtracking with Early Termination):");
console.log("Word 1:", exist2(board, word1)); // Output: true
console.log("Word 2:", exist2(board, word2)); // Output: true
console.log("Word 3:", exist2(board, word3)); // Output: false

console.log("\nApproach 3 (Backtracking with Visited Array):");
console.log("Word 1:", exist3(board, word1)); // Output: true
console.log("Word 2:", exist3(board, word2)); // Output: true
console.log("Word 3:", exist3(board, word3)); // Output: false

console.log("\nApproach 4 (Iterative Backtracking with Stack):");
console.log("Word 1:", exist4(board, word1)); // Output: true
console.log("Word 2:", exist4(board, word2)); // Output: true
console.log("Word 3:", exist4(board, word3)); // Output: false

console.log("\nApproach 5 (Optimized Iterative Backtracking):");
console.log("Word 1:", exist5(board, word1)); // Output: true
console.log("Word 2:", exist5(board, word2)); // Output: true
console.log("Word 3:", exist5(board, word3)); // Output: false
