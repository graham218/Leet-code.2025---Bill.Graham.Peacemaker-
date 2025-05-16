import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

public class Subsets {

    public static void main(String[] args) {
        int[] nums = {1, 2, 3};
        System.out.println("Input: nums = " + Arrays.toString(nums));

        System.out.println("\nApproach 1: Iterative Approach");
        List<List<Integer>> subsets1 = findSubsetsIterative(nums);
        System.out.println("Output: " + subsets1);

        System.out.println("\nApproach 2: Recursive Backtracking");
        List<List<Integer>> subsets2 = findSubsetsRecursive(nums);
        System.out.println("Output: " + subsets2);

        System.out.println("\nApproach 3: Backtracking with Concise Code");
        List<List<Integer>> subsets3 = findSubsetsConcise(nums);
        System.out.println("Output: " + subsets3);

        System.out.println("\nApproach 4: Using Bit Manipulation");
        List<List<Integer>> subsets4 = findSubsetsBitManipulation(nums);
        System.out.println("Output: " + subsets4);

        System.out.println("\nApproach 5: Cascading Approach");
        List<List<Integer>> subsets5 = findSubsetsCascading(nums);
        System.out.println("Output: " + subsets5);
    }

    // Approach 1: Iterative Approach
    // Time Complexity: O(N * 2^N), where N is the number of elements in nums.
    // Space Complexity: O(2^N) to store all the subsets.
    public static List<List<Integer>> findSubsetsIterative(int[] nums) {
        List<List<Integer>> subsets = new ArrayList<>();
        subsets.add(new ArrayList<>()); // Start with the empty subset

        for (int num : nums) {
            int n = subsets.size();
            for (int i = 0; i < n; i++) {
                // Create a new subset by adding the current number to each existing subset.
                List<Integer> currentSubset = new ArrayList<>(subsets.get(i));
                currentSubset.add(num);
                subsets.add(currentSubset);
            }
        }
        return subsets;
    }

    // Approach 2: Recursive Backtracking
    // Time Complexity: O(N * 2^N)
    // Space Complexity: O(N) for the depth of the recursion stack, and O(2^N) for the output.
    public static List<List<Integer>> findSubsetsRecursive(int[] nums) {
        List<List<Integer>> subsets = new ArrayList<>();
        List<Integer> currentSubset = new ArrayList<>();
        backtrack(nums, 0, currentSubset, subsets);
        return subsets;
    }

    private static void backtrack(int[] nums, int index, List<Integer> currentSubset, List<List<Integer>> subsets) {
        // Base case: Add the current subset to the result.
        subsets.add(new ArrayList<>(currentSubset));

        // Recursive step:
        for (int i = index; i < nums.length; i++) {
            // Include the current number in the subset.
            currentSubset.add(nums[i]);
            // Recurse to generate subsets with the next numbers.
            backtrack(nums, i + 1, currentSubset, subsets);
            // Backtrack: Remove the current number to explore other possibilities.
            currentSubset.remove(currentSubset.size() - 1);
        }
    }

    // Approach 3: Backtracking with Concise Code
    // Time Complexity: O(N * 2^N)
    // Space Complexity: O(N) for the recursion stack, O(2^N) for the result.
    public static List<List<Integer>> findSubsetsConcise(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrackConcise(nums, 0, new ArrayList<>(), result);
        return result;
    }

    private static void backtrackConcise(int[] nums, int start, List<Integer> currentList, List<List<Integer>> result) {
        result.add(new ArrayList<>(currentList)); // Add current subset (including empty)
        for (int i = start; i < nums.length; i++) {
            currentList.add(nums[i]);
            backtrackConcise(nums, i + 1, currentList, result);
            currentList.remove(currentList.size() - 1);
        }
    }

    // Approach 4: Bit Manipulation
    // Time Complexity: O(N * 2^N)
    // Space Complexity: O(2^N)
    public static List<List<Integer>> findSubsetsBitManipulation(int[] nums) {
        List<List<Integer>> subsets = new ArrayList<>();
        int n = nums.length;
        // Iterate through all possible bitmasks (0 to 2^n - 1).
        for (int i = 0; i < (1 << n); i++) {
            List<Integer> subset = new ArrayList<>();
            // Check each bit of the mask to determine if the corresponding number should be included.
            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) > 0) { // Check if the j-th bit is set
                    subset.add(nums[j]);
                }
            }
            subsets.add(subset);
        }
        return subsets;
    }

    // Approach 5: Cascading Approach
    // Time Complexity: O(N * 2^N)
    // Space Complexity: O(2^N)
    public static List<List<Integer>> findSubsetsCascading(int[] nums) {
        List<List<Integer>> subsets = new ArrayList<>();
        subsets.add(new ArrayList<>()); // Start with an empty set

        for (int num : nums) {
            int n = subsets.size();
            for (int j = 0; j < n; j++) {
                List<Integer> currentSubset = new ArrayList<>(subsets.get(j));
                currentSubset.add(num);
                subsets.add(currentSubset);
            }
        }
        return subsets;
    }
}

