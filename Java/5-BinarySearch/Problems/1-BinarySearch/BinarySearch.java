import java.util.Arrays;

public class BinarySearch {

    /**
     * **1. Iterative Binary Search**
     *
     * Performs a binary search on a sorted array using iteration.
     *
     * **Parameters:**
     * - `arr`: The sorted integer array to search.
     * - `target`: The integer value to search for.
     *
     * **Returns:**
     * The index of the `target` if found, otherwise -1.
     *
     * **Time Complexity:** O(log n) - logarithmic time complexity.
     * **Space Complexity:** O(1) - constant space complexity.
     */
    public static int iterativeBinarySearch(int[] arr, int target) {
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
        // If we reach here, the element was not found
        return -1;
    }

    /**
     * **2. Recursive Binary Search**
     *
     * Performs a binary search on a sorted array using recursion.
     *
     * **Parameters:**
     * - `arr`: The sorted integer array to search.
     * - `target`: The integer value to search for.
     * - `left`: The starting index of the search range.
     * - `right`: The ending index of the search range.
     *
     * **Returns:**
     * The index of the `target` if found, otherwise -1.
     *
     * **Time Complexity:** O(log n) - logarithmic time complexity.
     * **Space Complexity:** O(log n) - due to the recursive call stack.
     */
    public static int recursiveBinarySearch(int[] arr, int target, int left, int right) {
        if (left > right) {
            return -1; // Base case: element not found
        }

        int mid = left + (right - left) / 2;  // Prevent potential overflow

        if (arr[mid] == target) {
            return mid; // Base case: element found
        }

        if (arr[mid] < target) {
            return recursiveBinarySearch(arr, target, mid + 1, right); // Search right half
        } else {
            return recursiveBinarySearch(arr, target, left, mid - 1); // Search left half
        }
    }

    /**
     * **3. Binary Search using Java's `Arrays.binarySearch()`**
     *
     * Utilizes Java's built-in `Arrays.binarySearch()` method.
     *
     * **Parameters:**
     * - `arr`: The sorted integer array to search.
     * - `target`: The integer value to search for.
     *
     * **Returns:**
     * The index of the `target` if found, otherwise a negative value
     * (-(insertion point) - 1).
     *
     * **Time Complexity:** O(log n) - logarithmic time complexity.
     * **Space Complexity:** O(1) - constant space complexity.
     */
    public static int javaBinarySearch(int[] arr, int target) {
        return Arrays.binarySearch(arr, target);
    }

    /**
     * **4. Binary Search to find the First Occurrence**
     *
     * Finds the index of the *first* occurrence of the target value in a sorted array
     * which may contain duplicate elements.
     *
     * **Parameters:**
     * - `arr`: The sorted integer array to search.
     * - `target`: The integer value to search for.
     *
     * **Returns:**
     * The index of the *first* occurrence of the `target`, or -1 if not found.
     *
     * **Time Complexity:** O(log n)
     * **Space Complexity:** O(1)
     */
    public static int findFirstOccurrence(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;
        int result = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                result = mid;       // Found a match, but look for earlier ones
                right = mid - 1;    // Continue searching in the left half
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    }

    /**
     * **5. Binary Search to find the Last Occurrence**
     *
     * Finds the index of the *last* occurrence of the target value in a sorted array
     * which may contain duplicate elements.
     *
     * **Parameters:**
     * - `arr`: The sorted integer array to search.
     * - `target`: The integer value to search for.
     *
     * **Returns:**
     * The index of the *last* occurrence of the `target`, or -1 if not found.
     *
     * * **Time Complexity:** O(log n)
     * * **Space Complexity:** O(1)
     */
    public static int findLastOccurrence(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;
        int result = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                result = mid;       // Found a match, but look for later ones
                left = mid + 1;     // Continue searching in the right half
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    }

    public static void main(String[] args) {
        int[] sortedArray = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
        int targetValue = 23;

        // 1. Iterative Binary Search
        int iterativeResult = iterativeBinarySearch(sortedArray, targetValue);
        System.out.println("Iterative Binary Search: Index of " + targetValue + " is " + iterativeResult);

        // 2. Recursive Binary Search
        int recursiveResult = recursiveBinarySearch(sortedArray, targetValue, 0, sortedArray.length - 1);
        System.out.println("Recursive Binary Search: Index of " + targetValue + " is " + recursiveResult);

        // 3. Java's Arrays.binarySearch()
        int javaSearchResult = javaBinarySearch(sortedArray, targetValue);
        System.out.println("Java's Arrays.binarySearch(): Index of " + targetValue + " is " + javaSearchResult);

        // Example with duplicates to test first and last occurrence
        int[] duplicateArray = {2, 4, 6, 6, 6, 8, 10, 12};
        int duplicateTarget = 6;

        // 4. Find First Occurrence
        int firstOccurrence = findFirstOccurrence(duplicateArray, duplicateTarget);
        System.out.println("First Occurrence of " + duplicateTarget + " is at index " + firstOccurrence);

        // 5. Find Last Occurrence
        int lastOccurrence = findLastOccurrence(duplicateArray, duplicateTarget);
        System.out.println("Last Occurrence of " + duplicateTarget + " is at index " + lastOccurrence);

        // Example when the target is not in the array
        int notFoundTarget = 15;
        int notFoundResult = iterativeBinarySearch(sortedArray, notFoundTarget);
        System.out.println("Index of " + notFoundTarget + " is " + notFoundResult); // Output: -1
    }
}

