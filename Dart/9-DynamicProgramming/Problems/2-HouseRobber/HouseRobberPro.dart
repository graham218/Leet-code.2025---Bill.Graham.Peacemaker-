// Advanced Dart Solution for House Robber Problem
// Six different approaches with enhanced efficiency and real-world applications

import 'dart:math';

void main() {
  List<int> houses = [2, 7, 9, 3, 1, 8, 4, 6, 5];

  print("1. Recursive: ${robRecursive(houses, houses.length - 1)}");
  print("2. Memoization: ${robMemoization(houses)}");
  print("3. Tabulation: ${robTabulation(houses)}");
  print("4. Optimized Space: ${robOptimized(houses)}");
  print("5. Circular Houses: ${robCircular(houses)}");
  print("6. Graph-Based Robbery: ${robGraph(houses)}");
}

// 1. Recursive Approach (Brute Force) - Basic recursion
int robRecursive(List<int> nums, int i) {
  if (i < 0) return 0;
  return max(robRecursive(nums, i - 2) + nums[i], robRecursive(nums, i - 1));
}

// 2. Memoization (Top-Down DP) - Uses caching to optimize recursion
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

// 3. Tabulation (Bottom-Up DP) - Iterative approach with DP table
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

// 4. Optimized Space DP - Reduces space complexity from O(n) to O(1)
int robOptimized(List<int> nums) {
  if (nums.isEmpty) return 0;
  int prev1 = 0, prev2 = 0;
  for (int num in nums) {
    int curr = max(prev1 + num, prev2);
    prev1 = prev2;
    prev2 = curr;
  }
  return prev2;
}

// 5. Circular Houses (First and Last House Connected) - Special case handling
int robCircular(List<int> nums) {
  if (nums.length == 1) return nums[0];
  return max(robOptimized(nums.sublist(0, nums.length - 1)), robOptimized(nums.sublist(1)));
}

// 6. Graph-Based Robbery (House Connection Network)
int robGraph(List<int> nums) {
  if (nums.isEmpty) return 0;
  Map<int, List<int>> graph = {};
  for (int i = 0; i < nums.length; i++) {
    graph[i] = [i - 2, i - 3];
  }
  Map<int, int> memo = {};
  int dfs(int i) {
    if (i < 0) return 0;
    if (memo.containsKey(i)) return memo[i]!;
    int maxRob = nums[i];
    for (int neighbor in graph[i]!) {
      maxRob = max(maxRob, nums[i] + dfs(neighbor));
    }
    memo[i] = maxRob;
    return maxRob;
  }
  return dfs(nums.length - 1);
}

// ----------------------
// New Real-world Applications
// ----------------------
// 1. Cybersecurity: Detecting optimal hacking patterns in networks.
// 2. Inventory Management: Selecting non-consecutive peak restocking times.
// 3. Smart Cities: Maximizing patrol coverage of autonomous security drones.
// 4. AI-driven Heist Planning: Optimal selection of targets in bank heists.
// 5. Cloud Resource Allocation: Optimal non-overlapping job scheduling.
// 6. Genomics Research: Identifying non-adjacent genes for mutation detection.
