// Dart program implementing the power function pow(x, n) using 5 different approaches

import 'dart:math';

void main() {
  double x = 2.0;
  int n = 10;

  print("Computing pow($x, $n) using different approaches:");
  print("1. Iterative Approach: ${powerIterative(x, n)}");
  print("2. Recursive Approach: ${powerRecursive(x, n)}");
  print("3. Fast Exponentiation (Binary Exponentiation): ${powerFastExpo(x, n)}");
  print("4. Matrix Exponentiation (For Integer Bases): ${powerMatrix(x, n)}");
  print("5. Logarithmic Approach Using Math Library: ${powerLogarithmic(x, n)}");
}

// Approach 1: Iterative Approach (Brute Force)
// Calculates x^n iteratively using a loop.
// This approach is simple but less efficient for large exponents.
double powerIterative(double x, int n) {
  double result = 1.0;
  for (int i = 0; i < n.abs(); i++) { // Iterate n times.
    result *= x; // Multiply x to the result in each iteration.
  }
  return n < 0 ? 1 / result : result; // Handle negative exponents.
}

// Approach 2: Recursive Approach
// Calculates x^n recursively using a divide and conquer strategy.
// It's more efficient than the iterative approach for large exponents.
double powerRecursive(double x, int n) {
  if (n == 0) return 1; // Base case: x^0 = 1.
  double half = powerRecursive(x, n ~/ 2); // Recursively calculate x^(n/2).
  double result = half * half; // Square the result.
  if (n % 2 != 0) result *= x; // If n is odd, multiply by x.
  return n < 0 ? 1 / result : result; // Handle negative exponents.
}

// Approach 3: Fast Exponentiation (Binary Exponentiation)
// Calculates x^n using binary exponentiation, which is very efficient.
// It exploits the binary representation of the exponent to reduce the number of multiplications.
double powerFastExpo(double x, int n) {
  double result = 1.0;
  int exp = n.abs(); // Use absolute value of n.
  while (exp > 0) {
    if (exp % 2 == 1) result *= x; // If the least significant bit is 1, multiply by x.
    x *= x; // Square x.
    exp ~/= 2; // Right shift the exponent (divide by 2).
  }
  return n < 0 ? 1 / result : result; // Handle negative exponents.
}

// Approach 4: Matrix Exponentiation (Only for integer bases)
// Calculates x^n using matrix exponentiation.
// This approach is typically used for integer bases and large exponents.
// In this specific implementation, only integer bases are valid.
double powerMatrix(double x, int n) {
  if (x != x.toInt()) return powerFastExpo(x, n); // matrix exponentiation only works for integer bases.
  List<List<double>> base = [[x, 0], [0, 1]]; // Initialize the base matrix.
  List<List<double>> result = [[1, 0], [0, 1]]; // Initialize the result matrix.
  int exp = n.abs(); // Use absolute value of n.
  while (exp > 0) {
    if (exp % 2 == 1) result = matrixMultiply(result, base); // Multiply result by base.
    base = matrixMultiply(base, base); // Square the base matrix.
    exp ~/= 2; // Right shift the exponent.
  }
  return n < 0 ? 1 / result[0][0] : result[0][0]; // Handle negative exponents and return the result.
}

// Helper function to multiply two 2x2 matrices.
List<List<double>> matrixMultiply(List<List<double>> a, List<List<double>> b) {
  return [
    [a[0][0] * b[0][0] + a[0][1] * b[1][0], 0],
    [0, 1]
  ];
}

// Approach 5: Logarithmic Approach Using Math Library
// Calculates x^n using the built-in pow function from the math library.
// This is the simplest and most efficient approach in most cases.
double powerLogarithmic(double x, int n) {
  return pow(x, n).toDouble(); // Use the pow function.
}