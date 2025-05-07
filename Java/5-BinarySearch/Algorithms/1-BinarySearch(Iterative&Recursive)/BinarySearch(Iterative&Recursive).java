import java.util.Arrays;

public class BinarySearch {

    /**
     * Iterative Binary Search - Standard Implementation
     *
     * @param arr   The sorted array to search in.
     * @param target The target value to find.
     * @return The index of the target if found, otherwise -1.
     */
    public static int binarySearchIterative(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2; // Prevent potential overflow
            // Check if the target is present at the middle
            if (arr[mid] == target) {
                return mid;
            }
            // If target is greater, ignore left half
            if (arr[mid] < target) {
                left = mid + 1;
            }
            // If target is smaller, ignore right half
            else {
                right = mid - 1;
            }
        }
        // If we reach here, the target was not found
        return -1;
    }

    /**
     * Recursive Binary Search - Standard Implementation
     *
     * @param arr    The sorted array to search in.
     * @param target The target value to find.
     * @param left   The left boundary of the search space.
     * @param right  The right boundary of the search space.
     * @return The index of the target if found, otherwise -1.
     */
    public static int binarySearchRecursive(int[] arr, int target, int left, int right) {
        if (right >= left) {
            int mid = left + (right - left) / 2; // Prevent potential overflow

            // Check if the target is present at the middle
            if (arr[mid] == target) {
                return mid;
            }
            // If target is smaller than the middle element, recurse in the left half
            if (arr[mid] > target) {
                return binarySearchRecursive(arr, target, left, mid - 1);
            }
            // If target is greater than the middle element, recurse in the right half
            return binarySearchRecursive(arr, target, mid + 1, right);
        }
        // If we reach here, the target was not found
        return -1;
    }

    /**
     * Iterative Binary Search - Alternative Implementation (Slightly different logic)
     * This version might be easier to understand for some, as it explicitly checks
     * for equality *before* narrowing the search space.
     *
     * @param arr   The sorted array to search in.
     * @param target The target value to find.
     * @return The index of the target if found, otherwise -1.
     */
    public static int binarySearchIterativeAlt(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }


    /**
     * Recursive Binary Search - Alternative Implementation (Slightly different logic)
     * This version mirrors the alternative iterative approach.
     *
     * @param arr    The sorted array
     * @param target The target value
     * @param low    The starting index of the search space
     * @param high   The ending index of the search space
     * @return The index of the target, or -1 if not found
     */
    public static int binarySearchRecursiveAlt(int[] arr, int target, int low, int high) {
        if (low > high) { // Changed condition
            return -1;
        }

        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            return binarySearchRecursiveAlt(arr, target, mid + 1, high);
        } else {
            return binarySearchRecursiveAlt(arr, target, low, mid - 1);
        }
    }

    /**
     * Iterative Binary Search with Boundary Check
     * This version includes an explicit check to ensure the 'mid' index
     * is within the array bounds.  While not strictly necessary in standard
     * binary search (if implemented correctly), it adds an extra layer of safety.
     *
     * @param arr The sorted array
     * @param target The target value to search for
     * @return The index of the target value if found, -1 otherwise
     */
    public static int binarySearchIterativeBoundaryCheck(int[] arr, int target) {
        if (arr == null || arr.length == 0) {
            return -1; // Handle empty or null array
        }
        int left = 0;
        int right = arr.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            // Check for out-of-bounds (extra safe, but usually not needed)
            if (mid < 0 || mid >= arr.length) {
                return -1; // Should not happen in a standard, correct implementation, but good to have.
            }

            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        int[] arr = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
        int target = 23;

        System.out.println("Array: " + Arrays.toString(arr));
        System.out.println("Target: " + target);

        // Iterative Binary Search
        int resultIterative = binarySearchIterative(arr, target);
        System.out.println("Iterative Binary Search: Index of " + target + " is " + resultIterative);

        // Recursive Binary Search
        int resultRecursive = binarySearchRecursive(arr, target, 0, arr.length - 1);
        System.out.println("Recursive Binary Search: Index of " + target + " is " + resultRecursive);

        // Alternative Iterative Binary Search
        int resultIterativeAlt = binarySearchIterativeAlt(arr, target);
        System.out.println("Alternative Iterative Binary Search: Index of " + target + " is " + resultIterativeAlt);

        // Alternative Recursive Binary Search
        int resultRecursiveAlt = binarySearchRecursiveAlt(arr, target, 0, arr.length - 1);
        System.out.println("Alternative Recursive Binary Search: Index of " + target + " is " + resultRecursiveAlt);

        // Iterative Binary Search with Boundary Check
        int resultIterativeBoundaryCheck = binarySearchIterativeBoundaryCheck(arr, target);
        System.out.println("Iterative Binary Search with Boundary Check: Index of " + target + " is " + resultIterativeBoundaryCheck);

        // Test case: Target not in array
        target = 100;
        System.out.println("\nTarget: " + target);
        resultIterative = binarySearchIterative(arr, target);
        System.out.println("Iterative Binary Search: Index of " + target + " is " + resultIterative); // Output: -1

        resultRecursive = binarySearchRecursive(arr, target, 0, arr.length - 1);
        System.out.println("Recursive Binary Search: Index of " + target + " is " + resultRecursive); // Output: -1

        resultIterativeAlt = binarySearchIterativeAlt(arr, target);
        System.out.println("Alternative Iterative Binary Search: Index of " + target + " is " + resultIterativeAlt);

        resultRecursiveAlt = binarySearchRecursiveAlt(arr, target, 0, arr.length - 1);
        System.out.println("Alternative Recursive Binary Search: Index of " + target + " is " + resultRecursiveAlt);

        resultIterativeBoundaryCheck = binarySearchIterativeBoundaryCheck(arr, target);
        System.out.println("Iterative Binary Search with Boundary Check: Index of " + target + " is " + resultIterativeBoundaryCheck);
    }
}

