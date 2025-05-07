import java.util.Arrays;

public class DutchNationalFlag {

    /**
     * **Approach 1: Counting and Overwriting**
     *
     * 1.  Count the number of 0s, 1s, and 2s in the array.
     * 2.  Overwrite the array: first with the 0s, then the 1s, and finally the 2s.
     *
     * **Time Complexity:** O(n) - two passes through the array.
     * **Space Complexity:** O(1) - uses only constant extra space.
     */
    public static void dutchFlagCountAndOverwrite(int[] arr) {
        int count0 = 0, count1 = 0, count2 = 0;

        // Count the occurrences of each element
        for (int num : arr) {
            if (num == 0) {
                count0++;
            } else if (num == 1) {
                count1++;
            } else {
                count2++;
            }
        }

        // Overwrite the array with the sorted elements
        for (int i = 0; i < arr.length; i++) {
            if (i < count0) {
                arr[i] = 0;
            } else if (i < count0 + count1) {
                arr[i] = 1;
            } else {
                arr[i] = 2;
            }
        }
    }

    /**
     * **Approach 2: Single Pass with Three Pointers (Optimal)**
     *
     * This is the classic and most efficient solution.  It uses three pointers:
     * -   `low`:  Points to the beginning of the 0s section.
     * -   `mid`:  Iterates through the array.
     * -   `high`: Points to the end of the 2s section.
     *
     * The algorithm maintains the following invariants:
     * -   `arr[0...low-1]` contains only 0s.
     * -   `arr[low...mid-1]` contains only 1s.
     * -   `arr[mid...high]` are unknown.
     * -   `arr[high+1...n-1]` contains only 2s.
     *
     * **Time Complexity:** O(n) - single pass through the array.
     * **Space Complexity:** O(1) - uses only constant extra space.
     */
    public static void dutchFlagThreePointers(int[] arr) {
        int low = 0, mid = 0, high = arr.length - 1;

        while (mid <= high) {
            if (arr[mid] == 0) {
                // Swap arr[mid] and arr[low], increment both low and mid
                swap(arr, low, mid);
                low++;
                mid++;
            } else if (arr[mid] == 1) {
                // Increment mid only
                mid++;
            } else { // arr[mid] == 2
                // Swap arr[mid] and arr[high], decrement high only
                swap(arr, mid, high);
                high--;
                // Note: mid does not increment here, because the swapped element
                // from high could be 0, 1, or 2, and needs to be processed.
            }
        }
    }

    /**
     * **Approach 3: Using a helper function for swapping (Same as Approach 2 but with function)**
     *
     * This approach is identical to Approach 2, but encapsulates the swap operation
     * in a separate helper function for better code organization.
     *
     * **Time Complexity:** O(n)
     * **Space Complexity:** O(1)
     */
    public static void dutchFlagThreePointersWithSwap(int[] arr) {
        int low = 0, mid = 0, high = arr.length - 1;

        while (mid <= high) {
            if (arr[mid] == 0) {
                swap(arr, low++, mid++); // Use post-increment
            } else if (arr[mid] == 1) {
                mid++;
            } else {
                swap(arr, mid, high--); // Use post-decrement
            }
        }
    }

    /**
     * **Approach 4: Iterative with Nested Loops (Less Efficient)**
     *
     * This approach uses nested loops.  It iterates through the array, and whenever
     * it finds an out-of-place element (e.g., a 2 before a 1), it swaps it to the
     * correct position. This is less efficient than the three-pointer approach.
     *
     * **Time Complexity:** O(n^2) - in the worst case, nested loops.
     * **Space Complexity:** O(1) - uses only constant extra space.
     */
    public static void dutchFlagNestedLoops(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            for (int j = i + 1; j < arr.length; j++) {
                if (arr[i] > arr[j]) {
                    swap(arr, i, j);
                }
            }
        }
    }

    /**
     * **Approach 5: Using Java Streams (Not Recommended for In-Place Sort)**
     *
     * This approach uses Java Streams to sort the array.  While it's concise,
     * it's generally *not* recommended for the Dutch National Flag problem because:
     * 1.  It's not an in-place sort (creates a new array).
     * 2.  It's less efficient than the specialized three-pointer algorithm.
     *
     * This is included for demonstration, but the three-pointer approach is
     * generally preferred.
     *
     * **Time Complexity:** O(n log n) -  due to the sorting operation.
     * **Space Complexity:** O(n) -  due to the creation of a new array in the stream operation.
     */
    public static void dutchFlagStreams(int[] arr) {
        int[] sortedArr = Arrays.stream(arr)
                .sorted()
                .toArray();
        // Copy the sorted elements back into the original array
        System.arraycopy(sortedArr, 0, arr, 0, arr.length);
    }



    // Helper function to swap two elements in an array
    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args) {
        int[] arr = {2, 0, 2, 1, 1, 0, 2, 1, 0};

        System.out.println("Original array: " + Arrays.toString(arr));

        // Test each approach:
        int[] arr1 = arr.clone(); // Create a copy to test each method independently
        dutchFlagCountAndOverwrite(arr1);
        System.out.println("After Count and Overwrite: " + Arrays.toString(arr1));

        int[] arr2 = arr.clone();
        dutchFlagThreePointers(arr2);
        System.out.println("After Three Pointers: " + Arrays.toString(arr2));

        int[] arr3 = arr.clone();
        dutchFlagThreePointersWithSwap(arr3);
        System.out.println("After Three Pointers with Swap: " + Arrays.toString(arr3));

        int[] arr4 = arr.clone();
        dutchFlagNestedLoops(arr4);
        System.out.println("After Nested Loops: " + Arrays.toString(arr4));

        int[] arr5 = arr.clone();
        dutchFlagStreams(arr5);
        System.out.println("After Streams: " + Arrays.toString(arr5));
    }
}
