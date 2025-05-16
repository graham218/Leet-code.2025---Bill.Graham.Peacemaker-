import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Permutations {

    public static void main(String[] args) {
        int[] nums = {1, 2, 3};
        System.out.println("Input: " + Arrays.toString(nums));

        System.out.println("\nApproach 1: Backtracking with Swapping");
        List<List<Integer>> result1 = generatePermutations1(nums);
        System.out.println(result1);

        System.out.println("\nApproach 2: Backtracking with Visited Array");
        List<List<Integer>> result2 = generatePermutations2(nums);
        System.out.println(result2);

        System.out.println("\nApproach 3: Using Collections.swap()");
        List<List<Integer>> result3 = generatePermutations3(nums);
        System.out.println(result3);

        System.out.println("\nApproach 4: Iterative Approach");
        List<List<Integer>> result4 = generatePermutations4(nums);
        System.out.println(result4);

        System.out.println("\nApproach 5: Using a helper function with index");
        List<List<Integer>> result5 = generatePermutations5(nums);
        System.out.println(result5);
    }

    // Approach 1: Backtracking with Swapping
    // Time Complexity: O(n!), Space Complexity: O(n) for recursion depth
    public static List<List<Integer>> generatePermutations1(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        permute1(nums, 0, result);
        return result;
    }

    private static void permute1(int[] nums, int start, List<List<Integer>> result) {
        if (start == nums.length) {
            // Base case: when start reaches the end of the array, we have a complete permutation
            List<Integer> permutation = new ArrayList<>();
            for (int num : nums) {
                permutation.add(num);
            }
            result.add(permutation);
            return;
        }

        for (int i = start; i < nums.length; i++) {
            // Try swapping the current element with all the elements to its right
            swap(nums, start, i);
            // Recursively generate permutations for the remaining elements
            permute1(nums, start + 1, result);
            // Backtrack: swap the elements back to restore the original order
            swap(nums, start, i);
        }
    }

    private static void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    // Approach 2: Backtracking with Visited Array
    // Time Complexity: O(n!), Space Complexity: O(n) for visited array and recursion depth
    public static List<List<Integer>> generatePermutations2(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        boolean[] visited = new boolean[nums.length];
        List<Integer> currentPermutation = new ArrayList<>();
        permute2(nums, visited, currentPermutation, result);
        return result;
    }

    private static void permute2(int[] nums, boolean[] visited, List<Integer> currentPermutation, List<List<Integer>> result) {
        if (currentPermutation.size() == nums.length) {
            // Base case: when the current permutation has all the elements
            result.add(new ArrayList<>(currentPermutation)); // Add a *copy* of the current permutation
            return;
        }

        for (int i = 0; i < nums.length; i++) {
            if (!visited[i]) {
                // If the element at index i is not visited
                visited[i] = true; // Mark it as visited
                currentPermutation.add(nums[i]); // Add it to the current permutation
                permute2(nums, visited, currentPermutation, result); // Recurse
                currentPermutation.remove(currentPermutation.size() - 1); // Backtrack: remove the element
                visited[i] = false; // Mark it as not visited
            }
        }
    }

    // Approach 3: Using Collections.swap()
    // Time Complexity: O(n!), Space Complexity: O(n)
    public static List<List<Integer>> generatePermutations3(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> list = new ArrayList<>();
        for (int num : nums) {
            list.add(num);
        }
        permute3(list, 0, result);
        return result;
    }

    private static void permute3(List<Integer> list, int start, List<List<Integer>> result) {
        if (start == list.size()) {
            result.add(new ArrayList<>(list));
            return;
        }
        for (int i = start; i < list.size(); i++) {
            java.util.Collections.swap(list, start, i);
            permute3(list, start + 1, result);
            java.util.Collections.swap(list, start, i);
        }
    }

    // Approach 4: Iterative Approach (Less common, but included for completeness)
    // Time Complexity: O(n!), Space Complexity: O(n!) -  more space intensive
    public static List<List<Integer>> generatePermutations4(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        if (nums == null || nums.length == 0) {
            return result;
        }

        result.add(new ArrayList<>()); // Start with an empty list
        for (int num : nums) {
            List<List<Integer>> temp = new ArrayList<>();
            for (List<Integer> prevPermutation : result) {
                for (int i = 0; i <= prevPermutation.size(); i++) {
                    List<Integer> currentPermutation = new ArrayList<>(prevPermutation);
                    currentPermutation.add(i, num); // Insert the new number at every possible position
                    temp.add(currentPermutation);
                }
            }
            result = temp;
        }
        return result;
    }

    // Approach 5: Using a helper function with index.  Similar to approach 1, but structured slightly differently.
    public static List<List<Integer>> generatePermutations5(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        permute5(nums, 0, result);
        return result;
    }

    private static void permute5(int[] nums, int index, List<List<Integer>> result) {
        if (index == nums.length) {
            List<Integer> current = new ArrayList<>();
            for (int num : nums) {
                current.add(num);
            }
            result.add(current);
            return;
        }

        for (int i = index; i < nums.length; i++) {
            swap(nums, index, i);
            permute5(nums, index + 1, result);
            swap(nums, index, i); // backtrack
        }
    }
}

