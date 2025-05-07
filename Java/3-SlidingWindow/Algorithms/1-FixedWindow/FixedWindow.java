import java.util.Arrays;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Deque;

public class SlidingWindowFixed {

    /**
     * Given an array and a window size, this program demonstrates finding the maximum (or sum, etc.)
     * within each fixed-size sliding window.  The core concept is to efficiently "slide" the window
     * through the array without redundant calculations.
     *
     * Problem:
     * You are given an array of integers, `nums`, and an integer `k` representing the size of the sliding window.
     * Your task is to find the maximum value within each sliding window as it moves from left to right.
     *
     * Example:
     * nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
     * Output: [3, 3, 5, 5, 6, 7]
     * Explanation:
     * Window position                Max
     * ---------------               -----
     * [1  3  -1] -3  5  3  6  7       3
     * 1 [3  -1  -3] 5  3  6  7       3
     * 1  3 [-1  -3  5] 3  6  7       5
     * 1  3  -1 [-3  5  3] 6  7       5
     * 1  3  -1  -3 [5  3  6] 7       6
     * 1  3  -1  -3  5 [3  6  7]      7
     *
     * Key Concepts for Fixed Window Problems:
     * 1.  Window Size: The window size 'k' is fixed. This is crucial.
     * 2.  Iteration:  The window slides through the array, processing 'k' elements at a time.
     * 3.  Efficiency:  The goal is to avoid recalculating the same elements repeatedly.
     * 4.  Starting Point: The window starts at the beginning of the array.
     * 5.  Ending Condition: The window stops when its right edge reaches the end of the array.
     */

    public static void main(String[] args) {
        int[] nums = {1, 3, -1, -3, 5, 3, 6, 7};
        int k = 3;

        System.out.println("Array: " + Arrays.toString(nums));
        System.out.println("Window Size: " + k);

        // Example Usage of the different approaches:
        System.out.println("\nApproach 1: Brute Force (Iterative): " + Arrays.toString(maxSlidingWindowBruteForce(nums, k)));
        System.out.println("Approach 2: Optimized Iterative: " + Arrays.toString(maxSlidingWindowOptimized(nums, k)));
        System.out.println("Approach 3: Using a Deque: " + Arrays.toString(maxSlidingWindowDeque(nums, k)));
        System.out.println("Approach 4: Using Priority Queue: " + Arrays.toString(maxSlidingWindowPriorityQueue(nums, k)));
        System.out.println("Approach 5: Sum of Subarrays: " + Arrays.toString(sumOfSubarrays(nums, k)));

    }

    /**
     * Approach 1: Brute Force (Iterative)
     * -   For each window position, iterate through the 'k' elements and find the maximum.
     * -   This is the most straightforward but least efficient approach.
     * -   Time Complexity: O(n*k), where n is the length of the array and k is the window size.
     * -   Space Complexity: O(1) - constant extra space.
     */
    public static int[] maxSlidingWindowBruteForce(int[] nums, int k) {
        if (nums == null || nums.length == 0 || k <= 0) {
            return new int[0]; // Handle edge cases: null or empty array, invalid k
        }
        if (k > nums.length) {
            return new int[0]; // handle case where k is larger than array
        }

        int n = nums.length;
        int[] result = new int[n - k + 1]; // Size of result is (n - k + 1)
        for (int i = 0; i <= n - k; i++) {
            int max = Integer.MIN_VALUE;
            for (int j = i; j < i + k; j++) {
                max = Math.max(max, nums[j]);
            }
            result[i] = max;
        }
        return result;
    }


    /**
     * Approach 2: Optimized Iterative
     * -   An improvement over the brute force approach.
     * -   It avoids recalculating the maximum of the overlapping part of the window.
     * -   It calculates the maximum for the first window, and then for the subsequent windows,
     * it checks if the outgoing element was the maximum. If it was, it recalculates the maximum
     * for the new window. Otherwise, it simply compares the new incoming element with the
     * previous maximum.
     * -   Time Complexity: O(n*k) in worst case (if max is always leaving the window), but performs better in average case.
     * -   Space Complexity: O(1) - constant extra space.
     */
    public static int[] maxSlidingWindowOptimized(int[] nums, int k) {
        if (nums == null || nums.length == 0 || k <= 0) {
            return new int[0];
        }
        if (k > nums.length) {
            return new int[0];
        }

        int n = nums.length;
        int[] result = new int[n - k + 1];

        // Calculate max for the first window
        int max = Integer.MIN_VALUE;
        for (int i = 0; i < k; i++) {
            max = Math.max(max, nums[i]);
        }
        result[0] = max;

        // Slide the window
        for (int i = 1; i <= n - k; i++) {
            // If the outgoing element was the previous maximum, recalculate the maximum for the current window
            if (nums[i - 1] == max) {
                max = Integer.MIN_VALUE;
                for (int j = i; j < i + k; j++) {
                    max = Math.max(max, nums[j]);
                }
            } else {
                // Otherwise, just compare the new incoming element with the previous maximum
                max = Math.max(max, nums[i + k - 1]);
            }
            result[i] = max;
        }
        return result;
    }

