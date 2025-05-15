import java.util.Arrays;
import java.util.PriorityQueue;

public class MedianOfTwoSortedArrays {

    public static void main(String[] args) {
        int[] nums1 = {1, 3};
        int[] nums2 = {2, 4};

        // Approach 1: Merge and Sort
        System.out.println("Approach 1: Merge and Sort - Median: " + findMedianUsingMergeAndSort(nums1, nums2));

        // Approach 2: Binary Search
        System.out.println("Approach 2: Binary Search - Median: " + findMedianUsingBinarySearch(nums1, nums2));

        // Approach 3: Using Priority Queues
        System.out.println("Approach 3: Using Priority Queues - Median: " + findMedianUsingPriorityQueues(nums1, nums2));

        // Approach 4: Optimized Merge without extra space (Kth Element)
        System.out.println("Approach 4: Optimized Merge (Kth Element) - Median: " + findMedianUsingKthElement(nums1, nums2));

        // Approach 5: Recursive Binary Search
        System.out.println("Approach 5: Recursive Binary Search - Median: " + findMedianRecursive(nums1, nums2));
    }

    /**
     * Approach 1: Merge and Sort
     * - Merge the two sorted arrays into a single sorted array.
     * - Calculate the median from the merged array.
     * - Time Complexity: O(m + n) for merging, O(m+n log(m+n)) for sorting (if using a comparison sort), O(m+n) if using merge in place.
     * - Space Complexity: O(m + n) for the merged array.
     */
    public static double findMedianUsingMergeAndSort(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        int[] merged = new int[m + n];
        int i = 0, j = 0, k = 0;

        // Merge the two arrays
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
            int mid1 = merged[(m + n) / 2 - 1];
            int mid2 = merged[(m + n) / 2];
            return (double) (mid1 + mid2) / 2.0;
        } else {
            return (double) merged[(m + n) / 2];
        }
    }

    /**
     * Approach 2: Binary Search
     * - Use binary search to find the correct partition point in the smaller array.
     * - The goal is to find a partition where the elements on the left side are smaller
     * than the elements on the right side in the combined array.
     * - Time Complexity: O(log(min(m, n)))
     * - Space Complexity: O(1)
     */
    public static double findMedianUsingBinarySearch(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        // Ensure nums1 is the smaller array to optimize binary search
        if (m > n) {
            return findMedianUsingBinarySearch(nums2, nums1);
        }

        int low = 0, high = m;
        while (low <= high) {
            int partitionX = (low + high) / 2;
            int partitionY = ((m + n + 1) / 2) - partitionX;

            int maxLeftX = (partitionX == 0) ? Integer.MIN_VALUE : nums1[partitionX - 1];
            int minRightX = (partitionX == m) ? Integer.MAX_VALUE : nums1[partitionX];

            int maxLeftY = (partitionY == 0) ? Integer.MIN_VALUE : nums2[partitionY - 1];
            int minRightY = (partitionY == n) ? Integer.MAX_VALUE : nums2[partitionY];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                // Found the correct partition
                if ((m + n) % 2 == 0) {
                    return (double) (Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY)) / 2.0;
                } else {
                    return (double) Math.max(maxLeftX, maxLeftY);
                }
            } else if (maxLeftX > minRightY) {
                // Move towards the left in nums1
                high = partitionX - 1;
            } else {
                // Move towards the right in nums1
                low = partitionX + 1;
            }
        }
        throw new IllegalArgumentException("Arrays are not sorted.");
    }

    /**
     * Approach 3: Using Priority Queues (Heaps)
     * - Use two priority queues (max-heap and min-heap) to store the smaller and larger halves of the combined array.
     * - Balance the heaps to maintain the median efficiently.
     * - Time Complexity: O((m + n)log(m + n))  -- Insert each element into a heap.
     * - Space Complexity: O(m + n)
     */
    public static double findMedianUsingPriorityQueues(int[] nums1, int[] nums2) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>((a, b) -> b - a); // Max-heap for the left half
        PriorityQueue<Integer> minHeap = new PriorityQueue<>(); // Min-heap for the right half

        // Add all elements from both arrays into the heaps
        for (int num : nums1) {
            maxHeap.offer(num);
        }
        for (int num : nums2) {
            maxHeap.offer(num);
        }

        // Balance the heaps
        while (maxHeap.size() > minHeap.size() + 1) {
            minHeap.offer(maxHeap.poll());
        }
        while (minHeap.size() > maxHeap.size()) {
            maxHeap.offer(minHeap.poll());
        }
        // Calculate the median
        if ((nums1.length + nums2.length) % 2 == 0) {
            return (double) (maxHeap.peek() + minHeap.peek()) / 2.0;
        } else {
            return (double) maxHeap.peek();
        }
    }

    /**
     * Approach 4: Optimized Merge (Kth Element)
     * - Find the kth smallest element in the combined array, where k is (m+n)/2.
     * - This approach avoids explicitly merging the arrays and uses a modified binary search approach.
     * - Time Complexity: O(log(m + n))
     * - Space Complexity: O(1)
     */
    public static double findMedianUsingKthElement(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        int k = (m + n) / 2;
        if ((m + n) % 2 == 0) {
            // Even number of elements, average the two middle elements
            return (findKthElement(nums1, 0, m - 1, nums2, 0, n - 1, k) +
                    findKthElement(nums1, 0, m - 1, nums2, 0, n - 1, k - 1)) / 2.0;
        } else {
            // Odd number of elements, return the middle element
            return findKthElement(nums1, 0, m - 1, nums2, 0, n - 1, k);
        }
    }

    private static int findKthElement(int[] nums1, int start1, int end1, int[] nums2, int start2, int end2, int k) {
        int len1 = end1 - start1 + 1;
        int len2 = end2 - start2 + 1;

        // Ensure nums1 is the smaller array
        if (len1 == 0) {
            return nums2[start2 + k];
        }
        if (len2 == 0) {
            return nums1[start1 + k];
        }
        if (k == 0) {
            return Math.min(nums1[start1], nums2[start2]);
        }

        int mid1 = len1 * k / (len1 + len2);
        int mid2 = k - mid1 - 1;

        mid1 += start1;
        mid2 += start2;

        int a = (mid1 < nums1.length) ? nums1[mid1] : Integer.MAX_VALUE;
        int b = (mid2 < nums2.length) ? nums2[mid2] : Integer.MAX_VALUE;
        int c = (mid1 - 1 >= 0) ? nums1[mid1 - 1] : Integer.MIN_VALUE;
        int d = (mid2 - 1 >= 0) ? nums2[mid2 - 1] : Integer.MIN_VALUE;


        if (c > b) {
            return findKthElement(nums1, start1, mid1 - 1, nums2, mid2 + 1, end2, k - (mid2 - start2 + 1));
        } else if (d > a) {
            return findKthElement(nums1, mid1 + 1, end1, nums2, start2, mid2 - 1, k - (mid1 - start1 + 1));
        } else {
            return Math.min(a, b);
        }
    }

    /**
     * Approach 5: Recursive Binary Search
     * - A recursive approach that refines the search range in both arrays.
     * - Similar to the iterative binary search but implemented recursively.
     * - Time Complexity: O(log(min(m, n)))
     * - Space Complexity: O(log(min(m, n))) due to the recursive call stack.
     */
    public static double findMedianRecursive(int[] nums1, int[] nums2) {
        int m = nums1.length;
        int n = nums2.length;
        if (m > n) {
            return findMedianRecursiveHelper(nums2, 0, n - 1, nums1, 0, m - 1, (m + n + 1) / 2);
        } else {
            return findMedianRecursiveHelper(nums1, 0, m - 1, nums2, 0, n - 1, (m + n + 1) / 2);
        }
    }

    private static double findMedianRecursiveHelper(int[] nums1, int start1, int end1, int[] nums2, int start2, int end2, int k) {
        if (start1 > end1) {
            return findMedianFromSingleArray(nums2, start2, end2, k);
        }
        if (start2 > end2) {
            return findMedianFromSingleArray(nums1, start1, end1, k);
        }

        int mid1 = (start1 + end1) / 2;
        int mid2 = (start2 + end2) / 2;

        if (nums1[mid1] <= nums2[mid2]) {
            if (k <= (mid1 - start1) + (mid2 - start2) + 1) {
                return findMedianRecursiveHelper(nums1, start1, end1, nums2, start2, mid2 - 1, k);
            } else {
                return findMedianRecursiveHelper(nums1, mid1 + 1, end1, nums2, start2, end2, k - (mid1 - start1 + 1));
            }
        } else {
            if (k <= (mid1 - start1) + (mid2 - start2) + 1) {
                return findMedianRecursiveHelper(nums1, start1, mid1 - 1, nums2, start2, end2, k);
            } else {
                return findMedianRecursiveHelper(nums1, start1, end1, nums2, mid2 + 1, end2, k - (mid2 - start2 + 1));
            }
        }
    }

    private static double findMedianFromSingleArray(int[] nums, int start, int end, int k) {
        int n = end - start + 1;
        if (n % 2 == 0) {
            if (k == n / 2)
                return (double) (nums[start + k - 1] + nums[start + k]) / 2.0;
            else
                return (double) (nums[start + k - 1] + nums[start + k]) / 2.0; // Corrected index for even case
        } else {
            return (double) nums[start + k - 1];
        }
    }
}

