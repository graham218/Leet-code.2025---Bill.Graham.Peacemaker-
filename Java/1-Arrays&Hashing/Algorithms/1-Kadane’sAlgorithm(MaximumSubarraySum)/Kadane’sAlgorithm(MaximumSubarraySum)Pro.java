import java.util.Arrays;

public class KadanesAlgorithm {

    public static void main(String[] args) {
        int[] nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        int[] nums2 = {1};
        int[] nums3 = {5, 4, -1, 7, 8};
        int[] nums4 = {-2, -3, -1}; // Test case with all negative numbers
        int[] nums5 = {-1, -2, -3, -4, -5, -6};

        // 1. Basic Kadane's Algorithm (Most Common)
        System.out.println("1. Basic Kadane's Algorithm:");
        System.out.println("Maximum Subarray Sum: " + maxSubarraySum(nums)); // Output: 6
        System.out.println("Maximum Subarray Sum: " + maxSubarraySum(nums2)); // Output: 1
        System.out.println("Maximum Subarray Sum: " + maxSubarraySum(nums3)); // Output: 23
        System.out.println("Maximum Subarray Sum: " + maxSubarraySum(nums4)); // Output: -1
        System.out.println("Maximum Subarray Sum: " + maxSubarraySum(nums5)); // Output: -1

        // 2. Kadane's Algorithm with Start and End Indices
        System.out.println("\n2. Kadane's Algorithm with Start and End Indices:");
        int[] result = maxSubarraySumWithIndices(nums);
        System.out.println("Maximum Subarray Sum: " + result[0]); // Output: 6
        System.out.println("Start Index: " + result[1]);             // Output: 3
        System.out.println("End Index: " + result[2]);               // Output: 6

        int[] result2 = maxSubarraySumWithIndices(nums2);
        System.out.println("Maximum Subarray Sum: " + result2[0]);
        System.out.println("Start Index: " + result2[1]);
        System.out.println("End Index: " + result2[2]);

        int[] result3 = maxSubarraySumWithIndices(nums3);
        System.out.println("Maximum Subarray Sum: " + result3[0]);
        System.out.println("Start Index: " + result3[1]);
        System.out.println("End Index: " + result3[2]);

        int[] result4 = maxSubarraySumWithIndices(nums4);
        System.out.println("Maximum Subarray Sum: " + result4[0]);
        System.out.println("Start Index: " + result4[1]);
        System.out.println("End Index: " + result4[2]);

        int[] result5 = maxSubarraySumWithIndices(nums5);
        System.out.println("Maximum Subarray Sum: " + result5[0]);
        System.out.println("Start Index: " + result5[1]);
        System.out.println("End Index: " + result5[2]);

        // 3. Kadane's Algorithm with Handling All Negative Numbers
        System.out.println("\n3. Kadane's Algorithm with Handling All Negative Numbers:");
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumHandleNegative(nums)); // Output: 6
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumHandleNegative(nums2)); // Output: 1
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumHandleNegative(nums3)); // Output: 23
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumHandleNegative(nums4)); // Output: -1
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumHandleNegative(nums5)); // Output: -1

        // 4. Kadane's Algorithm for Circular Subarray (Handles Wraparound)
        System.out.println("\n4. Kadane's Algorithm for Circular Subarray:");
        System.out.println("Maximum Circular Subarray Sum: " + maxSubarraySumCircular(nums)); // Output: 6
        System.out.println("Maximum Circular Subarray Sum: " + maxSubarraySumCircular(nums2)); // Output: 1
        System.out.println("Maximum Circular Subarray Sum: " + maxSubarraySumCircular(nums3)); // Output: 23
        System.out.println("Maximum Circular Subarray Sum: " + maxSubarraySumCircular(nums4)); // Output: -1
        System.out.println("Maximum Circular Subarray Sum: " + maxSubarraySumCircular(nums5)); //Output: -1

        // 5. Kadane's Algorithm with Dynamic Programming (Less Common, for illustration)
        System.out.println("\n5. Kadane's Algorithm with Dynamic Programming:");
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumDP(nums)); // Output: 6
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumDP(nums2)); // Output: 1
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumDP(nums3)); // Output: 23
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumDP(nums4)); // Output: -1
        System.out.println("Maximum Subarray Sum: " + maxSubarraySumDP(nums5)); // Output: -1
    }

    // 1. Basic Kadane's Algorithm
    // This is the most common and straightforward implementation.
    // It iterates through the array, keeping track of the current maximum sum
    // and the overall maximum sum.
    public static int maxSubarraySum(int[] nums) {
        int maxSoFar = Integer.MIN_VALUE;
        int currentMax = 0;

        for (int num : nums) {
            currentMax = Math.max(num, currentMax + num);
            maxSoFar = Math.max(maxSoFar, currentMax);
        }
        return maxSoFar;
    }

    // 2. Kadane's Algorithm with Start and End Indices
    // This version keeps track of the start and end indices of the maximum subarray.
    // This is useful when you need to know *where* the maximum subarray is located.
    public static int[] maxSubarraySumWithIndices(int[] nums) {
        int maxSoFar = Integer.MIN_VALUE;
        int currentMax = 0;
        int start = 0;
        int end = 0;
        int tempStart = 0;

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > currentMax + nums[i]) {
                currentMax = nums[i];
                tempStart = i; // Start a new subarray here
            } else {
                currentMax += nums[i];
            }

            if (currentMax > maxSoFar) {
                maxSoFar = currentMax;
                start = tempStart;
                end = i; // Update end index of the maximum subarray.
            }
        }
        return new int[]{maxSoFar, start, end};
    }

    // 3. Kadane's Algorithm with Handling All Negative Numbers
    //  This version handles the case where all numbers in the array are negative.
    //  In that case, the maximum subarray sum is the largest negative number.
    public static int maxSubarraySumHandleNegative(int[] nums) {
        int maxSoFar = Integer.MIN_VALUE;
        int currentMax = 0;
        boolean allNegative = true;

        for (int num : nums) {
            if (num > 0) {
                allNegative = false;
                break;
            }
        }

        if (allNegative) {
            for (int num : nums) {
                maxSoFar = Math.max(maxSoFar, num);
            }
            return maxSoFar;
        } else {
            for (int num : nums) {
                currentMax = Math.max(num, currentMax + num);
                maxSoFar = Math.max(maxSoFar, currentMax);
            }
            return maxSoFar;
        }
    }

    // 4. Kadane's Algorithm for Circular Subarray
    // This version handles circular subarrays, where the end of the array
    // is considered to be connected to the beginning.
    // This is a more complex variation of Kadane's algorithm.
    public static int maxSubarraySumCircular(int[] nums) {
        int n = nums.length;
        if (n == 0) return 0;

        // 1. Calculate the maximum subarray sum using standard Kadane's
        int maxSoFar = maxSubarraySum(nums);

        // 2. Calculate the total sum of the array
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        // 3. Invert the signs of all elements in the array
        for (int i = 0; i < n; i++) {
            nums[i] = -nums[i];
        }

        // 4. Calculate the minimum subarray sum (which is the maximum subarray sum of the inverted array)
        int minSubarraySum = maxSubarraySum(nums);

        // 5. Calculate the maximum circular subarray sum
        //    It's the maximum of the standard Kadane's result and
        //    the total sum minus the minimum subarray sum.
        if (totalSum == -minSubarraySum) { //Handle the case where all elements are negative
            return maxSoFar;
        }
        int circularMax = totalSum + minSubarraySum;

        return Math.max(maxSoFar, circularMax);
    }

    // 5. Kadane's Algorithm with Dynamic Programming
    // This is a dynamic programming approach to Kadane's algorithm.
    // It's less common than the iterative approach, but it illustrates
    // how dynamic programming can be used to solve this problem.
    public static int maxSubarraySumDP(int[] nums) {
        int n = nums.length;
        if (n == 0) return 0;

        int[] dp = new int[n];
        dp[0] = nums[0];  // Base case: the first element itself.
        int maxSoFar = nums[0];

        for (int i = 1; i < n; i++) {
            // The maximum subarray ending at index i is either
            // the current element itself, or the current element plus
            // the maximum subarray ending at the previous index.
            dp[i] = Math.max(nums[i], dp[i - 1] + nums[i]);
            maxSoFar = Math.max(maxSoFar, dp[i]);
        }
        return maxSoFar;
    }
}

