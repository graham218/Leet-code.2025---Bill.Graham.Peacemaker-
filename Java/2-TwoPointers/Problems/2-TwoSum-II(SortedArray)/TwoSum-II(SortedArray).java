import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class TwoSumII {

    /**
     * Two Sum II - Input array is sorted
     *
     * Given a 1-indexed array of integers numbers sorted in non-decreasing order,
     * find two numbers such that they add up to a specific target number.
     * Let these two numbers be numbers[index1] and numbers[index2] where
     * 1 <= index1 < index2 <= numbers.length.
     *
     * Return the indices of the two numbers, index1 and index2,
     * added by one as an integer array [index1, index2] of length 2.
     *
     * The tests are generated such that there is exactly one solution.
     * You may not use the same element twice.
     * You must use only constant extra space.
     *
     * Example 1:
     * Input: numbers = [2,7,11,15], target = 9
     * Output: [1,2]
     * Explanation: The sum of 2 and 7 is 9. index1 = 1, index2 = 2. We return [1, 2].
     *
     * Example 2:
     * Input: numbers = [2,3,4], target = 6
     * Output: [1,3]
     * Explanation: The sum of 2 and 4 is 6. index1 = 1, index2 = 3. We return [1, 3].
     *
     * Example 3:
     * Input: numbers = [-1,0], target = -1
     * Output: [1,2]
     * Explanation: The sum of -1 and 0 is -1. index1 = 1, index2 = 2. We return [1, 2].
     *
     * Constraints:
     * 2 <= numbers.length <= 3 * 10^4
     * -1000 <= numbers[i] <= 1000
     * numbers is sorted in non-decreasing order.
     * -1000 <= target <= 1000
     */

    public static void main(String[] args) {
        int[] numbers1 = {2, 7, 11, 15};
        int target1 = 9;
        System.out.println("Two Sum (Sorted Array) - Approach 1: Two Pointers: " + Arrays.toString(twoSumTwoPointers(numbers1, target1)));
        System.out.println("Two Sum (Sorted Array) - Approach 2: Binary Search: " + Arrays.toString(twoSumBinarySearch(numbers1, target1)));
        System.out.println("Two Sum (Sorted Array) - Approach 3: HashMap: " + Arrays.toString(twoSumHashMap(numbers1, target1)));
        int[] numbers2 = {2, 3, 4};
        int target2 = 6;
        System.out.println("Two Sum (Sorted Array) - Approach 4: Recursion: " + Arrays.toString(twoSumRecursive(numbers2, target2)));

        int[] numbers3 = {-1, 0};
        int target3 = -1;
        System.out.println("Two Sum (Sorted Array) - Approach 5: Using Java 8 Stream: " + Arrays.toString(twoSumStream(numbers3, target3)));
    }

    // Approach 1: Two Pointers
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    public static int[] twoSumTwoPointers(int[] numbers, int target) {
        int left = 0;
        int right = numbers.length - 1;

        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return new int[]{left + 1, right + 1}; // Add 1 to convert to 1-based indexing
            } else if (sum < target) {
                left++; // Move left pointer to increase the sum
            } else {
                right--; // Move right pointer to decrease the sum
            }
        }
        return new int[0]; // No solution found.  The problem guarantees a solution, so this line will not be reached.
    }

    // Approach 2: Binary Search
    // Time Complexity: O(n log n)
    // Space Complexity: O(1)
    public static int[] twoSumBinarySearch(int[] numbers, int target) {
        for (int i = 0; i < numbers.length; i++) {
            int complement = target - numbers[i];
            int complementIndex = binarySearch(numbers, complement, i + 1, numbers.length - 1); // Search in the remaining part of the array
            if (complementIndex != -1) {
                return new int[]{i + 1, complementIndex + 1}; // Add 1 to convert to 1-based indexing
            }
        }
        return new int[0]; // No solution found. The problem guarantees a solution, so this line will not be reached.
    }

    private static int binarySearch(int[] numbers, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2; // Prevent overflow
            if (numbers[mid] == target) {
                return mid;
            } else if (numbers[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1; // Target not found
    }

    // Approach 3: HashMap
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    public static int[] twoSumHashMap(int[] numbers, int target) {
        Map<Integer, Integer> numMap = new HashMap<>();
        for (int i = 0; i < numbers.length; i++) {
            int complement = target - numbers[i];
            if (numMap.containsKey(complement)) {
                return new int[]{numMap.get(complement) + 1, i + 1}; // Add 1 to convert to 1-based indexing
            }
            numMap.put(numbers[i], i);
        }
        return new int[0]; // No solution found.  The problem guarantees a solution, so this line will not be reached.
    }

    // Approach 4: Recursion (Less efficient, mainly for demonstration)
    // Time Complexity: O(n^2) in the worst case (due to the recursive calls)
    // Space Complexity: O(n) due to the call stack
    public static int[] twoSumRecursive(int[] numbers, int target) {
        return twoSumRecursiveHelper(numbers, target, 0, numbers.length - 1);
    }

    private static int[] twoSumRecursiveHelper(int[] numbers, int target, int left, int right) {
        if (left >= right) {
            return new int[0]; // Base case: No solution found
        }
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            return new int[]{left + 1, right + 1};
        } else if (sum < target) {
            return twoSumRecursiveHelper(numbers, target, left + 1, right); // Recursively search with increased left
        } else {
            return twoSumRecursiveHelper(numbers, target, left, right - 1); // Recursively search with decreased right
        }
    }

    // Approach 5: Using Java 8 Stream (Not the most efficient, but demonstrates Streams)
    // Time Complexity: O(n^2)  due to nested loop within the stream operation.
    // Space Complexity: O(n) in the worst case (for the list created by the stream)
    public static int[] twoSumStream(int[] numbers, int target) {
        return Arrays.stream(numbers)
                .boxed()
                .flatMap(i -> Arrays.stream(numbers)
                        .boxed()
                        .filter(j -> i != j && i + j == target) // Find pairs that sum to the target, exclude same element twice
                        .map(j -> new int[]{Arrays.asList(numbers).indexOf(i) + 1, Arrays.asList(numbers).indexOf(j) + 1}) // Map indices, add 1 for 1-based indexing
                )
                .findFirst() // Find the first matching pair
                .orElse(new int[0]);
    }
}

