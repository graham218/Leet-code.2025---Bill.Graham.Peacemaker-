#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // Required for std::accumulate

using namespace std;

// 1. Greedy Approach (Optimized)
//    - Time Complexity: O(n)
//    - Space Complexity: O(1)
//    - Explanation: The most efficient approach.  Iterate from left to right,
//      keeping track of the farthest reachable index.  If the current index
//      is beyond the farthest reachable index, we cannot reach the end.
bool canJumpGreedy(vector<int>& nums) {
    int maxReach = 0; // Furthest index reachable
    for (int i = 0; i < nums.size(); ++i) {
        if (i > maxReach) { // If current index is beyond maxReach, we can't reach here.
            return false;
        }
        maxReach = max(maxReach, i + nums[i]); // Update maxReach
    }
    return true; // If we get to the end, we can jump to the end.
}

// 2. Dynamic Programming (Top-Down with Memoization)
//    - Time Complexity: O(n^2)  (Can be optimized to O(n) with careful memoization, but the basic top-down is O(n^2))
//    - Space Complexity: O(n) (for the memoization array and recursion stack)
//    - Explanation:  Use recursion with memoization to avoid redundant calculations.
//      `memo[i]` stores whether it's possible to reach the end from index `i`.
bool canJumpMemoizationHelper(vector<int>& nums, int index, vector<int>& memo) {
    if (index >= nums.size() - 1) {
        return true; // Base case: If we reach the end or go beyond, we can reach.
    }
    if (memo[index] != -1) {
        return memo[index] == 1; // Return memoized result if available
    }

    for (int jump = 1; jump <= nums[index]; ++jump) {
        if (canJumpMemoizationHelper(nums, index + jump, memo)) {
            memo[index] = 1; // Mark as reachable
            return true;
        }
    }
    memo[index] = 0; // Mark as unreachable
    return false;
}

bool canJumpMemoization(vector<int>& nums) {
    vector<int> memo(nums.size(), -1); // -1: unknown, 0: false, 1: true
    return canJumpMemoizationHelper(nums, 0, memo);
}

// 3. Dynamic Programming (Bottom-Up)
//    - Time Complexity: O(n^2)
//    - Space Complexity: O(n)
//    - Explanation:  Iterate from the end of the array to the beginning.
//      `dp[i]` stores whether it's possible to reach the end from index `i`.
bool canJumpBottomUp(vector<int>& nums) {
    int n = nums.size();
    vector<bool> dp(n, false);
    dp[n - 1] = true; // Base case: Last element is reachable from itself.

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 1; j <= nums[i] && i + j < n; ++j) {
            if (dp[i + j]) { // If any of the reachable positions can reach the end
                dp[i] = true;
                break;
            }
        }
    }
    return dp[0]; // Check if we can reach the end from the starting position.
}

// 4. Backtracking (Recursive) - Time Limit Exceeded for larger inputs
//    - Time Complexity: O(2^n)  (Exponential)
//    - Space Complexity: O(n) (for the recursion stack)
//    - Explanation:  Explore all possible jump combinations using recursion.
//      This approach is very inefficient and will result in a time limit exceeded
//      for most non-trivial test cases.
bool canJumpBacktrack(vector<int>& nums, int index) {
    if (index >= nums.size() - 1) {
        return true; // Base case: Reached the end
    }

    for (int jump = 1; jump <= nums[index]; ++jump) {
        if (canJumpBacktrack(nums, index + jump)) {
            return true; // If any path from here leads to the end, return true
        }
    }
    return false; // If no path from here leads to the end, return false
}

bool canJumpBacktracking(vector<int>& nums) {
    return canJumpBacktrack(nums, 0);
}

// 5. Greedy (Backward)
//    - Time Complexity: O(n)
//    - Space Complexity: O(1)
//    - Explanation: Start from the end and work backwards.  Keep track of the
//      leftmost position that can reach the end.  If we reach the beginning
//      and it's marked as a "good" position, we can reach the end.
bool canJumpGreedyBackward(vector<int>& nums) {
    int lastGoodPos = nums.size() - 1; // Last position that can reach the end.
    for (int i = nums.size() - 2; i >= 0; --i) {
        if (i + nums[i] >= lastGoodPos) {
            lastGoodPos = i; // Update the leftmost good position
        }
    }
    return lastGoodPos == 0; // If the first position is a "good" position, we can reach the end.
}

int main() {
    // Example usage
    vector<int> nums1 = {2, 3, 1, 1, 4};
    vector<int> nums2 = {3, 2, 1, 0, 4};
    vector<int> nums3 = {0};
    vector<int> nums4 = {2, 0, 0};
    vector<int> nums5 = {2, 5, 0, 0};

    cout << "Example 1: [2, 3, 1, 1, 4]\n";
    cout << "Greedy: " << (canJumpGreedy(nums1) ? "true" : "false") << endl;
    cout << "Memoization: " << (canJumpMemoization(nums1) ? "true" : "false") << endl;
    cout << "Bottom-Up DP: " << (canJumpBottomUp(nums1) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktracking(nums1) ? "true" : "false") << endl;
    cout << "Greedy Backward: " << (canJumpGreedyBackward(nums1) ? "true" : "false") << endl;


    cout << "\nExample 2: [3, 2, 1, 0, 4]\n";
    cout << "Greedy: " << (canJumpGreedy(nums2) ? "true" : "false") << endl;
    cout << "Memoization: " << (canJumpMemoization(nums2) ? "true" : "false") << endl;
    cout << "Bottom-Up DP: " << (canJumpBottomUp(nums2) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktracking(nums2) ? "true" : "false") << endl;
    cout << "Greedy Backward: " << (canJumpGreedyBackward(nums2) ? "true" : "false") << endl;

    cout << "\nExample 3: [0]\n";
    cout << "Greedy: " << (canJumpGreedy(nums3) ? "true" : "false") << endl;
    cout << "Memoization: " << (canJumpMemoization(nums3) ? "true" : "false") << endl;
    cout << "Bottom-Up DP: " << (canJumpBottomUp(nums3) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktracking(nums3) ? "true" : "false") << endl;
    cout << "Greedy Backward: " << (canJumpGreedyBackward(nums3) ? "true" : "false") << endl;

    cout << "\nExample 4: [2, 0, 0]\n";
    cout << "Greedy: " << (canJumpGreedy(nums4) ? "true" : "false") << endl;
    cout << "Memoization: " << (canJumpMemoization(nums4) ? "true" : "false") << endl;
    cout << "Bottom-Up DP: " << (canJumpBottomUp(nums4) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktracking(nums4) ? "true" : "false") << endl;
    cout << "Greedy Backward: " << (canJumpGreedyBackward(nums4) ? "true" : "false") << endl;

    cout << "\nExample 5: [2, 5, 0, 0]\n";
    cout << "Greedy: " << (canJumpGreedy(nums5) ? "true" : "false") << endl;
    cout << "Memoization: " << (canJumpMemoization(nums5) ? "true" : "false") << endl;
    cout << "Bottom-Up DP: " << (canJumpBottomUp(nums5) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktracking(nums5) ? "true" : "false") << endl;
    cout << "Greedy Backward: " << (canJumpGreedyBackward(nums5) ? "true" : "false") << endl;

    return 0;
}
