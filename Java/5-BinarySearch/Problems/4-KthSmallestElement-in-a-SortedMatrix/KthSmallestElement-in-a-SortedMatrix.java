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

        System.out.println("Kth Smallest Element in the Matrix:");
        System.out.println("Approach 1: Brute Force (Sorting): " + kthSmallest_BruteForce(matrix, k)); // Output: 13
        System.out.println("Approach 2: Max Heap: " + kthSmallest_MaxHeap(matrix, k)); // Output: 13
        System.out.println("Approach 3: Binary Search: " + kthSmallest_BinarySearch(matrix, k)); // Output: 13
        System.out.println("Approach 4: Min Heap with Visited Set: " + kthSmallest_MinHeapWithVisited(matrix, k));
        System.out.println("Approach 5: Min Heap (Optimized): " + kthSmallest_MinHeapOptimized(matrix, k));
    }

    // Approach 1: Brute Force (Sorting)
    // - Time Complexity: O(N^2 log N^2), where N is the number of rows/columns.
    // - Space Complexity: O(N^2)
    // - Description: Flatten the matrix into a 1D array, sort it, and return the kth element.
    public static int kthSmallest_BruteForce(int[][] matrix, int k) {
        int n = matrix.length;
        int[] flattened = new int[n * n];
        int index = 0;
        for (int[] row : matrix) {
            for (int num : row) {
                flattened[index++] = num;
            }
        }
        java.util.Arrays.sort(flattened);
        return flattened[k - 1];
    }

    // Approach 2: Max Heap
    // - Time Complexity: O(N^2 log k), where N is the number of rows/columns.
    // - Space Complexity: O(k)
    // - Description: Use a max heap of size k.  Add all matrix elements to the heap.
    //   If the heap size exceeds k, remove the largest element. The top of the heap
    //   will be the kth smallest element.
    public static int kthSmallest_MaxHeap(int[][] matrix, int k) {
        int n = matrix.length;
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(k, Comparator.reverseOrder());
        for (int[] row : matrix) {
            for (int num : row) {
                maxHeap.add(num);
                if (maxHeap.size() > k) {
                    maxHeap.poll();
                }
            }
        }
        return maxHeap.peek();
    }

    // Approach 3: Binary Search
    // - Time Complexity: O(N log(max - min)), where N is the number of rows/columns,
    //   and max/min are the largest/smallest elements in the matrix.
    // - Space Complexity: O(1)
    // - Description:  The kth smallest element is within the range [min, max]
    //   where min and max are the matrix's smallest and largest elements. Use
    //   binary search to find the target value. For each mid, count how many
    //   elements are <= mid.  Adjust the search range based on this count.
    public static int kthSmallest_BinarySearch(int[][] matrix, int k) {
        int n = matrix.length;
        int low = matrix[0][0];
        int high = matrix[n - 1][n - 1];

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = countElementsLessThanOrEqual(matrix, mid);
            if (count < k) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }

    // Helper function for Binary Search: Count elements <= mid
    private static int countElementsLessThanOrEqual(int[][] matrix, int mid) {
        int n = matrix.length;
        int row = n - 1;
        int col = 0;
        int count = 0;
        while (row >= 0 && col < n) {
            if (matrix[row][col] <= mid) {
                count += row + 1; // All elements in this column up to 'row' are <= mid
                col++;
            } else {
                row--;
            }
        }
        return count;
    }

    // Approach 4: Min Heap with Visited Set
    // - Time Complexity:  O(k log k).  In the worst case, we add k elements to the heap.
    // - Space Complexity: O(k + k) = O(k).  The heap and the visited set can each hold up to k elements.
    // - Description: Use a min heap to store the smallest elements.  Start with the top-left
    //   element.  Repeatedly extract the minimum, add its right and bottom neighbors
    //   to the heap (if they are within bounds and not visited), and mark them as visited.
    //   Do this k times.
    public static int kthSmallest_MinHeapWithVisited(int[][] matrix, int k) {
        int n = matrix.length;
        PriorityQueue<Tuple> minHeap = new PriorityQueue<>(Comparator.comparingInt(t -> t.val));
        boolean[][] visited = new boolean[n][n];

        minHeap.offer(new Tuple(0, 0, matrix[0][0])); // Start with the top-left element
        visited[0][0] = true;

        for (int i = 0; i < k - 1; i++) { // Iterate k-1 times because we already added one element.
            Tuple curr = minHeap.poll();

            int r = curr.row;
            int c = curr.col;

            // Add the right neighbor if it exists and is not visited
            if (r < n - 1 && !visited[r + 1][c]) {
                minHeap.offer(new Tuple(r + 1, c, matrix[r + 1][c]));
                visited[r + 1][c] = true;
            }
            // Add the bottom neighbor if it exists and is not visited
            if (c < n - 1 && !visited[r][c + 1]) {
                minHeap.offer(new Tuple(r, c + 1, matrix[r][c + 1]));
                visited[r][c + 1] = true;
            }
        }
        return minHeap.peek().val; // The kth smallest is at the top of the heap
    }

    // Approach 5: Min Heap (Optimized)
    // - Time Complexity: O(k log k).  Similar to the previous approach, but optimized.
    // - Space Complexity: O(k).  The heap will contain at most k elements.
    // - Description:  Similar to Approach 4 (Min Heap), but optimized to avoid using a fully separate
    //   visited array.  Instead, we track visited cells implicitly within the heap
    //   by only adding a cell to the heap *once*.
    public static int kthSmallest_MinHeapOptimized(int[][] matrix, int k) {
        int n = matrix.length;
        PriorityQueue<Tuple> minHeap = new PriorityQueue<>(Comparator.comparingInt(t -> t.val));

        // Offer the first element (0, 0) with its value.
        minHeap.offer(new Tuple(0, 0, matrix[0][0]));

        int count = 0;
        int result = 0;

        while (count < k) {
            Tuple current = minHeap.poll();
            result = current.val;
            count++;

            int row = current.row;
            int col = current.col;

            // Offer the element below if it exists and hasn't been offered before
            if (row + 1 < n && col == 0) { // Important Optimization: Only add the 'down' element ONCE.
                minHeap.offer(new Tuple(row + 1, col, matrix[row + 1][col]));
            }
            // Offer the element to the right if it exists
            if (col + 1 < n) {
                minHeap.offer(new Tuple(row, col + 1, matrix[row][col + 1]));
            }
        }
        return result;
    }
    // Inner class to represent a cell in the matrix
    static class Tuple {
        int row;
        int col;
        int val;

        public Tuple(int row, int col, int val) {
            this.row = row;
            this.col = col;
            this.val = val;
        }
    }
}

