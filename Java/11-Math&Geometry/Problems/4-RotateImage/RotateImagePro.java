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

        // Approach 1: Using Extra Space (Auxiliary Matrix)
        int[][] rotated1 = rotateUsingExtraSpace(matrix);
        System.out.println("\nRotated Matrix (Approach 1 - Extra Space):");
        printMatrix(rotated1);

        // Approach 2: In-Place Rotation (Transposing and Reversing)
        int[][] matrix2 = copyMatrix(matrix); // Create a copy to avoid modifying the original
        rotateInPlace(matrix2);
        System.out.println("\nRotated Matrix (Approach 2 - In-Place):");
        printMatrix(matrix2);

        // Approach 3: Using Collections (for demonstration)
        int[][] matrix3 = copyMatrix(matrix);
        rotateUsingCollections(matrix3);
        System.out.println("\nRotated Matrix (Approach 3 - Collections):");
        printMatrix(matrix3);

        // Approach 4: Layer-by-Layer Rotation (Most Efficient In-Place)
        int[][] matrix4 = copyMatrix(matrix);
        rotateLayerByLayer(matrix4);
        System.out.println("\nRotated Matrix (Approach 4 - Layer by Layer):");
        printMatrix(matrix4);

        // Approach 5: Using Java 8 Streams (for demonstration)
        int[][] matrix5 = copyMatrix(matrix);
        rotateUsingStreams(matrix5);
        System.out.println("\nRotated Matrix (Approach 5 - Streams):");
        printMatrix(matrix5);
    }

    // Helper method to print the matrix
    public static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            System.out.println(Arrays.toString(row));
        }
    }

    // Helper method to copy the matrix (to avoid modifying original)
    public static int[][] copyMatrix(int[][] matrix) {
        int rows = matrix.length;
        int cols = matrix[0].length;
        int[][] copy = new int[rows][cols];
        for (int i = 0; i < rows; i++) {
            System.arraycopy(matrix[i], 0, copy[i], 0, cols);
        }
        return copy;
    }

    // Approach 1: Using Extra Space
    // - Create a new matrix with dimensions swapped (n x n becomes n x n).
    // - Copy elements from the original matrix to the new matrix in rotated order.
    // - Time Complexity: O(n^2), Space Complexity: O(n^2)
    public static int[][] rotateUsingExtraSpace(int[][] matrix) {
        int n = matrix.length;
        int[][] rotated = new int[n][n]; // Create a new matrix

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                rotated[j][n - 1 - i] = matrix[i][j]; // Copy elements in rotated order
            }
        }
        return rotated;
    }

    // Approach 2: In-Place Rotation (Transposing and Reversing)
    // - Transpose the matrix (swap rows and columns).
    // - Reverse each row of the transposed matrix.
    // - Time Complexity: O(n^2), Space Complexity: O(1) - In-place
    public static void rotateInPlace(int[][] matrix) {
        int n = matrix.length;

        // Transpose the matrix
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }

        // Reverse each row
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][n - 1 - j];
                matrix[i][n - 1 - j] = temp;
            }
        }
    }

    // Approach 3: Using Collections (for demonstration)
    // - Convert each row to a list.
    // - Reverse the order of the rows.
    // - Reverse each row.
    // - This approach is generally less efficient than the in-place methods.
    // - Time Complexity: O(n^2), Space Complexity: O(n^2)
    public static void rotateUsingCollections(int[][] matrix) {
        int n = matrix.length;
        // Convert the matrix to a list of lists.  This is NOT the most efficient way.
        java.util.List<java.util.List<Integer>> listMatrix = new java.util.ArrayList<>();
        for (int[] row : matrix) {
            java.util.List<Integer> rowList = new java.util.ArrayList<>();
            for (int val : row) {
                rowList.add(val);
            }
            listMatrix.add(rowList);
        }

        // Transpose using Collections
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                Integer temp = listMatrix.get(i).get(j);
                listMatrix.get(i).set(j, listMatrix.get(j).get(i));
                listMatrix.get(j).set(i, temp);
            }
        }

        // Reverse each row using Collections
        for (int i = 0; i < n; i++) {
            java.util.Collections.reverse(listMatrix.get(i));
        }
        // Copy back to the original matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = listMatrix.get(i).get(j);
            }
        }
    }

    // Approach 4: Layer-by-Layer Rotation (Most Efficient In-Place)
    // - Rotate the matrix in layers (outer layer, then inner layer, etc.).
    // - For each layer, rotate the four edges one element at a time.
    // - This is the most efficient in-place rotation method.
    // - Time Complexity: O(n^2), Space Complexity: O(1) - In-place
    public static void rotateLayerByLayer(int[][] matrix) {
        int n = matrix.length;
        for (int layer = 0; layer < n / 2; layer++) {
            int first = layer;
            int last = n - 1 - layer;
            for (int i = first; i < last; i++) {
                int offset = i - first;
                int top = matrix[first][i]; // Save top

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

    // Approach 5: Using Java 8 Streams (for demonstration)
    // - Uses streams to achieve the rotation.
    // - Not the most efficient, but demonstrates functional programming.
    // - Time Complexity: O(n^2), Space Complexity: O(n^2) due to intermediate lists
    public static void rotateUsingStreams(int[][] matrix) {
        int n = matrix.length;
        int[][] rotated = new int[n][n];

        java.util.stream.IntStream.range(0, n).forEach(i ->
                java.util.stream.IntStream.range(0, n).forEach(j ->
                        rotated[j][n - 1 - i] = matrix[i][j]
                )
        );

        // Copy the rotated matrix back into the original
        for (int i = 0; i < n; i++) {
            System.arraycopy(rotated[i], 0, matrix[i], 0, n);
        }
    }
}

