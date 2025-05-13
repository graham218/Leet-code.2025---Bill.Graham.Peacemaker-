import java.util.Arrays;

public class KadanesAlgorithm {

    /**
     * **1. Basic Kadane's Algorithm (Maximum Subarray Sum)**
     *
     * * **Description:** This is the standard implementation of Kadane's algorithm. It efficiently finds the maximum sum of a contiguous subarray within a given array.
     * * **Real-World Application:** Analyzing stock prices to find the period with the maximum profit.  The input array would represent the daily price changes of a stock, and the algorithm would find the most profitable trading window.
     * * **Time Complexity:** O(n), where n is the length of the input array.
     * **Space Complexity:** O(1)
     */
    public static int maxSubarraySum(int[] arr) {
        int maxSoFar = Integer.MIN_VALUE; // Initialize to the smallest possible integer
        int currentMax = 0;

        for (int num : arr) {
            currentMax = Math.max(num, currentMax + num); // Decide to start a new subarray or extend the current one
            maxSoFar = Math.max(maxSoFar, currentMax);    // Update the maximum sum found so far
        }
        return maxSoFar;
    }

    /**
     * **2. Kadane's Algorithm with Start and End Indices**
     *
     * * **Description:** This variation of Kadane's algorithm not only finds the maximum subarray sum but also keeps track of the starting and ending indices of that subarray.
     * * **Real-World Application:** Identifying the most profitable time period in e-commerce sales data.  The input array represents daily sales figures, and the algorithm pinpoints the date range with the highest total sales.
     * * **Time Complexity:** O(n)
     * **Space Complexity:** O(1)
     */
    public static int maxSubarraySumWithIndices(int[] arr) {
        int maxSoFar = Integer.MIN_VALUE;
        int currentMax = 0;
        int start = 0;
        int end = 0;
        int tempStart = 0; // Temporary start index

        for (int i = 0; i < arr.length; i++) {
            int num = arr[i];
            if (num > currentMax + num) { // Start a new subarray
                currentMax = num;
                tempStart = i;        // Update the temporary start index
            } else {
                currentMax = currentMax + num; // Extend the current subarray
            }

            if (currentMax > maxSoFar) { // Update maxSoFar and indices
                maxSoFar = currentMax;
                start = tempStart;
                end = i;
            }
        }

        if (maxSoFar == Integer.MIN_VALUE) {
            return Integer.MIN_VALUE; // Handle the case where all elements are negative
        }

        System.out.println("Start Index: " + start);
        System.out.println("End Index: " + end);
        return maxSoFar;
    }

    /**
     * **3. Kadane's Algorithm with Negative Numbers Only Handling**
     *
     * * **Description:** This version handles arrays where all numbers might be negative.  Instead of returning 0, it returns the largest negative number if all numbers are negative, or the max subarray sum if there are positive numbers.
     * * **Real-World Application:** Analyzing the worst-case performance of a financial portfolio. If all daily returns are negative, it identifies the least negative return (smallest loss).
     * * **Time Complexity:** O(n)
     * * **Space Complexity:** O(1)
     */
    public static int maxSubarraySumNegative(int[] arr) {
        int maxSoFar = Integer.MIN_VALUE;
        int currentMax = 0;
        boolean hasPositive = false; // Flag to check for positive numbers

        for (int num : arr) {
            if (num > 0) {
                hasPositive = true; // Set the flag if a positive number is found
            }
            currentMax = Math.max(num, currentMax + num);
            maxSoFar = Math.max(maxSoFar, currentMax);
        }

        if (!hasPositive) {
            return maxSoFar; // Return the largest negative number if no positive numbers exist
        }
        return maxSoFar;
    }

