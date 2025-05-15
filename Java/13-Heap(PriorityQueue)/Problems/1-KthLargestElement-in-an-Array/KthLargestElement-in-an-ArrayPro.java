import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Random;

public class KthLargestElement {

    /**
     * Main method to demonstrate the usage of different approaches to find the Kth largest element.
     *
     * @param args command line arguments (not used)
     */
    public static void main(String[] args) {
        int[] nums = {3, 2, 1, 5, 6, 4};
        int k = 2;

        System.out.println("Input Array: " + Arrays.toString(nums));
        System.out.println("K = " + k);

        // Approach 1: Using Sorting
        int result1 = findKthLargestUsingSorting(nums, k);
        System.out.println("Kth Largest Element (Sorting): " + result1);

        // Approach 2: Using Min-Heap (Priority Queue)
        int result2 = findKthLargestUsingMinHeap(nums, k);
        System.out.println("Kth Largest Element (Min-Heap): " + result2);

        // Approach 3: Using Max-Heap (Priority Queue)
        int result3 = findKthLargestUsingMaxHeap(nums, k);
        System.out.println("Kth Largest Element (Max-Heap): " + result3);

        // Approach 4: Using QuickSelect (Optimized)
        int[] numsCopyForQuickSelect = Arrays.copyOf(nums, nums.length); // Create a copy to avoid modifying original array
        int result4 = findKthLargestUsingQuickSelect(numsCopyForQuickSelect, k);
        System.out.println("Kth Largest Element (QuickSelect): " + result4);

        // Approach 5: Using QuickSelect (Iterative)
        int[] numsCopyForIterativeQuickSelect = Arrays.copyOf(nums, nums.length);
        int result5 = findKthLargestUsingIterativeQuickSelect(numsCopyForIterativeQuickSelect, k);
        System.out.println("Kth Largest Element (Iterative QuickSelect): " + result5);
    }

    /**
     * Approach 1: Using Sorting
     * Sorts the array in descending order and returns the element at index k-1.
     *
     * Time Complexity: O(n log n) - due to sorting
     * Space Complexity: O(1) or O(n) depending on the sorting algorithm (in-place vs. creating a new array)
     *
     * @param nums the input array
     * @param k    the Kth largest element to find
     * @return the Kth largest element in the array
     */
    public static int findKthLargestUsingSorting(int[] nums, int k) {
        // Sort the array in descending order
        Arrays.sort(nums); // Uses Dual-Pivot Quicksort which is typically O(n log n)
        // Return the element at index k-1 (since the array is sorted in ascending order)
        return nums[nums.length - k];
    }

    /**
     * Approach 2: Using Min-Heap (Priority Queue)
     * Maintains a min-heap of size k.  Iterates through the array, adding elements to the heap.
     * If the heap size exceeds k, removes the smallest element.  The root of the heap
     * will be the Kth largest element.
     *
     * Time Complexity: O(n log k) - n is the length of nums, k is the target
     * Space Complexity: O(k) - for the min-heap
     *
     * @param nums the input array
     * @param k    the Kth largest element to find
     * @return the Kth largest element in the array
     */
    public static int findKthLargestUsingMinHeap(int[] nums, int k) {
        // Create a min-heap (priority queue)
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        // Iterate through the array
        for (int num : nums) {
            // Add the current element to the min-heap
            minHeap.add(num);
            // If the size of the min-heap exceeds k, remove the smallest element
            if (minHeap.size() > k) {
                minHeap.poll(); // Removes the smallest element (root of the min-heap)
            }
        }
        // The root of the min-heap is the Kth largest element
        return minHeap.peek();
    }

    /**
     * Approach 3: Using Max-Heap (Priority Queue)
     * Builds a max-heap from the input array, then polls (removes) the top element k-1 times.
     * The next top element will be the Kth largest.
     *
     * Time Complexity: O(n + k log n) - O(n) to build the heap, O(k log n) to extract k elements
     * Space Complexity: O(n) - for the max-heap
     *
     * @param nums the input array
     * @param k    the Kth largest element to find
     * @return the Kth largest element in the array
     */
    public static int findKthLargestUsingMaxHeap(int[] nums, int k) {
        // Create a max-heap (priority queue with reverse order)
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);

