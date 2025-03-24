import 'dart:math';

void main() {
  // Example Sudoku grid (0 represents empty cells)
  List<List<int>> grid = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9],
  ];

  print("Original Sudoku Grid:");
  printGrid(grid);

  // 1. Backtracking with Simple Iteration
  List<List<int>> grid1 = List.generate(9, (i) => List.from(grid[i])); // Create a copy
  if (solveSudoku1(grid1)) {
    print("\nSolved Sudoku (Backtracking 1):");
    printGrid(grid1);
  } else {
    print("\nNo solution exists (Backtracking 1).");
  }

  // 2. Backtracking with Optimized Search
  List<List<int>> grid2 = List.generate(9, (i) => List.from(grid[i])); // Create a copy
  if (solveSudoku2(grid2)) {
    print("\nSolved Sudoku (Backtracking 2):");
    printGrid(grid2);
  } else {
    print("\nNo solution exists (Backtracking 2).");
  }

  // 3. Backtracking with Forward Checking
  List<List<int>> grid3 = List.generate(9, (i) => List.from(grid[i]));
  if (solveSudoku3(grid3)) {
    print("\nSolved Sudoku (Backtracking 3):");
    printGrid(grid3);
  } else {
    print("\nNo solution exists (Backtracking 3).");
  }

  // 4. Backtracking with MRV Heuristic
  List<List<int>> grid4 = List.generate(9, (i) => List.from(grid[i]));
  if (solveSudoku4(grid4)) {
    print("\nSolved Sudoku (Backtracking 4 - MRV):");
    printGrid(grid4);
  } else {
    print("\nNo solution exists (Backtracking 4 - MRV).");
  }

  // 5. Backtracking with Random Cell Selection
  List<List<int>> grid5 = List.generate(9, (i) => List.from(grid[i]));
  if (solveSudoku5(grid5)) {
    print("\nSolved Sudoku (Backtracking 5 - Random):");
    printGrid(grid5);
  } else {
    print("\nNo solution exists (Backtracking 5).");
  }
}

// Helper function to print the Sudoku grid
void printGrid(List<List<int>> grid) {
  for (int i = 0; i < 9; i++) {
    if (i % 3 == 0 && i != 0) {
      print("---------");
    }
    for (int j = 0; j < 9; j++) {
      if (j % 3 == 0 && j != 0) {
        print("|"); // Removed end: ""
      }
      print("${grid[i][j]} "); // Removed end: ""
    }
    print("");
  }
}

// 1. Backtracking with Simple Iteration
// This is the basic backtracking approach.  It iterates through each cell
// and tries numbers 1-9.  If a number is valid, it recurses.  If no number
// is valid, it backtracks.
bool solveSudoku1(List<List<int>> grid) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (grid[row][col] == 0) {
        for (int number = 1; number <= 9; number++) {
          if (isValid(grid, row, col, number)) {
            grid[row][col] = number;
            if (solveSudoku1(grid)) {
              return true;
            } else {
              grid[row][col] = 0; // Backtrack
            }
          }
        }
        return false;
      }
    }
  }
  return true; // Grid is full, solution found
}

// 2. Backtracking with Optimized Search
// This version optimizes the search by finding the next empty cell
// directly, instead of iterating through the entire grid.  This can
// be slightly more efficient.
bool solveSudoku2(List<List<int>> grid) {
  int row = -1;
  int col = -1;
  bool isEmpty = true;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (grid[i][j] == 0) {
        row = i;
        col = j;
        isEmpty = false;
        break;
      }
    }
    if (!isEmpty) {
      break;
    }
  }

  if (isEmpty) {
    return true; // No empty cells, we are done
  }

  for (int number = 1; number <= 9; number++) {
    if (isValid(grid, row, col, number)) {
      grid[row][col] = number;
      if (solveSudoku2(grid)) {
        return true;
      } else {
        grid[row][col] = 0; // Backtrack
      }
    }
  }
  return false;
}

// 3. Backtracking with Forward Checking
// Forward checking is a more advanced technique.  It maintains a list of
// possible values for each empty cell.  Before assigning a value, it
// checks if that value is still possible for any unassigned cell in the
// same row, column, and block.  This can prune the search space and
// improve performance, but it adds complexity.
bool solveSudoku3(List<List<int>> grid) {
  List<List<Set<int>>> possibleValues = List.generate(
      9, (_) => List.generate(9, (_) => {1, 2, 3, 4, 5, 6, 7, 8, 9}));

  // Initialize possible values
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (grid[row][col] != 0) {
        possibleValues[row][col].clear(); // No possible values for filled cells
        updatePossibleValues(grid, possibleValues, row, col,
            grid[row][col]);
      }
    }
  }

  return solveSudokuWithForwardChecking(grid, possibleValues);
}

