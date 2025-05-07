import java.util.Arrays;

class MinRotatedSortedArray {

    /**
     * Approach 1: Linear Search
     *
     * Description:
     * - Iterate through the array and compare each element with the current minimum.
     * - Update the minimum if a smaller element is found.
     *
     * Time Complexity: O(n) - Linear time complexity as we iterate through the entire array.
     * Space Complexity: O(1) - Constant space complexity as we only use a few extra variables.
     */
    public int findMinLinearSearch(int[] nums) {
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
     * Approach 2: Using Java's Arrays.sort()
     *
     * Description:
     * - Use Java's built-in Arrays.sort() method to sort the array.
     * - The minimum element will then be at the first index (index 0).
     *
     * Time Complexity: O(n log n) - Time complexity of the Arrays.sort() method.
     * Space Complexity: O(log n) - Space complexity of the Arrays.sort() method (depends on the implementation, but typically O(log n) for merge sort).  It can be O(n) in the worst case.
     */
    public int findMinUsingSort(int[] nums) {
        if (nums == null || nums.length == 0) {
            throw new IllegalArgumentException("Input array cannot be null or empty.");
        }
        int[] copy = Arrays.copyOf(nums, nums.length); // create a copy to avoid modifying the original array.
        Arrays.sort(copy); // Sort the copied array
        return copy[0]; // The minimum element is at index 0
    }

    /**
     * Approach 3: Binary Search (Optimized)
     *
     * Description:
     * - Use Binary Search to efficiently find the minimum element.
     * - The key idea is to identify which half of the array is sorted.
     * - If the left half is sorted, the minimum element is either the first element
     * or in the unsorted right half.
     * - If the right half is sorted, the minimum element is in the unsorted left half.
     *
     * Time Complexity: O(log n) - Logarithmic time complexity due to the use of Binary Search.
     * Space Complexity: O(1) - Constant space complexity as we only use a few extra variables.
     */
    public int findMinBinarySearch(int[] nums) {
        if (nums == null || nums.length == 0) {
            throw new IllegalArgumentException("Input array cannot be null or empty.");
        }

        int left = 0;
        int right = nums.length - 1;

        // If the array is not rotated, the first element is the minimum.
        if (nums[left] <= nums[right]) {
            return nums[left];
        }

        while (left < right) {
            int mid = left + (right - left) / 2; // Prevent potential overflow

            if (nums[mid] > nums[right]) {
                // Minimum element is in the right half
                left = mid + 1;
            } else {
                // Minimum element is in the left half (including mid)
                right = mid;
            }
        }
        return nums[left]; // or nums[right], as left == right at the end
    }

    /**
     * Approach 4: Recursive Binary Search
     *
     * Description:
     * - Implement Binary Search recursively to find the minimum element.
     * - The base case is when the left index is equal to the right index.
     * - Recursively narrow down the search space by half, similar to the iterative approach.
     *
     * Time Complexity: O(log n) - Logarithmic time complexity due to the use of Binary Search.
     * Space Complexity: O(log n) -  Due to the recursive calls.
     */
    public int findMinRecursive(int[] nums) {
        if (nums == null || nums.length == 0) {
            throw new IllegalArgumentException("Input array cannot be null or empty.");
        }
        return findMinRecursiveHelper(nums, 0, nums.length - 1);
    }

    private int findMinRecursiveHelper(int[] nums, int left, int right) {
        if (left == right) {
            return nums[left];
        }

        // If the array is not rotated
        if (nums[left] <= nums[right]) {
            return nums[left];
        }

        int mid = left + (right - left) / 2;

        if (nums[mid] > nums[right]) {
            return findMinRecursiveHelper(nums, mid + 1, right);
        } else {
            return findMinRecursiveHelper(nums, left, mid);
        }
    }

    /**
     * Approach 5:  Iterative Binary Search (Slightly Different Condition)
     *
     * Description:
     * - Another iterative version of binary search, but with a slightly different condition
     * in the while loop and how it updates left and right.
     * - This approach emphasizes the comparison of the middle element with the leftmost.
     *
     * Time Complexity: O(log n) - Logarithmic time complexity.
     * Space Complexity: O(1) - Constant space complexity.
     */
    public int findMinBinarySearchVariant(int[] nums) {
        if (nums == null || nums.length == 0) {
            throw new IllegalArgumentException("Input array cannot be null or empty.");
        }

        int left = 0;
        int right = nums.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[left]) {
                if (nums[left] > nums[right])
                    left = mid;
                else
                    right = mid;
            } else {
                right = mid;
            }
        }
        return nums[left];
    }

    public static void main(String[] args) {
        MinRotatedSortedArray finder = new MinRotatedSortedArray();

        // Test cases
        int[] nums1 = {3, 4, 5, 1, 2};
        int[] nums2 = {4, 5, 6, 7, 0, 1, 2};
        int[] nums3 = {11, 13, 15, 17};
        int[] nums4 = {1};
        int[] nums5 = {2, 1};

        // Test case 1
        System.out.println("Test Case 1: " + Arrays.toString(nums1));
        System.out.println("Linear Search: " + finder.findMinLinearSearch(nums1));
        System.out.println("Using Sort: " + finder.findMinUsingSort(nums1));
        System.out.println("Binary Search: " + finder.findMinBinarySearch(nums1));
        System.out.println("Recursive Binary Search: " + finder.findMinRecursive(nums1));
        System.out.println("Binary Search Variant: " + finder.findMinBinarySearchVariant(nums1));
        System.out.println();

        // Test case 2
        System.out.println("Test Case 2: " + Arrays.toString(nums2));
        System.out.println("Linear Search: " + finder.findMinLinearSearch(nums2));
        System.out.println("Using Sort: " + finder.findMinUsingSort(nums2));
        System.out.println("Binary Search: " + finder.findMinBinarySearch(nums2));
        System.out.println("Recursive Binary Search: " + finder.findMinRecursive(nums2));
        System.out.println("Binary Search Variant: " + finder.findMinBinarySearchVariant(nums2));
        System.out.println();

        // Test case 3
        System.out.println("Test Case 3: " + Arrays.toString(nums3));
        System.out.println("Linear Search: " + finder.findMinLinearSearch(nums3));
        System.out.println("Using Sort: " + finder.findMinUsingSort(nums3));
        System.out.println("Binary Search: " + finder.findMinBinarySearch(nums3));
        System.out.println("Recursive Binary Search: " + finder.findMinRecursive(nums3));
        System.out.println("Binary Search Variant: " + finder.findMinBinarySearchVariant(nums3));
        System.out.println();

        // Test case 4
        System.out.println("Test Case 4: " + Arrays.toString(nums4));
        System.out.println("Linear Search: " + finder.findMinLinearSearch(nums4));
        System.out.println("Using Sort: " + finder.findMinUsingSort(nums4));
        System.out.println("Binary Search: " + finder.findMinBinarySearch(nums4));
        System.out.println("Recursive Binary Search: " + finder.findMinRecursive(nums4));
        System.out.println("Binary Search Variant: " + finder.findMinBinarySearchVariant(nums4));
        System.out.println();

        // Test case 5
        System.out.println("Test Case 5: " + Arrays.toString(nums5));
        System.out.println("Linear Search: " + finder.findMinLinearSearch(nums5));
        System.out.println("Using Sort: " + finder.findMinUsingSort(nums5));
        System.out.println("Binary Search: " + finder.findMinBinarySearch(nums5));
        System.out.println("Recursive Binary Search: " + finder.findMinRecursive(nums5));
        System.out.println("Binary Search Variant: " + finder.findMinBinarySearchVariant(nums5));
        System.out.println();
    }
}

