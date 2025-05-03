import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;

public class TwoSum {

    /**
     * Given an array of integers nums and an integer target, find the two numbers in the array that add up to the target.
     *
     * Example:
     * ----------
     * Input: nums = [2,7,11,15], target = 9
     * Output: [0,1]
     * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
     *
     * Constraints:
     * ----------
     * 2 <= nums.length <= 10^4
     * -10^9 <= nums[i] <= 10^9
     * -10^9 <= target <= 10^9
     * Only one valid answer exists.
     *
     * Follow-up: Can you come up with an algorithm that is less than O(n^2) time complexity?
     */

    // Approach 1: Brute Force
    // Time Complexity: O(n^2)
    // Space Complexity: O(1)
    public int[] twoSumBruteForce(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] + nums[j] == target) {
                    return new int[] { i, j };
                }
            }
        }
        // In case there is no solution, although the problem statement says there will always be one.
        return new int[] {};
    }

    // Approach 2: Using HashMap (Two-pass)
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    public int[] twoSumHashMapTwoPass(int[] nums, int target) {
        Map<Integer, Integer> numMap = new HashMap<>();
        // First pass: Store each number's value and index in the HashMap.
        for (int i = 0; i < nums.length; i++) {
            numMap.put(nums[i], i);
        }
        // Second pass: Iterate through the array and check if the complement (target - nums[i]) exists in the HashMap.
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (numMap.containsKey(complement) && numMap.get(complement) != i) {
                return new int[] { i, numMap.get(complement) };
            }
        }
        return new int[] {};
    }

    // Approach 3: Using HashMap (One-pass)
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    public int[] twoSumHashMapOnePass(int[] nums, int target) {
        Map<Integer, Integer> numMap = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (numMap.containsKey(complement)) {
                return new int[] { numMap.get(complement), i };
            } else {
                numMap.put(nums[i], i);
            }
        }
        return new int[] {};
    }

    // Approach 4: Using Two Pointers (for sorted array)
    // Time Complexity: O(n log n) for sorting, O(n) for two pointers, so O(n log n) overall
    // Space Complexity: O(n) because we are creating a copy of the input array.
    public int[] twoSumTwoPointers(int[] nums, int target) {
        // Create a copy of the original array with indices.
        int[][] numsWithIndices = new int[nums.length][2];
        for (int i = 0; i < nums.length; i++) {
            numsWithIndices[i][0] = nums[i];
            numsWithIndices[i][1] = i;
        }

        // Sort the copied array based on the numbers.
        Arrays.sort(numsWithIndices, (a, b) -> a[0] - b[0]);

        int left = 0;
        int right = nums.length - 1;

        while (left < right) {
            int sum = numsWithIndices[left][0] + numsWithIndices[right][0];
            if (sum == target) {
                // We need to return the original indices, not the indices in the sorted array.
                int originalIndex1 = numsWithIndices[left][1];
                int originalIndex2 = numsWithIndices[right][1];
                return new int[] { originalIndex1, originalIndex2 };
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return new int[] {};
    }

    // Approach 5: Using Binary Search (for sorted array)
    // Time Complexity: O(n log n)
    // Space Complexity: O(n)
    public int[] twoSumBinarySearch(int[] nums, int target) {
        // Create a copy of the original array with indices
        int[][] numsWithIndices = new int[nums.length][2];
        for (int i = 0; i < nums.length; i++) {
            numsWithIndices[i][0] = nums[i];
            numsWithIndices[i][1] = i;
        }

        // Sort the copied array based on the numbers.
        Arrays.sort(numsWithIndices, (a, b) -> a[0] - b[0]);

        for (int i = 0; i < nums.length; i++) {
            int complement = target - numsWithIndices[i][0];
            int complementIndex = binarySearch(numsWithIndices, complement, i); // Pass i to exclude the current number
            if (complementIndex != -1) {
                int originalIndex1 = numsWithIndices[i][1];
                int originalIndex2 = numsWithIndices[complementIndex][1];
                return new int[]{originalIndex1, originalIndex2};
            }
        }

        return new int[] {};
    }

    // Binary Search Helper Function
    private int binarySearch(int[][] arr, int target, int excludeIndex) {
        int left = 0;
        int right = arr.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            // Exclude the element at excludeIndex
            if (mid == excludeIndex) {
                if (mid + 1 <= right && arr[mid + 1][0] == target) {
                    return mid + 1;
                } else if (mid - 1 >= left && arr[mid - 1][0] == target) {
                    return mid - 1;
                } else {
                    return -1; // Target found at the excluded index
                }
            }

            if (arr[mid][0] == target) {
                return mid;
            } else if (arr[mid][0] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        TwoSum solution = new TwoSum();
        int[] nums = {2, 7, 11, 15};
        int target = 9;

        // Example Usage of each approach
        System.out.println("Input: nums = " + Arrays.toString(nums) + ", target = " + target);

        System.out.println("Brute Force: " + Arrays.toString(solution.twoSumBruteForce(nums, target))); // Output: [0, 1]
        System.out.println("HashMap Two-Pass: " + Arrays.toString(solution.twoSumHashMapTwoPass(nums, target))); // Output: [0, 1]
        System.out.println("HashMap One-Pass: " + Arrays.toString(solution.twoSumHashMapOnePass(nums, target))); // Output: [0, 1]

        int[] sortedNums = {2, 7, 11, 15}; // Already sorted for the two-pointer and binary search approaches
        System.out.println("Two Pointers: " + Arrays.toString(solution.twoSumTwoPointers(sortedNums, target))); // Output: [0, 1]
        System.out.println("Binary Search: " + Arrays.toString(solution.twoSumBinarySearch(sortedNums, target)));
    }
}
