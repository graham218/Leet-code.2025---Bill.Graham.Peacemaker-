#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // for std::accumulate

using namespace std;

// 1. Recursive Approach (Basic)
//    - Time Complexity: O(2^n) - Exponential (due to overlapping subproblems)
//    - Space Complexity: O(n) - Call stack depth in recursion
//    - Real-world application:  Conceptual understanding of DP, good for teaching basic recursion.  NOT suitable for large datasets.
int robRecursive(vector<int>& nums, int i) {
    if (i < 0) return 0;
    if (i == 0) return nums[0];

    // Choice: Rob current house or skip it
    int robHouse = nums[i] + robRecursive(nums, i - 2); // Rob current, skip previous
    int skipHouse = robRecursive(nums, i - 1);         // Skip current, consider previous

    return max(robHouse, skipHouse);
}

// 2. Memoization (Top-Down DP)
//    - Time Complexity: O(n) - Each subproblem is solved only once
//    - Space Complexity: O(n) - Memoization table (dp) + recursion stack
//    - Real-world application:  Moderately sized datasets where repeated calculations are costly.  Improves upon pure recursion.
int robMemo(vector<int>& nums, int i, vector<int>& dp) {
    if (i < 0) return 0;
    if (i == 0) return nums[0];

    if (dp[i] != -1) {
        return dp[i]; // Return stored result if available
    }

    int robHouse = nums[i] + robMemo(nums, i - 2, dp);
    int skipHouse = robMemo(nums, i - 1, dp);

    dp[i] = max(robHouse, skipHouse); // Store the result
    return dp[i];
}

// 3. Tabulation (Bottom-Up DP)
//    - Time Complexity: O(n) - Iterative solution, visits each house once
//    - Space Complexity: O(n) - DP table to store results
//    - Real-world application:  Standard DP approach, efficient for medium to large datasets.  More efficient than memoization (no recursion overhead).
int robTabulation(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]); // Careful with base cases

    for (int i = 2; i < n; ++i) {
        dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
    }
    return dp[n - 1];
}

// 4. Tabulation with Space Optimization (Iterative)
//    - Time Complexity: O(n) - Still iterates through the houses once
//    - Space Complexity: O(1) - Uses only a constant amount of extra space
//    - Real-world application:  Most space-efficient solution, crucial for very large datasets or memory-constrained environments (e.g., embedded systems).
int robOptimized(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int prev2 = 0;       // Represents dp[i-2]
    int prev1 = nums[0]; // Represents dp[i-1]
    int current;

    for (int i = 1; i < n; ++i) {
        current = max(nums[i] + (i > 1 ? prev2 : 0), prev1); //Simulates the DP relation
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}

// 5. Divide and Conquer (with Optimization for House Robber II variant)
//    - Time Complexity: O(n) -  Linear time due to the nature of the problem.
//    - Space Complexity: O(n) -  In the worst case, the recursion depth can go up to n/2.
//    - Real-world application: Useful for adapting the solution to variations of the problem, such as the "House Robber II" problem (houses in a circle).
//    - This approach divides the problem into two subproblems:
//        1. Rob houses from 0 to n-2 (excluding the last house).
//        2. Rob houses from 1 to n-1 (excluding the first house).
//    - The maximum of the two results is the final answer.
int robDivideConquer(vector<int>& nums, int start, int end) {
      if (start > end) return 0;
      if (start == end) return nums[start];

      int prev2 = 0;
      int prev1 = nums[start];
      int current;

      for (int i = start + 1; i <= end; ++i) {
          current = max(nums[i] + (i - start > 1 ? prev2 : 0), prev1);
          prev2 = prev1;
          prev1 = current;
      }
      return prev1;
}

int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return max(nums[0], nums[1]);
    return max(robDivideConquer(nums, 0, n - 2), robDivideConquer(nums, 1, n - 1));
}

int main() {
    vector<int> houses = {2, 7, 9, 3, 1};

    cout << "Recursive Approach: " << robRecursive(houses, houses.size() - 1) << endl;

    vector<int> dpMemo(houses.size(), -1); // Initialize memoization table
    cout << "Memoization Approach: " << robMemo(houses, houses.size() - 1, dpMemo) << endl;

    cout << "Tabulation Approach: " << robTabulation(houses) << endl;
    cout << "Optimized Approach: " << robOptimized(houses) << endl;
    cout << "Divide and Conquer Approach: " << rob(houses) << endl;


    // Example with a larger input
    vector<int> largeInput = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    cout << "Optimized Approach (Large Input): " << robOptimized(largeInput) << endl;

    // Example with all zeros
    vector<int> zeroInput = {0, 0, 0, 0, 0};
    cout << "Optimized Approach (Zero Input): " << robOptimized(zeroInput) << endl;

    // Example with single house
    vector<int> singleInput = {5};
    cout << "Optimized Approach (Single Input): " << robOptimized(singleInput) << endl;

    return 0;
}
