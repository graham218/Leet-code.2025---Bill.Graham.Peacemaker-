import java.util.HashMap;
import java.util.Map;

public class TwoSumII {

    /**
     * Two Sum II - Sorted Array:
     *
     * Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order,
     * find two numbers such that they add up to a specific target number. Let these two numbers be
     * numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
     *
     * Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
     *
     * The tests are generated such that there is exactly one solution. You may not use the same element twice.
     *
     *
     * Example 1:
     *
     * Input: numbers = [2,7,11,15], target = 9
     * Output: [1,2]
     * Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
     *
     * Example 2:
     *
     * Input: numbers = [2,3,4], target = 6
     * Output: [1,3]
     * Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].
     *
     * Example 3:
     *
     * Input: numbers = [-1,0], target = -1
     * Output: [1,2]
     * Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].
     *
     *
     * Constraints:
     *
     * 2 <= numbers.length <= 3 * 10^4
     * -1000 <= numbers[i] <= 1000
     * numbers is sorted in non-decreasing order.
     * -1000 <= target <= 1000
     * The tests are generated such that there is exactly one solution.
     *
     */

    /**
     * Approach 1: Two Pointers (Optimal)
     *
     * This is the most efficient approach, leveraging the sorted nature of the input array.
     * We initialize two pointers, one at the beginning (left) and one at the end (right) of the array.
     * We then move these pointers based on whether the sum of the elements they point to is less than,
     * equal to, or greater than the target.
     *
     * Time Complexity: O(n), where n is the length of the array.
     * Space Complexity: O(1), constant extra space.
     *
     * Real-world application:
     * -  Finding pairs of items in a sorted list that meet a specific condition, such as
     * finding two products whose prices add up to a given budget in an e-commerce application.
     *
     * @param numbers The sorted input array of integers.
     * @param target The target sum.
     * @return An array containing the 1-based indices of the two numbers that add up to the target.
     */
    public int[] twoSum_TwoPointers(int[] numbers, int target) {
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

        // The problem states there is exactly one solution, so this return should never be reached.
        return new int[]{-1, -1};
    }


    /**
     * Approach 2: Binary Search
     *
     * For each element in the array, we can use binary search to find the complement
     * (the number needed to reach the target) in the remaining part of the array.
     *
     * Time Complexity: O(n log n), where n is the length of the array.  We iterate through the array once (O(n)),
     * and perform a binary search (O(log n)) for each element.
     * Space Complexity: O(1), constant extra space.
     *
     * Real-world application:
     * -  Looking for matching records in a sorted database table, where one column is the target
     * and another column is used to find the complement.
     *
     * @param numbers The sorted input array of integers.
     * @param target The target sum.
     * @return An array containing the 1-based indices of the two numbers that add up to the target.
     */
    public int[] twoSum_BinarySearch(int[] numbers, int target) {
        for (int i = 0; i < numbers.length; i++) {
            int complement = target - numbers[i];
            int complementIndex = binarySearch(numbers, complement, i + 1, numbers.length - 1); // Search in the rest of the array
            if (complementIndex != -1) {
                return new int[]{i + 1, complementIndex + 1}; // Add 1 to convert to 1-based indexing
            }
        }

        // The problem states there is exactly one solution, so this return should never be reached.
        return new int[]{-1, -1};
    }

