#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <numeric> // for iota

using namespace std;

// Function to print a vector
void printVector(const vector<int>& vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

// 1. Backtracking with Swapping (Classic Approach)
//   - Real-world use case: Generating test cases for algorithms.  You need all possible input orderings.
void permute1(vector<int>& nums, int l, int r, vector<vector<int>>& result) {
    if (l == r) {
        result.push_back(nums);
        return;
    }
    for (int i = l; i <= r; ++i) {
        swap(nums[l], nums[i]);       // Explore: Fix the current element
        permute1(nums, l + 1, r, result); // Recurse: Permute the remaining
        swap(nums[l], nums[i]);       // Backtrack: Undo the change for the next iteration
    }
}

vector<vector<int>> generatePermutations1(vector<int> nums) {
    vector<vector<int>> result;
    permute1(nums, 0, nums.size() - 1, result);
    return result;
}

// 2. Backtracking with Extra Space (Using a 'chosen' vector)
//   - Real-world use case:  Job scheduling.  Trying all possible orders to find the optimal schedule.
void permute2(vector<int>& nums, vector<int>& current, vector<bool>& chosen, vector<vector<int>>& result) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }
    for (int i = 0; i < nums.size(); ++i) {
        if (!chosen[i]) {
            chosen[i] = true;            // Mark the element as used
            current.push_back(nums[i]); // Add it to the current permutation
            permute2(nums, current, chosen, result); // Recurse
            current.pop_back();         // Backtrack: Remove the element
            chosen[i] = false;           // Backtrack: Unmark the element
        }
    }
}

vector<vector<int>> generatePermutations2(vector<int> nums) {
    vector<vector<int>> result;
    vector<int> current;
    vector<bool> chosen(nums.size(), false);
    permute2(nums, current, chosen, result);
    return result;
}

// 3. Using the STL (std::next_permutation)
//    - Real-world use case:  Generating all possible orderings for a brute-force search in a small problem space.  e.g., Trying all password combinations (within a limited set).
vector<vector<int>> generatePermutations3(vector<int> nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end()); // Important: Start with sorted input
    do {
        result.push_back(nums);
    } while (next_permutation(nums.begin(), nums.end())); //  Keep generating the next permutation
    return result;
}

// 4. Backtracking for Strings (Handling Duplicates)
//    - Real-world use case: Generating unique string permutations, like creating variations of a username or product code.
void permuteUnique(string& s, int l, int r, set<string>& result) { // Use a set to avoid duplicates
    if (l == r) {
        result.insert(s); // Insert into the set
        return;
    }
    for (int i = l; i <= r; ++i) {
        swap(s[l], s[i]);
        permuteUnique(s, l + 1, r, result);
        swap(s[l], s[i]); // Backtrack
    }
}

set<string> generateUniquePermutations(string s) {
    set<string> result;
    permuteUnique(s, 0, s.size() - 1, result);
    return result;
}

// 5.  Iterative Approach (Using Index Tracking) - More Complex, but avoids recursion
//     - Real-world use case:  Implementing a permutation generator in a very memory-constrained environment where recursion is too expensive.
vector<vector<int>> generatePermutations5(vector<int> nums) {
    vector<vector<int>> result;
    if (nums.empty()) return result;

    vector<int> p(nums.size(), 0); // p[i] stores the index of the element to swap with at position i
    result.push_back(nums);       // Add the original input as the first permutation
    int i = 1;
    while (i < nums.size()) {
        if (p[i] < i) {
            int j = (i % 2 == 0) ? 0 : p[i]; // Choose element to swap with
            swap(nums[i], nums[j]);
            result.push_back(nums);
            p[i]++;
            i = 1; // Reset i to 1 to start the process for the next permutation
        } else {
            p[i] = 0; // Reset p[i] if it has reached its maximum value
            i++;
        }
    }
    return result;
}

int main() {
    cout << "1. Backtracking with Swapping:\n";
    vector<int> nums1 = {1, 2, 3};
    vector<vector<int>> result1 = generatePermutations1(nums1);
    for (const auto& perm : result1) {
        printVector(perm);
    }

    cout << "\n2. Backtracking with Extra Space:\n";
    vector<int> nums2 = {1, 2, 3};
    vector<vector<int>> result2 = generatePermutations2(nums2);
    for (const auto& perm : result2) {
        printVector(perm);
    }

    cout << "\n3. Using STL (std::next_permutation):\n";
    vector<int> nums3 = {1, 2, 3};
    vector<vector<int>> result3 = generatePermutations3(nums3);
    for (const auto& perm : result3) {
        printVector(perm);
    }

    cout << "\n4. Backtracking for Strings (Handling Duplicates):\n";
    string s = "aab";
    set<string> result4 = generateUniquePermutations(s);
    for (const auto& perm : result4) {
        cout << perm << endl;
    }

    cout << "\n5. Iterative Approach:\n";
    vector<int> nums5 = {1, 2, 3};
    vector<vector<int>> result5 = generatePermutations5(nums5);
    for (const auto& perm : result5) {
        printVector(perm);
    }

    return 0;
}
