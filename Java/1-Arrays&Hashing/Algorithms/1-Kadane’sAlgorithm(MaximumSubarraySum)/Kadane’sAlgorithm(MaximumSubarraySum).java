import java.util.Arrays;

public class KadanesAlgorithm {

    public static void main(String[] args) {
        int[] nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        //int[] nums = {5,4,-1,7,8};
        //int[] nums = {-2, -3, -1};

        System.out.println("Input Array: " + Arrays.toString(nums));

        // 1. Basic Kadane's Algorithm
        int maxSubarraySum1 = kadaneBasic(nums);
        System.out.println("1. Basic Kadane's Algorithm: " + maxSubarraySum1);

        // 2. Kadane's Algorithm with Start and End Indices
        int[] result2 = kadaneWithIndices(nums);
        System.out.println("2. Kadane's Algorithm with Start and End Indices: Max Sum = " + result2[0] +
                ", Start Index = " + result2[1] + ", End Index = " + result2[2]);

        // 3. Kadane's Algorithm - Optimized (Slightly more efficient)
        int maxSubarraySum3 = kadaneOptimized(nums);
        System.out.println("3. Kadane's Algorithm - Optimized: " + maxSubarraySum3);

        // 4. Kadane's Algorithm with Negative Numbers Handling
        int maxSubarraySum4 = kadaneHandleNegative(nums);
        System.out.println("4. Kadane's Algorithm with Negative Numbers Handling: " + maxSubarraySum4);

        // 5. Kadane's Algorithm (Concise Version)
        int maxSubarraySum5 = kadaneConcise(nums);
        System.out.println("5. Kadane's Algorithm (Concise Version): " + maxSubarraySum5);
    }

    /**
     * 1. Basic Kadane's Algorithm:
     * - Iterates through the array, keeping track of the current maximum subarray sum
     * ending at the current position (`currentSum`) and the overall maximum subarray sum
     * encountered so far (`maxSum`).
     * - If `currentSum` becomes negative, it's reset to 0 because a negative sum would
     * only decrease the sum of any subsequent subarray.
     *
     * Time Complexity: O(n), where n is the length of the input array.
     * Space Complexity: O(1)
     */
    public static int kadaneBasic(int[] nums) {
        int maxSum = Integer.MIN_VALUE; // Initialize maxSum to the smallest possible integer
        int currentSum = 0;

        for (int num : nums) {
            currentSum = Math.max(num, currentSum + num); // Decide to start a new subarray or extend the current one
            maxSum = Math.max(maxSum, currentSum);     // Update maxSum if currentSum is greater
        }
        return maxSum;
    }

    /**
     * 2. Kadane's Algorithm with Start and End Indices:
     * - In addition to calculating the maximum subarray sum, this version also tracks
     * the starting and ending indices of the maximum subarray.
     * - `start` and `end` track the start and end of the current subarray.
     * - `bestStart` and `bestEnd` track the start and end of the maximum subarray found so far.
     * - When a new maximum sum is found, `bestStart` and `bestEnd` are updated.  If the current_sum is
     * reset to zero, the start index is moved to the next element.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    public static int[] kadaneWithIndices(int[] nums) {
        int maxSum = Integer.MIN_VALUE;
        int currentSum = 0;
        int start = 0;
        int end = 0;
        int bestStart = 0;
        int bestEnd = 0;

        for (int i = 0; i < nums.length; i++) {
            if (currentSum <= 0) { //if current sum is less than or equal to zero, we start a new subarray
                currentSum = nums[i];
                start = i;        // Reset start index
            } else {
                currentSum += nums[i]; // Extend current subarray
            }

            if (currentSum > maxSum) { // Update max sum and indices
                maxSum = currentSum;
                bestStart = start;
                bestEnd = i;
            }
        }
        return new int[]{maxSum, bestStart, bestEnd};
    }

    /**
     * 3. Kadane's Algorithm - Optimized:
     * - This version is a slight optimization of the basic Kadane's algorithm.
     * - It avoids the use of Math.max() in the loop by checking if currentSum becomes
     * negative *before* adding the current element.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    public static int kadaneOptimized(int[] nums) {
        int maxSum = Integer.MIN_VALUE;
        int currentSum = 0;

        for (int num : nums) {
            if (currentSum < 0) {
                currentSum = 0; // Reset currentSum if it's negative
            }
            currentSum += num;
            maxSum = Math.max(maxSum, currentSum);
        }
        return maxSum;
    }

    /**
     * 4. Kadane's Algorithm with Negative Numbers Handling:
     * - This version explicitly handles cases where the array contains all negative numbers.
     * - If the array contains only negative numbers, the algorithm returns the largest
     * negative number (least negative number), which is the maximum subarray sum in that case.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    public static int kadaneHandleNegative(int[] nums) {
        int maxSum = Integer.MIN_VALUE;
        int currentSum = 0;
        boolean allNegative = true;

        for (int num : nums) {
            if (num > 0) {
                allNegative = false; //check if there is a positive number, if found, set allNegative to false
            }
            currentSum = Math.max(num, currentSum + num);
            maxSum = Math.max(maxSum, currentSum);
        }

        if (allNegative) {
            // Find the maximum (least negative) number in the array
            for (int num : nums) {
                maxSum = Math.max(maxSum, num);
            }
        }
        return maxSum;
    }

    /**
     * 5. Kadane's Algorithm (Concise Version):
     * - A more concise version of the basic Kadane's algorithm.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    public static int kadaneConcise(int[] nums) {
        int maxSum = nums[0];  // Initialize with the first element
        int currentSum = nums[0];

        for (int i = 1; i < nums.length; i++) {
            currentSum = Math.max(nums[i], currentSum + nums[i]); // 핵심
            maxSum = Math.max(maxSum, currentSum);
        }
        return maxSum;
    }
}

