/**
 * Math & Geometry: Rotate Image
 *
 * Problem:
 *
 * You are given a square 2D matrix representing an image. Rotate the image by 90 degrees clockwise.
 *
 * Input:
 *
 * -   matrix: A square 2D array (n x n) of integers.
 *
 * Output:
 *
 * -   The rotated matrix (in-place).  The functions modify the original matrix.
 *
 *
 * Examples:
 *
 * Example 1:
 *
 * Input:
 * [
 * [1, 2, 3],
 * [4, 5, 6],
 * [7, 8, 9]
 * ]
 * Output:
 * [
 * [7, 4, 1],
 * [8, 5, 2],
 * [9, 6, 3]
 * ]
 *
 * Example 2:
 *
 * Input:
 * [
 * [ 5, 1, 9,11],
 * [ 2, 4, 8,10],
 * [13, 3, 6, 7],
 * [15,14,12,16]
 * ]
 * Output:
 * [
 * [15,13, 2, 5],
 * [14, 3, 4, 1],
 * [12, 6, 8, 9],
 * [16, 7,10,11]
 * ]
 *
 */

/**
 * Approach 1: Transpose and Reverse
 *
 * 1.  Transpose the matrix: Swap rows and columns.
 * 2.  Reverse each row.
 *
 * Time Complexity: O(n^2), where n is the dimension of the matrix.
 * Space Complexity: O(1) (in-place)
 */
function rotateImageTransposeReverse(matrix) {
  const n = matrix.length;

  // Transpose the matrix
  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      [matrix[i][j], matrix[j][i]] = [matrix[j][i], matrix[i][j]];
    }
  }

  // Reverse each row
  for (let i = 0; i < n; i++) {
    matrix[i].reverse();
  }
}

/**
 * Approach 2: Layer Rotation
 *
 * Rotate the matrix layer by layer.  For each layer, rotate the elements
 * in a circular fashion.
 *
 * Time Complexity: O(n^2), where n is the dimension of the matrix.
 * Space Complexity: O(1) (in-place)
 */
function rotateImageLayerRotation(matrix) {
  const n = matrix.length;
  for (let layer = 0; layer < Math.floor(n / 2); layer++) {
    const first = layer;
    const last = n - 1 - layer;
    for (let i = first; i < last; i++) {
      const offset = i - first;
      const top = matrix[first][i]; // save top

      // left -> top
      matrix[first][i] = matrix[last - offset][first];

      // bottom -> left
      matrix[last - offset][first] = matrix[last][last - offset];

      // right -> bottom
      matrix[last][last - offset] = matrix[i][last];

      // top -> right
      matrix[i][last] = top; // savedTop
    }
  }
}

/**
 * Approach 3: Using Extra Space (Not In-Place)
 *
 * Create a new matrix and copy the elements to their rotated positions.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 */
function rotateImageExtraSpace(matrix) {
  const n = matrix.length;
  const rotatedMatrix = Array(n)
    .fill(null)
    .map(() => Array(n).fill(0));

  for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
      rotatedMatrix[j][n - 1 - i] = matrix[i][j];
    }
  }

  // Copy back to original matrix (to match in-place requirement)
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
      matrix[i][j] = rotatedMatrix[i][j];
    }
  }
}

/**
 * Approach 4:  Using Built-in reverse and map (Conceptual)
 *
 * This approach uses `reverse()` and `map()`, but it's not strictly in-place
 * as it creates intermediate arrays.  It's included for demonstration.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)  (due to map)
 */
function rotateImageFunctional(matrix) {
  const n = matrix.length;
  const rotated = matrix
    .slice() // Create a shallow copy to avoid modifying original during intermediate steps
    .reverse()
    .map((row, i) => row.map((_, j) => matrix[n - 1 - j][i]));

  // Copy the rotated matrix back into the original
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
      matrix[i][j] = rotated[i][j];
    }
  }
}

/**
 * Approach 5: Optimized Layer Rotation
 *
 * A slight optimization of Approach 2, but with more explicit variable names.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
function rotateImageOptimizedLayer(matrix) {
    const n = matrix.length;
    const layers = Math.floor(n / 2);

    for (let layer = 0; layer < layers; layer++) {
        const first = layer;
        const last = n - 1 - layer;

        for (let i = first; i < last; i++) {
            const offset = i - first;

            // Save the top element
            const topLeft = matrix[first][i];

            // Move left to top
            matrix[first][i] = matrix[last - offset][first];

            // Move bottom to left
            matrix[last - offset][first] = matrix[last][last - offset];

            // Move right to bottom
            matrix[last][last - offset] = matrix[i][last];

            // Move top to right
            matrix[i][last] = topLeft;
        }
    }
}



// Example Usage and Output
const matrix1 = [
  [1, 2, 3],
  [4, 5, 6],
  [7, 8, 9],
];

const matrix2 = [
  [5, 1, 9, 11],
  [2, 4, 8, 10],
  [13, 3, 6, 7],
  [15, 14, 12, 16],
];

console.log("Original Matrix 1:", matrix1);
console.log("Original Matrix 2:", matrix2);

// Approach 1: Transpose and Reverse
let matrix1Copy1 = JSON.parse(JSON.stringify(matrix1)); // Deep copy
rotateImageTransposeReverse(matrix1Copy1);
console.log("Approach 1 (Transpose and Reverse):", matrix1Copy1);

let matrix2Copy1 = JSON.parse(JSON.stringify(matrix2));
rotateImageTransposeReverse(matrix2Copy1);
console.log("Approach 1 (Transpose and Reverse):", matrix2Copy1);

// Approach 2: Layer Rotation
let matrix1Copy2 = JSON.parse(JSON.stringify(matrix1));
rotateImageLayerRotation(matrix1Copy2);
console.log("Approach 2 (Layer Rotation):", matrix1Copy2);

let matrix2Copy2 = JSON.parse(JSON.stringify(matrix2));
rotateImageLayerRotation(matrix2Copy2);
console.log("Approach 2 (Layer Rotation):", matrix2Copy2);

// Approach 3: Using Extra Space
let matrix1Copy3 = JSON.parse(JSON.stringify(matrix1));
rotateImageExtraSpace(matrix1Copy3);
console.log("Approach 3 (Extra Space):", matrix1Copy3);

let matrix2Copy3 = JSON.parse(JSON.stringify(matrix2));
rotateImageExtraSpace(matrix2Copy3);
console.log("Approach 3 (Extra Space):", matrix2Copy3);

// Approach 4: Functional Approach
let matrix1Copy4 = JSON.parse(JSON.stringify(matrix1));
rotateImageFunctional(matrix1Copy4);
console.log("Approach 4 (Functional):", matrix1Copy4);

let matrix2Copy4 = JSON.parse(JSON.stringify(matrix2));
rotateImageFunctional(matrix2Copy4);
console.log("Approach 4 (Functional):", matrix2Copy4);

// Approach 5: Optimized Layer Rotation
let matrix1Copy5 = JSON.parse(JSON.stringify(matrix1));
rotateImageOptimizedLayer(matrix1Copy5);
console.log("Approach 5 (Optimized Layer):", matrix1Copy5);

let matrix2Copy5 = JSON.parse(JSON.stringify(matrix2));
rotateImageOptimizedLayer(matrix2Copy5);
console.log("Approach 5 (Optimized Layer):", matrix2Copy5);
