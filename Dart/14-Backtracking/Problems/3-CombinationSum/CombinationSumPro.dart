// Advanced Dart solution for "Combination Sum" with real-world optimizations

import 'dart:collection';

void main() {
  List<int> candidates = [2, 3, 5, 7];
  int target = 8;

  print('Backtracking with Pruning: ${combinationSumBacktracking(candidates, target)}');
  print('Memoization with State Encoding: ${combinationSumMemoStateEncoding(candidates, target)}');
  print('DP with Space Optimization: ${combinationSumOptimizedDP(candidates, target)}');
  print('BFS with Level Processing: ${combinationSumBFSLevelProcessing(candidates, target)}');
  print('Parallel Processing (Simulated): ${combinationSumParallelProcessing(candidates, target)}');
  print('Hybrid Approach: ${combinationSumHybrid(candidates, target)}');
}

// Approach 1: Backtracking with Pruning
// This approach uses backtracking to explore all possible combinations.
// It sorts the candidates to enable pruning, which significantly reduces the search space.
List<List<int>> combinationSumBacktracking(List<int> candidates, int target) {
  List<List<int>> result = [];
  candidates.sort(); // Optimization: Sort candidates to prune early
  void backtrack(int start, int target, List<int> path) {
    if (target == 0) {
      result.add(List.from(path)); // Found a valid combination
      return;
    }
    for (int i = start; i < candidates.length; i++) {
      if (candidates[i] > target) break; // Pruning: If current candidate > target, no need to continue
      path.add(candidates[i]);
      backtrack(i, target - candidates[i], path); // Recursive call
      path.removeLast(); // Backtrack: Remove the last added candidate
    }
  }
  backtrack(0, target, []);
  return result;
}

// Approach 2: Memoization with State Encoding
// This approach uses memoization to store intermediate results, avoiding redundant calculations.
// The state is encoded as a string to use as a key in the memoization map.
Map<String, List<List<int>>> memo = {};
List<List<int>> combinationSumMemoStateEncoding(List<int> candidates, int target, [int start = 0]) {
  String key = '$start-$target'; // State encoding: start index and remaining target
  if (memo.containsKey(key)) return memo[key]!; // Return memoized result if available
  if (target == 0) return [[]]; // Base case: target reached
  if (target < 0) return []; // Base case: target exceeded
  List<List<int>> result = [];
  for (int i = start; i < candidates.length; i++) {
    for (var sublist in combinationSumMemoStateEncoding(candidates, target - candidates[i], i)) {
      result.add([candidates[i], ...sublist]); // Add current candidate to sublist
    }
  }
  return memo[key] = result; // Store and return the result
}

// Approach 3: Dynamic Programming with Space Optimization
// This approach uses dynamic programming to build solutions bottom-up.
// It optimizes space by storing only the necessary intermediate results.
List<List<int>> combinationSumOptimizedDP(List<int> candidates, int target) {
  List<List<List<int>>> dp = List.generate(target + 1, (_) => []); // DP table: dp[i] stores combinations for target i
  dp[0] = [[]]; // Base case: target 0 has an empty combination
  for (int num in candidates) {
    for (int i = num; i <= target; i++) {
      for (var combination in dp[i - num]) {
        dp[i].add([...combination, num]); // Add current candidate to existing combinations
      }
    }
  }
  return dp[target]; // Return combinations for the target
}

// Approach 4: BFS with Level Processing
// This approach uses Breadth-First Search (BFS) to explore combinations level by level.
// It uses a queue to manage the search process.
List<List<int>> combinationSumBFSLevelProcessing(List<int> candidates, int target) {
  List<List<int>> result = [];
  Queue<Map<String, dynamic>> queue = Queue();
  queue.add({'sum': 0, 'path': <int>[]}); // Initialize queue with starting state
  while (queue.isNotEmpty) {
    var current = queue.removeFirst();
    int sum = current['sum'] as int;
    List<int> path = List<int>.from(current['path']);
    for (int num in candidates) {
      if (path.isNotEmpty && num < path.last) continue; // Avoid duplicate combinations
      int newSum = sum + num;
      if (newSum == target) {
        result.add([...path, num]); // Found a valid combination
      } else if (newSum < target) {
        queue.add({'sum': newSum, 'path': [...path, num]}); // Enqueue next state
      }
    }
  }
  return result;
}

// Approach 5: Parallel Processing (Simulated)
// This approach simulates parallel processing using a recursive worker function.
// In a real-world scenario, this could be implemented using isolates or threads.
List<List<int>> combinationSumParallelProcessing(List<int> candidates, int target) {
  List<List<int>> result = [];
  void worker(List<int> subset, int remaining, int start) {
    if (remaining == 0) {
      result.add(List.from(subset)); // Found a valid combination
      return;
    }
    for (int i = start; i < candidates.length; i++) {
      if (candidates[i] > remaining) break;
      subset.add(candidates[i]);
      worker(subset, remaining - candidates[i], i);
      subset.removeLast();
    }
  }
  worker([], target, 0);
  return result;
}

// Approach 6: Hybrid Approach (Combining DP and Backtracking)
// This approach combines dynamic programming and backtracking for efficiency.
// It uses DP to store intermediate results and backtracking to explore combinations.
List<List<int>> combinationSumHybrid(List<int> candidates, int target) {
  Map<int, List<List<int>>> dp = {}; // DP table: dp[sum] stores combinations for sum
  void backtrack(int sum, List<int> path) {
    if (sum == target) {
      dp[sum] = dp[sum] ?? [];
      dp[sum]!.add(List.from(path));
      return;
    }
    for (int num in candidates) {
      if (sum + num > target) break;
      path.add(num);
      backtrack(sum + num, path);
      path.removeLast();
    }
  }
  backtrack(0, []);
  return dp[target] ?? [];
}