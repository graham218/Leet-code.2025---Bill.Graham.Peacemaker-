/**
 * Five different approaches to solve the Combination Sum problem using backtracking in JavaScript.
 *
 * Problem:
 * Given an array of distinct integers `candidates` and a target integer `target`,
 * return a list of all unique combinations of `candidates` where the chosen numbers sum to `target`.
 * You may assume that the same number can be chosen from `candidates` an unlimited number of times.
 * Two combinations are unique if the frequency of at least one of the chosen numbers is different.
 *
 * Example:
 * Input: candidates = [2,3,6,7], target = 7
 * Output: [[2,2,3],[7]]
 */

/**
 * Approach 1: Basic Backtracking
 * - Explore all possible combinations using recursion.
 * - If the current sum equals the target, add the combination to the result.
 * - If the current sum exceeds the target, backtrack.
 */
function combinationSum1(candidates, target) {
  const result = [];
  const combination = [];

  function backtrack(remaining, start) {
    if (remaining === 0) {
      result.push([...combination]);
      return;
    }
    if (remaining < 0) {
      return;
    }

    for (let i = start; i < candidates.length; i++) {
      combination.push(candidates[i]);
      backtrack(remaining - candidates[i], i); // Allow reuse of the same element
      combination.pop(); // Backtrack: remove the last element to try a different path
    }
  }

  backtrack(target, 0);
  return result;
}

/**
 * Approach 2: Backtracking with Early Pruning
 * - Optimized backtracking by adding a condition to avoid unnecessary recursion.
 * - Sort the candidates array to potentially prune earlier.  This doesn't change the fundamental time complexity, but can improve performance in some cases.
 */
function combinationSum2(candidates, target) {
    const result = [];
    const combination = [];
    candidates.sort((a, b) => a - b); // Sort candidates to potentially prune earlier

    function backtrack(remaining, start) {
        if (remaining === 0) {
            result.push([...combination]);
            return;
        }
        if (remaining < 0) {
            return;
        }

        for (let i = start; i < candidates.length; i++) {
            // Early pruning: if current candidate is larger than remaining, skip it
            if (candidates[i] > remaining) {
                break; // Since candidates are sorted, no need to check further
            }
            combination.push(candidates[i]);
            backtrack(remaining - candidates[i], i);
            combination.pop();
        }
    }

    backtrack(target, 0);
    return result;
}


/**
 * Approach 3: Backtracking with Optimized Sum Calculation
 * - Avoids repeated subtraction by calculating the sum incrementally.
 */
function combinationSum3(candidates, target) {
  const result = [];
  const combination = [];
  let currentSum = 0;

  function backtrack(start) {
    if (currentSum === target) {
      result.push([...combination]);
      return;
    }
    if (currentSum > target) {
      return;
    }

    for (let i = start; i < candidates.length; i++) {
      combination.push(candidates[i]);
      currentSum += candidates[i];
      backtrack(i);
      currentSum -= candidates[i]; // Backtrack: subtract the added value
      combination.pop();
    }
  }

  backtrack(0);
  return result;
}

/**
 * Approach 4: Iterative Backtracking (using a stack)
 * - Simulates the recursive backtracking process using a stack.
 * - More complex to understand but avoids recursion overhead.
 */
function combinationSum4(candidates, target) {
  const result = [];
  const stack = [{ combination: [], remaining: target, start: 0 }];

  while (stack.length > 0) {
    const { combination, remaining, start } = stack.pop();

    if (remaining === 0) {
      result.push([...combination]);
    } else if (remaining > 0) {
      for (let i = start; i < candidates.length; i++) {
        stack.push({
          combination: [...combination, candidates[i]],
          remaining: remaining - candidates[i],
          start: i,
        });
      }
    }
    // If remaining < 0, we do nothing (implicit backtracking)
  }
  return result;
}

/**
 * Approach 5: Backtracking with Memoization (Dynamic Programming - Top Down)
 * - Uses memoization to store intermediate results and avoid redundant calculations.
 * - This approach is generally NOT recommended for the *combination sum* problem when unlimited repetitions are allowed, as it doesn't provide significant performance benefits and adds complexity.  Memoization is more helpful when each candidate can be used only *once*.  It is included here for completeness and to show how memoization *could* be applied, but its efficiency is not great here.
 */
function combinationSum5(candidates, target) {
    const memo = new Map(); // Map to store results for subproblems
    const result = [];

    function backtrack(remaining, start) {
        if (remaining === 0) {
            return [[]]; // Base case: one empty combination
        }
        if (remaining < 0) {
            return [];
        }

        const key = `${remaining}-${start}`; // Unique key for the subproblem
        if (memo.has(key)) {
            return memo.get(key);
        }

        const combinations = [];
        for (let i = start; i < candidates.length; i++) {
            const subCombinations = backtrack(remaining - candidates[i], i);
            for (const subCombination of subCombinations) {
                combinations.push([candidates[i], ...subCombination]);
            }
        }
        memo.set(key, combinations);
        return combinations;
    }
    const finalCombinations = backtrack(target, 0);

    // Convert the result from array of arrays to the desired format.
    for(const comb of finalCombinations){
        result.push(comb);
    }
    return result;
}



// Example usage and output:
const candidates = [2, 3, 6, 7];
const target = 7;

console.log("Approach 1: Basic Backtracking");
console.log(combinationSum1(candidates, target)); // Output: [[2,2,3],[7]]

console.log("\nApproach 2: Backtracking with Early Pruning");
console.log(combinationSum2(candidates, target)); // Output: [[2,2,3],[7]]

console.log("\nApproach 3: Backtracking with Optimized Sum Calculation");
console.log(combinationSum3(candidates, target)); // Output: [[2,2,3],[7]]

console.log("\nApproach 4: Iterative Backtracking (using a stack)");
console.log(combinationSum4(candidates, target)); // Output: [[2,2,3],[7]]

console.log("\nApproach 5: Backtracking with Memoization (Dynamic Programming - Top Down)");
console.log(combinationSum5(candidates, target)); // Output: [[2,2,3],[7]]
