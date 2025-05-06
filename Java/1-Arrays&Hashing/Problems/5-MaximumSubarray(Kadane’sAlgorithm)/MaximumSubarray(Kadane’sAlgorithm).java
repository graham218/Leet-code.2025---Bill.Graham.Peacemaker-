import java.util.Arrays;

public class MaximumSubarray {

    public static void main(String[] args) {
        int[] nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        // int[] nums = {1};
        // int[] nums = {5,4,-1,7,8};
        // int[] nums = {-2, -1};

        System.out.println("Input Array: " + Arrays.toString(nums));

        // Approach 1: Basic Kadane's Algorithm
        int maxSubarray1 = maxSubarrayKadane(nums);
        System.out.println("Approach 1: Basic Kadane's Algorithm - Maximum Subarray Sum: " + maxSubarray1);

        // Approach 2: Kadane's Algorithm with Start and End Index
        int[] result2 = maxSubarrayKadaneWithIndex(nums);
        System.out.println("Approach 2: Kadane's with Start/End Index - Maximum Subarray Sum: " + result2[0]);
        System.out.println("Approach 2: Kadane's with Start/End Index - Start Index: " + result2[1]);
        System.out.println("Approach 2: Kadane's with Start/End Index - End Index: " + result2[2]);

        // Approach 3: Kadane's Algorithm - Optimized (Slightly more efficient)
        int maxSubarray3 = maxSubarrayKadaneOptimized(nums);
        System.out.println("Approach 3: Optimized Kadane's Algorithm - Maximum Subarray Sum: " + maxSubarray3);

        // Approach 4: Dynamic Programming (Similar to Kadane's)
        int maxSubarray4 = maxSubarrayDP(nums);
        System.out.println("Approach 4: Dynamic Programming - Maximum Subarray Sum: " + maxSubarray4);

        // Approach 5: Divide and Conquer (Recursive)
        int maxSubarray5 = maxSubarrayDivideAndConquer(nums, 0, nums.length - 1);
        System.out.println("Approach 5: Divide and Conquer - Maximum Subarray Sum: " + maxSubarray5);
    }

    // Approach 1: Basic Kadane's Algorithm
    // Time Complexity: O(n), Space Complexity: O(1)
    // Explanation: Iterates through the array, keeping track of the current maximum subarray sum
    // ending at the current position, and the overall maximum subarray sum.
    public static int maxSubarrayKadane(int[] nums) {
        int maxSoFar = Integer.MIN_VALUE; // Initialize with the smallest possible integer value.
        int currentMax = 0;

        for (int num : nums) {
            currentMax = Math.max(num, currentMax + num); // Decide to either start a new subarray from the current element, or extend the previous subarray.
            maxSoFar = Math.max(maxSoFar, currentMax);  // Update the overall maximum sum.
        }
        return maxSoFar;
    }

    // Approach 2: Kadane's Algorithm with Start and End Index
    // Time Complexity: O(n), Space Complexity: O(1)
    // Explanation:  This approach extends the basic Kadane's algorithm to also track the
    // starting and ending indices of the maximum subarray.
    public static int[] maxSubarrayKadaneWithIndex(int[] nums) {
        int maxSoFar = Integer.MIN_VALUE;
        int currentMax = 0;
        int start = 0;
        int end = 0;
        int tempStart = 0; // Temporary start index

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > currentMax + nums[i]) {
                currentMax = nums[i];
                tempStart = i; // Start a new subarray
            } else {
                currentMax += nums[i]; // Extend the current subarray
            }

            if (currentMax > maxSoFar) {
                maxSoFar = currentMax;
                start = tempStart; // Update start index
                end = i;     // Update end index
            }
        }
        return new int[]{maxSoFar, start, end};
    }

    // Approach 3: Kadane's Algorithm - Optimized (Slightly more efficient)
    // Time Complexity: O(n), Space Complexity: O(1)
    // Explanation: This version is slightly optimized by removing one Math.max() operation
    // in the loop.  It's a micro-optimization, but can be beneficial in performance-critical scenarios.
    public static int maxSubarrayKadaneOptimized(int[] nums) {
        int maxSoFar = Integer.MIN_VALUE;
        int currentMax = 0;

        for (int num : nums) {
            currentMax += num; // Add the current number
            if (currentMax > maxSoFar) {
                maxSoFar = currentMax; // Update maxSoFar if currentMax is greater
            }
            if (currentMax < 0) {
                currentMax = 0;    // Reset currentMax if it becomes negative
            }
        }
        return maxSoFar;
    }

    // Approach 4: Dynamic Programming (Similar to Kadane's)
    // Time Complexity: O(n), Space Complexity: O(n) - Can be optimized to O(1)
    // Explanation:  This approach uses dynamic programming to store the maximum subarray sum
    // ending at each position in a dp array.  It's very similar in concept to Kadane's.
    public static int maxSubarrayDP(int[] nums) {
        int n = nums.length;
        int[] dp = new int[n]; // dp[i] stores the maximum subarray sum ending at index i
        dp[0] = nums[0];
        int maxSoFar = nums[0];

        for (int i = 1; i < n; i++) {
            dp[i] = Math.max(nums[i], dp[i - 1] + nums[i]); // Recurrence relation
            maxSoFar = Math.max(maxSoFar, dp[i]);
        }
        return maxSoFar;
        // Optimized version with O(1) space complexity
        // int maxSoFar = nums[0];
        // int currentMax = nums[0];
        // for (int i = 1; i < n; i++) {
        //     currentMax = Math.max(nums[i], currentMax + nums[i]);
        //     maxSoFar = Math.max(maxSoFar, currentMax);
        // }
        // return maxSoFar;
    }

    // Approach 5: Divide and Conquer (Recursive)
    // Time Complexity: O(n log n), Space Complexity: O(log n) due to recursion depth
    // Explanation:  This approach recursively divides the array into two halves,
    // finds the maximum subarray sum in each half, and then finds the maximum
    // subarray sum that crosses the midpoint.
    public static int maxSubarrayDivideAndConquer(int[] nums, int low, int high) {
        if (low == high) {
            return nums[low]; // Base case: single element
        }

        int mid = (low + high) / 2;

        // Recursively find the maximum subarray sum in the left and right halves
        int leftMax = maxSubarrayDivideAndConquer(nums, low, mid);
        int rightMax = maxSubarrayDivideAndConquer(nums, mid + 1, high);
        int crossingMax = findMaxCrossingSubarray(nums, low, mid, high); // Find max crossing subarray

        // Return the maximum of the three
        return Math.max(Math.max(leftMax, rightMax), crossingMax);
    }

    // Helper function to find the maximum subarray sum that crosses the midpoint
    // Time Complexity: O(n), Space Complexity: O(1)
    private static int findMaxCrossingSubarray(int[] nums, int low, int mid, int high) {
        int leftSum = Integer.MIN_VALUE;
        int currentSum = 0;
        // Iterate from mid to low to find max sum ending at mid
        for (int i = mid; i >= low; i--) {
            currentSum += nums[i];
            leftSum = Math.max(leftSum, currentSum);
        }

        int rightSum = Integer.MIN_VALUE;
        currentSum = 0;
        // Iterate from mid+1 to high to find max sum starting from mid+1
        for (int i = mid + 1; i <= high; i++) {
            currentSum += nums[i];
            rightSum = Math.max(rightSum, currentSum);
        }

        return leftSum + rightSum; // Return the sum of the left and right max sums
    }
}

