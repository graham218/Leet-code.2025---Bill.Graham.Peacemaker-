import java.util.Arrays;

public class MaximumSubarray {

    public static void main(String[] args) {
        int[] nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        // int[] nums = {1};
        // int[] nums = {5,4,-1,7,8};
        // int[] nums = {-2, -3, -1};

        System.out.println("Input Array: " + Arrays.toString(nums));

        // 1. Kadane's Algorithm (Standard)
        int maxSubarray1 = maxSubarrayKadane(nums);
        System.out.println("1. Kadane's Algorithm (Standard): " + maxSubarray1);

        // 2. Kadane's Algorithm (with Start and End Index)
        int[] result2 = maxSubarrayKadaneWithIndex(nums);
        System.out.println("2. Kadane's Algorithm (with Start and End Index): Max Sum = " + result2[0] + ", Start Index = " + result2[1] + ", End Index = " + result2[2]);

        // 3. Divide and Conquer Approach
        int maxSubarray3 = maxSubarrayDivideAndConquer(nums, 0, nums.length - 1);
        System.out.println("3. Divide and Conquer Approach: " + maxSubarray3);

        // 4. Dynamic Programming Approach
        int maxSubarray4 = maxSubarrayDP(nums);
        System.out.println("4. Dynamic Programming Approach: " + maxSubarray4);

        // 5.  Optimized Kadane's Algorithm (Handles all negative numbers)
        int maxSubarray5 = maxSubarrayOptimized(nums);
        System.out.println("5. Optimized Kadane's Algorithm: " + maxSubarray5);
    }

    /**
     * 1. Kadane's Algorithm (Standard)
     *
     * Finds the maximum sum of a contiguous subarray using Kadane's algorithm.
     * This is the most efficient and standard way to solve the Maximum Subarray problem.
     *
     * Time Complexity: O(n) - Linear time, as it iterates through the array once.
     * Space Complexity: O(1) - Constant space, as it only uses a few variables.
     *
     * @param nums The input array of integers.
     * @return The maximum sum of any contiguous subarray within the input array.
     */
    public static int maxSubarrayKadane(int[] nums) {
        int maxSoFar = nums[0];  // Stores the maximum sum found so far.  Initialized with the first element.
        int currentMax = nums[0]; // Stores the maximum sum ending at the current position.

        for (int i = 1; i < nums.length; i++) {
            // Decide whether to extend the current subarray or start a new one.
            currentMax = Math.max(nums[i], currentMax + nums[i]);
            // Update the maximum sum found so far.
            maxSoFar = Math.max(maxSoFar, currentMax);
        }
        return maxSoFar;
    }

    /**
     * 2. Kadane's Algorithm (with Start and End Index)
     *
     * Finds the maximum sum of a contiguous subarray using Kadane's algorithm and also
     * returns the start and end indices of that subarray.  This is useful when you
     * need to know *where* the maximum subarray is located.
     *
     * Time Complexity: O(n) - Linear time, as it iterates through the array once.
     * Space Complexity: O(1) - Constant space, as it only uses a few variables.
     *
     * @param nums The input array of integers.
     * @return An array of three integers:
     * - result[0]: The maximum sum of the contiguous subarray.
     * - result[1]: The starting index of the maximum subarray.
     * - result[2]: The ending index of the maximum subarray.
     */
    public static int[] maxSubarrayKadaneWithIndex(int[] nums) {
        int maxSoFar = nums[0];
        int currentMax = nums[0];
        int start = 0;
        int end = 0;
        int tempStart = 0; // Temporary start index to track potential start of a new subarray.

        for (int i = 1; i < nums.length; i++) {
            if (nums[i] > currentMax + nums[i]) {
                // Start a new subarray from the current element.
                currentMax = nums[i];
                tempStart = i; // Update the temporary start index.
            } else {
                // Extend the current subarray.
                currentMax = currentMax + nums[i];
            }

            if (currentMax > maxSoFar) {
                // Update the maximum sum and the start/end indices.
                maxSoFar = currentMax;
                start = tempStart; // The start index is the last tempStart
                end = i;         // The end index is the current index.
            }
        }
        return new int[]{maxSoFar, start, end};
    }



