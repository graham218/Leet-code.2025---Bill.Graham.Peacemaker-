// Fibonacci Series using Dynamic Programming in Dart

// 1. Recursion with Memoization
// This approach stores computed values in a map to avoid redundant calculations.
import 'dart:math';

Map<int, int> memo = {};
int fibonacciMemo(int n) {
  if (memo.containsKey(n)) {
    return memo[n]!;
  }
  if (n <= 1) {
    return n;
  }
  memo[n] = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
  return memo[n]!;
}

// 2. Bottom-Up Approach (Tabulation)
// This uses an iterative approach with a list to store Fibonacci values.
int fibonacciTabulation(int n) {
  if (n <= 1) {
    return n;
  }
  List<int> table = List.filled(n + 1, 0);
  table[1] = 1;
  for (int i = 2; i <= n; i++) {
    table[i] = table[i - 1] + table[i - 2];
  }
  return table[n];
}

// 3. Space Optimized Bottom-Up Approach
// Instead of storing the entire table, we only keep the last two values.
int fibonacciSpaceOptimized(int n) {
  if (n <= 1) {
    return n;
  }
  int a = 0, b = 1;
  for (int i = 2; i <= n; i++) {
    int temp = b;
    b = a + b;
    a = temp;
  }
  return b;
}

// 4. Matrix Exponentiation
// This approach leverages matrix multiplication to compute Fibonacci in O(log n) time.
void matrixMultiply(List<List<int>> F, List<List<int>> M) {
  int x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
  int y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
  int z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
  int w = F[1][0] * M[0][1] + F[1][1] * M[1][1];

  F[0][0] = x;
  F[0][1] = y;
  F[1][0] = z;
  F[1][1] = w;
}

void matrixPower(List<List<int>> F, int n) {
  if (n <= 1) {
    return;
  }
  List<List<int>> M = [[1, 1], [1, 0]];
  matrixPower(F, n ~/ 2);
  matrixMultiply(F, F);
  if (n % 2 != 0) {
    matrixMultiply(F, M);
  }
}

int fibonacciMatrix(int n) {
  if (n <= 1) {
    return n;
  }
  List<List<int>> F = [[1, 1], [1, 0]];
  matrixPower(F, n - 1);
  return F[0][0];
}

// 5. Closed-Form Formula (Binet's Formula)
// Uses the golden ratio to compute Fibonacci numbers directly.
int fibonacciBinet(int n) {
  double phi = (1 + sqrt(5)) / 2;
  return ((pow(phi, n) - pow(-1 / phi, n)) / sqrt(5)).round();
}

void main() {
  int n = 10;
  print("Memoization: ${fibonacciMemo(n)}");
  print("Tabulation: ${fibonacciTabulation(n)}");
  print("Space Optimized: ${fibonacciSpaceOptimized(n)}");
  print("Matrix Exponentiation: ${fibonacciMatrix(n)}");
  print("Binet's Formula: ${fibonacciBinet(n)}");
}
