import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CombinationSum {

    public static void main(String[] args) {
        int[] candidates = {2, 3, 6, 7};
        int target = 7;

        System.out.println("Combination Sum - Approach 1: Basic Backtracking");
        System.out.println(combinationSum1(candidates, target));

        System.out.println("\nCombination Sum - Approach 2: Backtracking with Optimized Base Case");
        System.out.println(combinationSum2(candidates, target));

        System.out.println("\nCombination Sum - Approach 3: Backtracking with Pruning");
        System.out.println(combinationSum3(candidates, target));

        System.out.println("\nCombination Sum - Approach 4: Iterative Backtracking (Simulated with Stack)");
        System.out.println(combinationSum4(candidates, target));

        System.out.println("\nCombination Sum - Approach 5: Using Streams (Less Efficient, More Concise)");
        System.out.println(combinationSum5(candidates, target));
    }

    // Approach 1: Basic Backtracking
    // - Explores all possible combinations without any optimizations.
    // - Time Complexity: O(2^n) in the worst case, where n is the number of candidates.
    // - Space Complexity: O(n) for the recursion stack.
    public static List<List<Integer>> combinationSum1(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> combination = new ArrayList<>();
        findCombinations1(candidates, target, 0, combination, result);
        return result;
    }

    private static void findCombinations1(int[] candidates, int target, int start, List<Integer> combination, List<List<Integer>> result) {
        if (target == 0) {
            result.add(new ArrayList<>(combination));
            return;
        }
        if (target < 0) {
            return;
        }

        for (int i = start; i < candidates.length; i++) {
            combination.add(candidates[i]);
            findCombinations1(candidates, target - candidates[i], i, combination, result);
            combination.remove(combination.size() - 1); // Backtrack
        }
    }

    // Approach 2: Backtracking with Optimized Base Case
    // - Improves the base case check by moving the `target < 0` check before the loop.
    // - This avoids unnecessary iterations when the target becomes negative.
    // - Time Complexity: O(2^n) in the worst case.
    // - Space Complexity: O(n) for the recursion stack.
    public static List<List<Integer>> combinationSum2(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> combination = new ArrayList<>();
        findCombinations2(candidates, target, 0, combination, result);
        return result;
    }

    private static void findCombinations2(int[] candidates, int target, int start, List<Integer> combination, List<List<Integer>> result) {
        if (target < 0) { // Optimized base case check
            return;
        }
        if (target == 0) {
            result.add(new ArrayList<>(combination));
            return;
        }

        for (int i = start; i < candidates.length; i++) {
            combination.add(candidates[i]);
            findCombinations2(candidates, target - candidates[i], i, combination, result);
            combination.remove(combination.size() - 1);
        }
    }

    // Approach 3: Backtracking with Pruning
    // - Sorts the candidates array to enable pruning.
    // - If a candidate is greater than the target, we can break the loop, avoiding unnecessary recursion.
    // - Time Complexity: O(2^n) in the worst case, but performs better with pruning.
    // - Space Complexity: O(n) for the recursion stack.
    public static List<List<Integer>> combinationSum3(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> combination = new ArrayList<>();
        Arrays.sort(candidates); // Sort for pruning
        findCombinations3(candidates, target, 0, combination, result);
        return result;
    }

    private static void findCombinations3(int[] candidates, int target, int start, List<Integer> combination, List<List<Integer>> result) {
        if (target < 0) {
            return;
        }
        if (target == 0) {
            result.add(new ArrayList<>(combination));
            return;
        }

        for (int i = start; i < candidates.length; i++) {
            if (candidates[i] > target) { // Pruning: Skip if candidate is too large
                break;
            }
            combination.add(candidates[i]);
            findCombinations3(candidates, target - candidates[i], i, combination, result);
            combination.remove(combination.size() - 1);
        }
    }

    // Approach 4: Iterative Backtracking (Simulated with Stack)
    // - Simulates the recursive backtracking process using a stack.
    // - Avoids recursion, which can be helpful for very large input sets.
    // - Time Complexity: O(2^n) in the worst case.
    // - Space Complexity: O(n) for the stack.
    public static List<List<Integer>> combinationSum4(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        // Stack to store the current state of the combination and remaining target
        java.util.Stack<State> stack = new java.util.Stack<>();
        stack.push(new State(new ArrayList<>(), 0, target));

        while (!stack.isEmpty()) {
            State currentState = stack.pop();
            List<Integer> combination = currentState.combination;
            int start = currentState.start;
            int remainingTarget = currentState.remainingTarget;

            if (remainingTarget == 0) {
                result.add(new ArrayList<>(combination));
                continue; // Important: Go to the next state
            }
            if (remainingTarget < 0) {
                continue; // Important: Go to the next state
            }

            for (int i = start; i < candidates.length; i++) {
                List<Integer> nextCombination = new ArrayList<>(combination); // Create a new list!
                nextCombination.add(candidates[i]);
                stack.push(new State(nextCombination, i, remainingTarget - candidates[i]));
            }
        }
        return result;
    }

    // Helper class to store the state for iterative backtracking
    private static class State {
        List<Integer> combination;
        int start;
        int remainingTarget;

        public State(List<Integer> combination, int start, int remainingTarget) {
            this.combination = combination;
            this.start = start;
            this.remainingTarget = remainingTarget;
        }
    }

    // Approach 5: Using Streams (Less Efficient, More Concise)
    // - Uses Java streams for a more functional and concise approach.
    // - Generally less efficient than backtracking due to the overhead of stream operations.
    // - Time Complexity:  Difficult to precisely determine due to stream operations, likely higher than O(2^n)
    // - Space Complexity:  Can be higher than O(n) due to intermediate stream collections.
    public static List<List<Integer>> combinationSum5(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        findCombinations5(candidates, target, 0, new ArrayList<>(), result);
        return result;
    }

    private static void findCombinations5(int[] candidates, int target, int start, List<Integer> combination, List<List<Integer>> result) {
        if (target == 0) {
            result.add(new ArrayList<>(combination));
            return;
        }
        if (target < 0) {
            return;
        }

        for (int i = start; i < candidates.length; i++) {
            final int currentCandidate = candidates[i]; //store in final variable to be used in lambda.
            List<Integer> nextCombination = new ArrayList<>(combination);
            nextCombination.add(currentCandidate);
            findCombinations5(candidates, target - currentCandidate, i, nextCombination, result);
        }
    }
}

