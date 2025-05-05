import java.util.HashSet;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Set;

public class ContainsDuplicate {

    public static void main(String[] args) {
        int[] nums1 = {1, 2, 3, 1};
        int[] nums2 = {1, 2, 3, 4};
        int[] nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
        int[] nums4 = {1, 2, 3, 4, 5};
        int[] nums5 = {1, 2, 3, 1, 5};


        // Example Usage of each method
        System.out.println("Method 1 (HashSet): nums1 contains duplicate: " + containsDuplicateUsingHashSet(nums1)); // true
        System.out.println("Method 1 (HashSet): nums2 contains duplicate: " + containsDuplicateUsingHashSet(nums2)); // false

        System.out.println("Method 2 (Sorting): nums1 contains duplicate: " + containsDuplicateUsingSorting(nums1)); // true
        System.out.println("Method 2 (Sorting): nums2 contains duplicate: " + containsDuplicateUsingSorting(nums2)); // false

        System.out.println("Method 3 (HashMap): nums1 contains duplicate: " + containsDuplicateUsingHashMap(nums1)); // true
        System.out.println("Method 3 (HashMap): nums2 contains duplicate: " + containsDuplicateUsingHashMap(nums2)); // false

        System.out.println("Method 4 (Using Set Interface): nums3 contains duplicate: " + containsDuplicateUsingSetInterface(nums3)); //true
        System.out.println("Method 4 (Using Set Interface): nums4 contains duplicate: " + containsDuplicateUsingSetInterface(nums4)); //false

        System.out.println("Method 5 (Optimized HashSet): nums5 contains duplicate: " + containsDuplicateOptimized(nums5)); // true
        System.out.println("Method 5 (Optimized HashSet): nums2 contains duplicate: " + containsDuplicateOptimized(nums2)); // false
    }

    // Method 1: Using HashSet
    // Time Complexity: O(n), Space Complexity: O(n)
    // Real-world application: Detecting duplicate entries in a database or user input validation.
    public static boolean containsDuplicateUsingHashSet(int[] nums) {
        Set<Integer> set = new HashSet<>();
        for (int num : nums) {
            if (set.contains(num)) {
                return true; // Found a duplicate
            }
            set.add(num); // Add the number to the set
        }
        return false; // No duplicates found
    }

    // Method 2: Using Sorting
    // Time Complexity: O(n log n), Space Complexity: O(1) (for in-place sorting)
    // Real-world application: Useful when the input array is already sorted or sorting is required for other purposes.
    public static boolean containsDuplicateUsingSorting(int[] nums) {
        if (nums == null || nums.length <= 1) {
            return false; // No duplicates possible with 0 or 1 elements
        }
        Arrays.sort(nums); // Sort the array in place
        for (int i = 0; i < nums.length - 1; i++) {
            if (nums[i] == nums[i + 1]) {
                return true; // Found adjacent duplicates after sorting
            }
        }
        return false;
    }

    // Method 3: Using HashMap
    // Time Complexity: O(n), Space Complexity: O(n)
    // Real-world application: Counting frequency of elements to find duplicates,  useful in data analysis.
    public static boolean containsDuplicateUsingHashMap(int[] nums) {
        HashMap<Integer, Integer> map = new HashMap<>();
        for (int num : nums) {
            if (map.containsKey(num)) {
                return true; // Duplicate found
            }
            map.put(num, 1); // Add number to map
        }
        return false;
    }

    // Method 4: Using Set Interface (more generic)
    // Time Complexity: O(n), Space Complexity: O(n)
    // Real-world application:  Demonstrates using the Set interface.  HashSet is a common implementation, but this approach
    //                        could be used with other Set implementations if needed.
    public static boolean containsDuplicateUsingSetInterface(int[] nums) {
        Set<Integer> numberSet = Set.of(); // Start with empty, immutable set
        numberSet = new HashSet<>(); //Re-assign to a mutable HashSet
        for (int num : nums) {
            if (numberSet.contains(num)) {
                return true;
            }
            numberSet.add(num);
        }
        return false;
    }

    // Method 5: Optimized HashSet (Slightly more efficient)
    // Time Complexity: O(n), Space Complexity: O(n)
    // Real-world application:  Slightly optimized version of the HashSet approach.
    public static boolean containsDuplicateOptimized(int[] nums) {
        HashSet<Integer> set = new HashSet<>(nums.length); // Pre-allocate space for potential elements.
        for (int num : nums) {
            if (!set.add(num)) { // set.add() returns false if the element already exists
                return true;
            }
        }
        return false;
    }
}

