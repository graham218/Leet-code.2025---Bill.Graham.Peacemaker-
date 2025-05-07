import java.util.Arrays;

public class RotatedSortedArraySearch {

    /**
     * Approach 1: Linear Search
     *
     * Description:
     * - Perform a linear search through the array.
     * - Check each element to see if it matches the target.
     * - This approach does not take advantage of the sorted nature of the array, even partially.
     *
     * Time Complexity: O(n) - where n is the length of the array.
     * Space Complexity: O(1) - constant extra space.
     */
    public static int searchLinear(int[] nums, int target) {
        if (nums == null || nums.length == 0) {
            return -1;
        }

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == target) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Approach 2: Using Java's built-in method (for demonstration)
     *
     * Description:
     * - Uses Java's Arrays.binarySearch() method.
     * - This method requires the array to be sorted.  It will NOT work correctly on a rotated array.
     * - This is included for comparison and to show the *incorrect* result you'd get if you directly applied a standard binary search.
     *
     * Time Complexity: O(log n) - if the array were sorted.  In this case, it's not truly applicable.
     * Space Complexity: O(1) - for iterative binary search
     */
    public static int searchBuiltIn(int[] nums, int target) {
        // Arrays.binarySearch requires a sorted array.  This will not work correctly
        // on a rotated sorted array.  It's included here to show the wrong answer.
        return Arrays.binarySearch(nums, target);
    }