    /**
     * Approach 3: Using a Deque (Double-Ended Queue)
     * -   The most efficient approach for this problem.
     * -   A deque (double-ended queue) is used to store indices of the elements in the current window.
     * -   The deque maintains the indices of elements in descending order of their values.
     * -   The front of the deque always contains the index of the maximum element in the current window.
     * -   Time Complexity: O(n) - each element is processed at most twice (added and removed from deque).
     * -   Space Complexity: O(k) - the deque stores at most 'k' indices.
     */
    public static int[] maxSlidingWindowDeque(int[] nums, int k) {
        if (nums == null || nums.length == 0 || k <= 0) {
            return new int[0];
        }
        if (k > nums.length) {
            return new int[0];
        }

        int n = nums.length;
        int[] result = new int[n - k + 1];
        Deque<Integer> deque = new LinkedList<>(); // Use LinkedList as a Deque

        for (int i = 0; i < n; i++) {
            // Remove elements from the deque that are out of the current window
            while (!deque.isEmpty() && deque.peekFirst() <= i - k) {
                deque.pollFirst();
            }
            // Remove elements from the deque that are smaller than the current element
            while (!deque.isEmpty() && nums[deque.peekLast()] <= nums[i]) {
                deque.pollLast();
            }
            // Add the index of the current element to the deque
            deque.offerLast(i);
            // The front of the deque is the index of the maximum element in the current window
            if (i >= k - 1) {
                result[i - k + 1] = nums[deque.peekFirst()];
            }
        }
        return result;
    }

    /**
     * Approach 4: Using a Priority Queue (Max Heap)
     * -   Uses a priority queue (max heap) to store the elements of the current window along with their indices.
     * -   The priority queue automatically sorts the elements in descending order.
     * -    When the window slides, we remove elements that are no longer in the window and add the new element.
     * -   Time Complexity: O(n log k) -  Adding and removing elements from a priority queue of size k takes O(log k) time.
     * -   Space Complexity: O(k) - the priority queue stores at most 'k' elements.
     */
    public static int[] maxSlidingWindowPriorityQueue(int[] nums, int k) {
        if (nums == null || nums.length == 0 || k <= 0) {
            return new int[0];
        }
        if (k > nums.length) {
            return new int[0];
        }

        int n = nums.length;
        int[] result = new int[n - k + 1];
        // Use a max heap (PriorityQueue) to store elements and their indices.
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> b[0] - a[0]); // {value, index}

        for (int i = 0; i < n; i++) {
            // Add the current element and its index to the priority queue
            pq.offer(new int[]{nums[i], i});

            // Remove elements from the priority queue that are out of the current window
            while (pq.peek()[1] <= i - k) {
                pq.poll();
            }

            // The top of the priority queue is the maximum element in the current window
            if (i >= k - 1) {
                result[i - k + 1] = pq.peek()[0];
            }
        }
        return result;
    }

    /**
     * Approach 5: Sum of Subarrays (Illustrative Example - Not Maximum)
     * -   This approach calculates the sum of each subarray of size 'k'.
     * -   It demonstrates a different fixed-window problem (sum instead of maximum).
     * -   This highlights the versatility of the fixed-window technique.
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(1)
     */
    public static int[] sumOfSubarrays(int[] nums, int k) {
        if (nums == null || nums.length == 0 || k <= 0) {
            return new int[0];
        }
        if (k > nums.length) {
            return new int[0];
        }

        int n = nums.length;
        int[] result = new int[n - k + 1];
        int windowSum = 0;

        // Calculate the sum of the first window
        for (int i = 0; i < k; i++) {
            windowSum += nums[i];
        }
        result[0] = windowSum;

        // Slide the window and update the sum
        for (int i = 1; i <= n - k; i++) {
            windowSum = windowSum - nums[i - 1] + nums[i + k - 1]; // Subtract the outgoing element and add the incoming element
            result[i] = windowSum;
        }
        return result;
    }
}

