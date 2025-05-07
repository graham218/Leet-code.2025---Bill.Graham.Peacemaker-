/**
 * Java Implementation: Binary Search >>> Exponential Search
 *
 * This file contains 5 different approaches to implement Exponential Search,
 * all of which build on or utilize Binary Search in various ways.
 *
 * Each approach includes detailed comments explaining the logic and variations.
 */

public class ExponentialSearchSolutions {

    /**
     * Standard binary search implementation.
     * Searches target in array from left to right (inclusive).
     */
    public static int binarySearch(int[] arr, int left, int right, int target) {
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target)
                return mid;
            else if (arr[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1; // Not found
    }

    /**
     * Approach 1: Basic Exponential Search
     * Double the range exponentially, then perform binary search.
     */
    public static int exponentialSearch1(int[] arr, int target) {
        int n = arr.length;
        if (n == 0) return -1;
        if (arr[0] == target) return 0;

        int i = 1;
        while (i < n && arr[i] <= target) {
            i *= 2;
        }

        return binarySearch(arr, i / 2, Math.min(i, n - 1), target);
    }

    /**
     * Approach 2: Recursive Binary Search in Exponential Range
     */
    public static int binarySearchRecursive(int[] arr, int left, int right, int target) {
        if (left > right) return -1;

        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) return binarySearchRecursive(arr, mid + 1, right, target);
        else return binarySearchRecursive(arr, left, mid - 1, target);
    }

    public static int exponentialSearch2(int[] arr, int target) {
        int n = arr.length;
        if (n == 0) return -1;
        if (arr[0] == target) return 0;

        int i = 1;
        while (i < n && arr[i] <= target) {
            i *= 2;
        }

        return binarySearchRecursive(arr, i / 2, Math.min(i, n - 1), target);
    }

    /**
     * Approach 3: Early Exit Optimization
     * Breaks early if upper bound value is less than target
     */
    public static int exponentialSearch3(int[] arr, int target) {
        int n = arr.length;
        if (n == 0) return -1;

        if (arr[0] == target) return 0;

        int i = 1;
        while (i < n) {
            if (arr[i] == target) return i;
            if (arr[i] > target) break;
            i *= 2;
        }

        return binarySearch(arr, i / 2, Math.min(i, n - 1), target);
    }

    /**
     * Approach 4: Modified Binary Search Inside Exponential Step
     * Performs binary search in a dynamic exponential segment
     */
    public static int exponentialSearch4(int[] arr, int target) {
        int bound = 1;
        while (bound < arr.length && arr[bound] < target) {
            bound *= 2;
        }
        return binarySearch(arr, bound / 2, Math.min(bound, arr.length - 1), target);
    }

    /**
     * Approach 5: Using Java Streams (Just for Demo, not performance efficient)
     * Demonstrates search using Java 8+ features
     */
    public static int exponentialSearch5(int[] arr, int target) {
        return java.util.stream.IntStream.range(0, arr.length)
                .filter(i -> arr[i] == target)
                .findFirst()
                .orElse(-1);
    }

    /**
     * Test all approaches with the same input.
     */
    public static void main(String[] args) {
        int[] array = {1, 3, 5, 7, 9, 15, 20, 35, 50, 75, 100};
        int target = 20;

        System.out.println("Approach 1: " + exponentialSearch1(array, target));
        System.out.println("Approach 2: " + exponentialSearch2(array, target));
        System.out.println("Approach 3: " + exponentialSearch3(array, target));
        System.out.println("Approach 4: " + exponentialSearch4(array, target));
        System.out.println("Approach 5: " + exponentialSearch5(array, target));
    }
}
