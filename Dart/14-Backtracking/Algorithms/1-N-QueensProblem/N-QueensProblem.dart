import 'dart:math'; // Import for the max function

void main() {
  int n = 8; // Change N value as needed.  This sets the size of the chessboard (n x n).

  print("\nBacktracking Approach:");
  solveNQueensBacktracking(n); // Calls the backtracking solution to the N-Queens problem.

  print("\nBitmasking Optimization:");
  solveNQueensBitmasking(n); // Calls the bitmasking solution, an optimized version of backtracking.

  print("\nBranch and Bound:");
  solveNQueensBranchAndBound(n); // Calls the branch and bound solution, another optimization technique.

  print("\nHeuristic Approach (Local Search):");
  solveNQueensLocalSearch(n); // Calls the local search solution, which uses a heuristic approach.

  print("\nConstraint Programming:");
  solveNQueensConstraintProgramming(n); // Calls the constraint programming solution.
}

// 1. Backtracking Approach
//
//   * The most straightforward approach to solving the N-Queens problem.
//   * It explores all possible placements of queens, step by step.
//   * If a placement leads to a conflict, it backtracks (undoes the placement) and tries a different one.
//   * Guarantees to find all possible solutions, but can be slow for larger values of N.
void solveNQueensBacktracking(int n) {
  List<int> board = List.filled(n, -1); // Initialize an empty board.  -1 indicates no queen in that row.
  _backtrack(0, n, board); // Start the recursive backtracking process from the first row (row 0).
}

// _backtrack: Recursive function to find solutions using backtracking.
//
//   * row: The current row we are trying to place a queen in.
//   * n: The size of the board.
//   * board: A list representing the board.  board[i] is the column of the queen in row i.
void _backtrack(int row, int n, List<int> board) {
  if (row == n) { // Base case: If we have placed queens in all rows (0 to n-1), we have a solution.
    print(board); // Print the solution (the column position of the queen in each row).
    return; // Stop the recursion for this branch.
  }
  for (int col = 0; col < n; col++) { // Try placing a queen in each column of the current row.
    if (_isSafe(board, row, col)) { // Check if it's safe to place a queen at (row, col).
      board[row] = col; // Place the queen in the current row and column.
      _backtrack(row + 1, n, board); // Recursively try to place queens in the next row.
      board[row] = -1; // Backtrack: Remove the queen from this position to try other columns.
    }
  }
}

// _isSafe: Checks if it's safe to place a queen at a given position.
//
//   * board: The current state of the board.
//   * row: The row where we want to place the queen.
//   * col: The column where we want to place the queen.
//   * Returns: true if it's safe, false otherwise.
bool _isSafe(List<int> board, int row, int col) {
  for (int i = 0; i < row; i++) { // Check for conflicts with queens in previous rows.
    // Two conditions for a conflict:
    // 1.  The queen is in the same column: board[i] == col
    // 2.  The queen is on the same diagonal: (row - i).abs() == (col - board[i]).abs()
    if (board[i] == col || (row - i).abs() == (col - board[i]).abs()) {
      return false; // If there is a conflict, it's not safe.
    }
  }
  return true; // If no conflicts, it's safe.
}

// 2. Bitmasking Optimization
//
//   * An optimized version of backtracking that uses bitwise operations to represent the board.
//   * It's generally faster than the standard backtracking approach.
//   * Uses bit manipulation to efficiently track which positions are under attack.
void solveNQueensBitmasking(int n) {
  _solveBitmask(n, 0, 0, 0, 0); // Start the recursive bitmasking process.
}

