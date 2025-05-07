import java.util.PriorityQueue;
import java.util.Comparator;

public class KthSmallestInSortedMatrix {

    public static void main(String[] args) {
        int[][] matrix = {
                {1, 5, 9},
                {10, 11, 13},
                {12, 13, 15}
        };
        int k = 8;

        // Test all 5 approaches
        System.out.println("Approach 1: Brute Force (Sorting): " + kthSmallest_BruteForce(matrix, k));
        System.out.println("Approach 2: Min Heap: " + kthSmallest_MinHeap(matrix, k));
        System.out.println("Approach 3: Binary Search: " + kthSmallest_BinarySearch(matrix, k));
        System.out.println("Approach 4: Optimized Min Heap: " + kthSmallest_OptimizedMinHeap(matrix, k));
        System.out.println("Approach 5: Iterative Binary Search: " + kthSmallest_IterativeBinarySearch(matrix, k));
    }

    // Approach 1: Brute Force (Sorting)
    // - Time Complexity: O(N^2 log N^2), where N is the dimension of the matrix.
    // - Space Complexity: O(N^2)
    // - Explanation: Flatten the matrix into a 1D array, sort it, and return the k-th element.
    public static int kthSmallest_BruteForce(int[][] matrix, int k) {
        int n = matrix.length;
        int[] flattened = new int[n * n];
        int index = 0;

        // Flatten the matrix
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                flattened[index++] = matrix[i][j];
            }
        }

        // Sort the flattened array
        java.util.Arrays.sort(flattened);

        // Return the k-th smallest element (k is 1-indexed)
        return flattened[k - 1];
    }

    // Approach 2: Min Heap
    // - Time Complexity: O(k log k), where k is the given k.  Can be O(N^2 log k) in the worst case if k is close to N^2.
    // - Space Complexity: O(k)
    // - Explanation: Use a min-heap to store the smallest elements.  Iterate through the matrix,
    //              offer elements to the heap, and if the heap size exceeds k, remove the largest
    //              element in the heap.  The top of the heap will be the k-th smallest.
    public static int kthSmallest_MinHeap(int[][] matrix, int k) {
        int n = matrix.length;
        PriorityQueue<Integer> minHeap = new PriorityQueue<>(Comparator.reverseOrder());

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                minHeap.offer(matrix[i][j]);
                if (minHeap.size() > k) {
                    minHeap.poll();
                }
            }
        }
        return minHeap.peek();
    }

    // Approach 3: Binary Search
    // - Time Complexity: O(N log(max - min)), where N is the dimension of the matrix,
    //                    and max and min are the maximum and minimum elements in the matrix.
    // - Space Complexity: O(1)
    // - Explanation: Perform binary search on the range of values in the matrix. For each mid value,
    //              count how many elements in the matrix are less than or equal to it.  Adjust the
    //              search range based on this count.
    public static int kthSmallest_BinarySearch(int[][] matrix, int k) {
        int n = matrix.length;
        int low = matrix[0][0];
        int high = matrix[n - 1][n - 1];

        while (low < high) {
            int mid = low + (high - low) / 2;
            int count = countElementsLessThanOrEqual(matrix, mid);
            if (count < k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }

    private static int countElementsLessThanOrEqual(int[][] matrix, int target) {
        int n = matrix.length;
        int row = n - 1;
        int col = 0;
        int count = 0;

        while (row >= 0 && col < n) {
            if (matrix[row][col] <= target) {
                count += row + 1; // Add the entire column up to the current row
                col++;
            } else {
                row--;
            }
        }
        return count;
    }

    // Approach 4: Optimized Min Heap
    // - Time Complexity: O(k log N), where N is the dimension of the matrix.
    // - Space Complexity: O(N)
    // - Explanation:  A min-heap is used, but instead of adding all elements, we start by adding the first row.
    //       Each entry in the heap is an element along with its row and column index.  We repeatedly
    //       extract the minimum, add it to our count, and then add the element below it in the same
    //       column (if it exists) to the heap.  This ensures we only keep at most N elements in the heap.
    public static int kthSmallest_OptimizedMinHeap(int[][] matrix, int k) {
        int n = matrix.length;
        PriorityQueue<Tuple> minHeap = new PriorityQueue<>(Comparator.comparingInt(t -> t.val));

        // Add the first row to the min-heap
        for (int j = 0; j < n; j++) {
            minHeap.offer(new Tuple(matrix[0][j], 0, j));
        }

        int count = 0;
        int result = 0;
        while (count < k) {
            Tuple tuple = minHeap.poll();
            result = tuple.val;
            count++;

            int row = tuple.row;
            int col = tuple.col;
            if (row < n - 1) {
                minHeap.offer(new Tuple(matrix[row + 1][col], row + 1, col));
            }
        }
        return result;
    }

    // Helper class for Optimized Min Heap approach
    private static class Tuple {
        int val;
        int row;
        int col;

        public Tuple(int val, int row, int col) {
            this.val = val;
            this.row = row;
            this.col = col;
        }
    }

    // Approach 5: Iterative Binary Search
    // - Time Complexity: O(N log(max - min)), where N is the dimension of the matrix.
    // - Space Complexity: O(1)
    // - Explanation: This is a non-recursive version of the Binary Search approach.  It uses a while loop
    //   instead of recursion to perform the binary search, but the core logic remains the same.
    public static int kthSmallest_IterativeBinarySearch(int[][] matrix, int k) {
        int n = matrix.length;
        int low = matrix[0][0];
        int high = matrix[n - 1][n - 1];

        while (low <= high) { // Changed condition to low <= high
            int mid = low + (high - low) / 2;
            int count = 0;
            int j = n - 1;

            for (int i = 0; i < n; i++) {
                while (j >= 0 && matrix[i][j] > mid) {
                    j--;
                }
                count += (j + 1); // Important:  j could be -1.
            }

            if (count < k) {
                low = mid + 1;
            } else {
                high = mid - 1; // Changed to high = mid - 1
            }
        }
        return low; // Changed return value to low
    }
}

