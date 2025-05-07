import java.util.Arrays;
import java.util.Random;

public class DutchNationalFlag {

    /**
     * **Approach 1: Counting and Overwriting (Simplified - Good for understanding the basics)**
     *
     * **Concept:**
     * 1.  Count the occurrences of 0, 1, and 2 in the array.
     * 2.  Overwrite the array: first with the 0s, then the 1s, and finally the 2s.
     *
     * **Real-World Use Case:**
     * -   *Basic Data Organization:* Imagine you have a very simple embedded system that receives sensor data (0, 1, or 2 representing different sensor states).  You need to quickly organize this data in memory before processing it.  This approach is easy to understand and implement in such a constrained environment.
     *
     * **Time Complexity:** O(n) - two passes through the array.
     * **Space Complexity:** O(1) - uses only a few extra variables.
     */
    public static void dutchFlag1(int[] arr) {
        int count0 = 0, count1 = 0, count2 = 0;

        // Count occurrences
        for (int num : arr) {
            if (num == 0) {
                count0++;
            } else if (num == 1) {
                count1++;
            } else {
                count2++;
            }
        }

        // Overwrite the array
        for (int i = 0; i < count0; i++) {
            arr[i] = 0;
        }
        for (int i = count0; i < count0 + count1; i++) {
            arr[i] = 1;
        }
        for (int i = count0 + count1; i < arr.length; i++) {
            arr[i] = 2;
        }
    }

    /**
     * **Approach 2: Single-Pass with Three Pointers (Classic Dutch National Flag)**
     *
     * **Concept:**
     * -   Use three pointers: `low`, `mid`, and `high`.
     * -   `low`:  Keeps track of the boundary between 0s and 1s.
     * -   `mid`:  The current element being examined.
     * -   `high`: Keeps track of the boundary between 2s and 1s.
     * -   Iterate through the array using the `mid` pointer.
     * -   If `arr[mid]` is 0, swap it with `arr[low]` and move both `low` and `mid` forward.
     * -   If `arr[mid]` is 1, move `mid` forward.
     * -   If `arr[mid]` is 2, swap it with `arr[high]` and move `high` backward.
     *
     * **Real-World Use Case:**
     * -   *Packet Classification in Networking:* Imagine network routers need to classify incoming packets based on their priority (low, medium, high).  You can represent these priorities as 0, 1, and 2.  This algorithm efficiently reorders the packets in a buffer so that they can be processed in the correct order.  This is a performance-critical application where minimizing passes through the data is essential.
     *
     * **Time Complexity:** O(n) - single pass through the array.
     * **Space Complexity:** O(1) - uses only a few extra variables.
     */
    public static void dutchFlag2(int[] arr) {
        int low = 0, mid = 0, high = arr.length - 1;

        while (mid <= high) {
            if (arr[mid] == 0) {
                swap(arr, low, mid);
                low++;
                mid++;
            } else if (arr[mid] == 1) {
                mid++;
            } else {
                swap(arr, mid, high);
                high--;
            }
        }
    }

    /**
     * **Approach 3: Using a switch statement (Syntactic Variation of Approach 2)**
     *
     * **Concept:**
     * -  This is a variation of the three-pointer approach, but it uses a `switch` statement
     * to handle the different cases (0, 1, or 2) for `arr[mid]`.
     * -  It achieves the same reordering as Approach 2 but with slightly different syntax.
     *
     * **Real-World Use Case:**
     * -  *Configuration Management:* Consider a system where you have configuration settings represented as 0, 1, or 2 (e.g., logging levels:  0-Debug, 1-Info, 2-Error).  You might need to reorder these settings based on some criteria.  Using a `switch` statement can make the code more readable in this scenario, especially if there are more configuration levels to handle in the future.
     *
     * **Time Complexity:** O(n)
     * **Space Complexity:** O(1)
     */
    public static void dutchFlag3(int[] arr) {
        int low = 0;
        int mid = 0;
        int high = arr.length - 1;

        while (mid <= high) {
            switch (arr[mid]) {
                case 0:
                    swap(arr, low++, mid++);
                    break;
                case 1:
                    mid++;
                    break;
                case 2:
                    swap(arr, mid, high--);
                    break;
            }
        }
    }

