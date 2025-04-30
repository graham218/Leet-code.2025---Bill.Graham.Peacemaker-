#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <queue> // Include the queue header

using namespace std;

// 1. Backtracking with Swapping
//   - The most common and straightforward approach.
//   - Fix an element, permute the rest, and then backtrack.
void permute1(vector<int>& nums, int l, int r, vector<vector<int>>& result) {
    if (l == r) {
        result.push_back(nums);
        return;
    }
    for (int i = l; i <= r; ++i) {
        swap(nums[l], nums[i]);       // Fix the current element
        permute1(nums, l + 1, r, result); // Recurse for the remaining elements
        swap(nums[l], nums[i]);       // Backtrack: restore the original order
    }
}

vector<vector<int>> permute1(vector<int>& nums) {
    vector<vector<int>> result;
    permute1(nums, 0, nums.size() - 1, result);
    return result;
}

// 2. Backtracking with Visited Array
//   - Uses a boolean array to track which elements have been included in the current permutation.
void permute2(vector<int>& nums, vector<int>& current, vector<bool>& visited, vector<vector<int>>& result) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (!visited[i]) {
            visited[i] = true;            // Mark the element as visited
            current.push_back(nums[i]); // Add it to the current permutation
            permute2(nums, current, visited, result); // Recurse
            current.pop_back();         // Backtrack: remove the element
            visited[i] = false;           // Mark the element as unvisited
        }
    }
}

vector<vector<int>> permute2(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;
    vector<bool> visited(nums.size(), false);
    permute2(nums, current, visited, result);
    return result;
}

// 3. Using STL's next_permutation
//   - The simplest way, using the standard library function.
//   - Requires the input array to be sorted.
vector<vector<int>> permute3(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end()); // Important: Sort the input first
    do {
        result.push_back(nums);
    } while (next_permutation(nums.begin(), nums.end())); // Generate permutations
    return result;
}

// 4. Recursive Approach without Swapping (Building Permutations)
//   - Builds permutations by inserting each number into all possible positions of the existing permutations.
vector<vector<int>> permute4(vector<int>& nums) {
    vector<vector<int>> result;
    if (nums.empty()) {
        result.push_back({}); // Base case: empty input, one empty permutation
        return result;
    }

    int first = nums[0];
    vector<int> rest(nums.begin() + 1, nums.end()); // Get the remaining elements
    vector<vector<int>> subPermutations = permute4(rest); // Recursively get permutations of the rest

    for (const auto& subPermutation : subPermutations) {
        for (int i = 0; i <= subPermutation.size(); ++i) {
            vector<int> permutation = subPermutation;
            permutation.insert(permutation.begin() + i, first); // Insert 'first' at every possible position
            result.push_back(permutation);
        }
    }
    return result;
}

// 5. Iterative Approach (Using a Queue) -  More complex, but avoids recursion
//    -  Start with a queue containing an empty permutation.
//    -  Iteratively build larger permutations by inserting numbers.
vector<vector<int>> permute5(vector<int>& nums) {
    vector<vector<int>> result;
    if (nums.empty()) {
        return {{}};
    }

    queue<vector<int>> q; // Use std::queue
    q.push({}); // Start with an empty permutation

    for (int num : nums) {
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            vector<int> current = q.front();
            q.pop();
            for (int j = 0; j <= current.size(); ++j) {
                vector<int> next = current;
                next.insert(next.begin() + j, num); // Insert the current number
                if (next.size() == nums.size()) {
                    result.push_back(next);
                } else {
                    q.push(next);
                }
            }
        }
    }
    return result;
}

int main() {
    vector<int> nums = {1, 2, 3};

    cout << "Method 1: Backtracking with Swapping\n";
    vector<vector<int>> result1 = permute1(nums);
    for (const auto& p : result1) {
        for (int num : p) {
            cout << num << " ";
        }
        cout << endl;
    }

    cout << "\nMethod 2: Backtracking with Visited Array\n";
    vector<vector<int>> result2 = permute2(nums);
    for (const auto& p : result2) {
        for (int num : p) {
            cout << num << " ";
        }
        cout << endl;
    }

    cout << "\nMethod 3: Using STL's next_permutation\n";
    vector<vector<int>> result3 = permute3(nums);
    for (const auto& p : result3) {
        for (int num : p) {
            cout << num << " ";
        }
        cout << endl;
    }

    cout << "\nMethod 4: Recursive Approach without Swapping\n";
    vector<vector<int>> result4 = permute4(nums);
    for (const auto& p : result4) {
        for (int num : p) {
            cout << num << " ";
        }
        cout << endl;
    }

    cout << "\nMethod 5: Iterative Approach (Using a Queue)\n";
    vector<vector<int>> result5 = permute5(nums);
    for (const auto& p : result5) {
        for (int num : p) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}
