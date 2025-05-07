import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Scanner;

public class BinarySearch {

    /**
     * Iterative Binary Search Implementation.
     *
     * This method searches for a target value within a sorted array using the iterative approach.
     * It repeatedly divides the search interval in half until the target is found or the interval is empty.
     *
     * @param arr The sorted array to search within.
     * @param target The value to search for.
     * @return The index of the target value if found, otherwise -1.
     *
     * Example Use Case:
     * Searching for a specific product ID in a sorted list of product IDs in an e-commerce application.
     */
    public static int iterativeBinarySearch(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevent potential overflow

            if (arr[mid] == target) {
                return mid; // Target found at the middle
            } else if (arr[mid] < target) {
                low = mid + 1; // Target is in the right half
            } else {
                high = mid - 1; // Target is in the left half
            }
        }

        return -1; // Target not found
    }

    /**
     * Recursive Binary Search Implementation.
     *
     * This method searches for a target value within a sorted array using the recursive approach.
     * It recursively divides the search interval in half until the target is found or the interval is empty.
     *
     * @param arr The sorted array to search within.
     * @param target The value to search for.
     * @param low The starting index of the search interval.
     * @param high The ending index of the search interval.
     * @return The index of the target value if found, otherwise -1.
     *
     * Example Use Case:
     * Implementing a recursive search in a database index to locate a specific record.
     */
    public static int recursiveBinarySearch(int[] arr, int target, int low, int high) {
        if (low > high) {
            return -1; // Base case: Target not found
        }

        int mid = low + (high - low) / 2; // Prevent potential overflow

        if (arr[mid] == target) {
            return mid; // Target found at the middle
        } else if (arr[mid] < target) {
            return recursiveBinarySearch(arr, target, mid + 1, high); // Search in the right half
        } else {
            return recursiveBinarySearch(arr, target, low, mid - 1); // Search in the left half
        }
    }

    /**
     * Binary Search for First Occurrence.
     *
     * This method finds the index of the *first* occurrence of a target value in a sorted array that may contain duplicates.
     *
     * @param arr The sorted array to search within.
     * @param target The value to search for.
     * @return The index of the first occurrence of the target value if found, otherwise -1.
     *
     * Example Use Case:
     * Finding the first occurrence of a specific date in a sorted log file.
     */
    public static int binarySearchFirstOccurrence(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;
        int result = -1; // Initialize result to -1 (not found)

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                result = mid;     // Update result, but continue searching for earlier occurrences
                high = mid - 1;   // Search in the left half
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return result;
    }

    /**
     * Binary Search for Last Occurrence.
     *
     * This method finds the index of the *last* occurrence of a target value in a sorted array that may contain duplicates.
     *
     * @param arr The sorted array to search within.
     * @param target The value to search for.
     * @return The index of the last occurrence of the target value if found, otherwise -1.
     *
     * Example Use Case:
     * Finding the last occurrence of a specific event in a sorted list of events.
     */
    public static int binarySearchLastOccurrence(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;
        int result = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                result = mid;     // Update result, but continue searching for later occurrences
                low = mid + 1;    // Search in the right half
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return result;
    }

    /**
     * Binary Search in Rotated Sorted Array.
     *
     * This method searches for a target value in a sorted array that has been rotated.
     * A rotated sorted array is an array that was originally sorted, but then had some portion of it shifted to the beginning.
     *
     * @param arr The rotated sorted array.
     * @param target The value to search for.
     * @return The index of the target value if found, otherwise -1.
     *
     * Example Use Case:
     * Searching for a specific version number in a deployed application's configuration, where the configuration
     * array might be rotated due to deployment strategies.
     */
    public static int binarySearchRotated(int[] arr, int target) {
        int low = 0;
        int high = arr.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] == target) {
                return mid;
            }

            if (arr[low] <= arr[mid]) { // Left half is sorted
                if (target >= arr[low] && target < arr[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else { // Right half is sorted
                if (target > arr[mid] && target <= arr[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Binary Search Demo");
        System.out.println("-------------------");

        // Get array size from user
        int arraySize = 0;
        boolean validSize = false;
        while (!validSize) {
            System.out.print("Enter the size of the sorted array: ");
            try {
                arraySize = scanner.nextInt();
                if (arraySize > 0) {
                    validSize = true;
                } else {
                    System.out.println("Array size must be a positive integer.");
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter an integer.");
                scanner.next(); // Clear the invalid input
            }
        }

        // Create the array
        int[] sortedArray = new int[arraySize];

        // Get array elements from user, ensuring they are sorted
        System.out.println("Enter the elements of the sorted array in ascending order:");
        for (int i = 0; i < arraySize; i++) {
            boolean validElement = false;
            while (!validElement) {
                System.out.print("Element " + (i + 1) + ": ");
                try {
                    int element = scanner.nextInt();
                    if (i > 0 && element < sortedArray[i - 1]) {
                        System.out.println("Element must be greater than or equal to the previous element.");
                    } else {
                        sortedArray[i] = element;
                        validElement = true;
                    }
                } catch (InputMismatchException e) {
                    System.out.println("Invalid input. Please enter an integer.");
                    scanner.next(); // Clear invalid input
                }
            }
        }

        // Get the target value from the user
        System.out.print("Enter the target value to search for: ");
        int target = scanner.nextInt();

        // Perform and display the results of each binary search method
        System.out.println("\nResults:");
        System.out.println("-------------------");

        int iterativeResult = iterativeBinarySearch(sortedArray, target);
        System.out.println("Iterative Binary Search: " + (iterativeResult != -1 ? "Found at index " + iterativeResult : "Not found"));

        int recursiveResult = recursiveBinarySearch(sortedArray, target, 0, sortedArray.length - 1);
        System.out.println("Recursive Binary Search: " + (recursiveResult != -1 ? "Found at index " + recursiveResult : "Not found"));

        int firstOccurrenceResult = binarySearchFirstOccurrence(sortedArray, target);
        System.out.println("First Occurrence: " + (firstOccurrenceResult != -1 ? "Found at index " + firstOccurrenceResult : "Not found"));

        int lastOccurrenceResult = binarySearchLastOccurrence(sortedArray, target);
        System.out.println("Last Occurrence: " + (lastOccurrenceResult != -1 ? "Found at index " + lastOccurrenceResult : "Not found"));

        // Demonstrate on a rotated array
        int[] rotatedArray = {4, 5, 6, 7, 0, 1, 2}; // Example rotated array
        int rotatedResult = binarySearchRotated(rotatedArray, target);
        System.out.println("Rotated Array Search: " + (rotatedResult != -1 ? "Found at index " + rotatedResult : "Not found"));

        scanner.close();
    }
}

