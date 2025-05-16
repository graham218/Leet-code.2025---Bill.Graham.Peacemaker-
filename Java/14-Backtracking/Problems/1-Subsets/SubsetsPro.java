import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Subsets {

    public static void main(String[] args) {
        int[] nums = {1, 2, 3};
        System.out.println("Input: " + Arrays.toString(nums));

        // Approach 1: Iterative Approach
        List<List<Integer>> subsets1 = findSubsetsIterative(nums);
        System.out.println("\nApproach 1: Iterative Approach");
        System.out.println(subsets1);

        // Approach 2: Recursive Backtracking
        List<List<Integer>> subsets2 = findSubsetsRecursive(nums);
        System.out.println("\nApproach 2: Recursive Backtracking");
        System.out.println(subsets2);

        // Approach 3: Backtracking with Index
        List<List<Integer>> subsets3 = findSubsetsBacktrack(nums);
        System.out.println("\nApproach 3: Backtracking with Index");
        System.out.println(subsets3);

        // Approach 4: Using Bit Manipulation
        List<List<Integer>> subsets4 = findSubsetsBitManipulation(nums);
        System.out.println("\nApproach 4: Bit Manipulation");
        System.out.println(subsets4);

        // Approach 5: Combinations Approach
        List<List<Integer>> subsets5 = findSubsetsCombinations(nums);
        System.out.println("\nApproach 5: Combinations Approach");
        System.out.println(subsets5);
    }

    // Approach 1: Iterative Approach
    // Real-world application: Generating all possible feature combinations for machine learning model training.
    // Explanation: This approach iteratively builds subsets.  It starts with an empty set.
    // For each number in the input array, it adds the number to all existing subsets, creating new subsets.
    public static List<List<Integer>> findSubsetsIterative(int[] nums) {
        List<List<Integer>> subsets = new ArrayList<>();
        subsets.add(new ArrayList<>()); // Start with the empty subset

        for (int num : nums) {
            int n = subsets.size();
            for (int j = 0; j < n; j++) {
                List<Integer> currentSubset = new ArrayList<>(subsets.get(j)); // Important: Copy the subset
                currentSubset.add(num);
                subsets.add(currentSubset);
            }
        }
        return subsets;
    }

    // Approach 2: Recursive Backtracking
    // Real-world application: Generating all possible configurations in a decision-making process, such as in an AI agent.
    // Explanation: This approach uses recursion to explore all possible paths.  At each step, it has two choices:
    // include the current number in the subset, or exclude it.  The recursion continues until all numbers have been considered.
    public static List<List<Integer>> findSubsetsRecursive(int[] nums) {
        List<List<Integer>> subsets = new ArrayList<>();
        generateSubsetsRecursive(nums, 0, new ArrayList<>(), subsets);
        return subsets;
    }

    private static void generateSubsetsRecursive(int[] nums, int index, List<Integer> currentSubset, List<List<Integer>> subsets) {
        if (index == nums.length) {
            subsets.add(new ArrayList<>(currentSubset)); // Add a *copy* of the subset
            return;
        }

        // Include the current number
        currentSubset.add(nums[index]);
        generateSubsetsRecursive(nums, index + 1, currentSubset, subsets);

        // Exclude the current number (backtrack)
        currentSubset.remove(currentSubset.size() - 1);
        generateSubsetsRecursive(nums, index + 1, currentSubset, subsets);
    }

    // Approach 3: Backtracking with Index
    // Real-world application: Generating combinations for test case generation in software testing.
    // Explanation: Similar to the recursive approach, but uses a helper function with an index to track progress.
    // This is a more common way to implement backtracking for subset generation.
    public static List<List<Integer>> findSubsetsBacktrack(int[] nums) {
        List<List<Integer>> subsets = new ArrayList<>();
        backtrack(nums, 0, new ArrayList<>(), subsets);
        return subsets;
    }

    private static void backtrack(int[] nums, int start, List<Integer> currentSubset, List<List<Integer>> subsets) {
        subsets.add(new ArrayList<>(currentSubset)); // Add the current subset (which may be empty)

        for (int i = start; i < nums.length; i++) {
            currentSubset.add(nums[i]);       // Include the current number
            backtrack(nums, i + 1, currentSubset, subsets); // Recurse with the next number
            currentSubset.remove(currentSubset.size() - 1); // Backtrack: remove the current number
        }
    }

    // Approach 4: Using Bit Manipulation
    // Real-world application: Feature selection in machine learning, where each bit represents the presence or absence of a feature.
    // Explanation:  This approach uses bit manipulation to represent each subset.
    // If the j-th bit is set in the i-th number (from 0 to 2^n - 1), then the j-th element of the input array is included in the subset.
    // Example: For nums = [1, 2, 3], if i = 3 (binary 011), the subset is [2, 3].
    public static List<List<Integer>> findSubsetsBitManipulation(int[] nums) {
        List<List<Integer>> subsets = new ArrayList<>();
        int n = nums.length;
        int totalSubsets = 1 << n; // 2^n

        for (int i = 0; i < totalSubsets; i++) {
            List<Integer> subset = new ArrayList<>();
            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) != 0) { // Check if the j-th bit is set
                    subset.add(nums[j]);
                }
            }
            subsets.add(subset);
        }
        return subsets;
    }

    // Approach 5: Combinations Approach
    // Real-world application: Generating combinations for sampling or A/B testing scenarios.
    // Explanation: This approach generates subsets by first generating combinations of size k, for k = 0 to n.
    // For example, if nums is [1,2,3], it will generate [], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3].
    public static List<List<Integer>> findSubsetsCombinations(int[] nums) {
        List<List<Integer>> subsets = new ArrayList<>();
        for (int k = 0; k <= nums.length; k++) {
            generateCombinations(nums, k, 0, new ArrayList<>(), subsets);
        }
        return subsets;
    }

    private static void generateCombinations(int[] nums, int k, int start, List<Integer> currentCombination, List<List<Integer>> subsets) {
        if (currentCombination.size() == k) {
            subsets.add(new ArrayList<>(currentCombination));
            return;
        }
        for (int i = start; i < nums.length; i++) {
            currentCombination.add(nums[i]);
            generateCombinations(nums, k, i + 1, currentCombination, subsets);
            currentCombination.remove(currentCombination.size() - 1);
        }
    }
}

