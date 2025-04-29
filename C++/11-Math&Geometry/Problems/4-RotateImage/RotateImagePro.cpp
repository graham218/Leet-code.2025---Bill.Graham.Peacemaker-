#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // Added for std::iota

// Function to print the matrix
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Approach 1: Using an auxiliary matrix (Naive Approach)
// Time Complexity: O(N^2), Space Complexity: O(N^2)
// Real-world application: Image processing in legacy systems where in-place operations are not feasible
void rotateImage_Approach1(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    std::vector<std::vector<int>> rotated(n, std::vector<int>(n)); // Create a new matrix

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            rotated[j][n - 1 - i] = matrix[i][j]; // Copy elements to their rotated positions
        }
    }
    matrix = rotated; // Assign the rotated matrix back to the original
}

// Approach 2: In-place rotation (Optimized Approach)
// Time Complexity: O(N^2), Space Complexity: O(1)
// Real-world application: Embedded systems or mobile applications with limited memory
void rotateImage_Approach2(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    // Layer by layer rotation
    for (int i = 0; i < (n + 1) / 2; ++i) {
        for (int j = 0; j < n / 2; ++j) {
            int temp = matrix[i][j]; // Store the top element
            matrix[i][j] = matrix[n - 1 - j][i];       // left -> top
            matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j]; // bottom -> left
            matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i]; // right -> bottom
            matrix[j][n - 1 - i] = temp;             // top -> right
        }
    }
}

// Approach 3: Using STL reverse and transpose (Concise)
// Time Complexity: O(N^2), Space Complexity: O(1) - modifies in place
// Real-world application: Rapid prototyping or scripting where code conciseness is preferred
void rotateImage_Approach3(std::vector<std::vector<int>>& matrix) {
    std::reverse(matrix.begin(), matrix.end()); // Reverse the rows
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = i + 1; j < matrix.size(); ++j) {
            std::swap(matrix[i][j], matrix[j][i]); // Transpose the matrix
        }
    }
}

// Approach 4:  Using only swaps (Detailed In-Place)
// Time Complexity: O(N^2), Space Complexity: O(1)
// Real-world application:  Low-level graphics libraries or custom image manipulation routines
void rotateImage_Approach4(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            // Calculate the coordinates of the four elements involved in the rotation
            int top = matrix[i][j];
            int right = matrix[j][n - 1 - i];
            int bottom = matrix[n - 1 - i][n - 1 - j];
            int left = matrix[n - 1 - j][i];

            // Perform the rotation by swapping the elements
            matrix[i][j] = left;
            matrix[j][n - 1 - i] = top;
            matrix[n - 1 - i][n - 1 - j] = right;
            matrix[n - 1 - j][i] = bottom;
        }
    }
}

// Approach 5:  Using iota and index mapping (Illustrative)
// Time Complexity: O(N^2), Space Complexity: O(N^2) - due to the auxiliary vector
// Real-world application:  Educational purposes, demonstrating matrix manipulation with indices
void rotateImage_Approach5(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    std::vector<int> flattened(n * n);
    // Flatten the matrix using iota to fill with indices, then map back.
    std::iota(flattened.begin(), flattened.end(), 0); // Fill with 0, 1, 2, ..., n*n-1

    std::vector<int> rotated_flattened(n * n);
    for (int i = 0; i < n * n; ++i) {
        // Map the original 1D index to 2D coordinates
        int row = i / n;
        int col = i % n;
        // Map the original coordinates to the rotated coordinates, then to 1D index
        int new_row = col;
        int new_col = n - 1 - row;
        int new_index = new_row * n + new_col;
        rotated_flattened[new_index] = matrix[row][col];
    }

    // Copy the rotated values back into the original matrix
    for (int i = 0; i < n * n; ++i) {
        int row = i / n;
        int col = i % n;
        matrix[row][col] = rotated_flattened[i];
    }
}

int main() {
    // Example usage:
    std::vector<std::vector<int>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    std::vector<std::vector<int>> matrix2 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    std::cout << "Original Matrix 1:\n";
    printMatrix(matrix1);

    std::cout << "Original Matrix 2:\n";
    printMatrix(matrix2);

    std::vector<std::vector<int>> mat1_copy1 = matrix1;
    std::vector<std::vector<int>> mat1_copy2 = matrix1;
    std::vector<std::vector<int>> mat1_copy3 = matrix1;
    std::vector<std::vector<int>> mat1_copy4 = matrix1;
    std::vector<std::vector<int>> mat1_copy5 = matrix1;

    std::vector<std::vector<int>> mat2_copy1 = matrix2;
    std::vector<std::vector<int>> mat2_copy2 = matrix2;
    std::vector<std::vector<int>> mat2_copy3 = matrix2;
    std::vector<std::vector<int>> mat2_copy4 = matrix2;
    std::vector<std::vector<int>> mat2_copy5 = matrix2;

    // Rotate using different approaches
    rotateImage_Approach1(mat1_copy1);
    rotateImage_Approach2(mat1_copy2);
    rotateImage_Approach3(mat1_copy3);
    rotateImage_Approach4(mat1_copy4);
    rotateImage_Approach5(mat1_copy5);

    rotateImage_Approach1(mat2_copy1);
    rotateImage_Approach2(mat2_copy2);
    rotateImage_Approach3(mat2_copy3);
    rotateImage_Approach4(mat2_copy4);
    rotateImage_Approach5(mat2_copy5);


    std::cout << "Rotated Matrix 1 (Approach 1):\n";
    printMatrix(mat1_copy1);
    std::cout << "Rotated Matrix 1 (Approach 2):\n";
    printMatrix(mat1_copy2);
    std::cout << "Rotated Matrix 1 (Approach 3):\n";
    printMatrix(mat1_copy3);
    std::cout << "Rotated Matrix 1 (Approach 4):\n";
    printMatrix(mat1_copy4);
    std::cout << "Rotated Matrix 1 (Approach 5):\n";
    printMatrix(mat1_copy5);

    std::cout << "Rotated Matrix 2 (Approach 1):\n";
    printMatrix(mat2_copy1);
    std::cout << "Rotated Matrix 2 (Approach 2):\n";
    printMatrix(mat2_copy2);
    std::cout << "Rotated Matrix 2 (Approach 3):\n";
    printMatrix(mat2_copy3);
    std::cout << "Rotated Matrix 2 (Approach 4):\n";
    printMatrix(mat2_copy4);
    std::cout << "Rotated Matrix 2 (Approach 5):\n";
    printMatrix(mat2_copy5);

    return 0;
}
