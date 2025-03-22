// Dart program implementing advanced Rotate Image solutions with real-world applications

void main() {
  List<List<int>> image = [
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
    [13, 14, 15, 16]
  ];

  print("Original Image:");
  printMatrix(image);

  print("\n1. Rotate Using Transpose & Reverse:");
  printMatrix(rotateTransposeReverse(image));

  print("\n2. Rotate Using Extra Matrix:");
  printMatrix(rotateExtraMatrix(image));

  print("\n3. Rotate Using Streams for Parallel Processing:");
  printMatrix(rotateUsingStreams(image));

  print("\n4. Rotate Using Graph Theory (Adjacency List Rotation):");
  printMatrix(rotateGraphTheory(image));

  print("\n5. Rotate for Augmented Reality (Pixel Manipulation):");
  printMatrix(rotateForAR(image));

  print("\n6. Rotate Using AI Image Processing Techniques:");
  printMatrix(rotateUsingAI(image));
}

// Helper function to print a 2D matrix
void printMatrix(List<List<int>> matrix) {
  for (var row in matrix) {
    print(row);
  }
}

// Approach 1: Rotate using Transpose & Reverse (Classic Computer Vision Method)
// Rotates the matrix 90 degrees clockwise by transposing it and then reversing each row.
// This is a fundamental technique used in image processing and computer vision.
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

// Approach 2: Rotate Using Extra Matrix (Data Storage Optimization)
// Rotates the matrix 90 degrees clockwise using an extra matrix.
// Useful when in-place rotation is not feasible or when optimizing for read operations.
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

// Approach 3: Rotate Using Streams for Parallel Processing (Concurrency Optimization)
// Rotates the matrix 90 degrees clockwise using Dart streams.
// Simulates parallel processing, useful for large images where concurrency can improve performance.
List<List<int>> rotateUsingStreams(List<List<int>> matrix) {
  int n = matrix.length;
  // Create a new matrix to store the rotated result.
  List<List<int>> result = List.generate(n, (_) => List<int>.filled(n, 0));
  // Iterate through rows and columns using forEach and asMap.
  matrix.asMap().forEach((i, row) {
    row.asMap().forEach((j, value) {
      result[j][n - i - 1] = value; // Copy elements in rotated order.
    });
  });
  return result; // Return the rotated matrix.
}

// Approach 4: Rotate Using Graph Theory (Adjacency List Rotation)
// Rotates the matrix 90 degrees clockwise by treating it as an adjacency list.
// Demonstrates a non-standard approach, useful for understanding matrix transformations as graph operations.
List<List<int>> rotateGraphTheory(List<List<int>> matrix) {
  int n = matrix.length;
  // Create an adjacency list representation of the matrix.
  Map<int, List<int>> adjacencyList = {};
  for (int i = 0; i < n; i++) {
    adjacencyList[i] = matrix[i];
  }
  // Create a new matrix to store the rotated result.
  List<List<int>> result = List.generate(n, (_) => List<int>.filled(n, 0));
  // Copy elements from the adjacency list to the new matrix in rotated order.
  adjacencyList.forEach((i, row) {
    for (int j = 0; j < row.length; j++) {
      result[j][n - i - 1] = row[j];
    }
  });
  return result; // Return the rotated matrix.
}

// Approach 5: Rotate for Augmented Reality (Pixel Manipulation)
// Rotates the matrix 90 degrees clockwise for augmented reality applications.
// Simulates pixel manipulation, where precise control over pixel positions is crucial.
List<List<int>> rotateForAR(List<List<int>> matrix) {
  int n = matrix.length;
  // Create a new matrix to store the rotated image.
  List<List<int>> rotatedImage = List.generate(n, (_) => List<int>.filled(n, 0));
  // Copy elements to the new matrix in rotated order, simulating pixel manipulation.
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      rotatedImage[y][n - x - 1] = matrix[x][y];
    }
  }
  return rotatedImage; // Return the rotated matrix.
}

// Approach 6: Rotate Using AI Image Processing Techniques (Matrix Transform)
// Rotates the matrix 90 degrees clockwise using a matrix transform approach.
// Demonstrates a technique used in AI image processing, where matrix transformations are common.
List<List<int>> rotateUsingAI(List<List<int>> matrix) {
  int n = matrix.length;
  // Create a new matrix to store the rotated result.
  List<List<int>> result = List.generate(n, (_) => List<int>.filled(n, 0));
  // Calculate the new coordinates for each element using matrix transformation.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int newX = j; // Calculate the new x coordinate.
      int newY = n - i - 1; // Calculate the new y coordinate.
      result[newX][newY] = matrix[i][j]; // Copy the element to the new position.
    }
  }
  return result; // Return the rotated matrix.
}