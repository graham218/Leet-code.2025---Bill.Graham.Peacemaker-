import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;

public class SortingAlgorithms {

    // 1. Merge Sort - Top-Down Approach (Recursive)
    //   - Stable sort (preserves the order of equal elements).
    //   - Time Complexity: O(n log n) in all cases (best, average, worst).
    //   - Space Complexity: O(n) auxiliary space.
    //   - Suitable for: General-purpose sorting, external sorting (sorting large files that don't fit in memory).
    public static void mergeSort(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return; // Already sorted or empty
        }
        int[] temp = new int[arr.length]; // Auxiliary array for merging
        mergeSortHelper(arr, temp, 0, arr.length - 1);
    }

    private static void mergeSortHelper(int[] arr, int[] temp, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2; // Avoid (left + right) / 2 overflow
            mergeSortHelper(arr, temp, left, mid);      // Sort left half
            mergeSortHelper(arr, temp, mid + 1, right); // Sort right half
            merge(arr, temp, left, mid, right);         // Merge the sorted halves
        }
    }

    private static void merge(int[] arr, int[] temp, int left, int mid, int right) {
        // Copy data to the temporary array
        System.arraycopy(arr, left, temp, left, right - left + 1);

        int i = left;     // Index for the left subarray
        int j = mid + 1; // Index for the right subarray
        int k = left;    // Index for the merged subarray

        // Merge the two sorted subarrays back into the original array
        while (i <= mid && j <= right) {
            if (temp[i] <= temp[j]) {
                arr[k++] = temp[i++];
            } else {
                arr[k++] = temp[j++];
            }
        }

        // Copy the remaining elements of the left subarray (if any)
        while (i <= mid) {
            arr[k++] = temp[i++];
        }
        // Copy the remaining elements of the right subarray (if any) - not needed, because the right side
        // is already in place, but added for completeness.
        while (j <= right) {
            arr[k++] = temp[j++];
        }
    }

    // 2. Quick Sort - Recursive Approach (Hoare Partitioning)
    //   - Generally faster than Merge Sort in practice (smaller constant factor).
    //   - Time Complexity:
    //     - Average Case: O(n log n)
    //     - Best Case: O(n log n)
    //     - Worst Case: O(n^2) (rare with good pivot selection)
    //   - Space Complexity: O(log n) recursive stack space (can be O(n) in worst case).
    //   - Suitable for: General-purpose sorting, especially for large datasets.
    //   - Not stable.
    public static void quickSort(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return;
        }
        quickSortHelper(arr, 0, arr.length - 1);
    }

    private static void quickSortHelper(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high); // Partition the array
            quickSortHelper(arr, low, pi - 1);  // Sort the left subarray
            quickSortHelper(arr, pi + 1, high); // Sort the right subarray
        }
    }

    private static int partition(int[] arr, int low, int high) {
        // Choose the pivot (using the median-of-three approach for better performance)
        int pivot = getMedian(arr, low, high);
        int i = low - 1; // Index of smaller element

        for (int j = low; j < high; j++) {
            // If the current element is smaller than or equal to the pivot
            if (arr[j] <= pivot) {
                i++; // Increment index of smaller element
                // Swap arr[i] and arr[j]
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // Swap arr[i+1] and arr[high] (pivot)
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
    }

    private static int getMedian(int[] arr, int low, int high) {
        int mid = low + (high - low) / 2;
        int a = arr[low];
        int b = arr[mid];
        int c = arr[high];

        if (a < b) {
            if (b < c) {
                return b; // b is median
            } else if (a < c) {
                return c; // c is median
            } else {
                return a; // a is median
            }
        } else {
            if (c < b) {
                return b; // b is median
            } else if (c < a) {
                return c; // c is median
            } else {
                return a; // a is median
            }
        }
    }

    // 3. Merge Sort - Bottom-Up Approach (Iterative)
    //   - Non-recursive version of Merge Sort.
    //   - Avoids the overhead of recursive function calls.
    //   - Time Complexity: O(n log n)
    //   - Space Complexity: O(n)
    //   - Suitable for: Situations where recursion is limited or expensive.
    public static void mergeSortIterative(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return;
        }
        int n = arr.length;
        int[] temp = new int[n];

        for (int size = 1; size < n; size *= 2) { // size of subarray to merge
            for (int leftStart = 0; leftStart < n - size; leftStart += 2 * size) {
                int mid = leftStart + size - 1;
                int rightEnd = Math.min(leftStart + 2 * size - 1, n - 1);
                merge(arr, temp, leftStart, mid, rightEnd);
            }
        }
    }



    // 4. Quick Sort - Iterative Approach
    //   - Uses a stack to simulate the recursive calls.
    //   - Can be useful to avoid stack overflow errors for very large arrays.
    //   - Time Complexity: O(n log n) average, O(n^2) worst
    //   - Space Complexity: O(log n) average, O(n) worst (stack space)
    public static void quickSortIterative(int[] arr) {
        if (arr == null || arr.length <= 1) return;

        int[] stack = new int[arr.length];
        int top = -1;

        stack[++top] = 0;
        stack[++top] = arr.length - 1;

        while (top >= 0) {
            int high = stack[top--];
            int low = stack[top--];

            int pi = partition(arr, low, high);

            if (pi - 1 > low) {
                stack[++top] = low;
                stack[++top] = pi - 1;
            }

            if (pi + 1 < high) {
                stack[++top] = pi + 1;
                stack[++top] = high;
            }
        }
    }

    // 5. Quick Sort - Parallel using Fork/Join Framework
    //   - Utilizes multiple threads to speed up the sorting process.
    //   - Suitable for very large datasets where parallel processing is beneficial.
    //   - Time Complexity: O(n log n) (but with better constant factors due to parallelism)
    //   - Space Complexity: O(log n) (Fork/Join uses a work-stealing algorithm)
    private static final int THRESHOLD = 8192; // Threshold for switching to sequential sort

    public static void quickSortParallel(int[] arr) {
        if (arr == null || arr.length <= 1) return;

        ForkJoinPool pool = new ForkJoinPool();
        pool.invoke(new QuickSortTask(arr, 0, arr.length - 1));
        pool.shutdown(); // Important: Clean up the pool
    }

    private static class QuickSortTask extends RecursiveAction {
        private final int[] arr;
        private final int low;
        private final int high;

        public QuickSortTask(int[] arr, int low, int high) {
            this.arr = arr;
            this.low = low;
            this.high = high;
        }

        @Override
        protected void compute() {
            if (high - low <= THRESHOLD) {
                // Use sequential quicksort for small subarrays
                quickSortHelper(arr, low, high); // Or use mergeSortHelper for hybrid approach
            } else {
                int pi = partition(arr, low, high);
                QuickSortTask leftTask = new QuickSortTask(arr, low, pi - 1);
                QuickSortTask rightTask = new QuickSortTask(arr, pi + 1, high);
                invokeAll(leftTask, rightTask); // Fork and join the subtasks
            }
        }
    }

    public static void main(String[] args) {
        // Example usage and testing
        int[] arrayToSort = generateRandomArray(1000000); // Generate a large array
        int[] arrayToSortCopy;

        // Test Merge Sort (Top-Down)
        arrayToSortCopy = Arrays.copyOf(arrayToSort, arrayToSort.length); // Create a copy
        long startTime = System.nanoTime();
        mergeSort(arrayToSortCopy);
        long endTime = System.nanoTime();
        System.out.println("Merge Sort (Top-Down): Time taken = " + (endTime - startTime) / 1e6 + " ms");
        System.out.println("Is Sorted: " + isSorted(arrayToSortCopy));


        // Test Quick Sort (Recursive)
        arrayToSortCopy = Arrays.copyOf(arrayToSort, arrayToSort.length);
        startTime = System.nanoTime();
        quickSort(arrayToSortCopy);
        endTime = System.nanoTime();
        System.out.println("Quick Sort (Recursive): Time taken = " + (endTime - startTime) / 1e6 + " ms");
        System.out.println("Is Sorted: " + isSorted(arrayToSortCopy));

        // Test Merge Sort (Bottom-Up)
        arrayToSortCopy = Arrays.copyOf(arrayToSort, arrayToSort.length);
        startTime = System.nanoTime();
        mergeSortIterative(arrayToSortCopy);
        endTime = System.nanoTime();
        System.out.println("Merge Sort (Bottom-Up): Time taken = " + (endTime - startTime) / 1e6 + " ms");
        System.out.println("Is Sorted: " + isSorted(arrayToSortCopy));

        // Test Quick Sort (Iterative)
        arrayToSortCopy = Arrays.copyOf(arrayToSort, arrayToSort.length);
        startTime = System.nanoTime();
        quickSortIterative(arrayToSortCopy);
        endTime = System.nanoTime();
        System.out.println("Quick Sort (Iterative): Time taken = " + (endTime - startTime) / 1e6 + " ms");
        System.out.println("Is Sorted: " + isSorted(arrayToSortCopy));

        // Test Quick Sort (Parallel)
        arrayToSortCopy = Arrays.copyOf(arrayToSort, arrayToSort.length);
        startTime = System.nanoTime();
        quickSortParallel(arrayToSortCopy);
        endTime = System.nanoTime();
        System.out.println("Quick Sort (Parallel): Time taken = " + (endTime - startTime) / 1e6 + " ms");
        System.out.println("Is Sorted: " + isSorted(arrayToSortCopy));
    }

    // Helper method to generate a random integer array
    private static int[] generateRandomArray(int size) {
        int[] arr = new int[size];
        Random random = new Random();
        for (int i = 0; i < size; i++) {
            arr[i] = random.nextInt(1000000); // Generate random integers
        }
        return arr;
    }

    // Helper method to check if an array is sorted
    private static boolean isSorted(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return true;
        }
        for (int i = 1; i < arr.length; i++) {
            if (arr[i - 1] > arr[i]) {
                return false;
            }
        }
        return true;
    }
}

