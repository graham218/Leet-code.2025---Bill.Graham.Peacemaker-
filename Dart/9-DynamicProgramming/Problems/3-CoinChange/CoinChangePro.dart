// Advanced Dart Solution for Coin Change Problem (DartPad Compatible)
// Implements 6 different approaches for solving the problem with real-world applications

import 'dart:math';
import 'dart:collection';

void main() {
  List<int> coins = [1, 2, 5, 10];
  int amount = 27;

  print("1. Recursive: ${coinChangeRecursive(coins, amount)}");
  print("2. Memoization: ${coinChangeMemoization(coins, amount)}");
  print("3. Tabulation: ${coinChangeTabulation(coins, amount)}");
  print("4. BFS Approach: ${coinChangeBFS(coins, amount)}");
  print("5. Greedy + Backtracking: ${coinChangeGreedyBacktrack(coins, amount)}");
  print("6. Heap-Based Dijkstra Approach: ${coinChangeHeapDijkstra(coins, amount)}");
}

const int INF = 1000000;

// 1. Recursive Approach
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
int coinChangeMemoization(List<int> coins, int amount, [Map<int, int>? memo]) {
  memo ??= {};
  if (amount == 0) return 0;
  if (amount < 0) return -1;
  if (memo.containsKey(amount)) return memo[amount]!;

  int minCoins = INF;
  for (int coin in coins) {
    int res = coinChangeMemoization(coins, amount - coin, memo);
    if (res >= 0) minCoins = min(minCoins, res + 1);
  }
  memo[amount] = (minCoins == INF) ? -1 : minCoins;
  return memo[amount]!;
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

// 4. BFS Approach
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

// 5. Greedy + Backtracking
int coinChangeGreedyBacktrack(List<int> coins, int amount) {
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

// 6. Heap-Based Dijkstra Approach
int coinChangeHeapDijkstra(List<int> coins, int amount) {
  List<List<int>> heap = [];
  heap.add([amount, 0]);
  Set<int> visited = {};

  while (heap.isNotEmpty) {
    heap.sort((a, b) => a[1].compareTo(b[1])); // Min-heap property
    var current = heap.removeAt(0);
    int rem = current[0], steps = current[1];
    if (rem == 0) return steps;
    if (visited.contains(rem)) continue;
    visited.add(rem);

    for (int coin in coins) {
      if (rem - coin >= 0) {
        heap.add([rem - coin, steps + 1]);
      }
    }
  }
  return -1;
}

// ----------------------
// Real-world Applications
// ----------------------
// 1. Financial Systems: Optimal currency distribution for ATMs and online transactions.
// 2. Transportation Systems: Finding the best way to use bus/train tickets of different denominations.
// 3. Retail Payment Systems: Optimal change distribution at cash registers.
// 4. Game Development: Managing in-game currency exchange and purchases efficiently.
// 5. Logistics & Packing: Minimizing waste by finding optimal container sizes for shipping.
// 6. Digital Wallets: Converting digital credits into specific denominations efficiently.