    /**
     * **Approach 4:  Iterative with Boundary Tracking (More Explicit)**
     *
     * **Concept:**
     * -   This approach focuses on explicitly maintaining the boundaries between the different sections of the array.
     * -   It iterates through the array and uses two pointers (`zeroEnd` and `twoStart`) to mark the end of the 0s section and the beginning of the 2s section.
     * -   It's a bit more verbose but can be easier to follow for some developers.
     *
     * **Real-World Use Case:**
     * -   *Sorting Algorithm Visualization:* When teaching or visualizing sorting algorithms, this approach can be helpful.  The explicit tracking of boundaries makes it clearer how the array is being partitioned step by step.  It can be used in educational software or debugging tools.
     *
     * **Time Complexity:** O(n)
     * **Space Complexity:** O(1)
     */
    public static void dutchFlag4(int[] arr) {
        int zeroEnd = -1;  // Index of the last 0
        int twoStart = arr.length; // Index of the first 2
        int i = 0;

        while (i < twoStart) {
            if (arr[i] == 0) {
                zeroEnd++;
                swap(arr, i, zeroEnd);
                i++;
            } else if (arr[i] == 2) {
                twoStart--;
                swap(arr, i, twoStart);
                // Note:  Don't increment 'i' here because the swapped element might need to be processed
            } else { // arr[i] == 1
                i++;
            }
        }
    }

    /**
     * **Approach 5: Using Java 8 Streams (Functional Approach - Good for demonstration)**
     *
     * **Concept:**
     * - This approach uses Java 8 Streams to filter the array into three separate lists (0s, 1s, and 2s).
     * - Then, it creates a new array and populates it with the elements from the three lists.
     *
     * **Real-World Use Case:**
     * -  *Data Analysis and Reporting:* While not the most efficient for in-place sorting, this approach demonstrates how to use streams for data manipulation.  In a data analysis scenario, you might use streams to categorize data (e.g., customer segments based on some value) before generating a report.  This approach highlights the expressiveness of streams.  It's often used when you don't need to modify the original array, but rather create a new, ordered representation.
     *
     * **Time Complexity:** O(n) - due to the filtering and collection operations.
     * **Space Complexity:** O(n) -  because of the intermediate lists created by the streams.  This approach uses extra space, unlike the in-place algorithms.
     */
    public static void dutchFlag5(int[] arr) {
        // Use streams to filter the array into three lists
        int[] zeros = Arrays.stream(arr).filter(x -> x == 0).toArray();
        int[] ones = Arrays.stream(arr).filter(x -> x == 1).toArray();
        int[] twos = Arrays.stream(arr).filter(x -> x == 2).toArray();

        // Create a new array
        int[] sortedArr = new int[arr.length];

        // Copy the elements from the lists into the new array
        System.arraycopy(zeros, 0, sortedArr, 0, zeros.length);
        System.arraycopy(ones, 0, sortedArr, zeros.length, ones.length);
        System.arraycopy(twos, 0, sortedArr, zeros.length + ones.length, twos.length);

        // Copy the sorted array back into the original array
        System.arraycopy(sortedArr, 0, arr, 0, arr.length);
    }

    // Helper function to swap elements in an array
    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args) {
        // Test the different approaches
        int[] arr1 = {2, 1, 0, 2, 1, 0, 2, 1, 0};
        int[] arr2 = Arrays.copyOf(arr1, arr1.length); // Create a copy for each test
        int[] arr3 = Arrays.copyOf(arr1, arr1.length);
        int[] arr4 = Arrays.copyOf(arr1, arr1.length);
        int[] arr5 = Arrays.copyOf(arr1, arr1.length);


        System.out.println("Original Array: " + Arrays.toString(arr1));

        dutchFlag1(arr1);
        System.out.println("After dutchFlag1: " + Arrays.toString(arr1));

        dutchFlag2(arr2);
        System.out.println("After dutchFlag2: " + Arrays.toString(arr2));

        dutchFlag3(arr3);
        System.out.println("After dutchFlag3: " + Arrays.toString(arr3));

        dutchFlag4(arr4);
        System.out.println("After dutchFlag4: " + Arrays.toString(arr4));

        dutchFlag5(arr5);
        System.out.println("After dutchFlag5: " + Arrays.toString(arr5));

        // Example with a random array
        int[] randomArr = new int[20];
        Random random = new Random();
        for (int i = 0; i < randomArr.length; i++) {
            randomArr[i] = random.nextInt(3); // 0, 1, or 2
        }
        System.out.println("\nRandom Array: " + Arrays.toString(randomArr));
        dutchFlag2(randomArr); // Using the most efficient approach (Approach 2)
        System.out.println("Sorted Random Array: " + Arrays.toString(randomArr));
    }
}
