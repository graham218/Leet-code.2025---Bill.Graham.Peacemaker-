import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class SingleNumber {

    /**
     * Given an array of integers, every element appears twice except for one. Find that single one.
     *
     * You must implement a solution with a linear runtime complexity and use only constant extra space.
     *
     * Example 1:
     * Input: nums = [2,2,1]
     * Output: 1
     *
     * Example 2:
     * Input: nums = [4,1,2,1,2]
     * Output: 4
     *
     * Example 3:
     * Input: nums = [1]
     * Output: 1
     *
     * Constraints:
     * 1 <= nums.length <= 3 * 10^4
     * -3 * 10^4 <= nums[i] <= 3 * 10^4
     */

    public static void main(String[] args) {
        int[] nums1 = {2, 2, 1};
        System.out.println("Single number (XOR): " + singleNumberXOR(nums1)); // Expected: 1
        System.out.println("Single number (HashMap): " + singleNumberHashMap(nums1)); // Expected: 1
        System.out.println("Single number (HashSet): " + singleNumberHashSet(nums1)); // Expected: 1
        System.out.println("Single number (Sum of Set minus Sum of Array): " + singleNumberSumSetMinusSumArray(nums1)); // Expected: 1
        System.out.println("Single number (Bit Manipulation): " + singleNumberBitManipulation(nums1));

        int[] nums2 = {4, 1, 2, 1, 2};
        System.out.println("Single number (XOR): " + singleNumberXOR(nums2)); // Expected: 4
        System.out.println("Single number (HashMap): " + singleNumberHashMap(nums2)); // Expected: 4
        System.out.println("Single number (HashSet): " + singleNumberHashSet(nums2)); // Expected: 4
        System.out.println("Single number (Sum of Set minus Sum of Array): " + singleNumberSumSetMinusSumArray(nums2)); // Expected: 4
        System.out.println("Single number (Bit Manipulation): " + singleNumberBitManipulation(nums2));
    }

    /**
     * Approach 1: XOR Operation
     *
     * The XOR operation has the property that a ^ a = 0 and a ^ 0 = a.
     * We can use this property to find the single number.
     * We initialize a variable result to 0, and then XOR every number in the array with result.
     * The numbers that appear twice will cancel each other out, and the single number will remain.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     *
     * This is the most efficient approach in terms of both time and space complexity,
     * and it's the most commonly used and recommended solution for this problem.
     * It directly addresses the problem's constraints of linear time complexity and constant space.
     * It's used in various applications, such as:
     * -  Finding unique IDs in datasets.
     * -  Error detection in data transmission.
     * -  Cryptography for simple encryption/decryption.
     */
    public static int singleNumberXOR(int[] nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }

    /**
     * Approach 2: HashMap
     *
     * We can use a HashMap to store the frequency of each number.
     * We iterate through the array, and for each number, we either add it to the map with a frequency of 1,
     * or increment its frequency if it's already in the map.
     * Then, we iterate through the map and return the number with a frequency of 1.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * This approach is less efficient than the XOR approach because it uses extra space to store the frequency map.
     * However, it's more flexible and can be used to find numbers that appear an odd number of times
     * when the other numbers appear an even number of times.
     * Real-world applications:
     * -  Counting occurrences of events in log files.
     * -  Analyzing survey data to find unique responses.
     * -  Implementing caching mechanisms.
     */
    public static int singleNumberHashMap(int[] nums) {
        Map<Integer, Integer> numFrequencies = new HashMap<>();
        for (int num : nums) {
            numFrequencies.put(num, numFrequencies.getOrDefault(num, 0) + 1);
        }
        for (Map.Entry<Integer, Integer> entry : numFrequencies.entrySet()) {
            if (entry.getValue() == 1) {
                return entry.getKey();
            }
        }
        throw new IllegalArgumentException("No single number found");
    }

    /**
     * Approach 3: HashSet
     *
     * We can use a HashSet to store the numbers we have seen.
     * We iterate through the array, and for each number, if it's not in the set, we add it.
     * If it's already in the set, we remove it.  At the end, the set will contain only the single number.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * This approach is also less efficient than the XOR approach as it uses extra space.
     * It's similar to the HashMap approach in terms of use cases but is slightly less verbose.
     * Applications include:
     * -  Detecting duplicate entries in databases.
     * -  Filtering unique elements from a stream of data.
     * -  Implementing simple set operations.
     */
    public static int singleNumberHashSet(int[] nums) {
        Set<Integer> seenNumbers = new HashSet<>();
        for (int num : nums) {
            if (!seenNumbers.add(num)) {
                seenNumbers.remove(num);
            }
        }
        return seenNumbers.iterator().next();
    }

    /**
     * Approach 4: Sum of Set minus Sum of Array
     *
     * We can use a HashSet to store the unique numbers in the array.
     * The sum of the unique numbers multiplied by 2, minus the sum of all the numbers in the array,
     * will give us the single number.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * This approach is less efficient than the XOR approach because it involves more arithmetic operations and uses extra space.
     * It's less intuitive than the other approaches.
     * This method is not commonly used due to its complexity and the potential for integer overflow
     * if the numbers in the array are large.
     * It's primarily an academic exercise to demonstrate alternative problem-solving techniques.
     */
    public static int singleNumberSumSetMinusSumArray(int[] nums) {
        Set<Integer> uniqueNumbers = new HashSet<>();
        int sumOfArray = 0;
        for (int num : nums) {
            uniqueNumbers.add(num);
            sumOfArray += num;
        }
        int sumOfUniqueNumbers = 0;
        for (int num : uniqueNumbers) {
            sumOfUniqueNumbers += num;
        }
        return 2 * sumOfUniqueNumbers - sumOfArray;
    }

    /**
     * Approach 5: Bit Manipulation
     *
     * This approach is very similar to Approach 1 (XOR).  It emphasizes the bitwise operations.
     * It iterates through the array and applies the XOR operation to each number with the result.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     *
     * This is essentially the same as the first approach, but it explicitly highlights the bit manipulation aspect.
     * It's highly efficient and the preferred method.
     */
    public static int singleNumberBitManipulation(int[] nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num; // XOR operation
        }
        return result;
    }
}

