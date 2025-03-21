import 'dart:collection';
import 'dart:math';

void main() {
  // Example usage of the solutions:
  final List<List<int>> matrix = [
    [1, 2, 2, 3, 5],
    [3, 2, 3, 4, 4],
    [2, 4, 5, 3, 1],
    [6, 7, 1, 4, 5],
    [5, 1, 1, 2, 4],
  ];

  print('\n--- Pacific Atlantic Water Flow ---\n');
  print('Input Matrix:');
  printMatrix(matrix);

  // Solution 1: Depth-First Search
  final solutionDFS = PacificAtlanticWaterFlowDFS();
  final resultDFS = solutionDFS.pacificAtlantic(matrix);
  print('\nDFS Solution:');
  printResult(resultDFS);

  // Solution 2: Breadth-First Search
  final solutionBFS = PacificAtlanticWaterFlowBFS();
  final resultBFS = solutionBFS.pacificAtlantic(matrix);
  print('\nBFS Solution:');
  printResult(resultBFS);

  // Solution 3: Optimized DFS (Slightly more efficient)
  final solutionOptimizedDFS = PacificAtlanticWaterFlowOptimizedDFS();
  final resultOptimizedDFS = solutionOptimizedDFS.pacificAtlantic(matrix);
  print('\nOptimized DFS Solution:');
  printResult(resultOptimizedDFS);
}

// Helper function to print the matrix
void printMatrix(List<List<int>> matrix) {
  for (final row in matrix) {
    print(row);
  }
}

// Helper function to print the result list
void printResult(List<List<int>> result) {
  if (result.isEmpty) {
    print('[]');
    return;
  }
  print('[');
  for (final pair in result) {
    print('  ${pair},'); // Added comma for better formatting
  }
  print(']');
}

// --- Solution 1: Depth-First Search (DFS) ---
class PacificAtlanticWaterFlowDFS {
  /// Finds the cells in the given matrix from which water can flow to both
  /// the Pacific and Atlantic oceans.
  ///
  /// The matrix represents a landscape where each cell's value is its height.
  /// Water can flow from a cell to its adjacent cells (up, down, left, right)
  /// only if the adjacent cell's height is less than or equal to the current
  /// cell's height.
  ///
  /// Returns a list of coordinates [row, col] of the cells that can reach
  /// both oceans.
  List<List<int>> pacificAtlantic(List<List<int>> matrix) {
    // Handle edge case: empty matrix.
    if (matrix.isEmpty || matrix[0].isEmpty) {
      return [];
    }

    final int rows = matrix.length;
    final int cols = matrix[0].length;

    // Create boolean matrices to track which cells can reach the Pacific and Atlantic.
    // Initially, all cells are marked as unreachable (false).
    final List<List<bool>> pacificReachable =
    List.generate(rows, (_) => List.filled(cols, false));
    final List<List<bool>> atlanticReachable =
    List.generate(rows, (_) => List.filled(cols, false));

    // Perform DFS from the borders of the matrix to find reachable cells.
    // Water can flow from the Pacific ocean to the cells on the top and left edges.
    for (int i = 0; i < rows; i++) {
      _dfs(matrix, i, 0, pacificReachable, -1); // Pacific border (left edge)
      _dfs(matrix, i, cols - 1, atlanticReachable, -1); // Atlantic border (right edge)
    }
    for (int j = 0; j < cols; j++) {
      _dfs(matrix, 0, j, pacificReachable, -1); // Pacific border (top edge)
      _dfs(matrix, rows - 1, j, atlanticReachable, -1); // Atlantic border (bottom edge)
    }

    // Collect the cells that can reach both oceans.
    final List<List<int>> result = [];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (pacificReachable[i][j] && atlanticReachable[i][j]) {
          // If a cell can reach both oceans, add its coordinates to the result.
          result.add([i, j]);
        }
      }
    }
    return result;
  }

  /// Depth-First Search function to mark reachable cells.
  ///
  /// This function recursively explores the neighbors of a cell to determine if
  /// water can flow from that cell to the ocean.
  ///
  /// Parameters:
  ///   matrix: The input height matrix.
  ///   row: The current row index.
  ///   col: The current column index.
  ///   reachable: The boolean matrix to mark reachable cells.
  ///   previousHeight: The height of the cell from which water is flowing.
  void _dfs(
      List<List<int>> matrix,
      int row,
      int col,
      List<List<bool>> reachable,
      int previousHeight) {
    final int rows = matrix.length;
    final int cols = matrix[0].length;

    // Base cases:
    // 1. Out of bounds: If the current cell is outside the matrix boundaries, stop.
    // 2. Already visited: If the current cell has already been marked as reachable, stop.
    // 3. Cannot flow: If the current cell's height is less than the previous cell's height,
    //    water cannot flow from the previous cell to this cell, so stop.
    if (row < 0 ||
        row >= rows ||
        col < 0 ||
        col >= cols ||
        reachable[row][col] ||
        matrix[row][col] < previousHeight) {
      return;
    }

    // Mark the current cell as reachable.
    reachable[row][col] = true;

    // Explore adjacent cells (up, down, left, right).
    final List<List<int>> directions = [
      [0, 1],
      [0, -1],
      [1, 0],
      [-1, 0]
    ]; // Right, Left, Down, Up
    for (final dir in directions) {
      final int newRow = row + dir[0];
      final int newCol = col + dir[1];
      // Recursively call _dfs for the adjacent cell, passing the current cell's height
      // as the previousHeight.
      _dfs(matrix, newRow, newCol, reachable, matrix[row][col]);
    }
  }
}

