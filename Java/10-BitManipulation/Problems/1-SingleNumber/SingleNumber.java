import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class SingleNumber {

    /**
     * Given a non-empty array of integers nums, every element appears twice except
     * for one. Find that single one.
     *
     * You must implement a solution with a linear runtime complexity and use
     * only constant extra space.
     *
     * Example 1:
     *
     * Input: nums = [2,2,1]
     * Output: 1
     *
     * Example 2:
     *
     * Input: nums = [4,1,2,1,2]
     * Output: 4
     *
     * Example 3:
     *
     * Input: nums = [1]
     * Output: 1
     *
     * Constraints:
     *
     * 1 <= nums.length <= 3 * 104
     * -3 * 104 <= nums[i] <= 3 * 104
     * Each element in nums appears twice except for one element which appears only once.
     */

    public static void main(String[] args) {
        int[] nums1 = {2, 2, 1};
        System.out.println("Single number (XOR): " + singleNumberXOR(nums1)); // Expected: 1
        System.out.println("Single number (HashMap): " + singleNumberHashMap(nums1)); // Expected: 1
        System.out.println("Single number (HashSet): " + singleNumberHashSet(nums1)); // Expected: 1
        System.out.println("Single number (Sum of Sets): " + singleNumberSumOfSets(nums1)); // Expected: 1
        System.out.println("Single number (Bitwise): " + singleNumberBitwise(nums1)); // Expected: 1


        int[] nums2 = {4, 1, 2, 1, 2};
        System.out.println("Single number (XOR): " + singleNumberXOR(nums2)); // Expected: 4
        System.out.println("Single number (HashMap): " + singleNumberHashMap(nums2)); // Expected: 4
        System.out.println("Single number (HashSet): " + singleNumberHashSet(nums2)); // Expected: 4
        System.out.println("Single number (Sum of Sets): " + singleNumberSumOfSets(nums2)); // Expected: 4
        System.out.println("Single number (Bitwise): " + singleNumberBitwise(nums2)); // Expected: 4

        int[] nums3 = {1};
        System.out.println("Single number (XOR): " + singleNumberXOR(nums3)); // Expected: 1
        System.out.println("Single number (HashMap): " + singleNumberHashMap(nums3)); // Expected: 1
        System.out.println("Single number (HashSet): " + singleNumberHashSet(nums3)); // Expected: 1
        System.out.println("Single number (Sum of Sets): " + singleNumberSumOfSets(nums3)); // Expected: 1
        System.out.println("Single number (Bitwise): " + singleNumberBitwise(nums3)); // Expected: 1
    }

    /**
     * Approach 1: XOR Operation
     *
     * The XOR operation has the property that a ^ a = 0 and a ^ 0 = a.
     * We can use this property to find the single number.  We initialize a
     * result variable to 0, and then XOR each number in the array with
     * the result.  Numbers that appear twice will cancel each other out,
     * and the single number will be left in the result.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    public static int singleNumberXOR(int[] nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }

    /**
     * Approach 2: Using HashMap
     *
     * Store each number and its count in a HashMap.
     * The number with a count of 1 is the single number.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static int singleNumberHashMap(int[] nums) {
        Map<Integer, Integer> numCounts = new HashMap<>();
        for (int num : nums) {
            numCounts.put(num, numCounts.getOrDefault(num, 0) + 1);
        }

        for (Map.Entry<Integer, Integer> entry : numCounts.entrySet()) {
            if (entry.getValue() == 1) {
                return entry.getKey();
            }
        }
        return -1; // Should not reach here, given the problem constraints.
    }

    /**
     * Approach 3: Using HashSet
     *
     * Iterate through the array.  If the number is already in the set,
     * remove it.  If it's not in the set, add it.  At the end, the set
     * will contain only the single number.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static int singleNumberHashSet(int[] nums) {
        Set<Integer> numSet = new HashSet<>();
        for (int num : nums) {
            if (numSet.contains(num)) {
                numSet.remove(num);
            } else {
                numSet.add(num);
            }
        }
        return numSet.iterator().next();
    }

    /**
     * Approach 4: Sum of Sets
     *
     * Calculate the sum of all numbers in the array.
     * Create a set of the unique numbers in the array.
     * Multiply the sum of the unique numbers by 2, and subtract the sum
     * of all the numbers in the array.  This will leave you with the
     * single number.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static int singleNumberSumOfSets(int[] nums) {
        Set<Integer> uniqueNums = new HashSet<>();
        int sumOfNums = 0;

        for (int num : nums) {
            uniqueNums.add(num);
            sumOfNums += num;
        }

        int sumOfUniqueNums = 0;
        for (int num : uniqueNums) {
            sumOfUniqueNums += num;
        }

        return 2 * sumOfUniqueNums - sumOfNums;
    }

    /**
     * Approach 5: Bitwise Operations
     *
     * This approach is very similar to Approach 1 (XOR).
     * It leverages the property that a ^ a = 0 and a ^ 0 = a.
     * The code iterates through the array, applying the XOR operation
     * to each element with an accumulator variable (result).  Duplicate
     * numbers cancel each other out, leaving only the single number.
     *
     * This method has the advantage of using constant extra space.
     *
     * Time Complexity: O(n) - Linear time complexity, as it iterates through the array once.
     * Space Complexity: O(1) - Constant space complexity, as it only uses a single integer variable.
     */
    public static int singleNumberBitwise(int[] nums) {
        int result = 0; // Initialize the result to 0
        for (int num : nums) {
            result ^= num; // Apply XOR operation to each number
        }
        return result; // Return the final result
    }
}

