import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.Collections; // Import the Collections class

public class ThreeSum {

    /**
     * Approach 1: Brute Force
     * - Time Complexity: O(n^3)
     * - Space Complexity: O(1) (not considering the output list)
     *
     * @param nums The input array of integers.
     * @return A list of unique triplets that sum to zero.
     */
    public List<List<Integer>> threeSumBruteForce(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        Set<List<Integer>> resultSet = new HashSet<>(); // Use a set to avoid duplicate triplets

        // Iterate through all possible combinations of three numbers
        for (int i = 0; i < nums.length - 2; i++) {
            for (int j = i + 1; j < nums.length - 1; j++) {
                for (int k = j + 1; k < nums.length; k++) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        // Create a list to represent the triplet
                        List<Integer> triplet = Arrays.asList(nums[i], nums[j], nums[k]);
                        // Sort the triplet to ensure uniqueness in the set
                        Collections.sort(triplet);
                        resultSet.add(triplet); // Add the sorted triplet to the set
                    }
                }
            }
        }
        result.addAll(resultSet); //convert set to list
        return result;
    }

    /**
     * Approach 2: Using HashMap
     * - Time Complexity: O(n^2)
     * - Space Complexity: O(n)
     *
     * @param nums The input array of integers.
     * @return A list of unique triplets that sum to zero.
     */
    public List<List<Integer>> threeSumHashMap(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        Set<List<Integer>> resultSet = new HashSet<>(); // Use a set to avoid duplicate triplets
        // Iterate through the array
        for (int i = 0; i < nums.length - 1; i++) {
            // Create a HashMap to store the numbers encountered so far
            Set<Integer> seen = new HashSet<>();
            for (int j = i + 1; j < nums.length; j++) {
                // Calculate the complement needed to make the sum zero
                int complement = -nums[i] - nums[j];
                // If the complement is found in the HashMap, we have found a triplet
                if (seen.contains(complement)) {
                    List<Integer> triplet = Arrays.asList(nums[i], nums[j], complement);
                    Collections.sort(triplet);
                    resultSet.add(triplet);
                } else {
                    // Add the current number to the HashMap
                    seen.add(nums[j]);
                }
            }
        }
        result.addAll(resultSet);
        return result;
    }

    /**
     * Approach 3: Sorting and Two Pointers
     * - Time Complexity: O(n^2)
     * - Space Complexity: O(1) (not considering the output list)
     *
     * @param nums The input array of integers.
     * @return A list of unique triplets that sum to zero.
     */
    public List<List<Integer>> threeSumTwoPointers(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        // If the array is null or has less than 3 elements, return an empty list.
        if (nums == null || nums.length < 3) {
            return result;
        }

        // Sort the array to easily use the two-pointer approach and avoid duplicate triplets
        Arrays.sort(nums);

        // Iterate through the array.  Fix one number at a time.
        for (int i = 0; i < nums.length - 2; i++) {
            // Skip duplicate numbers for the first element in the triplet
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            // Initialize the two pointers: left and right
            int left = i + 1;
            int right = nums.length - 1;

            // Move the two pointers towards each other
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    // Found a triplet that sums to zero
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));

                    // Skip duplicate numbers for the second element in the triplet
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    // Skip duplicate numbers for the third element in the triplet
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }

                    // Move the pointers to find other possible triplets
                    left++;
                    right--;
                } else if (sum < 0) {
                    // If the sum is less than zero, move the left pointer to increase the sum
                    left++;
                } else {
                    // If the sum is greater than zero, move the right pointer to decrease the sum
                    right--;
                }
            }
        }
        return result;
    }

    /**
     * Approach 4: Optimized Two Pointers with Early Exit
     * - Time Complexity: O(n^2)
     * - Space Complexity: O(1)
     * This approach adds an optimization to exit early if the smallest
     * possible sum is greater than 0 or the largest possible sum is less than 0.
     */
    public List<List<Integer>> threeSumOptimized(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        if (nums == null || nums.length < 3)
            return result;

        Arrays.sort(nums);

        // Optimization: Early exit if the smallest possible sum is greater than 0
        if (nums[0] + nums[1] + nums[2] > 0)
            return result;

        // Optimization: Early exit if the largest possible sum is less than 0
        if (nums[nums.length - 1] + nums[nums.length - 2] + nums[nums.length - 3] < 0)
            return result;

        for (int i = 0; i < nums.length - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int left = i + 1, right = nums.length - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));
                    while (left < right && nums[left] == nums[left + 1])
                        left++;
                    while (left < right && nums[right] == nums[right - 1])
                        right--;
                    left++;
                    right--;
                } else if (sum < 0)
                    left++;
                else
                    right--;
            }
        }
        return result;
    }

    /**
     * Approach 5: Using HashSet and Two Pointers
     * - Time Complexity: O(n^2)
     * - Space Complexity: O(n)
     * This approach uses a HashSet to store the triplets, ensuring uniqueness
     */
    public List<List<Integer>> threeSumHashSet(int[] nums) {
        Set<List<Integer>> result = new HashSet<>(); // Use a HashSet directly
        if (nums == null || nums.length < 3)
            return new ArrayList<>(result);

        Arrays.sort(nums);

        for (int i = 0; i < nums.length - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int left = i + 1, right = nums.length - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    result.add(Arrays.asList(nums[i], nums[left], nums[right])); // HashSet adds only unique
                    left++;
                    right--;
                } else if (sum < 0)
                    left++;
                else
                    right--;
            }
        }
        return new ArrayList<>(result); // Convert the set to a list
    }

    public static void main(String[] args) {
        ThreeSum solution = new ThreeSum();
        int[] nums = {-1, 0, 1, 2, -1, -4};

        System.out.println("Input: " + Arrays.toString(nums));

        // Test Approach 1: Brute Force
        List<List<Integer>> result1 = solution.threeSumBruteForce(nums);
        System.out.println("Brute Force: " + result1);

        // Test Approach 2: Using HashMap
        List<List<Integer>> result2 = solution.threeSumHashMap(nums);
        System.out.println("HashMap: " + result2);

        // Test Approach 3: Sorting and Two Pointers
        List<List<Integer>> result3 = solution.threeSumTwoPointers(nums);
        System.out.println("Two Pointers: " + result3);

        // Test Approach 4: Optimized Two Pointers
        List<List<Integer>> result4 = solution.threeSumOptimized(nums);
        System.out.println("Optimized Two Pointers: " + result4);

        // Test Approach 5: Using HashSet
        List<List<Integer>> result5 = solution.threeSumHashSet(nums);
        System.out.println("HashSet and Two Pointers: " + result5);
    }
}

