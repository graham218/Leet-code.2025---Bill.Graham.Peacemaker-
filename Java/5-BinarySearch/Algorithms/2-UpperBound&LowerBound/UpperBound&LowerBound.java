import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class BinarySearchBounds {

    /**
     * Main method to test the binary search methods.
     *
     * @param args command line arguments (not used)
     */
    public static void main(String[] args) {
        int[] arr = {2, 5, 5, 5, 6, 8, 8, 11, 12};
        int target = 5;

        System.out.println("Array: " + Arrays.toString(arr));
        System.out.println("Target: " + target);

        // Test Lower Bound methods
        System.out.println("\nLower Bound:");
        System.out.println("  Recursive Approach 1: " + lowerBoundRecursive1(arr, target, 0, arr.length - 1));
        System.out.println("  Recursive Approach 2: " + lowerBoundRecursive2(arr, target, 0, arr.length));
        System.out.println("  Iterative Approach 1: " + lowerBoundIterative1(arr, target));
        System.out.println("  Iterative Approach 2: " + lowerBoundIterative2(arr, target));
        System.out.println("  Iterative Approach 3: " + lowerBoundIterative3(arr, target));


        // Test Upper Bound methods
        System.out.println("\nUpper Bound:");
        System.out.println("  Recursive Approach: " + upperBoundRecursive(arr, target, 0, arr.length - 1));
        System.out.println("  Iterative Approach 1: " + upperBoundIterative1(arr, target));
        System.out.println("  Iterative Approach 2: " + upperBoundIterative2(arr, target));
        System.out.println("  Iterative Approach 3: " + upperBoundIterative3(arr, target));

        //Test edge cases
        int[] arr2 = {1, 2, 3, 4, 5};
        int target2 = 6;
        System.out.println("\nEdge Case Test:");
        System.out.println("Array: " + Arrays.toString(arr2));
        System.out.println("Target: " + target2);
        System.out.println("Lower Bound (Iterative 1): " + lowerBoundIterative1(arr2, target2)); // Should return 5
        System.out.println("Upper Bound (Iterative 1): " + upperBoundIterative1(arr2, target2)); // Should return -1

        int[] arr3 = {1, 1, 1, 1, 1};
        int target3 = 1;
        System.out.println("\nEdge Case Test 2:");
        System.out.println("Array: " + Arrays.toString(arr3));
        System.out.println("Target: " + target3);
        System.out.println("Lower Bound (Iterative 1): " + lowerBoundIterative1(arr3, target3));
        System.out.println("Upper Bound (Iterative 1): " + upperBoundIterative1(arr3, target3));

        int[] arr4 = {1, 2, 3, 4, 5};
        int target4 = 0;
        System.out.println("\nEdge Case Test 3:");
        System.out.println("Array: " + Arrays.toString(arr4));
        System.out.println("Target: " + target4);
        System.out.println("Lower Bound (Iterative 1): " + lowerBoundIterative1(arr4, target4));
        System.out.println("Upper Bound (Iterative 1): " + upperBoundIterative1(arr4, target4));
    }

    // ==========================
    // Lower Bound Implementations
    // ==========================

    /**
     * Recursive implementation of lower bound using binary search.
     * Returns the index of the first element that is greater than or equal to the target.
     * <p>
     * Time Complexity: O(log n)
     * Space Complexity: O(log n) (due to recursion stack)
     *
     * @param arr    The sorted input array.
     * @param target The target value to search for.
     * @param low    The starting index of the search space.
     * @param high   The ending index of the search space.
     * @return The index of the lower bound, or high + 1 if target is greater than all elements.
     */
    public static int lowerBoundRecursive1(int[] arr, int target, int low, int high) {
        if (low > high) {
            return low; // Corrected: Return low, not high+1
        }
        int mid = low + (high - low) / 2; // Prevent overflow
        if (arr[mid] >= target) {
            return lowerBoundRecursive1(arr, target, low, mid - 1);
        } else {
            return lowerBoundRecursive1(arr, target, mid + 1, high);
        }
    }

    /**
     * Recursive implementation of lower bound using binary search.
     * Returns the index of the first element that is greater than or equal to the target.
     * <p>
     * Time Complexity: O(log n)
     * Space Complexity: O(log n) (due to recursion stack)
     *
     * @param arr    The sorted input array.
     * @param target The target value to search for.
     * @param low    The starting index of the search space.
     * @param high   The ending index of the search space (exclusive).
     * @return The index of the lower bound.
     */
    public static int lowerBoundRecursive2(int[] arr, int target, int low, int high) {
        if (low >= high) {
            return low;
        }
        int mid = low + (high - low) / 2;
        if (arr[mid] >= target) {
            return lowerBoundRecursive2(arr, target, low, mid);
        } else {
            return lowerBoundRecursive2(arr, target, mid + 1, high);
        }
    }


    /**
     * Iterative implementation of lower bound using binary search.
     * Returns the index of the first element that is greater than or equal to the target.
     * <p>
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     *
     * @param arr    The sorted input array.
     * @param target The target value to search for.
     * @return The index of the lower bound, or arr.length if target is greater than all elements.
     */
    public static int lowerBoundIterative1(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        int result = arr.length; // Initialize result to a value outside the array bounds

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= target) {
                result = mid; // Update result and search in the left half
                high = mid - 1;
            } else {
                low = mid + 1; // Search in the right half
            }
        }
        return result;
    }

    /**
     * Iterative implementation of lower bound using binary search.
     * Returns the index of the first element that is greater than or equal to the target.
     * <p>
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     *
     * @param arr    The sorted input array.
     * @param target The target value to search for.
     * @return The index of the lower bound.
     */
    public static int lowerBoundIterative2(int[] arr, int target) {
        int low = 0;
        int high = arr.length; // high is exclusive
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= target) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }

    /**
     * Iterative implementation of lower bound using binary search.
     * Returns the index of the first element that is greater than or equal to the target.
     * <p>
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     *
     * @param arr The sorted input array.
     * @param target The target value to search for.
     * @return The index of the lower bound.
     */
    public static int lowerBoundIterative3(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] < target)
                low = mid + 1;
            else
                high = mid;
        }
        return (low < arr.length && arr[low] >= target) ? low : arr.length;
    }


    // ==========================
    // Upper Bound Implementations
    // ==========================

    /**
     * Recursive implementation of upper bound using binary search.
     * Returns the index of the last element that is less than or equal to the target.
     * <p>
     * Time Complexity: O(log n)
     * Space Complexity: O(log n) (due to recursion stack)
     *
     * @param arr    The sorted input array.
     * @param target The target value to search for.
     * @param low    The starting index of the search space.
     * @param high   The ending index of the search space.
     * @return The index of the upper bound, or -1 if target is smaller than all elements.
     */
    public static int upperBoundRecursive(int[] arr, int target, int low, int high) {
        if (low > high) {
            return high; // Corrected: return high
        }
        int mid = low + (high - low) / 2;
        if (arr[mid] <= target) {
            return upperBoundRecursive(arr, target, mid + 1, high);
        } else {
            return upperBoundRecursive(arr, target, low, mid - 1);
        }
    }

    /**
     * Iterative implementation of upper bound using binary search.
     * Returns the index of the last element that is less than or equal to the target.
     * <p>
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     *
     * @param arr    The sorted input array.
     * @param target The target value to search for.
     * @return The index of the upper bound, or -1 if target is smaller than all elements.
     */
    public static int upperBoundIterative1(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        int result = -1; // Initialize result to -1

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] <= target) {
                result = mid; // Update result and search in the right half
                low = mid + 1;
            } else {
                high = mid - 1; // Search in the left half
            }
        }
        return result;
    }

    /**
     * Iterative implementation of upper bound using binary search.
     * Returns the index of the last element that is less than or equal to the target.
     *
     * <p>
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     * @param arr The sorted array
     * @param target The target value
     * @return the upper bound
     */
    public static int upperBoundIterative2(int[] arr, int target) {
        int low = 0;
        int high = arr.length;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] <= target) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low - 1;
    }

    /**
     * Iterative implementation of upper bound using binary search.
     * Returns the index of the last element that is less than or equal to the target.
     * <p>
     * Time Complexity: O(log n)
     * Space Complexity: O(1)
     *
     * @param arr The sorted input array.
     * @param target The target value to search for.
     * @return The index of the upper bound.
     */
    public static int upperBoundIterative3(int[] arr, int target) {
        int low = 0, high = arr.length - 1;
        while (low < high) {
            int mid = low + (high - low + 1) / 2; // Bias towards right
            if (arr[mid] > target)
                high = mid - 1;
            else
                low = mid;
        }
        return (low >= 0 && arr[low] <= target) ? low : -1;
    }
}
