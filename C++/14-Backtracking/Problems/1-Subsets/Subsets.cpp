#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // for iota

using namespace std;

// Approach 1: Recursive Backtracking (Classic)
// Time Complexity: O(N * 2^N), Space Complexity: O(N) - due to the depth of recursion
class Solution1 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> currentSubset;
        backtrack(nums, 0, currentSubset, result);
        return result;
    }

private:
    void backtrack(vector<int>& nums, int start, vector<int>& currentSubset, vector<vector<int>>& result) {
        // Each time the function is called, the current subset is a valid subset.
        result.push_back(currentSubset);

        // Explore the elements after 'start'
        for (int i = start; i < nums.size(); ++i) {
            // Include the current element
            currentSubset.push_back(nums[i]);
            // Recursively find subsets with the current element included
            backtrack(nums, i + 1, currentSubset, result);
            // Backtrack: Remove the current element to explore other possibilities
            currentSubset.pop_back();
        }
    }
};

// Approach 2: Iterative Approach using Bit Manipulation
// Time Complexity: O(N * 2^N), Space Complexity: O(1) - excluding the result vector
class Solution2 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        // Iterate through all possible subsets represented by binary numbers from 0 to 2^n - 1
        for (int i = 0; i < (1 << n); ++i) {
            vector<int> currentSubset;
            // Check each bit of 'i' to determine if the corresponding element should be included
            for (int j = 0; j < n; ++j) {
                // If the j-th bit of 'i' is set, include nums[j] in the current subset
                if ((i >> j) & 1) {
                    currentSubset.push_back(nums[j]);
                }
            }
            result.push_back(currentSubset);
        }
        return result;
    }
};

// Approach 3: Cascading Approach
// Time Complexity: O(N * 2^N), Space Complexity: O(1) - excluding the result vector
class Solution3 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        // Start with an empty subset
        result.push_back({});

        // Iterate through each element in nums
        for (int num : nums) {
            int size = result.size(); // Important: capture the current size, as result will grow in the loop
            // Iterate through all existing subsets in 'result'
            for (int j = 0; j < size; ++j) {
                // Create a new subset by adding the current element to each existing subset
                vector<int> newSubset = result[j];
                newSubset.push_back(num);
                result.push_back(newSubset); // Add the new subset to the result
            }
        }
        return result;
    }
};

// Approach 4: Recursive Backtracking (Alternative)
// Time Complexity: O(N * 2^N), Space Complexity: O(N)
class Solution4 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> subset;
        generateSubsets(nums, 0, subset, result);
        return result;
    }

private:
    void generateSubsets(vector<int>& nums, int index, vector<int>& subset, vector<vector<int>>& result) {
        if (index == nums.size()) {
            result.push_back(subset);
            return;
        }
        // Option 1: Exclude nums[index]
        generateSubsets(nums, index + 1, subset, result);

        // Option 2: Include nums[index]
        subset.push_back(nums[index]);
        generateSubsets(nums, index + 1, subset, result);
        subset.pop_back(); // Backtrack
    }
};

// Approach 5: Using std::accumulate (Functional Approach) -  Heavily relies on the initial empty set
// Time Complexity: O(N * 2^N), Space Complexity: O(N * 2^N) - due to copying of vectors.
class Solution5 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result = accumulate(nums.begin(), nums.end(), vector<vector<int>>{{}},
            [](vector<vector<int>> subsets, int num) {
                vector<vector<int>> newSubsets;
                for (const auto& subset : subsets) {
                    newSubsets.push_back(subset); // Copy the existing subset
                    vector<int> subsetWithNum = subset;
                    subsetWithNum.push_back(num);  // Add the current number
                    newSubsets.push_back(subsetWithNum); // Add the new subset
                }
                return newSubsets;
            });
        return result;
    }
};

int main() {
    vector<int> nums = {1, 2, 3};

    Solution1 sol1;
    vector<vector<int>> result1 = sol1.subsets(nums);
    cout << "Approach 1: Recursive Backtracking (Classic)" << endl;
    for (const auto& subset : result1) {
        cout << "[";
        for (int i = 0; i < subset.size(); ++i) {
            cout << subset[i];
            if (i < subset.size() - 1) {
                cout << ", ";
            }
        }
        cout << "] ";
    }
    cout << endl;

    Solution2 sol2;
    vector<vector<int>> result2 = sol2.subsets(nums);
    cout << "Approach 2: Iterative Approach using Bit Manipulation" << endl;
    for (const auto& subset : result2) {
        cout << "[";
        for (int i = 0; i < subset.size(); ++i) {
            cout << subset[i];
            if (i < subset.size() - 1) {
                cout << ", ";
            }
        }
        cout << "] ";
    }
    cout << endl;

    Solution3 sol3;
    vector<vector<int>> result3 = sol3.subsets(nums);
    cout << "Approach 3: Cascading Approach" << endl;
    for (const auto& subset : result3) {
        cout << "[";
        for (int i = 0; i < subset.size(); ++i) {
            cout << subset[i];
            if (i < subset.size() - 1) {
                cout << ", ";
            }
        }
        cout << "] ";
    }
    cout << endl;

    Solution4 sol4;
    vector<vector<int>> result4 = sol4.subsets(nums);
    cout << "Approach 4: Recursive Backtracking (Alternative)" << endl;
    for (const auto& subset : result4) {
        cout << "[";
        for (int i = 0; i < subset.size(); ++i) {
            cout << subset[i];
            if (i < subset.size() - 1) {
                cout << ", ";
            }
        }
        cout << "] ";
    }
    cout << endl;

    Solution5 sol5;
    vector<vector<int>> result5 = sol5.subsets(nums);
    cout << "Approach 5: Using std::accumulate (Functional Approach)" << endl;
    for (const auto& subset : result5) {
        cout << "[";
        for (int i = 0; i < subset.size(); ++i) {
            cout << subset[i];
            if (i < subset.size() - 1) {
                cout << ", ";
            }
        }
        cout << "] ";
    }
    cout << endl;

    return 0;
}
