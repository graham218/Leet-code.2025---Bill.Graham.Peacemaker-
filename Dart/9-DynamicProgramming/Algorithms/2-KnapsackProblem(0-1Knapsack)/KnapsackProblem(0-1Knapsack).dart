import 'dart:math';

// Knapsack Problem (0/1 Knapsack) using Dynamic Programming in Dart

// 1. Recursive Approach (Exponential Time Complexity)
// This is the most straightforward approach, but it recalculates the same subproblems multiple times,
// leading to exponential time complexity.
int knapsackRecursive(List<int> weights, List<int> values, int capacity, int n) {
  // Base case: If there are no items (n == 0) or the capacity is zero, the maximum value is 0.
  if (n == 0 || capacity == 0) return 0;

  // If the weight of the current item is greater than the remaining capacity,
  // we cannot include it, so we move to the next item.
  if (weights[n - 1] > capacity) {
    return knapsackRecursive(weights, values, capacity, n - 1);
  } else {
    // Otherwise, we have two choices:
    // 1. Include the current item: Add its value and recurse with the remaining capacity and items.
    // 2. Exclude the current item: Recurse with the same capacity and remaining items.
    // We return the maximum of these two choices.
    return max(
      values[n - 1] + knapsackRecursive(weights, values, capacity - weights[n - 1], n - 1),
      knapsackRecursive(weights, values, capacity, n - 1),
    );
  }
}

// 2. Memoization (Top-Down DP)
// Memoization optimizes the recursive approach by storing the results of subproblems
// in a map (memo) to avoid recalculations.
Map<String, int> memo = {};
int knapsackMemoization(List<int> weights, List<int> values, int capacity, int n) {
  // Base case: If there are no items or the capacity is zero, the maximum value is 0.
  if (n == 0 || capacity == 0) return 0;

  // Create a unique key for the current subproblem.
  String key = "$n-$capacity";

  // If the result is already in the memo, return it.
  if (memo.containsKey(key)) return memo[key]!;

  // If the weight of the current item is greater than the remaining capacity,
  // we cannot include it, so we recurse with the next item and store the result.
  if (weights[n - 1] > capacity) {
    memo[key] = knapsackMemoization(weights, values, capacity, n - 1);
  } else {
    // Otherwise, we have two choices: include or exclude the current item.
    // We store the maximum of these two choices in the memo.
    memo[key] = max(
      values[n - 1] + knapsackMemoization(weights, values, capacity - weights[n - 1], n - 1),
      knapsackMemoization(weights, values, capacity, n - 1),
    );
  }
  // Return the stored result.
  return memo[key]!;
}

// 3. Tabulation (Bottom-Up DP)
// Tabulation builds a table (dp) to store the results of subproblems in a bottom-up manner.
// It avoids recursion and typically has better performance than memoization.
int knapsackTabulation(List<int> weights, List<int> values, int capacity) {
  int n = weights.length;
  // Create a 2D list (dp) to store the maximum values for different capacities and items.
  // dp[i][w] represents the maximum value that can be obtained with the first i items and capacity w.
  List<List<int>> dp = List.generate(n + 1, (_) => List.filled(capacity + 1, 0));

  // Iterate through the items and capacities.
  for (int i = 1; i <= n; i++) {
    for (int w = 1; w <= capacity; w++) {
      // If the weight of the current item is less than or equal to the current capacity,
      // we have two choices: include or exclude the item.
      if (weights[i - 1] <= w) {
        // We choose the maximum of including or excluding the item.
        dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
      } else {
        // If the weight is greater than the capacity, we cannot include the item.
        dp[i][w] = dp[i - 1][w];
      }
    }
  }
  // The result is stored in the bottom-right cell of the dp table.
  return dp[n][capacity];
}

// 4. Space Optimized DP
// This approach optimizes the tabulation method by using only two rows (prev and curr)
// instead of the entire dp table. This reduces the space complexity from O(n*capacity) to O(capacity).
int knapsackSpaceOptimized(List<int> weights, List<int> values, int capacity) {
  int n = weights.length;
  // Create two 1D lists to store the previous and current row values.
  List<int> prev = List.filled(capacity + 1, 0);
  List<int> curr = List.filled(capacity + 1, 0);

  // Iterate through the items and capacities.
  for (int i = 1; i <= n; i++) {
    for (int w = 1; w <= capacity; w++) {
      // If the weight of the current item is less than or equal to the current capacity,
      // we have two choices: include or exclude the item.
      if (weights[i - 1] <= w) {
        // We choose the maximum of including or excluding the item.
        curr[w] = max(values[i - 1] + prev[w - weights[i - 1]], prev[w]);
      } else {
        // If the weight is greater than the capacity, we cannot include the item.
        curr[w] = prev[w];
      }
    }
    // Update the previous row with the current row values.
    prev = List.from(curr);
  }
  // The result is stored in the last row (prev).
  return prev[capacity];
}

// 5. Iterative Greedy Approximation (Not Optimal for 0/1 Knapsack, but useful for Fractional Knapsack)
// This greedy approach sorts the items by their value-to-weight ratio and selects items
// in that order until the capacity is full. It's not optimal for 0/1 Knapsack because
// it doesn't consider all possible combinations, but it works well for Fractional Knapsack
// where you can take fractions of items.
int knapsackGreedy(List<int> weights, List<int> values, int capacity) {
  // Create a list of indices and sort them by the value-to-weight ratio in descending order.
  List<int> indices = List.generate(weights.length, (i) => i);
  indices.sort((a, b) => (values[b] / weights[b]).compareTo(values[a] / weights[a]));

  int totalValue = 0, remainingCapacity = capacity;
  // Iterate through the sorted items and select them if they fit within the remaining capacity.
  for (int i in indices) {
    if (weights[i] <= remainingCapacity) {
      totalValue += values[i];
      remainingCapacity -= weights[i];
    }
  }
  return totalValue;
}

void main() {
  List<int> weights = [2, 3, 4, 5];
  List<int> values = [3, 4, 5, 6];
  int capacity = 5;

  print("Recursive: ${knapsackRecursive(weights, values, capacity, weights.length)}");
  print("Memoization: ${knapsackMemoization(weights, values, capacity, weights.length)}");
  print("Tabulation: ${knapsackTabulation(weights, values, capacity)}");
  print("Space Optimized: ${knapsackSpaceOptimized(weights, values, capacity)}");
  print("Greedy Approximation: ${knapsackGreedy(weights, values, capacity)}");
}