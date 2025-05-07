import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.List;
import java.util.ArrayList;

public class BinarySearch {

    /**
     * 1. Iterative Binary Search (Basic Implementation)
     *
     * -   Description: This is the most straightforward implementation of binary search.  It uses a `while` loop
     * to repeatedly divide the search space in half.
     * -   Real-world application: Searching for a specific entry in a sorted database table (e.g., searching for a
     * customer by ID in a customer database).  This is a fundamental algorithm used in database systems.
     * -   Error Handling:  Handles the case where the target is not found.
     * -   Assumptions: The input array is sorted.
     * -   Time Complexity: O(log n)
     * -   Space Complexity: O(1)
     *
     * @param array The sorted array to search in.
     * @param target The value to search for.
     * @return The index of the target if found, otherwise -1.
     */
    public static int iterativeBinarySearch(int[] array, int target) {
        int low = 0;
        int high = array.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevent potential overflow

            if (array[mid] == target) {
                return mid;
            } else if (array[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1; // Target not found
    }

    /**
     * 2. Recursive Binary Search
     *
     * -   Description: This implementation uses recursion to repeatedly divide the search space.
     * -   Real-world application:  Implementing a search function in a file system or directory structure,
     * where subdirectories can be thought of as subproblems.  Less common than the iterative approach
     * in production due to potential stack overflow issues with very large datasets, but useful for
     * understanding the divide-and-conquer paradigm.
     * -   Error Handling: Handles the base case (target not found).
     * -   Assumptions: The input array is sorted.
     * -   Time Complexity: O(log n)
     * -   Space Complexity: O(log n) due to the recursive call stack.
     *
     * @param array The sorted array to search in.
     * @param target The value to search for.
     * @param low   The starting index of the search space.
     * @param high  The ending index of the search space.
     * @return The index of the target if found, otherwise -1.
     */
    public static int recursiveBinarySearch(int[] array, int target, int low, int high) {
        if (low > high) {
            return -1; // Base case: target not found
        }

        int mid = low + (high - low) / 2;

        if (array[mid] == target) {
            return mid;
        } else if (array[mid] < target) {
            return recursiveBinarySearch(array, target, mid + 1, high);
        } else {
            return recursiveBinarySearch(array, target, low, mid - 1);
        }
    }

    // Overload for easier initial call.  This is good practice for user-friendly APIs.
    public static int recursiveBinarySearch(int[] array, int target) {
        return recursiveBinarySearch(array, target, 0, array.length - 1);
    }


    /**
     * 3. Binary Search with Duplicates Handling (Find First Occurrence)
     *
     * -   Description: This version of binary search is modified to find the *first* occurrence of a target
     * value in a sorted array that may contain duplicate elements.
     * -   Real-world application:  Finding the first record with a specific timestamp in a log file, or the
     * first occurrence of a product in a sorted list of search results where duplicates are possible.
     * -   Error Handling:  Handles the case where the target is not found.
     * -   Assumptions: The input array is sorted.
     * -   Time Complexity: O(log n)
     * -   Space Complexity: O(1)
     *
     * @param array The sorted array to search in.
     * @param target The value to search for.
     * @return The index of the *first* occurrence of the target, or -1 if not found.
     */
    public static int binarySearchFirstOccurrence(int[] array, int target) {
        int low = 0;
        int high = array.length - 1;
        int result = -1; // Initialize result to -1 (not found)

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (array[mid] == target) {
                result = mid;     // Found a match, but keep searching for the first one
                high = mid - 1;   // Search in the left half
            } else if (array[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return result;
    }

    /**
     * 4. Binary Search with Duplicates Handling (Find Last Occurrence)
     *
     * -   Description: This version of binary search is modified to find the *last* occurrence of a target
     * value in a sorted array that may contain duplicate elements.
     * -   Real-world application: Finding the last record with a specific timestamp in a log file, or the
     * last occurrence of a product in a sorted list.  Useful in scenarios where you need to know the
     * end of a range of identical values.
     * -   Error Handling: Handles the case where the target is not found.
     * -   Assumptions: The input array is sorted.
     * -   Time Complexity: O(log n)
     * -   Space Complexity: O(1)
     *
     * @param array The sorted array to search in.
     * @param target The value to search for.
     * @return The index of the *last* occurrence of the target, or -1 if not found.
     */
    public static int binarySearchLastOccurrence(int[] array, int target) {
        int low = 0;
        int high = array.length - 1;
        int result = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (array[mid] == target) {
                result = mid;       // Found a match, but keep searching for the last one
                low = mid + 1;     // Search in the right half
            } else if (array[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return result;
    }

    /**
     * 5. Binary Search in a Rotated Sorted Array
     *
     * -  Description: This is a more complex variation where the sorted array has been rotated
     * by an unknown number of positions.  For example, [4, 5, 6, 7, 0, 1, 2].  This implementation
     * finds the target in such a rotated array.
     * -  Real-world application: Searching for data in a circularly shifted log file or in a
     * database table that has been partitioned and reordered.  This is a good example of
     * how binary search can be adapted to non-standard sorted data.
     * -  Error Handling: Handles the case where the target is not found.
     * -  Assumptions: The array was originally sorted, then rotated.
     * -  Time Complexity: O(log n)
     * -  Space Complexity: O(1)
     *
     * @param array The rotated sorted array.
     * @param target The value to search for.
     * @return The index of the target if found, otherwise -1.
     */
    public static int binarySearchRotated(int[] array, int target) {
        int low = 0;
        int high = array.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (array[mid] == target) {
                return mid;
            }

            // Check if the left half is sorted
            if (array[low] <= array[mid]) {
                if (target >= array[low] && target <= array[mid]) {
                    // Target is in the sorted left half
                    high = mid - 1;
                } else {
                    // Target is in the unsorted right half
                    low = mid + 1;
                }
            } else {
                // The right half is sorted
                if (target >= array[mid] && target <= array[high]) {
                    // Target is in the sorted right half
                    low = mid + 1;
                } else {
                    // Target is in the unsorted left half
                    high = mid - 1;
                }
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        int[] sortedArray = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
        int target = 23;

        System.out.println("Sorted Array: " + Arrays.toString(sortedArray));
        System.out.println("Target Value: " + target);
        System.out.println();

        // 1. Iterative Binary Search
        int iterativeResult = iterativeBinarySearch(sortedArray, target);
        System.out.println("1. Iterative Binary Search:");
        if (iterativeResult != -1) {
            System.out.println("Target found at index: " + iterativeResult);
        } else {
            System.out.println("Target not found.");
        }
        System.out.println();

        // 2. Recursive Binary Search
        int recursiveResult = recursiveBinarySearch(sortedArray, target);
        System.out.println("2. Recursive Binary Search:");
        if (recursiveResult != -1) {
            System.out.println("Target found at index: " + recursiveResult);
        } else {
            System.out.println("Target not found.");
        }
        System.out.println();

        // 3. Binary Search with Duplicates (First Occurrence)
        int[] duplicateArray = {2, 5, 5, 5, 6, 6, 8, 9};
        target = 5;
        System.out.println("Array with Duplicates: " + Arrays.toString(duplicateArray));
        System.out.println("Target Value: " + target);
        int firstOccurrenceResult = binarySearchFirstOccurrence(duplicateArray, target);
        System.out.println("3. Binary Search (First Occurrence):");
        if (firstOccurrenceResult != -1) {
            System.out.println("First occurrence of target found at index: " + firstOccurrenceResult);
        } else {
            System.out.println("Target not found.");
        }
        System.out.println();

        // 4. Binary Search with Duplicates (Last Occurrence)
        int lastOccurrenceResult = binarySearchLastOccurrence(duplicateArray, target);
        System.out.println("4. Binary Search (Last Occurrence):");
        if (lastOccurrenceResult != -1) {
            System.out.println("Last occurrence of target found at index: " + lastOccurrenceResult);
        } else {
            System.out.println("Target not found.");
        }
        System.out.println();

        // 5. Binary Search in Rotated Sorted Array
        int[] rotatedArray = {4, 5, 6, 7, 0, 1, 2};
        target = 0;
        System.out.println("Rotated Sorted Array: " + Arrays.toString(rotatedArray));
        System.out.println("Target Value: " + target);
        int rotatedResult = binarySearchRotated(rotatedArray, target);
        System.out.println("5. Binary Search in Rotated Sorted Array:");
        if (rotatedResult != -1) {
            System.out.println("Target found at index: " + rotatedResult);
        } else {
            System.out.println("Target not found.");
        }
    }
}