// _solveBitmask: Recursive function to find solutions using bitmasking.
//
//   * n: The size of the board.
//   * row: The current row.
//   * cols: A bitmask representing columns that are under attack.
//   * diags: A bitmask representing diagonals that are under attack.
//   * antiDiags: A bitmask representing anti-diagonals that are under attack.
void _solveBitmask(int n, int row, int cols, int diags, int antiDiags) {
  if (row == n) { // Base case: All queens are placed.
    print("Solution Found"); // Print that a solution is found.  You could reconstruct the board from the bitmasks if needed.
    return;
  }
  // Calculate the available positions in the current row using bitwise operations.
  // (1 << n) - 1 creates a bitmask with n 1s (representing all columns).
  // ~(cols | diags | antiDiags) creates a bitmask where 1s represent safe columns.
  int available = (~(cols | diags | antiDiags)) & ((1 << n) - 1);
  while (available > 0) {
    // Get the least significant bit (LSB), which represents the rightmost available position.
    int pos = available & -available;
    available -= pos; // Remove the LSB from the available positions.
    // Recursively call _solveBitmask for the next row, updating the bitmasks to reflect the new queen placement.
    _solveBitmask(n, row + 1, cols | pos, (diags | pos) << 1, (antiDiags | pos) >> 1);
  }
}

// 3. Branch and Bound
//
//   * Similar to backtracking, but it uses bounding functions to avoid exploring unnecessary branches.
//   * It can be more efficient than backtracking, especially for larger problems.
//   * Keeps track of columns, diagonals, and anti-diagonals that are already occupied.
void solveNQueensBranchAndBound(int n) {
  List<bool> cols = List.filled(n, false); // Array to track if a column is occupied.
  List<bool> diags = List.filled(2 * n, false); // Array to track if a diagonal is occupied.
  List<bool> antiDiags = List.filled(2 * n, false); // Array to track if an anti-diagonal is occupied.
  _branchAndBound(0, n, cols, diags, antiDiags); // Start the recursive branch and bound process.
}

// _branchAndBound: Recursive function to find solutions using branch and bound.
//
//   * row: The current row.
//   * n: The size of the board.
//   * cols: Array indicating occupied columns.
//   * diags: Array indicating occupied diagonals.
//   * antiDiags: Array indicating occupied anti-diagonals.
void _branchAndBound(int row, int n, List<bool> cols, List<bool> diags, List<bool> antiDiags) {
  if (row == n) { // Base case: All queens are placed.
    print("Solution Found");
    return;
  }
  for (int col = 0; col < n; col++) {
    // Check if the current position (row, col) is safe.
    if (!cols[col] && !diags[row - col + n] && !antiDiags[row + col]) {
      // If safe, mark the column, diagonal, and anti-diagonal as occupied.
      cols[col] = diags[row - col + n] = antiDiags[row + col] = true;
      _branchAndBound(row + 1, n, cols, diags, antiDiags); // Recursively call for the next row.
      // Backtrack: Unmark the column, diagonal, and anti-diagonal to explore other possibilities.
      cols[col] = diags[row - col + n] = antiDiags[row + col] = false;
    }
  }
}

// 4. Heuristic Approach (Local Search using Min-Conflicts Algorithm)
//
//   * A heuristic approach that doesn't guarantee to find a solution, but it's often faster than backtracking for large N.
//   * It starts with a random placement of queens and iteratively tries to reduce the number of conflicts.
//   * The Min-Conflicts algorithm is a type of local search.
void solveNQueensLocalSearch(int n) {
  List<int> board = List.generate(n, (i) => i); // Initialize the board with queens in the diagonal.
  board.shuffle(); // Shuffle the board to get a random initial placement.

  for (int i = 0; i < 1000; i++) { // Iterate a fixed number of times (max iterations).
    int row = _getMostConflictedRow(board, n); // Find the row with the most conflicts.
    if (row == -1) { // If there are no conflicts, we have a solution.
      print(board);
      return;
    }
    board[row] = _getBestColumn(board, row, n); // Move the queen in the most conflicted row to the column that minimizes conflicts.
  }
  print("Local search failed to find solution."); // If the loop finishes without finding a solution.
}

