// Dart Solution for Coin Change Problem (DartPad Compatible)
// Implements 5 different approaches for solving the problem

import 'dart:math';
import 'dart:collection';

void main() {
  List<int> coins = [1, 2, 5];
  int amount = 11;

  print("1. Recursive: ${coinChangeRecursive(coins, amount)}");
  print("2. Memoization: ${coinChangeMemoization(coins, amount)}");
  print("3. Tabulation: ${coinChangeTabulation(coins, amount)}");
  print("4. Optimized BFS: ${coinChangeBFS(coins, amount)}");
  print("5. Greedy + DP: ${coinChangeGreedyDP(coins, amount)}");
}

const int INF = 1000000; // Large integer value to replace infinity

// 1. Recursive Approach (Brute Force)
int coinChangeRecursive(List<int> coins, int amount) {
  if (amount == 0) return 0;
  if (amount < 0) return -1;

  int minCoins = INF;
  for (int coin in coins) {
    int res = coinChangeRecursive(coins, amount - coin);
    if (res >= 0) minCoins = min(minCoins, res + 1);
  }
  return minCoins == INF ? -1 : minCoins;
}

// 2. Memoization (Top-Down DP)
int coinChangeMemoization(List<int> coins, int amount) {
  Map<int, int> memo = {};
  int dp(int rem) {
    if (rem == 0) return 0;
    if (rem < 0) return -1;
    if (memo.containsKey(rem)) return memo[rem]!;

    int minCoins = INF;
    for (int coin in coins) {
      int res = dp(rem - coin);
      if (res >= 0) minCoins = min(minCoins, res + 1);
    }
    memo[rem] = (minCoins == INF) ? -1 : minCoins;
    return memo[rem]!;
  }
  return dp(amount);
}

// 3. Tabulation (Bottom-Up DP)
int coinChangeTabulation(List<int> coins, int amount) {
  List<int> dp = List.filled(amount + 1, INF);
  dp[0] = 0;
  for (int i = 1; i <= amount; i++) {
    for (int coin in coins) {
      if (i >= coin) dp[i] = min(dp[i], dp[i - coin] + 1);
    }
  }
  return dp[amount] == INF ? -1 : dp[amount];
}

// 4. Optimized BFS Approach
int coinChangeBFS(List<int> coins, int amount) {
  if (amount == 0) return 0;
  Queue<int> queue = Queue();
  Set<int> visited = {};
  queue.add(amount);
  visited.add(amount);
  int steps = 0;

  while (queue.isNotEmpty) {
    int size = queue.length;
    for (int i = 0; i < size; i++) {
      int current = queue.removeFirst();
      for (int coin in coins) {
        int next = current - coin;
        if (next == 0) return steps + 1;
        if (next > 0 && !visited.contains(next)) {
          queue.add(next);
          visited.add(next);
        }
      }
    }
    steps++;
  }
  return -1;
}

// 5. Greedy + DP Hybrid Approach
int coinChangeGreedyDP(List<int> coins, int amount) {
  coins.sort((a, b) => b - a);
  int minCoins = INF;

  void backtrack(int index, int remaining, int count) {
    if (remaining == 0) {
      minCoins = min(minCoins, count);
      return;
    }
    if (index == coins.length) return;
    for (int i = remaining ~/ coins[index]; i >= 0 && count + i < minCoins; i--) {
      backtrack(index + 1, remaining - i * coins[index], count + i);
    }
  }
  backtrack(0, amount, 0);
  return minCoins == INF ? -1 : minCoins;
}

// ----------------------
// Real-world Applications
// ----------------------
// 1. ATM cash dispensing: Finding the optimal way to dispense cash.
// 2. E-commerce payment systems: Optimizing payment options with different denominations.
// 3. Financial planning: Minimizing transaction fees using optimal change distribution.
// 4. Game development: Managing in-game currency exchange systems.
// 5. Logistics and inventory: Optimizing packaging and supply chain management.
