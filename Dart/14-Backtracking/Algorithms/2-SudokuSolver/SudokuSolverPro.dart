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

  if (solveSudoku(grid)) {
    print("\nSolved Sudoku:");
    printGrid(grid);
  } else {
    print("\nNo solution exists.");
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
        print("|");
      }
      print("${grid[i][j]} ");
    }
    print("");
  }
}

bool solveSudoku(List<List<int>> grid) {
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
      if (solveSudoku(grid)) {
        return true;
      } else {
        grid[row][col] = 0; // Backtrack
      }
    }
  }
  return false;
}

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
