import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;
import java.util.stream.IntStream;

public class TwoSum {

    /**
     * Given an array of integers, find two numbers such that they add up to a specific target.
     *
     * The function should return an array of indices of the two numbers.
     *
     * Example:
     * Given nums = [2, 7, 11, 15], target = 9,
     * Return [0, 1].  (Because nums[0] + nums[1] = 2 + 7 = 9)
     *
     * Assumptions:
     * - Each input would have exactly one solution
     * - You may not use the same element twice.
     *
     *
     */

    /**
     * Approach 1: Brute Force
     *
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     *
     * Real-world application:
     * This approach is simple to understand and implement, making it suitable for small datasets
     * or when optimizing for code readability over performance.  For example, in a very
     * simple configuration check in a legacy system with a small number of parameters.
     */
    public int[] twoSumBruteForce(int[] nums, int target) {
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] + nums[j] == target) {
                    return new int[]{i, j};
                }
            }
        }
        // In a real application, you would handle the case where no solution is found.
        // Here, we throw an exception to indicate that no solution exists, as the problem
        // states there *is* always a solution.
        throw new IllegalArgumentException("No two sum solution found");
    }

    /**
     * Approach 2: Two-pass Hash Table
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * Real-world application:
     * Hash tables are incredibly useful for key-value lookups.  This approach could be used
     * in a system that needs to quickly find matching pairs of data, such as:
     * -  Finding matching records in a database based on the sum of two fields.
     * -  Identifying pairs of products whose prices add up to a specific value in an e-commerce system.
     */
    public int[] twoSumTwoPassHashTable(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            map.put(nums[i], i);
        }
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (map.containsKey(complement) && map.get(complement) != i) {
                return new int[]{i, map.get(complement)};
            }
        }
        throw new IllegalArgumentException("No two sum solution found");
    }

    /**
     * Approach 3: One-pass Hash Table
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * Real-world application:
     * This is an optimized version of the hash table approach.  It's very efficient for
     * applications where speed is critical, such as:
     * -  Real-time data processing.
     * -  High-frequency trading systems.
     * -  Network packet analysis.
     */
    public int[] twoSumOnePassHashTable(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (map.containsKey(complement)) {
                return new int[]{map.get(complement), i};
            }
            map.put(nums[i], i);
        }
        throw new IllegalArgumentException("No two sum solution found");
    }

    /**
     * Approach 4: Sorting and Two Pointers
     *
     * Time Complexity: O(n log n)  (due to sorting)
     * Space Complexity: O(1) or O(n) depending on the sorting algorithm.  Most in-place sorts are O(1),
     * but some, like merge sort, can be O(n).
     *
     * Real-world application:
     * This approach is useful when the input array can be modified, and when you need to find pairs
     * that satisfy a certain condition in a sorted array.  For example:
     * -  Finding pairs of transactions that sum to a specific amount in a financial system.
     * -  Identifying complementary items in an inventory management system.
     */
    public int[] twoSumTwoPointers(int[] nums, int target) {
        // Create a copy of the array to avoid modifying the original input.
        int[] numsCopy = Arrays.copyOf(nums, nums.length);
        Arrays.sort(numsCopy); // Sort the *copy*

        int left = 0;
        int right = numsCopy.length - 1;

        while (left < right) {
            int sum = numsCopy[left] + numsCopy[right];
            if (sum == target) {
                // Need to find the *original* indices in the unsorted array.
                int index1 = -1;
                int index2 = -1;
                for (int i = 0; i < nums.length; i++) {
                    if (nums[i] == numsCopy[left]) {
                        index1 = i;
                        break; // Found the first one, no need to keep looping for it.
                    }
                }
                for (int i = 0; i < nums.length; i++) {
                    if (nums[i] == numsCopy[right] && i != index1) { // Ensure we don't pick the same index.
                        index2 = i;
                        break;
                    }
                }
                // Handle the case where the same number is used twice.
                if (index1 != -1 && index2 != -1)
                    return new int[]{index1, index2};
                else
                    return new int[]{-1,-1}; //error
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        throw new IllegalArgumentException("No two sum solution found");
    }

    /**
     * Approach 5: Using Java 8 Streams
     *
     * Time Complexity: O(n^2) in the worst case, due to the nested loop within the filter.
     * It can be argued that it's closer to O(n) on average, but the nested loop
     * makes it potentially quadratic.
     * Space Complexity: O(n) -  The space used by the stream and the resulting array.
     *
     * Real-world application:
     * Useful in modern Java applications where you want to leverage functional programming
     * and the conciseness of streams.  However, for performance-critical sections,
     * the iterative approaches are generally preferred.  Good for:
     * -  Data processing pipelines where you're performing multiple transformations
     * and filtering operations.
     * -  Simplifying complex logic in business applications, as long as performance
     * is not the absolute top priority.
     */
    public int[] twoSumStreams(int[] nums, int target) {
        return IntStream.range(0, nums.length)
                .boxed()
                .flatMap(i -> IntStream.range(i + 1, nums.length) // Start from i+1 to avoid duplicates
                        .filter(j -> nums[i] + nums[j] == target)
                        .mapToObj(j -> new int[]{i, j}))
                .findFirst()
                .orElseThrow(() -> new IllegalArgumentException("No two sum solution found"));
    }

    public static void main(String[] args) {
        TwoSum solution = new TwoSum();
        int[] nums = {2, 7, 11, 15};
        int target = 9;

        System.out.println("Input: nums = " + Arrays.toString(nums) + ", target = " + target);

        // Brute Force
        int[] result1 = solution.twoSumBruteForce(nums, target);
        System.out.println("Two Sum (Brute Force): " + Arrays.toString(result1));

        // Two-pass Hash Table
        int[] result2 = solution.twoSumTwoPassHashTable(nums, target);
        System.out.println("Two Sum (Two-pass Hash Table): " + Arrays.toString(result2));

        // One-pass Hash Table
        int[] result3 = solution.twoSumOnePassHashTable(nums, target);
        System.out.println("Two Sum (One-pass Hash Table): " + Arrays.toString(result3));

        // Sorting and Two Pointers
        int[] result4 = solution.twoSumTwoPointers(nums, target);
        System.out.println("Two Sum (Sorting and Two Pointers): " + Arrays.toString(result4));

        // Java 8 Streams
        int[] result5 = solution.twoSumStreams(nums, target);
        System.out.println("Two Sum (Java 8 Streams): " + Arrays.toString(result5));
    }
}