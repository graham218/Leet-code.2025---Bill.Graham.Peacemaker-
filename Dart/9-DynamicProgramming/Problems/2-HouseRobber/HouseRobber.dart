// Dart Solution for House Robber problem using 6 different approaches
// Covers brute force, DP, space optimization, and advanced methods

import 'dart:math';

void main() {
  List<int> houses = [2, 7, 9, 3, 1];

  print("1. Recursive: ${robRecursive(houses, houses.length - 1)}");
  print("2. Memoization: ${robMemoization(houses)}");
  print("3. Tabulation: ${robTabulation(houses)}");
  print("4. Optimized Space: ${robOptimized(houses)}");
  print("5. Iterative with Variables: ${robIterativeVars(houses)}");
  print("6. Circular Houses: ${robCircular(houses)}");
}

// 1. Recursive Approach (Brute Force)
int robRecursive(List<int> nums, int i) {
  if (i < 0) return 0;
  return max(robRecursive(nums, i - 2) + nums[i], robRecursive(nums, i - 1));
}

// 2. Memoization (Top-Down DP)
int robMemoization(List<int> nums) {
  Map<int, int> memo = {};
  int dp(int i) {
    if (i < 0) return 0;
    if (memo.containsKey(i)) return memo[i]!;
    memo[i] = max(dp(i - 2) + nums[i], dp(i - 1));
    return memo[i]!;
  }
  return dp(nums.length - 1);
}

// 3. Tabulation (Bottom-Up DP)
int robTabulation(List<int> nums) {
  if (nums.isEmpty) return 0;
  if (nums.length == 1) return nums[0];

  List<int> dp = List.filled(nums.length, 0);
  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);

  for (int i = 2; i < nums.length; i++) {
    dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
  }
  return dp.last;
}

// 4. Optimized Space DP (Only storing last two values)
int robOptimized(List<int> nums) {
  if (nums.isEmpty) return 0;
  if (nums.length == 1) return nums[0];

  int prev1 = 0, prev2 = 0;
  for (int num in nums) {
    int temp = prev1;
    prev1 = max(prev2 + num, prev1);
    prev2 = temp;
  }
  return prev1;
}

// 5. Iterative with Variables (Same as Optimized Space but simplified)
int robIterativeVars(List<int> nums) {
  int rob1 = 0, rob2 = 0;
  for (int num in nums) {
    int newRob = max(rob1 + num, rob2);
    rob1 = rob2;
    rob2 = newRob;
  }
  return rob2;
}

// 6. Circular Houses (First and Last House Connected)
int robCircular(List<int> nums) {
  if (nums.length == 1) return nums[0];
  return max(robOptimized(nums.sublist(0, nums.length - 1)),
      robOptimized(nums.sublist(1)));
}

// ----------------------
// Real-world Applications
// ----------------------
// 1. Security systems: Optimal burglary detection scheduling
// 2. Game theory: Resource collection strategies
// 3. Financial planning: Choosing non-consecutive investments