    /**
     * 3. Divide and Conquer Approach
     *
     * Finds the maximum sum of a contiguous subarray using the divide and conquer approach.
     * This approach recursively divides the array into two halves, finds the maximum subarray
     * in each half, and then finds the maximum subarray that crosses the midpoint.
     *
     * Time Complexity: O(n log n) - Due to the recursive calls.
     * Space Complexity: O(log n) -  Due to the recursion depth.
     *
     * @param nums  The input array of integers.
     * @param left  The starting index of the subarray.
     * @param right The ending index of the subarray.
     * @return The maximum sum of any contiguous subarray within the specified range.
     */
    public static int maxSubarrayDivideAndConquer(int[] nums, int left, int right) {
        if (left == right) {
            // Base case: If the subarray has only one element, return that element.
            return nums[left];
        }

        int mid = (left + right) / 2;  // Find the middle point of the subarray.

        // Recursively find the maximum subarray sum in the left and right halves.
        int leftMax = maxSubarrayDivideAndConquer(nums, left, mid);
        int rightMax = maxSubarrayDivideAndConquer(nums, mid + 1, right);
        int crossingMax = findMaxCrossingSubarray(nums, left, mid, right); // Find max crossing subarray

        // Return the maximum of the three: left subarray max, right subarray max, and crossing subarray max.
        return Math.max(Math.max(leftMax, rightMax), crossingMax);
    }

    /**
     * Helper function for the divide and conquer approach to find the maximum subarray
     * that crosses the midpoint of the given subarray.
     *
     * Time Complexity: O(n) - Linear time, as it iterates through a portion of the array.
     * Space Complexity: O(1) - Constant space.
     */
    private static int findMaxCrossingSubarray(int[] nums, int left, int mid, int right) {
        int leftSum = Integer.MIN_VALUE;
        int currentSum = 0;
        // Iterate from the midpoint to the left, finding the maximum sum ending at the midpoint.
        for (int i = mid; i >= left; i--) {
            currentSum += nums[i];
            leftSum = Math.max(leftSum, currentSum);
        }

        int rightSum = Integer.MIN_VALUE;
        currentSum = 0;
        // Iterate from the midpoint + 1 to the right, finding the maximum sum starting from the midpoint + 1.
        for (int i = mid + 1; i <= right; i++) {
            currentSum += nums[i];
            rightSum = Math.max(rightSum, currentSum);
        }

        // The maximum crossing subarray sum is the sum of the maximum left sum and maximum right sum.
        return leftSum + rightSum;
    }

    /**
     * 4. Dynamic Programming Approach
     *
     * Finds the maximum sum of a contiguous subarray using dynamic programming.
     * This approach builds a table (in this case, implicitly using a single variable)
     * to store the maximum subarray sum ending at each position.
     *
     * Time Complexity: O(n) - Linear time, as it iterates through the array once.
     * Space Complexity: O(1) - Constant space, as it only uses a few variables.
     *
     * @param nums The input array of integers.
     * @return The maximum sum of any contiguous subarray within the input array.
     */
    public static int maxSubarrayDP(int[] nums) {
        if (nums == null || nums.length == 0) {
            return 0;
        }

        int[] dp = new int[nums.length]; // dp[i] stores the maximum subarray sum ending at index i.
        dp[0] = nums[0];                 // Initialize the first element of the dp array.
        int maxSoFar = nums[0];         // Initialize the overall maximum sum.

        for (int i = 1; i < nums.length; i++) {
            // The maximum sum ending at i is either the current element itself,
            // or the current element plus the maximum sum ending at the previous position.
            dp[i] = Math.max(nums[i], dp[i - 1] + nums[i]);
            maxSoFar = Math.max(maxSoFar, dp[i]); // Update the overall maximum.
        }
        return maxSoFar;
    }

    /**
     * 5. Optimized Kadane's Algorithm (Handles all negative numbers)
     *
     * An optimized version of Kadane's algorithm that specifically handles cases where the
     * input array contains all negative numbers.  In such cases, the standard Kadane's
     * algorithm might return 0, but this version correctly returns the largest negative number.
     *
     * Time Complexity: O(n) - Linear time, as it iterates through the array once.
     * Space Complexity: O(1) - Constant space.
     *
     * @param nums The input array of integers.
     * @return The maximum sum of any contiguous subarray within the input array.
     */
    public static int maxSubarrayOptimized(int[] nums) {
        int maxSoFar = Integer.MIN_VALUE; // Initialize maxSoFar to the smallest possible integer.
        int currentMax = 0;

        for (int i = 0; i < nums.length; i++) {
            currentMax = currentMax + nums[i];
            if (currentMax > maxSoFar) {
                maxSoFar = currentMax;
            }
            if (currentMax < 0) {
                currentMax = 0; // Reset currentMax to 0, effectively starting a new subarray.
            }
        }
        return maxSoFar;
    }
}