// --- Solution 2: Breadth-First Search (BFS) ---
class PacificAtlanticWaterFlowBFS {
  /// Finds the cells in the given matrix from which water can flow to both
  /// the Pacific and Atlantic oceans using Breadth-First Search.
  ///
  /// The matrix represents a landscape where each cell's value is its height.
  /// Water can flow from a cell to its adjacent cells (up, down, left, right)
  /// only if the adjacent cell's height is less than or equal to the current
  /// cell's height.
  ///
  /// Returns a list of coordinates [row, col] of the cells that can reach
  /// both oceans.
  List<List<int>> pacificAtlantic(List<List<int>> matrix) {
    // Handle edge case: empty matrix.
    if (matrix.isEmpty || matrix[0].isEmpty) {
      return [];
    }

    final int rows = matrix.length;
    final int cols = matrix[0].length;

    // Create boolean matrices to track which cells can reach the Pacific and Atlantic.
    // Initially, all cells are marked as unreachable (false).
    final List<List<bool>> pacificReachable =
    List.generate(rows, (_) => List.filled(cols, false));
    final List<List<bool>> atlanticReachable =
    List.generate(rows, (_) => List.filled(cols, false));

    // Perform BFS from the borders of the matrix to find reachable cells.
    // Start BFS from top-left for Pacific and bottom-right for Atlantic.
    _bfs(matrix, pacificReachable, 0, 0); // Start BFS from top-left (Pacific)
    _bfs(matrix, atlanticReachable, rows - 1, cols - 1); // Start BFS from bottom-right (Atlantic)

    // Collect cells reachable from both oceans.
    final List<List<int>> result = [];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (pacificReachable[i][j] && atlanticReachable[i][j]) {
          // If a cell can reach both oceans, add its coordinates to the result.
          result.add([i, j]);
        }
      }
    }
    return result;
  }

  /// Breadth-First Search function.
  ///
  /// This function explores the matrix using BFS, starting from a given cell,
  /// to find all reachable cells.
  ///
  /// Parameters:
  ///   matrix: The input height matrix.
  ///   reachable: The boolean matrix to mark reachable cells.
  ///   startRow: The starting row index for BFS.
  ///   startCol: The starting column index for BFS.
  void _bfs(List<List<int>> matrix, List<List<bool>> reachable, int startRow,
      int startCol) {
    final int rows = matrix.length;
    final int cols = matrix[0].length;
    // Use a queue to store the cells to be visited.
    final Queue<List<int>> queue = Queue();
    // Start BFS from the given start cell.
    queue.add([startRow, startCol]);
    reachable[startRow][startCol] = true; // Mark the starting cell as reachable.

    // Continue BFS until the queue is empty.
    while (queue.isNotEmpty) {
      final List<int> current = queue.removeFirst(); // Get the next cell from the queue.
      final int row = current[0];
      final int col = current[1];

      // Explore adjacent cells (up, down, left, right).
      final List<List<int>> directions = [
        [0, 1],
        [0, -1],
        [1, 0],
        [-1, 0]
      ]; // Right, Left, Down, Up
      for (final dir in directions) {
        final int newRow = row + dir[0];
        final int newCol = col + dir[1];

        // Check if the neighbor is within bounds, not already visited, and can be reached.
        if (newRow >= 0 &&
            newRow < rows &&
            newCol >= 0 &&
            newCol < cols &&
            !reachable[newRow][newCol] &&
            matrix[newRow][newCol] >= matrix[row][col]) {
          reachable[newRow][newCol] = true; // Mark the neighbor as reachable.
          queue.add([newRow, newCol]); // Add the neighbor to the queue for further exploration.
        }
      }
    }
  }
}

