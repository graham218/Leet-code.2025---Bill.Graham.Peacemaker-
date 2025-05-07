import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Arrays;

public class BinarySearchBounds {

    /**
     * **1. Lower Bound using Standard Library (Real-world use case: Finding the first available time slot in a schedule)**
     *
     * * Utilizes Java's `Collections.binarySearch()` to find the lower bound of a target value in a sorted list.
     * * If the target is found, it returns the index.
     * * If the target is not found, it returns `-(insertion point) - 1`, where the insertion point
     * is the index where the target would be inserted to maintain the sorted order.
     * * This method calculates the lower bound by adjusting the result from `binarySearch()`.
     *
     * @param sortedList The sorted list to search in.
     * @param target     The target value to find the lower bound of.
     * @return The index of the lower bound of the target value, or -1 if the target is smaller
     * than all elements in the list.
     */
    public static <T extends Comparable<T>> int lowerBoundStdLib(List<T> sortedList, T target) {
        int index = Collections.binarySearch(sortedList, target);
        if (index >= 0) {
            // Target found, but we need the *first* occurrence (lower bound)
            while (index > 0 && sortedList.get(index - 1).compareTo(target) == 0) {
                index--;
            }
            return index;
        } else {
            // Target not found.  -(insertion point) - 1 is returned.
            int insertionPoint = -index - 1;
            //If the insertion point is 0, it means the target is smaller than all elements.
            return (insertionPoint == 0) ? -1 : insertionPoint; // Return -1 if target is smaller than all elements.
        }
    }

    /**
     * **2. Upper Bound using Standard Library (Real-world use case: Finding the last eligible product within a price range)**
     *
     * * Similar to `lowerBoundStdLib`, but finds the *last* occurrence of the target value,
     * which represents the upper bound.
     * * It uses the same `Collections.binarySearch()` method.
     *
     * @param sortedList The sorted list to search in.
     * @param target     The target value to find the upper bound of.
     * @return The index of the upper bound of the target value, or -1 if the target is larger
     * than all elements in the list.
     */
    public static <T extends Comparable<T>> int upperBoundStdLib(List<T> sortedList, T target) {
        int index = Collections.binarySearch(sortedList, target);
        if (index >= 0) {
            // Target found, find the *last* occurrence (upper bound)
            while (index < sortedList.size() - 1 && sortedList.get(index + 1).compareTo(target) == 0) {
                index++;
            }
            return index;
        } else {
            int insertionPoint = -index - 1;
            // If insertionPoint is sortedList.size(), target is greater than all elements.
            return (insertionPoint == sortedList.size()) ? -1 : insertionPoint - 1;
        }
    }

