#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // For std::accumulate

using namespace std;

// Approach 1: Greedy (Most Efficient)
// Time Complexity: O(n), Space Complexity: O(1)
// Real-world application: Optimizing resource allocation.  Imagine you have a series of tasks (represented by the array),
// and each task has a 'jump' value indicating how many subsequent tasks you can complete by finishing the current one.
// This greedy approach finds out if you can complete all tasks with the minimum effort.
bool canJumpGreedy(vector<int>& nums) {
    int maxReach = 0;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        if (i > maxReach) { // If the current index is beyond the maximum reachable index, we cannot reach the end.
            return false;
        }
        maxReach = max(maxReach, i + nums[i]); // Update the maximum reachable index.
    }
    return true; // If we reach here, we can reach the end.
}

// Approach 2: Dynamic Programming (Top-Down with Memoization)
// Time Complexity: O(n^2), Space Complexity: O(n)
// Real-world application: Game development.  Think of a platformer game where the player can jump a certain distance.  You can use
// this approach to determine if the player can reach a destination point.  Memoization avoids redundant calculations, which
// can be important for complex game levels.
bool canJumpDP(vector<int>& nums, int index, vector<int>& memo) {
    if (index >= nums.size() - 1) {
        return true; // Base case: If we reach the end or go beyond, we can jump.
    }
    if (memo[index] != -1) {
        return memo[index]; // Return memoized result if available.
    }

    for (int i = 1; i <= nums[index]; i++) {
        if (canJumpDP(nums, index + i, memo)) {
            memo[index] = 1; // Mark as reachable.
            return true;
        }
    }
    memo[index] = 0; // Mark as unreachable.
    return false;
}

bool canJumpDP(vector<int>& nums) {
    vector<int> memo(nums.size(), -1); // Initialize memoization table with -1 (unvisited).
    return canJumpDP(nums, 0, memo);
}

// Approach 3: Dynamic Programming (Bottom-Up)
// Time Complexity: O(n^2), Space Complexity: O(n)
// Real-world application:  Route planning.  Imagine you have a series of waypoints, and each waypoint indicates how far you
// can travel from it.  This bottom-up approach can determine if you can reach your destination.  It's similar to the top-down
// approach but builds the solution iteratively.
bool canJumpDPBottomUp(vector<int>& nums) {
    int n = nums.size();
    vector<bool> dp(n, false); // dp[i] is true if we can reach index i.
    dp[0] = true; // We can always reach the first index.

    for (int i = 0; i < n; i++) {
        if (dp[i]) { // If we can reach index i,
            for (int j = 1; j <= nums[i] && i + j < n; j++) {
                dp[i + j] = true; // then we can reach any index within our jump range.
            }
        }
    }
    return dp[n - 1]; // Return whether we can reach the last index.
}

// Approach 4: Backtracking (Brute Force - Time Limit Exceeded for larger inputs)
// Time Complexity: O(2^n), Space Complexity: O(n) (due to recursion depth)
// Real-world application:  This is the *least* efficient approach, but it demonstrates a basic problem-solving technique.  In
// some very limited scenarios (small problem sizes), you might use backtracking to explore all possibilities, such as
// finding all possible paths in a very small maze or solving a puzzle with a limited number of moves.  Generally, avoid this
// for performance-critical applications.
bool canJumpBacktrack(vector<int>& nums, int index) {
    if (index >= nums.size() - 1) {
        return true; // Base case: Reached the end.
    }

    for (int i = 1; i <= nums[index]; i++) {
        if (canJumpBacktrack(nums, index + i)) {
            return true; // If any jump from this position leads to the end, return true.
        }
    }
    return false; // If no jump leads to the end, return false.
}

bool canJumpBacktrack(vector<int>& nums) {
    return canJumpBacktrack(nums, 0);
}

// Approach 5: Optimized Greedy (Forward Iteration)
// Time Complexity: O(n), Space Complexity: O(1)
// Real-world application: Similar to the first greedy approach, but with a slight optimization.  Imagine optimizing the movement
// of a robot or a vehicle.  You want to find the furthest reachable point at each step to minimize the number of steps.  This
// approach is efficient for problems where you need to track the maximum extent of progress.
bool canJumpOptimizedGreedy(vector<int>& nums) {
    int n = nums.size();
    int furthestReach = 0;

    for (int i = 0; i < n; ++i) {
        if (i > furthestReach) {
            return false; // Cannot reach current position
        }
        furthestReach = max(furthestReach, i + nums[i]);
        if (furthestReach >= n - 1) return true; // Optimization: If we can reach the end, we are done.
    }
    return true;
}

int main() {
    vector<int> nums1 = {2, 3, 1, 1, 4};
    vector<int> nums2 = {3, 2, 1, 0, 4};
    vector<int> nums3 = {0};
    vector<int> nums4 = {2, 0, 0};
    vector<int> nums5 = {2, 5, 0, 0};

    cout << "Example 1: [2, 3, 1, 1, 4]\n";
    cout << "Greedy: " << (canJumpGreedy(nums1) ? "true" : "false") << endl;
    cout << "DP (Top-Down): " << (canJumpDP(nums1) ? "true" : "false") << endl;
    cout << "DP (Bottom-Up): " << (canJumpDPBottomUp(nums1) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktrack(nums1) ? "true" : "false") << endl;
    cout << "Optimized Greedy: " << (canJumpOptimizedGreedy(nums1) ? "true" : "false") << endl;


    cout << "\nExample 2: [3, 2, 1, 0, 4]\n";
    cout << "Greedy: " << (canJumpGreedy(nums2) ? "true" : "false") << endl;
    cout << "DP (Top-Down): " << (canJumpDP(nums2) ? "true" : "false") << endl;
    cout << "DP (Bottom-Up): " << (canJumpDPBottomUp(nums2) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktrack(nums2) ? "true" : "false") << endl;
    cout << "Optimized Greedy: " << (canJumpOptimizedGreedy(nums2) ? "true" : "false") << endl;

    cout << "\nExample 3: [0]\n";
    cout << "Greedy: " << (canJumpGreedy(nums3) ? "true" : "false") << endl;
    cout << "DP (Top-Down): " << (canJumpDP(nums3) ? "true" : "false") << endl;
    cout << "DP (Bottom-Up): " << (canJumpDPBottomUp(nums3) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktrack(nums3) ? "true" : "false") << endl;
    cout << "Optimized Greedy: " << (canJumpOptimizedGreedy(nums3) ? "true" : "false") << endl;

    cout << "\nExample 4: [2, 0, 0]\n";
    cout << "Greedy: " << (canJumpGreedy(nums4) ? "true" : "false") << endl;
    cout << "DP (Top-Down): " << (canJumpDP(nums4) ? "true" : "false") << endl;
    cout << "DP (Bottom-Up): " << (canJumpDPBottomUp(nums4) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktrack(nums4) ? "true" : "false") << endl;
    cout << "Optimized Greedy: " << (canJumpOptimizedGreedy(nums4) ? "true" : "false") << endl;

    cout << "\nExample 5: [2, 5, 0, 0]\n";
    cout << "Greedy: " << (canJumpGreedy(nums5) ? "true" : "false") << endl;
    cout << "DP (Top-Down): " << (canJumpDP(nums5) ? "true" : "false") << endl;
    cout << "DP (Bottom-Up): " << (canJumpDPBottomUp(nums5) ? "true" : "false") << endl;
    cout << "Backtracking: " << (canJumpBacktrack(nums5) ? "true" : "false") << endl;
    cout << "Optimized Greedy: " << (canJumpOptimizedGreedy(nums5) ? "true" : "false") << endl;

    return 0;
}
