import java.util.Arrays;

public class PrefixSum {

    public static void main(String[] args) {
        int[] data = {2, 5, 1, 8, 3, 7};
        int[] prefixSum;

        // 1. Basic Prefix Sum
        prefixSum = basicPrefixSum(data);
        System.out.println("1. Basic Prefix Sum: " + Arrays.toString(prefixSum)); // Output: [2, 7, 8, 16, 19, 26]

        // 2. Prefix Sum with Cumulative Sum (In-place)
        int[] data2 = {2, 5, 1, 8, 3, 7}; // Create a new array to avoid modifying the original
        cumulativeSum(data2);
        System.out.println("2. Cumulative Sum (In-place): " + Arrays.toString(data2)); // Output: [2, 7, 8, 16, 19, 26]

        // 3. Prefix Sum for Range Queries
        int[][] queries = {{1, 3}, {2, 5}, {0, 4}}; // Example queries (start, end)
        prefixSum = basicPrefixSum(data); // Use the basic prefix sum array
        for (int[] query : queries) {
            int sum = rangeSumQuery(prefixSum, query[0], query[1]);
            System.out.println("3. Range Sum Query [" + query[0] + ", " + query[1] + "]: " + sum);
        }
        // Expected outputs: 14, 19, 19

        // 4. 2D Prefix Sum (Image Processing Example)
        int[][] image = {
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12},
                {13, 14, 15, 16}
        };
        int[][] prefixSum2D = prefixSum2D(image);

        System.out.println("4. 2D Prefix Sum:");
        for (int[] row : prefixSum2D) {
            System.out.println(Arrays.toString(row));
        }
        // Expected output
        //[1, 3, 6, 10]
        //[5, 11, 18, 26]
        //[9, 25, 43, 62]
        //[13, 33, 54, 75]

        int[] query2D = {1, 1, 3, 3}; // Example query: sub-rectangle from (1,1) to (3,3)
        int sum2D = rangeSumQuery2D(prefixSum2D, query2D[0], query2D[1], query2D[2], query2D[3]);
        System.out.println("   2D Range Sum Query (" + query2D[0] + "," + query2D[1] + ") to (" + query2D[2] + "," + query2D[3] + "): " + sum2D); //52

        // 5. Prefix Sum with Negative Numbers
        int[] dataWithNegatives = {-2, 3, -1, 5, -4, 2};
        int[] prefixSumWithNegatives = basicPrefixSum(dataWithNegatives);
        System.out.println("5. Prefix Sum with Negative Numbers: " + Arrays.toString(prefixSumWithNegatives));
        //Output: [-2, 1, 0, 5, 1, 3]

