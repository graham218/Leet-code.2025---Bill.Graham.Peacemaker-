// Rotate Image - 5 Implementation Approaches

// Approach 1: Using a New Matrix (Simple Rotation)
// Time Complexity: O(n²), Space Complexity: O(n²)
function rotateWithNewMatrix(matrix) {
    const n = matrix.length;
    const rotated = new Array(n).fill().map(() => new Array(n).fill(0));

    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            rotated[j][n - 1 - i] = matrix[i][j];
        }
    }

    return rotated;
}

// Approach 2: In-Place Rotation (Transpose + Reverse)
// Time Complexity: O(n²), Space Complexity: O(1)
function rotateInPlace(matrix) {
    const n = matrix.length;

    // Transpose the matrix
    for (let i = 0; i < n; i++) {
        for (let j = i; j < n; j++) {
            [matrix[i][j], matrix[j][i]] = [matrix[j][i], matrix[i][j]];
        }
    }

    // Reverse each row
    for (let i = 0; i < n; i++) {
        matrix[i].reverse();
    }

    return matrix;
}

// Approach 3: Layer-by-Layer Rotation
// Time Complexity: O(n²), Space Complexity: O(1)
function rotateLayerByLayer(matrix) {
    const n = matrix.length;

    for (let layer = 0; layer < Math.floor(n / 2); layer++) {
        const first = layer;
        const last = n - 1 - layer;

        for (let i = first; i < last; i++) {
            const offset = i - first;
            const top = matrix[first][i];

            // left -> top
            matrix[first][i] = matrix[last - offset][first];

            // bottom -> left
            matrix[last - offset][first] = matrix[last][last - offset];

            // right -> bottom
            matrix[last][last - offset] = matrix[i][last];

            // top -> right
            matrix[i][last] = top;
        }
    }

    return matrix;
}

// Approach 4: Using Array Methods (Functional Style)
// Time Complexity: O(n²), Space Complexity: O(n²)
function rotateFunctional(matrix) {
    return matrix[0].map((_, index) =>
        matrix.map(row => row[index]).reverse()
    );
}

// Approach 5: Using String Manipulation (Unconventional)
// Time Complexity: O(n²), Space Complexity: O(n²)
function rotateWithStrings(matrix) {
    const n = matrix.length;
    let str = '';

    // Convert matrix to a special string format
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            str += matrix[i][j] + (j < n - 1 ? ',' : ';');
        }
    }

    // Parse the string in rotated order
    const rotated = new Array(n).fill().map(() => new Array(n));
    const elements = str.split(/[,;]/).filter(x => x !== '');

    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            rotated[j][n - 1 - i] = elements[i * n + j];
        }
    }

    return rotated;
}

// Test Cases
const originalMatrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];

const largeMatrix = [
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
    [13, 14, 15, 16]
];

// Display all outputs
console.log("Original Matrix:");
console.log(originalMatrix);

console.log("\nApproach 1: Using New Matrix");
console.log(rotateWithNewMatrix(originalMatrix));

console.log("\nApproach 2: In-Place Rotation");
console.log(rotateInPlace([...originalMatrix])); // Using spread to avoid modifying original

console.log("\nApproach 3: Layer-by-Layer Rotation");
console.log(rotateLayerByLayer([...originalMatrix]));

console.log("\nApproach 4: Functional Style");
console.log(rotateFunctional(originalMatrix));

console.log("\nApproach 5: Using String Manipulation");
console.log(rotateWithStrings(originalMatrix));

console.log("\nLarge Matrix Test (4x4) - Original:");
console.log(largeMatrix);

console.log("\nLarge Matrix Rotated (Approach 2):");
console.log(rotateInPlace([...largeMatrix]));