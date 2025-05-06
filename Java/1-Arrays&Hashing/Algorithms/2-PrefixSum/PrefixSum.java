import java.util.Arrays;

public class PrefixSumExamples {

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5};
        int[][] queries = {{1, 3}, {2, 4}, {0, 2}}; // Example queries: {start_index, end_index}

        // Approach 1: Iterative Calculation for Each Query
        System.out.println("Approach 1: Iterative Calculation for Each Query");
        for (int[] query : queries) {
            int sum = prefixSumQueryIterative(arr, query[0], query[1]);
            System.out.println("Sum of query " + Arrays.toString(query) + ": " + sum);
        }

        // Approach 2: Prefix Sum Array - Precompute and Query
        System.out.println("\nApproach 2: Prefix Sum Array - Precompute and Query");
        int[] prefixSumArray = calculatePrefixSum(arr);
        for (int[] query : queries) {
            int sum = prefixSumQuery(prefixSumArray, query[0], query[1]);
            System.out.println("Sum of query " + Arrays.toString(query) + ": " + sum);
        }

        // Approach 3: In-place Prefix Sum Modification
        System.out.println("\nApproach 3: In-place Prefix Sum Modification");
        int[] arrCopy = Arrays.copyOf(arr, arr.length); // Create a copy to avoid modifying original
        inPlacePrefixSum(arrCopy); // Modify the copy
        for (int[] query : queries) {
            int sum = prefixSumQuery(arrCopy, query[0], query[1]);
            System.out.println("Sum of query " + Arrays.toString(query) + ": " + sum);
        }

        // Approach 4: Using Java 8 Streams
        System.out.println("\nApproach 4: Using Java 8 Streams");
        for (int[] query : queries) {
            int sum = prefixSumQueryStreams(arr, query[0], query[1]);
            System.out.println("Sum of query " + Arrays.toString(query) + ": " + sum);
        }

        // Approach 5: 2D Prefix Sum (Example with a 2D array)
        System.out.println("\nApproach 5: 2D Prefix Sum");
        int[][] matrix = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}
        };
        int[][] queries2D = {{0, 0, 1, 1}, {1, 0, 2, 2}}; // {row1, col1, row2, col2}
        int[][] prefixSum2D = calculatePrefixSum2D(matrix);

        for (int[] query : queries2D) {
            int sum = rangeSumQuery2D(prefixSum2D, query[0], query[1], query[2], query[3]);
            System.out.println("Sum of query " + Arrays.toString(query) + ": " + sum);
        }
    }

    // Approach 1: Iterative Calculation for Each Query
    // Calculates the sum for each query by iterating through the array.
    // Time Complexity: O(n) per query, where n is the range size.
    // Space Complexity: O(1)
    public static int prefixSumQueryIterative(int[] arr, int start, int end) {
        int sum = 0;
        for (int i = start; i <= end; i++) {
            sum += arr[i];
        }
        return sum;
    }

    // Approach 2: Prefix Sum Array - Precompute and Query
    // 1. Precomputes the prefix sum array.
    // 2. Uses the prefix sum array to answer queries in O(1) time.
    // Time Complexity: O(n) for precomputation, O(1) per query.
    // Space Complexity: O(n) for the prefix sum array.
    public static int[] calculatePrefixSum(int[] arr) {
        int n = arr.length;
        int[] prefixSum = new int[n];
        prefixSum[0] = arr[0];
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + arr[i];
        }
        return prefixSum;
    }

    // Performs the query on a precomputed prefix sum array.
    public static int prefixSumQuery(int[] prefixSum, int start, int end) {
        if (start == 0) {
            return prefixSum[end];
        }
        return prefixSum[end] - prefixSum[start - 1];
    }

    // Approach 3: In-place Prefix Sum Modification
    // Modifies the original array to store the prefix sums.
    // This approach modifies the input array.
    // Time Complexity: O(n) for precomputation, O(1) per query
    // Space Complexity: O(1) (excluding the input array)
    public static void inPlacePrefixSum(int[] arr) {
        int n = arr.length;
        for (int i = 1; i < n; i++) {
            arr[i] += arr[i - 1];
        }
    }

    // Approach 4: Using Java 8 Streams
    // Uses Java 8 streams to calculate the sum for each query.
    // Demonstrates a more functional approach.
    // Time Complexity: O(n) per query.
    // Space Complexity: O(n) (due to stream operations)
    public static int prefixSumQueryStreams(int[] arr, int start, int end) {
        return Arrays.stream(arr, start, end + 1).sum();
    }

    // Approach 5: 2D Prefix Sum
    // Calculates the prefix sum for a 2D array.
    // Useful for range sum queries in a 2D matrix.
    // Time Complexity: O(m * n) for precomputation, O(1) per query, where m and n are
    // the dimensions of the matrix.
    // Space Complexity: O(m * n) for the prefix sum matrix.

    // Function to calculate the 2D prefix sum array
    public static int[][] calculatePrefixSum2D(int[][] matrix) {
        int rows = matrix.length;
        int cols = matrix[0].length;
        int[][] prefixSum = new int[rows + 1][cols + 1]; // Extra row and column for easier calculation

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                prefixSum[i][j] = matrix[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
            }
        }
        return prefixSum;
    }

    // Function to calculate the sum of a submatrix using the 2D prefix sum
    public static int rangeSumQuery2D(int[][] prefixSum, int row1, int col1, int row2, int col2) {
        // Use prefix sum to find sum of sub-matrix.  Important to understand the formula.
        return prefixSum[row2 + 1][col2 + 1] - prefixSum[row1][col2 + 1] - prefixSum[row2 + 1][col1] + prefixSum[row1][col1];
    }
}

