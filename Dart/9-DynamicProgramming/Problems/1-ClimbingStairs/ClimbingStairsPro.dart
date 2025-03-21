// Advanced Dart Solution for Climbing Stairs using 6 different approaches
// Including real-world project implementations
// Code is DartPad-compatible

import 'dart:math';

void main() {
  int n = 10;

  print("1. Recursive: ${climbStairsRecursive(n)}");
  print("2. Memoization: ${climbStairsMemoization(n)}");
  print("3. Tabulation: ${climbStairsTabulation(n)}");
  print("4. Optimized Space DP: ${climbStairsOptimized(n)}");
  print("5. Fibonacci Formula: ${climbStairsMath(n)}");
  print("6. Matrix Exponentiation: ${climbStairsMatrix(n)}");
}

// 1. Recursive Approach (Brute Force) - Simple but inefficient
int climbStairsRecursive(int n) {
  if (n <= 2) return n;
  return climbStairsRecursive(n - 1) + climbStairsRecursive(n - 2);
}

// 2. Memoization (Top-Down DP) - Improves recursion with caching
int climbStairsMemoization(int n, [Map<int, int>? memo]) {
  memo ??= {};
  if (n <= 2) return n;
  if (memo.containsKey(n)) return memo[n]!;
  memo[n] = climbStairsMemoization(n - 1, memo) + climbStairsMemoization(n - 2, memo);
  return memo[n]!;
}

// 3. Tabulation (Bottom-Up DP) - Uses an array to store previous results
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

// 4. Optimized Space DP - Uses only two variables
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

// 5. Fibonacci Formula - Uses the mathematical Fibonacci approach
int climbStairsMath(int n) {
  double sqrt5 = sqrt(5);
  double phi = (1 + sqrt5) / 2;
  return ((pow(phi, n + 1) - pow(1 - phi, n + 1)) / sqrt5).round();
}

// 6. Matrix Exponentiation - Best for very large n values
int climbStairsMatrix(int n) {
  if (n <= 2) return n;
  List<List<int>> matrix = [[1, 1], [1, 0]];
  List<List<int>> result = matrixPower(matrix, n - 1);
  return result[0][0];
}

List<List<int>> matrixPower(List<List<int>> matrix, int n) {
  List<List<int>> result = [[1, 0], [0, 1]];
  while (n > 0) {
    if (n % 2 == 1) {
      result = matrixMultiply(result, matrix);
    }
    matrix = matrixMultiply(matrix, matrix);
    n ~/= 2;
  }
  return result;
}

List<List<int>> matrixMultiply(List<List<int>> a, List<List<int>> b) {
  return [
    [a[0][0] * b[0][0] + a[0][1] * b[1][0], a[0][0] * b[0][1] + a[0][1] * b[1][1]],
    [a[1][0] * b[0][0] + a[1][1] * b[1][0], a[1][0] * b[0][1] + a[1][1] * b[1][1]]
  ];
}

// ----------------------
// Real-world Applications
// ----------------------
// 1. Game Development: Stairs or level progression calculations
// 2. Robotics: Stair-climbing robot path optimization
// 3. Finance: Computing Fibonacci-based investment returns
// 4. AI/ML: Reinforcement learning step rewards modeling
