import java.util.HashSet;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Set;

public class ContainsDuplicate {

    /**
     * Approach 1: Using HashSet
     *
     * Time Complexity: O(n), where n is the length of the input array.
     * Space Complexity: O(n), in the worst case, the HashSet might store all n elements.
     *
     * @param nums The input array of integers.
     * @return true if the array contains any duplicate element, false otherwise.
     */
    public boolean containsDuplicateUsingHashSet(int[] nums) {
        // Create a HashSet to store unique elements.
        HashSet<Integer> set = new HashSet<>();

        // Iterate through the array.
        for (int num : nums) {
            // If the element is already in the set, it's a duplicate.
            if (set.contains(num)) {
                return true;
            }
            // Otherwise, add the element to the set.
            set.add(num);
        }
        // If the loop finishes without finding a duplicate, return false.
        return false;
    }

    /**
     * Approach 2: Using Sorting
     *
     * Time Complexity: O(n log n), due to the sorting operation.
     * Space Complexity: O(1) for primitive types,  O(log n) for Object types in the best case and O(n) in the worst case
     *
     * @param nums The input array of integers.
     * @return true if the array contains any duplicate element, false otherwise.
     */
    public boolean containsDuplicateUsingSorting(int[] nums) {
        // Sort the array.  Duplicate elements will be adjacent after sorting.
        Arrays.sort(nums);

        // Iterate through the sorted array, comparing adjacent elements.
        for (int i = 0; i < nums.length - 1; i++) {
            // If two adjacent elements are equal, it's a duplicate.
            if (nums[i] == nums[i + 1]) {
                return true;
            }
        }
        // If the loop finishes without finding a duplicate, return false.
        return false;
    }

    /**
     * Approach 3: Using HashMap (Less Efficient for this specific problem, but showing the approach)
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * @param nums The input array of integers.
     * @return true if the array contains any duplicate element, false otherwise.
     */
    public boolean containsDuplicateUsingHashMap(int[] nums) {
        // Create a HashMap to store the frequency of each element.
        HashMap<Integer, Integer> map = new HashMap<>();

        // Iterate through the array.
        for (int num : nums) {
            // If the element is already in the map, increment its count.
            if (map.containsKey(num)) {
                map.put(num, map.get(num) + 1);
                return true; // Found a duplicate.
            } else {
                // Otherwise, add the element to the map with a count of 1.
                map.put(num, 1);
            }
        }
        // If the loop finishes without finding a duplicate, return false.
        return false;
    }

    /**
     * Approach 4: Using HashSet (Optimized - slight improvement in some cases)
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * @param nums The input array
     * @return true if the array contains duplicate, false otherwise
     */
    public boolean containsDuplicateUsingHashSetOptimized(int[] nums) {
        Set<Integer> seen = new HashSet<>();
        for (int num : nums) {
            if (!seen.add(num)) { // .add() returns false if the element was already in the set
                return true;
            }
        }
        return false;
    }

    /**
     * Approach 5: Using Nested Loop (Brute Force - Inefficient)
     *
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     *
     * @param nums The input array
     * @return true if the array contains duplicate, false otherwise
     */
    public boolean containsDuplicateUsingNestedLoop(int[] nums) {
        for (int i = 0; i < nums.length; i++) {
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }

    public static void main(String[] args) {
        ContainsDuplicate solution = new ContainsDuplicate();
        int[] nums1 = {1, 2, 3, 1};
        int[] nums2 = {1, 2, 3, 4};
        int[] nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};

        // Test cases for each approach
        System.out.println("Test Case 1: " + Arrays.toString(nums1));
        System.out.println("HashSet: " + solution.containsDuplicateUsingHashSet(nums1)); // true
        System.out.println("Sorting: " + solution.containsDuplicateUsingSorting(nums1));     // true
        System.out.println("HashMap: " + solution.containsDuplicateUsingHashMap(nums1));     // true
        System.out.println("HashSet Optimized: " + solution.containsDuplicateUsingHashSetOptimized(nums1)); // true
        System.out.println("Nested Loop: " + solution.containsDuplicateUsingNestedLoop(nums1)); // true


        System.out.println("\nTest Case 2: " + Arrays.toString(nums2));
        System.out.println("HashSet: " + solution.containsDuplicateUsingHashSet(nums2)); // false
        System.out.println("Sorting: " + solution.containsDuplicateUsingSorting(nums2));     // false
        System.out.println("HashMap: " + solution.containsDuplicateUsingHashMap(nums2));     // false
        System.out.println("HashSet Optimized: " + solution.containsDuplicateUsingHashSetOptimized(nums2)); // false
        System.out.println("Nested Loop: " + solution.containsDuplicateUsingNestedLoop(nums2)); // false

        System.out.println("\nTest Case 3: " + Arrays.toString(nums3));
        System.out.println("HashSet: " + solution.containsDuplicateUsingHashSet(nums3)); // true
        System.out.println("Sorting: " + solution.containsDuplicateUsingSorting(nums3));     // true
        System.out.println("HashMap: " + solution.containsDuplicateUsingHashMap(nums3));     // true
        System.out.println("HashSet Optimized: " + solution.containsDuplicateUsingHashSetOptimized(nums3)); // true
        System.out.println("Nested Loop: " + solution.containsDuplicateUsingNestedLoop(nums3)); // true
    }
}
