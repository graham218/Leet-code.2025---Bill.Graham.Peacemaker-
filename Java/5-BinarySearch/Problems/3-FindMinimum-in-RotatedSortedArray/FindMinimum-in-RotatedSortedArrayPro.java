import java.util.Arrays;

public class FindMinimumInRotatedSortedArray {

    /**
     * Approach 1: Linear Search (Brute Force)
     *
     * Description:
     * - Iterates through the entire array to find the minimum element.
     * - This approach does not utilize the sorted nature of the array, even partially.
     *
     * Time Complexity: O(n) - Linear time, as it iterates through all elements.
     * Space Complexity: O(1) - Constant space, as it only uses a few variables.
     */
    public static int findMinLinearSearch(int[] nums) {
        if (nums == null || nums.length == 0) {
            throw new IllegalArgumentException("Input array cannot be null or empty.");
        }

        int min = nums[0]; // Initialize min with the first element
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] < min) {
                min = nums[i]; // Update min if a smaller element is found
            }
        }
        return min;
    }

    /**
     * Approach 2: Using Java's встроенный (built-in) function (for demonstration)
     *
     * Description:
     * - Uses Java's Streams API to find the minimum element.
     * - This is a concise way to find the minimum but doesn't illustrate the
     * algorithmic concepts of binary search.  Good for quick, non-performance
     * critical code.
     *
     * Time Complexity: O(n) -  The `min()` operation on a stream is generally O(n).
     * Space Complexity: O(1) -  Constant space for the stream operation.
     */
    public static int findMinUsingJavaStream(int[] nums) {
        if (nums == null || nums.length == 0) {
            throw new IllegalArgumentException("Input array cannot be null or empty.");
        }
        return Arrays.stream(nums).min().getAsInt();
    }

    /**
     * Approach 3: Binary Search - Iterative
     *
     * Description:
     * - Implements the classic binary search algorithm to find the minimum element.
     * - It leverages the fact that the rotated array is sorted in two parts.
     * - The key idea is to find the pivot point (the index of the minimum element).
     * - We compare the middle element with the rightmost element:
     * - If middle < right, the minimum is in the left half.
     * - Otherwise, the minimum is in the right half.
     *
     * Time Complexity: O(log n) - Logarithmic time, due to binary search.
     * Space Complexity: O(1) - Constant space, as it uses only a few variables.
     */
    public static int findMinBinarySearchIterative(int[] nums) {
        if (nums == null || nums.length == 0) {
            throw new IllegalArgumentException("Input array cannot be null or empty.");
        }

        int left = 0;
        int right = nums.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2; // Prevent potential overflow
            // Important check for the rotated sorted array condition.
            if (nums[mid] < nums[right]) {
                // Minimum is in the left half, including mid.
                right = mid;
            } else {
                // Minimum is in the right half, excluding mid.
                left = mid + 1;
            }
        }
        // 'left' and 'right' converge to the minimum element's index.
        return nums[left];
    }

    /**
     * Approach 4: Binary Search - Recursive
     *
     * Description:
     * - A recursive version of the binary search approach.
     * - It breaks down the problem into smaller subproblems.
     * - The base case is when the left pointer is equal to the right pointer.
     *
     * Time Complexity: O(log n) - Logarithmic time, due to binary search.
     * Space Complexity: O(log n) - Logarithmic space, due to the recursion call stack.
     */
    public static int findMinBinarySearchRecursive(int[] nums) {
        if (nums == null || nums.length == 0) {
            throw new IllegalArgumentException("Input array cannot be null or empty.");
        }
        return findMinRecursiveHelper(nums, 0, nums.length - 1);
    }

    private static int findMinRecursiveHelper(int[] nums, int left, int right) {
        if (left == right) {
            return nums[left]; // Base case: single element
        }

        int mid = left + (right - left) / 2;
        if (nums[mid] < nums[right]) {
            // Minimum is in the left half
            return findMinRecursiveHelper(nums, left, mid);
        } else {
            // Minimum is in the right half
            return findMinRecursiveHelper(nums, mid + 1, right);
        }
    }
    /**
     * Approach 5: Optimized Binary Search - Handling Duplicates
     *
     * Description:
     * - Handles cases where the input array contains duplicate elements.
     * - In the presence of duplicates, the standard binary search might fail
     * to narrow down the search space effectively.
     * - This approach adds a check to handle the case where nums[mid] == nums[right].
     * - If nums[mid] == nums[right], we can't determine which half contains the minimum
     * element, so we simply reduce the search space by shrinking the right boundary.
     *
     * Time Complexity: O(log n) in the average case, but O(n) in the worst case
     * (when there are many duplicate elements).
     * Space Complexity: O(1) - Constant space.
     */
    public static int findMinBinarySearchOptimized(int[] nums) {
        if (nums == null || nums.length == 0) {
            throw new IllegalArgumentException("Input array cannot be null or empty.");
        }

        int left = 0;
        int right = nums.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] < nums[right]) {
                right = mid;
            } else if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                // Handle duplicate case:  The key change is here.
                right--; // Shrink the right boundary.
            }
        }
        return nums[left];
    }

    public static void main(String[] args) {
        // Test cases
        int[] nums1 = {3, 4, 5, 1, 2};
        int[] nums2 = {4, 5, 6, 7, 0, 1, 2};
        int[] nums3 = {11, 13, 15, 17, 10};
        int[] nums4 = {2, 2, 2, 0, 1}; // Test with duplicates
        int[] nums5 = {1, 3, 3};
        int[] nums6 = {3, 1};

        // Test case with a single element
        int[] nums7 = {5};

        System.out.println("Test Case 1: " + Arrays.toString(nums1));
        System.out.println("Linear Search: " + findMinLinearSearch(nums1));
        System.out.println("Using Java Stream: " + findMinUsingJavaStream(nums1));
        System.out.println("Iterative Binary Search: " + findMinBinarySearchIterative(nums1));
        System.out.println("Recursive Binary Search: " + findMinBinarySearchRecursive(nums1));
        System.out.println("Optimized Binary Search (Duplicates): " + findMinBinarySearchOptimized(nums1));
        System.out.println();

        System.out.println("Test Case 2: " + Arrays.toString(nums2));
        System.out.println("Linear Search: " + findMinLinearSearch(nums2));
        System.out.println("Using Java Stream: " + findMinUsingJavaStream(nums2));
        System.out.println("Iterative Binary Search: " + findMinBinarySearchIterative(nums2));
        System.out.println("Recursive Binary Search: " + findMinBinarySearchRecursive(nums2));
        System.out.println("Optimized Binary Search (Duplicates): " + findMinBinarySearchOptimized(nums2));
        System.out.println();

        System.out.println("Test Case 3: " + Arrays.toString(nums3));
        System.out.println("Linear Search: " + findMinLinearSearch(nums3));
        System.out.println("Using Java Stream: " + findMinUsingJavaStream(nums3));
        System.out.println("Iterative Binary Search: " + findMinBinarySearchIterative(nums3));
        System.out.println("Recursive Binary Search: " + findMinBinarySearchRecursive(nums3));
        System.out.println("Optimized Binary Search (Duplicates): " + findMinBinarySearchOptimized(nums3));
        System.out.println();

        System.out.println("Test Case 4 (Duplicates): " + Arrays.toString(nums4));
        System.out.println("Linear Search: " + findMinLinearSearch(nums4));
        System.out.println("Using Java Stream: " + findMinUsingJavaStream(nums4));
        System.out.println("Iterative Binary Search: " + findMinBinarySearchIterative(nums4));
        System.out.println("Recursive Binary Search: " + findMinBinarySearchRecursive(nums4));
        System.out.println("Optimized Binary Search (Duplicates): " + findMinBinarySearchOptimized(nums4));
        System.out.println();

        System.out.println("Test Case 5: " + Arrays.toString(nums5));
        System.out.println("Linear Search: " + findMinLinearSearch(nums5));
        System.out.println("Using Java Stream: " + findMinUsingJavaStream(nums5));
        System.out.println("Iterative Binary Search: " + findMinBinarySearchIterative(nums5));
        System.out.println("Recursive Binary Search: " + findMinBinarySearchRecursive(nums5));
        System.out.println("Optimized Binary Search (Duplicates): " + findMinBinarySearchOptimized(nums5));
        System.out.println();

        System.out.println("Test Case 6: " + Arrays.toString(nums6));
        System.out.println("Linear Search: " + findMinLinearSearch(nums6));
        System.out.println("Using Java Stream: " + findMinUsingJavaStream(nums6));
        System.out.println("Iterative Binary Search: " + findMinBinarySearchIterative(nums6));
        System.out.println("Recursive Binary Search: " + findMinBinarySearchRecursive(nums6));
        System.out.println("Optimized Binary Search (Duplicates): " + findMinBinarySearchOptimized(nums6));
        System.out.println();

        System.out.println("Test Case 7 (Single Element): " + Arrays.toString(nums7));
        System.out.println("Linear Search: " + findMinLinearSearch(nums7));
        System.out.println("Using Java Stream: " + findMinUsingJavaStream(nums7));
        System.out.println("Iterative Binary Search: " + findMinBinarySearchIterative(nums7));
        System.out.println("Recursive Binary Search: " + findMinBinarySearchRecursive(nums7));
        System.out.println("Optimized Binary Search (Duplicates): " + findMinBinarySearchOptimized(nums7));
        System.out.println();
    }
}

