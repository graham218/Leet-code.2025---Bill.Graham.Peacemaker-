import java.util.Arrays;
import java.util.Random;

public class SortingAlgorithms {

    /**
     * **1. Merge Sort (Recursive)**
     *
     * * **Description:** Merge sort is a divide-and-conquer algorithm. It divides the input array into two halves, recursively sorts the two halves, and then merges the sorted halves.
     * * **Time Complexity:** O(n log n) in all cases (best, average, and worst).
     * **Space Complexity:** O(n) due to the auxiliary array used in merging.
     * **Stability:** Stable (maintains the relative order of equal elements).
     */
    public static void mergeSortRecursive(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return; // Base case: already sorted or empty
        }
        int[] temp = new int[arr.length]; // Auxiliary array for merging
        mergeSortHelper(arr, 0, arr.length - 1, temp);
    }

    private static void mergeSortHelper(int[] arr, int left, int right, int[] temp) {
        if (left < right) {
            int mid = left + (right - left) / 2; // Calculate mid to avoid overflow
            mergeSortHelper(arr, left, mid, temp);     // Sort left half
            mergeSortHelper(arr, mid + 1, right, temp);    // Sort right half
            merge(arr, left, mid, right, temp);       // Merge the sorted halves
        }
    }

    private static void merge(int[] arr, int left, int mid, int right, int[] temp) {
        int i = left;       // Index for left subarray
        int j = mid + 1;    // Index for right subarray
        int k = 0;         // Index for temp array

        // Copy elements from both halves into the temp array in sorted order
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        // Copy remaining elements from left subarray, if any
        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        // Copy remaining elements from right subarray, if any
        while (j <= right) {
            temp[k++] = arr[j++];
        }

        // Copy the sorted elements from temp back to the original array
        System.arraycopy(temp, 0, arr, left, k);
    }

    /**
     * **2. Merge Sort (Iterative - Bottom-Up)**
     *
     * * **Description:** Iterative merge sort eliminates recursion.  It starts by merging pairs of single elements, then pairs of two-element groups, and so on.
     * * **Time Complexity:** O(n log n)
     * * **Space Complexity:** O(n)
     * * **Stability:** Stable
     */
    public static void mergeSortIterative(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return;
        }
        int n = arr.length;
        int[] temp = new int[n];

        for (int size = 1; size < n; size *= 2) { // size: size of subarrays to merge
            for (int left = 0; left < n - size; left += 2 * size) {
                int mid = left + size - 1;
                int right = Math.min(left + 2 * size - 1, n - 1); // handle odd-sized array
                merge(arr, left, mid, right, temp);
            }
        }
    }


    /**
     * **3. Quick Sort (Recursive, Lomuto Partitioning)**
     *
     * * **Description:** Quick sort is also a divide-and-conquer algorithm.  It picks an element as a pivot and partitions the array around the pivot.
     * The Lomuto partition scheme picks the last element as the pivot.
     * * **Time Complexity:**
     * * Best/Average: O(n log n)
     * * Worst: O(n^2) (occurs when the pivot is consistently the smallest or largest element)
     * * **Space Complexity:** O(log n) on average due to the recursive call stack.  O(n) in the worst case.
     * * **Stability:** Unstable (does not guarantee the relative order of equal elements).
     */
    public static void quickSortLomuto(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return;
        }
        quickSortLomutoHelper(arr, 0, arr.length - 1);
    }

    private static void quickSortLomutoHelper(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partitionLomuto(arr, low, high); // Partition the array
            quickSortLomutoHelper(arr, low, pi - 1);  // Recursively sort left subarray
            quickSortLomutoHelper(arr, pi + 1, high); // Recursively sort right subarray
        }
    }

    private static int partitionLomuto(int[] arr, int low, int high) {
        int pivot = arr[high]; // Choose the last element as pivot
        int i = (low - 1);    // Index of smaller element

        for (int j = low; j < high; j++) {
            // If current element is smaller than or equal to pivot
            if (arr[j] <= pivot) {
                i++; // increment index of smaller element
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

        return (i + 1);
    }

    /**
     * **4. Quick Sort (Recursive, Hoare Partitioning)**
     * * **Description:** This version of Quick Sort uses the Hoare partition scheme, which can be more efficient in some cases.
     * * **Time Complexity:**
     * * Best/Average: O(n log n)
     * * Worst: O(n^2)
     * * **Space Complexity:** O(log n) on average, O(n) in the worst case.
     * * **Stability:** Unstable
     */
    public static void quickSortHoare(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return;
        }
        quickSortHoareHelper(arr, 0, arr.length - 1);
    }

    private static void quickSortHoareHelper(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partitionHoare(arr, low, high);
            quickSortHoareHelper(arr, low, pi);  // Note: pi, not pi-1
            quickSortHoareHelper(arr, pi + 1, high);
        }
    }

    private static int partitionHoare(int[] arr, int low, int high) {
        int pivot = arr[low]; // Choose the first element as pivot
        int i = low - 1;
        int j = high + 1;

        while (true) {
            // Find leftmost element greater than or equal to pivot
            do {
                i++;
            } while (arr[i] < pivot && i < high);

            // Find rightmost element less than or equal to pivot
            do {
                j--;
            } while (arr[j] > pivot && j > low);

            if (i >= j) {
                return j; // Return the partition index
            }

            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    /**
     * **5. Quick Sort (Randomized Pivot Selection)**
     *
     * * **Description:** This version of Quick Sort aims to improve average-case performance and reduce the likelihood of the worst-case scenario by selecting a random pivot element.  It uses the Lomuto partition scheme.
     * * **Time Complexity:**
     * * Average: O(n log n) - Randomized pivot significantly reduces the probability of worst-case
     * * Worst: Still O(n^2), but extremely unlikely with random pivot selection
     * * **Space Complexity:** O(log n) on average, O(n) in the worst case.
     * * **Stability:** Unstable
     */
    public static void quickSortRandomized(int[] arr) {
        if (arr == null || arr.length <= 1) {
            return;
        }
        quickSortRandomizedHelper(arr, 0, arr.length - 1);
    }

    private static void quickSortRandomizedHelper(int[] arr, int low, int high) {
        if (low < high) {
            int pi = randomizedPartition(arr, low, high); // Use randomized partition
            quickSortRandomizedHelper(arr, low, pi - 1);
            quickSortRandomizedHelper(arr, pi + 1, high);
        }
    }

    private static int randomizedPartition(int[] arr, int low, int high) {
        Random random = new Random();
        int randomIndex = random.nextInt(high - low + 1) + low; // Pick a random index
        // Swap arr[randomIndex] and arr[high] to use the last element as pivot
        int temp = arr[randomIndex];
        arr[randomIndex] = arr[high];
        arr[high] = temp;
        return partitionLomuto(arr, low, high); // Use Lomuto partition with the chosen pivot
    }



    public static void main(String[] args) {
        int[] arr = {12, 11, 13, 5, 6, 7, 5, 12, 34, 1, -2, 0};
        int[] arrCopy;

        System.out.println("Original array: " + Arrays.toString(arr));

        // 1. Merge Sort (Recursive)
        arrCopy = Arrays.copyOf(arr, arr.length); // Create a copy to preserve original
        mergeSortRecursive(arrCopy);
        System.out.println("Merge Sort (Recursive): " + Arrays.toString(arrCopy));

        // 2. Merge Sort (Iterative)
        arrCopy = Arrays.copyOf(arr, arr.length);
        mergeSortIterative(arrCopy);
        System.out.println("Merge Sort (Iterative): " + Arrays.toString(arrCopy));

        // 3. Quick Sort (Lomuto)
        arrCopy = Arrays.copyOf(arr, arr.length);
        quickSortLomuto(arrCopy);
        System.out.println("Quick Sort (Lomuto): " + Arrays.toString(arrCopy));

        // 4. Quick Sort (Hoare)
        arrCopy = Arrays.copyOf(arr, arr.length);
        quickSortHoare(arrCopy);
        System.out.println("Quick Sort (Hoare): " + Arrays.toString(arrCopy));

        // 5. Quick Sort (Randomized)
        arrCopy = Arrays.copyOf(arr, arr.length);
        quickSortRandomized(arrCopy);
        System.out.println("Quick Sort (Randomized): " + Arrays.toString(arrCopy));
    }
}
