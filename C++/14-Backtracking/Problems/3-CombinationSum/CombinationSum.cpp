#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // for std::accumulate

using namespace std;

// Approach 1: Basic Backtracking
// - Uses recursion to explore all possible combinations.
// - Includes a base case to stop recursion when the target sum is reached.
// - Time Complexity: O(2^n) in the worst case, where n is the number of candidates.
// - Space Complexity: O(n) for the depth of the recursion tree.
void combinationSum1(vector<int>& candidates, int target, vector<vector<int>>& result, vector<int>& combination, int start) {
    if (target == 0) {
        result.push_back(combination);
        return;
    }
    if (target < 0) {
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        combination.push_back(candidates[i]);
        combinationSum1(candidates, target - candidates[i], result, combination, i); // Allow duplicates
        combination.pop_back(); // Backtrack
    }
}

// Approach 2: Backtracking with Pruning
// - Optimizes the basic backtracking approach by adding a pruning step.
// - Sorts the candidates array to avoid unnecessary recursive calls.
// - If a candidate is greater than the remaining target, the branch is pruned.
// - Time Complexity: O(b^k), where b is the average branching factor and k is the maximum depth of the recursion.
// - Space Complexity: O(k), where k is the maximum depth of the recursion.
void combinationSum2(vector<int>& candidates, int target, vector<vector<int>>& result, vector<int>& combination, int start) {
    if (target == 0) {
        result.push_back(combination);
        return;
    }
    if (target < 0) {
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        if (candidates[i] > target) { // Pruning step: if current candidate is too big, skip it and the rest
            break; // Assuming candidates are sorted
        }
        combination.push_back(candidates[i]);
        combinationSum2(candidates, target - candidates[i], result, combination, i);
        combination.pop_back();
    }
}

// Approach 3: Backtracking with Skipping Duplicates
// - Handles duplicate candidates in the input array.
// - Skips duplicate candidates to avoid duplicate combinations in the result.
// - Time Complexity: Similar to Approach 2, but avoids redundant computations.
// - Space Complexity: O(k)
void combinationSum3(vector<int>& candidates, int target, vector<vector<int>>& result, vector<int>& combination, int start) {
    if (target == 0) {
        result.push_back(combination);
        return;
    }
    if (target < 0) {
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        if (i > start && candidates[i] == candidates[i - 1]) { // Skip duplicates
            continue;
        }
        if (candidates[i] > target) {
            break;
        }
        combination.push_back(candidates[i]);
        combinationSum3(candidates, target - candidates[i], result, combination, i);
        combination.pop_back();
    }
}

// Approach 4: Iterative Approach using Stack (Simulated Recursion)
// - Simulates the recursive backtracking using a stack.
// - Avoids recursion overhead, but can be more complex to understand.
// - Time Complexity: Similar to the recursive approaches.
// - Space Complexity: O(k), where k is the maximum depth of the combinations.
void combinationSum4(vector<int>& candidates, int target, vector<vector<int>>& result) {
    sort(candidates.begin(), candidates.end()); // Need to sort for optimization
    vector<pair<int, vector<int>>> stack; // Store remaining target and current combination
    stack.push_back({target, {}});

    while (!stack.empty()) {
        int remainingTarget = stack.back().first;
        vector<int> combination = stack.back().second;
        stack.pop_back();

        if (remainingTarget == 0) {
            result.push_back(combination);
            continue;
        }

        for (int i = 0; i < candidates.size(); ++i) {
            if (candidates[i] <= remainingTarget) {
                vector<int> nextCombination = combination;
                nextCombination.push_back(candidates[i]);
                stack.push_back({remainingTarget - candidates[i], nextCombination});
            }
        }
    }
}

// Approach 5: Dynamic Programming (Unbounded Knapsack Variation)
// - Treats the problem as an unbounded knapsack problem.
// - dp[i] stores all combinations that sum up to i.
// - Time Complexity: O(target * n), where n is the number of candidates.
// - Space Complexity: O(target * k), where k is the average size of the combinations.

void combinationSum5(vector<int>& candidates, int target, vector<vector<int>>& result) {
    vector<vector<vector<int>>> dp(target + 1); // dp[i] stores list of combinations that sum to i

    dp[0].push_back({}); // Base case: sum 0 has an empty combination

    for (int i = 1; i <= target; ++i) {
        for (int j = 0; j < candidates.size(); ++j) {
            if (i - candidates[j] >= 0) {
                for (const auto& prevCombination : dp[i - candidates[j]]) {
                    vector<int> currentCombination = prevCombination;
                    currentCombination.push_back(candidates[j]);
                    dp[i].push_back(currentCombination);
                }
            }
        }
    }
    result = dp[target];
}

int main() {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> result;

    cout << "Candidates: ";
    for (int c : candidates) {
        cout << c << " ";
    }
    cout << endl;
    cout << "Target: " << target << endl << endl;

    // Approach 1: Basic Backtracking
    result.clear();
    vector<int> combination1;
    combinationSum1(candidates, target, result, combination1, 0);
    cout << "Approach 1: Basic Backtracking" << endl;
    for (const auto& comb : result) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

    // Approach 2: Backtracking with Pruning
    result.clear();
    vector<int> combination2;
    sort(candidates.begin(), candidates.end()); // Important for pruning
    combinationSum2(candidates, target, result, combination2, 0);
    cout << "Approach 2: Backtracking with Pruning" << endl;
    for (const auto& comb : result) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

    // Approach 3: Backtracking with Skipping Duplicates
    result.clear();
    vector<int> combination3;
    vector<int> candidates3 = {10, 1, 2, 7, 6, 1, 5}; // Example with duplicates
    sort(candidates3.begin(), candidates3.end());
    combinationSum3(candidates3, 8, result, combination3, 0);
    cout << "Approach 3: Backtracking with Skipping Duplicates" << endl;
    for (const auto& comb : result) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

    // Approach 4: Iterative Approach using Stack
    result.clear();
    combinationSum4(candidates, target, result);
    cout << "Approach 4: Iterative Approach using Stack" << endl;
    for (const auto& comb : result) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

     // Approach 5: Dynamic Programming
    result.clear();
    combinationSum5(candidates, target, result);
    cout << "Approach 5: Dynamic Programming" << endl;
    for (const auto& comb : result) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

    return 0;
}