bool solveSudokuWithForwardChecking(
    List<List<int>> grid, List<List<Set<int>>> possibleValues) {
  int row = -1;
  int col = -1;
  bool isEmpty = true;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (grid[i][j] == 0) {
        row = i;
        col = j;
        isEmpty = false;
        break;
      }
    }
    if (!isEmpty) break;
  }

  if (isEmpty) return true;

  for (int number in possibleValues[row][col].toList()) {
    // Iterate over a copy to avoid concurrent modification
    if (isValid(grid, row, col, number)) {
      grid[row][col] = number;
      List<List<Set<int>>> savedPossibleValues = List.generate(
          9,
              (i) => List.generate(9, (j) => Set.from(possibleValues[i][j]))); // Deep copy

      updatePossibleValues(grid, possibleValues, row, col, number);

      if (solveSudokuWithForwardChecking(grid, possibleValues)) {
        return true;
      } else {
        grid[row][col] = 0;
        possibleValues = savedPossibleValues; // Restore
      }
    }
  }
  return false;
}

void updatePossibleValues(List<List<int>> grid,
    List<List<Set<int>>> possibleValues, int row, int col, int number) {
  // Remove 'number' from possible values in the same row
  for (int c = 0; c < 9; c++) {
    possibleValues[row][c].remove(number);
  }
  // Remove 'number' from possible values in the same column
  for (int r = 0; r < 9; r++) {
    possibleValues[r][col].remove(number);
  }
  // Remove 'number' from possible values in the same block
  int startRow = row - row % 3;
  int startCol = col - col % 3;
  for (int r = startRow; r < startRow + 3; r++) {
    for (int c = startCol; c < startCol + 3; c++) {
      possibleValues[r][c].remove(number);
    }
  }
}

// 4. Backtracking with MRV (Minimum Remaining Values) Heuristic
// MRV is a heuristic that selects the cell with the fewest possible values
// to fill next.  This can significantly reduce the branching factor of the
// search tree.  This version combines MRV with backtracking.
bool solveSudoku4(List<List<int>> grid) {
  List<List<Set<int>>> possibleValues = List.generate(
      9, (_) => List.generate(9, (_) => {1, 2, 3, 4, 5, 6, 7, 8, 9}));

  // Initialize possible values
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (grid[row][col] != 0) {
        possibleValues[row][col].clear(); // No possible values for filled cells
        updatePossibleValues(grid, possibleValues, row, col,
            grid[row][col]);
      }
    }
  }
  return solveSudokuWithMRV(grid, possibleValues);
}

bool solveSudokuWithMRV(
    List<List<int>> grid, List<List<Set<int>>> possibleValues) {
  int minRemaining = 10;
  int mrvRow = -1;
  int mrvCol = -1;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (grid[i][j] == 0) {
        int numRemaining = possibleValues[i][j].length;
        if (numRemaining < minRemaining) {
          minRemaining = numRemaining;
          mrvRow = i;
          mrvCol = j;
        }
      }
    }
  }

  if (mrvRow == -1 && mrvCol == -1) {
    return true; // No empty cells
  }

  for (int number in possibleValues[mrvRow][mrvCol].toList()) {
    if (isValid(grid, mrvRow, mrvCol, number)) {
      grid[mrvRow][mrvCol] = number;
      List<List<Set<int>>> savedPossibleValues = List.generate(
          9,
              (i) => List.generate(9, (j) => Set.from(possibleValues[i][j]))); // Deep copy
      updatePossibleValues(grid, possibleValues, mrvRow, mrvCol, number);
      if (solveSudokuWithMRV(grid, possibleValues)) {
        return true;
      } else {
        grid[mrvRow][mrvCol] = 0;
        possibleValues = savedPossibleValues;
      }
    }
  }
  return false;
}

// 5. Backtracking with Random Cell Selection
//  This approach selects a random empty cell at each step.  While not
//  generally the most efficient, it can sometimes perform well and
//  provides a contrast to the more deterministic approaches.
bool solveSudoku5(List<List<int>> grid) {
  List<List<int>> emptyCells = [];
  for (int r = 0; r < 9; r++) {
    for (int c = 0; c < 9; c++) {
      if (grid[r][c] == 0) {
        emptyCells.add([r, c]);
      }
    }
  }

  if (emptyCells.isEmpty) {
    return true; // No empty cells
  }

  // Randomly select an empty cell
  final random = Random();
  int randomIndex = random.nextInt(emptyCells.length);
  int row = emptyCells[randomIndex][0];
  int col = emptyCells[randomIndex][1];

  for (int number = 1; number <= 9; number++) {
    if (isValid(grid, row, col, number)) {
      grid[row][col] = number;
      if (solveSudoku5(grid)) {
        return true;
      } else {
        grid[row][col] = 0; // Backtrack
      }
    }
  }
  return false;
}

// Helper function to check if a number can be placed in a cell
bool isValid(List<List<int>> grid, int row, int col, int number) {
  // Check row
  for (int c = 0; c < 9; c++) {
    if (grid[row][c] == number) {
      return false;
    }
  }
  // Check column
  for (int r = 0; r < 9; r++) {
    if (grid[r][col] == number) {
      return false;
    }
  }
  // Check 3x3 block
  int startRow = row - row % 3;
  int startCol = col - col % 3;
  for (int r = startRow; r < startRow + 3; r++) {
    for (int c = startCol; c < startCol + 3; c++) {
      if (grid[r][c] == number) {
        return false;
      }
    }
  }
  return true;
}
