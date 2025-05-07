import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class SearchAlgorithms {

    /**
     * Binary Search Algorithm - Iterative Approach
     *
     * This is the most common and fundamental implementation of binary search.  It
     * works on a sorted array and repeatedly divides the search interval in half.
     *
     * Real-world application:
     * -  Searching for a specific entry in a sorted database table (e.g., searching
     * for a customer by ID in a customer database).  Databases often use
     * optimized versions of binary search for fast data retrieval.
     *
     * @param array The sorted array to search in.
     * @param target The element to search for.
     * @return The index of the target element if found, otherwise -1.
     * @throws IllegalArgumentException if the input array is null.
     */
    public static int binarySearchIterative(int[] array, int target) {
        if (array == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }
        int low = 0;
        int high = array.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevent potential overflow
            //int mid = (low + high) / 2; //This can cause integer overflow for very large low and high
            if (array[mid] == target) {
                return mid;
            } else if (array[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }

    /**
     * Binary Search Algorithm - Recursive Approach
     *
     * This implementation uses recursion to divide the search interval.  While
     * conceptually elegant, the iterative approach is often preferred in practice
     * due to its better performance (avoiding function call overhead).
     *
     * Real-world application:
     * -  Implementing search functionality in a sorted data structure like a binary
     * search tree.  Although a binary search tree is a different data structure,
     * the recursive approach here mirrors the tree traversal.
     *
     * @param array The sorted array to search in.
     * @param target The element to search for.
     * @return The index of the target element if found, otherwise -1.
     * @throws IllegalArgumentException if the input array is null.
     */
    public static int binarySearchRecursive(int[] array, int target) {
        if (array == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }
        return binarySearchRecursiveHelper(array, target, 0, array.length - 1);
    }

    private static int binarySearchRecursiveHelper(int[] array, int target, int low, int high) {
        if (low > high) {
            return -1;
        }
        int mid = low + (high - low) / 2;  // Prevent potential overflow
        if (array[mid] == target) {
            return mid;
        } else if (array[mid] < target) {
            return binarySearchRecursiveHelper(array, target, mid + 1, high);
        } else {
            return binarySearchRecursiveHelper(array, target, low, mid - 1);
        }
    }

    /**
     * Exponential Search
     *
     * Exponential search is useful for unbounded (infinite) arrays or very large arrays
     * where the target element is likely to be found early.  It first finds a range
     * where the element might be present and then performs binary search within that range.
     *
     * Real-world application:
     * -  Searching in a very large log file where entries are sorted by timestamp,
     * and you want to find a specific log entry.  Exponential search can quickly
     * narrow down the search to a relevant section of the log file.
     * - Searching in online databases where the size of the database is not known beforehand.
     *
     * @param array The sorted array to search in.
     * @param target The element to search for.
     * @return The index of the target element if found, otherwise -1.
     * @throws IllegalArgumentException if the input array is null.
     */
    public static int exponentialSearch(int[] array, int target) {
        if (array == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }
        int n = array.length;
        if (n == 0) return -1;
        if (array[0] == target) {
            return 0; // Target found at the first position
        }

        int i = 1;
        while (i < n && array[i] <= target) {
            i = i * 2;
        }

        // Perform binary search within the found range
        return binarySearchRecursiveHelper(array, target, i / 2, Math.min(i, n - 1));
    }

    /**
     * Binary Search with Optimization for Large Arrays
     *
     * This version of binary search is optimized to handle extremely large arrays
     * by using a more robust way to calculate the middle index, preventing potential
     * integer overflow issues.
     *
     * Real-world application:
     * -  Searching for data in very large datasets, such as in scientific computing
     * or financial data analysis, where datasets can exceed the maximum integer
     * value.
     *
     * @param array The sorted array to search in.
     * @param target The element to search for.
     * @return The index of the target element if found, otherwise -1.
     * @throws IllegalArgumentException if the input array is null.
     */
    public static int binarySearchLargeArray(int[] array, int target) {
        if (array == null) {
            throw new IllegalArgumentException("Array cannot be null.");
        }
        int low = 0;
        int high = array.length - 1;

        while (low <= high) {
            // Use this to avoid overflow: mid = low + (high - low) / 2
            int mid = low + (high - low) / 2;
            if (array[mid] == target) {
                return mid;
            } else if (array[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }

    /**
     * Exponential Search with Pre-check for Small Arrays
     *
     * This version of Exponential search first checks the size of the array. If the array is small,
     * it performs a simple linear search. If the array is large, it performs the normal exponential search.
     *
     * Real-world Application:
     * - Useful in scenarios where you're dealing with data that sometimes comes in small chunks
     * and sometimes in very large streams.  This hybrid approach optimizes for both cases.
     * -  Searching within a data stream where the initial chunk might be small, but the stream can grow very large.
     *
     * @param array The sorted array to search in.
     * @param target The element to search for.
     * @return The index of the target element if found, otherwise -1.
     */
    public static int exponentialSearchOptimized(int[] array, int target) {
        if (array == null) {
            throw new IllegalArgumentException("Array cannot be null");
        }
        int n = array.length;
        if (n == 0) return -1;
        if (n <= 5) { // If the array is small, use linear search
            for (int i = 0; i < n; i++) {
                if (array[i] == target) {
                    return i;
                }
            }
            return -1;
        }

        if (array[0] == target) {
            return 0;
        }

        int i = 1;
        while (i < n && array[i] <= target) {
            i *= 2;
        }
        return binarySearchLargeArray(array, target, i / 2, Math.min(i, n - 1));
    }

    // Using the optimized binary search for Exponential Search
    private static int binarySearchLargeArray(int[] array, int target, int low, int high) {
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (array[mid] == target) {
                return mid;
            } else if (array[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }

    /**
     * Main method to demonstrate the search algorithms.
     *
     * @param args Command line arguments (not used).
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] array = null; // Declare array here

        // Input array size and elements
        while (true) {
            System.out.print("Enter the size of the sorted array: ");
            try {
                int size = scanner.nextInt();
                if (size < 0) {
                    System.out.println("Array size must be non-negative. Please try again.");
                    continue; // Go back to the beginning of the while loop
                }
                array = new int[size]; // Initialize array here, now that size is known.
                if (size > 0) { // only ask for elements if size > 0
                    System.out.println("Enter the sorted elements of the array:");
                    for (int i = 0; i < size; i++) {
                        System.out.print("Element " + (i + 1) + ": ");
                        array[i] = scanner.nextInt();
                    }
                }
                break; // Exit the loop if size is valid
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter an integer.");
                scanner.next(); // Clear the invalid input
            }
        }

        // Input target element
        int target = 0; // Initialize target
        if (array != null && array.length > 0) {
            System.out.print("Enter the element to search for: ");
            try {
                target = scanner.nextInt();
            } catch (InputMismatchException e) {
                System.out.println("Invalid input for the target. Exiting.");
                scanner.close();
                return;
            }
        }


        // Perform and print the results of each search
        if (array == null || array.length == 0) {
            System.out.println("Array is empty.  Skipping search demos.");
            scanner.close();
            return;
        }
        System.out.println("\nArray: " + Arrays.toString(array));
        System.out.println("Target Element: " + target);

        int index;

        index = binarySearchIterative(array, target);
        System.out.println("\nBinary Search (Iterative): Index = " + index);

        index = binarySearchRecursive(array, target);
        System.out.println("Binary Search (Recursive): Index = " + index);

        index = exponentialSearch(array, target);
        System.out.println("Exponential Search: Index = " + index);

        index = binarySearchLargeArray(array, target);
        System.out.println("Binary Search (Large Array Optimized): Index = " + index);

        index = exponentialSearchOptimized(array, target);
        System.out.println("Exponential Search (Optimized): Index = " + index);

        scanner.close();
    }
}

