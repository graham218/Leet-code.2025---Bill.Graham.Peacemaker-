// Dart solution for "Combination Sum" using different approaches

import 'dart:collection';

void main() {
  List<int> candidates = [2, 3, 6, 7];
  int target = 7;

  print('Backtracking: ${combinationSumBacktracking(candidates, target)}');
  print('Memoization: ${combinationSumMemoization(candidates, target)}');
  print('DP: ${combinationSumDP(candidates, target)}');
  print('Iterative BFS: ${combinationSumBFS(candidates, target)}');
  print('Bitmasking: ${combinationSumBitmask(candidates, target)}');
}

// Approach 1: Backtracking
// This approach uses a recursive function to explore all possible combinations.
// It maintains a 'path' to store the current combination and recursively calls itself
// with the remaining target value.
List<List<int>> combinationSumBacktracking(List<int> candidates, int target) {
  List<List<int>> result = [];
  void backtrack(int start, int target, List<int> path) {
    if (target == 0) {
      // If the target is reached, add the current path to the result.
      result.add(List.from(path));
      return;
    }
    for (int i = start; i < candidates.length; i++) {
      if (candidates[i] <= target) {
        // If the current candidate is less than or equal to the remaining target,
        // add it to the path and recursively call backtrack.
        path.add(candidates[i]);
        backtrack(i, target - candidates[i], path);
        // Remove the last added candidate to backtrack.
        path.removeLast();
      }
    }
  }
  backtrack(0, target, []);
  return result;
}

// Approach 2: Memoization (Top-down DP)
// This approach uses memoization to store the results of subproblems to avoid redundant calculations.
// It uses a map 'memo' to store the results.
Map<String, List<List<int>>> memo = {};
List<List<int>> combinationSumMemoization(List<int> candidates, int target, [int start = 0]) {
  String key = '$start-$target';
  if (memo.containsKey(key)) return memo[key]!;
  if (target == 0) return [[]];
  if (target < 0) return [];
  List<List<int>> result = [];
  for (int i = start; i < candidates.length; i++) {
    for (var sublist in combinationSumMemoization(candidates, target - candidates[i], i)) {
      result.add([candidates[i], ...sublist]);
    }
  }
  return memo[key] = result;
}

// Approach 3: Dynamic Programming (Bottom-up DP)
// This approach uses dynamic programming to build up the solution from the bottom up.
// It creates a 'dp' table to store the results of subproblems.
List<List<int>> combinationSumDP(List<int> candidates, int target) {
  List<List<List<int>>> dp = List.generate(target + 1, (_) => []);
  dp[0] = [[]];
  for (int num in candidates) {
    for (int i = num; i <= target; i++) {
      for (var combination in dp[i - num]) {
        dp[i].add([...combination, num]);
      }
    }
  }
  return dp[target];
}

// Approach 4: Iterative BFS
// This approach uses breadth-first search to explore all possible combinations.
// It uses a queue to store the states of the search.
List<List<int>> combinationSumBFS(List<int> candidates, int target) {
  List<List<int>> result = [];
  Queue<Map<String, dynamic>> queue = Queue();
  queue.add({'sum': 0, 'path': <int>[]}); // (current sum, path)
  while (queue.isNotEmpty) {
    var current = queue.removeFirst();
    int sum = current['sum'] as int;
    List<int> path = List<int>.from(current['path']);
    for (int num in candidates) {
      if (path.isNotEmpty && num < path.last) continue;
      int newSum = sum + num;
      if (newSum == target) {
        result.add([...path, num]);
      } else if (newSum < target) {
        queue.add({'sum': newSum, 'path': [...path, num]});
      }
    }
  }
  return result;
}

// Approach 5: Bitmasking (Subset Generation)
// This approach uses bitmasking to generate all possible subsets of the candidates.
// It checks if the sum of each subset equals the target.
List<List<int>> combinationSumBitmask(List<int> candidates, int target) {
  Set<List<int>> result = {};
  int n = candidates.length;
  for (int mask = 0; mask < (1 << n); mask++) {
    List<int> subset = [];
    int sum = 0;
    for (int i = 0; i < n; i++) {
      if ((mask & (1 << i)) != 0) {
        subset.add(candidates[i]);
        sum += candidates[i];
      }
    }
    if (sum == target) {
      subset.sort();
      result.add(subset);
    }
  }
  return result.toList();
}