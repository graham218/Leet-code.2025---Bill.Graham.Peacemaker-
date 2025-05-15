import java.util.PriorityQueue;
import java.util.Arrays;

public class MedianOfTwoSortedArrays {

    /*
     * Approach 1: Merge and Find Median
     * - Time Complexity: O(m + n)
     * - Space Complexity: O(m + n)
     * - Description: Merge the two sorted arrays into a single sorted array, then find the median.
     * - Real-world Project Implementation:
     * - Simple to understand and implement.
     * - Suitable for small to medium-sized arrays where space is not a critical concern.
     * - Can be used as a baseline for comparison with more optimized approaches.
     */
    public static double findMedianSortedArrays_Merge(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        int[] merged = new int[m + n];
        int i = 0, j = 0, k = 0;

        // Merge the two sorted arrays
        while (i < m && j < n) {
            if (nums1[i] <= nums2[j]) {
                merged[k++] = nums1[i++];
            } else {
                merged[k++] = nums2[j++];
            }
        }
        while (i < m) {
            merged[k++] = nums1[i++];
        }
        while (j < n) {
            merged[k++] = nums2[j++];
        }

        // Calculate the median
        if ((m + n) % 2 == 0) {
            return (merged[(m + n) / 2 - 1] + merged[(m + n) / 2]) / 2.0;
        } else {
            return merged[(m + n) / 2];
        }
    }

    /*
     * Approach 2: Merge with Two Pointers (Optimized Space)
     * - Time Complexity: O(m + n)
     * - Space Complexity: O(1) - Constant space
     * - Description: Use two pointers to iterate through the arrays without fully merging them.
     * Keep track of the two middle elements.
     * - Real-world Project Implementation:
     * - More space-efficient than Approach 1.
     * - Suitable for scenarios where memory usage is a concern, but the arrays are not extremely large.
     */
    public static double findMedianSortedArrays_TwoPointers(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        int mid = (m + n) / 2;
        int i = 0, j = 0;
        int prev = 0, curr = 0;

        for (int k = 0; k <= mid; k++) {
            prev = curr;
            if (i < m && j < n) {
                if (nums1[i] <= nums2[j]) {
                    curr = nums1[i++];
                } else {
                    curr = nums2[j++];
                }
            } else if (i < m) {
                curr = nums1[i++];
            } else {
                curr = nums2[j++];
            }
        }

        if ((m + n) % 2 == 0) {
            return (prev + curr) / 2.0;
        } else {
            return curr;
        }
    }

    /*
     * Approach 3: Binary Search
     * - Time Complexity: O(log(min(m, n)))
     * - Space Complexity: O(1)
     * - Description: Use binary search on the smaller array to find the correct partition.
     * - Real-world Project Implementation:
     * - The most efficient approach in terms of time complexity.
     * - Preferred for large arrays.
     * - Requires careful handling of edge cases.
     */
    public static double findMedianSortedArrays_BinarySearch(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        // Ensure nums1 is the smaller array to optimize binary search
        if (m > n) {
            return findMedianSortedArrays_BinarySearch(nums2, nums1);
        }

        int low = 0, high = m;
        while (low <= high) {
            int partitionX = (low + high) / 2;
            int partitionY = (m + n + 1) / 2 - partitionX;

            int maxLeftX = (partitionX == 0) ? Integer.MIN_VALUE : nums1[partitionX - 1];
            int minRightX = (partitionX == m) ? Integer.MAX_VALUE : nums1[partitionX];

            int maxLeftY = (partitionY == 0) ? Integer.MIN_VALUE : nums2[partitionY - 1];
            int minRightY = (partitionY == n) ? Integer.MAX_VALUE : nums2[partitionY];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if ((m + n) % 2 == 0) {
                    return (Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY)) / 2.0;
                } else {
                    return Math.max(maxLeftX, maxLeftY);
                }
            } else if (maxLeftX > minRightY) {
                high = partitionX - 1;
            } else {
                low = partitionX + 1;
            }
        }
        throw new IllegalArgumentException("Arrays are not sorted.");
    }

    /*
     * Approach 4: Using Priority Queues (Max Heap and Min Heap)
     * - Time Complexity: O((m+n)log(m+n))  due to adding elements to heaps
     * - Space Complexity: O(m + n)
     * - Description: Use a max heap for the left half and a min heap for the right half.
     * - Real-world Project Implementation:
     * - Useful when you need to maintain a running median as elements are added dynamically.
     * - Can be adapted for online algorithms where data arrives in a stream.
     */
    public static double findMedianSortedArrays_Heaps(int[] nums1, int[] nums2) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a); // Max heap for left half
        PriorityQueue<Integer> minHeap = new PriorityQueue<>(); // Min heap for right half

        for (int num : nums1) {
            addNumberToHeaps(num, maxHeap, minHeap);
        }
        for (int num : nums2) {
            addNumberToHeaps(num, maxHeap, minHeap);
        }

        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.peek() + minHeap.peek()) / 2.0;
        } else {
            return maxHeap.peek();
        }
    }

    private static void addNumberToHeaps(int num, PriorityQueue<Integer> maxHeap, PriorityQueue<Integer> minHeap) {
        if (maxHeap.isEmpty() || num <= maxHeap.peek()) {
            maxHeap.offer(num);
        } else {
            minHeap.offer(num);
        }
        rebalanceHeaps(maxHeap, minHeap);
    }

    private static void rebalanceHeaps(PriorityQueue<Integer> maxHeap, PriorityQueue<Integer> minHeap) {
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.offer(maxHeap.poll());
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.offer(minHeap.poll());
        }
    }

    /*
     * Approach 5: Using Java 8 Streams
     * - Time Complexity: O(m + n) in the worst case, due to the concatenation and sorting.
     * - Space Complexity: O(m + n)
     * - Description:  Uses Java 8 streams to concatenate the two arrays, sort the result, and then calculate
     * the median.  This approach is concise but may not be the most performant for very large arrays.
     * - Real-world Project Implementation:
     * - Good for quick prototyping or when code conciseness is preferred.
     * - May not be suitable for performance-critical applications with very large datasets.
     */
    public static double findMedianSortedArrays_Streams(int[] nums1, int[] nums2) {
        int[] mergedArray = java.util.stream.IntStream.concat(java.util.Arrays.stream(nums1), java.util.Arrays.stream(nums2)).sorted().toArray();
        int length = mergedArray.length;
        if (length % 2 == 0) {
            return (mergedArray[length / 2 - 1] + mergedArray[length / 2]) / 2.0;
        } else {
            return mergedArray[length / 2];
        }
    }

    public static void main(String[] args) {
        int[] nums1 = {1, 3};
        int[] nums2 = {2, 4};

        System.out.println("Approach 1 (Merge): " + findMedianSortedArrays_Merge(nums1, nums2));
        System.out.println("Approach 2 (Two Pointers): " + findMedianSortedArrays_TwoPointers(nums1, nums2));
        System.out.println("Approach 3 (Binary Search): " + findMedianSortedArrays_BinarySearch(nums1, nums2));
        System.out.println("Approach 4 (Heaps): " + findMedianSortedArrays_Heaps(nums1, nums2));
        System.out.println("Approach 5 (Streams): " + findMedianSortedArrays_Streams(nums1, nums2));
    }
}