// _getMostConflictedRow: Finds the row with the maximum number of conflicts.
//
//   * board: The current board state.
//   * n: The size of the board.
//   * Returns: The row index with the most conflicts, or -1 if there are no conflicts.
int _getMostConflictedRow(List<int> board, int n) {
  int maxConflicts = 0, row = -1;
  for (int i = 0; i < n; i++) {
    int conflicts = _countConflicts(board, i, board[i], n); // Count conflicts for the queen in row i.
    if (conflicts > maxConflicts) { // If this row has more conflicts than the current maximum.
      maxConflicts = conflicts;
      row = i; // Update the row with the most conflicts.
    }
  }
  return row; // Return the row with the most conflicts.  Returns -1 if no conflicts.
}

// _getBestColumn: Finds the column in a given row that results in the fewest conflicts.
//
//   * board: The current board state.
//   * row: The row to consider.
//   * n: The size of the board.
//   * Returns: The column index that minimizes conflicts.
int _getBestColumn(List<int> board, int row, int n) {
  int minConflicts = n, bestCol = board[row]; // Initialize with a large value (n) and the current column.
  for (int col = 0; col < n; col++) {
    int conflicts = _countConflicts(board, row, col, n); // Count conflicts for placing a queen in column 'col' of 'row'.
    if (conflicts < minConflicts) { // If this column has fewer conflicts than the current minimum.
      minConflicts = conflicts;
      bestCol = col; // Update the best column.
    }
  }
  return bestCol; // Return the column with the fewest conflicts.
}

// _countConflicts: Counts the number of conflicts for a queen at a given position.
//
//   * board: The current board state.
//   * row: The row of the queen.
//   * col: The column of the queen.
//   * n: The size of the board.
//   * Returns: The number of conflicts.
int _countConflicts(List<int> board, int row, int col, int n) {
  int conflicts = 0;
  for (int i = 0; i < n; i++) {
    if (i != row && (board[i] == col || (row - i).abs() == (col - board[i]).abs())) {
      conflicts++; // Increment conflict count if another queen attacks the current position
    }
  }
  return conflicts;
}

// 5. Constraint Programming (Using Constraint Propagation & DFS)
//
//   * A more advanced approach that uses constraint propagation to reduce the search space.
//   * It combines Depth-First Search (DFS) with constraint satisfaction techniques.
//   * Generally more efficient than backtracking for larger N.
void solveNQueensConstraintProgramming(int n) {
  List<int> board = List.filled(n, -1); // Initialize the board.
  Set<int> cols = {}; // Set to keep track of columns that are already occupied.
  Set<int> diags = {}; // Set to keep track of diagonals that are already occupied.
  Set<int> antiDiags = {}; // Set to keep track of anti-diagonals that are already occupied.
  _constraintDFS(0, n, board, cols, diags, antiDiags); // Start the recursive DFS with constraint propagation.
}

// _constraintDFS: Recursive function to find solutions using constraint programming and DFS.
//
//   * row: The current row.
//   * n: The size of the board.
//   * board: The current board state.
//   * cols: Set of occupied columns.
//   * diags: Set of occupied diagonals.
//   * antiDiags: Set of occupied anti-diagonals.
void _constraintDFS(int row, int n, List<int> board, Set<int> cols, Set<int> diags, Set<int> antiDiags) {
  if (row == n) { // Base case: All queens are placed.
    print(board);
    return;
  }
  for (int col = 0; col < n; col++) {
    // Check if the current position is safe based on the constraints (occupied columns, diagonals, anti-diagonals).
    if (!cols.contains(col) && !diags.contains(row - col) && !antiDiags.contains(row + col)) {
      board[row] = col; // Place the queen.
      cols.add(col); // Add the column to the set of occupied columns.
      diags.add(row - col); // Add the diagonal to the set of occupied diagonals.
      antiDiags.add(row + col); // Add the anti-diagonal to the set of occupied anti-diagonals.

      _constraintDFS(row + 1, n, board, cols, diags, antiDiags); // Recursively call for the next row.

      // Backtrack: Remove the column, diagonal, and anti-diagonal from the sets to explore other possibilities.
      cols.remove(col);
      diags.remove(row - col);
      antiDiags.remove(row + col);
    }
  }
}
