import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Random;

public class KthLargestElement {

    /**
     * Main method to demonstrate the usage of different approaches to find the Kth largest element.
     *
     * @param args command line arguments (not used in this example)
     */
    public static void main(String[] args) {
        int[] nums = {3, 2, 1, 5, 6, 4};
        int k = 2;

        System.out.println("Input Array: " + Arrays.toString(nums));
        System.out.println("K = " + k);

        // Approach 1: Using Sorting
        int result1 = findKthLargestUsingSorting(nums, k);
        System.out.println("Kth Largest Element (Sorting): " + result1);

        // Approach 2: Using Min Heap (Priority Queue)
        int result2 = findKthLargestUsingMinHeap(nums, k);
        System.out.println("Kth Largest Element (Min Heap): " + result2);

        // Approach 3: Using Max Heap (Priority Queue) - Less efficient but shows the use of Max Heap
        int result3 = findKthLargestUsingMaxHeap(nums, k);
        System.out.println("Kth Largest Element (Max Heap): " + result3);

        // Approach 4: Using QuickSelect (Optimized)
        int[] nums4 = nums.clone(); // Create a copy to avoid modifying the original array
        int result4 = findKthLargestUsingQuickSelect(nums4, k);
        System.out.println("Kth Largest Element (QuickSelect): " + result4);

        // Approach 5: Using QuickSelect (Iterative)
        int[] nums5 = nums.clone();
        int result5 = findKthLargestUsingQuickSelectIterative(nums5, k);
        System.out.println("Kth Largest Element (QuickSelect Iterative): " + result5);
    }

    /**
     * Approach 1: Using Sorting
     * Sorts the array in ascending order and returns the element at the (n-k)th position,
     * which is the kth largest element.
     *
     * Time Complexity: O(n log n) - due to sorting
     * Space Complexity: O(1) or O(n) depending on the sorting algorithm used.  Arrays.sort()
     * in Java uses a variant of quicksort for primitive types, which has
     * O(log n) space complexity in the average case, but can be O(n) in the worst case.
     *
     * @param nums the input array
     * @param k    the kth largest element to find
     * @return the kth largest element in the array
     */
    public static int findKthLargestUsingSorting(int[] nums, int k) {
        // Sort the array in ascending order
        Arrays.sort(nums);
        // Return the element at the (n-k)th position
        return nums[nums.length - k];
    }

    /**
     * Approach 2: Using Min Heap (Priority Queue)
     * Builds a min heap of size k.  Iterates through the array, adding elements to the heap.
     * If the heap size exceeds k, it removes the smallest element (root of the min heap).
     * After processing all elements, the root of the min heap is the kth largest element.
     *
     * Time Complexity: O(n log k) - Building the heap of size k takes O(k) time, and then
     * for each of the remaining (n-k) elements, we potentially add it
     * to the heap and remove the smallest, which takes O(log k) time.
     * Space Complexity: O(k) - for storing the min heap of size k
     *
     * @param nums the input array
     * @param k    the kth largest element to find
     * @return the kth largest element in the array
     */
    public static int findKthLargestUsingMinHeap(int[] nums, int k) {
        // Create a min heap (priority queue)
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        // Iterate through the array
        for (int num : nums) {
            // Add the element to the min heap
            minHeap.add(num);
            // If the heap size exceeds k, remove the smallest element
            if (minHeap.size() > k) {
                minHeap.poll(); // Removes the smallest element (root of min heap)
            }
        }
        // The root of the min heap is the kth largest element
        return minHeap.peek();
    }

    /**
     * Approach 3: Using Max Heap (Priority Queue)
     * Builds a max heap from the entire array, then polls (removes) the largest element k-1 times.
     * The next largest element is the kth largest.
     * This approach is less efficient than using a min heap of size k, but it demonstrates using a max heap.
     *
     * Time Complexity: O(n + k log n)  - Building the max heap takes O(n) time, and then
     * polling k-1 elements takes O(k log n) time.
     * Space Complexity: O(n) - for storing the max heap of size n
     *
     * @param nums the input array
     * @param k    the kth largest element to find
     * @return the kth largest element in the array
     */
    public static int findKthLargestUsingMaxHeap(int[] nums, int k) {
        // Create a max heap (priority queue with reverse order)
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a);

        // Add all elements to the max heap
        for (int num : nums) {
            maxHeap.add(num);
        }

