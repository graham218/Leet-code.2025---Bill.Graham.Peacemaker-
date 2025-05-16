import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CombinationSum {

    public static void main(String[] args) {
        int[] candidates = {2, 3, 6, 7};
        int target = 7;

        // Approach 1: Basic Backtracking
        System.out.println("Approach 1: Basic Backtracking");
        List<List<Integer>> result1 = combinationSum1(candidates, target);
        printResult(result1);

        // Approach 2: Backtracking with Optimization (Sorting)
        System.out.println("\nApproach 2: Backtracking with Optimization (Sorting)");
        List<List<Integer>> result2 = combinationSum2(candidates, target);
        printResult(result2);

        // Approach 3: Backtracking with Memoization (for distinct combinations - not directly applicable here but shown for concept)
        System.out.println("\nApproach 3: Backtracking with Memoization (Concept - Not directly applicable to original problem, but shown for variation)");
        //  The original problem allows duplicates, so pure memoization doesn't help *directly* with the original problem's output, but it's useful for *counting* distinct combinations.  We'd need a different problem statement (no duplicates allowed in a single combination) to see memoization's full benefit in *returning lists*.  This version shows how memoization *could* be used if the problem were modified to avoid duplicate combinations.
        List<List<Integer>> result3 = combinationSum3(candidates, target);
        printResult(result3);

        // Approach 4: Iterative Approach using a Stack (Simulated Recursion)
        System.out.println("\nApproach 4: Iterative Approach using a Stack (Simulated Recursion)");
        List<List<Integer>> result4 = combinationSum4(candidates, target);
        printResult(result4);

        // Approach 5: Dynamic Programming (Counting Combinations - Variation)
        System.out.println("\nApproach 5: Dynamic Programming (Counting Combinations - Variation)");
        int count = combinationSum5(candidates, target);
        System.out.println("Number of combinations: " + count); // Prints an integer, not a list of lists.
        //  Note:  DP is most natural for *counting* combinations, *not* for generating the lists of combinations when duplicates are allowed.  If the problem were to ask *how many* unique combinations sum to the target, DP would be very efficient.  For the original problem (returning lists with duplicates), backtracking is generally preferred.
    }

    // Helper method to print the result
    private static void printResult(List<List<Integer>> result) {
        for (List<Integer> combination : result) {
            System.out.println(combination);
        }
    }

    // Approach 1: Basic Backtracking
    // Time Complexity: O(2^n) in the worst case, where n is the number of candidates.
    // Space Complexity: O(n) for the depth of the recursion tree.
    public static List<List<Integer>> combinationSum1(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> currentCombination = new ArrayList<>();
        findCombinations1(candidates, target, 0, currentCombination, result);
        return result;
    }

    private static void findCombinations1(int[] candidates, int target, int start, List<Integer> currentCombination, List<List<Integer>> result) {
        if (target == 0) {
            result.add(new ArrayList<>(currentCombination));
            return;
        }
        if (target < 0) {
            return;
        }
        for (int i = start; i < candidates.length; i++) {
            currentCombination.add(candidates[i]);
            findCombinations1(candidates, target - candidates[i], i, currentCombination, result);
            currentCombination.remove(currentCombination.size() - 1);
        }
    }

    // Approach 2: Backtracking with Optimization (Sorting)
    // Time Complexity: O(2^n) in the worst case, but often faster than Approach 1 due to pruning.
    // Space Complexity: O(n) for the depth of the recursion tree.
    public static List<List<Integer>> combinationSum2(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> currentCombination = new ArrayList<>();
        Arrays.sort(candidates); // Sort the candidates to optimize (prune unnecessary branches)
        findCombinations2(candidates, target, 0, currentCombination, result);
        return result;
    }

    private static void findCombinations2(int[] candidates, int target, int start, List<Integer> currentCombination, List<List<Integer>> result) {
        if (target == 0) {
            result.add(new ArrayList<>(currentCombination));
            return;
        }
        if (target < 0) {
            return;
        }
        for (int i = start; i < candidates.length; i++) {
            if (target - candidates[i] < 0) { // Optimization: If current candidate is too large, skip it and the rest (since sorted)
                break;
            }
            currentCombination.add(candidates[i]);
            findCombinations2(candidates, target - candidates[i], i, currentCombination, result);
            currentCombination.remove(currentCombination.size() - 1);
        }
    }

    // Approach 3: Backtracking with Memoization (for distinct combinations - CONCEPTUAL EXAMPLE)
    // Time Complexity:  O(n * target)  if we were counting *distinct* combinations (with the problem modified).
    // Space Complexity: O(n * target)
    // IMPORTANT:  This approach is shown for the *concept* of memoization.  For the *original* Combination Sum problem (where the same number can be used multiple times), this memoization does NOT directly apply to reduce the number of *lists* returned.  It's more applicable to a variation where you want to count the number of *distinct* combinations.  To make this code directly usable for a variation of Combination Sum, you would need to change the problem statement (e.g., each number can be used at most once in a combination)
    public static List<List<Integer>> combinationSum3(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> currentCombination = new ArrayList<>();
        //  The memoization table stores boolean values, indicating if a certain target can be reached
        //  from a certain starting index.  It's not storing the lists of combinations themselves
        //  in this example, because with duplicates allowed, the lists aren't "distinct" enough
        //  to memoize effectively for the original problem.
        boolean[][] memo = new boolean[candidates.length + 1][target + 1];
        findCombinations3(candidates, target, 0, currentCombination, result, memo);
        return result;
    }

    private static void findCombinations3(int[] candidates, int target, int start, List<Integer> currentCombination, List<List<Integer>> result, boolean[][] memo) {
        if (target == 0) {
            result.add(new ArrayList<>(currentCombination));
            return;
        }
        if (target < 0) {
            return;
        }
        if (memo[start][target]) { // Check memoization table
            return;
        }

        for (int i = start; i < candidates.length; i++) {
            currentCombination.add(candidates[i]);
            findCombinations3(candidates, target - candidates[i], i, currentCombination, result, memo);
            currentCombination.remove(currentCombination.size() - 1);
        }
        memo[start][target] = true; // Store the result in the memoization table
    }

    // Approach 4: Iterative Approach using a Stack (Simulated Recursion)
    // Time Complexity:  Similar to the recursive approaches, O(2^n) in the worst case.
    // Space Complexity: O(n) for the stack.
    public static List<List<Integer>> combinationSum4(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        Arrays.sort(candidates); // Important for optimization
        // Stack to simulate the recursion
        java.util.Stack<State> stack = new java.util.Stack<>();
        stack.push(new State(0, new ArrayList<>(), target));

        while (!stack.isEmpty()) {
            State currentState = stack.pop();
            int start = currentState.start;
            List<Integer> currentCombination = currentState.combination;
            int currentTarget = currentState.target;

            if (currentTarget == 0) {
                result.add(new ArrayList<>(currentCombination));
                continue;
            }
            if (currentTarget < 0) {
                continue;
            }

            for (int i = start; i < candidates.length; i++) {
                if (currentTarget - candidates[i] < 0) {
                    break; // Optimization from sorted input
                }
                List<Integer> nextCombination = new ArrayList<>(currentCombination);
                nextCombination.add(candidates[i]);
                stack.push(new State(i, nextCombination, currentTarget - candidates[i]));
            }
        }
        return result;
    }

    // Helper class for the stack in the iterative approach
    private static class State {
        int start;
        List<Integer> combination;
        int target;

        public State(int start, List<Integer> combination, int target) {
            this.start = start;
            this.combination = combination;
            this.target = target;
        }
    }

    // Approach 5: Dynamic Programming (Counting Combinations - Variation)
    // Time Complexity: O(n * target), where n is the number of candidates.
    // Space Complexity: O(target)
    // IMPORTANT: This approach solves a *variation* of the problem: counting the *number* of combinations,
    // NOT generating the combinations themselves, and it's most suitable when you want to count
    // distinct combinations.  For the original problem (generating lists with duplicates), backtracking is better.
    public static int combinationSum5(int[] candidates, int target) {
        int[] dp = new int[target + 1];
        dp[0] = 1; // Base case: there is one way to make a sum of 0 (empty combination)

        for (int candidate : candidates) {
            for (int i = candidate; i <= target; i++) {
                dp[i] += dp[i - candidate];
            }
        }
        return dp[target];
    }
}