        int[] negativeQuery = {0, 5};
        int sumWithNegatives = rangeSumQuery(prefixSumWithNegatives, negativeQuery[0], negativeQuery[1]);
        System.out.println("   Range Sum Query [" + negativeQuery[0] + ", " + negativeQuery[1] + "]: " + sumWithNegatives); // 3
    }

    /**
     * 1. Basic Prefix Sum Calculation
     *
     * Calculates the prefix sum of an array.
     * The prefix sum at index i is the sum of all elements from index 0 to i.
     *
     * @param arr The input array.
     * @return A new array containing the prefix sums.
     */
    public static int[] basicPrefixSum(int[] arr) {
        if (arr == null || arr.length == 0) {
            return new int[0]; // Handle empty or null input
        }
        int[] prefixSum = new int[arr.length];
        prefixSum[0] = arr[0]; // The first element is the same
        for (int i = 1; i < arr.length; i++) {
            prefixSum[i] = prefixSum[i - 1] + arr[i];
        }
        return prefixSum;
    }

    /**
     * 2. Cumulative Sum (In-place)
     *
     * Calculates the cumulative sum of an array, modifying the array in-place.
     * This is useful when you want to save space and don't need the original array.
     *
     * @param arr The input array (will be modified).
     */
    public static void cumulativeSum(int[] arr) {
        if (arr == null || arr.length == 0) {
            return; // Handle empty or null input
        }
        for (int i = 1; i < arr.length; i++) {
            arr[i] += arr[i - 1]; // arr[i] now stores the cumulative sum up to i
        }
    }

    /**
     * 3. Range Sum Query using Prefix Sum
     *
     * Uses a pre-calculated prefix sum array to efficiently find the sum of elements
     * within a specified range (start to end, inclusive).
     *
     * @param prefixSum The prefix sum array.
     * @param start     The starting index of the range (inclusive).
     * @param end       The ending index of the range (inclusive).
     * @return The sum of the elements in the specified range.
     */
    public static int rangeSumQuery(int[] prefixSum, int start, int end) {
        if (prefixSum == null || prefixSum.length == 0 || start < 0 || end >= prefixSum.length || start > end) {
            return 0; // Handle invalid input
        }
        if (start == 0) {
            return prefixSum[end]; // Sum from 0 to end is just prefixSum[end]
        } else {
            return prefixSum[end] - prefixSum[start - 1]; // Sum from start to end
        }
    }

    /**
     * 4. 2D Prefix Sum Calculation
     *
     * Calculates the 2D prefix sum for a 2D array (matrix).  This allows for
     * efficient calculation of the sum of elements within any rectangular sub-region
     * of the matrix.  This is useful in image processing.
     *
     * @param matrix The input 2D array (matrix).
     * @return A new 2D array containing the 2D prefix sums.
     */
    public static int[][] prefixSum2D(int[][] matrix) {
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0) {
            return new int[0][0]; // Handle null or empty input
        }

        int rows = matrix.length;
        int cols = matrix[0].length;
        int[][] prefixSum = new int[rows][cols];

        // Calculate the first element of the prefix sum matrix.
        prefixSum[0][0] = matrix[0][0];

        // Calculate the prefix sum for the first row.
        for (int j = 1; j < cols; j++) {
            prefixSum[0][j] = prefixSum[0][j - 1] + matrix[0][j];
        }
        // Calculate the prefix sum for the first column
        for (int i = 1; i < rows; i++) {
            prefixSum[i][0] = prefixSum[i - 1][0] + matrix[i][0];
        }

        // Calculate the prefix sum for the rest of the matrix.
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {
                prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + matrix[i][j];
            }
        }
        return prefixSum;
    }

    /**
     * 5. 2D Range Sum Query
     *
     * Calculates the sum of elements within a rectangular sub-region of a 2D matrix,
     * using a pre-computed 2D prefix sum array.
     *
     * @param prefixSum  The 2D prefix sum array.
     * @param row1       The row index of the top-left corner of the sub-rectangle (inclusive).
     * @param col1       The column index of the top-left corner of the sub-rectangle (inclusive).
     * @param row2       The row index of the bottom-right corner of the sub-rectangle (inclusive).
     * @param col2       The column index of the bottom-right corner of the sub-rectangle (inclusive).
     * @return The sum of the elements within the specified sub-rectangle.
     */
    public static int rangeSumQuery2D(int[][] prefixSum, int row1, int col1, int row2, int col2) {
        if (prefixSum == null || prefixSum.length == 0 || prefixSum[0].length == 0 ||
                row1 < 0 || col1 < 0 || row2 >= prefixSum.length || col2 >= prefixSum[0].length ||
                row1 > row2 || col1 > col2) {
            return 0; // Handle invalid input
        }

        // Use the 2D prefix sum to calculate the sub-rectangle sum
        int sum = prefixSum[row2][col2]; // Sum of the rectangle from (0,0) to (row2,col2)

        if (row1 > 0) {
            sum -= prefixSum[row1 - 1][col2]; // Subtract the sum of the rectangle above the desired one
        }
        if (col1 > 0) {
            sum -= prefixSum[row2][col1 - 1]; // Subtract the sum of the rectangle to the left of the desired one
        }
        if (row1 > 0 && col1 > 0) {
            sum += prefixSum[row1 - 1][col1 - 1]; // Add back the overlapping region (subtracted twice)
        }
        return sum;
    }
}

