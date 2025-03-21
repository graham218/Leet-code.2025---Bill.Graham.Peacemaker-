import 'dart:collection';
import 'dart:math';

void main() {
  // 1. Example Usage:
  // Imagine a topographic map represented as a matrix of elevation levels.
  // We want to find areas that can drain into both the Pacific and Atlantic oceans.
  final List<List<int>> elevationMap = [
    [1, 2, 2, 3, 5],
    [3, 2, 3, 4, 4],
    [2, 4, 5, 3, 1],
    [6, 7, 1, 4, 5],
    [5, 1, 1, 2, 4],
  ];

  print('\n--- Topographic Map Analysis ---\n');
  print('Elevation Map:');
  printMatrix(elevationMap);

  // 2. Find drainage areas using Depth-First Search (DFS)
  final solutionDFS = DrainageAnalysisDFS();
  final drainageResultDFS = solutionDFS.findDrainage(elevationMap);
  print('\nDFS Drainage Areas (Coordinates [row, col]):');
  printResult(drainageResultDFS);

  // 3. Find drainage areas using Breadth-First Search (BFS)
  final solutionBFS = DrainageAnalysisBFS();
  final drainageResultBFS = solutionBFS.findDrainage(elevationMap);
  print('\nBFS Drainage Areas (Coordinates [row, col]):');
  printResult(drainageResultBFS);

  // 4. Find drainage areas using Optimized DFS
  final solutionOptimizedDFS = DrainageAnalysisOptimizedDFS();
  final drainageResultOptimizedDFS = solutionOptimizedDFS.findDrainage(elevationMap);
  print('\nOptimized DFS Drainage Areas (Coordinates [row, col]):');
  printResult(drainageResultOptimizedDFS);

  // 5.  Simulate Water Flow from a Specific Point (Example)
  final simulation = WaterFlowSimulation(elevationMap);
  final startRow = 2;
  final startCol = 2;
  print('\nWater Flow Simulation from [$startRow, $startCol]:');
  simulation.simulateFlow(startRow, startCol);
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
    print('  ${pair},');
  }
  print(']');
}

// --- 1. Depth-First Search (DFS) for Drainage Analysis ---
class DrainageAnalysisDFS {
  /// Finds areas in an elevation map that drain to both water bodies.
  ///
  /// Input:
  ///   - elevationMap: A matrix representing elevation levels.
  ///
  /// Output:
  ///   - A list of coordinates [row, col] of areas draining to both.
  List<List<int>> findDrainage(List<List<int>> elevationMap) {
    if (elevationMap.isEmpty || elevationMap[0].isEmpty) {
      return [];
    }

    final int rows = elevationMap.length;
    final int cols = elevationMap[0].length;

    final List<List<bool>> drainsToSource1 =
    List.generate(rows, (_) => List.filled(cols, false));
    final List<List<bool>> drainsToSource2 =
    List.generate(rows, (_) => List.filled(cols, false));

    // Perform DFS from the borders (simulating water sources).
    for (int i = 0; i < rows; i++) {
      _dfs(elevationMap, i, 0, drainsToSource1, -1); // Source 1 (e.g., Pacific)
      _dfs(elevationMap, i, cols - 1, drainsToSource2, -1); // Source 2 (e.g., Atlantic)
    }
    for (int j = 0; j < cols; j++) {
      _dfs(elevationMap, 0, j, drainsToSource1, -1);
      _dfs(elevationMap, rows - 1, j, drainsToSource2, -1);
    }

    final List<List<int>> result = [];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (drainsToSource1[i][j] && drainsToSource2[i][j]) {
          result.add([i, j]);
        }
      }
    }
    return result;
  }

  void _dfs(
      List<List<int>> elevationMap,
      int row,
      int col,
      List<List<bool>> reachable,
      int previousHeight) {
    final int rows = elevationMap.length;
    final int cols = elevationMap[0].length;

    if (row < 0 ||
        row >= rows ||
        col < 0 ||
        col >= cols ||
        reachable[row][col] ||
        elevationMap[row][col] < previousHeight) {
      return;
    }

    reachable[row][col] = true;

    final List<List<int>> directions = [
      [0, 1],
      [0, -1],
      [1, 0],
      [-1, 0]
    ];
    for (final dir in directions) {
      final int newRow = row + dir[0];
      final int newCol = col + dir[1];
      _dfs(elevationMap, newRow, newCol, reachable, elevationMap[row][col]);
    }
  }
}