        // Poll (remove) the largest element k-1 times
        for (int i = 0; i < k - 1; i++) {
            maxHeap.poll();
        }
        // The next largest element is the kth largest
        return maxHeap.peek();
    }

    /**
     * Approach 4: Using QuickSelect (Optimized - In-place partitioning)
     * Implements the QuickSelect algorithm, which is a selection algorithm to find the kth
     * smallest element in an unordered list. It is similar to the QuickSort algorithm.
     * The idea is to partition the array around a pivot element such that elements smaller
     * than the pivot are on the left and elements greater than the pivot are on the right.
     * The position of the pivot after partitioning determines which subarray to recurse into.
     * This version uses an iterative approach, which can be slightly more efficient in some cases.
     *
     * Time Complexity: O(n) on average, O(n^2) in the worst case (rare with randomized pivot)
     * Space Complexity: O(1) - in-place partitioning
     *
     * @param nums the input array (will be modified)
     * @param k    the kth largest element to find
     * @return the kth largest element in the array
     */
    public static int findKthLargestUsingQuickSelect(int[] nums, int k) {
        int left = 0;
        int right = nums.length - 1;
        int target = nums.length - k; // Index of the kth largest element

        while (left <= right) {
            // Partition the array around a pivot
            int pivotIndex = partition(nums, left, right);

            if (pivotIndex == target) {
                // Found the kth largest element
                return nums[pivotIndex];
            } else if (pivotIndex < target) {
                // The kth largest element is in the right subarray
                left = pivotIndex + 1;
            } else {
                // The kth largest element is in the left subarray
                right = pivotIndex - 1;
            }
        }
        return -1; //Should not reach here.
    }

    /**
     * Partitions the array around a pivot element.
     *
     * @param nums  the input array
     * @param left  the left index of the subarray to partition
     * @param right the right index of the subarray to partition
     * @return the index of the pivot element after partitioning
     */
    private static int partition(int[] nums, int left, int right) {
        // Choose a random pivot to avoid worst-case scenario (O(n^2))
        int pivotIndex = left + new Random().nextInt(right - left + 1);
        int pivotValue = nums[pivotIndex];
        // Swap pivot with the leftmost element
        swap(nums, left, pivotIndex);
        int storeIndex = left + 1;

        // Partition the array
        for (int i = left + 1; i <= right; i++) {
            if (nums[i] < pivotValue) {
                swap(nums, storeIndex, i);
                storeIndex++;
            }
        }
        // Place the pivot in its correct position
        swap(nums, left, storeIndex - 1);
        return storeIndex - 1;
    }

    /**
     * Swaps two elements in the array.
     *
     * @param nums the input array
     * @param i    the index of the first element to swap
     * @param j    the index of the second element to swap
     */
    private static void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    /**
     * Approach 5: Using QuickSelect (Iterative)
     * An iterative implementation of the QuickSelect algorithm.  It finds the kth largest
     * element in an array by repeatedly partitioning the array and narrowing down the
     * search range.  This avoids recursion and uses a while loop.
     *
     * Time Complexity: O(n) on average, O(n^2) in the worst case.
     * Space Complexity: O(1) -  Operates in place.
     *
     * @param nums the array to search in
     * @param k    the kth largest element to find
     * @return the kth largest element
     */
    public static int findKthLargestUsingQuickSelectIterative(int[] nums, int k) {
        int left = 0;
        int right = nums.length - 1;
        int target = nums.length - k;

        while (left <= right) {
            int pivotIndex = partitionIterative(nums, left, right);

            if (pivotIndex == target) {
                return nums[pivotIndex];
            } else if (pivotIndex < target) {
                left = pivotIndex + 1;
            } else {
                right = pivotIndex - 1;
            }
        }

        return -1; // Should not reach here.
    }

    /**
     * Partitions the specified portion of the array using the last element as the pivot.
     *
     * @param nums The array to partition.
     * @param left The starting index of the portion to partition.
     * @param right The ending index of the portion to partition.
     * @return The final index of the pivot element after partitioning.
     */
    private static int partitionIterative(int[] nums, int left, int right) {
        int pivot = nums[right];  // Choose the rightmost element as the pivot
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (nums[j] <= pivot) {
                i++;
                swap(nums, i, j);
            }
        }
        swap(nums, i + 1, right);
        return i + 1;
    }
}

