#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // For std::accumulate

using namespace std;

// 1. Top-Down Recursion with Memoization
//    - Time Complexity: O(n), where n is the number of houses.
//    - Space Complexity: O(n) for the memoization table and recursion stack.
int robTopDown(const vector<int>& nums, int i, vector<int>& memo) {
    if (i < 0) {
        return 0;
    }
    if (memo[i] != -1) {
        return memo[i];
    }

    // Option 1: Rob the current house i and skip the previous house (i-1).
    int robHouse = nums[i] + robTopDown(nums, i - 2, memo);
    // Option 2: Skip the current house i and consider the maximum from previous houses.
    int skipHouse = robTopDown(nums, i - 1, memo);

    memo[i] = max(robHouse, skipHouse); // Store the maximum for future use.
    return memo[i];
}

int rob_top_down(vector<int>& nums) {
    if (nums.empty()) return 0;
    vector<int> memo(nums.size(), -1); // Initialize memoization table with -1.
    return robTopDown(nums, nums.size() - 1, memo);
}

// 2. Bottom-Up Dynamic Programming (Tabulation) - Optimized
//    - Time Complexity: O(n)
//    - Space Complexity: O(1) - Constant space
int robBottomUpOptimized(vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];

    int prev2 = 0;       // Represents dp[i-2]
    int prev1 = 0;       // Represents dp[i-1]
    int current;

    for (int i = 0; i < nums.size(); ++i) {
        // Calculate the maximum amount that can be robbed up to house i.
        current = max(prev1, prev2 + nums[i]); // Either rob house i or don't.
        prev2 = prev1;  // Update prev2 (dp[i-2])
        prev1 = current; // Update prev1 (dp[i-1])
    }
    return prev1; // The result is stored in prev1 after the loop.
}

// 3. Bottom-Up Dynamic Programming (Tabulation) - Array
//    - Time Complexity: O(n)
//    - Space Complexity: O(n)
int robBottomUpArray(vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];

    vector<int> dp(nums.size()); // dp[i] stores the max loot up to house i.
    dp[0] = nums[0];            // Base case: Only one house.
    dp[1] = max(nums[0], nums[1]); // Base case: Two houses - rob the one with max value.

    for (int i = 2; i < nums.size(); ++i) {
        // dp[i] is the maximum of:
        // 1. Robbing the current house i and adding it to the loot from i-2.
        // 2. Not robbing house i and taking the best loot from i-1.
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }
    return dp[nums.size() - 1]; // Result: max loot up to the last house.
}

// 4.  Recursion (Plain Recursion - Exceeds Time Limit for larger inputs)
//     - Time Complexity: O(2^n) - Exponential (very slow for larger n)
//     - Space Complexity: O(n) -  Due to the recursion call stack.
int robRecursive(const vector<int>& nums, int i) {
    if (i < 0) {
        return 0;
    }
    // Option 1: Rob current house and skip the previous
    int robHouse = nums[i] + robRecursive(nums, i - 2);
    // Option 2: Skip current house
    int skipHouse = robRecursive(nums, i - 1);
    return max(robHouse, skipHouse);
}

int rob_recursive(vector<int>& nums) {
    if (nums.empty()) return 0;
    return robRecursive(nums, nums.size() - 1);
}

// 5. Iterative with two variables, similar to optimized bottom up, but written slightly differently
int robIterative(vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];

    int rob = nums[0]; // Max loot including the current house
    int notRob = 0;    // Max loot excluding the current house

    for (int i = 1; i < nums.size(); ++i) {
        int newRob = max(notRob + nums[i], rob); // Current house robbed
        int newNotRob = max(rob, notRob);    // Current house not robbed

        rob = newRob;
        notRob = newNotRob;
    }
    return rob;
}

int main() {
    vector<int> houses = {2, 7, 9, 3, 1}; // Example house values

    cout << "House Robber Problem" << endl;
    cout << "House values: ";
    for (int val : houses) {
        cout << val << " ";
    }
    cout << endl;

    cout << "\n1. Top-Down Recursion with Memoization: " << rob_top_down(houses) << endl;
    cout << "2. Bottom-Up Dynamic Programming (Optimized): " << robBottomUpOptimized(houses) << endl;
    cout << "3. Bottom-Up Dynamic Programming (Array): " << robBottomUpArray(houses) << endl;
    cout << "4. Plain Recursion: " << rob_recursive(houses) << endl;
    cout << "5. Iterative with two variables: " << robIterative(houses) << endl;

    return 0;
}
