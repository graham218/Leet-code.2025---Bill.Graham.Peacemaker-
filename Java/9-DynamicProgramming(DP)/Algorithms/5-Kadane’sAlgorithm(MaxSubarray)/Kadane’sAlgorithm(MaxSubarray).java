import java.util.Arrays;

public class KadanesAlgorithm {

    public static void main(String[] args) {
        int[] arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        int[] arr2 = {-1, -2, -3, -4}; // Example with all negative numbers
        int[] arr3 = {2, 3, -2, 4};

        System.out.println("Kadane's Algorithm - Maximum Subarray Sum:");
        System.out.println("Array: " + Arrays.toString(arr));

        // 1. Basic Kadane's Algorithm
        System.out.println("1. Basic Kadane's Algorithm: " + kadaneBasic(arr)); // Should be 6
        System.out.println("1. Basic Kadane's Algorithm (all negative): " + kadaneBasic(arr2)); // Should be -1
        System.out.println("1. Basic Kadane's Algorithm: " + kadaneBasic(arr3));

        // 2. Kadane's Algorithm with Start and End Index
        int[] result = kadaneWithStartEnd(arr);
        System.out.println("2. Kadane's Algorithm with Start and End Index: Sum = " + result[0] +
                ", Start Index = " + result[1] + ", End Index = " + result[2]); // Should be 6, 3, 6

        int[] result2 = kadaneWithStartEnd(arr2);
        System.out.println("2. Kadane's Algorithm with Start and End Index (all negative): Sum = " + result2[0] +
                ", Start Index = " + result2[1] + ", End Index = " + result2[2]);

        int[] result3 = kadaneWithStartEnd(arr3);
        System.out.println("2. Kadane's Algorithm with Start and End Index: Sum = " + result3[0] +
                ", Start Index = " + result3[1] + ", End Index = " + result3[2]);

        // 3. Kadane's Algorithm with Handling All Negative Numbers Efficiently
        System.out.println("3. Kadane's Algorithm (Handles All Negatives): " + kadaneAllNegative(arr));
        System.out.println("3. Kadane's Algorithm (Handles All Negatives): " + kadaneAllNegative(arr2)); // Should be -1
        System.out.println("3. Kadane's Algorithm (Handles All Negatives): " + kadaneAllNegative(arr3));

        // 4. Kadane's Algorithm - Concise Version
        System.out.println("4. Kadane's Algorithm (Concise): " + kadaneConcise(arr));
        System.out.println("4. Kadane's Algorithm (Concise): " + kadaneConcise(arr2));
        System.out.println("4. Kadane's Algorithm (Concise): " + kadaneConcise(arr3));

        // 5. Kadane's Algorithm with Explanation
        System.out.println("5. Kadane's Algorithm (Detailed Explanation): " + kadaneDetailed(arr));
        System.out.println("5. Kadane's Algorithm (Detailed Explanation): " + kadaneDetailed(arr2));
        System.out.println("5. Kadane's Algorithm (Detailed Explanation): " + kadaneDetailed(arr3));
    }

    // 1. Basic Kadane's Algorithm
    //   - Iterates through the array, keeping track of the current maximum subarray sum
    //   - If the current sum becomes negative, reset it to 0
    //   - Time Complexity: O(n), Space Complexity: O(1)
    public static int kadaneBasic(int[] arr) {
        int maxSoFar = 0;
        int currentMax = 0;

        for (int num : arr) {
            currentMax = Math.max(0, currentMax + num); // Reset currentMax if it goes negative
            maxSoFar = Math.max(maxSoFar, currentMax);
        }
        // Handles the case where all elements are negative (returns 0 in that case)
        if (maxSoFar == 0) {
            int maxVal = Integer.MIN_VALUE;
            for(int num : arr){
                maxVal = Math.max(maxVal, num);
            }
            return maxVal;
        }

        return maxSoFar;
    }

