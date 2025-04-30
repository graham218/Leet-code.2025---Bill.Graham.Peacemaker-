#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

// Approach 1: Basic Backtracking (Power Set Generation)
//
//   * Real-world application: Generating all possible combinations of options in a configuration file.
//   * Explanation: This is the most straightforward backtracking approach.  For each element, we have two choices: include it in the current subset or exclude it.  We recursively explore both possibilities.
//   * Time Complexity: O(2^n), where n is the number of elements in the input set.
//   * Space Complexity: O(n), due to the depth of the recursion.
void generateSubsets1(const vector<int>& nums, int index, vector<int>& currentSubset, vector<vector<int>>& result) {
    // Base case: When we have processed all elements, add the current subset to the result.
    if (index == nums.size()) {
        result.push_back(currentSubset);
        return;
    }

    // Recursive case 1: Exclude the current element.
    generateSubsets1(nums, index + 1, currentSubset, result);

    // Recursive case 2: Include the current element.
    currentSubset.push_back(nums[index]);
    generateSubsets1(nums, index + 1, currentSubset, result);
    currentSubset.pop_back(); // Backtrack: Remove the element to explore other possibilities.
}

vector<vector<int>> subsets1(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> currentSubset;
    generateSubsets1(nums, 0, currentSubset, result);
    return result;
}

// Approach 2: Backtracking with Iterative Subset Construction
//
//   * Real-world application: Building feature sets for machine learning models.
//   * Explanation: Instead of adding/removing elements during recursion, we build subsets iteratively.  For each element, we add it to all existing subsets. This avoids explicit backtracking in the recursive calls.
//   * Time Complexity: O(2^n)
//   * Space Complexity: O(2^n) -  More space intensive as it stores all intermediate subsets.
void generateSubsets2(const vector<int>& nums, int index, vector<vector<int>>& currentSubsets) {
    if (index == nums.size()) {
        return;
    }

    int numSubsets = currentSubsets.size(); // Important: Store the current size, as it changes in the loop.
    for (int i = 0; i < numSubsets; ++i) {
        vector<int> newSubset = currentSubsets[i]; // Copy an existing subset.
        newSubset.push_back(nums[index]);         // Add the current element.
        currentSubsets.push_back(newSubset);       // Add the new subset to the list.
    }
    generateSubsets2(nums, index + 1, currentSubsets);
}

vector<vector<int>> subsets2(vector<int>& nums) {
    vector<vector<int>> result = {{}}; // Start with the empty set.
    generateSubsets2(nums, 0, result);
    return result;
}

// Approach 3: Using Bit Manipulation
//
//   * Real-world application: Representing and manipulating combinations of flags or options.
//   * Explanation:  Each subset can be represented by a binary number, where the i-th bit indicates whether the i-th element is present in the subset. We iterate through all possible binary numbers (0 to 2^n - 1) and construct the corresponding subsets.
//   * Time Complexity: O(n * 2^n) - Iterating through 2^n subsets, and copying up to n elements for each.
//   * Space Complexity: O(1) - Excluding the space used to store the result.
vector<vector<int>> subsets3(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;

    for (int i = 0; i < (1 << n); ++i) { // Iterate through all possible bitmasks (subsets).
        vector<int> currentSubset;
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) { // Check if the j-th bit is set.
                currentSubset.push_back(nums[j]);
            }
        }
        result.push_back(currentSubset);
    }
    return result;
}

// Approach 4: Backtracking with Pruning to Avoid Duplicates (for non-unique input)
//
//   * Real-world application: Generating unique combinations when dealing with data that has duplicate entries, such as in database queries.
//   * Explanation: When the input array contains duplicate elements, we need to avoid generating duplicate subsets.  We sort the input array and add a condition to skip duplicate elements during the backtracking process.
//   * Time Complexity: O(2^n) in the worst case, but performs better with duplicates.
//   * Space Complexity: O(n)
void generateSubsets4(const vector<int>& nums, int index, vector<int>& currentSubset, vector<vector<int>>& result) {
    if (index == nums.size()) {
        result.push_back(currentSubset);
        return;
    }

    // Include the current element.
    currentSubset.push_back(nums[index]);
    generateSubsets4(nums, index + 1, currentSubset, result);
    currentSubset.pop_back();

    // Exclude the current element, but skip duplicates.
    while (index + 1 < nums.size() && nums[index] == nums[index + 1]) {
        index++; // Skip duplicate elements.
    }
    generateSubsets4(nums, index + 1, currentSubset, result);
}

vector<vector<int>> subsets4(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> currentSubset;
    sort(nums.begin(), nums.end()); // Sort the input to handle duplicates.
    generateSubsets4(nums, 0, currentSubset, result);
    return result;
}

// Approach 5: Using std::set to ensure unique subsets (Alternative for duplicate input)
//
//   * Real-world application:  Eliminating redundant data entries or ensuring uniqueness in generated data.
//   * Explanation: This approach uses a `std::set` to store the generated subsets, automatically ensuring uniqueness.  The subsets (which are vectors) need to be converted to a hashable type (like a string) before being inserted into the set.  This is an alternative way to handle duplicates, trading off some efficiency for simplicity.
//   * Time Complexity: O(n * 2^n * log(2^n))  -  log(2^n) factor comes from set insertion.  String conversion is O(n).
//   * Space Complexity: O(n * 2^n) -  To store all unique subsets in the set.
vector<vector<int>> subsets5(vector<int>& nums) {
    set<string> uniqueSubsets;
    vector<vector<int>> result;
    vector<int> currentSubset;

    generateSubsets1(nums, 0, currentSubset, result); // Use basic backtracking to generate all subsets (including duplicates)

    for (const auto& subset : result) {
        string subsetString = "";
        for (int num : subset) {
            subsetString += to_string(num) + ","; // Convert subset to a string.
        }
        uniqueSubsets.insert(subsetString); // Insert into the set, which automatically removes duplicates.
    }

    result.clear(); // Clear the result vector.
    for (const auto& subsetString : uniqueSubsets) {
        vector<int> subset;
        string numStr = "";
        for (char c : subsetString) {
            if (c == ',') {
                if (!numStr.empty()) {
                    subset.push_back(stoi(numStr));
                    numStr = "";
                }
            } else {
                numStr += c;
            }
        }
        result.push_back(subset);
    }
    return result;
}

int main() {
    vector<int> nums1 = {1, 2, 3};
    cout << "Subsets of {1, 2, 3} (Approach 1):" << endl;
    vector<vector<int>> result1 = subsets1(nums1);
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

    cout << "Subsets of {1, 2, 3} (Approach 2):" << endl;
    vector<vector<int>> result2 = subsets2(nums1);
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

    cout << "Subsets of {1, 2, 3} (Approach 3):" << endl;
    vector<vector<int>> result3 = subsets3(nums1);
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

    vector<int> nums4 = {1, 2, 2};
    cout << "Subsets of {1, 2, 2} (Approach 4):" << endl;
    vector<vector<int>> result4 = subsets4(nums4);
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

    cout << "Subsets of {1, 2, 2} (Approach 5):" << endl;
    vector<vector<int>> result5 = subsets5(nums4);
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
