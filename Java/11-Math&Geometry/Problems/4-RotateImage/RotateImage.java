import java.util.Arrays;

public class RotateImage {

    public static void main(String[] args) {
        int[][] matrix = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };

        System.out.println("Original Matrix:");
        printMatrix(matrix);

        // Approach 1: Using Extra Space (Creating a new matrix)
        int[][] rotatedMatrix1 = rotateUsingExtraSpace(matrix);
        System.out.println("\nRotated Matrix (Approach 1 - Extra Space):");
        printMatrix(rotatedMatrix1);

        // Approach 2: In-Place Rotation (Optimal)
        int[][] matrix2 = copyMatrix(matrix); // Create a copy to avoid modifying the original
        rotateInPlace(matrix2);
        System.out.println("\nRotated Matrix (Approach 2 - In-Place):");
        printMatrix(matrix2);

        // Approach 3: Layer-by-Layer Rotation
        int[][] matrix3 = copyMatrix(matrix);
        rotateLayerByLayer(matrix3);
        System.out.println("\nRotated Matrix (Approach 3 - Layer by Layer):");
        printMatrix(matrix3);

        // Approach 4: Using Collections (for demonstration)
        int[][] matrix4 = copyMatrix(matrix);
        rotateUsingCollections(matrix4);
        System.out.println("\nRotated Matrix (Approach 4 - Collections):");
        printMatrix(matrix4);

        // Approach 5: Transpose and Reverse
        int[][] matrix5 = copyMatrix(matrix);
        rotateTransposeReverse(matrix5);
        System.out.println("\nRotated Matrix (Approach 5 - Transpose and Reverse):");
        printMatrix(matrix5);
    }

    // Helper method to print the matrix
    public static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            System.out.println(Arrays.toString(row));
        }
    }

    // Helper method to copy the matrix, so original matrix is not changed.
    public static int[][] copyMatrix(int[][] matrix) {
        int rows = matrix.length;
        int cols = matrix[0].length;
        int[][] newMatrix = new int[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                newMatrix[i][j] = matrix[i][j];
            }
        }
        return newMatrix;
    }

    // Approach 1: Using Extra Space
    // - Create a new matrix with dimensions swapped (n x n becomes n x n, but elements are re-arranged).
    // - Copy elements from the original matrix to the new matrix in the rotated order.
    // - Time Complexity: O(n^2), Space Complexity: O(n^2)
    public static int[][] rotateUsingExtraSpace(int[][] matrix) {
        int n = matrix.length;
        int[][] rotatedMatrix = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                rotatedMatrix[j][n - 1 - i] = matrix[i][j];
            }
        }
        return rotatedMatrix;
    }

    // Approach 2: In-Place Rotation (Optimal)
    // - Rotate the matrix in-place by considering it in layers/cycles.
    // - For each layer, rotate the four edges one by one.
    // - This is the most efficient approach in terms of space complexity.
    // - Time Complexity: O(n^2), Space Complexity: O(1)
    public static void rotateInPlace(int[][] matrix) {
        int n = matrix.length;
        for (int i = 0; i < (n + 1) / 2; i++) { // Iterate through layers
            for (int j = 0; j < n / 2; j++) {
                int temp = matrix[i][j]; // Store the top element

                // Rotate elements in a cycle
                matrix[i][j] = matrix[n - 1 - j][i];            // left -> top
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];  // bottom -> left
                matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];  // right -> bottom
                matrix[j][n - 1 - i] = temp;                      // top -> right
            }
        }
    }

    // Approach 3: Layer-by-Layer Rotation (Similar to In-Place, but more explicit)
    public static void rotateLayerByLayer(int[][] matrix) {
        int n = matrix.length;
        for (int layer = 0; layer < n / 2; layer++) {
            int first = layer;
            int last = n - 1 - layer;
            for (int i = first; i < last; i++) {
                int offset = i - first;
                int top = matrix[first][i]; //save top

                //left -> top
                matrix[first][i] = matrix[last - offset][first];

                //bottom -> left
                matrix[last - offset][first] = matrix[last][last - offset];

                //right -> bottom
                matrix[last][last - offset] = matrix[i][last];

                //top -> right
                matrix[i][last] = top; //right
            }
        }
    }

    // Approach 4: Using Collections (Demonstration - Not the most efficient)
    // - This approach uses Java Collections to rotate the matrix.
    // - It's less efficient than the in-place methods due to the overhead of using Collections.
    // - Included for demonstration purposes.
    public static void rotateUsingCollections(int[][] matrix) {
        int n = matrix.length;
        // Transpose the matrix (swap rows and columns)
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
        // Reverse each row
        for (int i = 0; i < n; i++) {
            reverseArray(matrix[i]);
        }
    }

    // Helper method to reverse an array (used in Approach 4)
    private static void reverseArray(int[] arr) {
        int left = 0;
        int right = arr.length - 1;
        while (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }

    // Approach 5: Transpose and Reverse Rows
    // 1. Transpose the matrix: Swap elements across the main diagonal.
    // 2. Reverse each row of the transposed matrix.
    public static void rotateTransposeReverse(int[][] matrix) {
        int n = matrix.length;

        // Transpose the matrix
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) { // Start from i+1 to avoid double swapping
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }

        // Reverse each row
        for (int i = 0; i < n; i++) {
            int left = 0;
            int right = n - 1;
            while (left < right) {
                int temp = matrix[i][left];
                matrix[i][left] = matrix[i][right];
                matrix[i][right] = temp;
                left++;
                right--;
            }
        }
    }
}