        // Add all elements to the max-heap
        for (int num : nums) {
            maxHeap.add(num);
        }

        // Poll (remove) the top element k-1 times
        for (int i = 0; i < k - 1; i++) {
            maxHeap.poll();
        }
        // The next top element is the Kth largest
        return maxHeap.peek();
    }

    /**
     * Approach 4: Using QuickSelect (Optimized - Recursive)
     * Implements the QuickSelect algorithm to find the Kth largest element.  This is an optimization
     * of the QuickSort algorithm, where we only partition the part of the array that contains
     * the Kth largest element.  Uses a recursive approach.
     *
     * Average Time Complexity: O(n) - Linear time on average
     * Worst Case Time Complexity: O(n^2) -  Rare, but possible if the pivot is consistently the smallest/largest element
     * Space Complexity: O(log n) - for the recursive call stack (average case), O(n) in worst case.
     *
     * @param nums the input array
     * @param k    the Kth largest element to find
     * @return the Kth largest element in the array
     */
    public static int findKthLargestUsingQuickSelect(int[] nums, int k) {
        int n = nums.length;
        return quickSelect(nums, 0, n - 1, n - k); // Convert k to index from the start
    }

    /**
     * Recursive helper method for QuickSelect.
     *
     * @param nums  the input array
     * @param low   the starting index of the subarray
     * @param high  the ending index of the subarray
     * @param k     the index of the Kth largest element from the start (0-based)
     * @return the Kth largest element
     */
    private static int quickSelect(int[] nums, int low, int high, int k) {
        // Base case: If the subarray has only one element
        if (low == high) {
            return nums[low];
        }

        // Partition the subarray
        int pivotIndex = partition(nums, low, high);

        // Recursively search in the appropriate subarray
        if (k == pivotIndex) {
            return nums[k];
        } else if (k < pivotIndex) {
            return quickSelect(nums, low, pivotIndex - 1, k);
        } else {
            return quickSelect(nums, pivotIndex + 1, high, k);
        }
    }

    /**
     * Partitions the subarray using the last element as the pivot.
     *
     * @param nums  the input array
     * @param low   the starting index of the subarray
     * @param high  the ending index of the subarray
     * @return the index of the pivot after partitioning
     */
    private static int partition(int[] nums, int low, int high) {
        int pivot = nums[high]; // Choose the last element as the pivot
        int i = low - 1; // Index of the smaller element

        for (int j = low; j < high; j++) {
            // If the current element is smaller than or equal to the pivot
            if (nums[j] <= pivot) {
                i++; // Increment index of smaller element
                // Swap nums[i] and nums[j]
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }

        // Swap nums[i+1] and nums[high] (pivot)
        int temp = nums[i + 1];
        nums[i + 1] = nums[high];
        nums[high] = temp;

        return i + 1; // Return the index of the pivot
    }

    /**
     * Approach 5: Using QuickSelect (Iterative)
     * Iterative version of the QuickSelect algorithm.  Avoids recursion, which can be beneficial
     * in scenarios with very large arrays to prevent stack overflow errors.
     *
     * Average Time Complexity: O(n) - Linear time on average
     * Worst Case Time Complexity: O(n^2) - Rare, but possible
     * Space Complexity: O(1) - Constant space (iterative approach)
     *
     * @param nums the input array
     * @param k    the Kth largest element to find
     * @return the Kth largest element in the array
     */
    public static int findKthLargestUsingIterativeQuickSelect(int[] nums, int k) {
        int n = nums.length;
        int targetIndex = n - k; // Index of the Kth largest element from the start

        int low = 0;
        int high = n - 1;

        while (low <= high) {
            int pivotIndex = partition(nums, low, high);

            if (targetIndex == pivotIndex) {
                return nums[pivotIndex];
            } else if (targetIndex < pivotIndex) {
                high = pivotIndex - 1;
            } else {
                low = pivotIndex + 1;
            }
        }

        return -1; // Should not reach here, but added for completeness
    }
}

