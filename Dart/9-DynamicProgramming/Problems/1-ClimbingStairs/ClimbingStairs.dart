// Dart Solution for Climbing Stairs using 5 different approaches
import 'dart:math';
void main() {
  int n = 10;
  print("Recursive: ${climbStairsRecursive(n)}");
  print("Memoization: ${climbStairsMemoization(n)}");
  print("Tabulation: ${climbStairsTabulation(n)}");
  print("Optimized Space: ${climbStairsOptimized(n)}");
  print("Mathematical Formula: ${climbStairsMath(n)}");
}

// 1. Recursive Approach (Brute Force)
int climbStairsRecursive(int n) {
  if (n <= 2) return n;
  return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
}

// 2. Memoization (Top-Down DP)
int climbStairsMemoization(int n, [Map<int, int>? memo]) {
  memo ??= {};
  if (n <= 2) return n;
  if (memo.containsKey(n)) return memo[n]!;
  memo[n] = climbStairsMemoization(n - 1, memo) + climbStairsMemoization(n - 2, memo);
  return memo[n]!;
}

// 3. Tabulation (Bottom-Up DP)
int climbStairsTabulation(int n) {
  if (n <= 2) return n;
  List<int> dp = List.filled(n + 1, 0);
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

// 4. Optimized Space DP
int climbStairsOptimized(int n) {
  if (n <= 2) return n;
  int prev1 = 1, prev2 = 2;
  for (int i = 3; i <= n; i++) {
    int curr = prev1 + prev2;
    prev1 = prev2;
    prev2 = curr;
  }
  return prev2;
}

// 5. Mathematical (Fibonacci Formula)
int climbStairsMath(int n) {
  double sqrt5 = sqrt(5);
  double phi = (1 + sqrt5) / 2;
  return ((pow(phi, n + 1) - pow(1 - phi, n + 1)) / sqrt5).round();
}