    /**
     * Helper function to perform binary search in a sorted array.
     *
     * @param numbers The sorted array to search in.
     * @param target The target value to find.
     * @param left The left boundary of the search range.
     * @param right The right boundary of the search range.
     * @return The index of the target value if found, otherwise -1.
     */
    private int binarySearch(int[] numbers, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2; // Prevent potential overflow
            if (numbers[mid] == target) {
                return mid;
            } else if (numbers[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }


    /**
     * Approach 3: HashMap (Hash Table)
     *
     * This approach uses a hash map to store each number and its index.  For each number,
     * we check if its complement (target - number) is already in the map.  If it is,
     * we have found our pair.  This approach does NOT take advantage of the sorted property
     * of the input array.
     *
     * Time Complexity: O(n), where n is the length of the array.  Average case for hash map
     * operations (put and get) is O(1).
     * Space Complexity: O(n), in the worst case, we might store all n elements in the hash map.
     *
     * Real-world application:
     * -  Finding matching records based on a specific value, such as identifying users with
     * complementary preferences in a recommendation system.  Though a sorted array is not
     * usually the initial data structure in this case.
     *
     * @param numbers The sorted input array of integers.
     * @param target The target sum.
     * @return An array containing the 1-based indices of the two numbers that add up to the target.
     */
    public int[] twoSum_HashMap(int[] numbers, int target) {
        Map<Integer, Integer> numMap = new HashMap<>();
        for (int i = 0; i < numbers.length; i++) {
            int complement = target - numbers[i];
            if (numMap.containsKey(complement)) {
                return new int[]{numMap.get(complement) + 1, i + 1}; // Add 1 to convert to 1-based indexing
            }
            numMap.put(numbers[i], i);
        }

        // The problem states there is exactly one solution, so this return should never be reached.
        return new int[]{-1, -1};
    }

    /**
     * Approach 4: Brute Force
     *
     * This is the most straightforward but least efficient approach.  We use two nested loops
     * to check every possible pair of numbers in the array to see if they add up to the target.
     *
     * Time Complexity: O(n^2), where n is the length of the array.  We have two nested loops, each
     * iterating up to n times.
     * Space Complexity: O(1), constant extra space.
     *
     * Real-world application:
     * -  While not ideal, this approach can be used for small datasets or as a baseline for
     * comparing the performance of more optimized algorithms.  For example, a very small
     * configuration check in a system with limited resources.
     *
     * @param numbers The sorted input array of integers.
     * @param target The target sum.
     * @return An array containing the 1-based indices of the two numbers that add up to the target.
     */
    public int[] twoSum_BruteForce(int[] numbers, int target) {
        for (int i = 0; i < numbers.length; i++) {
            for (int j = i + 1; j < numbers.length; j++) {
                if (numbers[i] + numbers[j] == target) {
                    return new int[]{i + 1, j + 1}; // Add 1 to convert to 1-based indexing
                }
            }
        }

        // The problem states there is exactly one solution, so this return should never be reached.
        return new int[]{-1, -1};
    }

    /**
     * Approach 5: Recursive Binary Search
     *
     * This approach uses recursion with binary search.  It's similar to Approach 2, but
     * the binary search is implemented recursively. For each element, we recursively
     * search for its complement in the rest of the array.
     *
     * Time Complexity: O(n log n), where n is the length of the array.  We iterate through the array once (O(n)),
     * and perform a binary search (O(log n)) for each element.
     * Space Complexity: O(log n), due to the recursive call stack of the binary search.
     *
     * Real-world application:
     * -  This approach demonstrates a recursive solution for binary search, which can be useful
     * in scenarios where a recursive approach is preferred for code clarity or specific
     * architectural reasons (e.g., certain functional programming paradigms).
     *
     * @param numbers The sorted input array of integers.
     * @param target The target sum.
     * @return An array containing the 1-based indices of the two numbers that add up to the target.
     */
    public int[] twoSum_RecursiveBinarySearch(int[] numbers, int target) {
        for (int i = 0; i < numbers.length; i++) {
            int complement = target - numbers[i];
            int complementIndex = recursiveBinarySearch(numbers, complement, i + 1, numbers.length - 1);
            if (complementIndex != -1) {
                return new int[]{i + 1, complementIndex + 1}; // Add 1 to convert to 1-based indexing
            }
        }

        // The problem states there is exactly one solution, so this return should never be reached.
        return new int[]{-1, -1};
    }

    /**
     * Recursive helper function to perform binary search.
     *
     * @param numbers The sorted array to search in.
     * @param target The target value to find.
     * @param left The left boundary of the search range.
     * @param right The right boundary of the search range.
     * @return The index of the target value if found, otherwise -1.
     */
    private int recursiveBinarySearch(int[] numbers, int target, int left, int right) {
        if (left > right) {
            return -1;
        }
        int mid = left + (right - left) / 2;
        if (numbers[mid] == target) {
            return mid;
        } else if (numbers[mid] < target) {
            return recursiveBinarySearch(numbers, target, mid + 1, right);
        } else {
            return recursiveBinarySearch(numbers, target, left, mid - 1);
        }
    }


    public static void main(String[] args) {
        TwoSumII solution = new TwoSumII();

        // Example 1
        int[] numbers1 = {2, 7, 11, 15};
        int target1 = 9;
        int[] result1 = solution.twoSum_TwoPointers(numbers1, target1);
        System.out.println("Example 1 (Two Pointers): [" + result1[0] + ", " + result1[1] + "]"); // Output: [1, 2]
        result1 = solution.twoSum_BinarySearch(numbers1, target1);
        System.out.println("Example 1 (Binary Search): [" + result1[0] + ", " + result1[1] + "]");
        result1 = solution.twoSum_HashMap(numbers1, target1);
        System.out.println("Example 1 (HashMap): [" + result1[0] + ", " + result1[1] + "]");
        result1 = solution.twoSum_BruteForce(numbers1, target1);
        System.out.println("Example 1 (Brute Force): [" + result1[0] + ", " + result1[1] + "]");
        result1 = solution.twoSum_RecursiveBinarySearch(numbers1, target1);
        System.out.println("Example 1 (Recursive Binary Search): [" + result1[0] + ", " + result1[1] + "]");


        // Example 2
        int[] numbers2 = {2, 3, 4};
        int target2 = 6;
        int[] result2 = solution.twoSum_TwoPointers(numbers2, target2);
        System.out.println("Example 2 (Two Pointers): [" + result2[0] + ", " + result2[1] + "]"); // Output: [1, 3]
        result2 = solution.twoSum_BinarySearch(numbers2, target2);
        System.out.println("Example 2 (Binary Search): [" + result2[0] + ", " + result2[1] + "]");
        result2 = solution.twoSum_HashMap(numbers2, target2);
        System.out.println("Example 2 (HashMap): [" + result2[0] + ", " + result2[1] + "]");
        result2 = solution.twoSum_BruteForce(numbers2, target2);
        System.out.println("Example 2 (Brute Force): [" + result2[0] + ", " + result2[1] + "]");
        result2 = solution.twoSum_RecursiveBinarySearch(numbers2, target2);
        System.out.println("Example 2 (Recursive Binary Search): [" + result2[0] + ", " + result2[1] + "]");

        // Example 3
        int[] numbers3 = {-1, 0};
        int target3 = -1;
        int[] result3 = solution.twoSum_TwoPointers(numbers3, target3);
        System.out.println("Example 3 (Two Pointers): [" + result3[0] + ", " + result3[1] + "]"); // Output: [1, 2]
        result3 = solution.twoSum_BinarySearch(numbers3, target3);
        System.out.println("Example 3 (Binary Search): [" + result3[0] + ", " + result3[1] + "]");
        result3 = solution.twoSum_HashMap(numbers3, target3);
        System.out.println("Example 3 (HashMap): [" + result3[0] + ", " + result3[1] + "]");
        result3 = solution.twoSum_BruteForce(numbers3, target3);
        System.out.println("Example 3 (Brute Force): [" + result3[0] + ", " + result3[1] + "]");
        result3 = solution.twoSum_RecursiveBinarySearch(numbers3, target3);
        System.out.println("Example 3 (Recursive Binary Search): [" + result3[0] + ", " + result3[1] + "]");
    }
}