    /**
     * Approach 3: Binary Search with Rotation Handling
     *
     * Description:
     * - This is the standard and correct approach.
     * - Find the pivot point (the index of the smallest element).
     * - Apply binary search in the left sorted part or the right sorted part.
     *
     * Time Complexity: O(log n) - where n is the length of the array.
     * Space Complexity: O(1) - constant extra space.
     */
    public static int searchRotatedBinarySearch(int[] nums, int target) {
        if (nums == null || nums.length == 0) {
            return -1;
        }

        int left = 0;
        int right = nums.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2; // Prevent overflow

            if (nums[mid] == target) {
                return mid;
            }

            // Check if the left side is sorted
            if (nums[left] <= nums[mid]) {
                if (target >= nums[left] && target <= nums[mid]) {
                    // Target is in the left sorted part
                    right = mid - 1;
                } else {
                    // Target is in the right unsorted part
                    left = mid + 1;
                }
            } else {
                // The right side is sorted
                if (target >= nums[mid] && target <= nums[right]) {
                    // Target is in the right sorted part
                    left = mid + 1;
                } else {
                    // Target is in the left unsorted part
                    right = mid - 1;
                }
            }
        }
        return -1;
    }


    /**
     * Approach 4: Find Pivot and then Binary Search
     *
     * Description:
     * - Find the pivot point (the index of the smallest element).
     * - Perform binary search on the left side (0 to pivot - 1)
     * - Perform binary search on the right side (pivot to nums.length - 1)
     * - This approach explicitly separates the pivot finding and the binary searches.
     *
     * Time Complexity: O(log n) - where n is the length of the array.
     * Space Complexity: O(1) - constant extra space.
     */
    public static int searchWithPivot(int[] nums, int target) {
        if (nums == null || nums.length == 0) {
            return -1;
        }

        int pivot = findPivot(nums);

        // If pivot is 0, array is not rotated
        if (pivot == 0) {
            return binarySearch(nums, 0, nums.length - 1, target);
        }

        if (target >= nums[0] && target <= nums[pivot - 1]) {
            return binarySearch(nums, 0, pivot - 1, target);
        } else {
            return binarySearch(nums, pivot, nums.length - 1, target);
        }
    }

    // Helper function to find the pivot point (index of the smallest element)
    private static int findPivot(int[] nums) {
        int left = 0;
        int right = nums.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }

    // Helper function for standard binary search
    private static int binarySearch(int[] nums, int left, int right, int target) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    /**
     * Approach 5: Recursive Binary Search with Rotation Handling
     *
     * Description:
     * -  A recursive version of the standard binary search approach for rotated sorted arrays.
     * -  It mirrors the iterative approach (Approach 3) but uses recursion.
     *
     * Time Complexity: O(log n)
     * Space Complexity: O(log n)  Due to the recursion call stack.
     */
    public static int searchRotatedBinarySearchRecursive(int[] nums, int target) {
        if (nums == null || nums.length == 0) {
            return -1;
        }
        return searchRotatedRecursiveHelper(nums, target, 0, nums.length - 1);
    }

    private static int searchRotatedRecursiveHelper(int[] nums, int target, int left, int right) {
        if (left > right) {
            return -1;
        }

        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[left] <= nums[mid]) { // Left part is sorted
            if (target >= nums[left] && target <= nums[mid]) {
                return searchRotatedRecursiveHelper(nums, target, left, mid - 1);
            } else {
                return searchRotatedRecursiveHelper(nums, target, mid + 1, right);
            }
        } else { // Right part is sorted
            if (target >= nums[mid] && target <= nums[right]) {
                return searchRotatedRecursiveHelper(nums, target, mid + 1, right);
            } else {
                return searchRotatedRecursiveHelper(nums, target, left, mid - 1);
            }
        }
    }



    public static void main(String[] args) {
        int[] nums = {4, 5, 6, 7, 0, 1, 2};
        int target = 0;

        System.out.println("Array: " + Arrays.toString(nums));
        System.out.println("Target: " + target);

        System.out.println("\nApproach 1: Linear Search");
        System.out.println("Index: " + searchLinear(nums, target)); // Expected: 4

        System.out.println("\nApproach 2: Using Java's built-in method (Incorrect for rotated array)");
        System.out.println("Index: " + searchBuiltIn(nums, target)); // Expected: -1 (Incorrect)

        System.out.println("\nApproach 3: Binary Search with Rotation Handling");
        System.out.println("Index: " + searchRotatedBinarySearch(nums, target)); // Expected: 4

        System.out.println("\nApproach 4: Find Pivot and then Binary Search");
        System.out.println("Index: " + searchWithPivot(nums, target)); // Expected: 4

        System.out.println("\nApproach 5: Recursive Binary Search with Rotation Handling");
        System.out.println("Index: " + searchRotatedBinarySearchRecursive(nums, target)); // Expected: 4


        // Test case where target is not present
        target = 3;
        System.out.println("\nTarget: " + target);
        System.out.println("\nApproach 3: Binary Search with Rotation Handling");
        System.out.println("Index: " + searchRotatedBinarySearch(nums, target)); // Expected: -1

        // Test case with duplicate elements
        int[] nums2 = {4, 5, 6, 7, 0, 1, 2, 4, 4, 4};
        target = 4;
        System.out.println("\nArray: " + Arrays.toString(nums2));
        System.out.println("Target: " + target);
        System.out.println("\nApproach 3: Binary Search with Rotation Handling (Duplicates)");
        System.out.println("Index: " + searchRotatedBinarySearch(nums2, target)); // Expected: 0 or 7 or 8 or 9 (any of these is correct)

        // Test case: Array with one element
        int[] nums3 = {5};
        target = 5;
        System.out.println("\nArray: " + Arrays.toString(nums3));
        System.out.println("Target: " + target);
        System.out.println("\nApproach 3: Binary Search with Rotation Handling (Single element)");
        System.out.println("Index: " + searchRotatedBinarySearch(nums3, target));  // Expected: 0

        // Test case: Target at the pivot
        int[] nums4 = {4, 5, 6, 7, 0, 1, 2};
        target = 0;
        System.out.println("\nArray: " + Arrays.toString(nums4));
        System.out.println("Target: " + target);
        System.out.println("\nApproach 3: Binary Search with Rotation Handling (Target at pivot)");
        System.out.println("Index: " + searchRotatedBinarySearch(nums4, target)); //Expected 4

        // Test case: Empty array
        int[] nums5 = {};
        target = 5;
        System.out.println("\nArray: " + Arrays.toString(nums5));
        System.out.println("Target: " + target);
        System.out.println("\nApproach 3: Binary Search with Rotation Handling (Empty Array)");
        System.out.println("Index: " + searchRotatedBinarySearch(nums5, target)); // Expected -1
    }
}
