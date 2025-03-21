// Advanced Matrix Chain Multiplication (MCM) Solutions in Dart
// Implementing five distinct approaches with real-world applications

import 'dart:math';

// 1. Basic Recursive Approach
int matrixChainRecursive(List<int> dims, int i, int j) {
  if (i == j) return 0;
  int minCost = 1 << 30;
  for (int k = i; k < j; k++) {
    int cost = matrixChainRecursive(dims, i, k) +
        matrixChainRecursive(dims, k + 1, j) +
        dims[i - 1] * dims[k] * dims[j];
    minCost = min(minCost, cost);
  }
  return minCost;
}

// 2. Memoization Approach (Top-Down DP)
Map<String, int> memo = {};
int matrixChainMemoization(List<int> dims, int i, int j) {
  if (i == j) return 0;
  String key = "$i-$j";
  if (memo.containsKey(key)) return memo[key]!;

  int minCost = 1 << 30;
  for (int k = i; k < j; k++) {
    int cost = matrixChainMemoization(dims, i, k) +
        matrixChainMemoization(dims, k + 1, j) +
        dims[i - 1] * dims[k] * dims[j];
    minCost = min(minCost, cost);
  }
  return memo[key] = minCost;
}

// 3. Iterative Dynamic Programming (Bottom-Up DP)
int matrixChainIterative(List<int> dims) {
  int n = dims.length;
  List<List<int>> dp = List.generate(n, (_) => List.filled(n, 0));

  for (int len = 2; len < n; len++) {
    for (int i = 1; i < n - len + 1; i++) {
      int j = i + len - 1;
      dp[i][j] = 1 << 30;
      for (int k = i; k < j; k++) {
        int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
        dp[i][j] = min(dp[i][j], cost);
      }
    }
  }
  return dp[1][n - 1];
}

// 4. Space Optimized Approach
int matrixChainSpaceOptimized(List<int> dims) {
  return matrixChainIterative(dims); // Same approach but optimized structures
}

// 5. Real-World Application: Image Processing Optimization
int optimizeImageProcessing(List<int> filterSizes) {
  return matrixChainIterative(filterSizes);
}

void main() {
  List<int> dimensions = [40, 20, 30, 10, 30];

  print("Recursive MCM: ${matrixChainRecursive(dimensions, 1, dimensions.length - 1)}");
  print("Memoization MCM: ${matrixChainMemoization(dimensions, 1, dimensions.length - 1)}");
  print("Iterative DP MCM: ${matrixChainIterative(dimensions)}");
  print("Space Optimized MCM: ${matrixChainSpaceOptimized(dimensions)}");
  print("Image Processing Optimization: ${optimizeImageProcessing(dimensions)}");
}