    /**
     * **4. Kadane's Algorithm with Circular Subarray Handling**
     *
     * * **Description:** This approach handles circular subarrays, where the end of the array is considered to be connected to the beginning. It finds the maximum subarray sum in such a circular array.
     * * **Real-World Application:** Optimizing resource allocation in a circular network.  For example, if the array represents resource availability at different nodes in a ring network, this algorithm can find the maximum contiguous resource availability.
     * * **Time Complexity:** O(n)
     * * **Space Complexity:** O(1)
     */
    public static int maxCircularSubarraySum(int[] arr) {
        int n = arr.length;
        if (n == 0) return 0;

        // 1. Find the maximum subarray sum using standard Kadane's
        int maxSoFar = maxSubarraySum(arr);

        // 2. Find the maximum sum of the inverted subarray
        int minSoFar = Integer.MAX_VALUE;
        int currentMin = 0;
        int totalSum = 0;

        for (int i = 0; i < n; i++) {
            totalSum += arr[i]; // Calculate the total sum of the array
            currentMin = Math.min(arr[i], currentMin + arr[i]);
            minSoFar = Math.min(minSoFar, currentMin);
            arr[i] = -arr[i];    // Invert the array elements
        }

        // 3. Calculate the maximum circular subarray sum
        int circularMax = totalSum + maxSubarraySum(arr); // Max subarray sum of inverted array is actually the min subarray sum of original
        // 4. Return the greater of the regular max subarray sum and the circular max subarray sum.
        if (circularMax == 0)
            return maxSoFar;
        return Math.max(maxSoFar, circularMax);
    }

    /**
     * **5. Kadane's Algorithm for 2D Array (Maximum Submatrix Sum)**
     *
     * * **Description**: This extends Kadane's algorithm to find the maximum sum submatrix within a 2D array.
     * * **Real-World Application**: Image processing, where you might want to find the brightest region in a grayscale image.  The 2D array represents pixel intensities, and the algorithm identifies the submatrix with the highest total intensity.
     * * **Time Complexity**: O(rows * cols^2), where rows is the number of rows and cols is the number of columns.
     * * **Space Complexity**: O(cols)
     */
    public static int maxSubmatrixSum(int[][] matrix) {
        int rows = matrix.length;
        if (rows == 0) return 0;
        int cols = matrix[0].length;
        int maxSum = Integer.MIN_VALUE;

        for (int left = 0; left < cols; left++) {
            int[] temp = new int[rows]; // Array to store the sum of each row for the current column range

            for (int right = left; right < cols; right++) {
                // Calculate the sum of elements for each row between 'left' and 'right' columns
                for (int i = 0; i < rows; i++) {
                    temp[i] += matrix[i][right];
                }

                // Apply 1D Kadane's algorithm to the 'temp' array
                int currentMax = 0;
                for (int num : temp) {
                    currentMax = Math.max(num, currentMax + num);
                    maxSum = Math.max(maxSum, currentMax);
                }
            }
        }
        return maxSum;
    }

    public static void main(String[] args) {
        // Example Usage
        int[] arr1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        System.out.println("1. Maximum Subarray Sum: " + maxSubarraySum(arr1)); // Output: 6

        int[] arr2 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        System.out.println("2. Maximum Subarray Sum with Indices: " + maxSubarraySumWithIndices(arr2)); // Output: 6, Start Index: 3, End Index: 6

        int[] arr3 = {-2, -3, -4, -1, -5};
        System.out.println("3. Maximum Subarray Sum with Negative Numbers: " + maxSubarraySumNegative(arr3)); // Output: -1

        int[] arr4 = {1, -2, 3, -2};
        System.out.println("4. Maximum Circular Subarray Sum: " + maxCircularSubarraySum(arr4)); // Output: 4

        int[][] matrix = {
                {1, -2, -3},
                {-4, 5, -6},
                {-7, 8, 9}
        };
        System.out.println("5. Maximum Submatrix Sum: " + maxSubmatrixSum(matrix));  // Output: 12
        int[][] matrix2 = {
                {1, 2, -1, -4, -20},
                {-8, -3, 4, 2, 1},
                {3, 8, 10, 1, 3},
                {-4, -1, 1, 7, -6}
        };
        System.out.println("5. Maximum Submatrix Sum of matrix2: " + maxSubmatrixSum(matrix2));
    }
}

