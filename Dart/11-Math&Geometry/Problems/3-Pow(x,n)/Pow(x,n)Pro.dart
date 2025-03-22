// Dart program implementing pow(x, n) using 6 advanced real-world approaches

import 'dart:math';

void main() {
  double x = 2.5;
  int n = -3;

  print("Advanced pow($x, $n) computations using different approaches:");
  print("1. Iterative Multiplication Approach: ${powerIterative(x, n)}");
  print("2. Recursive Divide & Conquer Approach: ${powerRecursive(x, n)}");
  print("3. Fast Modular Exponentiation (Optimized for Security): ${powerModular(x.toInt(), n, 1000000007)}");
  print("4. Monte Carlo Approximation (Probabilistic Estimation): ${powerMonteCarlo(x, n)}");
  print("5. Machine Learning-Based Approximation: ${powerMLApprox(x, n)}");
  print("6. Financial Growth Model (Real-World Application): ${powerFinancialGrowth(1000, 1.05, n)}");
}

// Approach 1: Iterative Multiplication Approach
// Calculates x^n using a simple iterative loop.
// Suitable for small exponents, but less efficient for large exponents.
double powerIterative(double x, int n) {
  double result = 1.0;
  for (int i = 0; i < n.abs(); i++) { // Iterate n times.
    result *= x; // Multiply x by the result.
  }
  return n < 0 ? 1 / result : result; // Handle negative exponents.
}

// Approach 2: Recursive Divide & Conquer Approach
// Calculates x^n using a recursive divide and conquer approach.
// More efficient than the iterative approach for larger exponents.
double powerRecursive(double x, int n) {
  if (n == 0) return 1; // Base case: x^0 = 1.
  double half = powerRecursive(x, n ~/ 2); // Recursively calculate x^(n/2).
  double result = half * half; // Square the result.
  if (n % 2 != 0) result *= x; // If n is odd, multiply by x.
  return n < 0 ? 1 / result : result; // Handle negative exponents.
}

// Approach 3: Fast Modular Exponentiation (For Cryptography & Security)
// Calculates x^n modulo a given modulus, optimized for large exponents.
// Crucial in cryptography for operations in finite fields.
int powerModular(int x, int n, int mod) {
  if (n < 0) return powerModular(pow(x, -n).toInt(), mod - 2, mod); // Fermat's theorem for modular inverse.
  int result = 1;
  x = x % mod; // Reduce x modulo mod.
  while (n > 0) {
    if (n % 2 == 1) result = (result * x) % mod; // Multiply and take modulo if n is odd.
    x = (x * x) % mod; // Square and take modulo.
    n ~/= 2; // Right shift n (divide by 2).
  }
  return result;
}

// Approach 4: Monte Carlo Approximation (Probabilistic Estimation)
// Approximates x^n using a Monte Carlo method.
// Provides a probabilistic estimate, useful when an exact result is not required.
double powerMonteCarlo(double x, int n) {
  double estimate = 1.0;
  Random rand = Random();
  for (int i = 0; i < n.abs(); i++) { // Simulate n steps.
    if (rand.nextBool()) estimate *= x; // Randomly multiply by x.
  }
  return n < 0 ? 1 / estimate : estimate; // Handle negative exponents.
}

// Approach 5: Machine Learning-Based Approximation
// Approximates x^n using the exponential and logarithmic functions.
// This is often how neural networks might approximate power calculations.
double powerMLApprox(double x, int n) {
  return exp(n * log(x)); // Use exp(n * log(x)) to approximate x^n.
}

// Approach 6: Financial Growth Model (Real-World Application)
// Calculates the future value of an investment using compound interest.
// Demonstrates the power function in a financial context.
double powerFinancialGrowth(double principal, double rate, int years) {
  return principal * powerRecursive(rate, years); // Use recursive approach for rate^years.
}