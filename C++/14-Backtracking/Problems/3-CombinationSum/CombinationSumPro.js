/*
Combination Sum Problem:

Given an array of distinct integers `candidates` and a target integer `target`, return a list of all unique combinations of `candidates` where the chosen numbers sum to `target`. You may assume that the same number from `candidates` may be chosen an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

Example:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]

Constraints:
1 <= candidates.length <= 30
1 <= candidates[i] <= 200
All elements of candidates are distinct.
1 <= target <= 500
*/

/**
 * Approach 1: Basic Backtracking
 *
 * This is the most straightforward backtracking approach.  It explores all possible combinations
 * recursively, pruning branches when the current sum exceeds the target.
 *
 * Time Complexity: O(N^(T/M)), where N is the number of candidates, T is the target, and M is the minimum candidate.
 * Space Complexity: O(T/M) - maximum depth of the recursion tree.
 */
function combinationSum1(candidates, target) {
    const result = [];

    function backtrack(combination, remaining, start) {
        if (remaining === 0) {
            result.push([...combination]); // Found a valid combination, add a copy to the result
            return;
        }
        if (remaining < 0) {
            return; // Current combination exceeds the target, stop exploring
        }

        for (let i = start; i < candidates.length; i++) {
            combination.push(candidates[i]); // Include the current candidate
            backtrack(combination, remaining - candidates[i], i); // Explore further with the same candidate allowed
            combination.pop(); // Backtrack: remove the candidate to try others
        }
    }

    backtrack([], target, 0);
    return result;
}

/**
 * Approach 2: Backtracking with Optimization
 *
 * This approach adds a small optimization by sorting the candidates array. This allows us to
 * potentially prune branches earlier if the current candidate is already too large.
 *
 * Time Complexity: O(N^(T/M)), where N is the number of candidates, T is the target, and M is the minimum candidate.
 * Space Complexity: O(T/M)
 */
function combinationSum2(candidates, target) {
    const result = [];
    candidates.sort((a, b) => a - b); // Sort candidates to optimize

    function backtrack(combination, remaining, start) {
        if (remaining === 0) {
            result.push([...combination]);
            return;
        }
        if (remaining < 0) {
            return;
        }

        for (let i = start; i < candidates.length; i++) {
             // Optimization: If current candidate is too large, skip it and the rest (since sorted)
            if (candidates[i] > remaining) {
                break;
            }
            combination.push(candidates[i]);
            backtrack(combination, remaining - candidates[i], i);
            combination.pop();
        }
    }

    backtrack([], target, 0);
    return result;
}

/**
 * Approach 3: Backtracking with Memoization (for repeated targets) - Caching Combinations
 *
 * If the function is called multiple times with the same target, we can memoize the results
 * to avoid redundant computations. This approach stores the combinations for each target value.
 *
 * Time Complexity: O(N^(T/M)) in the worst case (first call), but subsequent calls with the same target are O(1).
 * Space Complexity: O(T * (T/M)) -  O(T) for the memo, and O(T/M) for the combinations stored.
 */
function combinationSum3(candidates, target, memo = new Map()) {
    if (memo.has(target)) {
        return memo.get(target); // Return memoized result if available
    }

    const result = [];

    function backtrack(combination, remaining, start) {
        if (remaining === 0) {
            result.push([...combination]);
            return;
        }
        if (remaining < 0) {
            return;
        }

        for (let i = start; i < candidates.length; i++) {
            combination.push(candidates[i]);
            backtrack(combination, remaining - candidates[i], i);
            combination.pop();
        }
    }

    backtrack([], target, 0);
    memo.set(target, result); // Store the result in the memo
    return result;
}

/**
 * Approach 4: Iterative Backtracking (using a stack)
 *
 * This approach uses a stack to simulate the recursion of the backtracking algorithm.  It can
 * be useful in environments with limited recursion depth, though often more complex to understand.
 *
 * Time Complexity: O(N^(T/M))
 * Space Complexity: O(T/M)
 */
function combinationSum4(candidates, target) {
    const result = [];
    const stack = [{ combination: [], remaining: target, start: 0 }]; // Store state: combination, remaining, start

    while (stack.length > 0) {
        const { combination, remaining, start } = stack.pop();

        if (remaining === 0) {
            result.push([...combination]);
            continue;
        }
        if (remaining < 0) {
            continue;
        }

        for (let i = start; i < candidates.length; i++) {
            stack.push({
                combination: [...combination, candidates[i]],
                remaining: remaining - candidates[i],
                start: i,
            });
        }
    }
    return result;
}

/**
 * Approach 5: Dynamic Programming (Tabulation) - When target is relatively small
 *
 * This approach uses dynamic programming to build up a table of all possible combinations for sums
 * from 0 to target.  It's generally suitable when the target value is not too large.
 *
 * Time Complexity: O(N * T), where N is the number of candidates and T is the target.
 * Space Complexity: O(T)
 */
function combinationSum5(candidates, target) {
    const dp = Array(target + 1).fill(null).map(() => []); // dp[i] stores combinations that sum to i
    dp[0] = [[]]; // Base case: sum of 0 has an empty combination

    for (let sum = 1; sum <= target; sum++) {
        for (const candidate of candidates) {
            if (sum - candidate >= 0) {
                const prevCombinations = dp[sum - candidate]; // Combinations for the remaining sum
                for (const combination of prevCombinations) {
                    dp[sum].push([...combination, candidate]); // Add current candidate to form new combination
                }
            }
        }
    }
    return dp[target];
}



// Example Usage and output using console.log
const candidates = [2, 3, 6, 7];
const target = 7;

console.log("Approach 1: Basic Backtracking");
console.log(combinationSum1(candidates, target)); // Output: [[2,2,3],[7]]

console.log("\nApproach 2: Backtracking with Optimization");
console.log(combinationSum2(candidates, target)); // Output: [[2,2,3],[7]]

console.log("\nApproach 3: Backtracking with Memoization");
console.log(combinationSum3(candidates, target)); // Output: [[2,2,3],[7]]

console.log("\nApproach 4: Iterative Backtracking");
console.log(combinationSum4(candidates, target)); // Output: [[2,2,3],[7]]

console.log("\nApproach 5: Dynamic Programming");
console.log(combinationSum5(candidates, target)); // Output: [[2,2,3],[7]]

// Example of using memoization (Approach 3) for repeated calls:
const candidates2 = [2, 3, 5];
const target1 = 8;
const target2 = 8;
const memo = new Map(); //  Use the same memo object across calls

console.log("\nApproach 3: Backtracking with Memoization - Example with repeated target");
console.log("First call with target 8:", combinationSum3(candidates2, target1, memo)); // Calculate and memoize
console.log("Second call with target 8 (should be faster):", combinationSum3(candidates2, target2, memo)); // Retrieve from memo