    /**
     * **3. Lower Bound using Custom Binary Search (Real-world use case: Implementing a custom search in a database index)**
     *
     * * Implements a standard iterative binary search algorithm.
     * * Refines the search range (`low`, `high`) based on comparisons with the middle element.
     * * Specifically targets the *first* occurrence of the target value.
     *
     * @param sortedList The sorted list to search in.
     * @param target     The target value to find the lower bound of.
     * @return The index of the lower bound of the target value, or -1 if not found.
     */
    public static <T extends Comparable<T>> int lowerBoundCustom(List<T> sortedList, T target) {
        int low = 0;
        int high = sortedList.size() - 1;
        int result = -1; // Initialize to -1, meaning not found

        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevent overflow
            if (sortedList.get(mid).compareTo(target) == 0) {
                result = mid; // Found, but look for earlier occurrences
                high = mid - 1; // Continue searching in the left half
            } else if (sortedList.get(mid).compareTo(target) < 0) {
                low = mid + 1;     // Search in the right half
            } else {
                high = mid - 1;    // Search in the left half
            }
        }
        return result;
    }

    /**
     * **4. Upper Bound using Custom Binary Search (Real-world use case: Finding the latest version of a file in a version control system)**
     *
     * * Similar to `lowerBoundCustom`, but targets the *last* occurrence of the target value.
     *
     * @param sortedList The sorted list to search in.
     * @param target     The target value to find the upper bound of.
     * @return The index of the upper bound of the target value, or -1 if not found.
     */
    public static <T extends Comparable<T>> int upperBoundCustom(List<T> sortedList, T target) {
        int low = 0;
        int high = sortedList.size() - 1;
        int result = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (sortedList.get(mid).compareTo(target) == 0) {
                result = mid; // Found, but look for later occurrences
                low = mid + 1;   // Search in the right half
            } else if (sortedList.get(mid).compareTo(target) < 0) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return result;
    }

    /**
     * **5. Lower Bound using Recursive Binary Search (Real-world use case: Implementing a recursive search in a tree-like data structure)**
     *
     * * Implements a recursive version of the binary search algorithm to find the lower bound.
     * * This approach can be useful in scenarios where recursion provides a more elegant or
     * natural solution, such as when traversing tree-like data structures.
     *
     * @param sortedList The sorted list to search in.
     * @param target     The target value to find the lower bound of.
     * @param low        The starting index of the search range.
     * @param high       The ending index of the search range.
     * @return The index of the lower bound of the target value, or -1 if not found.
     */
    public static <T extends Comparable<T>> int lowerBoundRecursive(List<T> sortedList, T target, int low, int high) {
        if (low > high) {
            return -1; // Base case: target not found
        }
        int mid = low + (high - low) / 2;
        if (sortedList.get(mid).compareTo(target) == 0) {
            // Found, check for earlier occurrences
            int result = lowerBoundRecursive(sortedList, target, low, mid - 1);
            return (result != -1) ? result : mid; // Return earliest found
        } else if (sortedList.get(mid).compareTo(target) < 0) {
            return lowerBoundRecursive(sortedList, target, mid + 1, high); // Search right
        } else {
            return lowerBoundRecursive(sortedList, target, low, mid - 1);    // Search left
        }
    }

    public static void main(String[] args) {
        // Example sorted list of integers
        List<Integer> numbers = Arrays.asList(2, 5, 5, 5, 6, 6, 8, 9, 9, 10);

        // Example sorted list of strings
        List<String> words = Arrays.asList("apple", "banana", "banana", "cherry", "date", "date", "grape");

        // Example sorted list of double
        List<Double> doubles = Arrays.asList(1.1, 2.2, 2.2, 3.3, 4.4, 4.4, 5.5);

        System.out.println("Integer List: " + numbers);
        System.out.println("String List: " + words);
        System.out.println("Double List: " + doubles);
        System.out.println("\n--- Integer List ---");
        testBinarySearch(numbers, 5);
        testBinarySearch(numbers, 6);
        testBinarySearch(numbers, 7);
        testBinarySearch(numbers, 10);
        testBinarySearch(numbers, 1);
        testBinarySearch(numbers, 11);

        System.out.println("\n--- String List ---");
        testBinarySearch(words, "banana");
        testBinarySearch(words, "date");
        testBinarySearch(words, "grape");
        testBinarySearch(words, "avocado");
        testBinarySearch(words, "elderberry");

        System.out.println("\n--- Double List ---");
        testBinarySearch(doubles, 2.2);
        testBinarySearch(doubles, 4.4);
        testBinarySearch(doubles, 5.5);
        testBinarySearch(doubles, 1.0);
        testBinarySearch(doubles, 6.6);

        // Example of using the recursive version of lower bound (for integers)
        int target = 5;
        int recursiveLowerBound = lowerBoundRecursive(numbers, target, 0, numbers.size() - 1);
        System.out.println("\n--- Recursive Lower Bound Example ---");
        System.out.println("Lower bound of " + target + " (recursive): " + recursiveLowerBound);
    }

    /**
     * Helper method to run and print test cases for binary search methods
     * @param list
     * @param target
     * @param <T>
     */
    private static <T extends Comparable<T>> void testBinarySearch(List<T> list, T target) {
        System.out.println("\nTarget Value: " + target);
        System.out.println("Lower Bound (StdLib): " + lowerBoundStdLib(list, target));
        System.out.println("Upper Bound (StdLib): " + upperBoundStdLib(list, target));
        System.out.println("Lower Bound (Custom): " + lowerBoundCustom(list, target));
        System.out.println("Upper Bound (Custom): " + upperBoundCustom(list, target));
    }
}