// --- Solution 3: Optimized DFS ---
class PacificAtlanticWaterFlowOptimizedDFS {
  /// Finds the cells in the given matrix from which water can flow to both
  /// the Pacific and Atlantic oceans using an optimized Depth-First Search.
  ///
  /// The optimization involves marking a cell as reachable *before* exploring its neighbors,
  /// which can reduce redundant checks.
  ///
  /// The matrix represents a landscape where each cell's value is its height.
  /// Water can flow from a cell to its adjacent cells (up, down, left, right)
  /// only if the adjacent cell's height is less than or equal to the current
  /// cell's height.
  ///
  /// Returns a list of coordinates [row, col] of the cells that can reach
  /// both oceans.
  List<List<int>> pacificAtlantic(List<List<int>> matrix) {
    // Handle edge case: empty matrix.
    if (matrix.isEmpty || matrix[0].isEmpty) {
      return [];
    }

    final int rows = matrix.length;
    final int cols = matrix[0].length;
    // Create boolean matrices to track which cells can reach the Pacific and Atlantic.
    final List<List<bool>> pacificReachable =
    List.generate(rows, (_) => List.filled(cols, false));
    final List<List<bool>> atlanticReachable =
    List.generate(rows, (_) => List.filled(cols, false));

    // Perform DFS from the borders of the matrix to find reachable cells.
    // Optimized DFS: Start from the edges.
    for (int i = 0; i < rows; i++) {
      _optimizedDfs(matrix, i, 0, pacificReachable); // Pacific
      _optimizedDfs(matrix, i, cols - 1, atlanticReachable); // Atlantic
    }
    for (int j = 0; j < cols; j++) {
      _optimizedDfs(matrix, 0, j, pacificReachable); // Pacific
      _optimizedDfs(matrix, rows - 1, j, atlanticReachable); // Atlantic
    }

    // Collect the cells that can reach both oceans.
    final List<List<int>> result = [];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (pacificReachable[i][j] && atlanticReachable[i][j]) {
          result.add([i, j]);
        }
      }
    }
    return result;
  }

  /// Optimized Depth-First Search function to mark reachable cells.
  ///
  /// This function recursively explores the neighbors of a cell to determine if
  /// water can flow from that cell to the ocean.  It is optimized by marking the
  /// cell as reachable *before* checking its neighbors.
  ///
  /// Parameters:
  ///   matrix: The input height matrix.
  ///   row: The current row index.
  ///   col: The current column index.
  ///   reachable: The boolean matrix to mark reachable cells.
  void _optimizedDfs(List<List<int>> matrix, int row, int col,
      List<List<bool>> reachable) {
    final int rows = matrix.length;
    final int cols = matrix[0].length;

    // Base cases:
    // 1. Out of bounds.
    // 2. Already visited.
    if (row < 0 ||
        row >= rows ||
        col < 0 ||
        col >= cols ||
        reachable[row][col]) {
      return;
    }

    // Mark the current cell as reachable *before* exploring neighbors.  This is the optimization.
    reachable[row][col] = true;

    // Explore adjacent cells.
    final List<List<int>> directions = [
      [0, 1],
      [0, -1],
      [1, 0],
      [-1, 0]
    ];
    for (final dir in directions) {
      final int newRow = row + dir[0];
      final int newCol = col + dir[1];
      // Check if the neighbor is within bounds and can be reached (height is greater or equal).
      if (newRow >= 0 &&
          newRow < rows &&
          newCol >= 0 &&
          newCol < cols &&
          matrix[newRow][newCol] >= matrix[row][col]) {
        _optimizedDfs(matrix, newRow, newCol, reachable);
      }
    }
  }
}
