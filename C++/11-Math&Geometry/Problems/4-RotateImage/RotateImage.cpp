#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // for iota

using namespace std;

// Function to print the matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Approach 1: Using an auxiliary matrix (simplest, not in-place)
// - Create a new matrix with dimensions swapped (n x n becomes n x n).
// - Copy elements from the original matrix to the new matrix in rotated order.
// - Time Complexity: O(n^2), Space Complexity: O(n^2)
vector<vector<int>> rotateImage_approach1(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> rotated(n, vector<int>(n)); // Initialize new matrix

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            rotated[j][n - 1 - i] = matrix[i][j];
        }
    }
    return rotated;
}

// Approach 2: In-place rotation with layers (most efficient)
// - Rotate the matrix layer by layer.
// - For each layer, rotate the four edges using a temporary variable.
// - Time Complexity: O(n^2), Space Complexity: O(1)
void rotateImage_approach2(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int layer = 0; layer < n / 2; ++layer) {
        int first = layer;
        int last = n - 1 - layer;
        for (int i = first; i < last; ++i) {
            int offset = i - first;
            int top = matrix[first][i]; // save top

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
}

// Approach 3: Using reverse and transpose (in-place)
// - Transpose the matrix (swap rows and columns).
// - Reverse each row of the transposed matrix.
// - Time Complexity: O(n^2), Space Complexity: O(1)
void rotateImage_approach3(vector<vector<int>>& matrix) {
    int n = matrix.size();
    // Transpose the matrix
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    // Reverse each row
    for (int i = 0; i < n; ++i) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

// Approach 4: Using nested loops and swapping (in-place, less optimized than 2)
// - Iterate through half of the matrix.
// - Swap elements in a circular manner for each element in the first half.
// - Time Complexity: O(n^2), Space Complexity: O(1)
void rotateImage_approach4(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[n - 1 - j][i];
            matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
            matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
            matrix[j][n - 1 - i] = temp;
        }
    }
}

// Approach 5: Using std::rotate (In-place, more concise, same efficiency as Approach 2)
// - Similar to approach 2, but uses the standard library function `std::rotate`
// - Time Complexity: O(n^2), Space Complexity: O(1)
void rotateImage_approach5(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int layer = 0; layer < n / 2; ++layer) {
        int first = layer;
        int last = n - 1 - layer;
        for (int i = first; i < last; ++i) {
            int offset = i - first;
            vector<int*> ptrs = {
                &matrix[first][i],
                &matrix[last - offset][first],
                &matrix[last][last - offset],
                &matrix[i][last]
            };
            int temp = *ptrs[0];
            rotate(ptrs.rbegin(), ptrs.rbegin() + 1, ptrs.rend()); // Rotate pointers
            *ptrs[3] = temp;
        }
    }
}

int main() {
    // Example usage
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Original Matrix:" << endl;
    printMatrix(matrix);

    // Approach 1
    vector<vector<int>> rotated1 = rotateImage_approach1(matrix);
    cout << "Rotated Matrix (Approach 1):" << endl;
    printMatrix(rotated1);

    // Approach 2 (in-place)
    vector<vector<int>> matrix2 = matrix; // Make a copy to preserve original
    rotateImage_approach2(matrix2);
    cout << "Rotated Matrix (Approach 2):" << endl;
    printMatrix(matrix2);

    // Approach 3 (in-place)
    vector<vector<int>> matrix3 = matrix;
    rotateImage_approach3(matrix3);
    cout << "Rotated Matrix (Approach 3):" << endl;
    printMatrix(matrix3);

    // Approach 4 (in-place)
    vector<vector<int>> matrix4 = matrix;
    rotateImage_approach4(matrix4);
    cout << "Rotated Matrix (Approach 4):" << endl;
    printMatrix(matrix4);

    // Approach 5 (in-place)
    vector<vector<int>> matrix5 = matrix;
    rotateImage_approach5(matrix5);
    cout << "Rotated Matrix (Approach 5):" << endl;
    printMatrix(matrix5);

    return 0;
}