// --- 2. Breadth-First Search (BFS) for Drainage Analysis ---
class DrainageAnalysisBFS {
  /// Finds areas in an elevation map that drain to both water bodies using BFS.
  List<List<int>> findDrainage(List<List<int>> elevationMap) {
    if (elevationMap.isEmpty || elevationMap[0].isEmpty) {
      return [];
    }

    final int rows = elevationMap.length;
    final int cols = elevationMap[0].length;
    final List<List<bool>> drainsToSource1 =
    List.generate(rows, (_) => List.filled(cols, false));
    final List<List<bool>> drainsToSource2 =
    List.generate(rows, (_) => List.filled(cols, false));

    _bfs(elevationMap, drainsToSource1, 0, 0); // Source 1
    _bfs(elevationMap, drainsToSource2, rows - 1, cols - 1); // Source 2

    final List<List<int>> result = [];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (drainsToSource1[i][j] && drainsToSource2[i][j]) {
          result.add([i, j]);
        }
      }
    }
    return result;
  }

  void _bfs(List<List<int>> elevationMap, List<List<bool>> reachable,
      int startRow, int startCol) {
    final int rows = elevationMap.length;
    final int cols = elevationMap[0].length;
    final Queue<List<int>> queue = Queue();
    queue.add([startRow, startCol]);
    reachable[startRow][startCol] = true;

    while (queue.isNotEmpty) {
      final List<int> current = queue.removeFirst();
      final int row = current[0];
      final int col = current[1];

      final List<List<int>> directions = [
        [0, 1],
        [0, -1],
        [1, 0],
        [-1, 0]
      ];
      for (final dir in directions) {
        final int newRow = row + dir[0];
        final int newCol = col + dir[1];

        if (newRow >= 0 &&
            newRow < rows &&
            newCol >= 0 &&
            newCol < cols &&
            !reachable[newRow][newCol] &&
            elevationMap[newRow][newCol] >= elevationMap[row][col]) {
          reachable[newRow][newCol] = true;
          queue.add([newRow, newCol]);
        }
      }
    }
  }
}

// --- 3. Optimized DFS for Drainage Analysis ---
class DrainageAnalysisOptimizedDFS {
  List<List<int>> findDrainage(List<List<int>> elevationMap) {
    if (elevationMap.isEmpty || elevationMap[0].isEmpty) {
      return [];
    }

    final int rows = elevationMap.length;
    final int cols = elevationMap[0].length;
    final List<List<bool>> drainsToSource1 =
    List.generate(rows, (_) => List.filled(cols, false));
    final List<List<bool>> drainsToSource2 =
    List.generate(rows, (_) => List.filled(cols, false));

    for (int i = 0; i < rows; i++) {
      _optimizedDfs(elevationMap, i, 0, drainsToSource1); // Source 1
      _optimizedDfs(elevationMap, i, cols - 1, drainsToSource2); // Source 2
    }
    for (int j = 0; j < cols; j++) {
      _optimizedDfs(elevationMap, 0, j, drainsToSource1);
      _optimizedDfs(elevationMap, rows - 1, j, drainsToSource2);
    }

    final List<List<int>> result = [];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (drainsToSource1[i][j] && drainsToSource2[i][j]) {
          result.add([i, j]);
        }
      }
    }
    return result;
  }

  void _optimizedDfs(List<List<int>> elevationMap, int row, int col,
      List<List<bool>> reachable) {
    final int rows = elevationMap.length;
    final int cols = elevationMap[0].length;

    if (row < 0 ||
        row >= rows ||
        col < 0 ||
        col >= cols ||
        reachable[row][col]) {
      return;
    }

    reachable[row][col] = true;

    final List<List<int>> directions = [
      [0, 1],
      [0, -1],
      [1, 0],
      [-1, 0]
    ];
    for (final dir in directions) {
      final int newRow = row + dir[0];
      final int newCol = col + dir[1];
      if (newRow >= 0 &&
          newRow < rows &&
          newCol >= 0 &&
          newCol < cols &&
          elevationMap[newRow][newCol] >= elevationMap[row][col]) {
        _optimizedDfs(elevationMap, newRow, newCol, reachable);
      }
    }
  }
}

// --- 4. Water Flow Simulation from a Specific Point ---
class WaterFlowSimulation {
  final List<List<int>> _elevationMap;
  final int _rows;
  final int _cols;

  WaterFlowSimulation(this._elevationMap)
      : _rows = _elevationMap.length,
        _cols = _elevationMap[0].length;

  /// Simulates water flow from a given starting point.
  ///
  /// Input:
  ///   - startRow: The row index of the starting point.
  ///   - startCol: The column index of the starting point.
  void simulateFlow(int startRow, int startCol) {
    if (startRow < 0 ||
        startRow >= _rows ||
        startCol < 0 ||
        startCol >= _cols) {
      print('Invalid start coordinates.');
      return;
    }

    final List<List<bool>> visited =
    List.generate(_rows, (_) => List.filled(_cols, false));
    _flow(startRow, startCol, visited, _elevationMap[startRow][startCol]);

    // Print the flow result (visualize with 'V' for visited)
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < _cols; j++) {
        if (visited[i][j]) {
          print('V '); // Water flowed through this cell
        } else {
          print('${_elevationMap[i][j]} '); // Original elevation
        }
      }
      print('');
    }
  }

  void _flow(int row, int col, List<List<bool>> visited, int previousHeight) {
    if (row < 0 ||
        row >= _rows ||
        col < 0 ||
        col >= _cols ||
        visited[row][col] ||
        _elevationMap[row][col] < previousHeight) {
      return;
    }

    visited[row][col] = true;

    final List<List<int>> directions = [
      [0, 1],
      [0, -1],
      [1, 0],
      [-1, 0]
    ];
    for (final dir in directions) {
      final int newRow = row + dir[0];
      final int newCol = col + dir[1];
      _flow(newRow, newCol, visited, _elevationMap[row][col]);
    }
  }
}
