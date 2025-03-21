// Advanced 0/1 Knapsack Problem Solutions in Dart
// Implementing six distinct and innovative approaches with real-world applications

import 'dart:math';

// 1. Pure Functional Approach (Recursive without Mutation)
int knapsackFunctional(List<int> weights, List<int> values, int capacity, int n) {
  return (n == 0 || capacity == 0)
      ? 0
      : (weights[n - 1] > capacity)
      ? knapsackFunctional(weights, values, capacity, n - 1)
      : max(
      values[n - 1] + knapsackFunctional(weights, values, capacity - weights[n - 1], n - 1),
      knapsackFunctional(weights, values, capacity, n - 1));
}

// 2. Dynamic Programming with Optimized Iterative Approach
int knapsackIterative(List<int> weights, List<int> values, int capacity) {
  int n = weights.length;
  List<int> dp = List.filled(capacity + 1, 0);

  for (int i = 0; i < n; i++) {
    for (int w = capacity; w >= weights[i]; w--) {
      dp[w] = max(dp[w], values[i] + dp[w - weights[i]]);
    }
  }
  return dp[capacity];
}

// 3. Bitmasking Approach (for small constraints)
int knapsackBitmasking(List<int> weights, List<int> values, int capacity) {
  int n = weights.length, maxValue = 0;
  for (int mask = 0; mask < (1 << n); mask++) {
    int totalWeight = 0, totalValue = 0;
    for (int i = 0; i < n; i++) {
      if ((mask & (1 << i)) != 0) {
        totalWeight += weights[i];
        totalValue += values[i];
      }
    }
    if (totalWeight <= capacity) maxValue = max(maxValue, totalValue);
  }
  return maxValue;
}

// 4. Memoization Approach (Top-down DP)
Map<String, int> memo = {};
int knapsackMemoization(List<int> weights, List<int> values, int capacity, int n) {
  if (n == 0 || capacity == 0) return 0;
  String key = "$n-$capacity";
  if (memo.containsKey(key)) return memo[key]!;

  if (weights[n - 1] > capacity) {
    return memo[key] = knapsackMemoization(weights, values, capacity, n - 1);
  }
  return memo[key] = max(
      values[n - 1] + knapsackMemoization(weights, values, capacity - weights[n - 1], n - 1),
      knapsackMemoization(weights, values, capacity, n - 1)
  );
}

// 5. AI-Based Evolutionary Approach (Simulating Natural Selection)
int knapsackGeneticAI(List<int> weights, List<int> values, int capacity) {
  Random rand = Random();
  int bestValue = 0;
  for (int i = 0; i < 1000; i++) {
    List<int> individual = List.generate(weights.length, (_) => rand.nextInt(2));
    int weightSum = 0, valueSum = 0;
    for (int j = 0; j < weights.length; j++) {
      if (individual[j] == 1) {
        weightSum += weights[j];
        valueSum += values[j];
      }
    }
    if (weightSum <= capacity) bestValue = max(bestValue, valueSum);
  }
  return bestValue;
}

// 6. Real-World Application: Cloud Storage Optimization
// Simulating file storage selection based on price vs space trade-off
int knapsackCloudStorage(List<int> fileSizes, List<int> fileValues, int maxStorage) {
  return knapsackIterative(fileSizes, fileValues, maxStorage);
}

void main() async {
  List<int> weights = [1, 3, 4, 5];
  List<int> values = [10, 40, 50, 70];
  int capacity = 7;

  print("Functional: ${knapsackFunctional(weights, values, capacity, weights.length)}");
  print("Iterative: ${knapsackIterative(weights, values, capacity)}");
  print("Bitmasking: ${knapsackBitmasking(weights, values, capacity)}");
  print("Memoization: ${knapsackMemoization(weights, values, capacity, weights.length)}");
  print("Genetic AI: ${knapsackGeneticAI(weights, values, capacity)}");
  print("Cloud Storage Optimization: ${knapsackCloudStorage(weights, values, capacity)}");
}