    // 2. Kadane's Algorithm with Start and End Index
    //   - Tracks the start and end indices of the maximum subarray
    //   - Uses similar logic as the basic version, but also updates indices
    //   - Time Complexity: O(n), Space Complexity: O(1)
    public static int[] kadaneWithStartEnd(int[] arr) {
        int maxSoFar = Integer.MIN_VALUE;
        int currentMax = 0;
        int start = 0;
        int end = 0;
        int currentStart = 0;

        for (int i = 0; i < arr.length; i++) {
            if (currentMax + arr[i] > arr[i]) {
                currentMax += arr[i];
            } else {
                currentMax = arr[i];
                currentStart = i; // Start a new subarray from the current index
            }

            if (currentMax > maxSoFar) {
                maxSoFar = currentMax;
                start = currentStart;
                end = i;
            }
        }
        if (maxSoFar == Integer.MIN_VALUE)
        {
            int maxVal = Integer.MIN_VALUE;
            int index = 0;
            for(int i = 0; i< arr.length; i++){
                if(arr[i] > maxVal){
                    maxVal = arr[i];
                    index = i;
                }
            }
            return new int[]{maxVal, index, index};

        }
        return new int[]{maxSoFar, start, end};
    }

    // 3. Kadane's Algorithm with Handling All Negative Numbers Efficiently
    //   - Specifically handles cases where all numbers in the array are negative
    //   - If all numbers are negative, returns the largest negative number
    //   - Time Complexity: O(n), Space Complexity: O(1)
    public static int kadaneAllNegative(int[] arr) {
        int maxSoFar = Integer.MIN_VALUE;
        int currentMax = 0;
        boolean allNegative = true;

        for (int num : arr) {
            if (num > 0) {
                allNegative = false; // Found a positive number
                break;
            }
        }

        if (allNegative) {
            for (int num : arr) {
                maxSoFar = Math.max(maxSoFar, num); // Find the largest negative
            }
            return maxSoFar;
        }

        for (int num : arr) {
            currentMax = Math.max(0, currentMax + num);
            maxSoFar = Math.max(maxSoFar, currentMax);
        }
        return maxSoFar;
    }

    // 4. Kadane's Algorithm - Concise Version
    //   - A more compact version of the basic algorithm
    //   - Uses the same logic but with less verbose code
    //   - Time Complexity: O(n), Space Complexity: O(1)
    public static int kadaneConcise(int[] arr) {
        int maxSoFar = arr[0]; // Initialize with the first element
        int currentMax = arr[0];

        for (int i = 1; i < arr.length; i++) {
            currentMax = Math.max(arr[i], currentMax + arr[i]);
            maxSoFar = Math.max(maxSoFar, currentMax);
        }
        return maxSoFar;
    }

    // 5. Kadane's Algorithm with Detailed Explanation
    //      - Includes print statements to show the execution flow
    //      - Explains each step in detail
    public static int kadaneDetailed(int[] arr) {
        int maxSoFar = 0;
        int currentMax = 0;
        System.out.println("Kadane's Algorithm with Detailed Explanation:");

        for (int i = 0; i < arr.length; i++) {
            int num = arr[i];
            System.out.println("Iteration " + i + ", Current Number: " + num);
            currentMax = Math.max(0, currentMax + num);
            System.out.println("  currentMax: " + currentMax + " (Math.max(0, " + currentMax + " + " + num + "))");
            maxSoFar = Math.max(maxSoFar, currentMax);
            System.out.println("  maxSoFar: " + maxSoFar + " (Math.max(" + maxSoFar + ", " + currentMax + "))");
        }
        if (maxSoFar == 0) {
            int maxVal = Integer.MIN_VALUE;
            for(int num : arr){
                maxVal = Math.max(maxVal, num);
            }
            return maxVal;
        }
        System.out.println("Final Maximum Subarray Sum: " + maxSoFar);
        return maxSoFar;
    }
}

