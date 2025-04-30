#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

// 1. Backtracking with Duplicates Allowed (Basic Approach)
//   - Allows repeated use of numbers from the candidates array.
//   - Directly explores all possible combinations.
//   - Suitable for problems where the same element can be chosen multiple times.
//   - Example: Finding all possible combinations of coins to make a target sum.
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
        combinationSum1(candidates, target - candidates[i], result, combination, i); // Important: i, not i+1
        combination.pop_back();
    }
}

// 2. Backtracking with Duplicates Allowed (Optimized)
//   - Similar to the first approach, but with slight optimization.
//   - Avoids unnecessary recursive calls by checking if the target becomes negative.
void combinationSum2(vector<int>& candidates, int target, vector<vector<int>>& result, vector<int>& combination, int start) {
     if (target == 0) {
        result.push_back(combination);
        return;
    }

    for (int i = start; i < candidates.size(); ++i) {
        if (target - candidates[i] >= 0) { // Optimization: Check before recursion
            combination.push_back(candidates[i]);
            combinationSum2(candidates, target - candidates[i], result, combination, i);
            combination.pop_back();
        }
    }
}


// 3. Backtracking with Duplicates Not Allowed
//   - Each number in the candidates array can be used only once in a combination.
//   - Requires sorting the candidates array to handle duplicates effectively.
//   - Example: Finding unique subsets of a set that sum to a target.
void combinationSum3(vector<int>& candidates, int target, vector<vector<int>>& result, vector<int>& combination, int start) {
    if (target == 0) {
        result.push_back(combination);
        return;
    }
    if (target < 0) {
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        // Skip duplicate numbers to avoid duplicate combinations
        if (i > start && candidates[i] == candidates[i - 1]) {
            continue;
        }
        combination.push_back(candidates[i]);
        combinationSum3(candidates, target - candidates[i], result, combination, i + 1); // Important: i+1
        combination.pop_back();
    }
}

// 4. Using set to avoid Duplicates
//  - Uses a set to store the results, thus removing any duplicate combinations.
void combinationSum4(vector<int>& candidates, int target, set<vector<int>>& result_set, vector<int>& combination, int start) {
    if (target == 0) {
        // Sort the combination to handle duplicates correctly in the set.
        vector<int> sortedCombination = combination;
        sort(sortedCombination.begin(), sortedCombination.end());
        result_set.insert(sortedCombination);
        return;
    }
    if (target < 0) {
        return;
    }
    for (int i = start; i < candidates.size(); ++i) {
        combination.push_back(candidates[i]);
        combinationSum4(candidates, target - candidates[i], result_set, combination, i);
        combination.pop_back();
    }

}

// 5. Iterative Approach using Stack
// - Iterative approach to solve the combination sum problem
// - Uses a stack to keep track of the current combination and the remaining target
// - Handles duplicate candidates
vector<vector<int>> combinationSum5(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    sort(candidates.begin(), candidates.end()); // Sort candidates to handle duplicates
    vector<pair<vector<int>, int>> stack; // Store combination and remaining target
    stack.push_back({{}, target});

    while (!stack.empty()) {
        vector<int> combination = stack.back().first;
        int remainingTarget = stack.back().second;
        stack.pop_back();

        if (remainingTarget == 0) {
            result.push_back(combination);
            continue;
        }

        for (int i = (combination.empty() ? 0 : (lower_bound(candidates.begin(), candidates.end(), combination.back()) - candidates.begin())); i < candidates.size(); ++i) {
             if (i > (combination.empty() ? 0 : (lower_bound(candidates.begin(), candidates.end(), combination.back()) - candidates.begin())) && candidates[i] == candidates[i - 1]) {
                continue; // Skip duplicates
            }
            if (remainingTarget - candidates[i] >= 0) {
                vector<int> nextCombination = combination;
                nextCombination.push_back(candidates[i]);
                stack.push_back({nextCombination, remainingTarget - candidates[i]});
            }
        }
    }
    return result;
}

int main() {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> result1, result2, result3;
    set<vector<int>> result_set;
    vector<int> combination;

    cout << "Candidates: ";
    for (int num : candidates) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Target: " << target << endl << endl;

    // Approach 1: Backtracking with Duplicates Allowed
    combinationSum1(candidates, target, result1, combination, 0);
    cout << "Approach 1: Backtracking with Duplicates Allowed" << endl;
    for (const auto& comb : result1) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

    // Approach 2: Backtracking with Duplicates Allowed (Optimized)
    combination.clear();
    combinationSum2(candidates, target, result2, combination, 0);
    cout << "Approach 2: Backtracking with Duplicates Allowed (Optimized)" << endl;
    for (const auto& comb : result2) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

    // Test Case for Approach 3: Duplicates Not Allowed
    vector<int> candidates3 = {10, 1, 2, 7, 6, 1, 5};
    int target3 = 8;
    vector<vector<int>> result3_1;
    vector<int> combination3;
    sort(candidates3.begin(), candidates3.end()); // Sort for approach 3
    combinationSum3(candidates3, target3, result3_1, combination3, 0);
    cout << "Approach 3: Backtracking with Duplicates Not Allowed" << endl;
    cout << "Candidates: ";
    for(int c : candidates3)
        cout<< c << " ";
    cout << endl;
    cout << "Target: " << target3 << endl;
    for (const auto& comb : result3_1) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

    // Approach 4: Using set to avoid Duplicates
    combination.clear();
    combinationSum4(candidates, target, result_set, combination, 0);
    cout << "Approach 4: Using set to avoid Duplicates" << endl;
    for (const auto& comb : result_set) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

     // Approach 5: Iterative Approach using Stack
    vector<vector<int>> result5 = combinationSum5(candidates, target);
    cout << "Approach 5: Iterative Approach using Stack" << endl;
    for (const auto& comb : result5) {
        cout << "[ ";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "] ";
    }
    cout << endl << endl;

    return 0;
}

