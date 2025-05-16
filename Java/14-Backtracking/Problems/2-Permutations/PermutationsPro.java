import java.util.*;

public class Permutations {

    public static void main(String[] args) {
        int[] nums = {1, 2, 3};
        System.out.println("Input: " + Arrays.toString(nums));

        System.out.println("\nApproach 1: Backtracking with Swapping (Classic)");
        List<List<Integer>> permutations1 = generatePermutations1(nums);
        System.out.println(permutations1);

        System.out.println("\nApproach 2: Backtracking with Visited Array");
        List<List<Integer>> permutations2 = generatePermutations2(nums);
        System.out.println(permutations2);

        System.out.println("\nApproach 3: Using Collections.swap()");
        List<List<Integer>> permutations3 = generatePermutations3(nums);
        System.out.println(permutations3);

        System.out.println("\nApproach 4: Iterative Approach using Insertion");
        List<List<Integer>> permutations4 = generatePermutations4(nums);
        System.out.println(permutations4);

        System.out.println("\nApproach 5: Using a Library Function (for comparison and demonstration)");
        List<List<Integer>> permutations5 = generatePermutations5(nums);
        System.out.println(permutations5);
    }

    // Approach 1: Backtracking with Swapping (Classic)
    // This is the most common and intuitive backtracking approach.  It works by
    // fixing elements one by one and recursively generating permutations for the
    // remaining elements.  The key idea is to swap elements to explore different
    // arrangements and then backtrack to restore the original order.
    //
    // Real-world application:
    // -  Password generation:  Generating all possible password combinations.
    // -  Solving combinatorial problems:  Like finding all possible arrangements
    //    in a scheduling or resource allocation problem.
    public static List<List<Integer>> generatePermutations1(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        permute1(nums, 0, result);
        return result;
    }

    private static void permute1(int[] nums, int start, List<List<Integer>> result) {
        if (start == nums.length) {
            // Base case: When we have fixed all elements, add the current permutation to the result.
            List<Integer> permutation = new ArrayList<>();
            for (int num : nums) {
                permutation.add(num);
            }
            result.add(permutation);
            return;
        }

        for (int i = start; i < nums.length; i++) {
            // Explore all possible choices for the current position (start).
            swap(nums, start, i);            // Try placing the element at index i at the 'start' position.
            permute1(nums, start + 1, result); // Recursively generate permutations for the remaining elements.
            swap(nums, start, i);            // Backtrack: Restore the original order to explore other possibilities.
        }
    }

    private static void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }


    // Approach 2: Backtracking with Visited Array
    // This approach uses a boolean array to keep track of which elements have been
    // included in the current permutation.  It avoids swapping by explicitly
    // building the permutation step by step.
    //
    // Real-world application:
    // -  Generating unique IDs:  Ensuring that each ID is generated only once.
    // -  Solving puzzles:  Where you need to keep track of which options have
    //    already been tried (e.g., Sudoku).
    public static List<List<Integer>> generatePermutations2(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        boolean[] visited = new boolean[nums.length]; // Keep track of which numbers are used.
        List<Integer> currentPermutation = new ArrayList<>();
        permute2(nums, visited, currentPermutation, result);
        return result;
    }

    private static void permute2(int[] nums, boolean[] visited, List<Integer> currentPermutation, List<List<Integer>> result) {
        if (currentPermutation.size() == nums.length) {
            // Base case:  A complete permutation is formed.
            result.add(new ArrayList<>(currentPermutation)); // Add a *copy* of the permutation.
            return;
        }

        for (int i = 0; i < nums.length; i++) {
            if (!visited[i]) {
                // If the number hasn't been used yet
                visited[i] = true;             // Mark it as used
                currentPermutation.add(nums[i]); // Add it to the current permutation
                permute2(nums, visited, currentPermutation, result); // Recurse
                currentPermutation.remove(currentPermutation.size() - 1); // Backtrack: Remove the number
                visited[i] = false;            // Mark it as unused
            }
        }
    }

    // Approach 3: Using Collections.swap()
    // This approach is similar to the first one (swapping) but uses the
    // Collections.swap() method for swapping, which can be slightly more concise.
    //
    // Real-world application:
    //   -  Shuffling algorithms:  Implementing card shuffling or randomizing lists.
    //   -  Any application where you need to rearrange elements in a list.
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
            Collections.swap(list, start, i);
            permute3(list, start + 1, result);
            Collections.swap(list, start, i); // Backtrack
        }
    }

    // Approach 4: Iterative Approach using Insertion
    // This approach builds permutations iteratively.  It starts with the first
    // element and then inserts each subsequent element into all possible
    // positions of the previously generated permutations.  This is a non-recursive
    // approach.
    //
    // Real-world application:
    // -  String manipulation:  Generating all possible variations of a string.
    // -  Building search indexes:  Creating different combinations of keywords.
    public static List<List<Integer>> generatePermutations4(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        if (nums == null || nums.length == 0) {
            return result;
        }

        result.add(new ArrayList<>(Arrays.asList(nums[0]))); // Start with the first element.

        for (int i = 1; i < nums.length; i++) {
            List<List<Integer>> newResult = new ArrayList<>();
            for (List<Integer> prevPermutation : result) {
                for (int j = 0; j <= prevPermutation.size(); j++) {
                    // Insert the current number (nums[i]) at every possible position.
                    List<Integer> temp = new ArrayList<>(prevPermutation);
                    temp.add(j, nums[i]);  // Insert at index j
                    newResult.add(temp);
                }
            }
            result = newResult; // Update the result with the new permutations.
        }
        return result;
    }

    // Approach 5: Using a Library Function (for comparison and demonstration)
    // Java's Collections framework doesn't have a direct method for generating
    // permutations of an int array.  For demonstration, if you were working with
    // a List, you could adapt a library-based approach.  Guava library has
    // `Collections2.permutations()`, but here, for illustration with standard Java,
    // we show how you'd adapt the array to a List and use a conceptual approach.
    //
    // Real-world application:
    // -  Quick prototyping:  Rapidly generating permutations for testing or
    //    exploration when a library function is available.  For example, in test automation.
    public static List<List<Integer>> generatePermutations5(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> list = new ArrayList<>();
        for (int num : nums) {
            list.add(num);
        }

        // In real application, if you are allowed to use external library,
        // you can use Collections2.permutations(list) from Guava.
        // Here we are implementing the basic logic.
        permute5(list, 0, result);
        return result;
    }

    private static void permute5(List<Integer> list, int start, List<List<Integer>> result) {
        if (start == list.size()) {
            result.add(new ArrayList<>(list));
            return;
        }
        for (int i = start; i < list.size(); i++) {
            Collections.swap(list, start, i);
            permute5(list, start + 1, result);
            Collections.swap(list, start, i); // Backtrack
        }
    }
}

