// Dart program implementing Rotate Image using 5 different approaches

void main() {
  List<List<int>> image = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
  ];

  print("Original Image:");
  printMatrix(image);

  print("\n1. Rotate Using Transpose & Reverse:");
  printMatrix(rotateTransposeReverse(image));

  print("\n2. Rotate Using Extra Matrix:");
  printMatrix(rotateExtraMatrix(image));

  print("\n3. Rotate In-Place (Layer by Layer):");
  printMatrix(rotateInPlace(image));

  print("\n4. Rotate Using Matrix Multiplication:");
  printMatrix(rotateMatrixMultiplication(image));

  print("\n5. Rotate Using Recursive Approach:");
  printMatrix(rotateRecursive(image));
}

// Helper function to print a 2D matrix
void printMatrix(List<List<int>> matrix) {
  for (var row in matrix) {
    print(row);
  }
}

// Approach 1: Rotate using Transpose & Reverse
// Rotates the matrix 90 degrees clockwise by first transposing it and then reversing each row.
List<List<int>> rotateTransposeReverse(List<List<int>> matrix) {
  int n = matrix.length;
  // Transpose the matrix: Swap elements across the main diagonal.
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int temp = matrix[i][j]; // Store the element to be swapped.
      matrix[i][j] = matrix[j][i]; // Swap elements.
      matrix[j][i] = temp; // Complete the swap.
    }
  }
  // Reverse each row: Reflect each row about its center.
  for (int i = 0; i < n; i++) {
    matrix[i] = matrix[i].reversed.toList(); // Reverse the elements in the current row.
  }
  return matrix; // Return the rotated matrix.
}

// Approach 2: Rotate Using Extra Matrix
// Rotates the matrix 90 degrees clockwise by creating a new matrix and copying elements in rotated order.
List<List<int>> rotateExtraMatrix(List<List<int>> matrix) {
  int n = matrix.length;
  // Create a new matrix with the same dimensions.
  List<List<int>> result = List.generate(n, (_) => List<int>.filled(n, 0));
  // Copy elements from the original matrix to the new matrix in rotated order.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[j][n - i - 1] = matrix[i][j]; // Calculate the new position and copy.
    }
  }
  return result; // Return the rotated matrix.
}

// Approach 3: Rotate In-Place (Layer by Layer)
// Rotates the matrix 90 degrees clockwise in-place by rotating layers of elements.
List<List<int>> rotateInPlace(List<List<int>> matrix) {
  int n = matrix.length;
  // Iterate through the layers of the matrix.
  for (int layer = 0; layer < n ~/ 2; layer++) {
    int first = layer; // Index of the first element in the layer.
    int last = n - layer - 1; // Index of the last element in the layer.
    // Iterate through the elements in the current layer.
    for (int i = first; i < last; i++) {
      int offset = i - first; // Calculate the offset from the first element.
      int top = matrix[first][i]; // Store the top element.
      // Rotate the elements in the layer: left -> top, bottom -> left, right -> bottom, top -> right.
      matrix[first][i] = matrix[last - offset][first];
      matrix[last - offset][first] = matrix[last][last - offset];
      matrix[last][last - offset] = matrix[i][last];
      matrix[i][last] = top;
    }
  }
  return matrix; // Return the rotated matrix.
}

// Approach 4: Rotate Using Matrix Multiplication
// Rotates the matrix 90 degrees clockwise using matrix multiplication principles.
List<List<int>> rotateMatrixMultiplication(List<List<int>> matrix) {
  int n = matrix.length;
  // Rotation matrix for 90 degrees clockwise.
  List<List<int>> rotationMatrix = [
    [0, -1],
    [1, 0]
  ];
  // Create a new matrix to store the rotated result.
  List<List<int>> result = List.generate(n, (_) => List<int>.filled(n, 0));
  // Calculate the new coordinates for each element using matrix multiplication.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x = rotationMatrix[0][0] * i + rotationMatrix[0][1] * j + (n - 1); // Calculate new x coordinate.
      int y = rotationMatrix[1][0] * i + rotationMatrix[1][1] * j; // Calculate new y coordinate.
      result[x][y] = matrix[i][j]; // Copy the element to the new position.
    }
  }
  return result; // Return the rotated matrix.
}

// Approach 5: Rotate Using Recursive Approach
// Rotates the matrix 90 degrees clockwise using a recursive approach.
List<List<int>> rotateRecursive(List<List<int>> matrix) {
  // Recursive helper function to rotate submatrices.
  void helper(int row, int col, int n) {
    if (n <= 1) return; // Base case: single element or empty submatrix.
    int temp = matrix[row][col]; // Store the top-left element.
    // Rotate the four corner elements.
    matrix[row][col] = matrix[row + n - 1][col];
    matrix[row + n - 1][col] = matrix[row + n - 1][col + n - 1];
    matrix[row + n - 1][col + n - 1] = matrix[row][col + n - 1];
    matrix[row][col + n - 1] = temp;
    // Recursively rotate the inner submatrix.
    helper(row + 1, col + 1, n - 2);
  }
  helper(0, 0, matrix.length); // Start the recursive rotation from the top-left corner.
  return matrix; // Return the rotated matrix.
}