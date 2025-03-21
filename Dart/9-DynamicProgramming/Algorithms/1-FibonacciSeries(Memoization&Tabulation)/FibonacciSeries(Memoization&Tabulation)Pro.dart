// Advanced Fibonacci Implementations in Dart

import 'dart:math';

// 1. Recursion with Memoization (Top-Down DP)
Map<int, int> memo = {};
int fibonacciMemo(int n) {
  if (memo.containsKey(n)) return memo[n]!;
  if (n <= 1) return n;
  memo[n] = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
  return memo[n]!;
}

// 2. Iterative Tabulation (Bottom-Up DP)
int fibonacciTabulation(int n) {
  if (n <= 1) return n;
  List<int> dp = List.filled(n + 1, 0);
  dp[1] = 1;
  for (int i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

// 3. Space Optimized Iterative Approach
int fibonacciSpaceOptimized(int n) {
  if (n <= 1) return n;
  int a = 0, b = 1;
  for (int i = 2; i <= n; i++) {
    int temp = a + b;
    a = b;
    b = temp;
  }
  return b;
}

// 4. Matrix Exponentiation (O(log n) Time Complexity)
void multiply(List<List<int>> F, List<List<int>> M) {
  int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
  int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
  int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
  int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
  F[0][0] = x;
  F[0][1] = y;
  F[1][0] = z;
  F[1][1] = w;
}

void power(List<List<int>> F, int n) {
  if (n <= 1) return;
  List<List<int>> M = [[1, 1], [1, 0]];
  power(F, n ~/ 2);
  multiply(F, F);
  if (n % 2 != 0) multiply(F, M);
}

int fibonacciMatrix(int n) {
  if (n <= 1) return n;
  List<List<int>> F = [[1, 1], [1, 0]];
  power(F, n - 1);
  return F[0][0];
}

// 5. Binet’s Formula (Using Golden Ratio, Approximation)
int fibonacciBinet(int n) {
  double phi = (1 + sqrt(5)) / 2;
  return ((pow(phi, n) - pow(-1 / phi, n)) / sqrt(5)).round();
}

// 6. Stream-based Fibonacci Generator (Real-time Processing)
Stream<int> fibonacciStream(int n) async* {
  int a = 0, b = 1;
  for (int i = 0; i < n; i++) {
    yield a;
    int temp = a + b;
    a = b;
    b = temp;
  }
}

void main() {
  int n = 10;
  print("Memoization: ${fibonacciMemo(n)}");
  print("Tabulation: ${fibonacciTabulation(n)}");
  print("Space Optimized: ${fibonacciSpaceOptimized(n)}");
  print("Matrix Exponentiation: ${fibonacciMatrix(n)}");
  print("Binet's Formula: ${fibonacciBinet(n)}");

  print("Stream-based Fibonacci:");
  fibonacciStream(n).listen((value) => print(value));
}

/* Real-World Applications of Fibonacci:
1. **Stock Market Analysis** - Fibonacci retracements used in technical analysis.
2. **Cryptography** - Fibonacci sequences in pseudo-random number generators.
3. **Computer Graphics** - Fibonacci spirals in procedural content generation.
4. **Nature & Biology** - Growth patterns in shells, flowers, and branching trees.
5. **Data Structures & Algorithms** - Fibonacci heaps for priority queues.
6. **Distributed Systems** - Backoff algorithms for rate limiting and retries.
*/
